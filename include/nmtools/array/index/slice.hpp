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
        using op_type   = meta::resolve_optype<void,shape_slice_t,shape_t,slices_t...>;
        using return_t  = meta::type_t<op_type>;
        using size_type = meta::get_element_type_t<return_t>;
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
        // this is workaround for gcc 8, some how inferring 
        meta::template_for<N_SLICES>([&](auto i){
            auto slice = at(slices_pack, i);
            // we set si here to avoid gcc 8 internal error
            // note that we also explicit using size_t here
            // can't infer type (or using size_type ) :|
            size_t si = at(shape,i);
            // size_type si = at(shape,i);
            using slice_t = meta::remove_cvref_t<decltype(slice)>;

            // helper lambda to decompose start stop and step
            auto decompose = [&](auto slice){
                // assume slice has tuple_size
                constexpr auto NS = std::tuple_size_v<decltype(slice)>;
                if constexpr (NS==2) {
                    auto [start, stop] = slice;
                    return std::tuple{start,stop,None};
                }
                // return as it is to keep dtype
                else if constexpr (NS==3)
                    return slice;
            };

            // when slice is mixed with indexing,
            // the resulting dimension is len(shape) - N_INT
            // simply ignore if there is integer
            if constexpr (!std::is_integral_v<slice_t>) {
                // using IILE here triggers gcc 8 internal compiler error: 
                // in enclosing_instantiation_of, at cp/pt.c:13299 (works fine on gcc 9)
                // https://godbolt.org/z/7vcvPG8c1
                // move outside to avoid this problem
                // auto [start_, stop_, step_] = [&](){
                //     // assume slice has tuple_size
                //     constexpr auto NS = std::tuple_size_v<decltype(slice)>;
                //     if constexpr (NS==2) {
                //         auto [start, stop] = slice;
                //         return std::tuple{start,stop,None};
                //     }
                //     // return as it is to keep dtype
                //     else if constexpr (NS==3)
                //         return slice;
                // }();
                auto [start_,stop_,step_] = decompose(slice);
                using start_t = meta::remove_cvref_t<decltype(start_)>;
                using stop_t  = meta::remove_cvref_t<decltype(stop_)>;
                using step_t  = meta::remove_cvref_t<decltype(step_)>;

                // some tricky case:
                // shape of the following is the same, assume shape = (4,2)
                // (1) a[:,1::2]
                // (2) a[:,1::]
                // for now use ceil to handle such case
                // without ceiling, (1) results in 0 when it should be 1
                // another tricky case: assume shape=(4,2)
                // (3) a[3::-2]
                // (4) a[::-2]
                // note that (3) and (4) should be the same
                // another case to consider is: (not the same result)
                // (5) a[2::-2]
                // (6) a[1::-2]

                using std::ceil;
                using std::floor;

                // here we compute the allowed range, regardless of the step,
                // should handle various case, e.g. None, positive, negative start & stop
                auto s = [&](auto start, auto stop_, auto step_) -> size_type {
                    // cant capture start, stop, step :|
                    // to avoid clang complaining about reference to local bindings

                    // following numpy, stop is actually (stop,shape_i)
                    auto stop = [&](){
                        if constexpr (is_none_v<stop_t>)
                            return si;
                        // this triggers gcc 8 internal compiler error: in tsubst_copy, at cp/pt.c:15387
                        // use ternary op instead, and move 'at' outside
                        // else return std::min(static_cast<int>(stop_),static_cast<int>(at(shape,i)));
                        else return stop_ < si ? stop_ : si;
                    }();
                    // workaround to ambiguous call to std::abs, mostly because need to refactor avoiding
                    // gcc 8 internal compiler error :|
                    auto abs_ = [](auto v) { return v < 0 ? -v : v; };
                    // (1)
                    if constexpr (std::is_unsigned_v<start_t> && std::is_unsigned_v<stop_t>)
                        return stop - start;
                    // (2)
                    else if constexpr (std::is_signed_v<start_t> && std::is_signed_v<stop_t>) {
                        if (stop < 0 && start < 0)
                            return (si - abs_(stop)) - (si - abs_(start));
                        else if (stop < 0)
                            return (si - abs_(stop)) - start;
                        else
                            return stop - start;
                    }
                    // (3)
                    else if constexpr (std::is_unsigned_v<start_t> && std::is_signed_v<stop_t>)
                        return (si - abs_(stop)) - start;
                    // (4)
                    else if constexpr (is_none_v<start_t> && std::is_unsigned_v<stop_t>)
                        return stop;
                    // (5)
                    else if constexpr (is_none_v<start_t> && std::is_signed_v<stop_t>)
                        return stop < 0 ? (si - abs_(stop)) : stop;
                    // (6)
                    else if constexpr (is_none_v<start_t> && is_none_v<stop_t>)
                        return si;
                    // (7)
                    else if constexpr (std::is_integral_v<start_t> && is_none_v<stop_t> && is_none_v<step_t>)
                        return si - start;
                    // (8) need start + 1 for such following case: 2::-?
                    //     for such case, allowed indices should be (0,1,2) (range of 3) hence start + 1
                    else if constexpr (std::is_integral_v<start_t> && is_none_v<stop_t> && std::is_integral_v<step_t>)
                        return step_ < 0 && start >= 0 ? start + 1 : si - start;
                }(start_,stop_,step_);

                auto step = [](auto step_){
                    if constexpr (is_none_v<step_t>)
                        return 1ul;
                    else if constexpr (std::is_unsigned_v<step_t>)
                        return step_;
                    else return std::abs(step_);
                }(step_);

                // finally the resulting shape for corresponding indices
                // is simply the range divided by the step
                at(res,r_i++) = static_cast<size_type>(ceil(static_cast<float>(s) / step));
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
        using index_t  = meta::get_element_type_t<return_t>;
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
            // avoid gcc 8 internal compiler error
            size_t si = at(shape,i);
            using slice_t = meta::remove_cvref_t<decltype(slice)>;
            if constexpr (std::is_integral_v<slice_t>)
                at(res,i) = slice;
            else {
                auto [start_, stop_, step_] = [&](){
                    // assume slice has tuple_size
                    constexpr auto NS = std::tuple_size_v<decltype(slice)>;
                    if constexpr (NS==2) {
                        auto [start, stop] = slice;
                        return std::tuple{start,stop,None};
                    }
                    // return as it is to keep dtype
                    else if constexpr (NS==3)
                        return slice;
                }();
                using start_t = meta::remove_cvref_t<decltype(start_)>;
                using stop_t  = meta::remove_cvref_t<decltype(stop_)>;
                using step_t  = meta::remove_cvref_t<decltype(step_)>;

                // some tricky case: assume shape=(4,2)
                // (1) a[::-2,1::-2]
                // (2) a[::-2,1::2]
                // (1) and (2) is actually the same 
                // TODO: exploit the type information, such as signed-/unsigned-ness
                // to perform conditional compilation

                // here we compute the start index step, regardless of the dst index
                // should handle various case, e.g. None, positive, negative start & stop
                // also assume indices is properly generated
                auto [s, step] = [&](auto start_, auto stop_, auto step_) -> std::tuple<index_t,index_t> {
                    auto start = start_; // just alias
                    // following numpy, stop is actually (stop,shape_i)
                    auto stop = [&](){
                        if constexpr (is_none_v<stop_t>)
                            return si;
                        // clip value, keep sign
                        else {
                            auto s = stop_ < si ? stop_ : si;
                                 s = s > -si ? s : -si;
                            return s;
                        }
                    }();
                    // alias
                    auto step = step_;
                    // (1) simplest case: all is none
                    if constexpr (is_none_v<start_t> && is_none_v<stop_t> && is_none_v<step_t>)
                        return {0,1};
                    // (2) only start is integer
                    else if constexpr (std::is_integral_v<start_t> && is_none_v<stop_t> && is_none_v<step_t>)
                        return {start >= 0 ? start : stop - start, 1};
                    // (3) start and stop is integer, can be positive or negative
                    else if constexpr (std::is_integral_v<start_t> && std::is_integral_v<stop_t> && is_none_v<step_t>) {
                        if (start >= 0 && stop > 0)
                            return {start, 1};
                        else if (start < 0 && stop > 0)
                            return {stop+start,1};
                        else if (start >= 0 && stop < 0)
                            return {start, 1};
                        else /* if (start < 0 && stop < 0) */
                            return {si+start, 1};
                    }
                    // (4) all three is integer, can be positive or negative
                    else if constexpr (std::is_integral_v<start_t> && std::is_integral_v<stop_t> && std::is_integral_v<step_t>) {
                        // step is negative:
                        if /**/ (start >= 0 && stop > 0 && step < 0)
                            return {stop - 1, step};
                        else if (start < 0 && stop > 0 && step < 0)
                            return {stop+start, step};
                        else if (start >= 0 && stop < 0 && step < 0)
                            return {start, step};
                        else if (start < 0 && stop < 0 && step < 0)
                            return {si+start-1, step};

                        // step is positive:
                        else if (start >= 0 && stop > 0 && step > 0)
                            return {start, step};
                        else if (start < 0 && stop > 0 && step > 0)
                            return {stop+start, step};
                        else if (start >= 0 && stop < 0 && step > 0)
                            return {start, step};
                        else /* if (start < 0 && stop < 0 && step > 0) */
                            return {si+start, step};
                    }
                    else if constexpr (is_none_v<start_t> && std::is_integral_v<stop_t> && is_none_v<step_t>)
                        return {0,1};
                    else if constexpr (is_none_v<start_t> && std::is_integral_v<stop_t> && std::is_integral_v<step_t>) {
                        if (stop > 0 && step > 0)
                            return {0,step};
                        else if (stop > 0 && step < 0)
                            return {si,step};
                        else if (stop < 0 && step > 0)
                            return {0,step};
                        else /* if (stop > 0 && step > 0) */
                            return {0,step};
                    }
                    else if constexpr (is_none_v<start_t> && is_none_v<stop_t> && std::is_integral_v<step_t>) {
                        if (step < 0)
                            return {si-1,step};
                        else
                            return {0,step};
                    }
                    else /* if constexpr (std::is_integral_v<start_t> && is_none_v<stop_t> && std::is_integral_v<step_t>) */ {
                        if (start >= 0 && step > 0)
                            return {start, step};
                        else if (start >= 0 && step < 0)
                            return {start, step};
                        else if (start < 0 && step > 0)
                            return {si+start,step};
                        else /* if (start < 0 && step < 0) */
                            return {start, step};
                    }
                }(start_,stop_,step_);

                // TODO: check at(indices,i) < stop
                at(res,i) = s + at(indices,ii++) * step;
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