/**
 * @file to_string.hpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief Contains definition of to_string
 * @version 0.1
 * @date 2020-11-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef NMTOOLS_UTILS_TO_STRING_HPP
#define NMTOOLS_UTILS_TO_STRING_HPP

#if __has_include(<string>)
#define HAS_STRING true
#else
#define HAS_STRING false
#endif

#if HAS_STRING

#include "nmtools/traits.hpp"
#include "nmtools/array/utility.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/utility/apply_at.hpp"

#include <type_traits>
#include <cassert>
#include <cmath>
#include <tuple>
#include <array>

namespace nmtools::utils
{
    /**
     * @brief to_string given array to given stream type.
     * 
     * @tparam stream_t stream type, e.g. std::stringstream,
     * @tparam T array-like, 2d, 1d, or scalar
     * @param array array to to_string
     * @return auto stream with type of stream_t
     */
    template <typename T>
    auto to_string(const T& array)
    {
        constexpr auto is_packed = meta::has_tuple_size_v<T>;

        std::string str;

        if constexpr (std::is_arithmetic_v<T>) {
            using std::to_string;
            str += to_string(array);
        }
        else if constexpr (meta::is_ndarray_v<T>) {
            using std::to_string;
            using ::nmtools::detail::make_array;
            auto s = [&](){
                auto shape_ = shape(array);
                using shape_t = decltype(shape_);
                if constexpr (meta::is_specialization_v<shape_t,std::tuple>
                    || meta::is_specialization_v<shape_t,std::pair>)
                    return make_array<std::array>(shape_);
                else return shape_;
            }();
            auto indices = indices_pack(s);
            
            for (int i=0; i<indices.size(); i++) {
                auto idx = [&](){
                    auto idx = indices[i];
                    using idx_t = decltype(idx);
                    if constexpr (meta::is_specialization_v<idx_t,std::tuple>
                        || meta::is_specialization_v<idx_t,std::pair>)
                        return make_array<std::array>(idx);
                    else return idx;
                }();
                auto a = apply_at(array, idx);

                // check if we should print open bracket
                // only add open bracket up to axis n
                // that is equal to zero, starting from last axis
                for (int ii=idx.size()-1; ii>=0; ii--) {
                    if (idx[ii]==0)
                        str += "[";
                    else break;
                }

                str += "\t";
                str += to_string(a);

                int print_comma = 0;
                // check if we should print closing bracket
                // only add open bracket up to axis n
                // that is equal to shape[n]-1, starting from last axis
                for (int ii=idx.size()-1; ii>=0; ii--) {
                    if (idx[ii]==(s[ii]-1)) {
                        str += "]";
                        // also count how much newline to be printed
                        print_comma++;
                    }
                    else break;
                }
                if (print_comma && i<indices.size()-1) {
                    str += ",";
                    for (int ii=0; ii<print_comma; ii++)
                        str += "\n";
                }
            }
        } // meta::is_ndarray_v<T>
        // handle packed type (e.g. tuple), recursively call to_string for each elements
        else if constexpr (is_packed) {
            constexpr auto N = std::tuple_size_v<T>;
            str += "(";
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                const auto& a = std::get<i>(array);
                str += to_string(a);
                if constexpr (i<(N-1))
                    str += ",\t";
            });
            str += ")";
        } // is_packed
        return str;
    } // auto to_string
} // namespace nmtools::utils

#endif // HAS_STRING

#endif // NMTOOLS_UTILS_TO_STRING_HPP