#ifndef NMTOOLS_ARRAY_EVAL_SIMD_EVALUATOR_MATMUL_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_EVALUATOR_MATMUL_HPP

#include "nmtools/evaluator/simd/evaluator/ufunc.hpp"
#include "nmtools/evaluator/simd/index/matmul.hpp"
#include "nmtools/evaluator/simd/bit_width.hpp"
#include "nmtools/array/matmul.hpp"

namespace nmtools
{
    template <typename simd_tag_t, typename resolver_t, typename...matmul_args_t>
    struct evaluator_t<view::decorator_t<view::matmul_t,matmul_args_t...>, simd_base_t<simd_tag_t>, resolver_t>
    {
        using matmul_type  = view::decorator_t<view::matmul_t,matmul_args_t...>;
        using view_type    = const matmul_type&;
        using output_type  = meta::resolve_optype_t<resolver_t,matmul_type,none_t>;
        using context_type = const simd_base_t<simd_tag_t>&;

        view_type view;
        context_type context;

        template <typename output_t>
        auto eval_matmul(output_t& output) const
        {
            auto out_shape = ::nmtools::shape(output);
            auto inp_shape = ::nmtools::shape(view);

            // TODO: provide common base/utility for error handling

            if (!::nmtools::utils::isequal(out_shape,inp_shape))
                return false;

            using ::nmtools::index::ndindex;

            using element_type = meta::get_element_type_t<output_t>;
            // TODO: do not static assert, tell the caller some combo is not supported
            static_assert(meta::is_num_v<element_type>
                , "currently only support numeric types");

            auto input_array_ptr = get_array(view);

            auto lhs_ptr = nmtools::get<0>(input_array_ptr);
            auto rhs_ptr = nmtools::get<1>(input_array_ptr);
            using lhs_type [[maybe_unused]] = meta::remove_cvref_pointer_t<decltype(lhs_ptr)>;
            using rhs_type [[maybe_unused]] = meta::remove_cvref_pointer_t<decltype(rhs_ptr)>;

            // TODO: propagate error to call-site instead of static assert
            constexpr auto contiguous_axis = meta::contiguous_axis_v<rhs_type>;
            static_assert( contiguous_axis == 0
                , "currently only support rhs with column major storage"
            );

            auto lhs_data_ptr = nmtools::data(*lhs_ptr);
            auto rhs_data_ptr = nmtools::data(*rhs_ptr);
            auto out_data_ptr = nmtools::data(output);

            auto lhs_shape = nmtools::shape(*lhs_ptr);
            auto rhs_shape = nmtools::shape(*rhs_ptr);

            // only support non-batched array for now
            // only support rhs with transposed storage for now
            // assume output already resized

            using simd_op_t = simd::simd_op_t<simd_tag_t,element_type>;
            const auto op = simd_op_t{};

            constexpr auto bit_width = meta::bit_width_v<simd_tag_t>;
            constexpr auto n_simd_pack = (bit_width / (sizeof(element_type) * 8));
            constexpr auto n_elem_pack = meta::as_type<n_simd_pack>{};

            const auto enumerator = index::matmul_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);
            for (const auto [out_tag,out_ptr_idx,inner_enumerator] : enumerator) {
                auto result_pack = op.set1(0);
                for (const auto simd_pack : inner_enumerator) {
                    const auto [out_idx,lhs_idx,rhs_idx] = simd_pack;
                    const auto lhs_tag = nmtools::get<0>(lhs_idx);
                    const auto out_ptr_idx = nmtools::get<1>(out_idx);
                    const auto lhs_ptr_idx = nmtools::get<1>(lhs_idx);
                    const auto rhs_ptr_idx = nmtools::get<1>(rhs_idx);
                    switch (lhs_tag) {
                        using index::SIMD;
                        case SIMD::PACKED:
                        {
                            auto lhs = op.loadu(&lhs_data_ptr[lhs_ptr_idx]);
                            auto rhs = op.loadu(&rhs_data_ptr[rhs_ptr_idx]);
                            result_pack = op.fmadd(lhs,rhs,result_pack);
                        } break;
                        default:
                        {
                            constexpr auto n_possible_padding = n_simd_pack - 1;
                            meta::template_for<n_possible_padding>([&](auto pad){
                                constexpr auto n_pad = static_cast<int>(pad) + 1;
                                if (static_cast<int>(lhs_tag) == n_pad) {
                                    element_type lhs_array[n_simd_pack] = {0};
                                    element_type rhs_array[n_simd_pack] = {0};
                                    size_t i=0;
                                    for (; i<(n_simd_pack-n_pad); i++) {
                                        lhs_array[i] = lhs_data_ptr[lhs_ptr_idx+i];
                                        rhs_array[i] = rhs_data_ptr[rhs_ptr_idx+i];
                                    }
                                    for (; i<n_simd_pack; i++) {
                                        lhs_array[i] = 0;
                                        rhs_array[i] = 0;
                                    }
                                    auto lhs = op.loadu(lhs_array);
                                    auto rhs = op.loadu(rhs_array);
                                    result_pack = op.fmadd(lhs,rhs,result_pack);
                                }
                            });
                        } break;
                    }
                    // horizontal op
                    element_type tmp_res[n_simd_pack];
                    op.storeu(&tmp_res[0],result_pack);
                    element_type result = tmp_res[0];
                    for (size_t i=1; i<n_simd_pack; i++) {
                        result += tmp_res[i];
                    }
                    out_data_ptr[out_ptr_idx] = result;
                }
            }
            return true;
        }

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
        {
            return this->eval_matmul(output);
        }

        // TODO: provide common base/utility
        template <typename output_t=output_type, meta::enable_if_t<!meta::is_void_v<output_t>,int> = 0>
        constexpr auto operator()() const
        {
            using result_t = meta::transform_bounded_array_t<output_t>;
            auto output = result_t{};
            if constexpr (meta::is_resizable_v<result_t>) {
                auto inp_shape = ::nmtools::shape(view);
                ::nmtools::detail::apply_resize(output,inp_shape);
            }

            (*this)(output);

            return output;
        } // operator()

        // TODO: provide common base/utility
        template <typename output_t>
        constexpr auto operator()(meta::as_value<output_t>) const
        {
            return (*this).template operator()<output_t>();
        } // operator()

        // TODO: provide common base/utility
        constexpr auto operator()(none_t) const
        {
            return (*this)();
        } // operator()
    };
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_EVALUATOR_MATMUL_HPP