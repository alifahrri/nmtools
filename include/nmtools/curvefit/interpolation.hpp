#ifndef NMTOOLS_SPLINE_HPP
#define NMTOOLS_SPLINE_HPP

#include "nmtools/linalg/elimination.hpp"
#include "nmtools/linalg/matvec.hpp"
#include "nmtools/utility/tag.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
#include <tuple>

namespace nmtools::curvefit
{
    using std::tuple_size_v;

    namespace detail {

        /**
         * @brief helper alias template to add specialization 
         * (which check if we can replace template parameters of T with Args...)
         * to overload set
         * 
         * @tparam T type to check
         * @tparam Args args for substitution
         */
        template <typename T, typename...Args>
        using enable_if_tparam_replaceable_t = std::enable_if_t<!std::is_same_v<meta::replace_tparam_t<T,Args...>,void>>;

        /**
         * @brief metafunction to update size of array T with new_size
         * if T has fixed size, has member type 'type' 
         * with updated array with new size if T is fixed,
         * has type == T otherwise
         * 
         * @tparam T vector-like which its size is to be updated
         * @tparam value_t currently needed as argument to meta::replace_tparam_t
         * @tparam new_size new size
         * @tparam typename=void 
         */
        template <typename T, typename value_t, typename new_size, typename=void>
        struct update_size_if_fixed
        {
            using type = T;
        };

        /**
         * @brief specialization of update_size_if_fixed 
         * when template parameter of T is actually
         * can be replaced with value_t & new_size
         * 
         * @tparam T vector-like which its size is to be updated
         * @tparam value_t currently needed as argument to meta::replace_tparam_t
         * @tparam new_size new size
         */
        template <typename T, typename value_t, typename new_size>
        struct update_size_if_fixed<T,value_t,new_size,
            std::void_t<enable_if_tparam_replaceable_t<T,value_t,new_size>>
        >
        {
            using type = meta::replace_tparam_t<T,value_t,new_size>;
        };

        /**
         * @brief helper alias template for update_size_if_fixed
         * 
         * @tparam T 
         * @tparam value_t 
         * @tparam new_size 
         */
        template <typename T, typename value_t, typename new_size>
        using update_size_if_fixed_t = typename update_size_if_fixed<T,value_t,new_size>::type;

        /**
         * @brief metafunction to decrement size of array
         * 
         * @tparam T fixed array
         * @return constexpr auto tuple_size<T>::value - 1
         * @todo make this consteval
         */
        template <typename T>
        constexpr auto decrement_array_size()
        {
            using std::tuple_size_v;
            static_assert(traits::has_tuple_size_v<T>);
            constexpr auto size = tuple_size_v<T>;
            return size - 1;
        }

        /**
         * @brief metafunction to increment size of array
         * 
         * @tparam T fixed array
         * @return constexpr auto tuple_size<T>::value + 1
         * @todo make this consteval
         */
        template <typename T>
        constexpr auto increment_array_size()
        {
            using std::tuple_size_v;
            static_assert(traits::has_tuple_size_v<T>);
            constexpr auto size = tuple_size_v<T>;
            return size + 1;
        }

        /**
         * @brief metafunction to decrement size of fixed size array T
         * 
         * @tparam T fixed array which its size to be decremented
         * @tparam typename=void 
         */
        template <typename T, typename=void>
        struct decrement_size_if_fixed
        {
            using type = T;
        };

        /**
         * @brief specialization of metafunction decrement_size_if_fixed
         * 
         * @tparam T fixed array which its size to be decremented
         */
        template <typename T>
        struct decrement_size_if_fixed<T,std::enable_if_t<traits::has_tuple_size_v<T>>>
        {
            using element_t = traits::remove_cvref_t<typename T::value_type>;
            /* currently we need to pack value as type */
            using new_size_t = std::integral_constant<size_t,decrement_array_size<T>()>;
            using type = update_size_if_fixed_t<T,element_t,new_size_t>;
        };

        /**
         * @brief helper alias template to decrement_size_if_fixed
         * 
         * @tparam T fixed array which its size to be decremented
         */
        template <typename T>
        using decrement_size_if_fixed_t = typename decrement_size_if_fixed<T>::type;

        /**
         * @brief metafunction to increment the size of fixed array
         * 
         * @tparam T type which size to be incremented
         * @tparam typename=void 
         */
        template <typename T, typename=void>
        struct increment_if_fixed
        {
            using type = T;
        };

