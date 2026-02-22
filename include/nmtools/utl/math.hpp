#ifndef NMTOOLS_UTL_MATH_HPP
#define NMTOOLS_UTL_MATH_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/traits/is_resizable.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"
#include "nmtools/meta/bits/transform/get_element_type.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/transform/max_len.hpp"
#include "nmtools/utl/algorithm.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/vector.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/tuple.hpp"

namespace nmtools::utl
{
    template <typename T>
    constexpr inline T pi_v = 3.141592653589793238462643383279502884197;

    template <typename T>
    constexpr auto abs(T t)
    {
        if (t < 0) {
            return -t;
        } else {
            return t;
        }
    }

    template <typename T>
    constexpr auto get_exponent_bits(T x)
    {
        // TODO: handle double precision
        uint32_t bits = __builtin_bit_cast(uint32_t,x);

        auto shifted_bits = bits >> 23;

        auto exponent_field = shifted_bits & 0xFF;

        int32_t actual_exponent = exponent_field - 127;

        return actual_exponent;
    }

    template <typename T>
    constexpr auto copy_sign(T x, T y)
    {
        auto x_bits = __builtin_bit_cast(uint32_t,x);
        auto y_bits = __builtin_bit_cast(uint32_t,y);

        auto sign_mask = 0x80000000;

        auto mag_x = x_bits & (~sign_mask);
        auto sgn_y = y_bits & sign_mask;

        auto result_bits = mag_x | sgn_y;

        return __builtin_bit_cast(T,result_bits);
    }

    template <typename exponent_t>
    constexpr auto create_integer_mask(exponent_t exponent)
    {
        // TODO: assert constant index
        if (exponent >= 23) {
            return 0xFFFFFFFF;
        }
        if (exponent < 0) {
            return 0x80000000;
        }

        int32_t num_fractional_bits = 23 - exponent;
        auto mask = 0xFFFFFFFF << num_fractional_bits;

        return mask;
    }

    template <typename T, typename U>
    constexpr auto bitwise_and(T x, U mask)
    {
        auto bits = __builtin_bit_cast(uint32_t,x);

        auto masked_bits = bits & mask;

        return __builtin_bit_cast(T,masked_bits);
    }

    template <typename T>
    constexpr auto trunc(T x)
    {
        auto exponent = get_exponent_bits(x);

        if (exponent >= 23) {
            return x;
        }

        if ((int32_t)exponent < 0) {
            return copy_sign(T(0), x);
        }

        auto mask = create_integer_mask(exponent);
        auto result = bitwise_and(x,mask);

        return result;
    }

    template <typename T>
    constexpr auto floor(T x)
    {
        // assume float, so use int
        // TODO: infer type
        int32_t i = x;
        if (x < i) {
            return (T)(i-1);
        } else {
            return (T)i;
        }
    }

    template <typename T>
    constexpr auto ceil(T x)
    {
        // assume float, use int
        // TODO: infer type
        int32_t i = x;
        if (x > i) {
            return (T)(i + 1);
        } else {
            return (T)i;
        }
    }

    template <typename T>
    constexpr auto round(T x)
    {
        return (x >= 0) ? floor(x + T(0.5)) : ceil(x - T(0.5));
    }

    template <typename T, typename U>
    constexpr auto fmod(T x, U y)
    {
        // TODO: hanle nan
        // if (y == 0) {
        //     return T(NAN);
        // }
        auto quotient = trunc(T(x / y));

        auto result = x - (quotient * y);
        return result;
    }

    template <typename T, typename U=float>
    constexpr auto sqrt(T x, U tol=U{1e-7}, nm_size_t max_iter=25)
    {
        // zero
        if (abs(x) < tol) {
            return x;
        }
        T guess = x / T(2);

        for (nm_size_t i=0; (i<max_iter); i++) {
            auto next_guess = T(0.5) * (guess + (x/guess));

            auto done = abs(guess - next_guess) < tol;
            guess = next_guess;

            if (done) {
                break;
            }
        }
        return guess;
    }

