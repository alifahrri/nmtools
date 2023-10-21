#ifndef NMTOOLS_ARRAY_EVAL_SIMD_EVALUATOR_UFUNC_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_EVALUATOR_UFUNC_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/data.hpp"
#include "nmtools/array/eval/simd/index.hpp"
#include "nmtools/array/eval/simd/ufunc.hpp"
#include "nmtools/array/eval/simd/bit_width.hpp"

namespace nmtools::array
{
    template <typename simd_tag_t>
    struct simd_base_t
    {
        // TODO: do not make this a static member function
        template <typename dtype_t,typename op_type>
        static inline auto create_ufunc_simd_op(op_type op)
        {
            // TODO: tell the caller some combo is not supported
            using simd_t = simd::ufunc_simd_t<op_type,simd_tag_t,dtype_t>;
            return simd_t{op};
        }
    };

    template <typename view_t, typename simd_tag_t, typename resolver_t>
    struct evaluator_t<view_t,simd_base_t<simd_tag_t>,resolver_t>
    {
        using view_type    = const view_t&;
        using output_type  = meta::resolve_optype_t<resolver_t,view_t,none_t>;
        using context_type = const simd_base_t<simd_tag_t>&;
        using op_type      = typename view_t::op_type;

        view_type view;
        context_type context;

        template <typename output_t>
        constexpr auto eval_unary(output_t& output) const
        {
            auto out_shape = ::nmtools::shape(output);
            auto inp_shape = ::nmtools::shape(view);

            // TODO: provide common base/utility for error handling

            if (!::nmtools::utils::isequal(out_shape,inp_shape))
                return false;

            using ::nmtools::index::ndindex;
            auto out_index = ndindex(out_shape);
            auto inp_index = ndindex(inp_shape);

            using element_type = meta::get_element_type_t<output_t>;
            // TODO: do not static assert, tell the caller some combo is not supported
            static_assert(meta::is_floating_point_v<element_type>
                , "currently only support float/double");

            auto inp_ptr = nmtools::data(*nmtools::get<0>(view.array));
            auto out_ptr = nmtools::data(output);

            const auto op = context.template create_ufunc_simd_op<element_type>(view.op);
            const auto N = op.bit_width / (sizeof(element_type) * 8); // 8 means 8-bit

            const auto size = inp_index.size();
            // ex: 5 float; N=4; i=0..(5-4)
            // ex: 3 float; N=4; i=0..(3-4)
            for (size_t i=0; (i+N)<=size; i+=N) {
                // TODO: support aligned load/store
                const auto a = op.loadu(&inp_ptr[i]);
                const auto b = op.eval(a);
                op.storeu(&out_ptr[i],b);
            }

            // the rest of data
            // ex: 5 float, N=128/32=4; 5/4=1; i=1*4=4
            // ex: 3 float, N=4; M=3/4=0; i=M*N=0
            auto M = (size / N);
            for (size_t i=(M*N); i<size; i++) {
                // while the shape is the same,
                // the underlying type of indexing may be not
                auto inp_idx = inp_index[i];
                auto out_idx = out_index[i];
                apply_at(output,out_idx) = apply_at(view,inp_idx);
            }

            return true;
        }

        enum class BinaryCase : int
        {
            SAME_SHAPE=0,
            BROADCASTED_2D,
            INVALID=-1,
        };

