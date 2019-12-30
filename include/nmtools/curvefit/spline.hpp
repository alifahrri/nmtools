#ifndef NMTOOLS_SPLINE_HPP
#define NMTOOLS_SPLINE_HPP

#include "nmtools/utility.hpp"
#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
#include <tuple>

namespace nmtools
{
    namespace curvefit
    {
        namespace helper
        {
            /**
             * @brief 
             * 
             * @tparam XContainer 
             * @tparam YContainer 
             * @param x 
             * @param y 
             * @return constexpr auto 
             * 
             * @note see chapra chapter 16.4 cubic spline
             */
            template <typename XContainer, typename YContainer>
            constexpr auto tridiag(const XContainer &x, const YContainer &y)
            {
                static_assert(
                    traits::all_iterable_v<XContainer,YContainer> && 
                    traits::all_indexable_v<XContainer,YContainer>,
                    "x and y container should be iterable and indexable"
                );
                assert(std::size(x)==std::size(y));
                using value_type = std::common_type_t<
                    typename XContainer::value_type, 
                    typename YContainer::value_type
                >;
                mpl::copy_std_container_t<XContainer, value_type> e{}, f{}, g{}, r{};
                auto n = std::size(x)-1;
                if (traits::is_resizeable<XContainer>::value) {
                    e.resize(n);
                    f.resize(n);
                    g.resize(n);
                    r.resize(n);
                }

                e[0] ;
                f[0]=2*x[2]-x[0];
                g[0]=x[2]-x[1];
                r[0]=6/(x[2]-x[1])*(y[2]-y[1]);
                r[0]=r[0]+6/(x[1]-x[0])*(y[0]-y[1]);

                for(int i=1; i<n-1; i++){
                    e[i]=(x[i]-x[i-1]);
                    f[i]=2*(x[i+1]-x[i-1]);
                    g[i]=(x[i+1]-x[i]);
                    r[i]=6/(x[i+1]-x[i])*(y[i+1]-y[i]);
                    r[i]=r[i]+6/(x[i]-x[i-1])*(y[i-1]-y[i]);
                }
                e[n-1]=x[n-1]-x[n-2];
                f[n-1]=2*(x[n]-x[n-2]);
                r[n-1]=6/(x[n]-x[n-1])*(y[n]-y[n-1]);
                r[n-1]+=6/(x[n-1]-x[n-2])*(y[n-2]-y[n-1]);

                return std::make_tuple(e,f,g,r);
            }

            template <typename EContainer, typename FContainer, typename GContainer>
            constexpr auto decomp(const EContainer &e, const FContainer &f, const GContainer &g)
            {
                using value_type = std::common_type_t<
                    typename EContainer::value_type, 
                    typename FContainer::value_type
                >;
                mpl::copy_std_container_t<EContainer, value_type> ec{};
                mpl::copy_std_container_t<FContainer, value_type> fc{};
                auto ndata = std::size(e);
                if constexpr (traits::is_resizeable<EContainer>::value)
                    ec.resize(ndata);
                if constexpr (traits::is_resizeable<FContainer>::value)
                    fc.resize(ndata);
                std::copy(std::begin(e), std::end(e), std::begin(ec));
                std::copy(std::begin(f), std::end(f), std::begin(fc));
                for (size_t i=2; i<ndata-1; i++) {
                    ec[i] = ec[i] / fc[i-1];
                    fc[i] = fc[i] - ec[i] * g[i-1];
                }
                return std::make_tuple(ec, fc);
            }

            template <typename DContainer, typename EContainer, typename FContainer, typename GContainer, typename RContainer>
            constexpr auto substitute(const EContainer &e, const FContainer &f, const GContainer &g, const RContainer &r)
            {
                DContainer d2x{};
                RContainer rc{};
                auto ndata = std::size(e);
                if constexpr (traits::is_resizeable<DContainer>::value)
                    d2x.resize(ndata);
                if constexpr (traits::is_resizeable<RContainer>::value)
                    rc.resize(ndata);
                std::copy(std::begin(r), std::end(r), std::begin(rc));
                auto n = ndata-1;
                for (size_t i=1; i<n-1; i++) 
                    rc[i] -= e[i] * rc[i-1];
                d2x[n-1] = rc[n-1] / f[n-1];
                for (size_t i=n-3; i>0; i--)
                    d2x[i] = (rc[i]-g[i]*d2x[i+1]) / f[i];
                return std::make_tuple(rc, d2x);
            }
        } // namespace helper

        template <typename XContainer, typename YContainer, typename EContainer, typename FContainer, 
            typename GContainer, typename RContainer, typename DContainer, typename Scalar>
        constexpr auto cubic_spline(const XContainer &x, const YContainer &y, const EContainer &e, const FContainer &f, 
            const GContainer &g, const RContainer &r, const DContainer &d2x, const Scalar &s)
        {
            static_assert(
                traits::all_iterable_v<XContainer,YContainer,EContainer,GContainer,RContainer,DContainer> &&
                traits::all_indexable_v<XContainer,YContainer,EContainer,GContainer,RContainer,DContainer>,
                "expects all container params is iterable and indexable"
            );
            assert(s>=x.front() && s<=x.back());
            assert(std::size(x)==std::size(y));
            auto ndata = std::size(x);
            auto xu = s;
            Scalar result{};
            for (size_t i=1; i<ndata; i++) {
                if (s>=x[i-1] && s<=x[i]) {
                    auto c1=d2x[i-1]/6/(x[i]-x[i-1]);
                    auto c2=d2x[i]/6/(x[i]-x[i-1]);
                    auto c3=y[i-1]/(x[i]-x[i-1])-d2x[i-1]*(x[i]-x[i-1])/6;
                    auto c4=y[i]/(x[i]-x[i-1])-d2x[i]*(x[i]-x[i-1])/6;
                    auto t1=c1*pow(x[i]-xu,3);
                    auto t2=c2*pow(xu-x[i-1],3);
                    auto t3=c3*(x[i]-xu);
                    auto t4=c4*(xu-x[i-1]);
                    result=t1+t2+t3+t4;
                    break;
                }
            }
            return result;
        }
        
        template <typename XContainer, typename YContainer, typename TContainer>
        constexpr auto cubic_spline(const XContainer &x, const YContainer &y, const TContainer &t)
        {
            assert(std::size(x)==std::size(y));
            using value_type = std::common_type_t<
                typename XContainer::value_type,
                typename YContainer::value_type,
                typename TContainer::value_type
            >;
            using result_t = mpl::copy_std_container_t<YContainer, value_type>;
            result_t results{};
            if (traits::is_resizeable<YContainer>::value) 
                results.resize(std::size(t));
            
            auto [e, f, g, r] = helper::tridiag(x,y);
            auto [ec, fc] = helper::decomp(e,f,g);
            auto [rc, d2x] = helper::substitute<result_t>(ec, fc, g, r);

            for (size_t i=0; i<std::size(t); i++)
                results[i] = cubic_spline(x, y, ec, fc, g, rc, d2x, t[i]);
            return results;
        }
    } // namespace curvefit
    
} // namespace nmtools

#endif // NMTOOLS_SPLINE_HPP