#ifndef NMTOOLS_RUNTIME_CPU_HPP
#define NMTOOLS_RUNTIME_CPU_HPP

#include "nmtools/runtime/context.hpp"

namespace nmtools::runtime
{
    class cpu : public base_context
    {
    public:
        using functor_ptr_type     = ::std::shared_ptr<base_functor>;
        using functors_type        = nmtools_list<functor_ptr_type>;
        using functors_hashes_type = nmtools_list<nm_size_t>;
    private:
        functors_type        functors_;
        functors_hashes_type hashes_;
    public:
        cpu();
        auto functors() const noexcept -> functors_type override;
        auto eval(const ndarray&) -> ndarray override;

        // TODO: move to base class?
        auto hashes() const noexcept -> functors_hashes_type;
        auto get_functor(const Graph& g) const -> functor_ptr_type;

        template <typename functor>
        auto append_functor()
        {
            constexpr auto N = len_v<decltype(functor::types)>;
            template_for<N>([&](auto i){
                const auto [lhs,rhs] = at(functor::types,i);
                const auto lhs_rtype = to_value_v<decltype(lhs)>;
                const auto rhs_rtype = to_value_v<decltype(rhs)>;
                auto fn = ::std::make_shared<functor>(lhs_rtype,rhs_rtype);
                functors_.push_back(fn);
                hashes_.push_back(fn->hash());
            });
        }

        template <typename functor>
        auto append_reduce_functor()
        {
            constexpr auto N = len_v<decltype(functor::types)>;
            template_for<N>([&](auto i){
                const auto dtype = at(functor::types,i);
                const auto rtype = to_value_v<decltype(dtype)>;

                auto fn = ::std::make_shared<functor>(rtype,false);
                functors_.push_back(fn);
                hashes_.push_back(fn->hash());

                fn = ::std::make_shared<functor>(rtype,true);
                functors_.push_back(fn);
                hashes_.push_back(fn->hash());
            });
        }