        /**
         * @brief specialization of increment_if_fixed when T can be actually incremented
         * 
         * @tparam T type which size to be incremented
         */
        template <typename T>
        struct increment_if_fixed<T,std::enable_if_t<traits::has_tuple_size_v<T>>>
        {
            using element_t = traits::remove_cvref_t<typename T::value_type>;
            /* currently we need to pack value as type */
            using new_size_t = std::integral_constant<size_t,increment_array_size<T>()>;
            using type = update_size_if_fixed_t<T,element_t,new_size_t>;
        };

        /**
         * @brief helper alias template for increment_if_fixed
         * 
         * @tparam T 
         */
        template <typename T>
        using increment_if_fixed_t = typename increment_if_fixed<T>::type;

        /**
         * @brief make tridiagonal system for cubic spline
         * 
         * @tparam X vector-like
         * @tparam Y vector-like
         * @param x independent variable
         * @param y dependent variable
         * @return constexpr auto [e,f,g,r]
         */
        template <typename tag_t=tag::size_assert_t, typename X, typename Y>
        constexpr auto make_tridiagonal(const X& x, const Y& y)
        {
            static_assert(
                traits::is_array1d_v<X> &&
                traits::is_array1d_v<Y>,
                "unsupported type of x & y for make_tridiagonal"
            );

            using std::tuple_size_v;

            auto nx = size(x);
            auto ny = size(y);

            /* check if size assertion should be performed */
            constexpr auto size_assert = tag::is_tag_enabled_v<tag::size_assert_t,tag_t>;
            if constexpr (size_assert) {
                /* validate assumption (nx==ny) */
                if constexpr (traits::has_tuple_size_v<X> && traits::has_tuple_size_v<Y>)
                    static_assert(tuple_size_v<X> == tuple_size_v<Y>);
                else
                    assert(nx == ny);
            }
            
            auto n = nx;

            /* type transformations */
            using x_t = meta::transform_bounded_array_t<X>;
            using y_t = meta::transform_bounded_array_t<Y>;
            using value_t  = std::common_type_t<typename x_t::value_type, typename y_t::value_type>;
            using return_t = decrement_size_if_fixed_t<meta::select_resizeable_t<x_t,y_t,x_t>>;

            /* prepare placeholder */
            return_t e{}, f{}, g{}, r{};

            /* deal with possibly runtime container */
            if constexpr (traits::is_resizeable_v<return_t>) {
                e.resize(n-1);
                f.resize(n-1);
                g.resize(n-1);
                r.resize(n-1);
            }

            constexpr auto six = static_cast<value_t>(6);
            constexpr auto two = static_cast<value_t>(2);

            /* coefficient for 1st interval */
            f[0] = two * (x[2]-x[0]);
            g[0] = x[2] - x[1];
            r[0] = six * (((y[2]-y[1]) / (x[2]-x[1])) -
                ((y[1]-y[0]) / (x[1]-x[0])));

            for (int i=1; i<(nx-2); i++) {
                auto k = i+1;
                e[i] = x[k] - x[k-1];
                f[i] = two * (x[k+1] - x[k-1]);
                g[i] = x[k+1] - x[k];
                r[i] = six * (((y[k+1]-y[k]) / (x[k+1]-x[k])) -
                    ((y[k]-y[k-1]) / (x[k]-x[k-1])));
            }

            /* coefficient for last interval */
            auto i = (nx-2);
            e[i] = x[i] - x[i-1];
            f[i] = two * (x[i+1] - x[i-1]);
            r[i] = six * (((y[i+1]-y[i]) / (x[i+1]-x[i])) -
                    ((y[i]-y[i-1]) / (x[i]-x[i-1])));
            
            return std::make_tuple(e,f,g,r);
        }

