#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;
namespace utility = nm::utility;

using namespace nmtools::literals;

using nmtools_array;

TEST_CASE("has_path(case1)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,3>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,5>{
        make_vector(1,2),
        make_vector(3),
        make_vector(4),
        make_vector(),
        make_vector(),
    };

    {
        auto result = utility::has_path(adj_list,0,4);
        auto expect = true;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = utility::has_path(adj_list,0,3);
        auto expect = true;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = utility::has_path(adj_list,1,2);
        auto expect = false;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("has_path(case2)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,3>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,5>{
        make_vector(1,2),
        make_vector(3),
        make_vector(),
        make_vector(),
        make_vector(),
    };

    {
        auto result = utility::has_path(adj_list,0,4);
        auto expect = false;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = utility::has_path(adj_list,0,3);
        auto expect = true;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = utility::has_path(adj_list,1,2);
        auto expect = false;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = utility::has_path(adj_list,2,4);
        auto expect = false;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("has_path(case3)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,3>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,3>{
        make_vector(1),
        make_vector(2),
        make_vector(),
    };

    {
        auto result = utility::has_path(adj_list,0,0);
        auto expect = true;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("has_path(case4)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,3>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,3>{
        make_vector(),
        make_vector(2),
        make_vector(),
    };

    {
        auto result = utility::has_path(adj_list,0,2);
        auto expect = false;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("has_path(case5)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,3>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,13>{
        make_vector(1,3),
        make_vector(3),
        make_vector(3),
        make_vector(5,8),
        make_vector(5),
        make_vector(7),
        make_vector(7),
        make_vector(8),
        make_vector(10),
        make_vector(10),
        make_vector(12),
        make_vector(12),
        make_vector(),
    };

    {
        auto result = utility::has_path(adj_list,3,5);
        auto expect = true;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = utility::has_path(adj_list,3,7);
        auto expect = true;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
    {
        auto result = utility::has_path(adj_list,8,7);
        auto expect = false;
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}