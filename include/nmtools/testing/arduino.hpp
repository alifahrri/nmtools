#ifndef NMTOOLS_TESTING_ARDUINO_HPP
#define NMTOOLS_TESTING_ARDUINO_HPP

#include <Arduino.h>
#include <unity.h>

#define NMTOOLS_PIO_CONSTEXPR_SUBCASE(case_name, expected, function, ...) \
{ \
    using namespace args; \
    constexpr auto res = function(__VA_ARGS__); \
    constexpr auto success = nmtools::utils::isclose(res, expect::expected); \
    static_assert( success ); \
    TEST_ASSERT_TRUE( success ); \
}

#define NM_TEST_SUBCASE(case_name, subcase_name) \
void test_##case_name##_##subcase_name()

#define NMTOOLS_PIO_RUN(test_name, case_name) \
RUN_TEST(test_##test_name##_##case_name);

#endif // NMTOOLS_TESTING_ARDUINO_HPP