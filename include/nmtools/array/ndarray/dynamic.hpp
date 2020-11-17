#ifndef NMTOOLS_ARRAY_NDARRAY_DYNAMIC_HPP
#define NMTOOLS_ARRAY_NDARRAY_DYNAMIC_HPP

#include "nmtools/array/detail.hpp"
#include <cassert>
#include <vector>
#include <initializer_list>

namespace nmtools::array
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
    template <typename T, template <typename> typename storage_type=std::vector, template<typename> typename shape_storage_type=std::vector>
    struct dynamic_ndarray
    {
        using data_type = storage_type<T>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using shape_type = shape_storage_type<size_t>;
        using stride_type = shape_storage_type<size_t>;

        /**
         * @brief construct dynamic_ndarray given shape
         * 
         * @param shape desired shape of dynamic_ndarray
         */
        explicit dynamic_ndarray(std::vector<size_type> shape)
            : shape_(shape)
        {
            strides_ = strides();
            numel_   = numel();
            data.resize(numel_);
        }

        /**
         * @brief construct dynamic_ndarray from 1D initializer_list
         * 
         * @param initializer 
         */
        explicit dynamic_ndarray(std::initializer_list<value_type> initializer)
        {
            shape_   = shape_type({initializer.size()});
            strides_ = strides();
            numel_   = numel();
            data.resize(numel_);
            size_t i = 0;
            // TODO: find best way to copy
            for (auto v : initializer)
                data[i++] = v;
        }

        /**
         * @brief construct dynamic_ndarray from 1D intializer_list with specified shape
         * 
         * @param initializer 
         * @param shape desired shape
         */
        explicit dynamic_ndarray(std::initializer_list<value_type> initializer, std::vector<size_type> shape)
        {
            shape_ = shape;
            strides_ = strides();
            numel_ = numel();
            data.resize(numel_);
            size_t i = 0;
            assert (initializer.size() == numel_);
            // TODO: find best way to copy
            for (auto v : initializer)
                data[i++] = v;
        }

        /**
         * @brief construct dynamic_ndarray from nested initializer list
         * 
         * @param initializer 
         */
        explicit dynamic_ndarray(std::initializer_list<std::initializer_list<value_type>> initializer)
        {
            shape_   = shape_type({initializer.size(), (initializer.size()?initializer.begin()->size() : 0)});
            strides_ = strides();
            numel_   = numel();
            data.resize(numel_);
            size_t i = 0;
            for (const auto &v : initializer)
                for (const auto &e : v)
                    data[i++] = e;
        }

        // ambiguous call
        // TODO: fix
        // explicit dynamic_ndarray(std::initializer_list<std::initializer_list<std::initializer_list<value_type>>> initializer)
        // {
        //     auto i = initializer.size();
        //     auto j = (initializer.size() ? initializer.begin()->size() : 0);
        //     auto k = (j > 0 ? initializer.begin()->begin()->size() : 0);
        //     shape_ = shape_type({i,j,k});
        //     strides_ = strides();
        //     numel_ = numel();
        //     data.resize(numel_);
        //     size_t idx = 0;
        //     for (auto&& c : initializer)
        //         for (auto&& m : c)
        //             for (auto&& n : m)
        //                 data[idx++] = n;
        // }

        data_type data;
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
                stride[i] = detail::stride(shape_,i);
            return stride;
        } // strides

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
        constexpr reference operator()(size_type n, size_types...ns)
        {
            using common_size_t = std::common_type_t<size_type,size_types...>;
            auto indices = std::array<common_size_t,sizeof...(ns)+1>{
                n, static_cast<common_size_t>(ns)...
            };
            assert (dim()==indices.size());
            auto offset = detail::compute_offset(strides_, indices);
            return data[offset];
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
        constexpr const_reference operator()(size_type n, size_types...ns) const
        {
            using common_size_t = std::common_type_t<size_type,size_types...>;
            auto indices = std::array<common_size_t,sizeof...(ns)+1>{
                n, static_cast<common_size_t>(ns)...
            };
            assert (dim()==indices.size());
            auto offset = detail::compute_offset(strides_, indices);
            return data[offset];
        } // operator()

        template <typename ndarray_t>
        constexpr auto operator=(const ndarray_t& rhs);

        /**
         * @brief provides assignment operator from nested std::array
         * 
         * @param rhs nested std array to be copied
         * @return constexpr decltype(auto) 
         */
        template <size_t Shape1, size_t...ShapeN>
        constexpr decltype(auto) operator=(meta::make_nested_raw_array_t<T,Shape1,ShapeN...>&& rhs)
        {
            using nested_t = meta::make_nested_raw_array_t<T,Shape1,ShapeN...>;
            return this->template operator=<nested_t>(std::forward<nested_t>(rhs));
        } // operator=

    }; // struct dynamic_ndarray

    /** @} */ // end group dynamic
    
} // namespace nmtools::array