    template <typename F, typename T>
    constexpr auto minimize_bounded(F obj_fun, T lower_bound, T upper_bound, T tol=1e-5, nm_size_t max_iter=50)
    {
        auto R = (sqrt(T(5)) - 1) / T(2);

        auto a = lower_bound;
        auto b = upper_bound;
        auto distance = R * (b - a);
        auto x1 = b - distance;
        auto x2 = a + distance;

        auto f1 = obj_fun(x1);
        auto f2 = obj_fun(x2);

        for (nm_size_t i=0; (i<max_iter) && (abs(b-a) > tol); i++) {
            if (f1 < f2) {
                b = x2;
                x2 = x1;
                f2 = f1;

                distance = R * (b-a);
                x1 = b - distance;
                f1 = obj_fun(x1);
            } else {
                a = x1;
                x1 = x2;
                f1 = f2;

                distance = R * (b-a);
                x2 = a + distance;
                f2 = obj_fun(x2);
            }
        }

        auto final_x = (a+b) / T(2);
        return T(final_x);
    }

    template <typename T>
    constexpr auto taylor_cos(T x, T precision_limit=1e-16, nm_size_t max_iter=100)
    {
        x = fmod(x,(2 * pi_v<T>));
        if (x > pi_v<T>) {
            x = x - (2 * pi_v<T>);
        }

        T result = 1;
        T term = 1;
        nm_size_t n = 1;

        auto x_squared = x * x;

        while (abs(term) > precision_limit) {
            auto multiplier = -x_squared / ((2*n-1)*(2*n));
            term = term * multiplier;

            result = result + term;
            n = n + 1;

            if (n > max_iter) {
                break;
            }
        }

        return result;
    }

    template <typename T>
    constexpr auto taylor_sin(T x, T precision_limit=1e-16, nm_size_t max_iter=100)
    {
        x = fmod(x,(2 * pi_v<T>));
        if (x > pi_v<T>) {
            x = x - (2*pi_v<T>);
        } else if (x < -pi_v<T>) {
            x = x + (2*pi_v<T>);
        }

        auto result = x;
        auto term = x;
        nm_size_t n = 1;

        auto x_squared = x * x;

        while (abs(term) > precision_limit) {
            auto multiplier = -x_squared / ((2*n)*(2*n+1));
            term = term * multiplier;

            result = result + term;
            n = n + 1;

            if (n > max_iter) {
                break;
            }
        }

        return result;
    }

    template <typename T>
    constexpr auto taylor_exp(T t, T precision_limit=1e-15, nm_size_t max_iter=100)
    {
        T result = 1;
        T term = 1;
        nm_size_t n = 1;

        while (abs(term) > precision_limit) {
            term = term * (t / n);
            result = result + term;
            n = n+1;

            if (n>max_iter) {
                break;
            }
        }

        return result;
    }

    template <typename T, typename num_nodes_t>
    constexpr auto chebyshev_nodes(T a, T b, num_nodes_t n)
    {
        auto result_vtype = [](){
            if constexpr (is_constant_index_v<num_nodes_t>) {
                using type = utl::array<T,num_nodes_t::value>;
                return as_value_v<type>;
            } else {
                using type = utl::vector<T>;
                return as_value_v<type>;
            }
        }();
        using result_t = type_t<decltype(result_vtype)>;

        auto result = result_t {};

        if constexpr (is_resizable_v<result_t>) {
            result.resize(n);
        }

        // result[0] = a;
        // result[n-1] = b;
        #if 0
        for (nm_size_t i=1; i<=(nm_size_t)n; i++) {
            auto angle = (T(2) * i + 1) * pi_v<T> / (2 * n);
            auto x_standard = taylor_cos(angle);

            auto x_mapped = ((a+b) / 2) + (((b-a) * x_standard) / 2);

            result[n-i] = x_mapped;
        }
        #else
        nm_index_t degree = nm_index_t(n) - 2;
        for (nm_size_t i=0; i<nm_size_t(degree+2); i++) {
            // result[i] = a + (b-a) * (0.5 - 0.5 * taylor_cos(pi_v<T> * i / (degree + 1)));
            auto k = taylor_cos((2*i+1)*pi_v<T> / (2*n));
            result[i] = T(0.5) * (a+b) + T(0.5) * (b-a) * k;
        }
        #endif
        // insertion_sort_(result,[](auto a, auto b){
        //     return abs(a) > abs(b);
        // });
        insertion_sort_(result);

        return result;
    }
}

