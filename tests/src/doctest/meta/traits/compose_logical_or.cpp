#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("compose_logical_or" * doctest::test_suite("traits"))
{
    {
        using arg_t = int;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_arithmetic,std::is_integral>;
        STATIC_CHECK( value );
    }
    {
        using arg_t = int;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_arithmetic,std::is_floating_point>;
        STATIC_CHECK( value );
    }
    {
        using arg_t = int;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_floating_point,meta::is_integral_constant>;
        STATIC_CHECK( !value );
    }
    {
        using arg_t = float;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_arithmetic,std::is_integral>;
        STATIC_CHECK( value );
    }
    {
        using arg_t = float;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_arithmetic,std::is_floating_point>;
        STATIC_CHECK( value );
    }
    {
        using arg_t = float;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_integral,meta::is_integral_constant>;
        STATIC_CHECK( !value );
    }
    {
        using arg_t = std::integral_constant<int,3>;
        constexpr auto value = meta::compose_logical_or_v<arg_t,meta::is_integral_constant>;
        STATIC_CHECK( value );
    }
    {
        using arg_t = std::integral_constant<int,3>;
        constexpr auto value = meta::compose_logical_or_v<arg_t,meta::is_integral_constant,std::is_arithmetic>;
        STATIC_CHECK( value );
    }
    {
        using arg_t = std::integral_constant<int,3>;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_arithmetic,std::is_integral>;
        STATIC_CHECK( !value );
    }
    {
        using arg_t = std::integral_constant<int,3>;
        constexpr auto value = meta::compose_logical_or_v<arg_t,std::is_arithmetic,std::is_floating_point>;
        STATIC_CHECK( !value );
    }
}