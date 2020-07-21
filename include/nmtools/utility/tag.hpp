#ifndef NMTOOLS_UTILITY_TAG_HPP
#define NMTOOLS_UTILITY_TAG_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include <type_traits>
#include <tuple>

namespace nmtools::tag
{

    using meta::type_in_tuple;

    using std::tuple;
    using std::is_base_of;
    using std::is_base_of_v;
    using std::is_same;
    using std::enable_if_t;

    /**
     * @brief tag for assertion
     * 
     */
    struct assert_t {};

    /**
     * @brief size assertion
     * 
     */
    struct size_assert_t : assert_t {};

    /**
     * @brief size assertion
     * 
     */
    struct no_assert_t : assert_t {};

    /**
     * @brief helper variable template to determine 
     * if T is valid elimination tag
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_assert_v = is_base_of_v<assert_t,T>;
    /**
     * @brief specialized version of is_elimination_v to handle tuple
     * 
     * @tparam Args 
     */
    template <typename ...Args>
    inline constexpr bool is_assert_v<tuple<Args...>> = type_in_tuple<is_base_of>(assert_t{},tuple<Args...>{});

    using traits::is_tuple_v;

    /**
     * @brief check if given tag is present in T
     * in which T could be single type or tuple
     * specialization on tuple checks if tag is
     * presents in any of the tuple's arguments
     * 
     * @tparam tag_t 
     * @tparam T 
     * @tparam void 
     */
    template <typename tag_t, typename T, typename = void>
    struct is_tag_enabled : is_same<tag_t,T> {};

    /**
     * @brief partial specialization when T is tuple
     * 
     * @tparam tag_t 
     * @tparam T 
     */
    template <typename tag_t, typename T>
    struct is_tag_enabled<tag_t,T,enable_if_t<is_tuple_v<T>> > 
    {
        static constexpr bool value = type_in_tuple(tag_t{},T{});
    };

    /**
     * @brief helper variable template to check if tag_t is enabled, 
     * given T, where T can be single tag or tuple of tag
     * 
     * @tparam tag_t tag to check
     * @tparam T tuple of tag or single tag
     */
    template <typename tag_t, typename T>
    inline constexpr bool is_tag_enabled_v = is_tag_enabled<tag_t,T>::value;

} // namespace nmtools::tag

#endif // NMTOOLS_UTILITY_TAG_HPP