#include "nmtools/index/ndindex.hpp"
#include "nmtools/utility/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
using namespace nm::literals;
using nmtools::utils::isequal;
#ifndef NMTOOLS_DISABLE_STL
using std::tuple;
using std::vector;
#else
using nmtools_tuple;
#endif

TEST_CASE("ndindex({3,2})" * doctest::test_suite("index"))
{
    auto shape_ = nmtools_tuple{3,2};
    auto indices = nm::index::ndindex(shape_);
    REQUIRE( indices.size() == 6 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,nmtools_tuple{0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,nmtools_tuple{0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,nmtools_tuple{1,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,nmtools_tuple{1,1}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,nmtools_tuple{2,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,nmtools_tuple{2,1}) ));
    }
}

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("ndindex(vector{3,2})" * doctest::test_suite("index"))
{
    // NOTE: ndindex doesnt support temporary for now
    // TODO: support temporary (?)
    auto shape_ = vector{3,2};
    auto indices = nm::index::ndindex(shape_);
    REQUIRE( indices.size() == 6 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,vector{0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,vector{0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,vector{1,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,vector{1,1}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,vector{2,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,vector{2,1}) ));
    }
}
#endif

TEST_CASE("ndindex({3,2,3})" * doctest::test_suite("index"))
{
    auto shape_ = nmtools_tuple{3,2,3};
    auto indices = nm::index::ndindex(shape_);
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,nmtools_tuple{0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,nmtools_tuple{0,0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,nmtools_tuple{0,0,2}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,nmtools_tuple{0,1,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,nmtools_tuple{0,1,1}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,nmtools_tuple{0,1,2}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,nmtools_tuple{1,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,nmtools_tuple{1,0,1}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,nmtools_tuple{1,0,2}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,nmtools_tuple{1,1,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,nmtools_tuple{1,1,1}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,nmtools_tuple{1,1,2}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,nmtools_tuple{2,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,nmtools_tuple{2,0,1}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,nmtools_tuple{2,0,2}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,nmtools_tuple{2,1,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,nmtools_tuple{2,1,1}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,nmtools_tuple{2,1,2}) ));
    }
}

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("ndindex({3,2,3})" * doctest::test_suite("index"))
{
    auto shape_ = vector{3,2,3};
    auto indices = nm::index::ndindex(shape_);
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,vector{0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,vector{0,0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,vector{0,0,2}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,vector{0,1,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,vector{0,1,1}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,vector{0,1,2}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,vector{1,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,vector{1,0,1}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,vector{1,0,2}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,vector{1,1,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,vector{1,1,1}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,vector{1,1,2}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,vector{2,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,vector{2,0,1}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,vector{2,0,2}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,vector{2,1,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,vector{2,1,1}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,vector{2,1,2}) ));
    }
}
#endif // NMTOOLS_DISABLE_STL

TEST_CASE("ndindex({3,2,3,1})" * doctest::test_suite("index"))
{
    auto shape_  = nmtools_tuple{3,2,3,1};
    auto indices = nm::index::ndindex(shape_);
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,nmtools_tuple{0,0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,nmtools_tuple{0,0,1,0}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,nmtools_tuple{0,0,2,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,nmtools_tuple{0,1,0,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,nmtools_tuple{0,1,1,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,nmtools_tuple{0,1,2,0}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,nmtools_tuple{1,0,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,nmtools_tuple{1,0,1,0}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,nmtools_tuple{1,0,2,0}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,nmtools_tuple{1,1,0,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,nmtools_tuple{1,1,1,0}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,nmtools_tuple{1,1,2,0}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,nmtools_tuple{2,0,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,nmtools_tuple{2,0,1,0}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,nmtools_tuple{2,0,2,0}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,nmtools_tuple{2,1,0,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,nmtools_tuple{2,1,1,0}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,nmtools_tuple{2,1,2,0}) ));
    }
}

TEST_CASE("ndindex({3,2,3,1})" * doctest::test_suite("index"))
{
    auto shape_  = nmtools_tuple{2,3,1,3,1};
    auto indices = nm::index::ndindex(shape_);
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,nmtools_tuple{0,0,0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,nmtools_tuple{0,0,0,1,0}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,nmtools_tuple{0,0,0,2,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,nmtools_tuple{0,1,0,0,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,nmtools_tuple{0,1,0,1,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,nmtools_tuple{0,1,0,2,0}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,nmtools_tuple{0,2,0,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,nmtools_tuple{0,2,0,1,0}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,nmtools_tuple{0,2,0,2,0}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,nmtools_tuple{1,0,0,0,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,nmtools_tuple{1,0,0,1,0}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,nmtools_tuple{1,0,0,2,0}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,nmtools_tuple{1,1,0,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,nmtools_tuple{1,1,0,1,0}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,nmtools_tuple{1,1,0,2,0}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,nmtools_tuple{1,2,0,0,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,nmtools_tuple{1,2,0,1,0}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,nmtools_tuple{1,2,0,2,0}) ));
    }
}