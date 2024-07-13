#ifndef NMTOOLS_ARRAY_VIEW_INSTANCE_NORM_HPP
#define NMTOOLS_ARRAY_VIEW_INSTANCE_NORM_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/array/view/mean.hpp"
#include "nmtools/array/view/var.hpp"
#include "nmtools/array/view/atleast_nd.hpp"
#include "nmtools/array/view/moveaxis.hpp"

namespace nmtools::view
{
    template <typename input_t, typename weight_t, typename bias_t, typename nd_t, typename epsilon_t=float>
    constexpr auto instance_norm(const input_t& input, const weight_t& weight, const bias_t& bias, nd_t, epsilon_t epsilon=epsilon_t{1e-5})
    {
        constexpr int ND = nd_t::value;
        static_assert( meta::is_constant_index_v<nd_t>
            , "invalid nd type for instance_norm, can only support constant index");
        static_assert( ND > 0
            , "invalid dimension for instance_norm" );

        auto src_axis = meta::ct_v<-1>;
        auto dst_axis = meta::ct_v<-ND-1>;
        auto dim  = meta::ct_v<ND+1>;
        auto axis = meta::template_reduce<ND>([&](auto init, auto index){
            constexpr int axis = -(int)ND + (int)index;
            return utility::tuple_append(init,meta::ct_v<axis>);
        }, nmtools_tuple{});

        auto aliased  = view::aliased(input,weight,bias);
        auto a_input  = nmtools::get<0>(aliased);
        auto a_weight = view::moveaxis(view::atleast_nd(nmtools::get<1>(aliased),dim),src_axis,dst_axis);
        auto a_bias   = view::moveaxis(view::atleast_nd(nmtools::get<2>(aliased),dim),src_axis,dst_axis);

        auto dtype = None;
        auto ddof  = 0;
        auto keepdims = True;

        auto mean  = view::mean(a_input,axis,dtype,keepdims);
        auto shift = view::subtract(a_input,mean);

        auto var  = view::var(a_input,axis,dtype,ddof,keepdims);
        auto std  = view::sqrt(view::add(var,epsilon));
        auto norm = view::divide(shift,std);
        return view::add(view::multiply(norm,a_weight),a_bias);
    }

    template <typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto instance_norm_1d(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5})
    {
        return view::instance_norm(input,weight,bias,meta::ct_v<1>,epsilon);
    }

    template <typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto instance_norm_2d(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5})
    {
        return view::instance_norm(input,weight,bias,meta::ct_v<2>,epsilon);
    }

    template <typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto instance_norm_3d(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5})
    {
        return view::instance_norm(input,weight,bias,meta::ct_v<3>,epsilon);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_INSTANCE_NORM_HPP