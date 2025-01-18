#ifndef NMTOOLS_ARRAY_VIEW_REF_INITIALIZER_LIST_HPP
#define NMTOOLS_ARRAY_VIEW_REF_INITIALIZER_LIST_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/utility/shape.hpp"
#include <cassert>
#include <initializer_list>

namespace nmtools
{
    /**
     * @brief specialize ref_t for initializer_list
     *
     * override the element-access op for 1D array.
     * 
     * @tparam T 
     */
    template <typename T>
    struct view::ref_t<std::initializer_list<T>>
    {
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<std::initializer_list<T>>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const std::initializer_list<T>&;
        // number of dimension
        static inline constexpr auto dim_ = meta::nested_array_dim_v<std::initializer_list<T>>;

        // const reference to actual array type
        array_type array;

        /**
         * @brief construct ref view
         * 
         */
        constexpr ref_t(array_type array) : array(array) {}

        /**
         * @brief helper struct to randomly access initializer_list element
         * 
         */
        struct f
        {
            template <typename array_t, typename size_type>
            constexpr decltype(auto) operator()(array_t& array, size_type i)
            {
                // note that return type from initializer_list::begin is const T*
                return *(array.begin()+i);
            } // operator()
        }; // f

        /**
         * @brief helper struct to randomly access nested initializer_list element
         * 
         */
        struct g
        {
            template <typename array_t, typename size_type, typename...size_types>
            constexpr decltype(auto) operator()(array_t& array, size_type i, size_types...is)
            {
                // @note cast to bool for clang
                if constexpr (static_cast<bool>(sizeof...(is)))
                    return g{}(f{}(array,i),is...);
                else return f{}(array,i);
            } // operator()

            template <template<auto...>typename index_sequence, typename array_t, typename indices_t, size_t ...Is>
            constexpr decltype(auto) operator()(array_t& array, indices_t is, index_sequence<Is...>)
            {
                return g{}(array, nmtools::get<Is>(is)...);
            } // operator()

            template <typename array_t, template<typename...>typename type_list, typename...size_types>
            constexpr decltype(auto) operator()(array_t& array, type_list<size_types...> is)
            {
                using sequence_t = meta::make_index_sequence<sizeof...(size_types)>;
                return g{}(array, is, sequence_t{});
            } // operator()

            template <typename array_t, template<typename,size_t>typename type_list, typename size_type, size_t N>
            constexpr decltype(auto) operator()(array_t& array, type_list<size_type,N> is)
            {
                using sequence_t = meta::make_index_sequence<N>;
                return g{}(array, is, sequence_t{});
            } // operator()
        }; // g

        /**
         * @brief return the number of dimension
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const
        {
            return dim_;
        } // dim()

        /**
         * @brief return the shape of referenced nested initializer_list
         * 
         * @return constexpr auto 
         */
        constexpr auto shape() const
        {
            auto shape_ = nmtools_array<size_t,dim_>{};
            // get the size for each 'nested' list, dimension known at compile time
            // assuming each element on each 'axis' has the same size
            // this techniques is similar with nmtools::shape, but since
            // initializer list doesnt support nmtools::apply_at, we custumize here
            meta::template_for<dim_>([&](auto index){
                constexpr auto i = decltype(index)::value;
                // first axis, simply take the size of referenced array
                if constexpr (i==0) {
                    auto s = array.size();
                    nmtools::get<i>(shape_) = s;
                }
                // for the rest of axes, construct nested indices up to i times
                // then apply at to get the element at i-th axis and get the size
                else {
                    auto indices = ::nmtools::impl::detail::repeat<i>(0ul);
                    auto a = g{}(array, indices);
                    nmtools::get<i>(shape_) = a.size();
                }
            });
            return shape_;
        } // shape()

        /**
         * @brief randomly access elemenst of possibly nested initializer_list
         * 
         * @tparam size_types 
         * @param Is 
         * @return 
         */
        template <typename...size_types>
        constexpr auto operator()(size_types...Is) const
            -> meta::enable_if_t<sizeof...(size_types)==dim_,value_type>
        {
            // @note that this recursive lambda is not allowed
            // gcc internal compiler error: trying to capture ‘g’ in instantiation of generic lambda
            // clang error: variable 'g' declared with deduced type 'auto' cannot appear in its own initializer
            // auto f = [](auto array, auto i){
            //     return *(array.begin()+i);
            // };
            // auto g = [&](auto array, auto i, auto...is){
            //     if constexpr (sizeof...(is))
            //         return g(f(array,i),is...);
            //     else return f(array,i);
            // };
            // use helper struct instead
            return g{}(array, Is...);
        } // operator()
    }; // ref_t

    /**
     * @brief specializer is_array2d trait for ref view on nd initializer_list
     * 
     * @tparam T element type of initializer list, another initializer list in this case
     */
    template <typename T>
    struct meta::is_ndarray< view::decorator_t<view::ref_t,std::initializer_list<T>>> : meta::true_type {};

    /**
     * @brief specialize metafunction meta::remove_nested_array_dim for initializer_list
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct meta::remove_nested_array_dim<T,N,meta::enable_if_t< (N > 0) && meta::is_specialization_v<T,std::initializer_list>>>
    {
        using type = typename remove_nested_array_dim<typename T::value_type,N-1>::type;
    }; // remove_nested_array_dim

    /**
     * @brief specialize metafunction meta::remove_nested_array_dim for initializer_list
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct meta::remove_nested_array_dim<T,N,meta::enable_if_t<N == 0 && meta::is_specialization_v<T,std::initializer_list>>>
    {
        using type = T;
    }; // remove_nested_array_dim

    /**
     * @brief specialize metafunction meta::nested_array_dim for initializer_list
     * 
     * @tparam T 
     */
    template <typename T>
    struct meta::nested_array_dim<T,meta::enable_if_t<meta::is_specialization_v<T,std::initializer_list>>>
    {
        using value_type = remove_cvref_t<typename T::value_type>;
        static constexpr auto value = 1 + nested_array_dim<value_type>::value;
    }; // nested_array_dim

    /**
     * @brief specialze metafunction meta::get_element_type for initializer_list
     * 
     * @tparam T 
     */
    template <typename T>
    struct meta::get_element_type<std::initializer_list<T>>
    {
        using type = typename get_element_type<T>::type;
    }; // meta::get_element_type

    // disable various array traits for plain initializer list, must be via view::ref

    template <typename T>
    struct meta::is_array1d<std::initializer_list<T>> : meta::false_type {};

    template <typename T>
    struct meta::is_ndarray<std::initializer_list<T>> : meta::false_type {};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_REF_INITIALIZER_LIST_HPP