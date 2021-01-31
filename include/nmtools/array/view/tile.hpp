#ifndef NMTOOLS_ARRAY_VIEW_TILE_HPP
#define NMTOOLS_ARRAY_VIEW_TILE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/tile.hpp"
#include "nmtools/array/index/shape_tile.hpp"
#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    template <typename array_t, typename reps_t>
    struct tile_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        using array_type = const array_t&;
        using reps_type  = reps_t;
        
        array_type array;
        reps_type  reps;

        constexpr tile_t(array_type array, reps_type reps)
            : array(array), reps(reps) {}
        
        constexpr decltype(auto) shape() const
        {
            auto shape_ = ::nmtools::shape(array);
            return index::shape_tile(shape_,reps);
        } // shape

        constexpr decltype(auto) dim() const
        {
            auto shape_ = ::nmtools::shape(array);
            return index::tuple_size(index::shape_tile(shape_,reps));
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            using index::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for transpose view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            auto shape_ = ::nmtools::shape(array);
            return index::tile(shape_,reps,indices_);
        } // index
    }; // tile_t

    /**
     * @brief Construct a view by repeating array the number of times given by reps.
     * 
     * This follow numpy's tile, that is, if reps has length d, the result will have dimension of max(d, dim(array)).
     * 
     * @tparam array_t 
     * @tparam reps_t 
     * @param array The input array
     * @param reps The number of repetitions of array along each axis.
     * @return constexpr auto 
     */
    template <typename array_t, typename reps_t>
    constexpr auto tile(const array_t& array, const reps_t& reps)
    {
        return decorator_t<tile_t,array_t,reps_t>{{array,reps}};
    } // tile
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename reps_t>
    struct fixed_matrix_size< view::tile_t<array_t,reps_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    template <typename array_t, typename reps_t>
    struct fixed_vector_size< view::tile_t<array_t,reps_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    template <typename array_t, typename reps_t>
    struct fixed_ndarray_shape< view::tile_t<array_t,reps_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename array_t, typename reps_t>
    struct is_ndarray< view::decorator_t< view::tile_t, array_t, reps_t >>
        : is_ndarray<array_t> {};
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_TILE_HPP