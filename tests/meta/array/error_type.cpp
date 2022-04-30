#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta  = nm::meta;
namespace error = meta::error;

TEST_CASE("error_type(case1)" * doctest::test_suite("meta::error"))
{
    {
        using error_type = error::BOUNDED_DIM_UNSUPPORTED<int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SHAPE_UNSUPPORTED<int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_DIM_UNSUPPORTED<int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SIZE_UNSUPPORTED<int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
}

#if __has_include(<boost/array.hpp>)
#include <boost/array.hpp>
using array_type = ::boost::array<float,12>;

TEST_CASE("error_type(case1)" * doctest::test_suite("meta::error"))
{
    {
        using error_type = error::BOUNDED_DIM_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SHAPE_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_DIM_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SIZE_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    
    {
        using error_type = const error::BOUNDED_DIM_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = const error::FIXED_SHAPE_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = const error::FIXED_DIM_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = const error::FIXED_SIZE_UNSUPPORTED<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }

    {
        using error_type = const error::BOUNDED_DIM_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = const error::FIXED_SHAPE_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = const error::FIXED_DIM_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = const error::FIXED_SIZE_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }

    {
        using error_type = error::BOUNDED_DIM_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SHAPE_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_DIM_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SIZE_UNSUPPORTED<array_type>&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }

    {
        using error_type = error::BOUNDED_DIM_UNSUPPORTED<const array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SHAPE_UNSUPPORTED<const array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_DIM_UNSUPPORTED<const array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
    {
        using error_type = error::FIXED_SIZE_UNSUPPORTED<const array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, error_type );
    }
}

#endif