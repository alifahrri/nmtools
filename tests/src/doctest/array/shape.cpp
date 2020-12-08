#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/utility/helper.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
using nmtools::utils::isequal;
using nm::meta::index_constant;
using nm::array::fixed_vector;
using nm::array::fixed_matrix;
using nm::array::fixed_ndarray;
using nm::array::dynamic_vector;
using nm::array::dynamic_matrix;
using nm::array::dynamic_ndarray;
using std::array;
using std::tuple;

TEST_CASE("shape(std::array<>)" * doctest::test_suite("shape"))
{
    {
        auto a = array{1,2,3,4,5,6};
        auto s = nm::shape(a);
        // @todo whenever the dim is constant return it as compile-time constant
        // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
        // static_assert( std::is_same_v< decltype(s) ,tuple< index_constant<6> > > );
        NMTOOLS_ASSERT_EQUAL(s, array{6});
    }
    {
        auto a = array{
            array{1,2,3},
            array{4,5,6}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3}));
    }
    {
        auto a = array{
            array{array{1},array{2},array{3}},
            array{array{4},array{5},array{6}}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3,1}));
    }
}

TEST_CASE("shape(double[])" * doctest::test_suite("shape"))
{
    {
        double a[6] = {1,2,3,4,5,6};
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, array{6});
    }
    {
        double a[2][3] = {
            {1,2,3},
            {4,5,6}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3}));
    }
    {
        double a[2][3][1] = {
            {{1},{2},{3}},
            {{4},{5},{6}}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3,1}));
    }
    {
        double a[2][1][3][1] = {
            {{{1},{2},{3}}},
            {{{4},{5},{6}}}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,1,3,1}));
    }
}

TEST_CASE("shape(fixed_vector<>)" * doctest::test_suite("shape"))
{
    {
        // @todo support CTAD
        auto a = fixed_vector<double,6>{};
        auto s = nm::shape(a);
        // @todo whenever the dim is constant return it as compile-time constant
        // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
        // static_assert( std::is_same_v< decltype(s) ,tuple< index_constant<6> > > );
        NMTOOLS_ASSERT_EQUAL(s, (array{6}));
    }
}

TEST_CASE("shape(fixed_matrix<>)" * doctest::test_suite("shape"))
{
    {
        // @todo support CTAD
        auto a = fixed_matrix<double,2,3>{};
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3}));
    }
}

TEST_CASE("shape(fixed_ndarray<>)" * doctest::test_suite("shape"))
{
    {
        // @todo support CTAD
        auto a = fixed_ndarray<double,2,3,1>{};
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3,1}));
    }
    {
        // @todo support CTAD
        auto a = fixed_ndarray<double,2,1,3,1>{};
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,1,3,1}));
    }
}

TEST_CASE("shape(dynamic_vector<>)" * doctest::test_suite("shape"))
{
    {
        auto a = dynamic_vector{1.,2.,3.,4.,5.,6.};
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{6}));
    }
}

TEST_CASE("shape(dynamic_matrix<>)" * doctest::test_suite("shape"))
{

    {
        auto a = dynamic_matrix{
            {1.,2.,3.}, {4.,5.,6.,}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3}));
    }
}

TEST_CASE("shape(dynamic_ndarray<>)" * doctest::test_suite("shape"))
{
    {
        auto a = dynamic_ndarray({1.,2.,3.,4.,5.,6.});
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{6}));
    }
    {
        auto a = dynamic_ndarray({
            {1.,2.,3.},
            {4.,5.,6.}
        });
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3}));
    }
    {
        // @note need to specify tparam double and add literal ul (size_t)
        // otherwise falsely deduce class template
        // auto a = dynamic_ndarray<double>{std::vector{2ul,3ul,1ul}};
        // auto s = nm::shape(a);
        // NMTOOLS_ASSERT_EQUAL(s, (array{2,3,1}));
    }
}

TEST_CASE("shape(vector<>)" * doctest::test_suite("shape"))
{
    using std::vector;
    {
        auto a = vector{1.,2.,3.,4.,5.,6.};
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{6}));
    }
    {
        auto a = vector{
            vector{1.,2.,3.},
            vector{4.,5.,6.}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3}));
    }
    {
        auto a = vector{
            vector{vector{1.},vector{2.},vector{3.}},
            vector{vector{4.},vector{5.},vector{6.}}
        };
        auto s = nm::shape(a);
        NMTOOLS_ASSERT_EQUAL(s, (array{2,3,1}));
    }
}