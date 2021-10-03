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

    // TODO: remove
    template <typename shape_t, typename slice_t, typename axis_t>
    constexpr auto unpack(const shape_t& shape, const slice_t& slice, axis_t axis)
    {
        constexpr auto N = std::tuple_size_v<slice_t>;

        // TODO (wrap std metafunctions): provide meta::make_array_t<...>;
        using return_t = std::array<int,3>;
        auto res = return_t {};

        if constexpr (N==2) {
            // here, we dont have `step` parameter specified, fill with None
            // then recurse
            // TODO (wrap std metafunctions): create meta::make_tuple_t<...>;
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
            if constexpr (is_none_v<start_t>) {
                // TODO (wrap std metafunctions): create meta::make_tuple_t<...>;
                res = unpack(shape, std::tuple<size_t,decltype(stop),decltype(step)>{0,stop,step},axis);
            }
            else if constexpr (is_none_v<stop_t>) {
                // shape at axis, to replace None stop with actual size
                auto s = at(shape,axis);
                // TODO (wrap std metafunctions): create meta::make_tuple_t<...>;
                res = unpack(shape, std::tuple<decltype(start),size_t,decltype(step)>{start,s,step},axis);
            }
            else if constexpr (is_none_v<step_t>) {
                // TODO (wrap std metafunctions): create meta::make_tuple_t<...>;
                res = unpack(shape, std::tuple<decltype(start),decltype(stop),size_t>{start,stop,1},axis);
            } else {
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
        using return_t  = meta::resolve_optype_t<shape_slice_t,shape_t,slices_t...>;
        using size_type = meta::get_element_type_t<return_t>;
        // number of integer in slices, represent indexing instead of slice
        constexpr auto N_INT = (static_cast<size_t>(meta::is_index_v<slices_t>) + ...);

        // computes the number of elipsis provided in slices_t...
        // note that the only valid number of elipsis should be either 0 or 1
        constexpr auto NUM_ELIPSIS = (static_cast<size_t>(is_elipsis_v<slices_t>) + ...);
        static_assert( (NUM_ELIPSIS <= 1)
            , "only exactly zero or one elipsis are allowed"
        );

        auto res = return_t {};
        // Elipsis doesn't contribute to dimension reduction.
        // Not all constexpr branches are using dim
        [[maybe_unused]] auto dim = len(shape) - N_INT;
        if constexpr (meta::is_resizeable_v<return_t>) {
            res.resize(dim);
        }
        
        // TODO error handling
        // make sure sizeof...(slices) <= len(shape)

        auto slices_pack = std::tuple<const slices_t&...>{slices...};

        // since res and shape may have different dim,
        // this var is to keep track of the active result index
        auto r_i = size_t{0};
        // to keep track of the active shape index,
        // note that the active shape index may not be the same as
        // i (index of slices) because of elipsis
        auto s_i = size_t{0};
        constexpr auto N_SLICES = sizeof...(slices);
        meta::template_for<N_SLICES>([&](auto i){
            auto slice = at(slices_pack, i);
            // we set si here to avoid gcc 8 internal error
            // note that we also explicit using size_t here
            // can't infer type (or using size_type ) :|
            // size_type si = at(shape,i);
            size_t si = at(shape,s_i);
            using slice_t = meta::remove_cvref_t<decltype(slice)>;

            // helper lambda to decompose start stop and step
            [[maybe_unused]] auto decompose = [&](auto slice){
                // assume slice has tuple_size
                // TODO (wrap std metafunctions): use meta::len_v
                constexpr auto NS = std::tuple_size_v<decltype(slice)>;
                if constexpr (NS==2) {
                    auto [start, stop] = slice;
                    // TODO (wrap std metafunctions): create meta::make_tuple_t<...>;
                    return std::tuple{start,stop,None};
                }
                // return as it is to keep dtype
                else if constexpr (NS==3) {
                    return slice;
                }
            };

            // when we found elipsis,
            // fill up res with ":" aka tuple{None,None}
            // which is simply copy shape at the corresponding axis
            if constexpr (is_elipsis_v<slice_t>) {
                // elipsis takes src dim, not dst dim
                auto dim = len(shape);
                // number of shape to be filled (by elipsis):
                auto n = (dim-(N_SLICES-1));
                for (size_t j=0; j<n; j++) {
                    at(res,r_i++) = at(shape,j+s_i);
                }
                // must also increment active shape index
                // to properly assign next slice to correct axis
                s_i += (n-1);
            }
            // when slice is mixed with indexing,
            // the resulting dimension is len(shape) - N_INT
            // simply ignore if there is integer
            else if constexpr (!meta::is_index_v<slice_t>) {
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

                /**
                 * @brief Compute the allowed range for this axis/slice, independent to the step,
                 * should handle various case, e.g. None, postive, negative start & stop
                 * 
                 */
                auto compute_range = [&]([[maybe_unused]] auto start, auto stop_, [[maybe_unused]] auto step_) -> size_type {
                    // cant capture start, stop, step :|
                    // to avoid clang complaining about reference to local bindings

                    // following numpy, stop is actually max(stop,shape_i)
                    [[maybe_unused]] auto stop = [&](){
                        if constexpr (is_none_v<stop_t>)
                            return si;
                        else {
                            using stop_type = meta::promote_index_t<stop_t,meta::remove_cvref_t<decltype(si)>>;
                            return static_cast<stop_type>(stop_) < static_cast<stop_type>(si) ?
                                static_cast<stop_type>(stop_) : static_cast<stop_type>(si);
                        }
                    }();

                    // workaround to ambiguous call to std::abs, mostly because need to refactor avoiding
                    // gcc 8 internal compiler error :|
                    // gcc 8 no longer supported, maybe cleanup this code
                    [[maybe_unused]] auto abs_ = [](auto v) { return v < 0 ? -v : v; };
                    // both start and stop is none, simply returh shape for this axis
                    if constexpr (is_none_v<start_t> && is_none_v<stop_t>) {
                        return si;
                    }
                    // need start + 1 for such following case: 2::-?
                    // for such case, allowed indices should be (0,1,2) (range of 3) hence start + 1
                    else if constexpr (meta::is_index_v<start_t> && is_none_v<stop_t> && meta::is_index_v<step_t>) {
                        return (step_ < 0 && start >= 0) ? start + 1 : si - start;
                    }
                    else if constexpr (meta::is_index_v<start_t> && is_none_v<stop_t>) {
                        return si - start;
                    }
                    // start is none, a.k.a. zero
                    else if constexpr (is_none_v<start_t> && meta::is_index_v<stop_t>) {
                        return (stop_ < 0 ? (si + stop_) : stop);
                    }
                    else /* if constexpr (meta::is_index_v<start_t> && meta::is_index_v<stop_t>) */ {
                        // note that here we use "stop" instead of "stop_",
                        // also note that stop is already normalized
                        if ((stop < 0) && (start < 0)) {
                            return (si - abs_(stop)) - (si - abs_(start));
                        } else if ((stop < 0) && (start >= 0)) {
                            // sample case
                            // a[0:-1,...] with shape(a) = (2,3,2)
                            return (si - abs_(stop)) - start;
                        } else if ((stop >= 0) && (start < 0)) {
                            return (stop - (si - abs_(start)));
                        } else /* if ((stop >= 0) && (start >= 0)) */ {
                            return stop - start;
                        }
                    }
                };

                auto s = compute_range(start_,stop_,step_);

                auto step = []([[maybe_unused]] auto step_){
                    // NOTE: step_ is passed instead of captured to avoid clang error
                    if constexpr (is_none_v<step_t>)
                        return 1ul;
                    else if constexpr (std::is_unsigned_v<step_t>)
                        return step_;
                    else return std::abs(step_);
                }(step_);

                // finally the resulting shape for corresponding indices
                // is simply the range divided by the step
                at(res,r_i++) = static_cast<size_type>(ceil(static_cast<float>(s) / step));
            } else /* if constexpr (meta::is_index_v<slice_t>) */ {
                // only reduce the dimension,
                // doen't contributes to shape computation
            }
            // increment the active shape index here
            // to make sure that it handled all the case (elipsis,tuple,integral).
            // note that elipsis may cause both active shape index and active result index
            // to be incremented.
            s_i++;
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
        using index_t  = meta::remove_cvref_t<meta::get_element_type_t<return_t>>;
        auto res = return_t {};
        auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(dim);
        
        auto slices_pack = std::tuple<const slices_t&...>{slices...};

        // since res and shape may have different dim,
        // also indices and shape may have different dim,
        // this variable tracks index for indices
        auto i_i = size_t{0};
        // to track active result index
        auto r_i = size_t{0};
        // to track active shape index
        auto s_i = size_t{0};
        // TODO: provide overloads that accepts unpacked `start`, `stop`, `step`
        constexpr auto N_SLICES = sizeof...(slices);
        auto abs_ = [](auto v) { return v < 0 ? -v : v; };
        meta::template_for<N_SLICES>([&](auto i){
            auto slice = at(slices_pack, i);
            // si may not be used in all constexpr branch
            [[maybe_unused]] size_t si  = at(shape,s_i);
            using slice_t = meta::remove_cvref_t<decltype(slice)>;
            if constexpr (meta::is_index_v<slice_t>) {
                if constexpr (meta::is_signed_v<slice_t>) {
                    at(res,r_i) = (slice < 0 ? si - abs_(slice) : slice);
                } else {
                    at(res,r_i) = slice;
                }
            } else if constexpr (is_elipsis_v<slice_t>) {
                auto n = (dim-(N_SLICES-1));
                for (size_t j=0; j<n; j++) {
                    // we're on elipsis, active shape index may also shifted
                    auto index = at(indices,i_i+j);
                    using index_t = meta::remove_cvref_t<decltype(index)>;
                    if constexpr (meta::is_signed_v<index_t>) {
                        auto si    = at(shape,s_i+j);
                        at(res,r_i+j) = (index < 0 ? si - abs_(index) : index);
                    } else {
                        at(res,r_i+j) = index;
                    }
                }
                // NOTE: r_i and s_i will be incremented by 1
                // at the end of template_for loop,
                // effectively increment for any case of slice_t
                // (index, elpsis, tuple).
                // while i_i should only be incremented
                // for elipsis and tuple case of slice_t.
                // so here r_i and s_i are incremented by (n-1)
                // while i_i is incremented by n.
                r_i += (n-1);
                s_i += (n-1);
                i_i += (n);
            } else {
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
                auto index = [&](auto start_, auto stop_, auto step_) -> index_t {
                    [[maybe_unused]] auto start = start_; // just alias
                    // following numpy, stop is actually (stop,shape_i)
                    [[maybe_unused]] auto stop = [&](){
                        if constexpr (is_none_v<stop_t>)
                            return si;
                        // clip value, keep sign
                        else {
                            using common_t = meta::promote_index_t<decltype(stop_),decltype(si)>;
                            auto s = static_cast<common_t>(stop_) < static_cast<common_t>(si)
                                        ? static_cast<common_t>(stop_) : static_cast<common_t>(si);
                                 s = static_cast<common_t>(s) > static_cast<common_t>(-si)
                                        ? static_cast<common_t>(s) : static_cast<common_t>(-si);
                            return s;
                        }
                    }();
                    // alias
                    [[maybe_unused]] auto step = step_;
                    // (1) simplest case: all is none
                    if constexpr (is_none_v<start_t> && is_none_v<stop_t> && is_none_v<step_t>) {
                        // example case:
                        // a[:]
                        auto index = at(indices,i_i);
                        return index;
                    }
                    // (2) only start is integer
                    else if constexpr (meta::is_index_v<start_t> && is_none_v<stop_t> && is_none_v<step_t>) {
                        // example case:
                        // a[0::]
                        // a[-1::]
                        auto index = (start >= 0 ? start : stop - start) + at(indices,i_i);
                        return index;
                        // return {start >= 0 ? start : stop - start, 1};
                    }
                    // (3) start and stop is integer, can be positive or negative
                    else if constexpr (meta::is_index_v<start_t> && meta::is_index_v<stop_t> && is_none_v<step_t>) {
                        // example case:
                        // a[0:2:]
                        // a[-2:3:]
                        // a[0:-1:]
                        // a[-2:-1:]
                        auto s = index_t{0};
                        if (start >= 0 && stop > 0)
                            s = start;
                        else if (start < 0 && stop > 0)
                            s = stop + start;
                        else if (start >= 0 && stop < 0)
                            s = start;
                        else /* if (start < 0 && stop < 0) */
                            s = si + start;
                        auto index = s + at(indices,i_i);
                        return index;
                    }
                    // (4) all three is integer, can be positive or negative
                    else if constexpr (meta::is_index_v<start_t> && meta::is_index_v<stop_t> && meta::is_index_v<step_t>) {
                        auto _start = index_t{0};
                        auto _step  = index_t{0};
                        // step is negative:
                        if /**/ (start >= 0 && stop > 0 && step < 0) {
                            _start = stop - 1;
                            _step  = step;
                            // return {stop - 1, step};
                        }
                        else if (start < 0 && stop > 0 && step < 0) {
                            _start = stop + start;
                            _step  = step;
                            // return {stop+start, step};
                        } else if (start >= 0 && stop < 0 && step < 0) {
                            _start = start;
                            _step  = step;
                            // return {start, step};
                        } else if (start < 0 && stop < 0 && step < 0) {
                            _start = si + start - 1;
                            _step  = step;
                            // return {si+start-1, step};
                        }
                        // step is positive:
                        else if (start >= 0 && stop > 0 && step > 0) {
                            _start = start;
                            _step  = step;
                            // return {start, step};
                        } else if (start < 0 && stop > 0 && step > 0) {
                            _start = stop + start;
                            _step  = step;
                            // return {stop+start, step};
                        } else if (start >= 0 && stop < 0 && step > 0) {
                            _start = start;
                            _step  = step;
                            // return {start, step};
                        } else /* if (start < 0 && stop < 0 && step > 0) */ {
                            _start = si + start;
                            _step  = step;
                            // return {si+start, step};
                        }
                        auto index = _start + at(indices,i_i) * _step;
                        return index;
                    } else if constexpr (is_none_v<start_t> && meta::is_index_v<stop_t> && is_none_v<step_t>) {
                        auto index = at(indices,i_i);
                        return index;
                        // return {0,1};
                    } else if constexpr (is_none_v<start_t> && meta::is_index_v<stop_t> && meta::is_index_v<step_t>) {
                        auto _start = index_t{0};
                        auto _step  = index_t{0};
                        if (stop > 0 && step > 0) {
                            _start = 0;
                            _step  = step;
                            // return {0,step};
                        } else if (stop > 0 && step < 0) {
                            _start = si;
                            _step  = step;
                            // return {si,step};
                        } else if (stop < 0 && step > 0) {
                            _start = 0;
                            _step  = step;
                            // return {0,step};
                        } else /* if (stop > 0 && step > 0) */ {
                            _start = 0;
                            _step  = step;
                            // return {0,step};
                        }
                        auto index = _start + at(indices,i_i) * _step;
                        return index;
                    }
                    else if constexpr (is_none_v<start_t> && is_none_v<stop_t> && meta::is_index_v<step_t>) {
                        // example case:
                        // a[::-1]
                        auto _start = index_t{0};
                        auto _step  = index_t{0};
                        if (step < 0) {
                            _start = si - 1;
                            _step  = step;
                            // return {si-1,step};
                        } else {
                            _start = 0;
                            _step  = step;
                            // return {0,step};
                        }
                        auto index = _start + at(indices,i_i) * _step;
                        return index;
                    }
                    else /* if constexpr (meta::is_index_v<start_t> && is_none_v<stop_t> && meta::is_index_v<step_t>) */ {
                        auto _start = index_t{0};
                        auto _step  = index_t{0};
                        if (start >= 0 && step > 0) {
                            _start = start;
                            _step  = step;
                            // return {start, step};
                        } else if (start >= 0 && step < 0) {
                            _start = start;
                            _step  = step;
                            // return {start, step};
                        } else if (start < 0 && step > 0) {
                            _start = si + start;
                            _step  = step;
                            // return {si+start,step};
                        } else /* if (start < 0 && step < 0) */ {
                            _start = start;
                            _step  = step;
                            // return {start, step};
                        }
                        auto index = _start + at(indices,i_i) * _step;
                        return index;
                    }
                }(start_,stop_,step_);

                at(res,r_i) = index;
                i_i++;

                // TODO: check at(indices,i) < stop
                // at(res,r_i) = s + at(indices,i_i++) * step;
            }
            // note that the resulting dimension 
            // will always be the same as src dimension
            r_i++;
            s_i++;
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
        static constexpr auto vtype = [](){
            constexpr auto n_integer = ((static_cast<size_t>(meta::is_index_v<slices_t>)) + ...);
            if constexpr (is_fixed_index_array_v<shape_t>) {
                constexpr auto dim = fixed_index_array_size_v<shape_t> - n_integer;
                using shape_type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
                using type = resize_fixed_index_array_t<shape_type,dim>;
                return as_value_v<type>;
            } else {
                using type = shape_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
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