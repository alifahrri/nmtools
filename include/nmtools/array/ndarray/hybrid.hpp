#ifndef NMTOOLS_ARRAY_NDARRAY_HYBRID_HPP
#define NMTOOLS_ARRAY_NDARRAY_HYBRID_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/mutable_flatten.hpp"
#include "nmtools/array/view/ref/initializer_list.hpp"
#include "nmtools/array/shape.hpp"

#include <cassert>
#include <vector>
#include <initializer_list>

namespace nmtools::array
{
    using std::initializer_list;

    namespace detail
    {
        /**
         * @brief alias tempate to check if all type Ts is integral constant
         * 
         * @tparam Ts 
         */
        template <typename...Ts>
        using all_integral = meta::apply_logical_and<std::is_integral,std::tuple<Ts...>>;

        template <typename...Ts>
        static inline constexpr auto all_integral_v = all_integral<Ts...>::value;

        /**
         * @brief alias tempate to check if all type Ts is integral constant
         * 
         * @tparam Ts 
         */
        template <typename...Ts>
        using all_integral_constant = meta::apply_logical_and<meta::is_integral_constant,std::tuple<Ts...>>;

        template <typename...Ts>
        static inline constexpr auto all_integral_constant_v = all_integral_constant<Ts...>::value;

        template <int max_elements, typename shape_t>
        constexpr auto init_shape()
        {
            // assume fixed size and same length for shape & stride
            auto shape_ = shape_t{};
            shape_[0] = max_elements;
            for (size_t i=1; i<shape_.size(); i++)
                shape_[i] = static_cast<size_t>(1);
            return shape_;
        } // init_shape

        template <int max_elements, typename shape_t, typename other_shape_t>
        constexpr auto init_shape(const other_shape_t& shape)
        {
            // assume fixed size and can hold shape
            auto shape_ = shape_t{};
            for (size_t i=0; i<len(shape); i++)
                at(shape_,i) = at(shape,i);
            return shape_;
        } // init_shape

        template <typename stride_t, typename shape_t>
        constexpr auto init_strides(const shape_t& shape)
        {
            // assume fixed size shape_t and the size matches to shape
            auto strides_ = stride_t{};
            for (size_t i=0; i<len(strides_); i++)
                at(strides_,i) = index::stride(shape,i);
            return strides_;
        } // init_strides

        template <typename data_t, typename array_t>
        constexpr auto init_data(array_t&& array)
        {
            data_t data{};
            auto array_ref   = view::ref(array);
            auto array_dim   = ::nmtools::dim(array);
            auto array_shape = ::nmtools::shape(array_ref);
            auto n = index::product(array_shape);
            // assert ( array_dim == dimension
            //     // , "unsupported init, mismatched dimension"
            // );
            // for (size_t i=0; i<array_dim; i++)
            //     shape_[i] = ::nmtools::at(array_shape,i);
            // strides_ = strides();
            auto array_view = view::flatten(array_ref);
            for (size_t i=0; i<n; i++)
                at(data,i) = at(array_view,i);
            return data;
        } // init_data

    } // namespace detail

    /**
     * @addtogroup hybrid hybrid ndarray
     * @ingroup array
     * @{
     */

    /**
     * @brief ndarray with fixed dimension and resizeable shape up to fixed number of elements
     * 
     * @tparam T element type
     * @tparam max_elements maximum number of elements
     * @tparam dimension fixed number of dimension
     */
    template <typename T, size_t max_elements, size_t dimension>
    struct hybrid_ndarray
    {
        static constexpr auto dim() noexcept
        {
            return dimension;
        }
        static inline constexpr auto dim_ = dimension;

        // use std array to make it easier to support constexpr
        using data_type     = std::array<T,max_elements>;
        using value_type    = T;
        using size_type     = size_t;
        using shape_type    = std::array<size_t,dim_>;
        using stride_type   = std::array<size_t,dim_>;
        using reference     = value_type&;
        using const_reference = const value_type&;

