#include "nmtools/array/core/alias.hpp"
#include "nmtools/array/view/arange.hpp"
#include "nmtools/array/view/atleast_nd.hpp"
#include "nmtools/testing/doctest.hpp"

namespace view = nmtools::view;
namespace meta = nmtools::meta;

using nmtools::utils::to_string;

TEST_CASE("aliased(case1)" * doctest::test_suite("view::aliased"))
{
    int a[3] = {1,2,3};
    int b[2] = {4,5};
    auto aliased = view::aliased(a,b);
    auto v_a = nmtools::get<0>(aliased);
    auto v_b = nmtools::get<1>(aliased);
    static_assert( meta::is_ndarray_v<decltype(v_a)> );
    static_assert( meta::is_ndarray_v<decltype(v_b)> );
    NMTOOLS_ASSERT_EQUAL( a, v_a );
    NMTOOLS_ASSERT_EQUAL( b, v_b );
    NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_a)>, 0 );
    NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_b)>, 1 );

    {
        constexpr auto type_id = meta::get_type_id_v<decltype(a)>;
        CHECK_MESSAGE(true, to_string(type_id) );
    }
    {
        constexpr auto type_id = meta::get_type_id_v<decltype(b)>;
        CHECK_MESSAGE(true, to_string(type_id) );
    }
    {
        constexpr auto type_id = meta::get_type_id_v<decltype(v_a)>;
        CHECK_MESSAGE(true, to_string(type_id) );
    }
    {
        constexpr auto type_id = meta::get_type_id_v<decltype(v_b)>;
        CHECK_MESSAGE(true, to_string(type_id) );
    }
}

TEST_CASE("aliased(case2)" * doctest::test_suite("view::aliased"))
{
    int a[3] = {1,2,3};
    int b[2] = {4,5};
    int c[1][3] = {{6,7,8}};
    auto aliased = view::aliased(a,b,c);
    auto v_a = nmtools::get<0>(aliased);
    auto v_b = nmtools::get<1>(aliased);
    auto v_c = nmtools::get<2>(aliased);
    NMTOOLS_ASSERT_EQUAL( a, v_a );
    NMTOOLS_ASSERT_EQUAL( b, v_b );
    NMTOOLS_ASSERT_EQUAL( c, v_c );
    NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_a)>, 0 );
    NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_b)>, 1 );
    NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_c)>, 2 );

    static_assert( meta::has_id_type_v<decltype(v_a)> );
    static_assert( decltype(v_a)::id_type::value == 0 );
}

TEST_CASE("aliased(case2)" * doctest::test_suite("view::aliased"))
{
    int a[3] = {1,2,3};
    int b[2] = {4,5};
    auto c = view::arange(10);
    auto aliased = view::aliased(a,b,c);
    auto v_a = nmtools::get<0>(aliased);
    auto v_b = nmtools::get<1>(aliased);
    auto v_c = nmtools::get<2>(aliased);
    NMTOOLS_ASSERT_CLOSE( a, v_a );
    NMTOOLS_ASSERT_CLOSE( b, v_b );
    NMTOOLS_ASSERT_CLOSE( c, v_c );
    // c is not aliased together with a & b
    constexpr auto c_type_id = meta::get_type_id_v<typename decltype(c)::view_type>;
    NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(c)>, c_type_id );
    // not a simple 1 or 2 because c id is hashed
    // NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_a)>, 1 );
    // NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_b)>, 2 );
    NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_c)>, c_type_id );
}

TEST_CASE("aliased(case2)" * doctest::test_suite("view::aliased"))
{
    int a[3] = {1,2,3};
    int b[2] = {4,5};
    int a2d[1][3] = {{1,2,3}};
    auto c = view::arange(10);
    auto aliased = view::aliased(a,b,c);
    auto v_a = nmtools::get<0>(aliased);
    auto v_b = nmtools::get<1>(aliased);
    auto v_c = nmtools::get<2>(aliased);
    auto v_a_2d = view::atleast_2d(v_a);
    NMTOOLS_ASSERT_CLOSE( v_a, a );
    NMTOOLS_ASSERT_CLOSE( v_b, b );
    NMTOOLS_ASSERT_CLOSE( v_c, c );
    NMTOOLS_ASSERT_CLOSE( v_a_2d, a2d );
    // not a simple 1 or 2 because c id is hashed
    // NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(c)>, 0 );
    // NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_a)>, 1 );
    // NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_b)>, 2 );
    // NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(v_c)>, 0 );
    // NMTOOLS_ASSERT_EQUAL( view::get_id_v<decltype(nmtools::unwrap(v_a_2d))>, 2 );
}