#ifndef NMTOOLS_ARRAY_INDEX_TILE_HPP
#define NMTOOLS_ARRAY_INDEX_TILE_HPP

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/utl/static_vector.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of shape_tile op
     * 
     */
    struct shape_tile_t {};

    /**
     * @brief compute the resulting shape for tile view
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     * @param shape the shape of input array
     * @param reps number of repetitions foe each axis
     * @return constexpr auto 
     */
    template <typename shape_t, typename reps_t>
    constexpr auto shape_tile(const shape_t& shape, const reps_t& reps)
    {
        using return_t = meta::resolve_optype_t<shape_tile_t,shape_t,reps_t>;
        auto ret = return_t {};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            auto m = len(shape);
            auto n = len(reps);
            // TODO: better deduction
            auto s = [&]()->size_t{ // quick workaround for inconsistent type erro
                if ((size_t)m > (size_t)n) {
                    return m;
                } else {
                    return n;
                }
            }();

            if constexpr (meta::is_resizable_v<return_t>)
                ret.resize(s);

            auto shape_tile_impl = [&](auto i){
                using idx_t  = meta::remove_address_space_t<meta::get_index_element_type_t<shape_t>>;
                using sidx_t = meta::make_signed_t<idx_t>;
                sidx_t ai = m - i - 1;
                sidx_t bi = n - i - 1;
                sidx_t si = s - i - 1;
                if (ai < 0)
                    at(ret,si) = at(reps,bi);
                else if (bi < 0)
                    at(ret,si) = at(shape,ai);
                else {
                    auto a = at(shape,ai);
                    auto b = at(reps,bi);
                    at(ret,si) = a * b;
                }
            }; // shape_tile_impl

            for (size_t i=0; i<(size_t)len(ret); i++)
                shape_tile_impl(i);
        }

        return ret;
    } // shape_tile
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_TILE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    // TODO: compute at compile-time whenever possible
    /**
     * @brief resolve return type for index::shape_tile op
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     */
    template <typename shape_t, typename reps_t>
    struct resolve_optype <
        void, index::shape_tile_t, shape_t, reps_t
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_t> && is_constant_index_array_v<reps_t>) {
                constexpr auto result = index::shape_tile(to_value_v<shape_t>, to_value_v<reps_t>);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)-1>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    return as_value_v<append_type_t<init_type,ct<at(result,index+1)>>>;
                }, as_value_v<nmtools_tuple<ct<at(result,0)>>>);
            } else if constexpr (is_constant_index_array_v<shape_t> && is_index_array_v<reps_t>) {
                using type = resolve_optype_t<index::shape_tile_t,decltype(to_value_v<shape_t>),reps_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<shape_t> && is_constant_index_array_v<reps_t>) {
                using type = resolve_optype_t<index::shape_tile_t,shape_t,decltype(to_value_v<reps_t>)>;
                return as_value_v<type>;
            #if 1
            } else if constexpr (is_index_array_v<shape_t> && is_index_array_v<reps_t>) {
                constexpr auto N_SHAPE = len_v<shape_t>;
                constexpr auto N_REPS  = len_v<reps_t>;
                [[maybe_unused]] constexpr auto B_SHAPE = bounded_size_v<shape_t>;
                [[maybe_unused]] constexpr auto B_REPS  = bounded_size_v<reps_t>;
                using index_t = get_index_element_type_t<shape_t>;
                if constexpr ((N_SHAPE > 0) && (N_REPS > 0)) {
                    constexpr auto N = N_SHAPE > N_REPS ? N_SHAPE : N_REPS;
                    using type = nmtools_array<index_t,N>;
                    return as_value_v<type>;
                } else if constexpr ((N_SHAPE > 0) && !is_fail_v<decltype(B_REPS)>) {
                    constexpr auto N = N_SHAPE > B_REPS ? N_SHAPE : B_REPS;
                    using type = nmtools_static_vector<index_t,N>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_SHAPE)> && (N_REPS > 0)) {
                    constexpr auto N = B_SHAPE > N_REPS ? B_SHAPE : N_REPS;
                    using type = nmtools_static_vector<index_t,N>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_SHAPE)> && !is_fail_v<decltype(B_REPS)>) {
                    constexpr auto N = B_SHAPE > B_REPS ? B_SHAPE : B_REPS;
                    using type = nmtools_static_vector<index_t,N>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            #else
            } else if constexpr (is_hybrid_index_array_v<shape_t> && is_hybrid_index_array_v<reps_t>) {
                constexpr auto shape_max = bounded_size_v<shape_t>;
                constexpr auto reps_max  = bounded_size_v<reps_t>;
                constexpr auto max_size  = shape_max > reps_max ? shape_max : reps_max;
                using type = resize_bounded_size_t<shape_t,max_size>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t> && is_fixed_index_array_v<reps_t>) {
                constexpr auto shape_size = len_v<shape_t>;
                constexpr auto reps_size  = len_v<reps_t>;
                constexpr auto size = shape_size > reps_size ? shape_size : reps_size;
                // TODO: try to resize
                // using type = resize_fixed_index_array_t<shape_t,size>;
                using type = nmtools_array<get_index_element_type_t<shape_t>,size>;
                return as_value_v<type>;
            } else if constexpr (is_hybrid_index_array_v<shape_t> && is_fixed_index_array_v<reps_t>) {
                // always select max
                constexpr auto shape_max = bounded_size_v<shape_t>;
                constexpr auto reps_size = len_v<reps_t>;
                constexpr auto max = shape_max > reps_size ? shape_max : reps_size;
                using type = resize_bounded_size_t<shape_t,max>;
                return as_value_v<type>;
            } else if constexpr (is_hybrid_index_array_v<reps_t> && is_fixed_index_array_v<shape_t>) {
                constexpr auto shape_size = len_v<shape_t>;
                constexpr auto reps_max   = bounded_size_v<reps_t>;
                constexpr auto max = shape_size > reps_max ? shape_size : reps_max;
                using type = resize_bounded_size_t<reps_t,max>;
                return as_value_v<type>;
            } else if constexpr ((is_fixed_index_array_v<shape_t> || is_hybrid_index_array_v<shape_t>) && is_index_array_v<reps_t>) {
                return as_value_v<reps_t>;
            } else if constexpr (is_index_array_v<shape_t> && (is_fixed_index_array_v<reps_t> || is_hybrid_index_array_v<reps_t>)) {
                return as_value_v<shape_t>;
            } else if constexpr (is_index_array_v<shape_t> && is_index_array_v<reps_t>) {
                return as_value_v<shape_t>;
            #endif
            } else {
                return as_value_v<error::SHAPE_TILE_UNSUPPORTED<shape_t,reps_t>>;
            }
        }();
        using type = type_t<decltype(value)>;
    }; // resolve_optype
} // namespace nmtools::meta

