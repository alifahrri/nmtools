#include "nmtools/utl/static_queue.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

TEST_CASE("static_queue(case1)" * doctest::test_suite("utl"))
{
    auto q = utl::static_queue<int,4>();

    NMTOOLS_ASSERT_EQUAL( q.empty(), true );
}

TEST_CASE("static_queue(case2)" * doctest::test_suite("utl"))
{
    auto q = utl::static_queue<int,4>();

    q.push(1);

    NMTOOLS_ASSERT_EQUAL( q.empty(), false );
    NMTOOLS_ASSERT_EQUAL( q.size(), 1 );

    auto v = q.pop();

    NMTOOLS_ASSERT_EQUAL( q.empty(), true );
    NMTOOLS_ASSERT_EQUAL( v, 1 );

    q.push(2);
    q.push(3);
    q.push(5);

    v = q.pop();

    NMTOOLS_ASSERT_EQUAL( q.empty(), false );
    NMTOOLS_ASSERT_EQUAL( q.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( v, 2 );
    NMTOOLS_ASSERT_EQUAL( q.front(), 3 );
    NMTOOLS_ASSERT_EQUAL( q.back(), 5 );
}