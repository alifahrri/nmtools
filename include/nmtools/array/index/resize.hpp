#ifndef NMTOOLS_ARRAY_INDEX_RESIZE_HPP
#define NMTOOLS_ARRAY_INDEX_RESIZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

#include "nmtools/ndarray.hpp"

namespace nmtools::index
{
    struct shape_resize_t {};

    template <typename src_shape_t, typename dst_shape_t>
    constexpr auto check_shape_resize(const src_shape_t& src_shape, const dst_shape_t& dst_shape)
    {
        auto src_dim = (nm_size_t)len(src_shape);
        auto dst_dim = (nm_size_t)len(dst_shape);

        if (src_dim != dst_dim) {
            return false;
        }

        bool valid = true;
        for (nm_size_t i=0; valid && (i<src_dim); i++) {
            valid = valid && (at(dst_shape,i) > 0);
        }

        return valid;
    }

    template <typename src_shape_t, typename dst_shape_t>
    constexpr auto shape_resize([[maybe_unused]] const src_shape_t& src_shape, const dst_shape_t& dst_shape)
    {
        using return_t = meta::resolve_optype_t<shape_resize_t,src_shape_t,dst_shape_t>;
        
        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            auto valid = check_shape_resize(src_shape,dst_shape);
            // assume return_t is maybe type
            if (!valid) {
                return return_t{meta::Nothing};
            } else {
                using result_t = meta::get_maybe_type_t<return_t>;
                auto result = result_t{};
                auto dim = len(dst_shape);
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dim);
                }
                for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                    at(result,i) = at(dst_shape,i);
                }
                return return_t{result};
            }
        } else {
            return return_t {};
        }
    } // shape_resize

    struct resize_t {};

    template <typename indices_t, typename src_shape_t, typename dst_shape_t>
    constexpr auto resize(const indices_t& indices, const src_shape_t& src_shape, const dst_shape_t& dst_shape)
    {
        using result_t = meta::resolve_optype_t<resize_t,indices_t,src_shape_t,dst_shape_t>;
        using index_t  = meta::get_index_element_type_t<result_t>;

        auto result = result_t{};
        
        const auto dim = len(src_shape);
        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(dim);
        }

        for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
            at(result,i) = static_cast<index_t>(float(at(src_shape,i) * at(indices,i) / at(dst_shape,i)));
        }

        return result;
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_RESIZE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct SHAPE_RESIZE_INVALID : detail::fail_t {};

        template <typename...>
        struct RESIZE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename dst_shape_t>
    struct resolve_optype<void,index::shape_resize_t,src_shape_t,dst_shape_t>
    {
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto SRC_DIM = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto SRC_B_DIM = bounded_size_v<src_shape_t>;
            [[maybe_unused]] constexpr auto DST_DIM = len_v<dst_shape_t>;
            [[maybe_unused]] constexpr auto DST_B_DIM = bounded_size_v<dst_shape_t>;
            using element_t [[maybe_unused]] = make_unsigned_t<get_index_element_type_t<dst_shape_t>>;
            if constexpr (!is_index_array_v<src_shape_t> || !is_index_array_v<dst_shape_t>) {
                using type = error::SHAPE_RESIZE_UNSUPPORTED<src_shape_t,dst_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<src_shape_t> && is_constant_index_array_v<dst_shape_t>) {
                constexpr auto SRC_SHAPE = to_value_v<src_shape_t>;
                constexpr auto DST_SHAPE = to_value_v<dst_shape_t>;
                constexpr auto IS_VALID  = index::check_shape_resize(SRC_SHAPE,DST_SHAPE);
                if constexpr (!IS_VALID) {
                    using type = error::SHAPE_RESIZE_INVALID<src_shape_t,dst_shape_t>;
                    return as_value_v<type>;
                } else {
                    using type = dst_shape_t;
                    return as_value_v<type>;
                }
            } else if constexpr (DST_DIM > 0) {
                using result_type [[maybe_unused]] = nmtools_array<element_t,DST_DIM>;
                if constexpr (SRC_DIM > 0) {
                    if constexpr (DST_DIM != SRC_DIM) {
                        using type = error::SHAPE_RESIZE_INVALID<src_shape_t,dst_shape_t>;
                        return as_value_v<type>;
                    } else {
                        // NOTE: at runtime: make sure dst_shape > 0
                        using type = nmtools_maybe<result_type>;
                        return as_value_v<type>;
                    }
                } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)>) {
                    if constexpr (SRC_B_DIM < DST_DIM) {
                        using type = error::SHAPE_RESIZE_INVALID<src_shape_t,dst_shape_t>;
                        return as_value_v<type>;
                    } else {
                        // NOTE: at runtime: make sure dst_shape > 0
                        using type = nmtools_maybe<result_type>;
                        return as_value_v<type>;
                    }
                } else {
                    using type = nmtools_maybe<result_type>;
                    return as_value_v<type>;
                }
            } else if constexpr (!is_fail_v<decltype(DST_B_DIM)>) {
                using result_type [[maybe_unused]] = nmtools_static_vector<element_t,DST_B_DIM>;
                using type = nmtools_maybe<result_type>;
                return as_value_v<type>;
            } else {
                // TODO: use small vector instead
                using result_type = nmtools_list<element_t>;
                using type = nmtools_maybe<result_type>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename indices_t, typename src_shape_t, typename dst_shape_t>
    struct resolve_optype<void,index::resize_t,indices_t,src_shape_t,dst_shape_t>
    {
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto DIM = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto B_DIM = bounded_size_v<src_shape_t>;
            using element_t [[maybe_unused]] = make_unsigned_t<get_index_element_type_t<src_shape_t>>;
            if constexpr (!is_index_array_v<indices_t> || !is_index_array_v<src_shape_t> || !is_index_array_v<dst_shape_t>) {
                using type = error::RESIZE_UNSUPPORTED<indices_t,src_shape_t,dst_shape_t>;
                return as_value_v<type>;
            } else if constexpr (DIM > 0) {
                using type = nmtools_array<element_t,DIM>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                using type = nmtools_static_vector<element_t,B_DIM>;
                return as_value_v<type>;
            } else {
                // TODO: use small vector
                using type = nmtools_list<element_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_RESIZE_HPP