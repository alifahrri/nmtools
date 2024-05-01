#ifndef NMTOOLS_ARRAY_VIEW_BATCH_NORM_HPP
#define NMTOOLS_ARRAY_VIEW_BATCH_NORM_HPP

#include "nmtools/array/view/atleast_3d.hpp"
#include "nmtools/array/view/moveaxis.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"

#include "nmtools/meta.hpp"

namespace nmtools::view
{
    /**
     * @brief create a view that applies Batch Normalization for each channel across a batch of data.
     * 
     * @tparam input_t 
     * @tparam mean_t 
     * @tparam var_t 
     * @tparam weight_t 
     * @tparam bias_t 
     * @tparam epsilon_t 
     * @param input     input array with shape (N,C,H,W)
     * @param mean      (estimated) mean array with shape (C)
     * @param var       (estimated) var array with shape (C)
     * @param weight    a.k.a. scale with shape (C)
     * @param bias      bias with shape (C)
     * @param eps       epsilon value to use to avoid division by zero.
     * @return constexpr auto 
     */
    template <typename input_t, typename mean_t, typename var_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto batch_norm(const input_t& input, const mean_t& mean, const var_t& var, const weight_t& weight, const bias_t& bias, epsilon_t eps=epsilon_t{1e-5})
    {
        // assume only 2D for now
        // TODO: support 1D & 3D
        // assume NCHW or CHW
        // TODO: support NHWC

        // not supported yet
        // TODO: support moveaxis with compile-time axis
        auto src_axis = meta::ct_v<-1>;
        auto dst_axis = meta::ct_v<-3>;

        auto weight_ = view::moveaxis(view::atleast_3d(weight),src_axis,dst_axis);
        auto bias_   = view::moveaxis(view::atleast_3d(bias),src_axis,dst_axis);
        auto mean_   = view::moveaxis(view::atleast_3d(mean),src_axis,dst_axis);
        auto var_    = view::moveaxis(view::atleast_3d(var),src_axis,dst_axis);
        auto stddev_ = view::sqrt(view::add(var_,eps));

        auto subtracted = view::subtract(input,mean_);
        auto divided    = view::divide(subtracted,stddev_);
        auto multiplied = view::multiply(divided,weight_);
        return view::add(multiplied,bias_);
    } // batch_norm
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BATCH_NORM_HPP