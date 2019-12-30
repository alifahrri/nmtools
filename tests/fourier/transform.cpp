#include <gtest/gtest.h>
#include "nmtools/fourier/transform.hpp"
#include <array>
#include <vector>

TEST(fourier, dft_std_array) {
    using namespace std::complex_literals;
    std::array<std::complex<double>,4> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::array<std::complex<double>,4> Xt = {
        2, -2.-2i, -2i, 4.+4i
    };
    auto X = nmtools::fourier::dft(x);
    constexpr double zero = 1e-4;
    for (size_t i=0; i<Xt.size(); i++)
        EXPECT_NEAR( std::abs(X[i]-Xt[i]), 0, zero );
}

TEST(fourier, dft_std_vector) {
    using namespace std::complex_literals;
    std::vector<std::complex<double>> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::vector<std::complex<double>> Xt = {
        2, -2.-2i, -2i, 4.+4i
    };
    auto X = nmtools::fourier::dft(x);
    constexpr double zero = 1e-4;
    for (size_t i=0; i<Xt.size(); i++)
        EXPECT_NEAR( std::abs(X[i]-Xt[i]), 0, zero );
}

TEST(fourier, dft_raw_array) {
    using namespace std::complex_literals;
    std::complex<double> x[] = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::complex<double> Xt[] = {
        2, -2.-2i, -2i, 4.+4i
    };
    auto X = nmtools::fourier::dft(x);
    constexpr double zero = 1e-4;
    for (size_t i=0; i<std::size(Xt); i++)
        EXPECT_NEAR( std::abs(X[i]-Xt[i]), 0, zero );
}

TEST(fourier, fft2_copy_vector) {
    using namespace std::complex_literals;
    std::vector<std::complex<double>> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::vector<std::complex<double>> xo, xe;
    nmtools::fourier::detail::fft2_copy(x,xo,xe,std::size(x));
    EXPECT_EQ(xo.size(),2);
    EXPECT_EQ(xe.size(),2);
    EXPECT_EQ(xo[0],std::complex<double>{1});
    EXPECT_EQ(xo[1],std::complex<double>{-1i});
    EXPECT_EQ(xe[0],std::complex<double>{2.-1i});
    EXPECT_EQ(xe[1],std::complex<double>{-1.+2i});
}

TEST(fourier, fft2_copy_array) {
    using namespace std::complex_literals;
    std::array<std::complex<double>,4> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    nmtools::fourier::detail::fft_stdcomplex_alloc_t<decltype(x)> xo, xe;
    nmtools::fourier::detail::fft2_copy(x,xo,xe,std::size(x));
    EXPECT_EQ(xo[0],std::complex<double>{1});
    EXPECT_EQ(xo[1],std::complex<double>{-1i});
    EXPECT_EQ(xe[0],std::complex<double>{2.-1i});
    EXPECT_EQ(xe[1],std::complex<double>{-1.+2i});
}

TEST(fourier, fft2_vector_insert) {
    using namespace std::complex_literals;
    using namespace nmtools;
    std::vector<std::complex<double>> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::vector<std::complex<double>> X0 = { 1, -1i };
    std::vector<std::complex<double>> X1 = { 2.-1i, -1.+2i };
    fourier::detail::fft_stdcomplex_alloc_t<decltype(x)> X{};
    auto N = std::size(x);
    auto o_odd_it = std::begin(X);
    auto [i_odd_it,i_even_it] = std::make_tuple( std::begin(X0), std::begin(X1) );
    auto [i_odd_end,i_even_end] = std::make_tuple( i_odd_it+(N/2), i_even_it+(N/2) );
    helper::insert(X, o_odd_it,  i_odd_it,  i_odd_end);
    auto o_even_it = std::begin(X) + N/2;
    helper::insert(X, o_even_it, i_even_it, i_even_end);
    EXPECT_EQ(X.size(),4);
    EXPECT_EQ(X[0],std::complex<double>{1});
    EXPECT_EQ(X[1],std::complex<double>{-1i});
    EXPECT_EQ(X[2],std::complex<double>{2.-1i});
    EXPECT_EQ(X[3],std::complex<double>{-1.+2i});
}

