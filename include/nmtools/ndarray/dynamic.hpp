#ifndef NMTOOLS_ARRAY_NDARRAY_DYNAMIC_HPP
#define NMTOOLS_ARRAY_NDARRAY_DYNAMIC_HPP

#ifndef NMTOOLS_DISABLE_DYNAMIC_ARRAY

#include "nmtools/meta.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/core/flatten.hpp"
#include "nmtools/core/mutable_flatten.hpp"
#include "nmtools/core/ref/initializer_list.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/assert.hpp"

#include <cassert>
#include <vector>
#include <initializer_list>

namespace nmtools
{
    using std::initializer_list;

    /**
     * @addtogroup Dynamic Dynamic Array
     * @ingroup array
     * @{
     */

    /**
     * @brief sample implementation of dynamic n-dimensional array,
     * trying to mimic numpy ndarray layout @cite NumPy_ndarray_layout
     * 
     * @tparam T element type of nd-array
     * @tparam storage_type template template parameter to store data
     */
    template <typename T, template <typename...> typename storage_type=nmtools_list, template<typename...> typename shape_storage_type=nmtools_list>
    struct dynamic_ndarray
    {
        using data_type = storage_type<T>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using shape_type = shape_storage_type<size_t>;
        using stride_type = shape_storage_type<size_t>;

        template <typename array_t>
        auto init(array_t&& array)
        {
            auto array_ref = view::ref(array);
            auto array_shape = ::nmtools::shape(array_ref);
            for (const auto& s : array_shape)
                shape_.push_back(s);
            strides_ = strides();
            numel_   = numel();
            data_.resize(numel_);
            auto array_view = unwrap(view::flatten(array_ref));
            for (size_t i=0; i<numel_; i++)
                nmtools::at(data_,i) = nmtools::at(array_view,i);
        }

        dynamic_ndarray() {}

        // explicit dynamic_ndarray(const shape_type& shape) { resize(shape); }

        // @note explicit required here, somehow related to operator=
        template <typename array_t, typename=meta::enable_if_t<meta::is_ndarray_v<array_t>>>
        explicit dynamic_ndarray(array_t&& a) { init(a); }

        #define NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(N) \
        explicit dynamic_ndarray(meta::make_nested_dynamic_array_t<std::initializer_list,T,N>&& a) { init(a); }

        // doesn work
        #if 0
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(1)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(2)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(3)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(4)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(5)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(6)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(7)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(8)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(9)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(10)
        NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR(11)
        #endif

        #undef NMTOOLS_DYNAMIC_NDARRAY_CONSTRUCTOR

