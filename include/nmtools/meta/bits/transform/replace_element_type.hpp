#ifndef NMTOOLS_META_BITS_TRANSFORM_REPLACE_ELEMENT_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REPLACE_ELEMENT_TYPE_HPP

#include "nmtools/meta/common.hpp"

#include <tuple>
#include <array>
#include <utility>
#include <type_traits>

namespace nmtools::meta
{
    /**
     * @brief given T<Origin..>, transform to T<Substitution...>, if failed type is void
     * variadic template parameter Origin... & Substitution... should be type parameter. 
     * For non-type template parameter, only std::array is supported for now
     * 
     * @tparam T class which its template parameter to be replaced
     * @tparam  
     */
    template <typename T, typename...>
    struct replace_template_parameter 
    {
        // TODO: remove metafunctions
        using origin_tparams = void;
        /**
         * @brief define resulting type as void, so that
         * replace_template_parameter_t still well-formed
         * while error handling can be deferred to the caller
         * hence gives much more context
         */
        using type = void;
    };

    // TODO: remove metafunctions
    /**
     * @brief specialization for replace_template_parameter for success case
     * 
     * @tparam T 
     * @tparam Subs 
     * @tparam Origin 
     */
    template <template<typename...> typename T, typename ...Subs, typename ...Origin>
    struct replace_template_parameter<T<Origin...>,Subs...>
    {
        // use lighter type for type-list
        using origin_tparams = std::tuple<Origin...>;
        /**
         * @brief this assumes that the number of given substitute type, sizeof...(Subs),
         * is sufficient to instantiate T<Subs...>. Consider a case where this requirement
         * may not be met, we may need to substitute the missing template parameter from Subs
         * using appropriate type from Origin....
         */
        using type = T<Subs...>;
    };

    // TODO: remove metafunctions
    /**
     * @brief specialization for replace_template_parameter for std::array, 
     * since we can't mix non-type & type as variadic template parameter.
     * The new size of new array should be supplied via std::integral_constant,
     * since we expects type here.
     * 
     * @tparam value_t origin value_type
     * @tparam N origin size
     * @tparam subs_value_t value_type for substitution
     * @tparam subs_N substitution size
     */
    template <typename value_t, auto N, typename subs_value_t, auto subs_N, typename size_type>
    struct replace_template_parameter<std::array<value_t,N>,subs_value_t,std::integral_constant<size_type,subs_N>>
    {
        using origin_tparams = std::tuple<value_t>;
        using type = std::array<subs_value_t,subs_N>;
    };

    /**
     * @brief helper alias template to replace tparam
     * 
     * @tparam T original type
     * @tparam Args template parameter for substitution
     */
    template <typename T, typename...Args>
    using replace_template_parameter_t = typename replace_template_parameter<T,Args...>::type;

    /**
     * @brief similar to replace_template_parameter but assuming
     * new parameter are packed in typelist (tuple). default impl
     * has void as resulting type.
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct replace_template_parameter_from_typelist
    {
        /**
         * @brief define resulting type as void, so that
         * replace_template_parameter_t still well-formed
         * while error handling can be deferred to the caller
         * hence gives much more context
         */
        using type = void;
    };

    // TODO: remove metafunctions
    /**
     * @brief replace_template_parameter of class T with parameter(s) packed as tuple.
     *
     * @example 
     * @tparam T template template parameter, deduced automatically
     * @tparam Origin template parameter(s) of T, deduced automatically
     * @tparam Subs substitute for Origin, deduced automatically
     */
    template <template <typename...> typename T, typename...Origin, typename...Subs>
    struct replace_template_parameter_from_typelist<T<Origin...>,std::tuple<Subs...>>
    {
        /**
         * @brief call replace_template_parameter here so that any existing specialization
         * can be used, e.g. specialization of std::array which unpacks integral_constant<...>
         * to size_t as template parameter.
         * 
         */
        using type = replace_template_parameter_t<T<Origin...>,Subs...>;
    };

    /**
     * @brief helper alias template for replace_template_parameter_from_typelist.
     * 
     * @tparam T class which its template parameter(s) are to be replaced.
     * @tparam TypeList type list, e.g. std::tuple<...>, which holds types for substitution.
     */
    template <typename T, typename TypeList>
    using replace_template_parameter_from_typelist_t = typename replace_template_parameter_from_typelist<T,TypeList>::type;

    /**
     * @brief helper alias template to replace tparam
     * 
     * @tparam T original type
     * @tparam Args template parameter for substitution
     */
    /* TODO: remove */
    template <typename T, typename...Args>
    using replace_tparam_t = typename replace_template_parameter<T,Args...>::type;

    namespace detail
    {
        /**
         * @brief helper metafunction for replace_element_type
         *
         * return void type if no specialization exists
         * 
         * @tparam T type in which its element type to be replaced
         * @tparam U substitute to element type  of T
         * @tparam typename 
         */
        template <typename T, typename U, typename=void>
        struct replace_element_type_helper
        {
            using type = void;
        };

        // TODO: cleanup metafunctions
        // NOTE: make it easier to recurse
        template <typename T, typename U>
        struct replace_element_type_helper<T,U,std::enable_if_t<std::is_arithmetic_v<U>>>
        {
            static constexpr auto vtype = [](){
                if constexpr (has_value_type_v<T>) {
                    using value_type = typename T::value_type;
                    // TODO: wrap std::is_arithmetic using other metafunctions
                    if constexpr (std::is_arithmetic_v<value_type>)
                        return as_value_v<replace_template_parameter_t<T,U>>;
                    else {
                        using type = type_t<replace_element_type_helper<value_type,U>>;
                        return as_value_v<replace_template_parameter_t<T,type>>;
                    }
                }
                else return as_value_v<void>;
            }();
            using type = type_t<decltype(vtype)>;
        };
    } // namespace detail

    /**
     * @brief given type T, try to replace the element type of T with U.
     *
     * The default implementation if no specialization of type T exists is defined
     * by helper metafunction detail::relace_element_type_helper. This helper can handles
     * nested std::vector and std::array. By deferring implementation to helper class,
     * this metafunction doesn't need to provide specialization hence it will be easier
     * to specialize on custom types.
     * 
     * @tparam T type in which its element type to be replaced
     * @tparam U substitute to element type  of T
     * @tparam typename sfinae point
     * @see detail::replace_element_type_helper
     */
    template <typename T, typename U, typename=void>
    struct replace_element_type
    {
        using type = type_t<detail::replace_element_type_helper<T,U>>;
    }; // replace_element_type

    /**
     * @brief helper alias template for replace element type
     * 
     * @tparam T type in which its element type to be replaced
     * @tparam U substitute to element type  of T
     */
    template <typename T, typename U>
    using replace_element_type_t = typename replace_element_type<T,U>::type;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_REPLACE_ELEMENT_TYPE_HPP