        template <typename output_t>
        constexpr auto eval_reduction(output_t& output) const
        {
            auto out_shape  = ::nmtools::shape(output);
            auto view_shape = ::nmtools::shape(view);

            if (!::nmtools::utils::isequal(out_shape,view_shape))
                return false;

            using element_type = meta::get_element_type_t<output_t>;
            // TODO: do not static assert, tell the caller some combo is not supported
            static_assert(meta::is_num_v<element_type>
                , "currently only support numeric types");

            auto input_array_ptr = get_array(view);

            auto inp_shape = nmtools::shape(*input_array_ptr);

            auto inp_data_ptr = nmtools::data(*input_array_ptr);
            auto out_data_ptr = nmtools::data(output);

            constexpr auto bit_width = meta::bit_width_v<simd_tag_t>;
            const auto op = context.template create_ufunc_simd_op<element_type>(view.op);
            constexpr auto N = decltype(op)::bit_width / (sizeof(element_type) * 8); // 8 = 8-bit

            const auto size = nmtools::size(*input_array_ptr);

            auto out_size = nmtools::size(output);
            auto out_dim  = dim(output);
            using axis_type = decltype(view.axis);
            if (out_size == 1) {
                // reduce all to single scalar

                // vertical op
                auto reg = op.set1(0);
                for (size_t i=0; (i+N)<=size; i+=N) {
                    const auto operand = op.loadu(&inp_data_ptr[i]);
                    reg = op.eval(reg,operand);
                }

                // horizontal op
                element_type tmp_res[N];
                op.storeu(&tmp_res[0],reg);
                element_type result = tmp_res[0];
                for (size_t i=1; i<N; i++) {
                    result = view.op(result,tmp_res[i]);
                }

                // leftover
                auto M = (size/N);
                for (size_t i=(M*N); i<size; i++) {
                    result = view.op(result,inp_data_ptr[i]);
                }

                if constexpr (meta::is_num_v<output_t>) {
                    output = result;
                } else {
                    auto out_data_ptr = nmtools::data(output);
                    *out_data_ptr = result;
                }
                return true;
            }
            if constexpr (meta::is_index_v<axis_type>) {
                if (out_dim != 2) {
                    return false;
                }
                using index::ReductionKind, index::SIMD;
                const auto n_elem_pack = meta::as_type_v<N>;
                // vertical reduction
                if (view.axis == 0) {
                    const auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
                    const auto enumerator = index::reduction_2d_enumerator(reduction_kind,n_elem_pack,inp_shape,out_shape);
                    for (size_t i=0; i<enumerator.size(); i++) {
                        auto [out_pack, inp_pack] = enumerator[i];
                        auto [out_tag,out_offset] = out_pack;
                        auto [inp_tag,inp_offset] = inp_pack;
                        switch (out_tag) {
                            case SIMD::ACCUMULATE_PACKED: {
                                auto inp_pack = op.loadu(&inp_data_ptr[inp_offset]);
                                auto out_pack = op.loadu(&out_data_ptr[out_offset]);
                                auto tmp = op.eval(out_pack,inp_pack);
                                op.storeu(&out_data_ptr[out_offset],tmp);
                            } break;
                            case SIMD::ACCUMULATE: {
                                out_data_ptr[out_offset] = view.op(out_data_ptr[out_offset],inp_data_ptr[inp_offset]);
                            } break;
                            default:
                                break;
                        }
                    }
                }  else if (view.axis == 1) {
                    const auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
                    const auto enumerator = index::reduction_2d_enumerator(reduction_kind,n_elem_pack,inp_shape,out_shape);
                    auto accum = op.set1(0);
                    for (size_t i=0; i<enumerator.size(); i++) {
                        auto [out_pack, inp_pack] = enumerator[i];
                        auto [out_tag,out_offset] = out_pack;
                        auto [inp_tag,inp_offset] = inp_pack;
                        switch (inp_tag) {
                            case SIMD::PACKED: {
                                auto inp_pack = op.loadu(&inp_data_ptr[inp_offset]);
                                accum = op.eval(accum,inp_pack);
                            } break;
                            default: {
                                constexpr auto n_simd_pack = (bit_width / (sizeof(element_type) * 8));
                                constexpr auto n_possible_padding = n_simd_pack - 1;
                                meta::template_for<n_possible_padding>([&](auto pad){
                                    constexpr auto n_pad = static_cast<int>(pad) + 1;
                                    if (static_cast<int>(inp_tag) == n_pad) {
                                        element_type padded_inp[n_simd_pack] = {0};
                                        size_t i=0;
                                        for (; i<(n_simd_pack-n_pad); i++) {
                                            padded_inp[i] = inp_data_ptr[inp_offset+i];
                                        }
                                        for (; i<n_simd_pack; i++) {
                                            padded_inp[i] = 0;
                                        }
                                        auto padded_reg = op.loadu(padded_inp);
                                        accum = op.eval(accum,padded_reg);
                                    }
                                });
                            } break;
                        }
                        switch (out_tag) {
                            case SIMD::ACCUMULATE: {
                                // horizontal op
                                element_type tmp_res[N];
                                op.storeu(&tmp_res[0],accum);
                                element_type result = tmp_res[0];
                                for (size_t i=1; i<N; i++) {
                                    result = view.op(result,tmp_res[i]);
                                }
                                out_data_ptr[out_offset] = result;
                                accum = op.set1(0);
                            } break;
                            default:
                                break;
                        }
                    }
                }
                return true;
            }

            return false;
        }

