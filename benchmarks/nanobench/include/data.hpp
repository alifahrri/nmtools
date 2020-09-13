#ifndef NMTOOLS_BENCH_DATA_HPP
#define NMTOOLS_BENCH_DATA_HPP

#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"

#include <array>
#include <vector>
#include <valarray>

namespace nmtools::bench::data
{
    namespace array
    {
        using std::array;
        /**
         * @brief 2x2 matrix with type of
         * nested std::array of double,
         * for gauss_elimination
         * 
         */
        template <typename T>
        auto M2x2 = array<array<T,2>,2>{{
            {2e+0, 1e+5},
            {1e+0, 1e+0},
        }};
        auto Md2x2 = M2x2<double>;
        auto Mf2x2 = M2x2<float>;
        template <typename T> auto v2 = array<T,2>{1e+5 + 2, 2e+0};
        auto vd2 = v2<double>;
        auto vf2 = v2<float>;
        /**
         * @brief 3x3 nested std::array of double,
         * for lu_decomposition, inverse,
         * 
         */
        template <typename T>
        auto M3x3 = array<array<T,3>,3>{{
            {3.0, -0.1, -0.2},
            {0.1,  7.0, -0.3},
            {0.3, -0.2, 10.0},
        }};
        auto Md3x3 = M3x3<double>;
        auto Mf3x3 = M3x3<float>;
        template <typename T> auto v3 = array<T,3>{7.85, -19.3, 71.4};
        auto vd3 = v3<double>;
        auto vf3 = v3<float>;
        /**
         * @brief 3x3 upper tridiagonal matrix with type of
         * nested std::array of double,
         * for backward_substitution
         * 
         */
        template <typename T>
        auto M3x3_upper = array<array<T,3>,3>{{
            {3., -0.1, -0.2},
            {0.0, 7.00333, -0.29333},
            {0.0, 0.0, 10.0120}
        }};
        auto Md3x3_upper = M3x3_upper<double>;
        auto Mf3x3_upper = M3x3_upper<float>;
        template <typename T> auto v3_upper = array<T,3>{7.85, -19.5617, 70.0843};
        auto vd3_upper = v3_upper<double>;
        auto vf3_upper = v3_upper<float>;
        /**
         * @brief 3x3 symmetric matrix with type of
         * nested std::array of double,
         * for cholesky_decomposition
         * 
         */
        template <typename T>
        auto M3x3_symm = array<array<T,3>,3>{{
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        }};
        auto Md3x3_symm = M3x3_symm<double>;
        auto Mf3x3_symm = M3x3_symm<float>;
        /**
         * @brief 4x4 symmetric matrix with type of
         * nested std::array of double,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M4x4_symm = array<array<T,4>,4>{{
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        }};
        auto Md4x4_symm = M4x4_symm<double>;
        auto Mf4x4_symm = M4x4_symm<float>;
        /**
         * @brief 5x5 symmetric matrix with type of
         * nested std::array of float,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M5x5_symm = array<array<T,5>,5>{{
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        }};
        auto Md5x5_symm = M5x5_symm<double>;
        auto Mf5x5_symm = M5x5_symm<float>;
        /**
         * @brief vector with size of 4 with type of
         * std::array of double, for tridiagonal systems
         * 
         */
        template <typename T> auto v4_e = array<T,4>{0, -1, -1, -1};
        template <typename T> auto v4_f = array<T,4>{2.04, 2.04, 2.04, 2.04};
        template <typename T> auto v4_g = array<T,4>{-1, -1, -1, 0};
        template <typename T> auto v4_b = array<T,4>{40.8, 0.8, 0.8, 200.8};
        auto vd4_e = v4_e<double>;
        auto vd4_f = v4_f<double>;
        auto vd4_g = v4_g<double>;
        auto vd4_b = v4_b<double>;
        auto vf4_e = v4_e<float>;
        auto vf4_f = v4_f<float>;
        auto vf4_g = v4_g<float>;
        auto vf4_b = v4_b<float>;
    } // namespace array

