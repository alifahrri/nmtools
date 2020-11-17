#ifndef NMTOOLS_ARRAY_VECTOR_DYNAMIC_HPP
#define NMTOOLS_ARRAY_VECTOR_DYNAMIC_HPP

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
     * @brief sample implementation of resizeable vector
     * 
     * @tparam T elemen type of dynamic vector
     * @tparam storage_type=std::vector template template parameter which will be used to store actual data
     */
    template <typename T, template <typename> typename storage_type=std::vector>
    struct dynamic_vector
    {
        using data_type = storage_type<T>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;

        explicit dynamic_vector(size_type n)
        {
            data.resize(n);
        }

        dynamic_vector(initializer_list<value_type> initializer)
        {
            data.resize(initializer.size());
            size_t i=0;
            for (auto v : initializer)
                data[i++] = v;
        }

        /**
         * @brief underlying storage
         * 
         */
        data_type data;

        /**
         * @brief access element at i-th index
         * 
         * @param i 
         * @return constexpr reference 
         */
        constexpr reference operator()(size_type i)
        {
            return data[i];
        }

        /**
         * @brief access element at i-th index
         * 
         * @param i 
         * @return constexpr const_reference 
         */
        constexpr const_reference operator()(size_type i) const
        {
            return data[i];
        }

        /**
         * @brief return the size of vector (number of elements)
         * 
         * @return constexpr size_type 
         */
        constexpr size_type size() const noexcept
        {
            return data.size();
        }

        /**
         * @brief resize vector to contain count elements.
         * 
         * @param count 
         */
        void resize(size_type count)
        {
            data.resize(count);
        }
    };

    /**
     * @brief make dynamic_vector can be used with range-based for loop
     * 
     * @tparam T value_type of dynamic_vector, deduced automatically
     * @param v 
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto begin(dynamic_vector<T>& v)
    {
        return v.data.begin();
    } // constexpr auto begin

    template <typename T>
    constexpr auto begin(const dynamic_vector<T>& v)
    {
        return v.data.begin();
    } // constexpr auto begin

    /**
     * @brief make dynamic_vector can be used with range-based for loop
     * 
     * @tparam T value_type of dynamic_vector, deduced automatically
     * @param v 
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto end(dynamic_vector<T>& v)
    {
        return v.data.end();
    } // constexpr auto end

    template <typename T>
    constexpr auto end(const dynamic_vector<T>& v)
    {
        return v.data.end();
    } // constexpr auto end

    /** @} */ // end group dynamic
    
} // namespace nmtools::array

namespace nmtools
{

    /**
     * @brief specialization of vector_size for dynamic_vector
     * 
     * @tparam T element type of dynamic_vector, deduced via template argument deduction
     * @param v vector which size is to be checked
     * @return auto 
     */
    template <typename T>
    auto vector_size(const array::dynamic_vector<T>& v)
    {
        return v.size();
    }

} // namespace nmtools

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * 
     */

    /**
     * @brief overloaded version of zeros_like for array::dynamic_vector
     * 
     * @tparam T element type of dynamic_vector
     * @param v reference vector
     * @return auto 
     */
    template <typename T>
    auto zeros_like(const array::dynamic_vector<T>& v)
    {
        auto ret = array::dynamic_vector<T>(v.size()); 
        return ret;
    }

    /** @} */ // end group blas
}

#include "nmtools/traits.hpp"

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * 
     */

    /**
     * @brief specialization of is_array1d traits for dynamic_vector which is true
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     */
    template <typename T>
    struct is_array1d<array::dynamic_vector<T>> : true_type {};

    /**
     * @brief specialization of is_array2d traits for dynamic_vector which is false
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     */
    template <typename T>
    struct is_array2d<array::dynamic_vector<T>> : false_type {};

    /**
     * @brief specialization of is_resizeable trait for dynamic_vector which is true
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     */
    template <typename T>
    struct is_resizeable<array::dynamic_vector<T>> : true_type {};

    /**
     * @brief specialization of fixed_dim metafunction for dynamic_vector.
     *
     * Tells the compiler that dynamic_vector has fixed-dimension of 1.
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     * @tparam storage_type, template-template parameter corresponding to the storage type of dynamic_vector, automatically deduced
     */
    template <typename T, template <typename> typename storage_type>
    struct fixed_dim<array::dynamic_vector<T,storage_type>>
    {
        static constexpr auto value = 1;
        using value_type = decltype(value);
    }; // fixed_dim

    /** @} */ // end group traits
    
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VECTOR_DYNAMIC_HPP