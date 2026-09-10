#ifndef NMTOOLS_UTL_FORMAT_HPP
#define NMTOOLS_UTL_FORMAT_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/variant.hpp"
#include "nmtools/utl/string.hpp"
#include "nmtools/utl/static_string.hpp"

namespace nmtools::utl
{
    template <typename string_t=string, typename...args_t>
    constexpr auto make_format_args(const args_t&...args)
    {
        using variant_type = variant<
            int8_t,int16_t,int32_t,int64_t
            , uint8_t,uint16_t,uint32_t,uint64_t
            , float,double
            , string_t
        >;
        using result_t = array<variant_type,sizeof...(args)>;

        return result_t{args...};
    }

    template <typename out_string_t, typename string_t, typename args_t>
    constexpr auto vformat(const string_t& m_str, const args_t& args);

    template <typename out_string_t=utl::string, typename string_t, typename...args_t>
    constexpr auto format(const string_t& str, const args_t&...args)
    {
        auto fmt_args = make_format_args<out_string_t>(args...);
        return vformat<out_string_t>(str,fmt_args);
    }

    template <typename out_string_t=utl::string, typename string_t, typename args_t>
    constexpr auto vformat(const string_t& m_str, [[maybe_unused]] const args_t& args)
    {
        out_string_t out;

        nm_size_t arg_idx = 0;

        auto str = [&](){
            if constexpr (!is_same_v<out_string_t,string_t>) {
                return out_string_t(m_str);;
            } else {
                return m_str;
            }
        }();
        for (nm_size_t i=0; i<str.size(); i++) {
            auto c = str[i];

            if (c == '{') {
                if (i+1 < str.size() && str[i+1] == '{') {
                    out += "{";
                    ++i;
                    continue;
                }
                auto end_brace = str.find("}",i);
                auto placeholder = str.substr(i+1,end_brace-i-1);

                // use the specified arg index if the placeholder is a number,
                // otherwise consume the args in sequential order
                auto arg_index = args.size();
                if (placeholder.size() > 0) {
                    arg_index = 0;
                    for (nm_size_t k=0; k<placeholder.size(); k++) {
                        auto chr = placeholder[k];
                        if ((chr >= '0') && (chr <= '9')) {
                            arg_index = arg_index*10 + (nm_size_t)(chr - '0');
                        } else {
                            // not a number, fallback to sequential
                            arg_index = args.size();
                            break;
                        }
                    }
                }
                if (arg_index == args.size()) {
                    arg_index = arg_idx++;
                }
                nmtools_panic( arg_index < args.size(), "invalid format arg index" );
                const auto& arg = args[arg_index];
                if (auto i8_ptr = arg.template get_if<int8_t>()) {
                    out += to_string<out_string_t>(*i8_ptr);
                } else if (auto i16_ptr = arg.template get_if<int16_t>()) {
                    out += to_string<out_string_t>(*i16_ptr);
                } else if (auto i32_ptr = arg.template get_if<int32_t>()) {
                    out += to_string<out_string_t>(*i32_ptr);
                } else if (auto i64_ptr = arg.template get_if<int64_t>()) {
                    out += to_string<out_string_t>(*i64_ptr);
                } else if (auto u8_ptr = arg.template get_if<uint8_t>()) {
                    out += to_string<out_string_t>(*u8_ptr);
                } else if (auto u16_ptr = arg.template get_if<uint16_t>()) {
                    out += to_string<out_string_t>(*u16_ptr);
                } else if (auto u32_ptr = arg.template get_if<uint32_t>()) {
                    out += to_string<out_string_t>(*u32_ptr);
                } else if (auto u64_ptr = arg.template get_if<uint64_t>()) {
                    out += to_string<out_string_t>(*u64_ptr);
                } else if (auto f32_ptr = arg.template get_if<float>()) {
                    out += to_string<out_string_t>(*f32_ptr);
                } else if (auto f64_ptr = arg.template get_if<double>()) {
                    out += to_string<out_string_t>(*f64_ptr);
                } else if (auto str_ptr = arg.template get_if<out_string_t>()) {
                    out += *str_ptr;
                }
                i = end_brace;
            // } else if (c == '}') {
            //     out += "}";
                // TODO: validate }}
                // throw if invalid
            } else if (c > 0) {
                out += c;
            }
        }

        return out;
    }
}

#endif // NMTOOLS_UTL_FORMAT_HPP