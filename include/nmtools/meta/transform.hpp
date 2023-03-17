#ifndef NMTOOLS_META_TRANSFORM_HPP
#define NMTOOLS_META_TRANSFORM_HPP

#include "nmtools/meta/bits/transform/add_reference.hpp"
#include "nmtools/meta/bits/transform/append_type.hpp"
#include "nmtools/meta/bits/transform/append_value.hpp"
#include "nmtools/meta/bits/transform/at.hpp"
#include "nmtools/meta/bits/transform/bit_reference_to_bool.hpp"
#include "nmtools/meta/bits/transform/clipped_min.hpp"
#include "nmtools/meta/bits/transform/clipped_max.hpp"
#include "nmtools/meta/bits/transform/common_type.hpp"
#include "nmtools/meta/bits/transform/concat_type.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"
#include "nmtools/meta/bits/transform/get_either.hpp"
#include "nmtools/meta/bits/transform/get_element_type.hpp"
#include "nmtools/meta/bits/transform/get_common_type.hpp"
#include "nmtools/meta/bits/transform/get_element_or_common_type.hpp"
#include "nmtools/meta/bits/transform/get_index_element_type.hpp"
#include "nmtools/meta/bits/transform/get_index_type.hpp"
#include "nmtools/meta/bits/transform/get_maybe_type.hpp"
#include "nmtools/meta/bits/transform/get_value_type.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/transform/make_signed.hpp"
#include "nmtools/meta/bits/transform/make_unsigned.hpp"
#include "nmtools/meta/bits/transform/promote_index.hpp"
#include "nmtools/meta/bits/transform/promote_types.hpp"
#include "nmtools/meta/bits/transform/remove_const.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/meta/bits/transform/remove_pointer.hpp"
#include "nmtools/meta/bits/transform/replace_either.hpp"
#include "nmtools/meta/bits/transform/replace_element_type.hpp"
#include "nmtools/meta/bits/transform/replace_value_type.hpp"
#include "nmtools/meta/bits/transform/resize_fixed_ndarray.hpp"
#include "nmtools/meta/bits/transform/to_value.hpp"
#include "nmtools/meta/bits/transform/transform_bounded_array.hpp"
#include "nmtools/meta/bits/transform/tuple_to_array.hpp"
#include "nmtools/meta/bits/transform/type_list_at.hpp"

#include "nmtools/meta/bits/traits/has_type.hpp"

namespace nmtools::meta
{
    /**
     * @brief metafunction to resolve specific op return type.
     *
     * Default implementation has `type` member type aliasing `void`,
     * may be used at caller site to check and provide context.
     * 
     * @tparam always_void 
     * @tparam op_t operator tag
     * @tparam tparams 
     */
    template <typename always_void, typename op_t, typename...tparams>
    struct resolve_optype
    {
        using type = void;
    }; // resolve_optype

    /**
     * @brief helper alias template to get the resulting type of metafunction
     * resolve_optype.
     * 
     * @tparam op_t operator tag
     * @tparam tparams 
     */
    template <typename op_t, typename...tparams>
    using resolve_optype_t = typename resolve_optype<void,op_t,tparams...>::type;


    // TODO: cleanup metafunctions
    /**
     * @brief make nested raw array from element type T, first axis size N, and the rest of axis size Ns...
     *
     * For example make_nested_raw_array<double,3,4,5> is creating double[3][4][5].
     * 
     * @tparam T desired element type
     * @tparam N size of the first axis
     * @tparam Ns size(s) of the rest axes
     */
    template <typename T, size_t N, size_t...Ns>
    struct make_nested_raw_array
    {
        template <typename T_, size_t N_, size_t...Ns_>
        struct _make_type
        {
            using nested_type = typename _make_type<T_,Ns_...>::type;
            using type = nested_type[N_];
        }; // _make_type
        template <typename T_, size_t N_>
        struct _make_type<T_,N_>
        {
            using type = T_[N_];
        }; // _make_type

        using type = typename _make_type<T,N,Ns...>::type;
    }; // make_nested_raw_array

    // TODO: remove support for nested dynamic array
    /**
     * @brief metafunction to make nested dynamic array.
     * 
     * Create nested array type to N number of depth.
     * 
     * @tparam array_t template-template parameters that takes types. (e.g. array_t<typename...>)
     * @tparam T element type of desired nested dynamic array
     * @tparam N desired number of depth
     * @tparam Args additional template parameter to each array_t instantiation. e.g. array_t<T,Args...>
     */
    template <template<typename...> typename array_t, typename T, size_t N>
    struct make_nested_dynamic_array
    {
        // @note apparently it is required to make array_t to takes arbitrary nr of params
        static constexpr auto _make_nested_type()
        {
            if constexpr (N==1)
                return array_t<T>{};
            else {
                using type = typename make_nested_dynamic_array<array_t,T,N-1>::type;
                return array_t<type>{};
            }
        } // _make_nested_type()