        data_type data;
        shape_type shape_;
        stride_type strides_;

        template <typename array_t>
        auto init(array_t&& array)
        {
            auto array_ref   = view::ref(array);
            auto array_dim   = ::nmtools::dim(array);
            auto array_shape = ::nmtools::shape(array_ref);
            auto n = index::product(array_shape);
            assert ( array_dim == dimension
                // , "unsupported init, mismatched dimension"
            );
            for (size_t i=0; i<array_dim; i++)
                shape_[i] = ::nmtools::at(array_shape,i);
            strides_ = strides();
            auto array_view = view::flatten(array_ref);
            for (size_t i=0; i<n; i++)
                nmtools::at(data,i) = nmtools::at(array_view,i);
        } // init

        constexpr hybrid_ndarray() : data{},
            shape_(detail::init_shape<max_elements,shape_type>()),
            strides_(detail::init_strides<stride_type>(shape_))
        {} // hybrid_array

        // explicit hybrid_ndarray(const shape_type& shape) { resize(shape); }

        // @note explicit required here, somehow related to operator=
        template <typename array_t, typename=std::enable_if_t<meta::is_ndarray_v<array_t>>>
        constexpr explicit hybrid_ndarray(array_t&& a) :
            shape_(detail::init_shape<max_elements,shape_type>(::nmtools::shape(a))),
            strides_(detail::init_strides<stride_type>(shape_)),
            data(detail::init_data<data_type>(a))
        {} // hybrid_ndarray
        
