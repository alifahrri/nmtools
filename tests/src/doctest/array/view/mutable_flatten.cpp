#include "testing/doctest.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/utility/helper.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/testing.hpp"

#include <array>
#include <vector>

namespace view = nmtools::view;
using nmtools::utils::isclose;
using nmtools::utils::isequal;
using nmtools::array::fixed_vector;
using nmtools::array::fixed_matrix;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_vector;
using nmtools::array::dynamic_matrix;
using nmtools::array::dynamic_ndarray;

TEST_CASE("mutable_flatten(double[N])" * doctest::test_suite("view::mutable_flatten"))
{
    double array[3] = {1.,2.,3.};
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK( isequal(shape, std::array{3}) );
    }
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    {
        // view should have meta::fixed_ndarray_shape if its underlying array have too
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
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
    CHECK( isequal(array_ref.shape(),std::array{6}) );
    STATIC_CHECK(( nmtools::meta::is_ndarray_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));
    {
        constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
        STATIC_CHECK( isequal(shape, std::array{6}) );
    }

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
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
    {
        using view_type = typename decltype(array_ref)::view_type;
        auto index = static_cast<view_type>(array_ref).index(0);
        auto expected = std::array{0,0,0};
        // CHECK( isclose(index,expected) );
    }
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
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

TEST_CASE("mutable_flatten(std::array)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("mutable_flatten(std::array[2])" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{7.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }
}

TEST_CASE("mutable_flatten(std::vector)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("flatten(std::vector[2])" * doctest::test_suite("view::flatten"))
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        auto expected = std::vector{
            std::vector{1.,6.,3.},
            std::vector{7.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }
}

TEST_CASE("mutable_flatten(fixed_vector)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = fixed_vector({1.,2.,3.});
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("mutable_flatten(fixed_matrix)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = fixed_matrix{{
        {1.,2.,3.},
        {3.,4.,5.},
    }};
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
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

TEST_CASE("mutable_flatten(dynamic_vector)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = dynamic_vector{1.,2.,3.};
    auto array_ref = view::mutable_flatten(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isequal(array_ref.shape(),std::array{3}) );

    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // LOG_TYPEINFO( decltype(array_ref) );
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_vector_v<decltype(array_ref)> ));

    {
        auto expected = std::array{1.,2.,3.};
        CHECK( isclose(array_ref,expected) );
    }

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3;

    {
        nmtools::at(array_ref,0) = 3;
        auto expected = std::array{3.,2.,3.};
        CHECK( isclose(array,expected) );
    }

    // {
    //     // view should have meta::fixed_ndarray_shape if its underlying array have too
    //     constexpr auto shape = nmtools::meta::fixed_ndarray_shape_v<decltype(array_ref)>;
    //     STATIC_CHECK(( std::get<0>(shape)==3 ));
    //     STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    // }
}

TEST_CASE("mutable_flatten(dynamic_matrix)" * doctest::test_suite("view::mutable_flatten"))
{
    auto array = dynamic_matrix{
        {1.,2.,3.},
        {3.,4.,5.},
    };
    auto array_ref = view::mutable_flatten(array);
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( !nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isequal(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        auto expected = dynamic_matrix{
            {1.,6.,3.},
            {7.,4.,5.},
        };
        CHECK( isclose(array,expected) );
    }
}

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
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
        CHECK( isclose(array_ref,expected) );
    }
    {
        nmtools::at(array_ref,1) = 6;
        nmtools::at(array_ref,3) = 7;
        auto expected = std::array{
            std::array{1.,6.,3.},
            std::array{7.,4.,5.},
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
    {
        using view_type = typename decltype(array_ref)::view_type;
        auto index = static_cast<view_type>(array_ref).index(0);
        auto expected = std::array{0,0,0};
        // CHECK( isclose(index,expected) );
    }
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
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
    {
        using view_type = typename decltype(array_ref)::view_type;
        auto index = static_cast<view_type>(array_ref).index(0);
        auto expected = std::array{0,0,0};
        // CHECK( isclose(index,expected) );
    }
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
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
    {
        using view_type = typename decltype(array_ref)::view_type;
        auto index = static_cast<view_type>(array_ref).index(0);
        auto expected = std::array{0,0,0};
        // CHECK( isclose(index,expected) );
    }
    STATIC_CHECK(( nmtools::meta::is_array1d_v<decltype(array_ref)> ));
    STATIC_CHECK(( nmtools::meta::is_fixed_size_ndarray_v<decltype(array_ref)> ));

    CHECK( array_ref.dim()==1 );
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{6}) );

    {
        auto expected = std::array{1.,2.,3.,3.,4.,5.};
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