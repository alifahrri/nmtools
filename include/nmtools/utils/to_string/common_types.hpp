#ifndef NMTOOLS_UTILS_TO_STRING_COMMON_TYPES_HPP
#define NMTOOLS_UTILS_TO_STRING_COMMON_TYPES_HPP

#include "nmtools/utils/to_string/to_string.hpp"

#if NMTOOLS_HAS_STRING

#include "nmtools/meta.hpp"
#include "nmtools/array/utility.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/utility/apply_at.hpp"

namespace nmtools::utils
{
    /**
     * @brief Quick workaround to remove substring from string
     * 
     * @tparam string 
     * @param str 
     * @param substr 
     * @return auto 
     */
    template <typename string>
    inline auto remove_string(string& str, const string& substr)
    {
        // NOTE: quick workaround for checkif if we have full std string features
        // maybe not available on arduino
        #if (NMTOOLS_HAS_SSTREAM)
        auto start_pos = string::npos;
        do {
          start_pos = str.find(substr);
          if (start_pos != string::npos) {
            str.erase(start_pos, substr.size());
          }
        } while (start_pos != string::npos);
        #endif // NMTOOLS_HAS_SSTREAM
    }
}

namespace nmtools::utils::impl
{
    template <
        typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename compute_offset_t
    >
    struct to_string_t<
        const array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t> *, none_t, void
    > : to_string_t<array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t> *, none_t> {};

    template <typename T>
    struct to_string_t<T,none_t,void>
    {
        auto operator()(const T& array) const noexcept
        {
            nmtools_string str;
            using ::nmtools::index::ndindex;

            if constexpr (is_ellipsis_v<T>)
                str += "...";
            else if constexpr (is_none_v<T>)
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
                // TODO: do not use as array
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
                    str += to_string(a);

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
            }
            else if constexpr (meta::is_list_v<T>) {
                auto dim = len(array);
                for (size_t i=0; i<(size_t)dim; i++) {
                    if (i==0) {
                        str += "[";
                    }
                    str += "\t";
                    str += to_string(at(array,i));
                    if (i==(size_t)(dim-1)) {
                        str += "]";
                    }
                }
            }
            #if NMTOOLS_HAS_SSTREAM
            else if constexpr (meta::is_pointer_v<T>) {
                nmtools_sstream ss;
                auto type_name = NMTOOLS_TYPENAME_TO_STRING(T);
                ss << "<" << type_name << ">" << "(" << array << ")";

                str += ss.str();
            }
            #endif
            return str;
        } // operator()
    }; // struct to_string_t

    template <
        typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename compute_offset_t
    >
    struct to_string_t<
        array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t> *, none_t, void
    > {
        using array_type = array::ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,compute_offset_t>;

        auto operator()(const array_type* ptr) const noexcept
        {
            auto ptr_str = nmtools_string("");

            #if NMTOOLS_HAS_SSTREAM

            nmtools_sstream ss;
            auto buffer_name = NMTOOLS_TYPENAME_TO_STRING(buffer_t);
            auto shape_name  = NMTOOLS_TYPENAME_TO_STRING(shape_buffer_t);
            ss << "(" << ptr << ")\n"
            << "<ndarray_t<" << buffer_name << "," << shape_name << "...> >";

            ptr_str += ss.str();

            #endif // NMTOOLS_HAS_SSTREAM

            return ptr_str;
        }
    };

    #define NMTOOLS_DTYPE_TO_STRING_CASE(T,type,string) \
    if constexpr (meta::is_same_v<T,type>) { \
        return nmtools_string(string); \
    }

    template <typename T>
    struct to_string_t<
        dtype_t<T>, none_t, void
    >
    {
        auto operator()(dtype_t<T>) const noexcept
        {
            NMTOOLS_DTYPE_TO_STRING_CASE(T,float,"float32")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,double,"float64")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,int64_t,"int64")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,int32_t,"int32")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,int16_t,"int16")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,int8_t,"int8")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,uint64_t,"uint64")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,uint32_t,"uint32")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,uint16_t,"uint16")
            else NMTOOLS_DTYPE_TO_STRING_CASE(T,uint8_t,"uint8")
            else return nmtools_string("");
        }
    };

    #undef NMTOOLS_DTYPE_TO_STRING_CASE

}
#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_UTILS_TO_STRING_COMMON_TYPES_HPP