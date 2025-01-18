#ifndef NMTOOLS_ARRAY_VIEW_TAKE_ALONG_AXIS_HPP
#define NMTOOLS_ARRAY_VIEW_TAKE_ALONG_AXIS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/take_along_axis.hpp"
#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/index/insert_index.hpp"
#include "nmtools/array/slice.hpp"
#include "nmtools/array/flatten.hpp"
#include "nmtools/core/mutable_slice.hpp"
#include "nmtools/core/mutable_flatten.hpp"
#include "nmtools/core/discrete.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/array/broadcast_arrays.hpp"
#include "nmtools/utility/apply_resize.hpp"

#include "nmtools/array/index/split.hpp"

namespace nmtools::view
{
    /**
     * @brief Create take along axis view.
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @tparam dst_shape_t 
     */
    template <typename array_t, typename indices_t, typename axis_t, typename dst_shape_t>
    struct take_along_axis_t
    {
        using array_type     = resolve_array_type_t<array_t>;
        using indices_type   = resolve_array_type_t<indices_t>;
        using dst_shape_type = resolve_attribute_type_t<dst_shape_t>;
        using src_shape_type = decltype(shape(meta::declval<array_t>()));
        using axis_type      = const axis_t;

        array_type     array;
        indices_type   indices;
        dst_shape_type dst_shape;
        src_shape_type src_shape;
        axis_type      axis;


        constexpr take_along_axis_t(const array_t& array, const indices_t& indices, axis_t axis, const dst_shape_t& dst_shape)
            : array(initialize<array_type>(array))
            , indices(initialize<indices_type>(indices))
            , dst_shape(init_attribute<dst_shape_type>(dst_shape))
            , src_shape(shape(array))
            , axis(axis)
        {}

        template <typename output_t>
        constexpr auto eval(output_t& output) const
        {
            // TODO: check if element_type of output_t is index
            if constexpr (meta::is_resizable_v<output_t>) {
                ::nmtools::detail::apply_resize(output, dst_shape);
            }

            using namespace literals;

            auto b_result = index::broadcast_shape(src_shape,detail::shape(indices));
            auto success  = static_cast<bool>(b_result);

            if (!success) {
                // abort computation
                return success;
            }

            const auto& b_shape = *b_result;
            
            auto b_indices = [&](){
                if constexpr (meta::is_pointer_v<indices_type>) {
                    return view::broadcast_to(*indices,b_shape);
                } else {
                    return view::broadcast_to(indices,b_shape);
                }
            }();
            auto b_array = [&](){
                if constexpr (meta::is_pointer_v<indices_type>) {
                    return view::broadcast_to(*array,b_shape);
                } else {
                    return view::broadcast_to(array,b_shape);
                }
            }();

            auto inner_loop = [&](const auto& slices){
                auto a_1d = view::apply_slice(b_array,*slices);
                auto indices_1d = view::apply_slice(b_indices,*slices);
                auto out_1d = view::apply_mutable_slice(output,*slices);

                auto flat_a = unwrap(view::flatten(a_1d));
                auto flat_indices = unwrap(view::flatten(indices_1d));
                auto flat_out = unwrap(view::mutable_flatten(out_1d));

                auto n = len(flat_out);
                // auto n_i = len(flat_indices);
                // TODO: better error handling
                // nmtools_cassert( (n == n_i)
                //     , "nmtools internal error, shape mismatch"
                // );

                auto success = true;
                for (size_t j=0; j<(size_t)n; j++) {
                    // TODO: error when flat_indices(i) out of bounds
                    auto idx = flat_indices(j);
                    auto val = flat_a(idx);
                    flat_out(j) = val;
                }
                return success;
            };

            auto shape_ = b_shape;
            at(shape_,axis) = at(src_shape,axis);
            const auto [Ni, M_Nk] = index::split(shape_,axis);
            const auto [M_, Nk] = index::split(M_Nk,1_ct);

            // TODO: support range-for for ndindex
            auto Ni_index = index::ndindex(Ni);
            auto Nk_index = index::ndindex(Nk);

            // unlike numpy's ndindex, this ndindex behave differently for empty shape
            // TODO: fix product to return 0 if empty
            // auto ni_size = Ni_index.size();
            // auto nk_size = Nk_index.size();

            auto ni_size = len(Ni);
            auto nk_size = len(Nk);

            if (ni_size && nk_size) {
                for (size_t i=0; i<Ni_index.size(); i++) {
                    auto ii = Ni_index[i];
                    for (size_t k=0; k<Nk_index.size(); k++) {
                        auto kk = Nk_index[k];
                        // TODO: use fixed -1
                        // auto slices_ = index::insert_index(ii,Ellipsis,meta::ct_v<-1>);
                        auto slices_ = index::insert_index(ii,Ellipsis,-1);
                        nmtools_cassert( static_cast<bool>(slices_), "nmtools internal error" );
                        // auto slices  = index::insert_index(*slices_,kk,meta::ct_v<-1>);
                        auto slices  = index::insert_index(*slices_,kk,-1);
                        nmtools_cassert( static_cast<bool>(slices), "nmtools internal error" );

                        success = success && inner_loop(slices);
                    } // Nk_index
                } // Ni_index
            } else if (!ni_size) {
                // auto ni_src = at(src_shape,axis);
                // auto all = nmtools_array<int,2>{0,-1};
                auto nk_size_ = Nk_index.size();
                for (size_t k=0; k<nk_size_; k++) {
                    auto kk = Nk_index[k];
                    // TODO: use fixed -1
                    auto slices_ = nmtools_array{Ellipsis};
                    // auto slices  = index::insert_index(*slices_,kk,meta::ct_v<-1>);
                    auto slices  = index::insert_index(slices_,kk,-1);
                    nmtools_cassert( static_cast<bool>(slices), "nmtools internal error" );

                    success = success && inner_loop(slices);
                } // Nk_index
            } else if (!nk_size) {
                // auto ni_src = at(src_shape,axis);
                // auto all = nmtools_array<int,2>{0,-1};
                auto ni_size_ = Ni_index.size();
                for (size_t i=0; i<ni_size_; i++) {
                    auto ii = Ni_index[i];
                    // TODO: use fixed -1
                    // auto slices_ = index::insert_index(ii,Ellipsis,meta::ct_v<-1>);
                    auto slices = index::insert_index(ii,Ellipsis,-1);
                    nmtools_cassert( static_cast<bool>(slices), "nmtools internal error" );

                    success = success && inner_loop(slices);
                } // Ni_index
            }

            return success;
        } // eval
    }; // take_along_axis_t

    /**
     * @brief Create take_along_axis view.
     * Take values from the input array by matching 1d index and data slices.
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @param array 
     * @param indices 
     * @param axis 
     * @return constexpr auto 
     */
    template <typename array_t, typename indices_t, typename axis_t>
    constexpr auto take_along_axis(const array_t& array, const indices_t& indices, axis_t axis)
    {
        auto dst_shape = index::shape_take_along_axis(shape(array),shape(indices),axis);
        using dst_shape_t = meta::get_maybe_type_t<decltype(dst_shape)>;

        // NOTE: broadcasting at eval (see above)
        using view_t = discrete_t<take_along_axis_t,array_t,indices_t,axis_t,dst_shape_t>;
        using return_t = nmtools_maybe<view_t>;
        if (static_cast<bool>(dst_shape)) {
            return return_t{view_t{{array,indices,axis,*dst_shape}}};
        } else {
            return return_t{}; // Nothing
        }
    } // take_along_axis

} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_TAKE_ALONG_AXIS_HPP