    namespace vector
    {
        using std::vector;
        /**
         * @brief 2x2 matrix with type of
         * nested std::vector of double,
         * for gauss_elimination
         * 
         */
        template <typename T>
        auto M2x2 = vector<vector<T>>{{
            {2e+0, 1e+5},
            {1e+0, 1e+0},
        }};
        auto Md2x2 = M2x2<double>;
        auto Mf2x2 = M2x2<float>;
        template <typename T> auto v2 = vector<T>{1e+5 + 2, 2e+0};
        auto vd2 = v2<double>;
        auto vf2 = v2<float>;
        /**
         * @brief 3x3 nested std::vector of double,
         * for lu_decomposition, inverse,
         * 
         */
        template <typename T>
        auto M3x3 = vector<vector<T>>{{
            {3.0, -0.1, -0.2},
            {0.1,  7.0, -0.3},
            {0.3, -0.2, 10.0},
        }};
        auto Md3x3 = M3x3<double>;
        auto Mf3x3 = M3x3<float>;
        template <typename T> auto v3 = vector<T>{7.85, -19.3, 71.4};
        auto vd3 = v3<double>;
        auto vf3 = v3<float>;
        /**
         * @brief 3x3 upper tridiagonal matrix with type of
         * nested std::vector of double,
         * for backward_substitution
         * 
         */
        template <typename T>
        auto M3x3_upper = vector<vector<T>>{{
            {3., -0.1, -0.2},
            {0.0, 7.00333, -0.29333},
            {0.0, 0.0, 10.0120}
        }};
        auto Md3x3_upper = M3x3_upper<double>;
        auto Mf3x3_upper = M3x3_upper<float>;
        template <typename T> auto v3_upper = vector<T>{7.85, -19.5617, 70.0843};
        auto vd3_upper = v3_upper<double>;
        auto vf3_upper = v3_upper<float>;
        /**
         * @brief 3x3 symmetric matrix with type of
         * nested std::vector of double,
         * for cholesky_decomposition
         * 
         */
        template <typename T>
        auto M3x3_symm = vector<vector<T>>{{
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        }};
        auto Md3x3_symm = M3x3_symm<double>;
        auto Mf3x3_symm = M3x3_symm<float>;
        /**
         * @brief 4x4 symmetric matrix with type of
         * nested std::vector of double,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M4x4_symm = vector<vector<T>>{{
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        }};
        auto Md4x4_symm = M4x4_symm<double>;
        auto Mf4x4_symm = M4x4_symm<float>;
        /**
         * @brief 5x5 symmetric matrix with type of
         * nested std::vector of float,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M5x5_symm = vector<vector<T>>{{
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        }};
        auto Md5x5_symm = M5x5_symm<double>;
        auto Mf5x5_symm = M5x5_symm<float>;
        /**
         * @brief vector with size of 4 with type of
         * std::vector of double, for tridiagonal systems
         * 
         */
        template <typename T> auto v4_e = vector<T>{0, -1, -1, -1};
        template <typename T> auto v4_f = vector<T>{2.04, 2.04, 2.04, 2.04};
        template <typename T> auto v4_g = vector<T>{-1, -1, -1, 0};
        template <typename T> auto v4_b = vector<T>{40.8, 0.8, 0.8, 200.8};
        auto vd4_e = v4_e<double>;
        auto vd4_f = v4_f<double>;
        auto vd4_g = v4_g<double>;
        auto vd4_b = v4_b<double>;
        auto vf4_e = v4_e<float>;
        auto vf4_f = v4_f<float>;
        auto vf4_g = v4_g<float>;
        auto vf4_b = v4_b<float>;
    } // namespace vector