        using type = decltype(_make_nested_type());
    };

    // TODO: remove metafunctions
    /**
     * @brief helper alias template to get the type of nested raw array.
     * 
     * @tparam T desired element type
     * @tparam N size of the first axis
     * @tparam Ns size(s) of the rest axes
     */
    template <typename T, size_t N, size_t...Ns>
    using make_nested_raw_array_t = typename make_nested_raw_array<T,N,Ns...>::type;

    // TODO: remove metafunctions
    /**
     * @brief helper alias template to make nested dynamic array.
     * 
     * Create nested array type to N number of depth.
     * 
     * @tparam array_t template-template parameters that takes types. (e.g. array_t<typename...>)
     * @tparam T element type of desired nested dynamic array
     * @tparam N desired number of depth
     */
    template <template<typename...> typename array_t, typename T, size_t N>
    using make_nested_dynamic_array_t = typename make_nested_dynamic_array<array_t,T,N>::type;

    namespace detail
    {
        // TODO: remove metafunctions
        /**
         * @brief helper metafunction for meta::apply
         * 
         * @tparam TT template template parameter
         * @tparam T type list
         */
        template <template<typename...>typename TT, typename T>
        struct apply_helper
        {
            using type = void;
        }; // apply_helper

        // TODO: remove metafunctions
        template <template<typename...>typename TT, template<typename...>typename type_list, typename...Ts>
        struct apply_helper<TT,type_list<Ts...>>
        {
            static constexpr auto vtype = []()
            {
                using meta_fn_type = TT<Ts...>;
                if constexpr (meta::has_type_v<meta_fn_type>)
                    // assuming type from meta_fn_type is default constructible
                    return typename meta_fn_type::type{};
                else return detail::fail_t{};
            }();
            using type = meta::remove_cvref_t<detail::fail_to_void_t<decltype(vtype)>>;
        }; // apply_helper
    } // namespace detail

    // TODO: remove metafunctions
    /**
     * @brief apply template template parameter T on type list T
     * 
     * @tparam TT template template parameter
     * @tparam T type list
     */
    template <template<typename...>typename TT, typename T>
    struct apply
    {
        // @note use helper metafunction so specialization is not necessary
        using type = typename detail::apply_helper<TT,T>::type;
    }; // apply_traits_helper

    /**
     * @brief helper alias template for apply
     * 
     * @tparam TT template template parameter
     * @tparam T type list
     */
    template <template<typename...>typename TT, typename T>
    using apply_t = typename apply<TT,T>::type;

    namespace error
    {
        template<typename...>
        struct RESIZE_FIXED_VECTOR_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief metafunction to resize fixed vector.
     * 
     * @tparam T fixed vector type to be resized.
     * @tparam N new size.
     */
    template <typename T, auto N, typename=void>
    struct resize_fixed_vector
    {
        // TODO: use error type
        /* pack new size as type instead of non-type template param */
        using new_size = integral_constant<size_t,N>;
        static constexpr auto vtype = [](){
            using type = replace_template_parameter_t<T,new_size>;
            if constexpr (is_void_v<type>) {
                return as_value_v<error::RESIZE_FIXED_VECTOR_UNSUPPORTED<T,as_type<N>>>;
            } else {
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    /**
     * @brief helper alias template to resize metafunction to resize fixed vector.
     * 
     * @tparam T fixed vector type to be resized.
     * @tparam N new size.
     */
    template <typename T, auto N>
    using resize_fixed_vector_t = typename resize_fixed_vector<T,N>::type;

    template <typename T, size_t N>
    struct resize_fixed_index_array : resize_fixed_vector<T,N> {};

    template <typename T, size_t N>
    using resize_fixed_index_array_t = type_t<resize_fixed_index_array<T,N>>;


    /**
     * @brief Remove const-ness, reference, and pointer from a type.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    using remove_cvref_pointer_t = remove_cvref_t<remove_pointer_t<array_t>>;

    /** @} */ // end group meta
} // namespace nmtools::meta

#endif // NMTOOLS_META_TRANSFORM_HPP