TEST(fourier, fft2_std_vector) {
    using namespace std::complex_literals;
    std::vector<std::complex<double>> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::vector<std::complex<double>> Xt = {
        2, -2.-2i, -2i, 4.+4i
    };
    auto X = nmtools::fourier::fft2(x);
    constexpr double zero = 1e-4;
    for (size_t i=0; i<Xt.size(); i++)
        EXPECT_NEAR( std::abs(X[i]-Xt[i]), 0, zero ) << i;
}

TEST(fourier, fft2_std_array) {
    using namespace std::complex_literals;
    std::array<std::complex<double>,4> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::array<std::complex<double>,4> Xt = {
        2, -2.-2i, -2i, 4.+4i
    };
    auto X = nmtools::fourier::fft2(x);
    constexpr double zero = 1e-4;
    for (size_t i=0; i<Xt.size(); i++)
        EXPECT_NEAR( std::abs(X[i]-Xt[i]), 0, zero ) << i;
}

TEST(fourier_type_deduction, tag) {
    using namespace std::complex_literals;
    std::array<std::complex<double>,4> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    std::vector<std::complex<double>> v = {
        1, 2.-1i, -1i, -1.+2i
    };
    using array_tag = typename nmtools::helper::tag::resolve_insert_tag<decltype(x),decltype(x[0])>::type;
    using vector_tag = typename nmtools::helper::tag::resolve_insert_tag<decltype(v),decltype(v[0])>::type;
    static_assert(
        std::is_same_v<array_tag,nmtools::helper::tag::raw>
    );
    static_assert(
        std::is_same_v<vector_tag,nmtools::helper::tag::insert>
    );
}

TEST(fourier_type_deduction, raw_array) {
    using namespace std::complex_literals;
    using namespace nmtools::fourier;
    std::complex<double> x[] = {
        1, 2.-1i, -1i, -1.+2i
    };
    static_assert(std::is_same_v<
        detail::fft_stdcomplex_raw_t<decltype(x)>,
        std::complex<double>*
    >);
}

TEST(fourier_type_deduction, std_array) {
    using namespace std::complex_literals;
    using namespace nmtools::fourier;
    std::array<std::complex<double>,4> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    static_assert(std::is_same_v<
        detail::fft_stdcomplex_alloc_t<decltype(x)>,
        std::array<std::complex<double>,4>
    >);
}

TEST(fourier_type_deduction, std_vector) {
    using namespace std::complex_literals;
    using namespace nmtools::fourier;
    std::vector<std::complex<double>> x = {
        1, 2.-1i, -1i, -1.+2i
    };
    static_assert(std::is_same_v<
        detail::fft_stdcomplex_alloc_t<decltype(x)>,
        std::vector<std::complex<double>>
    >);
}

TEST(numeric_traits, is_std_array) {
    using namespace nmtools;
    std::array<double,10> array;
    std::vector<double> vector;
    static_assert(traits::is_std_array<decltype(array)>::value);
    static_assert(!traits::is_std_array<decltype(vector)>::value);
}

TEST(numeric_traits, is_std_complex) {
    using namespace nmtools;
    std::complex<double> z;
    double x;
    static_assert(traits::is_std_complex<decltype(z)>::value);
    static_assert(!traits::is_std_complex<decltype(x)>::value);
}

TEST(numeric_traits, is_insertable) {
    using namespace nmtools;
    std::array<double,10> array;
    std::vector<double> vector;
    static_assert(traits::is_insertable<decltype(vector),double>::value);
    static_assert(traits::is_insertable<decltype(vector),decltype(vector.begin()),decltype(array.begin()),decltype(array.end())>::value);
    static_assert(!traits::is_insertable<decltype(array),double>::value);
}

TEST(numeric_traits, is_resizeable) {
    using namespace nmtools;
    std::array<double,10> array;
    std::vector<double> vector;
    static_assert(traits::is_resizeable<decltype(vector)>::value);
    static_assert(!traits::is_resizeable<decltype(array)>::value);
}

TEST(numeric_traits, has_ref_square_bracket_operator) {
    using namespace nmtools;
    std::array<double,10> array;
    std::vector<double> vector;
    static_assert(traits::has_ref_square_bracket_operator<decltype(vector)>::value);
    static_assert(traits::has_ref_square_bracket_operator<decltype(array)>::value);
    static_assert(!traits::has_ref_square_bracket_operator<double>::value);
}