    namespace valarray
    {
        using std::valarray;
        /**
         * @brief 2x2 matrix with type of
         * nested std::valarray of double,
         * for gauss_elimination
         * 
         */
        template <typename T>
        auto M2x2 = valarray<valarray<T>>{{
            {2e+0, 1e+5},
            {1e+0, 1e+0},
        }};
        auto Md2x2 = M2x2<double>;
        auto Mf2x2 = M2x2<float>;
        template <typename T> auto v2 = valarray<T>{1e+5 + 2, 2e+0};
        auto vd2 = v2<double>;
        auto vf2 = v2<float>;
        /**
         * @brief 3x3 nested std::valarray of double,
         * for lu_decomposition, inverse,
         * 
         */
        template <typename T>
        auto M3x3 = valarray<valarray<T>>{{
            {3.0, -0.1, -0.2},
            {0.1,  7.0, -0.3},
            {0.3, -0.2, 10.0},
        }};
        auto Md3x3 = M3x3<double>;
        auto Mf3x3 = M3x3<float>;
        template <typename T> auto v3 = valarray<T>{7.85, -19.3, 71.4};
        auto vd3 = v3<double>;
        auto vf3 = v3<float>;
        /**
         * @brief 3x3 upper tridiagonal matrix with type of
         * nested std::valarray of double,
         * for backward_substitution
         * 
         */
        template <typename T>
        auto M3x3_upper = valarray<valarray<T>>{{
            {3., -0.1, -0.2},
            {0.0, 7.00333, -0.29333},
            {0.0, 0.0, 10.0120}
        }};
        auto Md3x3_upper = M3x3_upper<double>;
        auto Mf3x3_upper = M3x3_upper<float>;
        template <typename T> auto v3_upper = valarray<T>{7.85, -19.5617, 70.0843};
        auto vd3_upper = v3_upper<double>;
        auto vf3_upper = v3_upper<float>;
        /**
         * @brief 3x3 symmetric matrix with type of
         * nested std::valarray of double,
         * for cholesky_decomposition
         * 
         */
        template <typename T> 
        auto M3x3_symm = valarray<valarray<T>>{{
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        }};
        auto Md3x3_symm = M3x3_symm<double>;
        auto Mf3x3_symm = M3x3_symm<float>;
        /**
         * @brief 4x4 symmetric matrix with type of
         * nested std::valarray of double,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M4x4_symm = valarray<valarray<T>>{{
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        }};
        auto Md4x4_symm = M4x4_symm<double>;
        auto Mf4x4_symm = M4x4_symm<float>;
        /**
         * @brief 5x5 symmetric matrix with type of
         * nested std::valarray of float,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M5x5_symm = valarray<valarray<T>>{{
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        }};
        auto Md5x5_symm = M5x5_symm<double>;
        auto Mf5x5_symm = M5x5_symm<float>;

        /**
         * @brief vector with size of 4 with type of
         * std::array of double, for tridiagonal systems
         * 
         */
        template <typename T> auto v4_e = valarray<T>{0, -1, -1, -1};
        template <typename T> auto v4_f = valarray<T>{2.04, 2.04, 2.04, 2.04};
        template <typename T> auto v4_g = valarray<T>{-1, -1, -1, 0};
        template <typename T> auto v4_b = valarray<T>{40.8, 0.8, 0.8, 200.8};
        auto vd4_e = v4_e<double>;
        auto vd4_f = v4_f<double>;
        auto vd4_g = v4_g<double>;
        auto vd4_b = v4_b<double>;
        auto vf4_e = v4_e<float>;
        auto vf4_f = v4_f<float>;
        auto vf4_g = v4_g<float>;
        auto vf4_b = v4_b<float>;
    } // namespace valarray

    namespace raw
    {
        /* NOTE: cant be used, deduced type is T(*)[2] for matrix and T(*) for vector */
        // template <typename T>
        // T M2x2[2][2] = {
        //     {2e+0, 1e+5},
        //     {1e+0, 1e+0},
        // };
        // auto Md2x2 = M2x2<double>;
        // auto Mf2x2 = M2x2<float>;

