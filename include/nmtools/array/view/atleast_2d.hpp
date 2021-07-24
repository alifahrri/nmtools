#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

// nmtools/meta/traits may define NMTOOLS_HAS_VECTOR
#if defined(NMTOOLS_HAS_VECTOR) && (NMTOOLS_HAS_VECTOR)
    #include <vector>
#endif

namespace nmtools::view
{
    template <typename array_t>
    struct atleast_2d_t
    {
        // TODO: consider to copy when array_t is simply arithmetic type
        using array_type = const array_t&;

        array_type array;

        constexpr atleast_2d_t(array_type array)
            : array(array) {}
        
        constexpr auto shape() const
        {
            // arithmetic type
            if constexpr (std::is_arithmetic_v<array_t>)
                return std::array{1ul,1ul};
            // check if fixed 1d array
            else if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
                using namespace nmtools::literals;
                // exactly 1d, prepend 1 to the shape
                auto shape_ = ::nmtools::shape(array);
                if constexpr (meta::fixed_dim_v<array_t> == 1)
                    return index::expand_dims(shape_,0_ct);
                // referenced array is atleast 2d
                else return shape_;
            }
            // assume dynamic dim
            else {
                // assume std::vector is available
                static_assert (NMTOOLS_HAS_VECTOR);
                auto shape_ = ::nmtools::shape(array);
                // prepend
                if (len(shape_)==1)
                    shape_.insert(shape_.begin(),1);
                return shape_;
            }
        } // shape

        constexpr auto dim() const
        {
            if constexpr (std::is_arithmetic_v<array_t>)
                return 2ul;
            else {
                auto dim_ = ::nmtools::dim(array);
                return dim_ < 2 ? 2 : dim_;
            }
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            using ::nmtools::index::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();

            // for now, assume indices is generated such that
            // they are within range
            // TODO: check shape
            if constexpr (std::is_arithmetic_v<array_t>)
                return array;
            else {
                auto expanded_shape   = shape();
                auto squeezed_strides = index::compute_strides(expanded_shape);

                auto shape_     = ::nmtools::shape(array);
                auto offset     = index::compute_offset(indices_,squeezed_strides);
                auto tf_indices = index::compute_indices(offset,shape_);
                return apply_at(array,tf_indices);
            }
        } // operator()
    }; // atleast_2d_t

    /**
     * @brief Create a atleast_2d_t view to a given array.
     * 
     * Views array with at least 2 dimension. Also accept scalar value.
     *
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto atleast_2d(const array_t& array)
    {
        using view_t = decorator_t<atleast_2d_t, array_t>;
        return view_t{{array}};
    } // atleast_2d
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t>
    struct get_element_type< view::decorator_t<view::atleast_2d_t, array_t> >
    {
        using type = std::conditional_t<
            std::is_arithmetic_v<array_t>, array_t,
            get_element_type_t<array_t>
        >;
    };

    template <typename array_t>
    struct fixed_vector_size< view::atleast_2d_t<array_t> >
    {
        static constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    template <typename array_t>
    struct fixed_matrix_size< view::atleast_2d_t<array_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (std::is_arithmetic_v<array_t>)
                return std::array{1ul,1ul};
            return fixed_matrix_size_v<array_t>;
        }();
        using value_type = decltype(value);
    };

    template <typename array_t>
    struct fixed_ndarray_shape< view::atleast_2d_t<array_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (std::is_arithmetic_v<array_t>)
                return std::array{1ul,1ul};
            else if constexpr (is_fixed_size_ndarray_v<array_t>) {
                if constexpr (fixed_ndarray_dim_v<array_t> == 1) {
                    constexpr auto shape_ = fixed_ndarray_shape_v<array_t>;
                    return index::expand_dims(shape_,0);
                }
                else return fixed_ndarray_shape_v<array_t>;
            }
            else return fixed_ndarray_shape_v<array_t>;
        }();
        using value_type = decltype(value);
    };

    template <typename array_t>
    struct is_ndarray< view::decorator_t< view::atleast_2d_t, array_t >>
    {
        static constexpr auto value = std::is_arithmetic_v<array_t> || is_ndarray_v<array_t>;
    };

    /**
     * @brief specialization of eval type resolver for atleast_2d view.
     * 
     * @tparam array_t 
     * @note this specialization is provided since no actual type
     *      with fixed-dim dynamic-size trait is available, while such array is needed for this view.
     * @todo add fixed-dim dynamic-size ndarray and remove this specialization.
     */
    template <typename array_t>
    struct resolve_optype<
        void, array::eval_t, view::decorator_t< view::atleast_2d_t, array_t >, none_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_num_v<array_t>) {
                using shape_t = std::tuple<ct<1>,ct<1>>;
                using type = make_fixed_ndarray_t<array_t,shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_size_ndarray_v<array_t>) {
                if constexpr (fixed_ndarray_dim_v<array_t> == 1) {
                    constexpr auto shape_ = fixed_ndarray_shape_v<array_t>;
                    // use arbitraty fixed-shape type to 
                    // match resize_fixed_ndarray signature
                    // (needs type instead of value)
                    // using some_array_t = std::array<std::array<int,at(shape_,0)>,1>;
                    using some_array_t = int[1][nmtools::at(shape_,0)];
                    using tf_array_t   = transform_bounded_array_t<array_t>;
                    using type = resize_fixed_ndarray_t<tf_array_t,some_array_t>;
                    return as_value_v<type>;
                } else /* if constexpr (fixed_ndarray_dim_v<array_t> >= 2) */ {
                    return as_value_v<array_t>;
                }
            } else if constexpr (is_fixed_dim_ndarray_v<array_t>) {
                if constexpr (fixed_dim_v<array_t> == 2) {
                    return as_value_v<array_t>;
                } else {
                    using element_t = get_element_type_t<array_t>;
                    using type = make_dynamic_ndarray_t<element_t>;
                    return as_value_v<type>;
                }
            } else /* if constexpr (is_dynamic_ndarray_v<array_t> || is_hybrid_ndarray_v<array_t>) */ {
                return as_value_v<array_t>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP