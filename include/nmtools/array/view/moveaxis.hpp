#ifndef NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP

#include "nmtools/array/index/argsort.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view::detail
{
    struct moveaxis_to_transpose_t {};

    /**
     * @brief Transform moveaxis arguments to transpose arguments
     * 
     * @tparam shape_t 
     * @tparam source_t 
     * @tparam destination_t 
     * @param shape         the shape of src array
     * @param source        moveaxis' argument, maybe index or index array
     * @param destination   moveaxis' argument, maybe index or index array
     * @return constexpr auto 
     */
    template <typename shape_t, typename source_t, typename destination_t>
    constexpr auto moveaxis_to_transpose(const shape_t& shape, const source_t& source, const destination_t& destination)
    {
        using result_t = meta::resolve_optype_t<moveaxis_to_transpose_t, shape_t, source_t, destination_t>;
        using return_t = meta::make_maybe_type_t<result_t>;
        static_assert( !meta::is_fail_v<result_t>
            , "unsupported moveaxis_to_transpose"
        );

        auto dim = len(shape);

        auto order = result_t {};
        if constexpr (meta::is_resizeable_v<result_t>) {
            order.resize(dim);
        }

        auto as_array = [](const auto& a){
            using a_t = meta::remove_cvref_t<decltype(a)>;
            if constexpr (meta::is_index_v<a_t>) {
                using type = meta::make_array_type_t<a_t,1>;
                return type{a};
            } else {
                // TODO: check if we can use index::ref
                // a maybe bounded index
                using type = meta::transform_bounded_array_t<a_t>;
                auto res   = type{};
                auto dim   = len(a);
                if constexpr (meta::is_resizeable_v<type>) {
                    res.resize(dim);
                }
                for (size_t i=0; i<(size_t)dim; i++)
                    at(res,i) = at(a,i);
                return res;
            }
        };
        auto src = index::normalize_axis(as_array(source), dim);
        auto dst = index::normalize_axis(as_array(destination), dim);
        // sort by destination, arg shall be maybe type because normalize axis return maybe type
        auto arg = index::argsort(dst);

        auto ret = return_t {};
        auto valid = true;

        if (!src || !dst) {
            valid = false;
        } else if (len(*src) != len(*dst)) {
            valid = false;
        }

        auto in = [](auto v, const auto& array) {
            auto found = false;
            for (size_t i=0; (!found && i<len(array)); i++) {
                if (v==at(array,i)) {
                    found = true;
                }
            }
            return found;
        };

        // numpy: order = [n for n in range(a.ndim) if n not in source]
        // fill-up 0,1,2... first
        auto ii = 0;
        for (size_t i=0; i<(size_t)dim; i++) {
            if (!in(i,*src)) {
                at(order,ii++) = i;
            }
        }

        // simulate insert with shift
        auto insert = [](auto pos, auto val, auto& array){
            // shift right all element at pos+
            for (size_t i=(len(array)-1); i>pos; i--) {
                at(array,i) = at(array,i-1);
            }
            at(array,pos) = val;
        };

        // numpy:
        // for dest, src in sorted(zip(destination, source)):
        //      order.insert(dest, src)
        for (size_t index=0; valid && (index<len(*dst)); index++) {
            auto i  = at(*arg,index);
            auto di = at(*dst,i);
            auto si = at(*src,i);
            insert(di,si,order);
        }

        if (valid) {
            ret = order;
        } else {
            ret = meta::Nothing;
        }

        return ret;
    } // moveaxis_to_transpose
} // namespace nmtools::view::detail

namespace nmtools::meta
{
    namespace error
    {
        struct MOVEAXIS_TO_TRANSPOSE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename source_t, typename destination_t>
    struct resolve_optype<
        void, view::detail::moveaxis_to_transpose_t, shape_t, source_t, destination_t
    >
    {
        // simply follow the shape but make it unsigned
        static constexpr auto vtype = [](){
            constexpr auto valid_args =
                   (is_index_array_v<source_t> && is_index_array_v<destination_t>)
                || (is_index_v<source_t> && is_index_v<destination_t>);
            if constexpr (is_index_array_v<shape_t> && valid_args) {
                using index_t = get_element_type_t<shape_t>;
                using unsigned_t = make_unsigned_t<index_t>;
                using type = replace_element_type_t<transform_bounded_array_t<shape_t>,unsigned_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::MOVEAXIS_TO_TRANSPOSE_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

namespace nmtools::view
{
    /**
     * @brief Move axes of an array to a new postions.
     * 
     * Under the hood, this creates transpose view.
     * 
     * @tparam array_t 
     * @tparam source_t 
     * @tparam destination_t 
     * @param array         input array
     * @param source        original postions of axes to be moved
     * @param destination   desired position for each original axes
     * @return constexpr auto 
     */
    template <typename array_t, typename source_t, typename destination_t>
    constexpr auto moveaxis(const array_t& array, const source_t& source, const destination_t& destination)
    {
        auto shape_ = shape(array);
        auto order  = detail::moveaxis_to_transpose(shape_,source,destination);
        // order should be maybe type
        using result_t = meta::remove_cvref_t<decltype(transpose(array,*order))>;
        nmtools_assert_prepare_type( return_t, result_t );
        nmtools_assert( order, "unsupported moveaxis arguments", return_t );

        return return_t{transpose(array,*order)};
    } // moveaxis
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP