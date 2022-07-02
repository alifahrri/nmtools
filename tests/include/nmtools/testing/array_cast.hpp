#ifndef NMTOOLS_TESTING_ARRAY_CAST_HPP
#define NMTOOLS_TESTING_ARRAY_CAST_HPP

#include "nmtools/testing/platform.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/kind.hpp"
#include "nmtools/array/utility/cast.hpp"

#ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
#include "nmtools/array/ndarray/dynamic.hpp"
#endif

// macro for testing purpose

#if !defined(NMTOOLS_CAST_ARRAYS) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION) && !defined(NMTOOLS_TESTING_DISABLE_HYBRID_NDARRAY) && !defined(NMTOOLS_TESTING_DISABLE_FIXED_NDARRAY)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::array::kind::nested_arr); \
inline auto name##_f = nmtools::cast(name, nmtools::array::kind::fixed); \
inline auto name##_h = nmtools::cast(name, nmtools::array::kind::hybrid);

#elif !defined(NMTOOLS_CAST_ARRAYS) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION) && defined(NMTOOLS_TESTING_DISABLE_HYBRID_NDARRAY) && !defined(NMTOOLS_TESTING_DISABLE_FIXED_NDARRAY)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::array::kind::nested_arr); \
inline auto name##_f = nmtools::cast(name, nmtools::array::kind::fixed);

#elif !defined(NMTOOLS_CAST_ARRAYS) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION) && defined(NMTOOLS_TESTING_DISABLE_HYBRID_NDARRAY) && defined(NMTOOLS_TESTING_DISABLE_FIXED_NDARRAY)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::array::kind::nested_arr); \

#elif !defined(NMTOOLS_CAST_ARRAYS)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::array::kind::nested_arr); \
inline auto name##_v = nmtools::cast(name, nmtools::array::kind::nested_vec); \
inline auto name##_f = nmtools::cast(name, nmtools::array::kind::fixed); \
inline auto name##_d = nmtools::cast(name, nmtools::array::kind::dynamic); \
inline auto name##_h = nmtools::cast(name, nmtools::array::kind::hybrid);

#endif // NMTOOLS_CAST_ARRAYS define

#if !defined(NMTOOLS_CONSTEXPR_CAST_ARRAYS)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS(name) \
constexpr inline auto name##_a = nmtools::cast(name, nmtools::array::kind::nested_arr); \
constexpr inline auto name##_f = nmtools::cast(name, nmtools::array::kind::fixed); \
constexpr inline auto name##_h = nmtools::cast(name, nmtools::array::kind::hybrid);
#endif // NMTOOLS_CONSTEXPR_CAST_ARRAYS

#include "nmtools/array/index/product.hpp"

namespace nmtools::array::kind
{
    // for testing purpose only
    struct nested_vector_t {};
    struct nested_array_t {};

    struct fixed_vec_t {};
    struct dynamic_vec_t {};

    // TODO: rename to vector, drop nested vector support
    inline constexpr auto nested_vec  = nested_vector_t {};
    inline constexpr auto nested_arr  = nested_array_t {};
    inline constexpr auto fixed_vec   = fixed_vec_t {};
    inline constexpr auto dynamic_vec = dynamic_vec_t {};
} // namespace nmtools::array::kind

namespace nmtools
{
    struct cast_kind_t {};

    namespace meta::error
    {
        template <typename...>
        struct CAST_KIND_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_t, typename kind_t>
    struct meta::resolve_optype<
        void, cast_kind_t, src_t, kind_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (meta::is_fixed_size_ndarray_v<src_t> && meta::is_same_v<kind_t,array::kind::fixed_t>) {
                using element_t = get_element_type_t<src_t>;
                static_assert( !meta::is_void_v<element_t>, "internal error" );
                // start with arbitrary shaped fixed_ndarray, then resize with src
                using fixed_kind_t = array::fixed_ndarray<element_t,1>;
                using type = resize_fixed_ndarray_t<fixed_kind_t,src_t>;
                return meta::as_value_v<type>;
            }
            else if constexpr (meta::is_fixed_size_ndarray_v<src_t> && meta::is_same_v<kind_t,array::kind::hybrid_t>) {
                using element_t = get_element_type_t<src_t>;
                constexpr auto shape = fixed_ndarray_shape_v<src_t>;
                constexpr auto numel = index::product(shape);
                constexpr auto dim = fixed_ndarray_dim_v<src_t>;
                using type = array::hybrid_ndarray<element_t,numel,dim>;
                return as_value_v<type>;
            }
            else if constexpr (meta::is_fixed_size_ndarray_v<src_t> && meta::is_same_v<kind_t,array::kind::nested_array_t>) {
                using type = meta::transform_bounded_array_t<src_t>;
                return as_value_v<type>;
            }
            else if constexpr (meta::is_same_v<kind_t,array::kind::dynamic_t>) {
                using element_t [[maybe_unused]] = get_element_type_t<src_t>;
        #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
                using type = array::dynamic_ndarray<element_t>;
        #else
                using type = void;
        #endif // NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
                return meta::as_value_v<type>;
            }
            else if constexpr (meta::is_same_v<kind_t,array::kind::nested_vector_t>) {
                using element_t [[maybe_unused]] = get_element_type_t<src_t>;
                [[maybe_unused]] constexpr auto dim = fixed_dim_v<src_t>;
        #ifndef NMTOOLS_DISABLE_STL
                using type = meta::make_nested_dynamic_array_t<std::vector,element_t,dim>;
        #else
                using type = void;
        #endif // NMTOOLS_DISABLE_STL
                return as_value_v<type>;
            } else /* */ {
                return as_value_v<error::CAST_KIND_UNSUPPORTED<src_t,kind_t>>;
            }
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // resolve_optype

    // TODO: move to main source
    template <typename src_t, typename kind_t>
    constexpr auto cast(const src_t& src, const kind_t&)
    {
        using ret_t = meta::resolve_optype_t<cast_kind_t,src_t,kind_t>;
        return cast(src, meta::as_value_v<ret_t>);
    } // cast
} // namespace nmtools

#endif // NMTOOLS_TESTING_ARRAY_CAST_HPP