        template <typename output_t>
        constexpr auto eval_binary(output_t& output) const
        {
            auto out_shape = ::nmtools::shape(output);
            auto inp_shape = ::nmtools::shape(view);

            if (!::nmtools::utils::isequal(out_shape,inp_shape))
                return false;

            using ::nmtools::index::ndindex;
            auto out_index = ndindex(out_shape);
            auto inp_index = ndindex(inp_shape);

            using element_type = meta::get_element_type_t<output_t>;
            // TODO: do not static assert, tell the caller some combo is not supported
            static_assert(meta::is_num_v<element_type>
                , "currently only support numeric types");

            auto input_array_ptr = get_array(view);

            auto lhs_ptr = nmtools::get<0>(input_array_ptr);
            auto rhs_ptr = nmtools::get<1>(input_array_ptr);

            auto lhs_data_ptr = nmtools::data(*lhs_ptr);
            auto rhs_data_ptr = nmtools::data(*rhs_ptr);
            auto out_data_ptr = nmtools::data(output);

            auto lhs_shape = nmtools::shape(*lhs_ptr);
            auto rhs_shape = nmtools::shape(*rhs_ptr);

            const auto op = context.template create_ufunc_simd_op<element_type>(view.op);
            constexpr auto N = decltype(op)::bit_width / (sizeof(element_type) * 8); // 8 = 8-bit

            // assume same size, layout, etc;
            // TODO: handle different size, layout, broadcasting

            auto binary_case = BinaryCase::INVALID;
            if (utils::isequal(lhs_shape,rhs_shape)) {
                binary_case = BinaryCase::SAME_SHAPE;
            } else if ((len(lhs_shape) == len(rhs_shape)) && (len(rhs_shape) == 2)) {
                binary_case = BinaryCase::BROADCASTED_2D;
            }

            if (binary_case == BinaryCase::INVALID) {
                return false;
            }

            const auto size = inp_index.size();

            if (binary_case == BinaryCase::SAME_SHAPE) {
                for (size_t i=0; (i+N)<=size; i+=N) {
                    // TODO: support aligned load/store
                    const auto lhs = op.loadu(&lhs_data_ptr[i]);
                    const auto rhs = op.loadu(&rhs_data_ptr[i]);
                    const auto res = op.eval(lhs,rhs);
                    op.storeu(&out_data_ptr[i],res);
                }

                // leftover:
                auto M = (size / N);
                for (size_t i=(M*N); i<size; i++) {
                    auto inp_idx = inp_index[i];
                    auto out_idx = out_index[i];
                    apply_at(output,out_idx) = apply_at(view,inp_idx);
                }
            } else if (binary_case == BinaryCase::BROADCASTED_2D) {
                const auto n_elem_pack = meta::as_type<N>{};
                const auto enumerator = index::binary_2d_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);

                for (auto i=0ul; i<enumerator.size(); i++) {
                    // do not use structured bindings to avoid clang complaining
                    auto idx = enumerator[i];
                    auto out_idx = nmtools::get<0>(idx);
                    auto lhs_idx = nmtools::get<1>(idx);
                    auto rhs_idx = nmtools::get<2>(idx);
                    auto out_tag     = nmtools::get<0>(out_idx);
                    auto out_ptr_idx = nmtools::get<1>(out_idx);
                    auto lhs_tag     = nmtools::get<0>(lhs_idx);
                    auto lhs_ptr_idx = nmtools::get<1>(lhs_idx);
                    auto rhs_tag     = nmtools::get<0>(rhs_idx);
                    auto rhs_ptr_idx = nmtools::get<1>(rhs_idx);
                    if (out_tag == index::SIMD::PACKED) {
                        const auto lhs = (lhs_tag == index::SIMD::PACKED
                            ? op.loadu(&lhs_data_ptr[lhs_ptr_idx])
                            : op.set1(lhs_data_ptr[lhs_ptr_idx])
                        );
                        const auto rhs = (rhs_tag == index::SIMD::PACKED
                            ? op.loadu(&rhs_data_ptr[rhs_ptr_idx])
                            : op.set1(rhs_data_ptr[rhs_ptr_idx])
                        );
                        const auto res = op.eval(lhs,rhs);
                        op.storeu(&out_data_ptr[out_ptr_idx],res);
                    } else {
                        out_data_ptr[out_ptr_idx] = view.op(lhs_data_ptr[lhs_ptr_idx],rhs_data_ptr[rhs_ptr_idx]);
                    }
                }
            }

            return true;
        }

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
        {
            if constexpr (meta::is_reduction_v<view_type>) {
                return this->eval_reduction(output);
            } else {
                constexpr auto arity = meta::ufunc_arity_v<view_type>;
                static_assert( (arity == 1) || (arity == 2), "unsupported arity ufunc type");
                if constexpr (arity == 1) {
                    return this->eval_unary(output);
                } else if constexpr (arity == 2) {
                    return this->eval_binary(output);
                } else {
                    return false;
                }
            }
        } // operator()

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

#endif // NMTOOLS_ARRAY_EVAL_SIMD_EVALUATOR_UFUNC_HPP