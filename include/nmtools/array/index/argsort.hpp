#ifndef NMTOOLS_ARRAY_INDEX_ARGSORT_HPP
#define NMTOOLS_ARRAY_INDEX_ARGSORT_HPP

#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    // tag to resolve argsort return type
    struct argsort_t {};

    /**
     * @brief Return arguments (indices) that sorts array
     * 
     * @tparam array_t 
     * @param array     input array
     * @return constexpr auto 
     */
    template <typename array_t, meta::enable_if_t<!meta::is_maybe_v<array_t>,int> = 0>
    constexpr auto argsort(const array_t& array)
    {
        using result_t = meta::resolve_optype_t<argsort_t, array_t>;

        auto arg = result_t{};
        [[maybe_unused]] auto dim = len(array);
        [[maybe_unused]] auto swap = [](auto& lhs, auto& rhs){
            auto tmp = lhs;
            lhs = rhs;
            rhs = tmp;
        };

        if constexpr (meta::is_resizeable_v<result_t>) {
            arg.resize(dim);
        }

        // assume already sorted at resolve_optype if constant index
        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            // initialize with index
            for (size_t i=0; i<(size_t)dim; i++) {
                at(arg,i) = i;
            }

            // insertion argsort
            for (size_t i=1; i<(size_t)dim; i++) {
                int j = i;
                while ( (j > 0) && (at(array,at(arg,j-1)) > at(array,at(arg,j))) ) {
                    swap(at(arg,j), at(arg,j-1));
                    j = j - 1;
                }
            }
        }

        return arg;
    } // argsort

    /**
     * @brief Overloaded argsort for maybe type
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t, meta::enable_if_t<meta::is_maybe_v<array_t>,int> = 0>
    constexpr auto argsort(const array_t& array)
    {
        using result_t = meta::remove_cvref_t<decltype(argsort(*array))>;
        using return_t = meta::make_maybe_type_t<result_t>;

        auto ret = return_t{};
        if (static_cast<bool>(array)) {
            ret = argsort(*array);
        } else {
            ret = meta::Nothing;
        }

        return ret;
    } // argsort (maybe)
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct INDEX_ARGSORT_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename array_t>
    struct resolve_optype<
        void, index::argsort_t, array_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<array_t>) {
                constexpr auto array = to_value_v<array_t>;
                constexpr auto args  = index::argsort(array);
                // transform back to type
                using init_type = make_tuple_type_t<ct<at(args,0)>>;
                return template_reduce<nmtools::len(args)-1>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using init_i = ct<at(args,index+1)>;
                    return as_value_v<append_type_t<init_t,init_i>>;
                }, as_value_v<init_type>);
            } else if constexpr (is_bounded_array_v<array_t>) {
                using type = transform_bounded_array_t<array_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<array_t>) {
                return as_value_v<array_t>;
            } else {
                return as_value_v<error::INDEX_ARGSORT_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_ARGSORT_HPP