#ifndef NMTOOLS_META_BITS_TRANSFORM_REPLACE_ELEMENT_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REPLACE_ELEMENT_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"

namespace nmtools::meta
{
    /**
     * @brief given T<Origin..>, transform to T<Substitution...>, if failed type is void
     * variadic template parameter Origin... & Substitution... should be type parameter. 
     * For non-type template parameter, only std array is supported for now
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
        /**
         * @brief this assumes that the number of given substitute type, sizeof...(Subs),
         * is sufficient to instantiate T<Subs...>. Consider a case where this requirement
         * may not be met, we may need to substitute the missing template parameter from Subs
         * using appropriate type from Origin....
         */
        using type = T<Subs...>;
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

    /**
     * @brief helper alias template for replace_template_parameter_from_typelist.
     * 
     * @tparam T class which its template parameter(s) are to be replaced.
     * @tparam TypeList type list, e.g. std tuple<...>, which holds types for substitution.
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
        struct replace_element_type_helper<T,U,enable_if_t<is_num_v<U>>>
        {
            static constexpr auto vtype = [](){
                if constexpr (has_value_type_v<T>) {
                    using value_type = typename T::value_type;
                    if constexpr (is_num_v<value_type>)
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
     * nested std vector and std array. By deferring implementation to helper class,
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