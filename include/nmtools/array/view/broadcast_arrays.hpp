#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::view::detail::fn
{
    /**
     * @brief Returns either None (if array_t is number) or the shape otherwise
     * 
     * Broadcasting can involve number and ndarray(s).
     *
     * @tparam array_t 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto fixed_shape_or_none(meta::as_value<array_t>)
    {
        if constexpr (meta::is_num_v<array_t>) {
            return None;
        } else {
            return meta::fixed_ndarray_shape_v<array_t>;
        }
    } // fixed_shape_or_none

    /**
     * @brief Compile time version of index::broadcast_shape.
     * 
     * @tparam arrays_t 
     * @return constexpr auto 
     */
    template <typename...arrays_t>
    constexpr auto broadcast_shape(meta::as_value<arrays_t>...arrays)
    {
        // map type to value, and actually call broadcast_shape implementation
        // TODO: update broadcast_shape to use maybe type
        constexpr auto result  = index::broadcast_shape(fixed_shape_or_none(arrays)...);
        constexpr auto success = nmtools::get<0>(result);
        constexpr auto bshape  = nmtools::get<1>(result);
        using bshape_t = meta::remove_cvref_t<decltype(bshape)>;
        if constexpr (success && is_none_v<bshape_t>) {
            // Note broadcasting numbers return none
            return None;
        } else if constexpr (success && !is_none_v<bshape_t>) {
            constexpr auto vtype = meta::template_reduce<len(bshape)>([&](auto init, auto index){
                using init_t = meta::type_t<decltype(init)>;
                // NOTE: s_i maybe integral_constant
                // NOTE: this triggers gcc internal-compiler error
                // internal compiler error: in lookup_template_class_1, at cp/pt.c:9625
                constexpr auto s_i = at(bshape,index);
                constexpr auto shape_vtype = [&](){
                    if constexpr (meta::is_constant_index_v<decltype(s_i)>) {
                        return meta::as_value_v<decltype(s_i)>;
                    } else {
                        using shape_t = meta::ct<s_i>;
                        return meta::as_value_v<shape_t>;    
                    }
                }();
                using shape_t = meta::type_t<decltype(shape_vtype)>;
                if constexpr (meta::is_void_v<init_t>) {
                    using type = nmtools_tuple<shape_t>;
                    return meta::as_value_v<type>;
                } else {
                    using type = meta::append_type_t<init_t,shape_t>;
                    return meta::as_value_v<type>;
                }
            }, meta::as_value_v<void>);
            using type = meta::type_t<decltype(vtype)>;
            return type{};
        } else {
            // since this value is expected to be called at compile time,
            // return fail type when fail
            return meta::detail::Fail;
        }
    } // broadcast_shape
} // namespace nmtools::view::detail::fn

namespace nmtools::view
{
    /**
     * @brief broadcast arrays against each other.
     * 
     * @tparam arrays_t 
     * @param arrays 
     * @return constexpr auto 
     */
    template <typename...arrays_t>
    constexpr auto broadcast_arrays(const arrays_t&...arrays)
    {
        static_assert( sizeof...(arrays_t) >= 2
            , "please provide at least two arrays for broadcast_arrays");

        // when all arrays' shapes are known at compile time, perform checks at compile time
        // the return type is not wrapped, and should be noexcept ready
        if constexpr (((meta::is_fixed_size_ndarray_v<arrays_t> || meta::is_num_v<arrays_t>) && ...)) {
            constexpr auto bshape = detail::fn::broadcast_shape(meta::as_value_v<arrays_t>...);
            static_assert( !meta::is_fail_v<decltype(bshape)>
                , "cannot broadcast arrays together" );
            
            // deduce the resulting tuple.
            // without assuming some specific tuple type, can't use CTAD
            using types  = meta::type_list<const arrays_t&...>;
            using i_type = meta::make_tuple_type_t<decltype(broadcast_to(meta::declval<meta::at_t<types,0>>(),bshape))>;
            constexpr auto vtype = meta::template_reduce<sizeof...(arrays)-1>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value + 1;
                using init_t = meta::type_t<decltype(init)>;
                using type_i = meta::at_t<types,i>;
                using b_type = decltype(broadcast_to(meta::declval<type_i>(),bshape));
                using r_type = meta::append_type_t<init_t,b_type>;
                return meta::as_value_v<r_type>;
            }, meta::as_value_v<i_type>);
            using result_t = meta::type_t<decltype(vtype)>;
            static_assert( !meta::is_fail_v<result_t>, "nmtools meta unexpected error" );
            return result_t{broadcast_to(arrays,bshape)...};
        }
        // otherwise call runtime version,
        // the return type can be maybe type, and may throw if not maybe type
        else {
            // TODO: use maybe type instead
            const auto [success, bshape] = index::broadcast_shape(::nmtools::shape(arrays)...);
            using bshape_t = decltype(bshape);

            using types  = meta::type_list<const arrays_t&...>;
            using type0  = meta::at_t<types,0>;
            using i_type = meta::make_tuple_type_t<decltype(broadcast_to(meta::declval<type0>(),bshape))>;
            constexpr auto vtype = meta::template_reduce<sizeof...(arrays)-1>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value + 1;
                using init_t = meta::type_t<decltype(init)>;
                using type_i = meta::at_t<types,i>;
                // can't reference local binding on clang, use declval
                using b_type = decltype(broadcast_to(meta::declval<type_i>(),meta::declval<bshape_t>()));
                using r_type = meta::append_type_t<init_t,b_type>;
                return meta::as_value_v<r_type>;
            }, meta::as_value_v<i_type>);
            using result_t = meta::type_t<decltype(vtype)>;
            nmtools_assert_prepare_type (return_t, result_t);
            nmtools_assert (success, "cannot broadcast arrays together", return_t);

            return return_t{result_t{broadcast_to(arrays,bshape)...}};
        }
    } // broadcast_arrays
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP