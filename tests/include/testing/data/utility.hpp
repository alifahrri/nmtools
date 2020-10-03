#ifndef NMTOOLS_TESTING_DATA_UTILITY_HPP
#define NMTOOLS_TESTING_DATA_UTILITY_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>

namespace nmtools::testing::data::slice
{
    template <typename T>
    constexpr T x3[3] = {1,2,3};
    template <typename T>
    constexpr T x5[5] = {1,2,3,4,5};
    template <typename T>
    constexpr T x7[7] = {1,2,3,4,5,6,7};
    template <typename T>
    constexpr T x8[8] = {1,2,3,4,5,6,7,8};
    namespace case1::args
    {
        inline auto xad = cast(x3<double>);
        inline auto xaf = cast(x3<float>);
        inline auto xvd = cast<vec_t<double>>(xad);
        inline auto xvf = cast<vec_t<float>>(xaf);
        /* TODO: find-out how to left-out specifying size of array */
        inline auto xfd = cast<fdvec_t<3>>(xad);
        inline auto xff = cast<ffvec_t<3>>(xaf);
        inline constexpr size_t start = 1;
        inline constexpr size_t end = 2;
    }
    namespace case1::expect {
        inline constexpr auto x = std::array<double,1>{2};
    }
    namespace case2::args {
        inline auto xad = cast(x5<double>);
        inline auto xaf = cast(x5<float>);
        inline auto xvd = cast<vec_t<double>>(xad);
        inline auto xvf = cast<vec_t<float>>(xaf);
        /* TODO: find-out how to left-out specifying size of array */
        inline auto xfd = cast<fdvec_t<5>>(xad);
        inline auto xff = cast<ffvec_t<5>>(xaf);
        inline constexpr size_t start = 1;
        inline constexpr size_t end = 4;
    } // namespace case1
    namespace case2::expect {
        inline constexpr auto x = std::array<double,3>{2,3,4};
    }
    namespace case3::args {
        inline auto xad = cast(x7<double>);
        inline auto xaf = cast(x7<float>);
        inline auto xvd = cast<vec_t<double>>(xad);
        inline auto xvf = cast<vec_t<float>>(xaf);
        /* TODO: find-out how to left-out specifying size of array */
        inline auto xfd = cast<fdvec_t<7>>(xad);
        inline auto xff = cast<ffvec_t<7>>(xaf);
        inline constexpr size_t start = 3;
        inline constexpr size_t end = 6;
    } // namespace case1
    namespace case3::expect {
        inline constexpr auto x = std::array<double,4>{4,5,6};
    }
}

namespace nmtools::testing::data::at
{
    namespace case1::args {
        inline auto xad = common_matrix::magic::mad5x5;
        inline auto xaf = common_matrix::magic::maf5x5;
        inline auto xvd = common_matrix::magic::mvd5x5;
        inline auto xvf = common_matrix::magic::mvf5x5;
        inline auto xfd = common_matrix::magic::mfd5x5;
        inline auto xff = common_matrix::magic::mff5x5;
        inline constexpr auto i = 2;
        inline constexpr auto j = 2;
    }
    namespace case1::expect {
        inline auto x = 13;
    }
    namespace case2::args {
        inline auto xad = cast(slice::x8<double>);
        inline auto xaf = cast(slice::x8<float>);
        inline auto xvd = cast<vec_t<double>>(xad);
        inline auto xvf = cast<vec_t<float>>(xaf);
        /* TODO: find-out how to left-out specifying size of array */
        inline auto xfd = cast<fdvec_t<8>>(xad);
        inline auto xff = cast<ffvec_t<8>>(xaf);
        inline constexpr auto i = 3;
    }
    namespace case2::expect {
        inline auto x = 4;
    }
}

namespace nmtools::testing::data::row
{
    namespace case1::args {
        inline auto xad = common_matrix::magic::mad5x5;
        inline auto xaf = common_matrix::magic::maf5x5;
        inline auto xvd = common_matrix::magic::mvd5x5;
        inline auto xvf = common_matrix::magic::mvf5x5;
        inline auto xfd = common_matrix::magic::mfd5x5;
        inline auto xff = common_matrix::magic::mff5x5;
        inline constexpr auto r = 2;
    }
    namespace case1::expect {
        inline auto x = std::array<double,5>{ 4,    5,   13,   20,   22};
    }
}

namespace nmtools::testing::data::column
{
    namespace case1::args {
        inline auto xad = common_matrix::magic::mad5x5;
        inline auto xaf = common_matrix::magic::maf5x5;
        inline auto xvd = common_matrix::magic::mvd5x5;
        inline auto xvf = common_matrix::magic::mvf5x5;
        inline auto xfd = common_matrix::magic::mfd5x5;
        inline auto xff = common_matrix::magic::mff5x5;
        inline auto c = 2;
    }
    namespace case1::expect {
        inline auto x = std::array<double,5>{ 1, 7, 13, 19, 25};
    }
}

#endif // NMTOOLS_TESTING_DATA_UTILITY_HPP