#ifndef NMTOOLS_META_DETAIL_HPP
#define NMTOOLS_META_DETAIL_HPP

namespace nmtools::meta
{
    namespace detail {

        /**
         * @brief helper tag to indicate checking fail at compile-time
         * 
         */
        struct fail_t {};
        
        /**
         * @brief helper metafunction to transform fail_t to void
         *
         * This transform may be used to metafunction that returning a type 
         * from type deduction that may fail by returning fail_t instead of returning void.
         * 
         * @tparam T type to transform
         */
        template <typename T>
        struct fail_to_void
        {
            using type = T;
        }; // fail_to_void

        /**
         * @brief actual case for fail_to_void when T is fail_T
         * 
         * @tparam  
         */
        template <>
        struct fail_to_void<fail_t>
        {
            using type = void;
        }; // fail_to_void
        
        /**
         * @brief helper alias template to fail_to_void
         * 
         * @tparam T type to transform
         */
        template <typename T>
        using fail_to_void_t = typename fail_to_void<T>::type;

        /**
         * @brief maps void type to fail_t type.
         *
         * This may be helpful if one want to returning value in which it type is
         * deduced from another metafunction that may fail (member type is void),
         * since we can returning void, transform to fail_t instead.
         * 
         * @tparam T type to transform
         */
        template <typename T>
        struct void_to_fail
        {
            using type = T;
        }; // void_to_fail

        /**
         * @brief actual case for void_to_fail when T is void
         * 
         * @tparam 
         */
        template <>
        struct void_to_fail<void>
        {
            using type = fail_t;
        };

        /**
         * @brief helper alias template for void_to_fail.
         * 
         * @tparam T type to transform
         */
        template <typename T>
        using void_to_fail_t = typename void_to_fail<T>::type;
    } // namespace detail
} // namespace nmtools::meta

#endif // NMTOOLS_META_DETAIL_HPP