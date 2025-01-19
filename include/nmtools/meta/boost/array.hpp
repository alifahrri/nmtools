#ifndef NMTOOLS_META_BOOST_ARRAY_HPP
#define NMTOOLS_META_BOOST_ARRAY_HPP

#include <boost/array.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/vector.hpp>

#include "nmtools/meta/array.hpp"
#include "nmtools/meta/traits.hpp"

#include <boost/version.hpp>
#define BOOST_VERSION_MAJOR     (BOOST_VERSION / 100000)
#define BOOST_VERSION_MINOR     ((BOOST_VERSION / 100) % 1000)
#define BOOST_VERSION_SUB_MINOR (BOOST_VERSION % 100)

#define XSTR(x) STR(x)
#define STR(x) #x

#if 0
#pragma message "BOOST_VERSION_MAJOR: " XSTR(BOOST_VERSION_MAJOR)
#pragma message "BOOST_VERSION_MINOR: " XSTR(BOOST_VERSION_MINOR)
#pragma message "BOOST_VERSION_SUB_MINOR: " XSTR(BOOST_VERSION_SUB_MINOR)
#endif

#undef XSTR
#undef STR

#ifndef BOOST_CONTAINER_OPTIONS_MIN_VERSION
#define BOOST_CONTAINER_OPTIONS_MIN_VERSION (65)
#endif

namespace nmtools::meta
{
    template <typename T, std::size_t N>
    struct get_element_type<
        ::boost::array<T,N>
    >
    {
        using type = T;
    }; // get_element_type

