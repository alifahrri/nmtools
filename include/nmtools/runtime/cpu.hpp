#ifndef NMTOOLS_RUNTIME_CPU_HPP
#define NMTOOLS_RUNTIME_CPU_HPP

#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/cpu/add.hpp"
#include "nmtools/runtime/cpu/multiply.hpp"
#include "nmtools/runtime/cpu/subtract.hpp"
#include "nmtools/runtime/cpu/divide.hpp"

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
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_IMPLEMENTATION
#include "nmtools/core/transform/gvn.hpp"

namespace nmtools::runtime
{
    cpu::cpu()
    {
        append_functor<cpu_add>();
        append_functor<cpu_multiply>();
        append_functor<cpu_subtract>();
        append_functor<cpu_divide>();
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