        /**
         * @brief 2x2 matrix with type of
         * nested std::vector of double,
         * for gauss_elimination
         * 
         */
        double Md2x2[2][2] = {
            {2e+0, 1e+5},
            {1e+0, 1e+0},
        };
        float Mf2x2[2][2] = {
            {2e+0, 1e+5},
            {1e+0, 1e+0},
        };
        double vd2[2] = {1e+5 + 2, 2e+0};
        float vf2[2] = {1e+5 + 2, 2e+0};
        /**
         * @brief 3x3 nested raw array of double,
         * for lu_decomposition, inverse,
         * 
         */
        double Md3x3[3][3] = {
            {3.0, -0.1, -0.2},
            {0.1,  7.0, -0.3},
            {0.3, -0.2, 10.0},
        };
        float Mf3x3[3][3] = {
            {3.0, -0.1, -0.2},
            {0.1,  7.0, -0.3},
            {0.3, -0.2, 10.0},
        };
        double vd3[3] = {7.85, -19.3, 71.4};
        float vf3[3] = {7.85, -19.3, 71.4};
        /**
         * @brief 3x3 upper tridiagonal matrix with type of
         * nested std::vector of double,
         * for backward_substitution
         * 
         */
        double Md3x3_upper[3][3] = {
            {3., -0.1, -0.2},
            {0.0, 7.00333, -0.29333},
            {0.0, 0.0, 10.0120}
        };
        float Mf3x3_upper[3][3] = {
            {3., -0.1, -0.2},
            {0.0, 7.00333, -0.29333},
            {0.0, 0.0, 10.0120}
        };
        double vd3_upper[3] = {7.85, -19.5617, 70.0843};
        float vf3_upper[3] = {7.85, -19.5617, 70.0843};
        /**
         * @brief 3x3 symmetric matrix with type of
         * nested raw array of double,
         * for cholesky_decomposition
         * 
         */
        double Md3x3_symm[3][3] = {
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        };
        float Mf3x3_symm[3][3] = {
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        };
        /**
         * @brief 4x4 symmetric matrix with type of
         * nested raw array of double,
         * for cholesky_decomposition, inverse
         * 
         */
        double Md4x4_symm[4][4] = {
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        };
        float Mf4x4_symm[4][4] = {
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        };
        /**
         * @brief 5x5 symmetric matrix with type of
         * nested std::vector of float,
         * for cholesky_decomposition, inverse
         * 
         */
        double Md5x5_symm[5][5] = {
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        };
        float Mf5x5_symm[5][5] = {
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        };

        /**
         * @brief vector with size of 4 with type of
         * raw array of double, for tridiagonal systems
         * 
         */
        double vd4_e[4] = {0, -1, -1, -1};
        double vd4_f[4] = {2.04, 2.04, 2.04, 2.04};
        double vd4_g[4] = {-1, -1, -1, 0};
        double vd4_b[4] = {40.8, 0.8, 0.8, 200.8};
        float vf4_e[4] = {0, -1, -1, -1};
        float vf4_f[4] = {2.04, 2.04, 2.04, 2.04};
        float vf4_g[4] = {-1, -1, -1, 0};
        float vf4_b[4] = {40.8, 0.8, 0.8, 200.8};
    } // namespace raw