    template <typename T, std::size_t N>
    struct fixed_ndarray_shape<
        ::boost::array<T,N>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_num_v<T>) {
                return ::boost::array<size_t,1>{N};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<::boost::array<T,N>>{};
            }
            // NOTE: doesn't allow recursion type yet, nested type unsupported yet
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename T, std::size_t N>
    struct fixed_shape<
        ::boost::array<T,N>
    >
    {
        // NOTE: doesn't allow recursion type yet, nested type unsupported yet
        static constexpr auto value = nmtools_array<size_t,1>{N};
        using value_type = decltype(value);
    };

    template <typename T, std::size_t N>
    struct fixed_size<
        ::boost::array<T,N>
    >
    {
        static constexpr auto value = N;
    };

    // TODO: remove, update default impl of fixed_dim to compute from fixed_shape
    template <typename T, std::size_t N>
    struct fixed_dim<
        ::boost::array<T,N>
    >
    {
        static constexpr auto value = 1ul;
        using value_type = decltype(value);
    };

    template <typename T, std::size_t N, auto M>
    struct resize_size<
        ::boost::array<T,N>, M
    >
    {
        using type = ::boost::array<T,M>;
    }; // resize_size

    template <typename T, std::size_t N, typename NewShape>
    struct resize_shape<
        ::boost::array<T,N>, NewShape
    >
    {
        using array_type = ::boost::array<T,N>;

        static constexpr auto vtype = [](){
            constexpr auto new_shape = to_value_v<NewShape>;
            using new_shape_t = decltype(new_shape);
            using error_type [[maybe_unused]] = error::RESIZE_SHAPE_UNSUPPORTED<array_type,NewShape>;
            if constexpr (is_fail_v<new_shape_t>) {
                return as_value_v<error_type>;
            } else if constexpr (len_v<new_shape_t> > 1) {
                // not supported yet
                return as_value_v<error_type>;
            } else {
                constexpr auto M = new_shape[0];
                using type = ::boost::array<T,M>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resize_shape

    // TODO: consider to remove, make default impl smarter
    template <typename T, std::size_t N>
    struct fixed_index_array_size<
        ::boost::array<T,N>, enable_if_t<is_index_v<T>>
    >
    {
        static constexpr auto value = N;
    }; // fixed_index_array_size

    template <typename T, std::size_t N>
    struct len<::boost::array<T,N>>
    {
        static constexpr auto value = N;
    };

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t Capacity, typename Options>
    struct get_element_type<
        ::boost::container::static_vector<T,Capacity,Options>
    >
    {
        using type = T;
    }; // get_element_type
    #else
    template <typename T, std::size_t Capacity>
    struct get_element_type<
        ::boost::container::static_vector<T,Capacity>
    >
    {
        using type = T;
    }; // get_element_type
    #endif

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t Capacity, typename Options>
    struct fixed_dim<
        ::boost::container::static_vector<T,Capacity,Options>
    >
    {
        static constexpr auto value = 1ul;
        using value_type = decltype(value);
    };
    #else
    template <typename T, std::size_t Capacity>
    struct fixed_dim<
        ::boost::container::static_vector<T,Capacity>
    >
    {
        static constexpr auto value = 1ul;
        using value_type = decltype(value);
    };
    #endif

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t Capacity, typename Options>
    struct bounded_size<
        ::boost::container::static_vector<T,Capacity,Options>
    >
    {
        static constexpr auto value = Capacity;
        using value_type = decltype(value);
    };
    #else
    template <typename T, std::size_t Capacity>
    struct bounded_size<
        ::boost::container::static_vector<T,Capacity>
    >
    {
        static constexpr auto value = Capacity;
        using value_type = decltype(value);
    };
    #endif

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t Capacity, typename Options, auto NewSize>
    struct resize_bounded_size<
        ::boost::container::static_vector<T,Capacity,Options>, NewSize
    >
    {
        using type = ::boost::container::static_vector<T,NewSize,Options>;
    };
    #else
    template <typename T, std::size_t Capacity, auto NewSize>
    struct resize_bounded_size<
        ::boost::container::static_vector<T,Capacity>, NewSize
    >
    {
        using type = ::boost::container::static_vector<T,NewSize>;
    };
    #endif

    namespace error
    {
        // TODO: move to hybrid_index_array_max_size.hpp
        template <typename...>
        struct HYBRID_INDEX_ARRAY_BOUNDED_SIZE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    // TODO: remove
    template <typename T, std::size_t Capacity, typename Options>
    struct hybrid_index_array_max_size<
        ::boost::container::static_vector<T,Capacity,Options>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_index_v<T>) {
                return Capacity;
            } else {
                return error::HYBRID_INDEX_ARRAY_BOUNDED_SIZE_UNSUPPORTED<::boost::container::static_vector<T,Capacity,Options>>{};
            }
        }();
        using type = decltype(value);
    }; // hybrid_index_array_max_size
    #else
    // TODO: remove
    template <typename T, std::size_t Capacity>
    struct hybrid_index_array_max_size<
        ::boost::container::static_vector<T,Capacity>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_index_v<T>) {
                return Capacity;
            } else {
                return error::HYBRID_INDEX_ARRAY_BOUNDED_SIZE_UNSUPPORTED<::boost::container::static_vector<T,Capacity>>{};
            }
        }();
        using type = decltype(value);
    }; // hybrid_index_array_max_size
    #endif

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t N, typename Allocator, typename Options>
    struct get_element_type<
        ::boost::container::small_vector<T,N,Allocator,Options>
    >
    {
        using type = T;
    }; // get_element_type
    #else
    template <typename T, std::size_t N, typename Allocator>
    struct get_element_type<
        ::boost::container::small_vector<T,N,Allocator>
    >
    {
        using type = T;
    }; // get_element_type
    #endif

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, typename Allocator, typename Options>
    struct get_element_type<
        ::boost::container::vector<T,Allocator,Options>
    >
    {
        using type = T;
    };
    #else
    template <typename T, typename Allocator>
    struct get_element_type<
        ::boost::container::vector<T,Allocator>
    >
    {
        using type = T;
    };
    #endif

} // namespace nmtools::meta

#endif // NMTOOLS_META_BOOST_ARRAY_HPP