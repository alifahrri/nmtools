#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"

TEST_CASE("literals" * doctest::test_suite("constants"))
{
    using namespace nmtools::literals;
    {
        auto c = 1_ct;
        using expected_t = std::integral_constant<size_t,1>;
        STATIC_CHECK_IS_SAME( decltype(c), expected_t );
    }
    {
        auto c = 12_ct;
        using expected_t = std::integral_constant<size_t,12>;
        STATIC_CHECK_IS_SAME( decltype(c), expected_t );
    }
    {
        auto c = 123_ct;
        using expected_t = std::integral_constant<size_t,123>;
        STATIC_CHECK_IS_SAME( decltype(c), expected_t );
    }
    {
        auto c = 1234_ct;
        using expected_t = std::integral_constant<size_t,1234>;
        STATIC_CHECK_IS_SAME( decltype(c), expected_t );
    }
    {
        auto c = 12345_ct;
        using expected_t = std::integral_constant<size_t,12345>;
        STATIC_CHECK_IS_SAME( decltype(c), expected_t );
    }
    {
        auto c = 123456_ct;
        using expected_t = std::integral_constant<size_t,123456>;
        STATIC_CHECK_IS_SAME( decltype(c), expected_t );
    }
}