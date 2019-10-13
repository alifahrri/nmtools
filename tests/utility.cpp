#include <gtest/gtest.h>
#include "utility.hpp"

TEST(utility, constants) {
    namespace detail = numeric::helper::detail;
    constexpr detail::Constants<double,100,50,25,25> constants;
    static_assert(constants.values[0]==0.5);
    static_assert(constants.values[1]==0.25);
    static_assert(constants.values[2]==0.25);
}

TEST(utility, append_array) {
    namespace hp = numeric::helper;
    std::array<double,4> a{ 1., 2., 3., 4. };
    auto b = hp::append(a, 5.);
    static_assert( std::is_same_v<std::array<double,5>,decltype(b)> );
    EXPECT_EQ(b[4],5.);
}

TEST(utility, append_vector) {
    namespace hp = numeric::helper;
    std::vector<double> a{ 1., 2., 3., 4. };
    auto b = hp::append(a, 5.);
    static_assert( std::is_same_v<std::vector<double>,decltype(b)> );
    EXPECT_EQ(b.size(),5);
    EXPECT_EQ(b[4],5.);
}

TEST(traits, is_callable) {
    namespace nm = numeric;
    auto f1 = [](double) {};
    auto f2 = [](double,double) {};
    static_assert( nm::traits::is_callable<decltype(f1),double>::value);
    static_assert(!nm::traits::is_callable<decltype(f1),double,double>::value);
    static_assert( nm::traits::is_callable<decltype(f2),double,double>::value);
    static_assert(!nm::traits::is_callable<decltype(f2),double>::value);
}

TEST(traits, multiplicative) {
    namespace nm = numeric;
    auto f1 = [](double) { return double{}; };
    auto f2 = [](double,double) { return double{}; };
    static_assert( nm::traits::multiplicative<decltype(f1(double{})),decltype(f2(double{},double{}))>::value );
    static_assert(!nm::traits::multiplicative<double,std::string>::value);
}

TEST(traits, additive) {
    namespace nm = numeric;
    auto f1 = [](double) { return double{}; };
    auto f2 = [](double,double) { return double{}; };
    static_assert( nm::traits::additive<decltype(f1(double{})),decltype(f2(double{},double{}))>::value );
    static_assert(!nm::traits::additive<double,std::string>::value);
}

struct transposeable_t {
    std::array<double,2> transpose() {
        return std::array<double,2>{};
    }
};

TEST(traits, has_transpose_op) {
    namespace nm = numeric;
    static_assert( nm::traits::has_transpose_op<transposeable_t>::value );
    static_assert(!nm::traits::has_transpose_op<double>::value );
}

TEST(traits, is_transposeable) {
    namespace nm = numeric;
    static_assert( nm::traits::is_transposeable<transposeable_t>::value );
    static_assert( nm::traits::is_transposeable<double>::value );
    static_assert(!nm::traits::is_transposeable<std::string>::value );
}

TEST(helper, transpose) 
{
    namespace nm = numeric;
    static_assert( std::is_same_v<
        decltype(nm::helper::transpose(transposeable_t{})),
        std::array<double,2>
    >);
    static_assert( std::is_same_v<
        decltype(nm::helper::transpose(double{})), double
    >);
}