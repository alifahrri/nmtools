#ifndef NMTOOLS_ARRAY_INDEX_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_INDEX_MOVEAXIS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/array/index/argsort.hpp"

#include "nmtools/utl/maybe.hpp"

namespace nmtools::index
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
        // TODO: consider to take dim instead of shape

        using result_t = meta::resolve_optype_t<moveaxis_to_transpose_t, shape_t, source_t, destination_t>;

        if constexpr ((! meta::is_constant_index_array_v<result_t>) && (! meta::is_fail_v<result_t>)) {
            using return_t = utl::maybe<result_t>;

            auto dim = [&](){
                if constexpr (meta::is_constant_index_array_v<shape_t>) {
                    return meta::ct_v<meta::len_v<shape_t>>;
                } else {
                    return len(shape);
                }
            }();

            auto order = result_t {};
            if constexpr (meta::is_resizeable_v<result_t>) {
                order.resize(dim);
            }

            auto as_array = [](const auto& a){
                using a_t = meta::remove_cvref_t<decltype(a)>;
                if constexpr (meta::is_constant_index_v<a_t>) {
                    return nmtools_tuple{a};
                } else if constexpr (meta::is_index_v<a_t>) {
                    return nmtools_array{a};
                } else if constexpr (meta::is_constant_index_array_v<a_t>) {
                    return a_t {};
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
            const auto src = index::normalize_axis(as_array(source), dim);
            const auto dst = index::normalize_axis(as_array(destination), dim);
            // sort by destination, arg shall be maybe type because normalize axis return maybe type
            const auto arg = index::argsort(dst);

            // auto ret = return_t {};
            auto valid = true;

            if (!src || !dst) {
                valid = false;
                // NOTE: early return to allow constexpr
                // return return_t{meta::Nothing};
                return return_t{};
            } else if (len(*src) != len(*dst)) {
                valid = false;
                // NOTE: early return to allow constexpr
                // return return_t{meta::Nothing};
                return return_t{};
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
                // ret = order;
                return return_t(order);
            } else {
                // ret = meta::Nothing;
                // return return_t(meta::Nothing);
                return return_t{};
            }

            // return ret;
        } else {
            // NOTE: quick hack so no need to modify caller to handle non maybe type
            using return_t = meta::make_maybe_type_t<result_t>;
            static_assert( !meta::is_fail_v<result_t>
                , "unsupported moveaxis_to_transpose"
            );
            return return_t {result_t{}};
        }
    } // moveaxis_to_transpose
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct MOVEAXIS_TO_TRANSPOSE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct MOVEAXIS_TO_TRANSPOSE_INVALID : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename source_t, typename destination_t>
    struct resolve_optype<
        void, index::moveaxis_to_transpose_t, shape_t, source_t, destination_t
    >
    {
        // simply follow the shape but make it unsigned
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto valid_src_dst =
                   (is_index_array_v<source_t> && is_index_array_v<destination_t>)
                || (is_index_v<source_t> && is_index_v<destination_t>);
            if constexpr (is_constant_index_array_v<shape_t> && (is_constant_index_v<source_t> || is_constant_index_array_v<source_t>) && (is_constant_index_v<destination_t> || is_constant_index_array_v<destination_t>)) {
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto source = to_value_v<source_t>;
                constexpr auto destination = to_value_v<destination_t>;
                constexpr auto result      = index::moveaxis_to_transpose(shape,source,destination);
                if constexpr (result.has_value()) {
                    constexpr auto axes = *result;
                    return template_reduce<nmtools::len(axes)-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        return as_value_v<append_type_t<init_type,ct<nmtools::at(axes,index+1)>>>;
                    }, as_value_v<nmtools_tuple<ct<nmtools::at(axes,0)>>>);
                } else {
                    using type = error::MOVEAXIS_TO_TRANSPOSE_INVALID<shape_t,source_t,destination_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_constant_index_array_v<shape_t> && valid_src_dst) {
                using shape_type = remove_cvref_t<decltype(to_value_v<shape_t>)>;
                using type = resolve_optype_t<index::moveaxis_to_transpose_t,shape_type,source_t,destination_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<shape_t> && valid_src_dst) {
                using index_t = get_element_type_t<shape_t>;
                using unsigned_t = make_unsigned_t<index_t>;
                using type = replace_element_type_t<transform_bounded_array_t<shape_t>,unsigned_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::MOVEAXIS_TO_TRANSPOSE_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
        static_assert( !is_void_v<type>, "nmtools internal error");
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_MOVEAXIS_HPP