// linear

namespace nmtools::utl
{
    template <typename mat_t>
    constexpr auto pivot_swap_mat(mat_t& mat, nm_size_t row_i, nm_size_t row_k)
    {
        if (row_i == row_k) {
            return;
        }
        // assume mat is nxn
        auto n = mat.size();
        for (nm_size_t i=0; i<n; i++) {
            auto tmp = mat[row_i][i];
            mat[row_i][i] = mat[row_k][i];
            mat[row_k][i] = tmp;
        }
    }

    template <typename vec_t>
    constexpr auto pivot_swap_vec(vec_t& vec, nm_size_t row_i, nm_size_t row_k)
    {
        if (row_i == row_k) {
            return;
        }
        auto tmp = vec[row_i];
        vec[row_i] = vec[row_k];
        vec[row_k] = tmp;
    }

    template <typename mat_t, typename vec_t>
    constexpr auto linear_solve(const mat_t& A, const vec_t& b)
    {
        nm_size_t n = b.size();

        // assume A: nxn, B: n

        auto mA = A;
        auto mb = b;
        for (nm_size_t i=0; i<(nm_size_t)n-1; i++) {
            auto pivot_row = i;
            for (nm_size_t k=(i+1); k<(nm_size_t)n; k++) {
                if (abs(mA[k][i]) > abs(mA[pivot_row][i])) {
                    pivot_row = k;
                }
            }
            pivot_swap_mat(mA,i,pivot_row);
            pivot_swap_vec(mb,i,pivot_row);

            for (nm_size_t j=i+1; j<(nm_size_t)n; j++) {
                auto factor = mA[j][i] / mA[i][i];
                for (nm_size_t k=i; k<(nm_size_t)n; k++) {
                    mA[j][k] -= factor * mA[i][k];
                }
                mb[j] -= factor * mb[i];
            }
        }

        auto x = vec_t{};
        if constexpr (is_resizable_v<vec_t>) {
            x.resize(n);
        }
        using element_t = get_element_type_t<vec_t>;
        for (nm_index_t i=n-1; i>=0; i--) {
            auto sum = element_t{0};
            for (nm_size_t j=i+1; j<n; j++) {
                sum += mA[i][j] * x[j];
            }
            x[i] = (mb[i] - sum) / mA[i][i];
        }
        return x;
    }

    template <typename T>
    constexpr auto pow(T t, nm_size_t k)
    {
        auto res = T{1};
        for (nm_size_t i=0; i<k; i++) {
            res = res * t;
        }
        return res;
    }

