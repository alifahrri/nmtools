#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("is_fixed_shape(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type = na::hybrid_ndarray<float,12,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
}

TEST_CASE("is_fixed_size(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type = na::hybrid_ndarray<float,12,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, array_type );
    }
}

TEST_CASE("is_fixed_dim(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type = na::hybrid_ndarray<float,12,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
}

TEST_CASE("is_bounded_dim(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type = na::hybrid_ndarray<float,12,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
}

TEST_CASE("is_bounded_size(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type = na::hybrid_ndarray<float,12,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
}

TEST_CASE("resize_shape(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type  = na::hybrid_ndarray<float,12,3>;
        using result_type = meta::resize_shape_t<array_type,meta::as_type<2,3,2>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_type );
    }
}

TEST_CASE("resize_dim(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type  = na::hybrid_ndarray<float,12,3>;
        using result_type = meta::resize_dim_t<array_type,1>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, result_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, result_type );
    }
}

TEST_CASE("resize_size(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type  = na::hybrid_ndarray<float,12,3>;
        using result_type = meta::resize_size_t<array_type,1>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_type );
    }
}

TEST_CASE("resize_bounded_dim(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type  = na::hybrid_ndarray<float,12,3>;
        using result_type = meta::resize_bounded_dim_t<array_type,1>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, result_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, result_type );
    }
}

TEST_CASE("resize_bounded_size(case1)" * doctest::test_suite("meta::hybrid"))
{
    {
        using array_type  = na::hybrid_ndarray<float,12,3>;
        using result_type = meta::resize_bounded_size_t<array_type,6>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fail, result_type );
    }
}