        /**
         * @brief construct callable for linear spline
         * 
         * @tparam tag_t=tag::size_assert_t
         * @tparam X vector-like
         * @tparam Y vector-like
         * @tparam M vector-like
         * @param x independent variable
         * @param y dependent variable
         * @param m gradients/slopes
         * @return constexpr auto lambda f(x) -> [fx: scalar, in_range: bool]
         */
        template <typename tag_t=tag::size_assert_t, typename X, typename Y, typename M>
        constexpr auto make_linear_spline_fn(const X& x, const Y& y, const M& m)
        {
            static_assert(
                traits::is_array1d_v<X> &&
                traits::is_array1d_v<Y> &&
                traits::is_array1d_v<M>,
                "unsupported type of x, y, or m for make_linear_spline_fn"
            );

            /* check if size assertion is enabled */
            constexpr auto size_assert = tag::is_tag_enabled_v<tag::size_assert_t,tag_t>;
            if constexpr (size_assert) {
                if constexpr (
                    traits::has_tuple_size_v<X> &&
                    traits::has_tuple_size_v<Y> &&
                    traits::has_tuple_size_v<M>
                ) /* checking can be performed at compile-time */
                {
                    constexpr auto nx = tuple_size_v<X>;
                    constexpr auto ny = tuple_size_v<Y>;
                    constexpr auto nm = tuple_size_v<M>;
                    static_assert (nx==ny && nx==(nm+1));
                }
                else /* defer checking to runtime */
                {
                    auto nx = size(x);
                    auto ny = size(y);
                    auto nm = size(m);
                    assert (nx==ny && nx==(nm+1));
                }
            }

            /* construct lambda to be returned */   
            auto f = [=](auto t){
                /* get type of t */
                using value_t = traits::remove_cvref_t<decltype(t)>;
                auto n = size(x);
                value_t fx{};
                auto in_range = t >= x[0] && t <= x[n-1];
                if (in_range)
                    for (size_t i=0; i<(n-1); i++)
                        if (t >= x[i] && t <= x[i+1]) {
                            fx = y[i] + m[i]*(t - x[i]);
                            break;
                        }
                return std::make_tuple(fx,in_range);
            };
            return f;
        }

        /**
         * @brief construct callable for cubic spline
         * 
         * @tparam tag_t=tag::size_assert_t
         * @tparam D vector-like
         * @tparam X vector-like
         * @tparam Y vector-like
         * @param x independent variable
         * @param y dependent variable
         * @param d2x 2nd-order diff
         * @return constexpr auto callable lambda f(x) -> [fx: scalar, in_range: bool]
         * @cite chapra2014numerical_cubic_splines
         */
        template <typename tag_t=tag::size_assert_t, typename D, typename X, typename Y>
        constexpr auto make_cubic_spline_fn(const X& x, const Y& y, const D& d2x)
        {
            static_assert(
                traits::is_array1d_v<X> &&
                traits::is_array1d_v<Y> &&
                traits::is_array1d_v<D>,
                "unsupported type x, y, or d2x for make_cubic_spline_fn"
            );

            using traits::remove_cvref_t;
            using traits::get_container_value_type_t;



            using d2x_t = increment_if_fixed_t<D>;
            /* get value types */
            using x_t = remove_cvref_t<get_container_value_type_t<X>>;
            using y_t = remove_cvref_t<get_container_value_type_t<Y>>;
            using d_t = remove_cvref_t<typename d2x_t::value_type>;

            /* check if size assertion is enabled */
            constexpr auto size_assert = tag::is_tag_enabled_v<tag::size_assert_t,tag_t>;
            if constexpr (size_assert) {
                if constexpr (
                    traits::has_tuple_size_v<X> &&
                    traits::has_tuple_size_v<Y> &&
                    traits::has_tuple_size_v<D>
                ) /* checking can be performed at compile-time */
                {
                    constexpr auto nx = tuple_size_v<X>;
                    constexpr auto ny = tuple_size_v<Y>;
                    constexpr auto nm = tuple_size_v<D>;
                    static_assert (nx==ny && nx==(nm+1));
                }
                else /* defer checking to runtime */
                {
                    auto nx = size(x);
                    auto ny = size(y);
                    auto nm = size(d2x);
                    assert (nx==ny && nx==(nm+1));
                }
            }

            auto nx = size(x);
            auto ny = size(y);

            /* placeholder for padded 2nd derivative, with d2x[0] = 0 */
            d2x_t d2x_pad{};
            if constexpr (traits::is_resizeable_v<d2x_t>)
                d2x_pad.resize(nx);
            for (size_t i=1; i<nx; i++)
                d2x_pad[i] = d2x[i-1];
            
            /* create callable */
            auto f = [=,n=nx,z=d2x_pad](auto t){
                /* get type of t */
                using t_t = traits::remove_cvref_t<decltype(t)>;
                /* use common type between values */
                using common_t = std::common_type_t<x_t,y_t,t_t,d_t>;
                constexpr auto six = static_cast<common_t>(6);
                auto in_range = t >= x[0] && t<= x[n-1];
                /* placeholder for results */
                auto fx = common_t{};
                /* find range */
                if (in_range)
                    for (size_t i=0; i<(n-1); i++)
                        if (t >= x[i] && t <= x[i+1]) {
                            auto h = x[i+1] - x[i];
                            fx = z[i+1] / (six*h) * pow(t-x[i],3) 
                                + z[i] / (six*h) * pow(x[i+1]-t,3)
                                + (y[i+1]/h - h*z[i+1]/six) * (t-x[i])
                                + (y[i]/h - h*z[i]/six) * (x[i+1]-t);
                            break;
                        }
                return std::make_tuple(fx,in_range);
            };
            return f;
        }
    } // namespace detail