    namespace fixed
    {
        using ::nmtools::array::fixed_vector;
        using ::nmtools::array::fixed_matrix;
        /**
         * @brief 2x2 matrix with type of
         * nested std::array of double,
         * for gauss_elimination
         * 
         */
        template <typename T>
        auto M2x2 = fixed_matrix<T,2,2>{
            2e+0, 1e+5,
            1e+0, 1e+0,
        };
        auto Md2x2 = M2x2<double>;
        auto Mf2x2 = M2x2<float>;
        template <typename T> auto v2 = fixed_vector<T,2>{1e+5 + 2, 2e+0};
        auto vd2 = v2<double>;
        auto vf2 = v2<float>;
        /**
         * @brief 3x3 nested std::array of double,
         * for lu_decomposition, inverse,
         * 
         */
        template <typename T>
        auto M3x3 = fixed_matrix<T,3,3>{
            3.0, -0.1, -0.2,
            0.1,  7.0, -0.3,
            0.3, -0.2, 10.0,
        };
        auto Md3x3 = M3x3<double>;
        auto Mf3x3 = M3x3<float>;
        template <typename T> auto v3 = fixed_vector<T,3>{7.85, -19.3, 71.4};
        auto vd3 = v3<double>;
        auto vf3 = v3<float>;
        /**
         * @brief 3x3 upper tridiagonal matrix with type of
         * nested std::array of double,
         * for backward_substitution
         * 
         */
        template <typename T>
        auto M3x3_upper = fixed_matrix<T,3,3>{
            3., -0.1, -0.2,
            0.0, 7.00333, -0.29333,
            0.0, 0.0, 10.0120
        };
        auto Md3x3_upper = M3x3_upper<double>;
        auto Mf3x3_upper = M3x3_upper<float>;
        template <typename T> auto v3_upper = fixed_vector<T,3>{7.85, -19.5617, 70.0843};
        auto vd3_upper = v3_upper<double>;
        auto vf3_upper = v3_upper<float>;
        /**
         * @brief 3x3 symmetric matrix with type of
         * nested std::array of double,
         * for cholesky_decomposition
         * 
         */
        template <typename T>
        auto M3x3_symm = fixed_matrix<T,3,3>{
             6,  15,  55,
            15,  55, 225,
            55, 225, 979,
        };
        auto Md3x3_symm = M3x3_symm<double>;
        auto Mf3x3_symm = M3x3_symm<float>;
        /**
         * @brief 4x4 symmetric matrix with type of
         * nested std::array of double,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M4x4_symm = fixed_matrix<T,4,4>{
             1,  4,  9, 16,
             4,  9, 16, 25,
             9, 16, 25, 36,
            16, 25, 36, 49,
        };
        auto Md4x4_symm = M4x4_symm<double>;
        auto Mf4x4_symm = M4x4_symm<float>;
        /**
         * @brief 5x5 symmetric matrix with type of
         * nested std::array of float,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M5x5_symm = fixed_matrix<T,5,5>{
             1,  4,  9, 16, 25,
             4,  9, 16, 25, 36,
             9, 16, 25, 36, 49,
            16, 25, 36, 49, 64,
            25, 36, 49, 64, 81,
        };
        auto Md5x5_symm = M5x5_symm<double>;
        auto Mf5x5_symm = M5x5_symm<float>;
        /**
         * @brief vector with size of 4 with type of
         * std::array of double, for tridiagonal systems
         * 
         */
        template <typename T> auto v4_e = fixed_vector<T,4>{0, -1, -1, -1};
        template <typename T> auto v4_f = fixed_vector<T,4>{2.04, 2.04, 2.04, 2.04};
        template <typename T> auto v4_g = fixed_vector<T,4>{-1, -1, -1, 0};
        template <typename T> auto v4_b = fixed_vector<T,4>{40.8, 0.8, 0.8, 200.8};
        auto vd4_e = v4_e<double>;
        auto vd4_f = v4_f<double>;
        auto vd4_g = v4_g<double>;
        auto vd4_b = v4_b<double>;
        auto vf4_e = v4_e<float>;
        auto vf4_f = v4_f<float>;
        auto vf4_g = v4_g<float>;
        auto vf4_b = v4_b<float>;
    } // namespace fixed

