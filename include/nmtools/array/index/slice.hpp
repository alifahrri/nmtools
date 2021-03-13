#ifndef NMTOOLS_ARRAY_INDEX_SLICE_HPP
#define NMTOOLS_ARRAY_INDEX_SLICE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"

#include <tuple>

namespace nmtools::index
{
    struct shape_slice_t {};
    struct slice_t {};

    template <typename shape_t, typename slice_t, typename axis_t>
    constexpr auto unpack(const shape_t& shape, const slice_t& slice, axis_t axis)
    {
        constexpr auto N = std::tuple_size_v<slice_t>;

        using return_t = std::array<int,3>;
        auto res = return_t {};

        if constexpr (N==2) {
            // here, we dont have `step` parameter specified, fill with None
            // then recurse
            res = unpack(shape, std::tuple{std::get<0>(slice), std::get<1>(slice), None},axis);
        }
        else if constexpr (N==3) {
            // we have all `start` `stop` and `step` parameter,
            // check for those parameters, for any None params, replace with appropriate value,
            // for example None start should be 0, None stop should be actual shape at current axis
            auto [start, stop, step] = slice;
            using start_t = meta::remove_cvref_t<decltype(start)>;
            using stop_t  = meta::remove_cvref_t<decltype(stop)>;
            using step_t  = meta::remove_cvref_t<decltype(step)>;
            if constexpr (is_none_v<start_t>)
                res = unpack(shape, std::tuple<size_t,decltype(stop),decltype(step)>{0,stop,step},axis);
            else if constexpr (is_none_v<stop_t>) {
                // shape at axis, to replace None stop with actual size
                auto s = at(shape,axis);
                res = unpack(shape, std::tuple<decltype(start),size_t,decltype(step)>{start,s,step},axis);
            }
            else if constexpr (is_none_v<step_t>)
                res = unpack(shape, std::tuple<decltype(start),decltype(stop),size_t>{start,stop,1},axis);
            else {
                // here all of the params, `start`, `stop`, and `step` is already converted to numbers
                // now we need to wrap around for negative params,
                auto s = at(shape,axis);
                if (start < 0)
                    start = s - start;
                if (stop < 0)
                    stop = s + stop;
                // following numpy, stop is calculated as min(stop,at(shape,i))
                stop = std::min(static_cast<int>(stop),static_cast<int>(s));
                res = {static_cast<int>(start),static_cast<int>(stop),static_cast<int>(step)};
            }
        }
        // TODO error handling here
        return res;
    } // unpack

    template <typename shape_t, typename...slices_t>
    constexpr auto shape_slice(const shape_t& shape, const slices_t&...slices)
    {
        using op_type  = meta::resolve_optype<void,shape_slice_t,shape_t,slices_t...>;
        using return_t = meta::type_t<op_type>;
        // number of integer in slices, represent indexing instead of slice
        constexpr auto N_INT = op_type::N_INT;

        auto res = return_t {};
        auto dim = len(shape) - N_INT;
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(dim);
        
        // TODO error handling
        // make sure sizeof...(slices) <= len(shape)

        auto slices_pack = std::tuple<const slices_t&...>{slices...};

        // since res and shape may have different dim,
        auto r_i = size_t{0};
        constexpr auto N_SLICES = sizeof...(slices);
        meta::template_for<N_SLICES>([&](auto i){
            auto slice = at(slices_pack, i);
            using slice_t = meta::remove_cvref_t<decltype(slice)>;
            // when slice is mixed with indexing,
            // the resulting dimension is len(shape) - N_INT
            // simply ignore if there is integer
            if constexpr (!std::is_integral_v<slice_t>) {
                auto [start, stop, step] = unpack(shape, slice, i);

                // here we already transform negative value to actual bound
                // but still need to handle negative step, for now just take abs value
                at(res,r_i++) = (stop - start) / std::abs(step);
            }
        });

        return res;
    } // shape_slice

    template <typename shape_t, typename slices_t, size_t...Is>
    constexpr auto apply_shape_slice(const shape_t& shape, const slices_t& slices, std::index_sequence<Is...>)
    {
        return shape_slice(shape, std::get<Is>(slices)...);
    } // apply_shape_slice

    template <typename shape_t, typename slices_t>
    constexpr auto apply_shape_slice(const shape_t& shape, const slices_t& slices)
    {
        constexpr auto N = std::tuple_size_v<slices_t>;
        return apply_shape_slice(shape, slices, std::make_index_sequence<N>{});
    } // apply_shape_slice

    template <typename indices_t, typename shape_t, typename...slices_t>
    constexpr auto slice(const indices_t& indices, const shape_t& shape, const slices_t&...slices)
    {
        using return_t = meta::resolve_optype_t<slice_t,indices_t,shape_t,slices_t...>;
        auto res = return_t {};
        auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(dim);
        
        auto slices_pack = std::tuple<const slices_t&...>{slices...};

        // since res and shape may have different dim,
        // also indices and shape may have different dim,
        // this variable tracks index for indices
        auto ii = size_t{0};
        // TODO: provide overloads that accepts unpacked `start`, `stop`, `step`
        constexpr auto N_SLICES = sizeof...(slices);
        meta::template_for<N_SLICES>([&](auto i){
            auto slice = at(slices_pack, i);
            using slice_t = meta::remove_cvref_t<decltype(slice)>;
            if constexpr (std::is_integral_v<slice_t>)
                at(res,i) = slice;
            else {
                auto [start, stop, step] = unpack(shape, slice, i);
                // TODO: check at(indices,i) < stop
                // here, apply inverse from shape_pack
                at(res,i) = start + (at(indices,ii++) * std::abs(step));
            }
        });

        return res;
    } // slice

    template <typename indices_t, typename shape_t, typename slices_t, size_t...Is>
    constexpr auto apply_slice(const indices_t& indices, const shape_t& shape, const slices_t& slices, std::index_sequence<Is...>)
    {
        return slice(indices, shape, std::get<Is>(slices)...);
    } // apply_slice

    template <typename indices_t, typename shape_t, typename slices_t>
    constexpr auto apply_slice(const indices_t& indices, const shape_t& shape, const slices_t& slices)
    {
        constexpr auto N = std::tuple_size_v<slices_t>;
        return apply_slice(indices,shape,slices,std::make_index_sequence<N>{});
    } // apply_slice

} // namespace nmtools::index

namespace nmtools::meta
{
    template <typename shape_t, typename...slices_t>
    struct resolve_optype<
        void, index::shape_slice_t, shape_t, slices_t...
    >
    {
        static constexpr auto N_INT = [](){
            using slices_type = std::tuple<slices_t...>;
            size_t n_int = 0;
            template_for<sizeof...(slices_t)>([&](auto idx){
                constexpr auto i = decltype(idx)::value;
                using slice_t = std::tuple_element_t<i,slices_type>;
                if constexpr(std::is_integral_v<slice_t>)
                    n_int = n_int+1;
            });
            return n_int;
        }();
        using shape_type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
        // note resize_fixed_vector doesnt work well with std::vector
        // only return resized when it shape_type is fixed
        using type = std::conditional_t<
            is_fixed_index_array_v<shape_type>,
            resize_fixed_vector_t<shape_type,sizeof...(slices_t)-N_INT>,
            shape_type
        >;
    }; // shape_slice_t

    template <typename indices_t, typename shape_t, typename...slices_t>
    struct resolve_optype<
        void, index::slice_t, indices_t, shape_t, slices_t...
    >
    {
        using type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
    }; // slice_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SLICE_HPP