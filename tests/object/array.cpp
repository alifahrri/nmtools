#include "nmtools/ndarray/array.hpp"
#include "nmtools/testing/doctest.hpp"

TEST_CASE("array(case1)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1,2,3,4,5};
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a + 1;
    auto expect = nmtools_array{2,3,4,5,6};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

#if 1
TEST_CASE("array(case2)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1,2,3,4,5};
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a * 2;
    auto expect = nmtools_array{2,4,6,8,10};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("array(case3)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1,2,3,4,5};
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a - 2;
    auto expect = nmtools_array{-1,0,1,2,3};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("array(case4)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1.f,2.f,3.f,4.f,5.f};
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a / 2;
    auto expect = nmtools_array{.5f,1.f,1.5f,2.f,2.5f};
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case5)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1.f,2.f,3.f,4.f,5.f};
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a.max();
    auto expect = nmtools::amax(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case6)" * doctest::test_suite("object"))
{
    auto buffer = nmtools_array{1.f,2.f,3.f,4.f,5.f};
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a.min();
    auto expect = nmtools::amin(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case7)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a.flatten();
    auto expect = nmtools::flatten(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case8a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a.mean();
    auto expect = nmtools::mean(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case8b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto axis   = -1;
    auto result = a.mean(axis);
    auto expect = nmtools::mean(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case9a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a.sum();
    auto expect = nmtools::sum(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case9b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto axis   = -1;
    auto result = a.sum(axis);
    auto expect = nmtools::sum(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case10a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.prod();
    auto expect = nmtools::prod(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case10b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto axis = -1;
    auto result = a.prod(axis);
    auto expect = nmtools::prod(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case11a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.var();
    auto expect = nmtools::var(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case11b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto axis = -1;
    auto result = a.var(axis);
    auto expect = nmtools::var(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case12a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.std();
    auto expect = nmtools::std(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case12b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto axis = -1;
    auto result = a.std(axis);
    auto expect = nmtools::std(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case13a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.diagonal();
    auto expect = nmtools::diagonal(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case13b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto offset = 1;
    auto result = a.diagonal(offset);
    auto expect = nmtools::diagonal(buffer,offset);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case14)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto dst_shape = nmtools_array{3,2};
    auto result = a.reshape(dst_shape);
    auto expect = nmtools::reshape(buffer,dst_shape);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case15a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto repeats = 2;
    auto result = a.repeat(repeats);
    auto expect = nmtools::repeat(buffer,repeats);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

// TODO: fix runtime
TEST_CASE("array(case15b)" * doctest::test_suite("object") * doctest::skip())
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto repeats = nmtools_array{3,2};
    auto axis   = 0;
    auto result = a.repeat(repeats,axis);
    auto expect = nmtools::repeat(buffer,repeats,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case16a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.squeeze();
    auto expect = nmtools::squeeze(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case16b)" * doctest::test_suite("object"))
{
    int buffer[1][2][3] = {
        {
            {0,1,2},
            {3,4,5},
        }
    };
    auto a = nmtools::array(buffer);
    auto result = a.squeeze();
    auto expect = nmtools::squeeze(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case17)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto axis1 = -1;
    auto axis2 = -2;
    auto result = a.swapaxes(axis1,axis2);
    auto expect = nmtools::swapaxes(buffer,axis1,axis2);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case18a)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.trace();
    auto expect = nmtools::trace(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case18b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto offset = 1;
    auto result = a.trace(offset);
    auto expect = nmtools::trace(buffer,offset);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case19)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.transpose();
    auto expect = nmtools::transpose(buffer);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

// TODO: fix eval
TEST_CASE("array(case20)" * doctest::test_suite("object") * doctest::skip())
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto result = a.clip(1,4);
    auto expect = nmtools::clip(buffer,1,4);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

// TODO: fix compile
// TEST_CASE("array(case21a)" * doctest::test_suite("object"))
// {
//     int buffer[2][3] = {
//         {0,1,2},
//         {3,4,5},
//     };
//     auto a = nmtools::array(buffer);
//     static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );

//     auto result = a.cumsum();
//     auto expect = nmtools::cumsum(buffer);
//     NMTOOLS_ASSERT_CLOSE( result, expect );
// }

TEST_CASE("array(case21b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto axis   = -1;
    auto result = a.cumsum(axis);
    auto expect = nmtools::cumsum(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

// TODO: fix compile
// TEST_CASE("array(case22a)" * doctest::test_suite("object"))
// {
//     int buffer[2][3] = {
//         {0,1,2},
//         {3,4,5},
//     };
//     auto a = nmtools::array(buffer);
//     auto result = a.cumprod();
//     auto expect = nmtools::cumprod(buffer);
//     NMTOOLS_ASSERT_CLOSE( result, expect );
// }

TEST_CASE("array(case22b)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto axis = -1;
    auto result = a.cumprod(axis);
    auto expect = nmtools::cumprod(buffer,axis);
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case23)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    auto axis = -1;
    auto result = a.cumprod(axis).max();
    auto expect = nmtools::amax(nmtools::cumprod(buffer,axis));
    NMTOOLS_ASSERT_CLOSE( result, expect );
}

TEST_CASE("array(case24)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a < 1;
    auto expect = nmtools::less(buffer,1);
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("array(case25)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a <= 1;
    auto expect = nmtools::less_equal(buffer,1);
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("array(case26)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a > 1;
    auto expect = nmtools::greater(buffer,1);
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("array(case27)" * doctest::test_suite("object"))
{
    int buffer[2][3] = {
        {0,1,2},
        {3,4,5},
    };
    auto a = nmtools::array(buffer);
    static_assert( nmtools::meta::is_ndarray_v<decltype(a)> );
    auto result = a >= 1;
    auto expect = nmtools::greater_equal(buffer,1);
    NMTOOLS_ASSERT_EQUAL( result, expect );
}
#endif