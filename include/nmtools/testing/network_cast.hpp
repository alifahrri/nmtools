#ifndef NMTOOLS_TESTING_NETWORK_CAST_HPP
#define NMTOOLS_TESTING_NETWORK_CAST_HPP

#include "nmtools/testing/platform.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/network/cast.hpp"

#if !defined(NMTOOLS_CAST_NETWORK_ARRAY)
#define NMTOOLS_CAST_NETWORK_ARRAY(name) \
inline auto name##_a_a = nmtools::network::cast(name, nmtools::network::kind::array, nmtools::network::kind::array);
#endif // NMTOOLS_CAST_NETWORK_ARRAY

#if !defined(NMTOOLS_CAST_NETWORK_STATIC_VECTOR)
#define NMTOOLS_CAST_NETWORK_STATIC_VECTOR(name) \
inline auto name##_sv_sv = nmtools::network::cast(name, nmtools::network::kind::static_vec, nmtools::network::kind::static_vec);
#endif // NMTOOLS_CAST_NETWORK_STATIC_VECTOR

#if !defined(NMTOOLS_CAST_NETWORK_VECTOR)
#define NMTOOLS_CAST_NETWORK_VECTOR(name) \
inline auto name##_v_v = nmtools::network::cast(name, nmtools::network::kind::vector, nmtools::network::kind::vector);
#endif // NMTOOLS_CAST_NETWORK_VECTOR

#if !defined(NMTOOLS_CAST_NETWORK_ARRAY_STATIC_VECTOR)
#define NMTOOLS_CAST_NETWORK_ARRAY_STATIC_VECTOR(name) \
inline auto name##_a_sv = nmtools::network::cast(name, nmtools::network::kind::array, nmtools::network::kind::static_vec);
#endif // NMTOOLS_CAST_NETWORK_ARRAY_STATIC_VECTOR

#if !defined(NMTOOLS_CAST_NETWORK_ARRAY_VECTOR)
#define NMTOOLS_CAST_NETWORK_ARRAY_VECTOR(name) \
inline auto name##_a_v = nmtools::network::cast(name, nmtools::network::kind::array, nmtools::network::kind::vector);
#endif // NMTOOLS_CAST_NETWORK_ARRAY_VECTOR

#if !defined(NMTOOLS_CAST_NETWORK_STATIC_VECTOR_VECTOR)
#define NMTOOLS_CAST_NETWORK_STATIC_VECTOR_VECTOR(name) \
inline auto name##_sv_v = nmtools::network::cast(name, nmtools::network::kind::static_vec, nmtools::network::kind::vector);
#endif // NMTOOLS_CAST_NETWORK_STATIC_VECTOR_VECTOR

#if !defined(NMTOOLS_CAST_NETWORK_VECTOR_STATIC_VECTOR)
#define NMTOOLS_CAST_NETWORK_VECTOR_STATIC_VECTOR(name) \
inline auto name##_v_sv = nmtools::network::cast(name, nmtools::network::kind::vector, nmtools::network::kind::static_vec);
#endif // NMTOOLS_CAST_NETWORK_VECTOR_STATIC_VECTOR

#ifndef NMTOOLS_CAST_NETWORK
#define NMTOOLS_CAST_NETWORK(name) \
NMTOOLS_CAST_NETWORK_ARRAY(name) \
NMTOOLS_CAST_NETWORK_STATIC_VECTOR(name) \
NMTOOLS_CAST_NETWORK_VECTOR(name) \
NMTOOLS_CAST_NETWORK_ARRAY_STATIC_VECTOR(name) \
NMTOOLS_CAST_NETWORK_ARRAY_VECTOR(name) \
NMTOOLS_CAST_NETWORK_STATIC_VECTOR_VECTOR(name) \
NMTOOLS_CAST_NETWORK_VECTOR_STATIC_VECTOR(name) \

#endif // NMTOOLS_CAST_NETWORK


#if !defined(NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY)
#define NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY(name) \
constexpr inline auto name##_a_a_ct = nmtools::network::cast(name, nmtools::network::kind::array, nmtools::network::kind::array);
#endif // NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY

#if !defined(NMTOOLS_CONSTEXPR_CAST_NETWORK_STATIC_VECTOR)
#define NMTOOLS_CONSTEXPR_CAST_NETWORK_STATIC_VECTOR(name) \
constexpr inline auto name##_sv_sv_ct = nmtools::network::cast(name, nmtools::network::kind::static_vec, nmtools::network::kind::static_vec);
#endif // NMTOOLS_CONSTEXPR_CAST_NETWORK_STATIC_VECTOR

#if !defined(NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY_STATIC_VECTOR)
#define NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY_STATIC_VECTOR(name) \
constexpr inline auto name##_a_sv_ct = nmtools::network::cast(name, nmtools::network::kind::array, nmtools::network::kind::static_vec);
#endif // NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY_STATIC_VECTOR

#ifndef NMTOOLS_CONSTEXPR_CAST_NETWORK
#define NMTOOLS_CONSTEXPR_CAST_NETWORK(name) \
NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY(name) \
NMTOOLS_CONSTEXPR_CAST_NETWORK_STATIC_VECTOR(name) \
NMTOOLS_CONSTEXPR_CAST_NETWORK_ARRAY_STATIC_VECTOR(name) \

#endif // NMTOOLS_CONSTEXPR_CAST_NETWORK

#endif // NMTOOLS_TESTING_NETWORK_CAST_HPP