        template <size_t N>
        hybrid_ndarray(T (&&a)[N]) { init(a); }
        // @note 2D
        template <size_t Rows, size_t Cols>
        hybrid_ndarray(T (&&a)[Rows][Cols]) { init(a); }
        // @note 3D
        template <size_t Shape1, size_t Shape2, size_t Shape3>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3]) { init(a); }
        // @note 4D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4]) { init(a); }
        // @note 5D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5]) { init(a); }
        // @note 6D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6]) { init(a); }
        // @note 7D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7]) { init(a); }
        // @note 8D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8]) { init(a); }
        // @note 9D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9]) { init(a); }
        // @note 10D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10]) { init(a); }
        // @note 11D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10, size_t Shape11>
        hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10][Shape11]) { init(a); }

        constexpr auto shape() const noexcept
        {
            return shape_;
        } // shape

        // doesnt work, not ignored when dimension != 1
        // auto size() const -> std::enable_if_t<dimension==1,size_t>
        // {
        //     return shape_[0];
        // } // size

        constexpr auto strides() const
        {
            auto stride = index::compute_strides(shape_);
            return stride;
        } // strides

        template <typename...size_types>
        constexpr auto resize(size_types...shape)
            -> std::enable_if_t<detail::all_integral_v<size_types...>>
        {
            meta::template_for<sizeof...(shape)>([&](auto index){
                constexpr auto i = decltype(index)::value;
                shape_.at(i) = std::get<i>(std::tuple{shape...});
            });
            strides_ = strides();
            // numel_   = numel();
            // data.resize(numel_);
        } // resize

        constexpr auto resize(const shape_type& shape)
        {
            shape_   = shape;
            strides_ = strides();
            // numel_   = numel();
            // data.resize(numel_);
        } // resize

        template <typename ...size_types>
        constexpr auto operator()(size_types...ns)
            // noexcept(detail::all_integral_constant_v<size_types...>>)
            -> std::enable_if_t<
                sizeof...(ns)==dimension
                && detail::all_integral_v<size_types...>,
                reference
            >
        {
            using common_size_t = std::common_type_t<size_types...>;
            auto indices = std::array<common_size_t,sizeof...(ns)>{
                static_cast<common_size_t>(ns)...
            };
            static_assert ( dimension == sizeof...(ns)
                , "unsupporter element access, mismatched dimension"
            );
            auto offset = index::compute_offset(strides_, indices);
            return data[offset];
        } // operator()

        template <typename ...size_types>
        constexpr auto operator()(size_types...ns) const
            // noexcept(detail::all_integral_constant_v<size_types...>>)
            -> std::enable_if_t<
                sizeof...(ns)==dimension
                && detail::all_integral_v<size_types...>,
                const_reference
            >
        {
            using common_size_t = std::common_type_t<size_types...>;
            auto indices = std::array<common_size_t,sizeof...(ns)>{
                static_cast<common_size_t>(ns)...
            };
            static_assert ( dimension == sizeof...(ns)
                , "unsupporter element access, mismatched dimension"
            );
            auto offset = index::compute_offset(strides_, indices);
            return data[offset];
        } // operator()

        constexpr const_reference at(shape_type i) const
        {
            auto offset = index::compute_offset(strides_, i);
            return data[offset];
        } // at

        constexpr reference at(shape_type i)
        {
            auto offset = index::compute_offset(strides_, i);
            return data[offset];
        } // at

        template <typename ndarray_t, typename=std::enable_if_t<meta::is_ndarray_v<ndarray_t>>>
        auto operator=(const ndarray_t& rhs);

        #define NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(N) \
        decltype(auto) operator=(meta::make_nested_dynamic_array_t<std::initializer_list,value_type,N>&& rhs) \
        {   \
            auto rhs_view = view::ref(rhs); \
            using nested_t = decltype(rhs_view);  \
            return this->template operator=<nested_t>(rhs_view);         \
        } // operator=  \
        
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(1)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(2)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(3)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(4)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(5)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(6)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(7)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(8)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(9)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(10)
        NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT(11)

        #undef NMTOOLS_HYBRID_NDARRAY_ASSIGNMENT

    }; // struct hybrid_ndarray

    // provide user-defined ctad
    // @note 1D
    template <typename T, size_t N>
    hybrid_ndarray(T (&&a)[N]) -> hybrid_ndarray<T,N,1>;
    // @note 2D
    template <typename T, size_t Rows, size_t Cols>
    hybrid_ndarray(T (&&a)[Rows][Cols]) -> hybrid_ndarray<T,Rows*Cols,2>;
    // @note 3D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3,3>;
    // @note 4D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4,4>;
    // @note 5D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4*Shape5,5>;
    // @note 6D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4*Shape5*Shape6,6>;
    // @note 7D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4*Shape5*Shape6*Shape7,7>;
    // @note 8D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4*Shape5*Shape6*Shape7*Shape8,8>;
    // @note 9D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4*Shape5*Shape6*Shape7*Shape8*Shape9,9>;
    // @note 10D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4*Shape5*Shape6*Shape7*Shape8*Shape9*Shape10,10>;
    // @note 11D
    template <typename T, size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10, size_t Shape11>
    hybrid_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10][Shape11]) -> hybrid_ndarray<T,Shape1*Shape2*Shape3*Shape4*Shape5*Shape6*Shape7*Shape8*Shape9*Shape10*Shape11,11>;


    template <typename T>
    struct is_hybrid_ndarray : std::false_type {};

    template <typename T, size_t max_elements, size_t dimension>
    struct is_hybrid_ndarray<hybrid_ndarray<T,max_elements,dimension>> : std::true_type {};

    template <typename T>
    static inline constexpr auto is_hybrid_ndarray_v = is_hybrid_ndarray<T>::value;

    template <typename T, size_t max_elements>
    constexpr auto size(const array::hybrid_ndarray<T,max_elements,1>& a)
    {
        return a.shape_[0];
    } // size

    template <typename T, size_t max_elements>
    constexpr auto begin(const array::hybrid_ndarray<T,max_elements,1>& a)
    {
        return a.data.data();
    } // begin

    template <typename T, size_t max_elements>
    constexpr auto begin(array::hybrid_ndarray<T,max_elements,1>& a)
    {
        return a.data.data();
    } // begin

    template <typename T, size_t max_elements>
    constexpr auto end(const array::hybrid_ndarray<T,max_elements,1>& a)
    {
        return a.data.data() + a.shape_[0];
    } // end

    template <typename T, size_t max_elements>
    constexpr auto end(array::hybrid_ndarray<T,max_elements,1>& a)
    {
        return a.data.data() + a.shape_[0];
    } // end

    /** @} */ // end group dynamic
    
} // namespace nmtools::array