namespace nmtools
{
    /**
     * @brief return the shape of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray, deduced via template argument deduction
     * @param a 
     * @return auto 
     */
    template <typename T>
    auto shape(const array::dynamic_ndarray<T>& a)
    {
        return a.shape();
    } // shape

    /**
     * @brief return the dimensionality of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray, deduced via template argument deduction
     * @param a array in which its dim is to be read
     * @return auto 
     */
    template <typename T>
    auto dim(const array::dynamic_ndarray<T>& a)
    {
        return a.dim();
    } // dim

} // namespace nmtools

#include "nmtools/traits.hpp"

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
    template <typename T>
    struct is_ndarray<array::dynamic_ndarray<T>> : true_type {};

    /**
     * @brief specialization of is_dynamic_ndarray trait for dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray
     */
    template <typename T>
    struct is_dynamic_ndarray<array::dynamic_ndarray<T>> : true_type {};

    /** @} */ // end group traits
    
} // namespace nmtools::meta

#include "nmtools/meta.hpp"
// include fixed array for metafunction specialization
// note: fixed array also include array/utility,
// include here so that dynamic vector_size and matrix_size visible
#include "nmtools/array/fixed.hpp"

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * 
     */

    /**
     * @brief specialization of metafunction get_ndarray_value_type,
     * which tells the value/element type of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarrray, deduced automatically
     */
    template <typename T>
    struct get_ndarray_value_type<array::dynamic_ndarray<T>>
    {
        using type = T;
    };
    /** @} */ // end group meta
} // namespace nmtools::meta

#include "nmtools/array/utility/clone.hpp" // clone_impl

namespace nmtools::array
{
    
    /**
     * @brief assignment operator for dynamic_ndarray from generic matrix type
     * 
     * @tparam T element type of dynamic_ndarray
     * @tparam Rows compile-time rows of dynamic_ndarray
     * @tparam Cols compile-time cols of dynamic_ndarray
     * @tparam ndarray_t type of matrix to be cloned
     * @param rhs matrix to be cloned
     * @return constexpr auto 
     * @see nmtools::matrix_size
     * @see nmtools::detail::clone_impl
     */
    template <typename T, template <typename> typename storage_type, template<typename> typename shape_storage_type>
    template <typename ndarray_t>
    constexpr auto dynamic_ndarray<T,storage_type,shape_storage_type>::operator=(const ndarray_t& rhs)
    {
        static_assert(
            meta::is_array2d_v<ndarray_t> || meta::is_array1d_v<ndarray_t>,
            "dynamic_ndarray only support assignment from array2d for now"
        );

        using ::nmtools::detail::clone_impl;

        if constexpr (meta::is_array2d_v<ndarray_t>) {
            auto [rows, cols] = matrix_size(rhs);
            assert( (shape_.size()==2) && (rows==shape_[1]) && (cols==shape_[1])
                // , "mismatched type for dynamic_ndarray assignment"
            );
            clone_impl(*this,rhs,rows,cols);
        }
        else {
            auto n = vector_size(rhs);
            assert( (shape_.size()==1) && (n==numel_)
                // , "mismatched type for dynamic_ndarray assignment"
            );
            clone_impl(*this,rhs,n);
        }

        return *this;
    } // operator=

} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_NDARRAY_DYNAMIC_HPP