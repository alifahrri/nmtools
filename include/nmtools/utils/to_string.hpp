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
    #include <string>
    #define nmtools_string std::string
    // NOTE: quick hack, arduino (esp. atmel avr) doesn't have std::to_string
    // TODO: find better alternative
    #define nmtools_to_string std::to_string
#elif defined(ARDUINO)
    // TODO: do not include arduino here (?)
    #include <Arduino.h>
    #define HAS_STRING true
    #define nmtools_string String
    // NOTE: quick hack
    // TODO: find better alternative
    #define nmtools_to_string String
#else
#define HAS_STRING false
#endif

#if HAS_STRING

#include "nmtools/meta.hpp"
#include "nmtools/array/utility.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/utility/apply_at.hpp"

namespace nmtools::utils
{
    // NOTE: forward declare function here to allow function object to_string_t to
    // call the function,
    // this is because to_string_t can't deduce template args automatically (no constructor, and operator() cant be static)
    // TODO: revisit this and maybe refactor
    template <typename formatter_t=none_t, typename T>
    auto to_string(const T& array, formatter_t=formatter_t{});
}

namespace nmtools::utils::impl
{
template <typename T, typename formatter_t, typename=void>
struct to_string_t;

template <typename T>
struct to_string_t<T,none_t,void>
{
    auto operator()(const T& array) const noexcept
    {
        nmtools_string str;
        using ::nmtools::index::ndindex;

        if constexpr (is_none_v<T>)
            str += "None";
        else if constexpr (meta::is_either_v<T>) {
            using lhs_t = meta::get_either_left_t<T>;
            using rhs_t = meta::get_either_right_t<T>;
            // assume get_if<type>(&array) is available for either type
            if (auto l_ptr = nmtools::get_if<lhs_t>(&array)) {
                // NOTE: this call require forward declaration of to_string above
                str += to_string(*l_ptr);
            } else {
                auto r_ptr = nmtools::get_if<rhs_t>(&array);
                str += to_string(*r_ptr);
            }
        }
        else if constexpr (meta::is_nothing_v<T>) {
            str += "Nothing";
        }
        else if constexpr (meta::is_maybe_v<T>) {
            // for maybe type,
            // assume casting to bool checks if the objects contains a value
            // which is supported by std::optional
            if (static_cast<bool>(array))
                str += to_string(*array);
            else str += "Nothing";
        }
        else if constexpr (meta::is_num_v<T>) {
            // allow view type
            using type_t = meta::get_element_type_t<T>;
            str += nmtools_to_string(static_cast<type_t>(array));
        }
        else if constexpr (meta::is_integral_constant_v<T>) {
            str += nmtools_to_string(T::value);
        } // is_integral_constant
        else if constexpr (meta::is_ndarray_v<T>) {
            /**
             * @brief helper lambda to make sure to return array (instead of tuple)
             * this simplify indexing, since tuple must be unrolled (can't use runtime index)
             * 
             */
            auto as_array = [](auto shape_){
                using shape_t = decltype(shape_);
                using index_t = meta::get_element_or_common_type_t<shape_t>;
                if constexpr (meta::is_constant_index_array_v<shape_t>) {
                    return meta::to_value_v<shape_t>;
                } else if constexpr (meta::is_tuple_v<shape_t>) {
                    constexpr auto N = meta::len_v<shape_t>;
                    using array_t = meta::make_array_type_t<index_t,N>;
                    auto array = array_t{};
                    meta::template_for<N>([&](auto i){
                        at(array,i) = at(shape_,i);
                    });
                    return array;
                } else {
                    return shape_;
                }
            };

            auto shape_ = shape(array);
            auto s = as_array(shape_);
            auto indices = ndindex(s);

            // print empty ndarray
            if (!len(indices))
                str = "[]";
            
            for (size_t i=0; i<(size_t)len(indices); i++) {
                auto idx_ = indices[i];
                auto idx  = as_array(idx_);
                // TODO: support tuple for apply_at
                auto a = apply_at(array, idx);

                // check if we should print open bracket
                // only add open bracket up to axis n
                // that is equal to zero, starting from last axis
                for (int ii=len(idx)-1; ii>=0; ii--) {
                    if (at(idx,ii)==0)
                        str += "[";
                    else break;
                }

                str += "\t";
                str += nmtools_to_string(a);

                int print_comma = 0;
                // check if we should print closing bracket
                // only add open bracket up to axis n
                // that is equal to shape[n]-1, starting from last axis
                for (int ii=(int)len(idx)-1; ii>=0; ii--) {
                    // for simplicity just use int
                    if ((int)at(idx,ii)==(int)(at(s,ii)-1)) {
                        str += "]";
                        // also count how much newline to be printed
                        print_comma++;
                    }
                    else break;
                }
                if (print_comma && i<len(indices)-1) {
                    str += ",";
                    for (int ii=0; ii<print_comma; ii++)
                        str += "\n";
                }
            }
        } // meta::is_ndarray_v<T>
        // TODO: remove tuple_size metafunctions
        // handle packed type (e.g. tuple), recursively call to_string for each elements
        else if constexpr (meta::has_tuple_size_v<T>) {
            constexpr auto N = meta::len_v<T>;
            str += "(";
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                const auto& a = nmtools::get<i>(array);
                str += to_string(a);
                if constexpr (i<(N-1))
                    str += ",\t";
            });
            str += ")";
        } // is_packed
        return str;
    } // operator()
}; // struct to_string_t

template <typename T, typename formatter_t>
inline constexpr auto to_string_v = to_string_t<T,formatter_t>{};
}
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
    template <typename formatter_t, typename T>
    auto to_string(const T& array, formatter_t)
    {
        constexpr auto to_string = impl::to_string_v<T,formatter_t>;
        return to_string(array);
    } // auto to_string
} // namespace nmtools::utils

#endif // HAS_STRING

#endif // NMTOOLS_UTILS_TO_STRING_HPP