        #if 1
        // note that the following is taking rvalue
        template <size_t N>
        explicit dynamic_ndarray(T (&&a)[N]) { init(a); }
        // @note 2D
        template <size_t Rows, size_t Cols>
        explicit dynamic_ndarray(T (&&a)[Rows][Cols]) { init(a); }
        // @note 3D
        template <size_t Shape1, size_t Shape2, size_t Shape3>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3]) { init(a); }
        // @note 4D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4]) { init(a); }
        // @note 5D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5]) { init(a); }
        // @note 6D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6]) { init(a); }
        // @note 7D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7]) { init(a); }
        // @note 8D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8]) { init(a); }
        // @note 9D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9]) { init(a); }
        // @note 10D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10]) { init(a); }
        // @note 11D
        template <size_t Shape1, size_t Shape2, size_t Shape3, size_t Shape4, size_t Shape5, size_t Shape6, size_t Shape7, size_t Shape8, size_t Shape9, size_t Shape10, size_t Shape11>
        explicit dynamic_ndarray(T (&&a)[Shape1][Shape2][Shape3][Shape4][Shape5][Shape6][Shape7][Shape8][Shape9][Shape10][Shape11]) { init(a); }
        #endif

        data_type data_;
        shape_type shape_;
        stride_type strides_;
        size_type numel_;

        /**
         * @brief return the number of dimension
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const
        {
            return shape_.size();
        } // dim

        /**
         * @brief return the shape information
         * 
         * @return constexpr auto 
         */
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        /**
         * @brief return the number of elements
         * 
         * @return constexpr auto 
         */
        constexpr auto numel() const
        {
            size_t numel_ = 1;
            for (auto s : shape_)
                numel_ *= s;
            return numel_;
        } // numel

        /**
         * @brief return the strides information
         * 
         * @return constexpr auto 
         */
        constexpr auto strides() const
        {
            auto stride = stride_type{};
            stride.resize(dim());
            for (size_t i=0; i<dim(); i++)
                stride[i] = ::nmtools::index::stride(shape_,i);
            return stride;
        } // strides

        template <typename...size_types>
        auto resize(size_types...shape) -> meta::enable_if_t<(meta::is_index_v<size_types> &&...)>
        {
            // NOTE: use meta::is_index_v to allow constant index
            shape_.resize(sizeof...(shape));
            meta::template_for<sizeof...(shape)>([&](auto index){
                constexpr auto i = decltype(index)::value;
                using tuple_t = nmtools_tuple<decltype(shape)...>;
                shape_.at(i) = nmtools::get<i>(tuple_t{shape...});
            });
            strides_ = strides();
            numel_   = numel();
            data_.resize(numel_);
        }

        auto resize(const shape_type& shape)
        {
            shape_ = shape;
            strides_ = strides();
            numel_   = numel();
            data_.resize(numel_);
        }

        template <typename shape_t>
        auto resize(const shape_t& shape)
            -> meta::enable_if_t<meta::is_index_array_v<shape_t>>
        {
            auto n = len(shape);
            shape_.resize(n);
            for (size_t i=0; i<n; i++)
                shape_.at(i) = ::nmtools::at(shape,i);
            strides_ = strides();
            numel_   = numel();
            data_.resize(numel_);
        } // resize

        auto data() const
        {
            return data_.data();
        }

        /**
         * @brief mutable access to element
         * 
         * @tparam size 
         * @param n 1st index of element to be accessed
         * @param ns the rest of indices of element to be accessed
         * @return constexpr reference 
         * @todo explore more on error handling to make assertion more customizable
         */
        template <typename ...size_types>
        constexpr decltype(auto) operator()(size_type n, size_types...ns)
        {
            using common_size_t = meta::promote_index_t<size_type,size_types...>;
            auto indices = nmtools_array<common_size_t,sizeof...(ns)+1>{
                static_cast<common_size_t>(n), static_cast<common_size_t>(ns)...
            };
            assert (dim()==indices.size());
            auto offset = ::nmtools::index::compute_offset(strides_, indices);
            return data_[offset];
        } // operator()

        /**
         * @brief immutable access to element
         * 
         * @tparam size 
         * @param n 1st index of element to be accessed
         * @param ns the rest of indices of element to be accessed
         * @return constexpr const_reference 
         * @todo explore more on error handling to make assertion more customizable
         */
        template <typename ...size_types>
        constexpr decltype(auto) operator()(size_type n, size_types...ns) const
        {
            using common_size_t = meta::promote_index_t<size_type,size_types...>;
            auto indices = nmtools_array<common_size_t,sizeof...(ns)+1>{
                static_cast<common_size_t>(n), static_cast<common_size_t>(ns)...
            };
            assert (dim()==indices.size());
            auto offset = ::nmtools::index::compute_offset(strides_, indices);
            return data_[offset];
        } // operator()

        /**
         * @brief element access to support packed indices
         * 
         * @param i packed indices with same type as shape_type
         * @return const_reference 
         */
        decltype(auto) at(shape_type i) const
        {
            auto offset = ::nmtools::index::compute_offset(strides_, i);
            return data_[offset];
        } // at

        decltype(auto) at(shape_type i)
        {
            auto offset = ::nmtools::index::compute_offset(strides_, i);
            return data_[offset];
        } // at

        template <typename shape_t>
        auto at(const shape_t& i) const
            -> meta::enable_if_t<meta::is_index_array_v<shape_t>, const value_type&>
        {
            // this function is provided to support cross-compile for android
            // somehow storage_type is deduced as std::vector while
            // provided index array (std::vector defined outside) deduced
            // as std::__ndk1::vector
            auto offset = ::nmtools::index::compute_offset(strides_, i);
            return data_[offset];
        } // at

        template <typename shape_t>
        auto at(const shape_t& i)
            -> meta::enable_if_t<meta::is_index_array_v<shape_t>, value_type&>
        {
            // this function is provided to support cross-compile for android
            // somehow storage_type is deduced std::vector while
            // provided index array (std::vector defined outside) deduced
            // as std::__ndk1::vector
            auto offset = ::nmtools::index::compute_offset(strides_, i);
            return data_[offset];
        } // at

        template <typename ndarray_t, typename=meta::enable_if_t<meta::is_ndarray_v<ndarray_t>>>
        constexpr auto operator=(const ndarray_t& rhs);

        #define NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(N) \
        constexpr decltype(auto) operator=(meta::make_nested_dynamic_array_t<std::initializer_list,value_type,N>&& rhs) \
        {   \
            auto rhs_view = view::ref(rhs); \
            using nested_t = decltype(rhs_view);  \
            return this->template operator=<nested_t>(rhs_view);         \
        } // operator=
        
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(1)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(2)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(3)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(4)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(5)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(6)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(7)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(8)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(9)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(10)
        NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT(11)

        #undef NMTOOLS_DYNAMIC_NDARRAY_ASSIGNMENT

    }; // struct dynamic_ndarray

    /** @} */ // end group dynamic
    
} // namespace nmtools

namespace nmtools::impl
{
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    struct len_t<dynamic_ndarray<T,storage_type,shape_storage_type>>
    {
        using array = const dynamic_ndarray<T,storage_type,shape_storage_type>&;
        using type = size_t;

        auto operator()(array a) const
        {
            return at(a.shape(),0);
        }
    };
} // namespace nmtools::impl


namespace nmtools
{
    // TODO: remove, specialize shape_t instead
    /**
     * @brief return the shape of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray, deduced via template argument deduction
     * @param a 
     * @return auto 
     */
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    auto shape(const dynamic_ndarray<T,storage_type,shape_storage_type>& a)
    {
        return a.shape();
    } // shape