namespace nmtools::index
{
    struct tile_t {};

    /**
     * @brief Transform indices from tile view to original array shape
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     * @tparam indices_t 
     * @param shape shape of original array
     * @param reps number of repetitions for each axis
     * @param indices indices from tile view
     * @return constexpr auto 
     */
    template <typename shape_t, typename reps_t, typename indices_t>
    constexpr auto tile(const shape_t& shape, const reps_t&, const indices_t& indices)
    {
        using return_t = meta::resolve_optype_t<tile_t,shape_t,reps_t,indices_t>;

        auto ret = return_t {};

        // len(indices) == max(len(shape),len(reps))
        auto m = len(shape);
        auto n = len(indices);
        // clang (android & emscripten) complains about ambiguous call
        auto s = [&]()->size_t{ // quick workaround for inconsistent type error
            // TODO: better deduction
            if ((size_t)m > (size_t)n) {
                return m;
            } else {
                return n;
            }
        }();

        if constexpr (meta::is_resizable_v<return_t>)
            ret.resize(len(shape));
        
        // use int since ai/bi may be negative
        for (int i=0; i<(int)s; i++) {
            int ai = m - i - 1;
            int bi = n - i - 1;
            if (ai >= 0) {
                auto idx = at(indices,bi);
                auto s = at(shape,ai);
                at(ret,ai) = idx % s;
            }
            else break;
        }
        
        return ret;
    } // tile
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error {
        template <typename...>
        struct INDEX_TILE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief resolve return type for index::tile op
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     * @tparam indices_t 
     */
    template <typename shape_t, typename reps_t, typename indices_t>
    struct resolve_optype <
        void, index::tile_t, shape_t, reps_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_constant_index_array_v<shape_t>
                || is_clipped_index_array_v<shape_t>
            ) {
                // return as_value_v<error::INDEX_TILE_UNSUPPORTED<shape_t,reps_t,indices_t>>;
                using index_t = get_index_element_type_t<shape_t>;
                using type = nmtools_array<index_t,len_v<shape_t>>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t>) {
                return as_value_v<transform_bounded_array_t<shape_t>>;
            } else if constexpr (is_index_array_v<shape_t>) {
                return as_value_v<shape_t>;
            } else {
                return as_value_v<error::INDEX_TILE_UNSUPPORTED<shape_t,reps_t,indices_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_TILE_HPP