    template <typename T, typename coeffs_t>
    constexpr auto horner_poly(T x, const coeffs_t& coeffs)
    {
        auto n = coeffs.size();
        T result = coeffs[n-1];
        for (nm_index_t i=n-2; i>=0; i--) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    template <typename T>
    constexpr auto reduce_range(T x)
    {
        auto k = round(x / (pi_v<T> / T(2)));
        auto r = x - k * (pi_v<T> / T(2));

        // TODO: infer type
        return utl::tuple{int32_t(k) % 4, r};
    }

    template <typename F, typename T, typename degree_t=ct<4>>
    constexpr auto solve_remez(F f, T a, T b, degree_t degree=degree_t{}, nm_size_t num_iter=nm_size_t{10})
    {
        auto num_nodes = [&](){
            if constexpr (is_constant_index_v<degree_t>) {
                return ct_v<degree_t::value+2>;
            } else {
                return degree + 2;
            }
        }();

        auto mat_vtype = [](){
            if constexpr (is_constant_index_v<degree_t>) {
                using inner_t = utl::array<T,degree_t::value+2>;
                using outer_t = utl::array<inner_t,degree_t::value+2>;
                return as_value_v<outer_t>;
            } else {
                using inner_t = utl::vector<T>;
                using outer_t = utl::vector<inner_t>;
                return as_value_v<outer_t>;
            }
        }();
        using mat_t = type_t<decltype(mat_vtype)>;
        auto vec_vtype = [](){
            if constexpr (is_constant_index_v<degree_t>) {
                using type = utl::array<T,degree_t::value+2>;
                return as_value_v<type>;
            } else {
                using type = utl::vector<T>;
                return as_value_v<type>;
            }
        }();
        using vec_t = type_t<decltype(vec_vtype)>;

        auto nodes = chebyshev_nodes(a,b,num_nodes);

        auto get_coeffs = [](const auto& coeffs){
            using coeffs_t = remove_cvref_t<decltype(coeffs)>;
            using element_t = get_element_type_t<coeffs_t>;
            auto result_vtype = [](){
                constexpr auto DIM = len_v<coeffs_t>;
                [[maybe_unused]]
                constexpr auto MAX_DIM = max_len_v<coeffs_t>;
                if constexpr (DIM>0) {
                    using type = utl::array<element_t,DIM-1>;
                    return as_value_v<type>;
                } else if constexpr (MAX_DIM>0) {
                    using type = utl::static_vector<element_t,MAX_DIM-1>;
                    return as_value_v<type>;
                } else {
                    // TODO: use utl small vector
                    using type = utl::vector<element_t>;
                    return as_value_v<type>;
                }
            }();
            using result_t = type_t<decltype(result_vtype)>;
            auto result = result_t {};

            if constexpr (is_resizable_v<result_t>) {
                result.resize(coeffs.size()-1);
            }

            for (nm_size_t i=0; i<(nm_size_t)(coeffs.size()-1); i++) {
                result[i] = coeffs[i];
            }

            return result;
        };

        auto get_search_interval = [&](auto, auto, const auto& nodes){
            // TODO: ensure a and b are in the inteval
            return nodes;
        };

        auto size = degree + 2;
        auto final_coeffs = vec_t {};
        if constexpr (is_resizable_v<vec_t>) {
            final_coeffs.resize(size);
        }

        for (nm_size_t i=0; i<nm_size_t(num_iter); i++) {
            auto mat = mat_t{};
            auto vec = vec_t{};

            if constexpr (is_resizable_v<mat_t>) {
                mat.resize(size);
                for (nm_size_t j=0; j<(nm_size_t)size; j++) {
                    mat[j].resize(size);
                }
            }
            if constexpr (is_resizable_v<vec_t>) {
                vec.resize(size);
            }

            for (nm_size_t j=0; j<(nm_size_t)size; j++) {
                T t = nodes[j];
                for (nm_size_t k=0; k<(nm_size_t)(size-1); k++) {
                    mat[j][k] = utl::pow(t,k);
                }
                mat[j][degree+1] = utl::pow(-1,j);
                vec[j] = f(t);
            }

            auto solution = linear_solve(mat,vec);
            final_coeffs = solution;

            auto coeffs = get_coeffs(solution);
            [[maybe_unused]]
            auto E = solution[solution.size()-1];

            auto neg_abs_error = [&](T t){
                return -utl::abs(f(t)-horner_poly(t,coeffs));
            };

            auto search_interval = get_search_interval(a,b,nodes);
            insertion_sort_(search_interval);

            using new_nodes_t = remove_cvref_t<decltype(nodes)>;
            auto new_nodes = new_nodes_t {};
            if constexpr (is_resizable_v<new_nodes_t>) {
                new_nodes.resize(nodes.size());
            }
            for (nm_size_t i=0; i<(nm_size_t)search_interval.size()-1; i++) {
                auto res = minimize_bounded(neg_abs_error,search_interval[i],search_interval[i+1]);
                new_nodes[i] = (res);
            }
            insertion_sort_(new_nodes);
            nodes = new_nodes;
        }

        return final_coeffs;
    } // solve_remez

    template <typename T, typename sin_coeffs_t, typename cos_coeffs_t>
    constexpr auto sin_poly(T x, const sin_coeffs_t& sin_coeffs, const cos_coeffs_t& cos_coeffs)
    {
        const auto [k,r] = reduce_range(x);

        auto t = r * r;
        if (k == 0) {
            auto result = r * horner_poly(t,sin_coeffs);
            return result;            
        } else if (k == 1) {
            auto result = horner_poly(t,cos_coeffs);
            return result;
        } else if (k == 2) {
            auto result = r * horner_poly(t,sin_coeffs);
            return -result;
        } else {
            // assume k == 3
            auto result = horner_poly(t,cos_coeffs);
            return -result;
        }
    } // sin_poly

    template <typename T, typename cos_coeffs_t, typename sin_coeffs_t>
    constexpr auto cos_poly(T x, const cos_coeffs_t& cos_coeffs, const sin_coeffs_t& sin_coeffs)
    {
        const auto [k,r] = reduce_range(x);

        auto t = r * r;

        if (k == 0) {
            auto result = horner_poly(t,cos_coeffs);
            return result;
        } else if (k == 1) {
            auto result = r * horner_poly(t,sin_coeffs);
            return -result;
        } else if (k == 2) {
            auto result = horner_poly(t,cos_coeffs);
            return -result;
        } else {
            // assume k == 3
            auto result = r * horner_poly(t,sin_coeffs);
            return result;
        }
    } // cos_poly

    #ifndef NMTOOLS_UTL_REMEZ_DEGREE
    #define NMTOOLS_UTL_REMEZ_DEGREE (ct_v<4>)
    #endif // NMTOOLS_UTL_REMEZ_DEGREE

    #ifndef NMTOOLS_UTL_REMEZ_ITER
    #define NMTOOLS_UTL_REMEZ_ITER (10)
    #endif // NMTOOLS_UTL_REMEZ_ITER


    constexpr auto obj_fun_cos = [](auto t){
        using T = decltype(t);
        return T(utl::taylor_cos(utl::sqrt(utl::abs(t))));
    };
    constexpr auto obj_fun_sin = [](auto t){
        using T = decltype(t);
        if (utl::abs(t) < 1e-7) {
            return T(1.0);
        } else {
            return T(utl::taylor_sin(utl::sqrt(t)) / utl::sqrt(t));
        }
    };

    template <typename T>
    constexpr auto cos(T x)
    {
        constexpr auto a = T(0);
        constexpr auto b = T(utl::pow(T(utl::pi_v<T> / 4), 2));
        constexpr auto cos_coeffs = solve_remez(obj_fun_cos,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        constexpr auto sin_coeffs = solve_remez(obj_fun_sin,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);

        return cos_poly(x,cos_coeffs,sin_coeffs);
    }

    template <typename T>
    constexpr auto sin(T x)
    {
        constexpr auto a = T(0);
        constexpr auto b = T(utl::pow(T(utl::pi_v<T> / 4), 2));
        constexpr auto cos_coeffs = solve_remez(obj_fun_cos,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        constexpr auto sin_coeffs = solve_remez(obj_fun_sin,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);

        return sin_poly(x,sin_coeffs,cos_coeffs);
    }
}

#endif // NMTOOLS_UTL_MATH_HPP