        template <typename functor>
        auto append_unary_functor()
        {
            constexpr auto N = len_v<decltype(functor::types)>;
            template_for<N>([&](auto i){
                const auto dtype = at(functor::types,i);

                auto fn = ::std::make_shared<functor>(static_cast<DType>(dtype));
                functors_.push_back(fn);
                hashes_.push_back(fn->hash());
            });
        }
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_IMPLEMENTATION
#include "nmtools/core/transform/gvn.hpp"
#include "nmtools/runtime/cpu/add.hpp"
#include "nmtools/runtime/cpu/multiply.hpp"
#include "nmtools/runtime/cpu/subtract.hpp"
#include "nmtools/runtime/cpu/divide.hpp"
#include "nmtools/runtime/cpu/sum.hpp"
#include "nmtools/runtime/cpu/prod.hpp"
#include "nmtools/runtime/cpu/cos.hpp"
#include "nmtools/runtime/cpu/cosh.hpp"
#include "nmtools/runtime/cpu/sin.hpp"
#include "nmtools/runtime/cpu/sinh.hpp"
#include "nmtools/runtime/cpu/exp.hpp"
#include "nmtools/runtime/cpu/exp2.hpp"
#include "nmtools/runtime/cpu/expm1.hpp"
#include "nmtools/runtime/cpu/fabs.hpp"
#include "nmtools/runtime/cpu/floor.hpp"
#include "nmtools/runtime/cpu/invert.hpp"
#include "nmtools/runtime/cpu/isfinite.hpp"
#include "nmtools/runtime/cpu/isinf.hpp"
#include "nmtools/runtime/cpu/isnan.hpp"
#include "nmtools/runtime/cpu/log.hpp"
#include "nmtools/runtime/cpu/log1p.hpp"
#include "nmtools/runtime/cpu/log2.hpp"
#include "nmtools/runtime/cpu/log10.hpp"
#include "nmtools/runtime/cpu/negative.hpp"
#include "nmtools/runtime/cpu/reciprocal.hpp"
#include "nmtools/runtime/cpu/rint.hpp"
#include "nmtools/runtime/cpu/signbit.hpp"
#include "nmtools/runtime/cpu/sqrt.hpp"
#include "nmtools/runtime/cpu/square.hpp"
#include "nmtools/runtime/cpu/tan.hpp"
#include "nmtools/runtime/cpu/tanh.hpp"
#include "nmtools/runtime/cpu/trunc.hpp"
#include "nmtools/runtime/cpu/arccos.hpp"
#include "nmtools/runtime/cpu/arccosh.hpp"
#include "nmtools/runtime/cpu/arcsin.hpp"
#include "nmtools/runtime/cpu/arcsinh.hpp"
#include "nmtools/runtime/cpu/arctan.hpp"
#include "nmtools/runtime/cpu/arctanh.hpp"
#include "nmtools/runtime/cpu/cbrt.hpp"
#include "nmtools/runtime/cpu/ceil.hpp"

#include "nmtools/runtime/cpu/bitwise_and.hpp"
#include "nmtools/runtime/cpu/bitwise_or.hpp"
#include "nmtools/runtime/cpu/bitwise_xor.hpp"
#include "nmtools/runtime/cpu/equal.hpp"
#include "nmtools/runtime/cpu/greater_equal.hpp"
#include "nmtools/runtime/cpu/greater.hpp"
#include "nmtools/runtime/cpu/fmax.hpp"
#include "nmtools/runtime/cpu/fmin.hpp"
#include "nmtools/runtime/cpu/fmod.hpp"
#include "nmtools/runtime/cpu/hypot.hpp"
#include "nmtools/runtime/cpu/ldexp.hpp"
#include "nmtools/runtime/cpu/less_equal.hpp"
#include "nmtools/runtime/cpu/less.hpp"
#include "nmtools/runtime/cpu/left_shift.hpp"
#include "nmtools/runtime/cpu/right_shift.hpp"
#include "nmtools/runtime/cpu/maximum.hpp"
#include "nmtools/runtime/cpu/minimum.hpp"
#include "nmtools/runtime/cpu/mod.hpp"
#include "nmtools/runtime/cpu/power.hpp"

namespace nmtools::runtime
{
    cpu::cpu()
    {
        append_functor<cpu_add>();
        append_functor<cpu_multiply>();
        append_functor<cpu_subtract>();
        append_functor<cpu_divide>();
        append_functor<cpu_bitwise_and>();
        append_functor<cpu_bitwise_or>();
        append_functor<cpu_bitwise_xor>();
        append_functor<cpu_equal>();
        append_functor<cpu_greater_equal>();
        append_functor<cpu_greater>();
        append_functor<cpu_fmax>();
        append_functor<cpu_fmin>();
        append_functor<cpu_fmod>();
        append_functor<cpu_hypot>();
        append_functor<cpu_ldexp>();
        append_functor<cpu_left_shift>();
        append_functor<cpu_less_equal>();
        append_functor<cpu_less>();
        append_functor<cpu_right_shift>();
        append_functor<cpu_maximum>();
        append_functor<cpu_minimum>();
        append_functor<cpu_mod>();
        append_functor<cpu_power>();

        append_reduce_functor<cpu_sum>();
        append_reduce_functor<cpu_prod>();

        append_unary_functor<cpu_cos>();
        append_unary_functor<cpu_cosh>();
        append_unary_functor<cpu_sin>();
        append_unary_functor<cpu_sinh>();
        append_unary_functor<cpu_exp>();
        append_unary_functor<cpu_exp2>();
        append_unary_functor<cpu_expm1>();
        append_unary_functor<cpu_fabs>();
        append_unary_functor<cpu_floor>();
        append_unary_functor<cpu_invert>();
        append_unary_functor<cpu_isfinite>();
        append_unary_functor<cpu_isinf>();
        append_unary_functor<cpu_isnan>();
        append_unary_functor<cpu_log>();
        append_unary_functor<cpu_log1p>();
        append_unary_functor<cpu_log2>();
        append_unary_functor<cpu_log10>();
        append_unary_functor<cpu_negative>();
        append_unary_functor<cpu_reciprocal>();
        append_unary_functor<cpu_rint>();
        append_unary_functor<cpu_signbit>();
        append_unary_functor<cpu_sqrt>();
        append_unary_functor<cpu_square>();
        append_unary_functor<cpu_tan>();
        append_unary_functor<cpu_tanh>();
        append_unary_functor<cpu_trunc>();
        append_unary_functor<cpu_arccos>();
        append_unary_functor<cpu_arccosh>();
        append_unary_functor<cpu_arcsin>();
        append_unary_functor<cpu_arcsinh>();
        append_unary_functor<cpu_arctan>();
        append_unary_functor<cpu_arctanh>();
        append_unary_functor<cpu_cbrt>();
        append_unary_functor<cpu_ceil>();
    }

    auto cpu::functors() const noexcept -> nmtools_list<functor_ptr_type>
    {
        return functors_;
    }

    auto cpu::hashes() const noexcept -> cpu::functors_hashes_type
    {
        return hashes_;
    }

    auto cpu::eval(const ndarray& array) -> ndarray
    {
        auto graph = array.graph();

        // TODO: implement
        nmtools_panic( false
            , "cpu::eval not implemented"
        );
        return ndarray(IndexType{},DType::UNKNOWN);
    }

    auto cpu::get_functor(const Graph& g) const -> cpu::functor_ptr_type
    {
        // TODO: check if acyclic
        // TODO: check if only single output
        // nodes
        auto gvn  = functional::gvn(g,false,false);
        auto hash = gvn.at(output_id(g));

        auto idx = 0ul;
        for (const auto h : this->hashes()) {
            if (h == hash) {
                break;
            }
            idx++;
        }

        nmtools_panic( idx < this->functors_.size()
            , "unsupported graph for cpu context"
        );

        return functors().at(idx);
    }
}
#endif // NMTOOLS_RUNTIME_CPU_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_CPU_HPP