    namespace dynamic
    {
        using ::nmtools::array::dynamic_matrix;
        using ::nmtools::array::dynamic_vector;
        /**
         * @brief 2x2 matrix with type of
         * nested std::valarray of double,
         * for gauss_elimination
         * 
         */
        template <typename T>
        auto M2x2 = dynamic_matrix<T>{
            {2e+0, 1e+5},
            {1e+0, 1e+0},
        };
        auto Md2x2 = M2x2<double>;
        auto Mf2x2 = M2x2<float>;
        template <typename T> auto v2 = dynamic_vector<T>{1e+5 + 2, 2e+0};
        auto vd2 = v2<double>;
        auto vf2 = v2<float>;
        /**
         * @brief 3x3 nested std::valarray of double,
         * for lu_decomposition, inverse,
         * 
         */
        template <typename T>
        auto M3x3 = dynamic_matrix<T>{
            {3.0, -0.1, -0.2},
            {0.1,  7.0, -0.3},
            {0.3, -0.2, 10.0},
        };
        auto Md3x3 = M3x3<double>;
        auto Mf3x3 = M3x3<float>;
        template <typename T> auto v3 = dynamic_vector<T>{7.85, -19.3, 71.4};
        auto vd3 = v3<double>;
        auto vf3 = v3<float>;
        /**
         * @brief 3x3 upper tridiagonal matrix with type of
         * nested std::valarray of double,
         * for backward_substitution
         * 
         */
        template <typename T>
        auto M3x3_upper = dynamic_matrix<T>{
            {3., -0.1, -0.2},
            {0.0, 7.00333, -0.29333},
            {0.0, 0.0, 10.0120}
        };
        auto Md3x3_upper = M3x3_upper<double>;
        auto Mf3x3_upper = M3x3_upper<float>;
        template <typename T> auto v3_upper = dynamic_vector<T>{7.85, -19.5617, 70.0843};
        auto vd3_upper = v3_upper<double>;
        auto vf3_upper = v3_upper<float>;
        /**
         * @brief 3x3 symmetric matrix with type of
         * nested std::valarray of double,
         * for cholesky_decomposition
         * 
         */
        template <typename T> 
        auto M3x3_symm = dynamic_matrix<T>{
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        };
        auto Md3x3_symm = M3x3_symm<double>;
        auto Mf3x3_symm = M3x3_symm<float>;
        /**
         * @brief 4x4 symmetric matrix with type of
         * nested std::valarray of double,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M4x4_symm = dynamic_matrix<T>{
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        };
        auto Md4x4_symm = M4x4_symm<double>;
        auto Mf4x4_symm = M4x4_symm<float>;
        /**
         * @brief 5x5 symmetric matrix with type of
         * nested std::valarray of float,
         * for cholesky_decomposition, inverse
         * 
         */
        template <typename T>
        auto M5x5_symm = dynamic_matrix<T>{
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        };
        auto Md5x5_symm = M5x5_symm<double>;
        auto Mf5x5_symm = M5x5_symm<float>;

        /**
         * @brief vector with size of 4 with type of
         * std::array of double, for tridiagonal systems
         * 
         */
        template <typename T> auto v4_e = dynamic_vector<T>{0, -1, -1, -1};
        template <typename T> auto v4_f = dynamic_vector<T>{2.04, 2.04, 2.04, 2.04};
        template <typename T> auto v4_g = dynamic_vector<T>{-1, -1, -1, 0};
        template <typename T> auto v4_b = dynamic_vector<T>{40.8, 0.8, 0.8, 200.8};
        auto vd4_e = v4_e<double>;
        auto vd4_f = v4_f<double>;
        auto vd4_g = v4_g<double>;
        auto vd4_b = v4_b<double>;
        auto vf4_e = v4_e<float>;
        auto vf4_f = v4_f<float>;
        auto vf4_g = v4_g<float>;
        auto vf4_b = v4_b<float>;
    } // namespace dynamic

} // namespace nmtools::bench::data

#endif // NMTOOLS_BENCH_DATA_HPP