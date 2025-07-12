#include "nmtools/ndarray/array.hpp"
#include "nmtools/testing/doctest.hpp"

TEST_CASE("view(case1)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1,2,3,4,5};
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a + 1;
    auto expect = nmtools_array{2,3,4,5,6};
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("view(case2)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1,2,3,4,5};
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a * 2;
    auto expect = nmtools_array{2,4,6,8,10};
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("view(case3)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1,2,3,4,5};
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a - 2;
    auto expect = nmtools_array{-1,0,1,2,3};
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("view(case4)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1.f,2.f,3.f,4.f,5.f};
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a / 2;
    auto expect = nmtools_array{.5f,1.f,1.5f,2.f,2.5f};
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case5)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1.f,2.f,3.f,4.f,5.f};
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a.max();
    auto expect = nmtools::view::amax(buffer);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case6)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1.f,2.f,3.f,4.f,5.f};
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a.min();
    auto expect = nmtools::view::amin(buffer);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case7)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a.flatten();
    auto expect = nmtools::view::flatten(buffer);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case8a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a.mean();
    auto expect = nmtools::view::mean(buffer);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case8b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto axis   = -1;
    auto result = a.mean(axis);
    auto expect = nmtools::view::mean(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case9a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a.sum();
    auto expect = nmtools::view::sum(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case9b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto axis   = -1;
    auto result = a.sum(axis);
    auto expect = nmtools::view::sum(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case10a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.prod();
    auto expect = nmtools::view::prod(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case10b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto axis = -1;
    auto result = a.prod(axis);
    auto expect = nmtools::view::prod(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case11a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.var();
    auto expect = nmtools::view::var(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case11b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto axis = -1;
    auto result = a.var(axis);
    auto expect = nmtools::view::var(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case12a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.std();
    auto expect = nmtools::view::std(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case12b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto axis = -1;
    auto result = a.std(axis);
    auto expect = nmtools::view::std(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case13a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.diagonal();
    auto expect = nmtools::view::diagonal(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case13b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto offset = 1;
    auto result = a.diagonal(offset);
    auto expect = nmtools::view::diagonal(buffer,offset);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case14)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto dst_shape = nmtools_array{3,2};
    auto result = a.reshape(dst_shape);
    auto expect = nmtools::view::reshape(buffer,dst_shape);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case15a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto repeats = 2;
    auto result = a.repeat(repeats);
    auto expect = nmtools::view::repeat(buffer,repeats);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case15b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto repeats = nmtools_array{3,2};
    auto axis   = 0;
    auto result = a.repeat(repeats,axis);
    auto expect = nmtools::view::repeat(buffer,repeats,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case16a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.squeeze();
    auto expect = nmtools::view::squeeze(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case16b)" * doctest::test_suite("object"))
{
    int buffer[1][2][3] = {
        {
            {0,1,2},
            {3,4,5},
        }
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.squeeze();
    auto expect = nmtools::view::squeeze(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case17)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto axis1 = -1;
    auto axis2 = -2;
    auto result = a.swapaxes(axis1,axis2);
    auto expect = nmtools::view::swapaxes(buffer,axis1,axis2);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case18a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.trace();
    auto expect = nmtools::view::trace(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case18b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto offset = 1;
    auto result = a.trace(offset);
    auto expect = nmtools::view::trace(buffer,offset);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case19)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.transpose();
    auto expect = nmtools::view::transpose(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case20)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto result = a.clip(1,4);
    auto expect = nmtools::view::clip(buffer,1,4);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

// TODO: fix compile
// TEST_CASE("view(case21a)" * doctest::test_suite("object"))
// {
//     int buffer[2][3] = {
//         {0,1,2},
//         {3,4,5},
//     };
//     auto a = nmtools::view::array(buffer);
//     static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
//     static_assert( nmtools::meta::is_view_v<decltype(a)> );
//     auto result = a.cumsum();
//     auto expect = nmtools::view::cumsum(buffer);
//     NMTOOLS_ASSERT_CLOSE( result, expect );
// }

TEST_CASE("view(case21b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto axis   = -1;
    auto result = a.cumsum(axis);
    auto expect = nmtools::view::cumsum(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

// TODO: fix compile
// TEST_CASE("view(case22a)" * doctest::test_suite("object"))
// {
//     int buffer[2][3] = {
//         {0,1,2},
//         {3,4,5},
//     };
//     auto a = nmtools::view::array(buffer);
//     auto result = a.cumprod();
//     auto expect = nmtools::view::cumprod(buffer);
//     NMTOOLS_ASSERT_CLOSE( result, expect );
// }

TEST_CASE("view(case22b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto axis = -1;
    auto result = a.cumprod(axis);
    auto expect = nmtools::view::cumprod(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case23)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    auto axis = -1;
    auto result = a.cumprod(axis).max();
    auto expect = nmtools::view::amax(nmtools::view::cumprod(buffer,axis));
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("view(case24)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a < 1;
    auto expect = nmtools::view::less(buffer,1);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("view(case25)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a <= 1;
    auto expect = nmtools::view::less_equal(buffer,1);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("view(case26)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a > 1;
    auto expect = nmtools::view::greater(buffer,1);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("view(case27)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::view::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    static_assert( nmtools::meta::is_view_v<decltype(a)> );
    auto result = a >= 1;
    auto expect = nmtools::view::greater_equal(buffer,1);
    static_assert( nmtools::meta::is_view_v<decltype(result)> );
    NMTOOLS_ASSERT_EQUAL( result, expect );
}