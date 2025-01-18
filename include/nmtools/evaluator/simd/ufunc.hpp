#ifndef NMTOOLS_ARRAY_EVAL_SIMD_OP_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_OP_HPP

#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/array/view/ufuncs/ceil.hpp"
#include "nmtools/array/view/ufuncs/floor.hpp"
#include "nmtools/array/view/ufuncs/reciprocal.hpp"
#include "nmtools/array/view/activations/hardtanh.hpp"
#include "nmtools/array/view/activations/hardshrink.hpp"
#include "nmtools/array/view/activations/hardswish.hpp"
#include "nmtools/array/view/activations/leaky_relu.hpp"
#include "nmtools/array/view/activations/prelu.hpp"
#include "nmtools/array/view/activations/relu.hpp"
#include "nmtools/array/view/activations/relu6.hpp"
#include "nmtools/array/view/activations/softshrink.hpp"
#include "nmtools/array/view/activations/softsign.hpp"

#ifndef NMTOOLS_ALWAYS_INLINE
#define NMTOOLS_ALWAYS_INLINE __attribute__((always_inline))
#endif // NMTOOLS_ALWAYS_INLINE

namespace nmtools::array::simd
{
    template <typename simd_tag_t, typename data_t, typename=void>
    struct simd_op_t
    {
        NMTOOLS_ALWAYS_INLINE auto loadu(const data_t*) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto storeu(data_t*, packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto sqrt(packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto ceil(packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto floor(packed_t) const noexcept;
        NMTOOLS_ALWAYS_INLINE auto set1(data_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto max(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto min(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto cmpge(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto mul(packed_t,packed_t) const noexcept;
        template <typename packed_t,typename mask_t>
        NMTOOLS_ALWAYS_INLINE auto blendv(packed_t,packed_t,mask_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto add(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto sub(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto cmple(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto cmpgt(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto cmplt(packed_t,packed_t) const noexcept;
        // to avoid using 'and' or 'or' which is c++ keyword
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto logical_and(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto logical_or(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto div(packed_t,packed_t) const noexcept;
        template <typename packed_t>
        NMTOOLS_ALWAYS_INLINE auto fmadd(packed_t,packed_t,packed_t) const noexcept;
    }; // struct simd_op_t

    template <typename ufunc_op_t, typename simd_tag_t, typename data_t>
    struct ufunc_simd_t;

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::sqrt_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        // NOTE: use deduction because simd_t can't have member alias to avoid warning
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::sqrt_t;

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            return simd_t::sqrt(a);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::ceil_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::ceil_t;

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            return simd_t::ceil(a);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::floor_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::floor_t;

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            return simd_t::floor(a);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::relu_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::relu_t;

        const simd_dtype_t zero = simd_t::set1(0);

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            return simd_t::max(a,zero);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::relu6_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::relu6_t;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t six  = simd_t::set1(6);

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            return simd_t::max(simd_t::min(a,six),zero);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t, typename min_val_t, typename max_val_t>
    struct ufunc_simd_t<view::hardtanh_t<min_val_t,max_val_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::hardtanh_t<min_val_t,max_val_t>;

        const simd_dtype_t min_val;
        const simd_dtype_t max_val;

        ufunc_simd_t(ufunc_op_t op)
            : min_val(simd_t::set1(op.min_val))
            , max_val(simd_t::set1(op.max_val))
        {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            return simd_t::min(simd_t::max(a,min_val),max_val);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t, typename negative_slope_t>
    struct ufunc_simd_t<view::leaky_relu_t<negative_slope_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::leaky_relu_t<negative_slope_t>;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t negative_slope;

        ufunc_simd_t(ufunc_op_t op)
            : negative_slope(simd_t::set1(op.negative_slope))
        {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            const auto mask  = simd_t::cmpge(a,zero);
            const auto leaky = simd_t::mul(a,negative_slope);
            return simd_t::blendv(leaky,a,mask);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t,typename alpha_t>
    struct ufunc_simd_t<view::prelu_t<alpha_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::prelu_t<alpha_t>;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t alpha;

        ufunc_simd_t(ufunc_op_t op)
            : alpha(simd_t::set1(op.alpha))
        {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            const auto mask  = simd_t::cmpge(a,zero);
            const auto prelu = simd_t::mul(a,alpha);
            return simd_t::blendv(prelu,a,mask);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t, typename lambda_t>
    struct ufunc_simd_t<view::softshrink_t<lambda_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::softshrink_t<lambda_t>;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t pos_lambda;
        const simd_dtype_t neg_lambda;

        ufunc_simd_t(ufunc_op_t op)
            : pos_lambda(simd_t::set1(op.lambda))
            , neg_lambda(simd_t::set1(-op.lambda))
        {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            const auto x_add_lambda = simd_t::add(a,pos_lambda);
            const auto x_sub_lambda = simd_t::sub(a,pos_lambda);

            const auto gt_neg_lambda = simd_t::cmpge(a,neg_lambda);
            const auto lt_pos_lambda = simd_t::cmple(a,pos_lambda);

            const auto zero_mask    = simd_t::logical_and(gt_neg_lambda,lt_pos_lambda);
            const auto nonzero_mask = simd_t::logical_or(gt_neg_lambda,lt_pos_lambda);

            const auto pos_mask = simd_t::logical_and(nonzero_mask,simd_t::cmpgt(a,pos_lambda));
            const auto neg_mask = simd_t::logical_and(nonzero_mask,simd_t::cmplt(a,neg_lambda));

            a = simd_t::blendv(a,zero,zero_mask);
            a = simd_t::blendv(a,x_sub_lambda,pos_mask);
            a = simd_t::blendv(a,x_add_lambda,neg_mask);
            return a;
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::softsign_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::softsign_t;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t neg_one = simd_t::set1(-1);
        const simd_dtype_t pos_one = simd_t::set1(1);

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            const auto mul_neg_one = simd_t::mul(a,neg_one);
            const auto gt_zero = simd_t::cmpgt(a,zero);
            const auto abs_x   = simd_t::blendv(mul_neg_one,a,gt_zero);
            const auto y = simd_t::add(pos_one,abs_x);
            const auto z = simd_t::div(a,y);
            return z;
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t, typename lambda_t>
    struct ufunc_simd_t<view::hardshrink_t<lambda_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::hardshrink_t<lambda_t>;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t pos_lambda;
        const simd_dtype_t neg_lambda;

        ufunc_simd_t(ufunc_op_t op)
            : pos_lambda(simd_t::set1(op.lambda))
            , neg_lambda(simd_t::set1(-op.lambda))
        {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            const auto zero_mask = simd_t::logical_and(simd_t::cmpge(a,neg_lambda),simd_t::cmple(a,pos_lambda));
            return simd_t::blendv(a,zero,zero_mask);
        }
    }; // ufunc_simd_t

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::hardswish_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::hardswish_t;

        const simd_dtype_t zero  = simd_t::set1(0);
        const simd_dtype_t six   = simd_t::set1(6);
        const simd_dtype_t three = simd_t::set1(3);
        const simd_dtype_t neg_three = simd_t::set1(-3);

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {}

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            const auto inter_val = simd_t::div(simd_t::mul(a,simd_t::add(a,three)),six);

            const auto inter_mask = simd_t::logical_and(simd_t::cmplt(a,three),simd_t::cmpge(a,neg_three));
            const auto zero_mask  = simd_t::cmplt(a,neg_three);

            const auto x = simd_t::blendv(a,zero,zero_mask);
            return simd_t::blendv(x,inter_val,inter_mask);
        }
    };

    template <typename simd_tag_t, typename data_t, typename lhs_t, typename rhs_t, typename res_t>
    struct ufunc_simd_t<view::add_t<lhs_t,rhs_t,res_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t       = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(data_t{0}));
        using ufunc_op_t   = view::add_t<lhs_t,rhs_t,res_t>;

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {}

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t lhs, simd_dtype_t rhs) const noexcept
        {
            return simd_t::add(lhs,rhs);
        }
    };

    template <typename simd_tag_t, typename data_t, typename lhs_t, typename rhs_t, typename res_t>
    struct ufunc_simd_t<view::multiply_t<lhs_t,rhs_t,res_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t       = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(data_t{0}));
        using ufunc_op_t   = view::multiply_t<lhs_t,rhs_t,res_t>;

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {}

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t lhs, simd_dtype_t rhs) const noexcept
        {
            return simd_t::mul(lhs,rhs);
        }
    };

    template <typename simd_tag_t, typename data_t, typename lhs_t, typename rhs_t, typename res_t>
    struct ufunc_simd_t<view::subtract_t<lhs_t,rhs_t,res_t>,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t       = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(data_t{0}));
        using ufunc_op_t   = view::subtract_t<lhs_t,rhs_t,res_t>;

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {}

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t lhs, simd_dtype_t rhs) const noexcept
        {
            return simd_t::sub(lhs,rhs);
        }
    };

    template <typename simd_tag_t, typename data_t>
    struct ufunc_simd_t<view::divide_t,simd_tag_t,data_t> : simd_op_t<simd_tag_t,data_t>
    {
        using simd_t       = simd_op_t<simd_tag_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(data_t{0}));
        using ufunc_op_t   = view::divide_t;

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {}

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t lhs, simd_dtype_t rhs) const noexcept
        {
            return simd_t::div(lhs,rhs);
        }
    };
} // namespace nmtools::array::simd

#endif // NMTOOLS_ARRAY_EVAL_SIMD_OP_HPP