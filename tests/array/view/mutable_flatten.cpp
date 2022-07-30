#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/testing.hpp"

#include <array>
#include <vector>

namespace view = nmtools::view;
using nmtools::utils::isclose;
using nmtools::utils::isequal;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_ndarray;

TEST_CASE("mutable_flatten(double[N])" * doctest::test_suite("view::mutable_flatten"))
{
    double array[3] = {1.,2.,3.};
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),nmtools_array{3}) );

    STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK( isequal(shape, nmtools_array{3}) );
    }

    {
        auto expected = nmtools_array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = nmtools_array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    {
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( nmtools::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    }
}

TEST_CASE("mutable_flatten(double[2][3])" * doctest::test_suite("view::mutable_flatten"))
{
    double array[2][3] = {
        {1.,2.,3.},
        {3.,4.,5.},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),nmtools_array{6}) );
    STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK( isequal(shape, nmtools_array{6}) );
    }

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        double expected[2][3] = {
            {1.,6.,3.},
            {7.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }
}

TEST_CASE("mutable_flatten(double[2][3][1])" * doctest::test_suite("view::mutable_flatten"))
{
    double array[2][3][1] = {
        {{1.},{2.},{3.}},
        {{3.},{4.},{5.}},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),nmtools_array{6}) );

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        double expected[2][3][1] = {
            {{1.},{6.},{3.}},
            {{7.},{4.},{5.}},
        };
        CHECK( isclose(array,expected) );
    }
}

TEST_CASE("mutable_flatten(nmtools_array)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = nmtools_array{1.,2.,3.};
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),nmtools_array{3}) );

    {
        auto expected = nmtools_array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = nmtools_array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( nmtools::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("mutable_flatten(nmtools_array[2])" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = nmtools_array{
        nmtools_array{1.,2.,3.},
        nmtools_array{3.,4.,5.},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),nmtools_array{6}) );

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        auto expected = nmtools_array{
            nmtools_array{1.,6.,3.},
            nmtools_array{7.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }
}
#endif // NMTOOLS_DISABLE_STL

TEST_CASE("mutable_flatten(nmtools_list)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = nmtools_list{1.,2.,3.};
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),nmtools_array{3}) );

    {
        auto expected = nmtools_array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = nmtools_array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( nmtools::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("flatten(nmtools_list[2])" * doctest::test_suite("view::flatten"))
{
    auto array = nmtools_list{
        nmtools_list{1.,2.,3.},
        nmtools_list{3.,4.,5.},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),nmtools_array{6}) );

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        auto expected = nmtools_list{
            nmtools_list{1.,6.,3.},
            nmtools_list{7.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }
}
#endif // NMTOOLS_DISABLE_STL

TEST_CASE("mutable_flatten(fixed_ndarray[2])" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = fixed_ndarray{{
        {1.,2.,3.},
        {3.,4.,5.},
    }};
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        double expected[2][3] = {
            {1.,6.,3.},
            {7.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }
}

TEST_CASE("mutable_flatten(fixed_ndarray[3])" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = fixed_ndarray<double,2,3,1>{};
    array = {
        {{1.},{2.},{3.}},
        {{3.},{4.},{5.}},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),nmtools_array{6}) );

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        double expected[2][3][1] = {
            {{1.},{6.},{3.}},
            {{7.},{4.},{5.}},
        };
        CHECK( isclose(array,expected) );
    }
}

TEST_CASE("mutable_flatten(fixed_ndarray[4])" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = fixed_ndarray<double,2,1,3,1>{};
    array = {
        {{{1.},{2.},{3.}}},
        {{{3.},{4.},{5.}}},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),nmtools_array{6}) );

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        double expected[2][1][3][1] = {
            {{{1.},{6.},{3.}}},
            {{{7.},{4.},{5.}}},
        };
        CHECK( isclose(array,expected) );
    }
}

TEST_CASE("mutable_flatten(fixed_ndarray[5])" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = fixed_ndarray<double,1,2,1,3,1>{};
    array = {{
        {{{1.},{2.},{3.}}},
        {{{3.},{4.},{5.}}},
    }};
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),nmtools_array{6}) );

    {
        auto expected = nmtools_array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        double expected[1][2][1][3][1] = {{
            {{{1.},{6.},{3.}}},
            {{{7.},{4.},{5.}}},
        }};
        CHECK( isclose(array,expected) );
    }
}