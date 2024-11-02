#ifndef NMTOOLS_UTILS_TO_STRING_COMMON_TYPES_HPP
#define NMTOOLS_UTILS_TO_STRING_COMMON_TYPES_HPP

#include "nmtools/utility/to_string/to_string.hpp"

#if NMTOOLS_HAS_STRING

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/utility/at.hpp"

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
        // NOTE: quick workaround for check if if we have full std string features
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

    template <typename string>
    inline auto replace_string(string& str, const string& substr, const string& replacement)
    {
        // NOTE: quick workaround for check if if we have full std string features
        // maybe not available on arduino
        #if (NMTOOLS_HAS_SSTREAM)
        auto start_pos = string::npos;
        do {
          start_pos = str.find(substr);
          if (start_pos != string::npos) {
            str.replace(start_pos, substr.size(), replacement);
          }
        } while (start_pos != string::npos);
        #endif // NMTOOLS_HAS_SSTREAM
    }
}

namespace nmtools::utils::impl
{
    template <typename T, char tab, char space, char comma, char open_bracket, char close_bracket>
    struct to_string_t<T,fmt_string_t<tab,space,comma,open_bracket,close_bracket>,meta::enable_if_t<
        is_ellipsis_v<T> || is_none_v<T> || meta::is_either_v<T> || meta::is_nothing_v<T> || meta::is_maybe_v<T>
        || meta::is_num_v<T> || meta::is_integral_constant_v<T> || meta::is_ndarray_v<T> || meta::is_list_v<T>
        || meta::is_pointer_v<T> || meta::is_index_array_v<T> || meta::is_tuple_v<T> || meta::is_slice_index_v<T> || meta::is_slice_index_array_v<T>
    >>{
        using formatter_t = fmt_string_t<tab,space,comma,open_bracket,close_bracket>;
        using result_type = nmtools_string;

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
                    str += to_string(*l_ptr,formatter_t{});
                } else {
                    auto r_ptr = nmtools::get_if<rhs_t>(&array);
                    str += to_string(*r_ptr,formatter_t{});
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
                    str += to_string(*array,formatter_t{});
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
                        using array_t = nmtools_array<index_t,N>;
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

                auto dim = len(shape_);
                auto last_dim = at(s,dim-1);

                // print empty ndarray
                if (!len(indices)) {
                    str += open_bracket;
                    str += close_bracket;
                }
                
                for (size_t i=0; i<(size_t)len(indices); i++) {
                    auto idx_ = indices[i];
                    auto idx  = as_array(idx_);
                    // TODO: support tuple for apply_at
                    auto a = apply_at(array, idx);

                    // check if we should print open bracket
                    // only add open bracket up to axis n
                    // that is equal to zero, starting from last axis
                    for (int ii=len(idx)-1; ii>=0; ii--) {
                        if (at(idx,ii)==0) {
                            str += open_bracket;
                        }
                        else break;
                    }

                    str += tab;
                    str += to_string(a,formatter_t{});
                    if (at(idx,dim-1)!=(last_dim-1)) {
                        str += comma;
                    }

                    int print_comma = 0;
                    // check if we should print closing bracket
                    // only add open bracket up to axis n
                    // that is equal to shape[n]-1, starting from last axis
                    for (int ii=(int)len(idx)-1; ii>=0; ii--) {
                        // for simplicity just use int
                        if ((int)at(idx,ii)==(int)(at(s,ii)-1)) {
                            str += close_bracket;
                            // also count how much newline to be printed
                            print_comma++;
                        }
                        else break;
                    }
                    if (print_comma && i<len(indices)-1) {
                        str += comma;
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
                    if constexpr (i<(N-1)) {
                        str += comma; str += tab;
                    }
                });
                str += ")";
            }
            else if constexpr (meta::is_list_v<T>) {
                auto dim = len(array);
                for (size_t i=0; i<(size_t)dim; i++) {
                    if (i==0) {
                        str += open_bracket;
                    }
                    str += tab;
                    str += to_string(at(array,i),formatter_t{});
                    if (i==(size_t)(dim-1)) {
                        str += close_bracket;
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
            else if constexpr (meta::is_slice_index_v<T> || meta::is_slice_index_array_v<T>) {
                // TODO: implement
                str += NMTOOLS_TYPENAME_TO_STRING(T);
            }
            return str;
        } // operator()
    }; // struct to_string_t

    template <typename T, typename formatter_t, typename>
    struct to_string_t
    {
        static constexpr auto result_vtype = [](){
            if constexpr (is_none_v<formatter_t>) {
                using mapper_type = to_string_t<T,fmt_string_t<>>;
                if constexpr (meta::has_result_type_v<mapper_type>) {
                    using result_type = typename mapper_type::result_type;
                    return meta::as_value_v<result_type>;
                } else {
                    using result_type = error::TO_STRING_UNSUPPORTED<T,formatter_t>;
                    return meta::as_value_v<result_type>;
                }
            } else {
                using result_type = error::TO_STRING_UNSUPPORTED<T,formatter_t>;
                return meta::as_value_v<result_type>;
            }
        }();
        using result_type = meta::type_t<decltype(result_vtype)>;

        auto operator()([[maybe_unused]] const T& t) const noexcept
        {
            if constexpr (meta::is_fail_v<result_type>) {
                return result_type{};
            } else {
                return to_string(t,fmt_string_t<>{});
            }
        }
    }; // struct to_string_t

    #define NMTOOLS_DTYPE_TO_STRING_CASE(T,type,string) \
    if constexpr (meta::is_same_v<T,type>) { \
        return nmtools_string(string); \
    }

    template <typename T, auto...fmt_args>
    struct to_string_t<
        dtype_t<T>, fmt_string_t<fmt_args...>, void
    >
    {
        using result_type = nmtools_string;

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