    // TODO: remove, specialize dim_t
    /**
     * @brief return the dimensionality of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray, deduced via template argument deduction
     * @param a array in which its dim is to be read
     * @return auto 
     */
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    auto dim(const dynamic_ndarray<T,storage_type,shape_storage_type>& a)
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

    /**
     * @brief specialization of is_ndarray trait for dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray
     */
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    struct is_ndarray<dynamic_ndarray<T,storage_type,shape_storage_type>> : true_type {};

    /**
     * @brief specialization of is_dynamic_ndarray trait for dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray
     */
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    struct is_dynamic_ndarray<dynamic_ndarray<T,storage_type,shape_storage_type>> : true_type {};

    // cant be sure since the number of dimension depends at runtime
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    struct is_index_array<dynamic_ndarray<T,storage_type,shape_storage_type>> : false_type {};

    /**
     * @brief specialize replace_element_type for dynamic_ndarray
     * 
     * @tparam T 
     * @tparam U 
     * @tparam storage_type 
     * @tparam shape_storage_type 
     */
    template <typename T, typename U, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    struct replace_element_type<dynamic_ndarray<T,storage_type,shape_storage_type>,U,meta::enable_if_t<meta::is_num_v<U>>>
    {
        using type = dynamic_ndarray<U,storage_type,shape_storage_type>;
    }; // replace_element_type

#ifndef NMTOOLS_MAKE_DYNAMIC_NDARRAY
#define NMTOOLS_MAKE_DYNAMIC_NDARRAY
    /**
     * @brief Default definition of make_dynamic_ndarray,
     * returns nmtools::dynamic_ndarray.
     * 
     * @tparam element_t desired element type of resulting array
     * @todo consider to make this metafunction override-able via global macro
     */
    template <typename element_t>
    struct make_dynamic_ndarray
    {
        using type = dynamic_ndarray<element_t>;
    }; // make_dynamic_ndarray

    template <typename element_t>
    using make_dynamic_ndarray_t = type_t<make_dynamic_ndarray<element_t>>;
#endif // NMTOOLS_MAKE_DYNAMIC_NDARRAY

    /** @} */ // end group traits
    
} // namespace nmtools::meta

#include "nmtools/ndarray/fixed.hpp"

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * 
     */

    // TODO: remove
    /**
     * @brief specialization of metafunction get_ndarray_value_type,
     * which tells the value/element type of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray, deduced automatically
     */
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    struct get_ndarray_value_type<dynamic_ndarray<T,storage_type,shape_storage_type>>
    {
        using type = T;
    };
    /** @} */ // end group meta
} // namespace nmtools::meta

#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/isequal.hpp"

namespace nmtools
{
    
    /**
     * @brief assignment operator for dynamic_ndarray from generic ndarray type
     * 
     * @tparam T element type of dynamic_ndarray
     * @tparam ndarray_t type of ndarray to be cloned
     * @param rhs array to be cloned
     * @return constexpr auto 
     */
    template <typename T, template <typename...> typename storage_type, template<typename...> typename shape_storage_type>
    template <typename ndarray_t, typename>
    constexpr auto dynamic_ndarray<T,storage_type,shape_storage_type>::operator=(const ndarray_t& rhs)
    {
        using nmtools::dim;
        using nmtools::shape;
        using nmtools::utils::isequal;

        nmtools_cassert (isequal(dim(rhs),dim(*this))
            , "mismatched dimension for dynamic_ndarray assignment"
        );
        nmtools_cassert (isequal(shape(rhs),shape(*this))
            , "mismatched shape for dynamic_ndarray assignment"
        );

        auto flat_rhs = unwrap(view::flatten(rhs));
        for (size_t i=0; i<numel_; i++)
            nmtools::at(this->data_,i) = nmtools::at(flat_rhs,i);

        return *this;
    } // operator=

} // namespace nmtools

#endif // NMTOOLS_DISABLE_DYNAMIC_ARRAY

namespace nmtools::meta
{

#ifndef NMTOOLS_MAKE_DYNAMIC_NDARRAY
#define NMTOOLS_MAKE_DYNAMIC_NDARRAY

    namespace error
    {
        struct DYNAMIC_ARRAY_DISABLED : detail::fail_t {};
    }
    /**
     * @brief Default definition of make_dynamic_ndarray,
     * returns nmtools::dynamic_ndarray.
     * 
     * @tparam element_t desired element type of resulting array
     * @todo consider to make this metafunction override-able via global macro
     */
    template <typename element_t>
    struct make_dynamic_ndarray
    {
        using type = error::DYNAMIC_ARRAY_DISABLED;
    }; // make_dynamic_ndarray

    template <typename element_t>
    using make_dynamic_ndarray_t = type_t<make_dynamic_ndarray<element_t>>;

#endif // NMTOOLS_MAKE_DYNAMIC_NDARRAY

} // nmtools::meta

#endif // NMTOOLS_ARRAY_NDARRAY_DYNAMIC_HPP