#ifndef NMTOOLS_UTL_REMEZ_HPP
#define NMTOOLS_UTL_REMEZ_HPP

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

#include "nmtools/utl/power.hpp"

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

        nm_index_t degree = nm_index_t(n) - 2;
        for (nm_size_t i=0; i<nm_size_t(degree+2); i++) {
            // result[i] = a + (b-a) * (0.5 - 0.5 * taylor_cos(pi_v<T> * i / (degree + 1)));
            auto k = taylor_cos((2*i+1)*pi_v<T> / (2*n));
            result[i] = T(0.5) * (a+b) + T(0.5) * (b-a) * k;
        }
        // insertion_sort_(result,[](auto a, auto b){
        //     return abs(a) > abs(b);
        // });
        insertion_sort_(result);

        return result;
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

        auto nodes_vtype = [](){
            if constexpr (is_constant_index_v<degree_t>) {
                using type = utl::static_vector<T,degree_t::value+2>;
                return as_value_v<type>;
            } else {
                // TODO: use small vector
                using type = utl::vector<T>;
                return as_value_v<type>;
            }
        }();
        using nodes_t = type_t<decltype(nodes_vtype)>;

        auto m_nodes = chebyshev_nodes(a,b,num_nodes);
        auto nodes = nodes_t{};
        for (nm_size_t i=0; i<(nm_size_t)m_nodes.size(); i++) {
            nodes.push_back(m_nodes[i]);
        }

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

        constexpr auto abs = [](T t) {
            if (t < 0) {
                return -t;
            } else {
                return t;
            }
        };

        constexpr auto pow = [](T t, nm_size_t k){
            auto res = T{1};
            for (nm_size_t i=0; i<k; i++) {
                res = res * t;
            }
            return res;
        };

        // TODO: find better way?
        auto get_search_interval = [&](auto a, auto b, const auto& nodes){
            using nodes_t = remove_cvref_t<decltype(nodes)>;
            using element_t = get_element_type_t<nodes_t>;

            auto result_vtype = [](){
                constexpr auto MAX_DIM = max_len_v<nodes_t>;
                if constexpr (MAX_DIM > 0) {
                    using type = utl::static_vector<element_t,MAX_DIM+2>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = utl::vector<element_t>;
                    return as_value_v<type>;
                }
            }();
            using result_t = type_t<decltype(result_vtype)>;

            auto result = result_t {};

            result.push_back(a);
            for (nm_size_t i=0; i<nodes.size(); i++) {
                const auto node = nodes[i];
                // NOTE: this may be affecting the results precision
                constexpr auto eps = 1e-9;
                if ((abs(node-a) < eps) || (abs(b-node) < eps)) {
                    continue;
                }
                result.push_back(node);
            }
            result.push_back(b);
            return result;
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
                    mat[j][k] = pow(t,k);
                }
                mat[j][degree+1] = pow(-1,j);
                vec[j] = f(t);
            }

            auto solution = linear_solve(mat,vec);
            final_coeffs = solution;

            auto coeffs = get_coeffs(solution);
            [[maybe_unused]]
            auto E = solution[solution.size()-1];

            auto neg_abs_error = [&](T t){
                return -abs(f(t)-horner_poly(t,coeffs));
            };

            auto search_interval = get_search_interval(a,b,nodes);
            insertion_sort_(search_interval);

            using new_nodes_t = remove_cvref_t<decltype(search_interval)>;
            auto new_nodes = new_nodes_t {};
            if constexpr (is_resizable_v<new_nodes_t>) {
                new_nodes.resize(search_interval.size());
            }
            for (nm_size_t i=0; i<(nm_size_t)search_interval.size()-1; i++) {
                auto res = minimize_bounded(neg_abs_error,search_interval[i],search_interval[i+1]);
                new_nodes[i] = res;
            }
            insertion_sort_(new_nodes);
            for (nm_size_t i=0; i<(nm_size_t)nodes.size(); i++) {
                nodes[i] = new_nodes[i];
            }
        }

        return final_coeffs;
    } // solve_remez
}

#endif // NMTOOLS_UTL_REMEZ_HPP