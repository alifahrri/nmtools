#include "nmtools/meta.hpp"
#include "nmtools/meta/stl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("is_fixed_shape(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, array_type );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, array_type );
    }
    {
        using array_type = std::array<float,12>;
        constexpr auto fixed_shape = meta::fixed_shape_v<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index_array, decltype(fixed_shape) );
    }
    {
        using array_type = std::vector<float>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
}

TEST_CASE("is_fixed_dim(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using array_type = std::vector<float>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
}

TEST_CASE("is_fixed_size(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        using array_type = std::vector<float>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, array_type );
    }
}

TEST_CASE("bounded_dim(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using array_type = std::vector<float>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
}

TEST_CASE("bounded_size(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        using array_type = std::vector<float>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, array_type );
    }
}

TEST_CASE("resize_dim(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        using result_t   = meta::resize_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, result_t );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        using result_t   = meta::resize_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, result_t );
    }
    {
        using array_type = std::vector<float>;
        using result_t   = meta::resize_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

TEST_CASE("resize_size(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        using result_t   = meta::resize_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, result_t );
    }
    {
        // can't resize only size, should reshape
        using array_type = std::array<std::array<float,1>,12>;
        using result_t   = meta::resize_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = std::vector<float>;
        using result_t   = meta::resize_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

TEST_CASE("resize_shape(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<2,3,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, result_t );
    }
    {
        using array_type = std::vector<float>;
        using result_t   = meta::resize_shape_t<array_type,meta::as_type<2,3,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

TEST_CASE("resize_bounded_dim(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        using result_t   = meta::resize_bounded_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        using result_t   = meta::resize_bounded_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = std::vector<float>;
        using result_t   = meta::resize_bounded_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

TEST_CASE("resize_bounded_size(case1)" * doctest::test_suite("meta::stl"))
{
    {
        using array_type = std::array<float,12>;
        using result_t   = meta::resize_bounded_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = std::array<std::array<float,1>,12>;
        using result_t   = meta::resize_bounded_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = std::vector<float>;
        using result_t   = meta::resize_bounded_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}