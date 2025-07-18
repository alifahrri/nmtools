#ifndef NMTOOLS_TESTING_ARRAY_CAST_HPP
#define NMTOOLS_TESTING_ARRAY_CAST_HPP

#include "nmtools/testing/platform.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/utility/cast.hpp"

// macro for testing purpose

#if !defined(NMTOOLS_CAST_ARRAYS_NESTED_VEC) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION)
#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(name)
#define NMTOOLS_CAST_INDEX_VECTOR(name)
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
inline auto name##_a = nmtools::cast(name, nmtools::kind::nested_arr);
#endif
// TODO: remove nested vector support
#ifndef NMTOOLS_CAST_ARRAYS_NESTED_VEC
#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(name) \
inline auto name##_v = nmtools::cast(name, nmtools::kind::nested_vec);
#endif
// TODO: add index_vec tag
#ifndef NMTOOLS_CAST_INDEX_VECTOR
#define NMTOOLS_CAST_INDEX_VECTOR(name) \
inline auto name##_v = nmtools::cast(name, nmtools::kind::nested_vec);
#endif
#ifndef NMTOOLS_CAST_INDEX_STATIC_VECTOR
#define NMTOOLS_CAST_INDEX_STATIC_VECTOR(name) \
inline auto name##_sv = nmtools::cast(name, nmtools::kind::static_vec);
#endif
#ifndef NMTOOLS_CAST_ARRAYS_FIXED
#define NMTOOLS_CAST_ARRAYS_FIXED(name) \
inline auto name##_f = nmtools::cast(name, nmtools::kind::fixed);
#endif
#ifndef NMTOOLS_CAST_ARRAYS_HYBRID
#define NMTOOLS_CAST_ARRAYS_HYBRID(name) \
inline auto name##_h = nmtools::cast(name, nmtools::kind::hybrid);
#endif
#ifndef NMTOOLS_CAST_ARRAYS_DYNAMIC
#define NMTOOLS_CAST_ARRAYS_DYNAMIC(name) \
inline auto name##_d = nmtools::cast(name, nmtools::kind::dynamic);
#endif

#ifndef NMTOOLS_MAYBE_CAST_ARRAYS_NESTED
#define NMTOOLS_MAYBE_CAST_ARRAYS_NESTED(name) \
inline auto m_##name##_a = nmtools_maybe{nmtools::cast(name, nmtools::kind::nested_arr)};
#endif
// TODO: remove nested vector support
#ifndef NMTOOLS_MAYBE_CAST_ARRAYS_NESTED_VEC
#define NMTOOLS_MAYBE_CAST_ARRAYS_NESTED_VEC(name) \
inline auto m_##name##_v = nmtools_maybe{nmtools::cast(name, nmtools::kind::nested_vec)};
#endif
// TODO: add index_vec tag
#ifndef NMTOOLS_MAYBE_CAST_INDEX_VECTOR
#define NMTOOLS_MAYBE_CAST_INDEX_VECTOR(name) \
inline auto m_##name##_v = nmtools_maybe{nmtools::cast(name, nmtools::kind::nested_vec)};
#endif
#ifndef NMTOOLS_MAYBE_CAST_INDEX_STATIC_VECTOR
#define NMTOOLS_MAYBE_CAST_INDEX_STATIC_VECTOR(name) \
inline auto m_##name##_sv = nmtools_maybe{nmtools::cast(name, nmtools::kind::static_vec)};
#endif
#ifndef NMTOOLS_MAYBE_CAST_ARRAYS_FIXED
#define NMTOOLS_MAYBE_CAST_ARRAYS_FIXED(name) \
inline auto m_##name##_f = nmtools_maybe{nmtools::cast(name, nmtools::kind::fixed)};
#endif
#ifndef NMTOOLS_MAYBE_CAST_ARRAYS_HYBRID
#define NMTOOLS_MAYBE_CAST_ARRAYS_HYBRID(name) \
inline auto m_##name##_h = nmtools_maybe{nmtools::cast(name, nmtools::kind::hybrid)};
#endif
#ifndef NMTOOLS_MAYBE_CAST_ARRAYS_DYNAMIC
#define NMTOOLS_MAYBE_CAST_ARRAYS_DYNAMIC(name) \
inline auto m_##name##_d = nmtools_maybe{nmtools::cast(name, nmtools::kind::dynamic)};
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
NMTOOLS_CAST_INDEX_STATIC_VECTOR  (name) \

