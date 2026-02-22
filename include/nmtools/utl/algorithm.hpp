#ifndef NMTOOLS_UTL_ALGORITHM_HPP
#define NMTOOLS_UTL_ALGORITHM_HPP

#include "nmtools/def.hpp"

namespace nmtools::utl
{
    template <typename array_t>
    constexpr auto is_sorted(const array_t& array)
    {
        auto n = array.size();

        if (n < 2) {
            return true;
        }

        for (nm_size_t i=0; i<(nm_size_t)n-1; i++) {
            if (array[i] > array[i+1]) {
                return false;
            }
        }

        return true;
    }

    template <typename array_t, typename F>
    constexpr auto insertion_sort_(array_t& array, F compare)
    {
        for (nm_index_t i=1; i<(nm_index_t)array.size(); i++) {
            auto key = array[i];
            auto j = i - 1;

            while ((j >= 0) && compare(array[j],key)) {
                array[j+1] = array[j];
                j = j - 1;
            }

            array[j+1] = key;
        }
    }

    template <typename array_t>
    constexpr auto insertion_sort_(array_t& array)
    {
        for (nm_index_t i=1; i<(nm_index_t)array.size(); i++) {
            auto key = array[i];
            auto j = i - 1;

            while ((j >= 0) && (array[j] > key)) {
                array[j+1] = array[j];
                j = j - 1;
            }

            array[j+1] = key;
        }
    }

    template <typename array_t>
    constexpr auto insertion_sort(array_t& array)
    {
        auto m_array = array;

        insertion_sort_(m_array);

        return m_array;
    }
}

#endif // NMTOOLS_UTL_ALGORITHM_HPP