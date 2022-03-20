#ifndef NMTOOLS_ARRAY_INDEX_RESHAPE_HPP
#define NMTOOLS_ARRAY_INDEX_RESHAPE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/ref.hpp"

namespace nmtools::index
{
    struct shape_reshape_t {};
    
    template <typename src_shape_t, typename dst_shape_t>
    constexpr auto shape_reshape(const src_shape_t& src_shape, const dst_shape_t& dst_shape)
    {
        using result_t = meta::resolve_optype_t<shape_reshape_t,src_shape_t,dst_shape_t>;

        if constexpr (meta::is_fail_v<result_t>) {
            // let the caller decides what to do
            return result_t {};
        } else if constexpr (meta::is_constant_index_array_v<result_t>) {
            // already computed
            return result_t {};
        } else {
            auto result = result_t {};
            using return_t = nmtools_maybe<result_t>;
            using element_t = meta::get_element_type_t<result_t>;
            using index_t = meta::make_signed_t<element_t>; // for comparison

            auto dst_shape_ = [&](){
                if constexpr (meta::is_constant_index_array_v<dst_shape_t>) {
                    return meta::to_value_v<dst_shape_t>;
                } else {
                    return index::ref(dst_shape);
                }
            }();

            // number of "-1" in dst_shape
            auto [minus_1_count, dst_numel] = [&](){
                auto minus_1_count = 0;
                auto dst_numel = (size_t)0;
                for (size_t i=0; i<len(dst_shape_); i++) {
                    auto d_i = at(dst_shape_,i);
                    if (i==0) {
                        dst_numel = 1;
                    }
                    if ((index_t)d_i == index_t(-1)) {
                        minus_1_count++;
                    } else {
                        dst_numel *= d_i;
                    }
                }
                return nmtools_tuple{minus_1_count,dst_numel};
            }();

            if (minus_1_count > 1) {
                return return_t{meta::Nothing};
            }

            auto src_numel = (size_t)product(src_shape);

            if ((minus_1_count == 0) && (src_numel != dst_numel)) {
                return return_t{meta::Nothing};
            } else if (static_cast<bool>(src_numel % dst_numel)) {
                return return_t{meta::Nothing};
            }

            if constexpr (meta::is_resizeable_v<result_t>) {
                result.resize(len(dst_shape_));
            }

            for (size_t i=0; i<(size_t)len(dst_shape_); i++) {
                auto d_i = at(dst_shape_,i);
                if ((index_t)d_i == index_t(-1)) {
                    at(result,i) = src_numel / dst_numel;
                } else {
                    at(result,i) = at(dst_shape_,i);
                }
            }

            return return_t{result};
        }
    } // shape_reshape
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_RESHAPE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct SHAPE_RESHAPE_INVALID : detail::fail_t {};
    } // namespace error
    
    template <typename src_shape_t, typename dst_shape_t>
    struct resolve_optype<void, index::shape_reshape_t, src_shape_t, dst_shape_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<src_shape_t> && is_constant_index_array_v<dst_shape_t>) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto dst_shape = to_value_v<dst_shape_t>;
                constexpr auto result = index::shape_reshape(src_shape,dst_shape);
                // assume maybe type (see above)
                if constexpr (static_cast<bool>(result)) {
                    constexpr auto DIM = nmtools::len(*result);
                    return template_reduce<DIM>([&](auto init, auto index_){
                        using init_t = type_t<decltype(init)>;
                        if constexpr (meta::is_same_v<init_t,none_t>) {
                            using type = nmtools_tuple<ct<at(*result,index_)>>;
                            return as_value_v<type>;
                        } else {
                            using type = append_type_t<init_t,ct<at(*result,index_)>>;
                            return as_value_v<type>;
                        }
                    }, as_value_v<none_t>);
                } else {
                    using type = error::SHAPE_RESHAPE_INVALID<src_shape_t,dst_shape_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_index_array_v<src_shape_t> && is_constant_index_array_v<dst_shape_t>) {
                constexpr auto dst_shape = to_value_v<dst_shape_t>;
                // NOTE: return the runtime type to not confuse the computation (make sure not skip)
                using m_dst_shape_t = remove_cvref_t<decltype(dst_shape)>;
                return as_value_v<resolve_optype_t<index::shape_reshape_t,src_shape_t,m_dst_shape_t>>;
            } else if constexpr (is_index_array_v<src_shape_t> && is_index_array_v<dst_shape_t>) {
                using element_t = get_element_type_t<dst_shape_t>;
                using indices_t = transform_bounded_array_t<dst_shape_t>;
                using type = replace_element_type_t<indices_t,make_unsigned_t<element_t>>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_RESHAPE_UNSUPPORTED<src_shape_t,dst_shape_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_RESHAPE_HPP