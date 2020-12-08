// TODO: support dynamic size array for at
#define NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY
// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/utility/zeros_like.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <vector>

using std::tuple;
using std::vector;
namespace nm = nmtools;

TEST_CASE("detail::resize(vector)" * doctest::test_suite("utility"))
{
    {
        auto a = vector<double>{};
        a = nm::detail::resize(a,3);
        NMTOOLS_ASSERT_EQUAL(a.size(), 3);
    }
}

TEST_CASE("detail::resize(vector[2])" * doctest::test_suite("utility"))
{
    {
        auto a = vector<vector<double>>{};
        a = nm::detail::resize(a,3,5);
        NMTOOLS_ASSERT_EQUAL(a.size(), 3);
        for (auto& b : a)
            NMTOOLS_ASSERT_EQUAL(b.size(), 5);
    }
}

TEST_CASE("detail::resize(vector[3])" * doctest::test_suite("utility"))
{
    {
        auto a = vector<vector<vector<double>>>{};
        a = nm::detail::resize(a,3,5,1);
        NMTOOLS_ASSERT_EQUAL(a.size(), 3);
        for (auto& b : a) {
            NMTOOLS_ASSERT_EQUAL(b.size(), 5);
            for (auto& c : b)
                NMTOOLS_ASSERT_EQUAL(c.size(), 1);
        }
    }
}

TEST_CASE("zeros_like(vector)" * doctest::test_suite("utility"))
{
    {
        auto a = vector{1,2,3};
        auto r = nm::zeros_like(a);
        NMTOOLS_ASSERT_CLOSE( r, (vector{0,0,0}) );
    }
}

TEST_CASE("zeros_like(double[])" * doctest::test_suite("utility"))
{
    {
        double a[3] = {1,2,3};
        auto r = nm::zeros_like(a);
        NMTOOLS_ASSERT_CLOSE( r, (vector{0,0,0}) );
    }
}

TEST_CASE("zeros_like(vector[2])" * doctest::test_suite("utility"))
{
    {
        auto a = vector<vector<double>>{{1,2,3},{4,5,6}};
        auto e = vector<vector<double>>{{0,0,0},{0,0,0}};
        auto r = nm::zeros_like(a);
        NMTOOLS_ASSERT_CLOSE( r, e );
    }
}

TEST_CASE("zeros_like(double[2])" * doctest::test_suite("utility"))
{
    {
        double a[2][3] = {{1,2,3},{4,5,6}};
        double e[2][3] = {{0,0,0},{0,0,0}};
        auto r = nm::zeros_like(a);
        NMTOOLS_ASSERT_CLOSE( r, e );
    }
}

TEST_CASE("zeros_like(vector[3])" * doctest::test_suite("utility"))
{
    {
        double a[2][2][3] = {{{1,2,3},{4,5,6}},{{1,2,3},{4,5,6}}};
        double e[2][2][3] = {{{0,0,0},{0,0,0}},{{0,0,0},{0,0,0}}};
        auto r = nm::zeros_like(a);
        NMTOOLS_ASSERT_CLOSE( r, e );
    }
}