    /**
     * @brief compute slopes
     * 
     * @tparam tag_t=tag::size_assert_t 
     * @tparam X vector-like
     * @tparam Y vector-like
     * @param x independent variables
     * @param y dependent variables
     * @return constexpr auto vector-like
     * @cite chapra2014numerical_linear_splines
     */
    template <typename tag_t=tag::size_assert_t, typename X, typename Y>
    constexpr auto compute_slopes(const X&x, const Y& y)
    {
        static_assert(
            traits::is_array1d_v<X> &&
            traits::is_array1d_v<Y>,
            "unsupported type for x & y"
        );

        /* type transformations */
        using x_t = meta::transform_bounded_array_t<X>;
        using y_t = meta::transform_bounded_array_t<Y>;
        using value_t  = std::common_type_t<typename x_t::value_type, typename y_t::value_type>;
        using return_t = detail::decrement_size_if_fixed_t<meta::select_resizeable_t<x_t,y_t,x_t>>;

        auto m = return_t{};

        auto nx = size(x);
        auto ny = size(y);

        /* check if size assertion is enabled */
        constexpr auto size_assert = tag::is_tag_enabled_v<tag::size_assert_t,tag_t>;
        if constexpr (size_assert)
        {
            if constexpr (
                traits::has_tuple_size_v<X> &&
                traits::has_tuple_size_v<Y>
            ) /* checking can be done at compile-time */
            {
                using std::tuple_size_v;
                constexpr auto nx = tuple_size_v<X>;
                constexpr auto ny = tuple_size_v<Y>;
                static_assert (nx == ny);            }
            else /* defer checking to runtime */
                assert (nx == ny);
        }

        if constexpr (traits::is_resizeable_v<return_t>)
            m.resize(nx-1);
        
        for (size_t i=0; i<(nx-1); i++)
            m[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]);

        return m;
    }

    /**
     * @brief construct callable cubic-spline intepolation fn
     * 
     * @tparam tag_t=tag::no_assert_t 
     * @tparam X vector-like
     * @tparam Y vector-like
     * @param x independent variable
     * @param y dependent variable
     * @return constexpr auto callable f(x) -> [fx: scalar, in_range: bool]
     * @cite chapra2014numerical_cubic_splines
     */
    template <typename tag_t=tag::no_assert_t, typename X, typename Y>
    constexpr auto cubic_spline(const X& x, const Y& y)
    {
        auto [e, f, g, r] = detail::make_tridiagonal<tag_t>(x,y);
        auto d2x = linalg::tridiagonal_elimination<tag_t>(e,f,g,r);
        auto fn = detail::make_cubic_spline_fn<tag_t>(x,y,d2x);
        return fn;
    }

    /**
     * @brief compute linear spline
     * 
     * @tparam tag_t=tag::size_assert_t optional tag for size assertion
     * @tparam X vector-like
     * @tparam Y vector-like
     * @param x independent variables
     * @param y dependent variables
     * @return constexpr auto callable
     * @cite chapra2014numerical_linear_splines
     */
    template <typename tag_t=tag::size_assert_t, typename X, typename Y>
    constexpr auto linear_spline(const X& x, const Y& y)
    {
        static_assert(
            traits::is_array1d_v<X> &&
            traits::is_array1d_v<Y>,
            "unsupported type for x & y"
        );
        auto m = compute_slopes<tag_t>(x,y);
        auto f = detail::make_linear_spline_fn<tag_t>(x,y,m);
        return f;
    }

} // namespace nmtools::curvefit

#endif // NMTOOLS_SPLINE_HPP