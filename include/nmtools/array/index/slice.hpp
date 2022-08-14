#ifndef NMTOOLS_ARRAY_INDEX_DYNAMIC_SLICE_HPP
#define NMTOOLS_ARRAY_INDEX_DYNAMIC_SLICE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/math.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/utility/flatten_either.hpp"

namespace nmtools::index
{
    /**
     * @brief slicing on dynamic dimension
     * 
     */
    struct shape_dynamic_slice_t {};
    struct dynamic_slice_t {};

    /**
     * @brief Compute range (number of dim at specific axis) ignoring the value of step
     * 
     * @tparam si_t 
     * @tparam start_t 
     * @tparam stop_t 
     * @tparam step_t 
     * @param si        shape at i-th axis
     * @param start     start
     * @param stop_     stop
     * @param step_     step
     * @return constexpr auto 
     */
    template <typename si_t, typename start_t, typename stop_t, typename step_t>
    constexpr inline auto compute_range(si_t si, [[maybe_unused]] start_t start, stop_t stop_, [[maybe_unused]] step_t step_) // -> size_type
    {
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

        // workaround to ambiguous call to std abs, mostly because need to refactor avoiding
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
            // to make sure we have consistent return types
            using result_t = meta::promote_index_t<start_t,stop_t>;
            // note that here we use "stop" instead of "stop_",
            // also note that stop is already normalized
            if ((stop < 0) && (start < 0)) {
                return static_cast<result_t>((si - abs_(stop)) - (si - abs_(start)));
            } else if ((stop < 0) && (start >= 0)) {
                // sample case
                // a[0:-1,...] with shape(a) = (2,3,2)
                return static_cast<result_t>((si - abs_(stop)) - start);
            } else if ((stop >= 0) && (start < 0)) {
                return static_cast<result_t>(stop - (si - abs_(start)));
            } else /* if ((stop >= 0) && (start >= 0)) */ {
                // the following should works for both negative and positive step
                if ((result_t)stop > (result_t)start) {
                    return static_cast<result_t>(stop - start);
                } else {
                    return static_cast<result_t>(start - stop);
                }
            }
        }
    }

    template <typename step_t>
    constexpr inline auto compute_step([[maybe_unused]] step_t step_)
    {
        // NOTE: step_ is passed instead of captured to avoid clang error
        if constexpr (is_none_v<step_t>)
            return 1ul;
        else if constexpr (meta::is_unsigned_v<step_t>)
            return step_;
        else {
            return (step_ < 0 ? -step_ : step_);
        }
    }

    template <typename indices_t, typename si_t, typename start_t, typename stop_t, typename step_t, typename i_i_t>
    constexpr inline auto compute_index(const indices_t& indices, si_t si, start_t start_, stop_t stop_, step_t step_, i_i_t i_i)
    {
        using index_t [[maybe_unused]]  = meta::get_element_type_t<indices_t>;
        using sindex_t [[maybe_unused]] = meta::make_signed_t<index_t>;
        using result_t [[maybe_unused]] = meta::make_unsigned_t<index_t>;
        [[maybe_unused]] auto start = start_; // just alias
        // following numpy, stop is actually (stop,shape_i)
        [[maybe_unused]] auto stop = [&](){
            if constexpr (is_none_v<stop_t>)
                return si;
            // clip value, keep sign
            else {
                using common_t = meta::promote_index_t<stop_t,si_t>;
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
            return (result_t)index;
        }
        // (2) only start is integer
        else if constexpr (meta::is_index_v<start_t> && is_none_v<stop_t> && is_none_v<step_t>) {
            // example case:
            // a[0::]
            // a[-1::]
            auto index = (start >= 0 ? start : stop - start) + at(indices,i_i);
            return (result_t)index;
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
            return (result_t)index;
        }
        // (4) all three is integer, can be positive or negative
        else if constexpr (meta::is_index_v<start_t> && meta::is_index_v<stop_t> && meta::is_index_v<step_t>) {
            auto _start = index_t{0};
            auto _step  = index_t{0};
            // step is negative:
            if /**/ (start >= 0 && stop >= 0 && step < 0) {
                if (stop > 0) {
                    _start = stop - 1;
                    _step  = step;
                } else {
                    _start = start;
                    _step  = step;
                }
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
            return (result_t)index;
        } else if constexpr (is_none_v<start_t> && meta::is_index_v<stop_t> && is_none_v<step_t>) {
            auto index = at(indices,i_i);
            return (result_t)index;
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
            return (result_t)index;
        }
        else if constexpr (is_none_v<start_t> && is_none_v<stop_t> && meta::is_index_v<step_t>) {
            // example case:
            // a[::-1]
            auto _start = sindex_t{0};
            auto _step  = sindex_t{0};
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
            return (result_t)index;
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
            return (result_t)index;
        }
    };

    /**
     * @brief Either-aware type check for index type
     * 
     * @tparam value_t 
     * @param value 
     * @return auto 
     */
    template <typename value_t>
    auto is_int(const value_t& value)
    {
        if constexpr (meta::is_either_v<value_t>) {
            using left_t  = meta::get_either_left_t<value_t>;
            using right_t = meta::get_either_right_t<value_t>;
            auto l_ptr = nmtools::get_if<left_t>(&value);
            auto r_ptr = nmtools::get_if<right_t>(&value);
            if (l_ptr) {
                return is_int(*l_ptr);
            } else {
                return is_int(*r_ptr);
            }
        } else {
            return meta::is_index_v<value_t>;
        }
    }

    /**
     * @brief Either-aware type check for ellipsis type
     * 
     * @tparam value_t 
     * @param value 
     * @return auto 
     */
    template <typename value_t>
    auto is_ellipsis(const value_t& value)
    {
        if constexpr (meta::is_either_v<value_t>) {
            using left_t  = meta::get_either_left_t<value_t>;
            using right_t = meta::get_either_right_t<value_t>;
            auto l_ptr = nmtools::get_if<left_t>(&value);
            auto r_ptr = nmtools::get_if<right_t>(&value);
            if (l_ptr) {
                return is_ellipsis(*l_ptr);
            } else {
                return is_ellipsis(*r_ptr);
            }
        } else {
            return is_ellipsis_v<value_t>;
        }
    }

    /**
     * @brief Get the index array from possibly nested-either type
     * 
     * @tparam slice_t 
     * @param slice 
     * @return constexpr auto 
     */
    template <typename slice_t>
    constexpr auto get_index_array(const slice_t& slice)
    {
        if constexpr (meta::is_either_v<slice_t>) {
            using left_t  = meta::get_either_left_t<slice_t>;
            using right_t = meta::get_either_right_t<slice_t>;
            auto l_ptr = nmtools::get_if<left_t>(&slice);
            auto r_ptr = nmtools::get_if<right_t>(&slice);
            // assume ther no other index array in this possibly-nested either
            // TODO: consider to use flatten_either
            if constexpr (meta::is_index_array_v<left_t>) {
                return l_ptr;
            } else if constexpr (meta::is_index_array_v<right_t>) {
                return r_ptr;
            }
            // if neither left or right is index array,
            // then the only possible index array is those who is either
            else if constexpr (meta::is_either_v<left_t>) {
                using return_t = decltype(get_index_array(*l_ptr));
                if (l_ptr) {
                    return static_cast<return_t>(get_index_array(*l_ptr));
                } else {
                    return static_cast<return_t>(nullptr);
                }
            } else if constexpr (meta::is_either_v<right_t>) {
                using return_t = decltype(get_index_array(*r_ptr));
                if (r_ptr) {
                    return static_cast<return_t>(get_index_array(*r_ptr));
                } else {
                    return static_cast<return_t>(nullptr);
                }
            }
            // can't find any index array on this type
            // simply just return nullptr
            else {
                return static_cast<const left_t*>(nullptr);
            }
        } else {
            using return_t = const slice_t*;
            if (meta::is_index_array_v<slice_t>) {
                return static_cast<return_t>(&slice);
            } else {
                return static_cast<return_t>(nullptr);
            }
        }
    }

    /**
     * @brief Get the tuple from possibly nested either type
     * 
     * @tparam slice_t 
     * @param slice 
     * @return constexpr auto 
     */
    template <typename slice_t>
    constexpr auto get_tuple(const slice_t& slice)
    {
        if constexpr (meta::is_either_v<slice_t>) {
            using left_t  = meta::get_either_left_t<slice_t>;
            using right_t = meta::get_either_right_t<slice_t>;
            auto l_ptr = nmtools::get_if<left_t>(&slice);
            auto r_ptr = nmtools::get_if<right_t>(&slice);
            if constexpr (meta::is_tuple_v<left_t>) {
                return l_ptr;
            } else if constexpr (meta::is_tuple_v<right_t>) {
                return r_ptr;
            }
            // if neither left or right is tuple,
            // then the only possible tuple is on those who is either type
            else if constexpr (meta::is_either_v<left_t>) {
                using return_t = decltype(get_tuple(*l_ptr));
                if (l_ptr) {
                    return static_cast<return_t>(get_tuple(*l_ptr));
                } else {
                    return static_cast<return_t>(nullptr);
                }
            } else if constexpr (meta::is_either_v<right_t>) {
                using return_t = decltype(get_tuple(*r_ptr));
                if (r_ptr) {
                    return static_cast<return_t>(get_tuple(*r_ptr));
                } else {
                    return static_cast<return_t>(nullptr);
                }
            }
            // can't find any tuple on this type
            // simply just return nullptr
            else {
                return static_cast<const left_t*>(nullptr);
            }
        } else {
            using return_t = const slice_t*;
            if (meta::is_tuple_v<slice_t>) {
                return static_cast<return_t>(&slice);
            } else {
                return static_cast<return_t>(nullptr);
            }
        }
    }

    /**
     * @brief Compute the shape of slice op for dynamic dimension array
     * 
     * @tparam shape_t  the original shape of dynamic-dim ndarray
     * @tparam slices_t slice arguments (as list)
     * @param shape 
     * @param slices 
     * @return constexpr auto 
     */
    template <typename shape_t, typename slices_t>
    constexpr auto shape_dynamic_slice(const shape_t& shape, const slices_t& slices)
    {
        using result_t  = meta::resolve_optype_t<shape_dynamic_slice_t,shape_t,slices_t>;
        using size_type = meta::get_element_type_t<result_t>;
        using slice_t [[maybe_unused]] = meta::get_value_type_t<slices_t>;
        using namespace literals;

        [[maybe_unused]] auto dim = len(shape);
        const auto n_slices = len(slices);
        const auto& slices_pack = slices;

        [[maybe_unused]] auto apply_range_slice = [&](const auto& slice, auto shape_i){
            auto start = at(slice,0_ct);
            auto stop  = at(slice,1_ct);
            // NOTE: can not explicitly capture only slice, clang may triggers warning
            auto step  = [&](){
                using m_slice_t = meta::remove_cvref_t<decltype(slice)>;
                // TODO: assert for fixed-size value_type of slices_t
                constexpr auto N = meta::len_v<m_slice_t>;
                if constexpr (N == 3) {
                    return at(slice,2_ct);
                } else {
                    return size_t{1};
                }
            }();
            auto s = compute_range(shape_i,start,stop,step);
            auto step_ = compute_step(step);
            return static_cast<size_type>(math::ceil(static_cast<float>(s) / step_));
        };

        auto res = result_t {};
        // slicing with index instead of range will reduce dimension
        auto n_int = [&](){
            auto n_int = 0;
            for (size_t i=0; i<n_slices; i++) {
                n_int += (is_int(at(slices,i)) ? 1 : 0);
            }
            return n_int;
        }();

        // slicing with ellipsis allows len(slices) != len(shape)
        [[maybe_unused]] auto n_ellipsis = [&](){
            auto n_ellipsis = 0;
            for (size_t i=0; i<n_slices; i++) {
                n_ellipsis += (is_ellipsis(at(slices,i)) ? 1 : 0);
            }
            return n_ellipsis;
        }();
        // TODO: error handling for ellipsis > 1

        if constexpr (meta::is_resizeable_v<result_t>) {
            res.resize(dim-n_int);
        }

        // keep track of result index,
        // since there may be int that will reduce dimension,
        // len(shape) != len(res)
        size_t res_i = 0;
        // keep track of shape index,
        // since there may be ellipsis that allow
        // len(slices) != len(shape)
        size_t shp_i = 0;
        for (size_t slc_i=0; slc_i<n_slices; slc_i++) {
            auto slice = at(slices_pack,slc_i);
            // fill up
            if (is_ellipsis(slice)) {
                // number of shape to be filled by ellipsis
                auto n = (dim - (n_slices-1));
                for (size_t i=0; i<n; i++) {
                    at(res,res_i++) = at(shape,shp_i++);
                }
            }
            // using int reduce the resulting dimension
            // doesn't contribute to shape value, only skip
            else if (is_int(slice)) {
                shp_i++;
                continue;
            }
            else {
                auto index_ptr = get_index_array(slice);
                auto tuple_ptr = get_tuple(slice);
                using index_t = meta::remove_cvref_t<decltype(*index_ptr)>;
                using tuple_t = meta::remove_cvref_t<decltype(*tuple_ptr)>;
                if (index_ptr) {
                    // avoid compile-time instantiation on ellipsis, int or other type
                    // should not be encountered at runtime,
                    // ellipsis or int at runtime should be handled by first top-level if branch
                    if constexpr (meta::is_index_array_v<index_t>) {
                        const auto& slice_ = *index_ptr;
                        auto shape_i = at(shape,shp_i);
                        at(res,res_i) = apply_range_slice(slice_,shape_i);
                        res_i++;
                        shp_i++;
                    }
                } else if (tuple_ptr) {
                    // avoid compile-time instantiation on ellipsis, int or other type
                    // should not be encountered at runtime,
                    // ellipsis or int at runtime should be handled by first top-level if branch
                    if constexpr (meta::is_tuple_v<tuple_t>) {
                        const auto& slice_ = *tuple_ptr;
                        auto shape_i = at(shape,shp_i);
                        at(res,res_i) = apply_range_slice(slice_,shape_i);
                        res_i++;
                        shp_i++;
                    }
                }
            } // else (index array & tuple handler)
        }

        return res;
    } // shape_dynamic_slice

    /**
     * @brief Get integer ptr from possibly-nested either
     * 
     * @tparam value_t 
     * @param value 
     * @return constexpr auto 
     */
    template <typename value_t>
    constexpr auto get_int(const value_t& value)
    {
        // NOTE: use maybe type to allow nullability,
        // while also make sure the returned type is indeed index type (no either type)
        using empty_t = nmtools_maybe<int>;
        [[maybe_unused]] auto empty = empty_t{meta::Nothing};
        if constexpr (meta::is_either_v<value_t>) {
            using left_t  = meta::get_either_left_t<value_t>;
            using right_t = meta::get_either_right_t<value_t>;
            auto l_ptr = nmtools::get_if<left_t>(&value);
            auto r_ptr = nmtools::get_if<right_t>(&value);
            // assume there is no other int in this possibly-nested either
            // TODO: consider to use flatten_either
            if constexpr (meta::is_index_v<left_t>) {
                return l_ptr;
            } else if constexpr (meta::is_index_v<right_t>) {
                return r_ptr;
            }
            // try to find int in left or right
            else if constexpr (meta::is_either_v<left_t>) {
                using return_t = decltype(get_int(*l_ptr));
                if (l_ptr) {
                    return static_cast<return_t>(get_int(*l_ptr));
                } else {
                    return static_cast<return_t>(nullptr);
                }
            } else if constexpr (meta::is_either_v<right_t>) {
                using return_t = decltype(get_int(*r_ptr));
                if (r_ptr) {
                    return static_cast<return_t>(get_int(*r_ptr));
                } else {
                    return static_cast<return_t>(nullptr);
                }
            }
            // can't find any int on this type
            // simply return dummy int ptr
            else {
                return static_cast<const int*>(nullptr);
            }
        } else if constexpr (meta::is_index_v<value_t>) {
            using return_t = const value_t*;
            return static_cast<return_t>(&value);
        } else {
            // dummy int, to avoid instantiating function with unsupported concept
            return static_cast<const int*>(nullptr);
        }
    }


    /**
     * @brief Transform sliced indices back to original indics
     * 
     * @tparam indices_t    sliced indices
     * @tparam shape_t      shape of original ndarray
     * @tparam slices_t     slicing arguments
     * @param indices 
     * @param shape 
     * @param slices 
     * @return constexpr auto 
     */
    template <typename indices_t, typename shape_t, typename slices_t>
    constexpr auto dynamic_slice(const indices_t& indices, const shape_t& shape, const slices_t& slices)
    {
        using result_t = meta::resolve_optype_t<dynamic_slice_t,indices_t,shape_t,slices_t>;
        using namespace literals;

        auto res = result_t {};
        auto dim = len(shape);
        const auto n_slices = len(slices);

        if constexpr (meta::is_resizeable_v<result_t>) {
            res.resize(dim);
        }

        const auto& slices_pack = slices;

        // TODO: error handling, len(slices) may be not equal to len(shape)

        [[maybe_unused]] auto abs_ = [](auto v) { return v < 0 ? -v : v; };

        auto index_i  = size_t{0};
        auto shape_i  = size_t{0};
        auto result_i = size_t{0};
        auto slice_i  = size_t{0};
        for (; slice_i<n_slices;) {
            auto slice = at(slices_pack,slice_i);
            using slice_t = decltype(slice);
            [[maybe_unused]]
            auto handle_ellipsis = [&](){
                // 1 refers to the fact that:
                // there should be only 1 ellipsis in slices
                auto n = (dim - (n_slices - 1));
                for (size_t i=0; i<n; i++) {
                    auto index = at(indices,index_i++);
                    [[maybe_unused]]
                    auto si    = at(shape,shape_i++);
                    // TODO: use normalize axis
                    using index_t = meta::remove_cvref_t<decltype(index)>;
                    if constexpr (meta::is_signed_v<index_t>) {
                        at(res,result_i++) = (index < 0 ? si - abs_(index) : index);
                    } else {
                        at(res,result_i++) = index;
                    }
                }
                slice_i++;
            };
            [[maybe_unused]]
            auto handle_integer = [&](auto integer){
                auto si = at(shape,shape_i++);
                at(res,result_i++) = (integer < 0 ? si - abs_(integer) : integer);
                // NOTE: index_i should not be incremented, len(indices) != len(slices)
                slice_i++;
            };
            [[maybe_unused]]
            auto handle_index_array = [&](auto slice){
                const auto [start_, stop_, step_] = [&](){
                    // assume slice has tuple_size
                    constexpr auto NS = meta::len_v<decltype(slice)>;
                    if constexpr (NS==2) {
                        const auto [start, stop] = slice;
                        using mresult_t = meta::make_tuple_type_t<decltype(start),decltype(stop),none_t>;
                        return mresult_t{start,stop,None};
                    }
                    // return as it is to keep dtype
                    else if constexpr (NS==3)
                        return slice;
                }();
                auto si = at(shape,shape_i);
                auto index = compute_index(indices,si,start_,stop_,step_,index_i);
                at(res,result_i) = index;
                slice_i++, shape_i++, index_i++, result_i++;
            };
            if constexpr (meta::is_either_v<slice_t>) {
                // may be nested either, use flatten either
                const auto slice_ptrs = flatten_either(slice);
                constexpr auto N = meta::len_v<decltype(slice_ptrs)>;
                meta::template_for<N>([&](auto index){
                    constexpr auto I = decltype(index)::value;
                    const auto slice_ptr = nmtools::get<I>(slice_ptrs);
                    using m_slice_t = meta::remove_cvref_t<decltype(*slice_ptr)>;
                    if constexpr (is_ellipsis_v<m_slice_t>) {
                        if (slice_ptr) {
                            [[maybe_unused]] const auto& slice = *slice_ptr;
                            handle_ellipsis();
                        }
                    } else if constexpr (meta::is_index_v<m_slice_t>) {
                        if (slice_ptr) {
                            const auto& slice = *slice_ptr;
                            handle_integer(slice);
                        }
                    } else /* if constexpr (meta::is_index_array_v<m_slice_t> || meta::is_tuple_v<m_slice_t>) */ {
                        if (slice_ptr) {
                            const auto& slice = *slice_ptr;
                            handle_index_array(slice);
                        }
                    }
                });
            } else if constexpr (is_ellipsis_v<slice_t>) {
                handle_ellipsis();
            } else if constexpr (meta::is_integer_v<slice_t>) {
                handle_integer(slice);
            } else {
                handle_index_array(slice);
            }
        }

        return res;
    }
    
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_DYNAMIC_SLICE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct DYNAMIC_SLICE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename slice_t>
    struct resolve_optype<void,index::shape_dynamic_slice_t,shape_t,slice_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (is_fixed_index_array_v<shape_t>) {
                using index_t = get_element_or_common_type_t<shape_t>;
                using elem_t  = make_unsigned_t<index_t>;
                constexpr auto src_dim = len_v<shape_t>;
                using type = make_hybrid_ndarray_t<elem_t,src_dim,1>;
                return as_value_v<type>;
            } else if constexpr (is_dynamic_index_array_v<shape_t>) {
                using index_t = get_element_or_common_type_t<shape_t>;
                using elem_t  = make_unsigned_t<index_t>;
                using type = replace_element_type_t<shape_t,elem_t>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_DYNAMIC_SLICE_UNSUPPORTED<shape_t,slice_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename indices_t, typename shape_t, typename slice_t>
    struct resolve_optype<void,index::dynamic_slice_t,indices_t,shape_t,slice_t>
    {
        static constexpr auto vtype  = [](){
            // index computation follow shape
            if constexpr (is_constant_index_array_v<shape_t>) {
                using type = resolve_optype_t<index::dynamic_slice_t,indices_t,remove_cvref_t<decltype(to_value_v<shape_t>)>,slice_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<shape_t>) {
                // TODO: handle raw array
                using index_t = get_element_or_common_type_t<shape_t>;
                using elem_t  = make_unsigned_t<index_t>;
                using type = replace_element_type_t<shape_t,elem_t>;
                return as_value_v<type>;
            } else {
                using type = error::DYNAMIC_SLICE_UNSUPPORTED<indices_t,shape_t,slice_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_DYNAMIC_SLICE_HPP

#ifndef NMTOOLS_ARRAY_INDEX_SLICE_HPP
#define NMTOOLS_ARRAY_INDEX_SLICE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/index/ref.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/math.hpp"

namespace nmtools::index
{
    struct shape_slice_t {};
    struct slice_t {};

    template <typename shape_t, typename...slices_t>
    constexpr auto shape_slice(const shape_t& shape_, const slices_t&...slices)
    {
        using return_t  = meta::resolve_optype_t<shape_slice_t,shape_t,slices_t...>;
        using size_type = meta::get_element_type_t<return_t>;
        // number of integer in slices, represent indexing instead of slice
        constexpr auto N_INT = (static_cast<size_t>(meta::is_index_v<slices_t>) + ...);

        auto shape = [&](){
            // convert constant_index_array of shape to easily allow element access with runtime index
            if constexpr (meta::is_constant_index_array_v<shape_t>) {
                return meta::to_value_v<shape_t>;
            } else if constexpr (meta::is_bounded_array_v<shape_t>) {
                // raw array can't be copied (without decaying)
                return index::ref(shape_);
            } else /* if constexpr (meta::is_index_array_v<shape_t>) */ {
                // assume copyable
                return shape_;
            }
        }();

        // computes the number of ellipsis provided in slices_t...
        // note that the only valid number of ellipsis should be either 0 or 1
        constexpr auto NUM_ELLIPSIS = (static_cast<size_t>(is_ellipsis_v<slices_t>) + ...);
        static_assert( (NUM_ELLIPSIS <= 1)
            , "only exactly zero or one ellipsis are allowed"
        );

        auto res = return_t {};
        // Ellipsis doesn't contribute to dimension reduction.
        // Not all constexpr branches are using dim
        [[maybe_unused]] auto dim = len(shape) - N_INT;
        if constexpr (meta::is_resizeable_v<return_t>) {
            res.resize(dim);
        }
        
        // TODO error handling
        // make sure sizeof...(slices) <= len(shape)

        auto slices_pack = meta::make_tuple_type_t<const slices_t&...>{slices...};

        // since res and shape may have different dim,
        // this var is to keep track of the active result index
        auto r_i = size_t{0};
        // to keep track of the active shape index,
        // note that the active shape index may not be the same as
        // i (index of slices) because of ellipsis
        auto s_i = size_t{0};
        constexpr auto N_SLICES = sizeof...(slices);
        meta::template_for<N_SLICES>([&](auto i){
            auto slice = at(slices_pack, i);
            // we set si here to avoid gcc 8 internal error
            // note that we also explicit using size_t here
            // can't infer type (or using size_type ) :|
            // size_type si = at(shape,i);
            [[maybe_unused]] size_t si = at(shape,s_i);
            using slice_t = meta::remove_cvref_t<decltype(slice)>;

            // helper lambda to decompose start stop and step
            [[maybe_unused]] auto decompose = [&](auto slice){
                // assume slice has tuple_size
                constexpr auto NS = meta::len_v<decltype(slice)>;
                if constexpr (NS==2) {
                    const auto [start, stop] = slice;
                    return nmtools_tuple{start,stop,None};
                }
                // return as it is to keep dtype
                else if constexpr (NS==3) {
                    return slice;
                }
            };

            // when we found ellipsis,
            // fill up res with ":" aka tuple{None,None}
            // which is simply copy shape at the corresponding axis
            if constexpr (is_ellipsis_v<slice_t>) {
                // ellipsis takes src dim, not dst dim
                auto dim = len(shape);
                // number of shape to be filled (by ellipsis):
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
                const auto [start_,stop_,step_] = decompose(slice);
                using step_t [[maybe_unused]] = meta::remove_cvref_t<decltype(step_)>;

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

                auto s = compute_range(si,start_,stop_,step_);

                auto step = []([[maybe_unused]] auto step_){
                    using m_step_t = meta::remove_cvref_t<decltype(step_)>;
                    // NOTE: step_ is passed instead of captured to avoid clang error
                    if constexpr (is_none_v<m_step_t>)
                        return 1ul;
                    else if constexpr (meta::is_unsigned_v<m_step_t>)
                        return step_;
                    else {
                        using unsigned_step_t = meta::make_unsigned_t<m_step_t>;
                        if (step_ < 0) {
                            return (unsigned_step_t)-step_;
                        } else {
                            return (unsigned_step_t)step_;
                        }
                    }
                }(step_);

                // finally the resulting shape for corresponding indices
                // is simply the range divided by the step
                at(res,r_i++) = static_cast<size_type>(math::ceil(static_cast<float>(s) / step));
            } else /* if constexpr (meta::is_index_v<slice_t>) */ {
                // only reduce the dimension,
                // doesn't contributes to shape computation
            }
            // increment the active shape index here
            // to make sure that it handled all the case (ellipsis,tuple,integral).
            // note that ellipsis may cause both active shape index and active result index
            // to be incremented.
            s_i++;
        });

        return res;
    } // shape_slice

    /**
     * @brief Compute the index (of the original shape) from destination index (sliced index)
     * 
     * @tparam indices_t    transformed index (sliced index)
     * @tparam shape_t      original shape
     * @tparam slices_t     arguments to slice
     * @param indices 
     * @param shape_ 
     * @param slices 
     * @return constexpr auto 
     */
    template <typename indices_t, typename shape_t, typename...slices_t>
    constexpr auto slice(const indices_t& indices, const shape_t& shape_, const slices_t&...slices)
    {
        using return_t = meta::resolve_optype_t<slice_t,indices_t,shape_t,slices_t...>;
        using index_t [[maybe_unused]]  = meta::remove_cvref_t<meta::get_element_type_t<return_t>>;

        const auto shape = [&](){
            // convert constant_index_array of shape to easily allow element access with runtime index
            if constexpr (meta::is_constant_index_array_v<shape_t>) {
                return meta::to_value_v<shape_t>;
            } else if constexpr (meta::is_bounded_array_v<shape_t>) {
                // raw array can't be copied (without decaying)
                return index::ref(shape_);
            } else /* if constexpr (meta::is_index_array_v<shape_t>) */ {
                // assume copyable
                return shape_;
            }
        }();

        auto res = return_t {};
        auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(dim);
        
        auto slices_pack = meta::make_tuple_type_t<const slices_t&...>{slices...};

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
            } else if constexpr (is_ellipsis_v<slice_t>) {
                auto n = (dim-(N_SLICES-1));
                for (size_t j=0; j<n; j++) {
                    // we're on ellipsis, active shape index may also shifted
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
                // for ellipsis and tuple case of slice_t.
                // so here r_i and s_i are incremented by (n-1)
                // while i_i is incremented by n.
                r_i += (n-1);
                s_i += (n-1);
                i_i += (n);
            } else {
                const auto [start_, stop_, step_] = [&](){
                    // assume slice has tuple_size
                    constexpr auto NS = meta::len_v<decltype(slice)>;
                    if constexpr (NS==2) {
                        const auto [start, stop] = slice;
                        using mresult_t = meta::make_tuple_type_t<decltype(start),decltype(stop),none_t>;
                        return mresult_t{start,stop,None};
                    }
                    // return as it is to keep dtype
                    else if constexpr (NS==3)
                        return slice;
                }();
                using start_t [[maybe_unused]] = meta::remove_cvref_t<decltype(start_)>;
                using stop_t [[maybe_unused]]  = meta::remove_cvref_t<decltype(stop_)>;
                using step_t [[maybe_unused]]  = meta::remove_cvref_t<decltype(step_)>;

                // some tricky case: assume shape=(4,2)
                // (1) a[::-2,1::-2]
                // (2) a[::-2,1::2]
                // (1) and (2) is actually the same 
                // TODO: exploit the type information, such as signed-/unsigned-ness
                // to perform conditional compilation

                // TODO: use compute_index
                // here we compute the start index step, regardless of the dst index
                // should handle various case, e.g. None, positive, negative start & stop
                // also assume indices is properly generated
                #if 0
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
                #endif

                at(res,r_i) = compute_index(indices,si,start_,stop_,step_,i_i);
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

} // namespace nmtools::index

namespace nmtools::meta
{
    // TODO: compute at compile time whenever possible
    template <typename shape_t, typename...slices_t>
    struct resolve_optype<
        void, index::shape_slice_t, shape_t, slices_t...
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_fixed_index_array_v<shape_t>) {
                constexpr auto n_integer = ((static_cast<size_t>(meta::is_index_v<slices_t>)) + ...);
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

namespace nmtools::index
{
    /**
     * @brief Expand slice arguments to call slice.
     * 
     * @tparam index_sequence 
     * @tparam indices_t 
     * @tparam shape_t 
     * @tparam slices_t 
     * @tparam Is 
     * @param indices 
     * @param shape 
     * @param slices 
     * @return constexpr auto 
     */
    template <template <auto...> typename index_sequence, typename indices_t, typename shape_t, typename slices_t, size_t...Is>
    constexpr auto apply_slice(const indices_t& indices, const shape_t& shape, const slices_t& slices, index_sequence<Is...>)
    {
        return slice(indices, shape, nmtools::get<Is>(slices)...);
    } // apply_slice

    /**
     * @brief Tranform indices from sliced array back to original array indices.
     * 
     * @tparam indices_t 
     * @tparam shape_t 
     * @tparam slices_t 
     * @param indices sliced array's indices
     * @param shape   original array shape
     * @param slices  slicing arguments
     * @return constexpr auto 
     */
    template <typename indices_t, typename shape_t, typename slices_t>
    constexpr auto apply_slice(const indices_t& indices, const shape_t& shape, const slices_t& slices)
    {
        constexpr auto N = meta::len_v<slices_t>;
        constexpr auto element_vtype = [](){
            if constexpr (meta::is_tuple_v<slices_t>) {
                using type = void;
                return meta::as_value_v<type>;
            } else {
                // assume has value_type
                using type = meta::get_value_type_t<slices_t>;
                return meta::as_value_v<type>;
            }
        }();
        using element_t = meta::type_t<decltype(element_vtype)>;
        // NOTE: variadic version doesn't handle either type properly
        if constexpr ((N > 0) && !meta::is_either_v<element_t>) {
            return apply_slice(indices,shape,slices,meta::make_index_sequence<N>{});
        } else {
            return dynamic_slice(indices,shape,slices);
        }
    } // apply_slice

    template <typename shape_t, typename slices_t, template<auto...> typename index_sequence, auto...Is>
    constexpr auto apply_shape_slice(const shape_t& shape, const slices_t& slices, index_sequence<Is...>)
    {
        return shape_slice(shape, nmtools::get<Is>(slices)...);
    }

    /**
     * @brief Compute the shape of slice operations.
     * 
     * Dispatch to fixed length or dynamic length accordingly.
     * 
     * @tparam shape_t 
     * @tparam slices_t 
     * @param shape 
     * @param slices 
     * @return constexpr auto 
     */
    template <typename shape_t, typename slices_t>
    constexpr auto apply_shape_slice(const shape_t& shape, const slices_t& slices)
    {
        constexpr auto N = meta::len_v<slices_t>;
        constexpr auto element_vtype = [](){
            if constexpr (meta::is_tuple_v<slices_t>) {
                using type = void;
                return meta::as_value_v<type>;
            } else {
                // assume has value_type
                using type = meta::get_value_type_t<slices_t>;
                return meta::as_value_v<type>;
            }
        }();
        using element_t = meta::type_t<decltype(element_vtype)>;
        // NOTE: variadic version doesn't handle either type properly
        if constexpr ((N > 0) && !meta::is_either_v<element_t>) {
            return apply_shape_slice(shape,slices,meta::make_index_sequence<N>{});
        } else {
            return shape_dynamic_slice(shape,slices);
        }
    } // apply_shape_slice
} // namespace nmtools::index


#endif // NMTOOLS_ARRAY_INDEX_SLICE_HPP