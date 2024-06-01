#ifndef NMTOOLS_ARRAY_INDEX_ROLL_HPP
#define NMTOOLS_ARRAY_INDEX_ROLL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    struct shape_roll_t {};
    struct roll_t {};

    template <typename src_shape_t, typename shift_t, typename axis_t>
    constexpr auto shape_roll(const src_shape_t& shape, [[maybe_unused]] const shift_t& shift, const axis_t& axis)
    {
        using result_t = meta::resolve_optype_t<shape_roll_t,src_shape_t,shift_t,axis_t>;

        if constexpr (meta::is_fail_v<result_t>
            || meta::is_constant_index_array_v<result_t>
        ) {
            auto result = result_t{};
            return result;
        } else {
            using return_t = meta::conditional_t<
                is_none_v<axis_t> /* when axis is none, always success, no need maybe type */
                , result_t
                , nmtools_maybe<result_t> /* otherwise whe should check for axis in range */
            >;

            auto success = true;
            auto result  = result_t{};

            auto dim = len(shape);

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                at(result,i) = at(shape,i);
            }

            if constexpr (meta::is_index_array_v<axis_t>
                || meta::is_index_v<axis_t>
            ) {
                auto normalized_axis = normalize_axis(axis,len(shape));
                // assume normalize_axis always return maybe type for this path
                success = static_cast<bool>(normalized_axis);
            }

            if constexpr (meta::is_maybe_v<return_t>) {
                if (success) {
                    return return_t{result};
                } else {
                    return return_t{meta::Nothing};
                }
            } else {
                return result;
            }
        }
    } // shape_roll

    struct normalize_roll_length_t {};

    // normalize the size of lhs to rhs (make same size, follow rhs)
    template <typename lhs_t, typename rhs_t>
    constexpr auto normalize_roll_length(const lhs_t& lhs, const rhs_t& rhs)
    {
        using result_t [[maybe_unused]] = meta::resolve_optype_t<normalize_roll_length_t,lhs_t,rhs_t>;
        if constexpr (meta::is_index_v<meta::remove_cvref_t<decltype(rhs)>>) {
            // assume lhs is index
            return lhs;
        } else if constexpr (meta::is_index_v<decltype(lhs)>
            && meta::is_index_array_v<meta::remove_cvref_t<decltype(rhs)>>
        ) {
            auto result = result_t {};
            auto dim = len(rhs);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dim);
            }
            for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                at(result,i) = lhs;
            }
            return result;
        } else /* if constexpr (meta::is_index_array_v<decltype(lhs)>
            && meta::is_index_array_v<meta::remove_cvref_t<decltype(rhs)>>) */
        {
            // assume rhs & lhs is the same length
            auto result = result_t {};
            auto dim = len(rhs);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dim);
            }
            for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                at(result,i) = at(lhs,i);
            }
            return result;
        }
    }

    template <typename shape_t, typename indices_t, typename shift_t, typename axis_t=none_t>
    constexpr auto roll(const shape_t& shape, const indices_t& indices, const shift_t& shift, const axis_t& axis=axis_t{})
    {
        using result_t = meta::resolve_optype_t<roll_t,shape_t,indices_t,shift_t,axis_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto dim = len(shape);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dim);
            }

            #if 0
            // The following produce different result in compile-time vs runtime computation :|
            auto normalize_roll_index = [](auto index, const auto axis)
            #else
            auto normalize_roll_index = [](nm_index_t index, const auto axis) -> nm_index_t
            #endif
            {
                if (index < 0) {
                    return axis + index;
                } else if ((nm_index_t)index >= (nm_index_t)axis) {
                    return index - axis;
                } else {
                    return index;
                }
            };

            if constexpr (is_none_v<axis_t>) {
                for (nm_size_t i=0; i<nm_size_t(dim); i++) {
                    auto shape_i = at(shape,i);
                    auto index   = nm_index_t(at(indices,i)) - shift;
                    at(result,i) = normalize_roll_index(index,shape_i);
                }
            } else if constexpr (meta::is_index_v<axis_t>) {
                // fill with index first then adjust at axis
                for (nm_size_t i=0; i<nm_size_t(dim); i++) {
                    at(result,i) = at(indices,i);
                }
                auto shape_i = at(shape,axis);
                auto index   = nm_index_t(at(indices,axis)) - shift;
                at(result,axis) = normalize_roll_index(index,shape_i);
            } else /* if constexpr (meta::is_index_array_v<axis_t>) */ {
                // fill with index first then adjust at axis
                for (nm_size_t i=0; i<nm_size_t(dim); i++) {
                    at(result,i) = at(indices,i);
                }
                auto m_shift = normalize_roll_length(shift,axis);
                for (size_t i=0; i<len(axis); i++) {
                    auto axis_i  = at(axis,i);
                    auto shape_i = at(shape,axis_i);
                    auto index   = nm_index_t(at(indices,axis_i)) - at(m_shift,i);
                    at(result,axis_i) = normalize_roll_index(index,shape_i);
                }
            }
        }

        return result;
    } // roll
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct SHAPE_ROLL_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct SHAPE_ROLL_INVALID : detail::fail_t {};
        template<typename...>
        struct ROLL_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct NORMALIZE_ROLL_LENGTH_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename shift_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_roll_t, src_shape_t, shift_t, axis_t
    >{
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto DIM = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto B_DIM = bounded_size_v<src_shape_t>;
            if constexpr (
                !is_index_array_v<src_shape_t>
                || !(is_index_v<shift_t> || is_index_array_v<shift_t>)
                || !(is_index_v<axis_t>  || is_index_array_v<axis_t> || is_none_v<axis_t>)
            ) {
                using type = error::SHAPE_ROLL_UNSUPPORTED<src_shape_t,shift_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && (is_constant_index_array_v<shift_t> || is_constant_index_v<shift_t>)
                && (is_constant_index_array_v<axis_t>  || is_constant_index_v<axis_t> || is_none_v<axis_t>)
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto shift  = to_value_v<shift_t>;
                constexpr auto axis   = to_value_v<axis_t>;
                constexpr auto result = index::shape_roll(src_shape,shift,axis);
                if constexpr (has_value(result)) {
                    using nmtools::len, nmtools::at, nmtools::unwrap;
                    return meta::template_reduce<len(unwrap(result))>([&](auto init, auto i){
                        using init_type = type_t<decltype(init)>;
                        using result_t  = append_type_t<init_type,ct<at(unwrap(result),i)>>;
                        return as_value_v<result_t>;
                    }, as_value_v<nmtools_tuple<>>);
                } else {
                    using type = error::SHAPE_ROLL_INVALID<src_shape_t,shift_t,axis_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (DIM > 0) {
                using type = nmtools_array<nm_size_t,DIM>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                using type = nmtools_static_vector<nm_size_t,B_DIM>;
                return as_value_v<type>;
            } else {
                // TODO: support small_vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // shape_roll_t

    template <typename lhs_t, typename rhs_t>
    struct resolve_optype<
        void, index::normalize_roll_length_t, lhs_t, rhs_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !(is_index_v<lhs_t> || is_index_array_v<lhs_t>)
                || !(is_index_v<rhs_t> || is_index_array_v<rhs_t>)
            ) {
                using type = error::NORMALIZE_ROLL_LENGTH_UNSUPPORTED<lhs_t,rhs_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_index_v<rhs_t>
            ) {
                using type = lhs_t;
                return as_value_v<type>;
            } else if constexpr (
                is_index_v<lhs_t>
                && is_index_array_v<rhs_t>
            ) {
                constexpr auto DIM = len_v<rhs_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<rhs_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_index_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_index_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<nm_index_t>;
                    return as_value_v<type>;
                }
            } else {
                constexpr auto DIM = len_v<lhs_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<lhs_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_index_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_index_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<nm_index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename shape_t, typename indices_t, typename shift_t, typename axis_t>
    struct resolve_optype<
        void, index::roll_t, shape_t, indices_t, shift_t, axis_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>
                || !is_index_array_v<indices_t>
                || !(is_index_v<shift_t> || is_index_array_v<shift_t> || is_constant_index_array_v<shift_t>)
                || !(is_none_v<axis_t> || is_index_array_v<axis_t> || is_index_v<axis_t>)
            ) {
                using type = error::ROLL_UNSUPPORTED<shape_t,indices_t,shift_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<shape_t>
                && is_constant_index_array_v<indices_t>
                && (is_constant_index_v<shift_t> || is_constant_index_array_v<shift_t>)
                && (is_none_v<axis_t> || is_constant_index_v<axis_t> || is_constant_index_array_v<axis_t>)
            ) {
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto shift   = to_value_v<shift_t>;
                constexpr auto result  = index::roll(shape,indices,shift,axis_t{});
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto i){
                    using init_type   = type_t<decltype(init)>;
                    using result_type = append_type_t<init_type,ct<at(result,i)>>;
                    return as_value_v<result_type>;
                },as_value_v<nmtools_tuple<>>);
            } else if constexpr ((len_v<shape_t> > 0)
                && is_index_array_v<indices_t>
                && (is_index_v<shift_t> || is_index_array_v<shift_t>)
                && (is_none_v<axis_t> || is_index_array_v<axis_t> || is_index_v<axis_t>)
            ) {
                using type = nmtools_array<nm_size_t,len_v<shape_t>>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(bounded_size_v<shape_t>)>) {
                using type = nmtools_static_vector<nm_size_t,bounded_size_v<shape_t>>;
                return as_value_v<type>;
            } else {
                // TODO: support small-vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_ROLL_HPP