namespace nmtools
{
    /**
     * @brief return the shape of hybrid_ndarray
     * 
     * @tparam T element type of hybrid_ndarray, deduced via template argument deduction
     * @param a 
     * @return auto 
     */
    template <typename T, size_t max_elements, size_t dimension>
    auto shape(const array::hybrid_ndarray<T,max_elements,dimension>& a)
    {
        return a.shape();
    } // shape

    /**
     * @brief return the dimensionality of hybrid_ndarray
     * 
     * @tparam T element type of hybrid_ndarray, deduced via template argument deduction
     * @param a array in which its dim is to be read
     * @return auto 
     */
    template <typename T, size_t max_elements, size_t dimension>
    auto dim(const array::hybrid_ndarray<T,max_elements,dimension>& a)
    {
        return a.dim();
    } // dim

} // namespace nmtools

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * 
     */

    template <typename T, size_t max_elements, size_t dimension>
    struct is_index_array< array::hybrid_ndarray<T,max_elements,dimension>
        , std::enable_if_t<is_index_v<T> && (dimension==1)>
    > : std::true_type {};

    template <typename T, size_t max_elements>
    struct is_hybrid_index_array< array::hybrid_ndarray<T,max_elements,1>
        , std::enable_if_t<is_index_v<T>>
    > : std::true_type {};

    template <typename T, size_t max_elements>
    struct hybrid_index_array_max_size< array::hybrid_ndarray<T,max_elements,1>
        , std::enable_if_t<is_index_v<T>>
    >
    {
        static constexpr auto value = max_elements;
        using type = size_t;
    }; // hybrid_index_array_max_size

    template <typename T, size_t max_elements, size_t new_max_elements>
    struct resize_hybrid_index_array_max_size< array::hybrid_ndarray<T,max_elements,1>
        , new_max_elements, std::enable_if_t<is_index_v<T>>
    >
    {
        using type = array::hybrid_ndarray<T,new_max_elements,1>;
    }; // resize_hybrid_index_array_max_size

    /**
     * @brief specialization of is_ndarray trait for hybrid_ndarray
     * 
     * @tparam T element type of hybrid_ndarray
     */
    template <typename T, size_t max_elements, size_t dimension>
    struct is_ndarray<array::hybrid_ndarray<T,max_elements,dimension>> : true_type {};

    template <typename T, size_t max_elements, size_t dimension>
    struct is_hybrid_ndarray<array::hybrid_ndarray<T,max_elements,dimension>> : true_type {};

    template <typename T, size_t max_elements, size_t dimension>
    struct fixed_dim<array::hybrid_ndarray<T,max_elements,dimension>>
    {
        static constexpr auto value = dimension;
        using value_type = size_t;
    };

    template <typename T, size_t max_elements, size_t dimension>
    struct hybrid_ndarray_max_size<array::hybrid_ndarray<T,max_elements,dimension>>
    {
        static constexpr auto value = max_elements;
        using type = size_t;
    }; // hybrid_ndarray_max_size

    /**
     * @brief specialize metafunction resize_hybrid_ndarray_max_size for hybrid_ndarray
     * 
     * @tparam T 
     * @tparam max_elements 
     * @tparam N new maximum size
     */
    template <typename T, size_t max_elements, auto N, size_t dimension>
    struct resize_hybrid_ndarray_max_size<array::hybrid_ndarray<T,max_elements,dimension>,N>
    {
        using type = array::hybrid_ndarray<T,N,dimension>;
    }; // resize_hybrid_ndarray_max_size

    /**
     * @brief Construct new hybrid_ndarray which its dimension are replaced with new dimension.
     * 
     * @tparam T            element type
     * @tparam max_elements 
     * @tparam dimension    existing dimension
     * @tparam DIM          desired new dimension
     */
    template <typename T, size_t max_elements, size_t dimension, auto DIM>
    struct resize_hybrid_ndarray_dim<
        array::hybrid_ndarray<T,max_elements,dimension>, DIM
    >
    {
        using type = array::hybrid_ndarray<T,max_elements,DIM>;
    }; // resize_hybrid_ndarray_dim

    /**
     * @brief specialize replace_element_type for array::hybrid_ndarray
     * 
     * @tparam T 
     * @tparam U 
     * @tparam storage_type 
     * @tparam shape_storage_type 
     */
    template <typename T, typename U, size_t max_elements, size_t dimension>
    struct replace_element_type<array::hybrid_ndarray<T,max_elements,dimension>,U,std::enable_if_t<std::is_arithmetic_v<U>>>
    {
        using type = array::hybrid_ndarray<U,max_elements,dimension>;
    }; // replace_element_type

    /**
     * @brief return the element type of hybrid_ndarray
     * 
     * @tparam T element type
     * @tparam max_elements 
     * @tparam dimension 
     */
    template <typename T, size_t max_elements, size_t dimension>
    struct get_element_type<array::hybrid_ndarray<T,max_elements,dimension>>
    {
        using type = T;
    }; // get_element_type

    /**
     * @brief Default impl for make_hybrid_ndarray
     * 
     * @tparam element_t 
     * @tparam max_elements 
     * @tparam dim 
     * @todo make this bypass-able via macro
     */
    template <typename element_t, auto max_elements, auto dim>
    struct make_hybrid_ndarray
    {
        using type = array::hybrid_ndarray<element_t,max_elements,dim>;
    }; // make_hybrid_ndarray

    template <typename element_t, auto max_elements, auto dim>
    using make_hybrid_ndarray_t = type_t<make_hybrid_ndarray<element_t,max_elements,dim>>;

    /** @} */ // end group traits
    
} // namespace nmtools::meta

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * 
     */

    /**
     * @brief specialization of metafunction get_ndarray_value_type,
     * which tells the value/element type of hybrid_ndarray
     * 
     * @tparam T element type of dynamic_ndarrray, deduced automatically
     */
    template <typename T, size_t max_elements, size_t dimension>
    struct get_ndarray_value_type<array::hybrid_ndarray<T,max_elements,dimension>>
    {
        using type = T;
    };
    /** @} */ // end group meta
} // namespace nmtools::meta

#include "nmtools/array/shape.hpp"
#include "nmtools/utils/isequal.hpp"

namespace nmtools::array
{
    
    /**
     * @brief assignment operator for hybrid_ndarray from generic matrix type
     * 
     * @tparam T element type of hybrid_ndarray
     * @tparam ndarray_t type of matrix to be cloned
     * @param rhs matrix to be cloned
     * @return constexpr auto 
     */
    template <typename T, size_t max_elements, size_t dimension>
    template <typename ndarray_t, typename>
    auto hybrid_ndarray<T,max_elements,dimension>::operator=(const ndarray_t& rhs)
    {
        using nmtools::dim;
        using nmtools::shape;
        using nmtools::utils::isequal;

        assert (dim(rhs)==dim(*this)
            // , mismatched dimension for hybrid_ndarray assignment
        );
        assert (isequal(shape(rhs),shape(*this))
            // , mismatched shape for hybrid_ndarray assignment
        );
        auto n = index::product(shape(rhs));

        auto flat_rhs = view::flatten(rhs);
        for (size_t i=0; i<n; i++)
            nmtools::at(this->data,i) = nmtools::at(flat_rhs,i);

        return *this;
    } // operator=

} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_NDARRAY_HYBRID_HPP