#endif // NMTOOLS_CAST_INDEX_ARRAYS

#ifndef NMTOOLS_MAYBE_CAST_INDEX_ARRAYS
#define NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(name) \
NMTOOLS_MAYBE_CAST_ARRAYS_NESTED (name) \
NMTOOLS_MAYBE_CAST_ARRAYS_FIXED  (name) \
NMTOOLS_MAYBE_CAST_ARRAYS_HYBRID (name) \
NMTOOLS_MAYBE_CAST_INDEX_VECTOR  (name) \
NMTOOLS_MAYBE_CAST_INDEX_STATIC_VECTOR  (name) \

#endif // NMTOOLS_CAST_ARRAYS

#if !defined(NMTOOLS_CAST_ARRAYS) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION) && !defined(NMTOOLS_TESTING_DISABLE_HYBRID_NDARRAY) && !defined(NMTOOLS_TESTING_DISABLE_FIXED_NDARRAY)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::kind::nested_arr); \
inline auto name##_f = nmtools::cast(name, nmtools::kind::fixed); \
inline auto name##_h = nmtools::cast(name, nmtools::kind::hybrid);

#elif !defined(NMTOOLS_CAST_ARRAYS) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION) && defined(NMTOOLS_TESTING_DISABLE_HYBRID_NDARRAY) && !defined(NMTOOLS_TESTING_DISABLE_FIXED_NDARRAY)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::kind::nested_arr); \
inline auto name##_f = nmtools::cast(name, nmtools::kind::fixed);

#elif !defined(NMTOOLS_CAST_ARRAYS) && defined(NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION) && defined(NMTOOLS_TESTING_DISABLE_HYBRID_NDARRAY) && defined(NMTOOLS_TESTING_DISABLE_FIXED_NDARRAY)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::kind::nested_arr); \

#elif !defined(NMTOOLS_CAST_ARRAYS)
#define NMTOOLS_CAST_ARRAYS(name) \
inline auto name##_a = nmtools::cast(name, nmtools::kind::nested_arr); \
inline auto name##_v = nmtools::cast(name, nmtools::kind::nested_vec); \
inline auto name##_f = nmtools::cast(name, nmtools::kind::fixed); \
inline auto name##_d = nmtools::cast(name, nmtools::kind::dynamic); \
inline auto name##_h = nmtools::cast(name, nmtools::kind::hybrid);

#endif // NMTOOLS_CAST_ARRAYS define

#ifndef NMTOOLS_CONSTEXPR_CAST_ARRAYS_NESTED
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_NESTED(name) \
constexpr inline auto name##_a = nmtools::cast(name, nmtools::kind::nested_arr);
#endif
#ifndef NMTOOLS_CONSTEXPR_CAST_ARRAYS_FIXED
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_FIXED(name) \
constexpr inline auto name##_f = nmtools::cast(name, nmtools::kind::nested_arr);
#endif
#ifndef NMTOOLS_CONSTEXPR_CAST_ARRAYS_HYBRID
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_HYBRID(name) \
constexpr inline auto name##_h = nmtools::cast(name, nmtools::kind::nested_arr);
#endif
// to easily add new kind
#ifndef NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name)
#endif

#if !defined(NMTOOLS_CONSTEXPR_CAST_ARRAYS)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS(name) \
NMTOOLS_CONSTEXPR_CAST_ARRAYS_NESTED (name) \
NMTOOLS_CONSTEXPR_CAST_ARRAYS_FIXED  (name) \
NMTOOLS_CONSTEXPR_CAST_ARRAYS_HYBRID (name) \
NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA  (name)
#endif // NMTOOLS_CONSTEXPR_CAST_ARRAYS

#ifndef NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS
#define NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(name) \
NMTOOLS_CONSTEXPR_CAST_ARRAYS_NESTED (name) \
NMTOOLS_CONSTEXPR_CAST_ARRAYS_FIXED  (name) \
NMTOOLS_CONSTEXPR_CAST_ARRAYS_HYBRID (name) \
NMTOOLS_CAST_ARRAYS_EXTRA  (name)
#endif // NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS

#endif // NMTOOLS_TESTING_ARRAY_CAST_HPP