#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_3D_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_3D_HPP

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
    struct atleast_3d_t
    {
        // TODO: consider to copy when array_t is simply arithmetic type
        using array_type = const array_t&;

        array_type array;

        constexpr atleast_3d_t(array_type array)
            : array(array) {}
        
        constexpr auto shape() const
        {
            // arithmetic type
            if constexpr (std::is_arithmetic_v<array_t>)
                return std::array{1ul,1ul,1ul};
            // check if fixed 1d array
            else if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
                using namespace nmtools::literals;
                auto shape_ = ::nmtools::shape(array);
                constexpr auto dim_ = meta::fixed_dim_v<array_t>;
                if constexpr (dim_ == 1)
                    return index::expand_dims(shape_,std::tuple{0_ct,1_ct});
                else if constexpr (dim_ == 2)
                    return index::expand_dims(shape_,0_ct);
                // referenced array is atleast 2d
                else return shape_;
            }
            // assume dynamic dim
            else {
                // assume std::vector is available
                static_assert (NMTOOLS_HAS_VECTOR);
                auto shape_ = ::nmtools::shape(array);
                auto dim_   = ::nmtools::dim(array);

                using shape_t = decltype(shape_);
                auto rshape = shape_t{};
                // prepend
                if (dim_ == 1)
                    index::impl::expand_dims(rshape,shape_,std::array{0ul,1ul});
                else if (dim_ == 2)
                    index::impl::expand_dims(rshape,shape_,std::array{0ul});
                else rshape = shape_;
                return rshape;
            }
        } // shape

        constexpr auto dim() const
        {
            if constexpr (std::is_arithmetic_v<array_t>)
                return 3ul;
            else {
                auto dim_ = ::nmtools::dim(array);
                return dim_ < 3 ? 3 : dim_;
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
    }; // atleast_3d_t

    /**
     * @brief Create a atleast_3d_t view to a given array.
     * 
     * Views array with at least 3 dimension. Also accept scalar value.
     *
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto atleast_3d(const array_t& array)
    {
        using view_t = decorator_t<atleast_3d_t, array_t>;
        return view_t{{array}};
    } // atleast_3d
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t>
    struct get_element_type< view::decorator_t<view::atleast_3d_t, array_t> >
    {
        using type = std::conditional_t<
            std::is_arithmetic_v<array_t>, array_t,
            get_element_type_t<array_t>
        >;
    };

    template <typename array_t>
    struct fixed_matrix_size< view::atleast_3d_t<array_t> >
    {
        static constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    template <typename array_t>
    struct fixed_vector_size< view::atleast_3d_t<array_t> >
    {
        static constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    template <typename array_t>
    struct fixed_ndarray_shape< view::atleast_3d_t<array_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (std::is_arithmetic_v<array_t>)
                return std::array{1ul,1ul,1ul};
            else if constexpr (is_fixed_size_ndarray_v<array_t>) {
                constexpr auto dim_ = fixed_ndarray_dim_v<array_t>;
                constexpr auto shape_ = fixed_ndarray_shape_v<array_t>;
                if constexpr (dim_ == 1)
                    return index::expand_dims(shape_,std::array{0,1});
                else if constexpr (dim_ == 2)
                    return index::expand_dims(shape_,0);
                else return shape_;
            }
            else return fixed_ndarray_shape_v<array_t>;
        }();
        using value_type = decltype(value);
    };

    template <typename array_t>
    struct is_ndarray< view::decorator_t< view::atleast_3d_t, array_t >>
    {
        static constexpr auto value = std::is_arithmetic_v<array_t> || is_ndarray_v<array_t>;
    };

    /**
     * @brief specialization of eval type resolver for atleast_3d view.
     * 
     * @tparam array_t 
     * @note this specialization is provided since no actual type
     *      with fixed-dim dynamic-size trait is available, while such array is needed for this view.
     * @todo add fixed-dim dynamic-size ndarray and remove this specialization.
     */
    template <typename array_t>
    struct resolve_optype<
        void, array::eval_t, view::decorator_t< view::atleast_3d_t, array_t >, none_t
    >
    {
        // deduce the type,
        // for now only check for fixed-size ndarray
        // not yet decided what to do for hybrid ndarray or nested view
        static constexpr auto vtype = [](){
            if constexpr (is_num_v<array_t>) {
                using shape_t = std::tuple<ct<1>,ct<1>,ct<1>>;
                using type = make_fixed_ndarray_t<array_t,shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_size_ndarray_v<array_t>) {
                constexpr auto dim_ = fixed_ndarray_dim_v<array_t>;
                constexpr auto shape_ = fixed_ndarray_shape_v<array_t>;
                if constexpr (dim_ == 1) {
                    using some_array_t = int[1][1][nmtools::at(shape_,0)];
                    using tf_array_t   = transform_bounded_array_t<array_t>;
                    using type = resize_fixed_ndarray_t<tf_array_t,some_array_t>;
                    return as_value_v<type>;
                } else if constexpr (dim_ == 2) {
                    constexpr auto dim0 = nmtools::at(shape_,0);
                    constexpr auto dim1 = nmtools::at(shape_,1);
                    using some_array_t = int[1][dim0][dim1];
                    using tf_array_t   = transform_bounded_array_t<array_t>;
                    using type = resize_fixed_ndarray_t<tf_array_t,some_array_t>;
                    return as_value_v<type>;
                } else /* if constexpr (dim >= 3) */ {
                    // already 3+ dim, no transformation needed
                    using type = array_t;
                    return as_value_v<type>;
                }
            } else if constexpr (is_fixed_dim_ndarray_v<array_t>) {
                if constexpr (fixed_dim_v<array_t> == 3) {
                    return as_value_v<array_t>;
                } else {
                    using element_t = get_element_type_t<array_t>;
                    using type = make_dynamic_ndarray_t<element_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = array_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_3D_HPP