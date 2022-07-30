#ifndef NMTOOLS_TESTING_ARRAY_CAST_HPP
#define NMTOOLS_TESTING_ARRAY_CAST_HPP

#include "nmtools/testing/platform.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/cast.hpp"

// macro for testing purpose

#if !defined(NMTOOLS_CAST_ARRAYS_NESTED_VEC) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION)
#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(name)
#endif
#if !defined(NMTOOLS_CAST_ARRAYS_DYNAMIC) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION)
#define NMTOOLS_CAST_ARRAYS_DYNAMIC(name)
#endif
#if !defined(NMTOOLS_CAST_ARRAYS_HYBRID) && defined(NMTOOLS_TESTING_DISABLE_HYBRID_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_HYBRID(name)
#endif
#if !defined(NMTOOLS_CAST_ARRAYS_FIXED) && defined(NMTOOLS_TESTING_DISABLE_FIXED_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_FIXED(name)
#endif

#ifndef NMTOOLS_CAST_ARRAYS_NESTED
#define NMTOOLS_CAST_ARRAYS_NESTED(name) \
inline auto name##_a = nmtools::cast(name, nmtools::array::kind::nested_arr);
#endif
// TODO: remove nested vector support
#ifndef NMTOOLS_CAST_ARRAYS_NESTED_VEC
#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(name) \
inline auto name##_v = nmtools::cast(name, nmtools::array::kind::nested_vec);
#endif
// TODO: add index_vec tag
#ifndef NMTOOLS_CAST_INDEX_VECTOR
#define NMTOOLS_CAST_INDEX_VECTOR(name) \
inline auto name##_v = nmtools::cast(name, nmtools::array::kind::nested_vec);
#endif
#ifndef NMTOOLS_CAST_ARRAYS_FIXED
#define NMTOOLS_CAST_ARRAYS_FIXED(name) \
inline auto name##_f = nmtools::cast(name, nmtools::array::kind::fixed);
#endif
#ifndef NMTOOLS_CAST_ARRAYS_HYBRID
#define NMTOOLS_CAST_ARRAYS_HYBRID(name) \
inline auto name##_h = nmtools::cast(name, nmtools::array::kind::hybrid);
#endif
#ifndef NMTOOLS_CAST_ARRAYS_DYNAMIC
#define NMTOOLS_CAST_ARRAYS_DYNAMIC(name) \
inline auto name##_d = nmtools::cast(name, nmtools::array::kind::dynamic);
#endif
// to easily add new kind
#ifndef NMTOOLS_CAST_ARRAYS_EXTRA
#define NMTOOLS_CAST_ARRAYS_EXTRA(name)
#endif

#ifndef NMTOOLS_CAST_ARRAYS
#define NMTOOLS_CAST_ARRAYS(name) \
NMTOOLS_CAST_ARRAYS_NESTED (name) \
NMTOOLS_CAST_ARRAYS_FIXED  (name) \
NMTOOLS_CAST_ARRAYS_HYBRID (name) \
NMTOOLS_CAST_ARRAYS_DYNAMIC(name) \
NMTOOLS_CAST_ARRAYS_EXTRA  (name) \

#endif // NMTOOLS_CAST_ARRAYS

// NOTE: quick workaround to weeds out nested vector while allowing vector
#ifndef NMTOOLS_CAST_INDEX_ARRAYS
#define NMTOOLS_CAST_INDEX_ARRAYS(name) \
NMTOOLS_CAST_ARRAYS_NESTED (name) \
NMTOOLS_CAST_ARRAYS_FIXED  (name) \
NMTOOLS_CAST_ARRAYS_HYBRID (name) \
NMTOOLS_CAST_ARRAYS_EXTRA  (name) \
NMTOOLS_CAST_INDEX_VECTOR  (name) \

#endif // NMTOOLS_CAST_ARRAYS

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

#endif // NMTOOLS_TESTING_ARRAY_CAST_HPP