#include "nmtools/meta.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/constants.hpp"

#include <Arduino.h>
#include <unity.h>

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

void test_array()
{
    {
        using array_t = utl::array<int,3>;
        auto array = array_t{1,2,3};

        TEST_ASSERT_TRUE( array.size() == 3 );
        TEST_ASSERT_TRUE( array[0] == 1 );
        TEST_ASSERT_TRUE( array[1] == 2 );
        TEST_ASSERT_TRUE( array[2] == 3 );
    }
    {
        auto array = utl::array{1,2,3};

        TEST_ASSERT_TRUE( array.size() == 3 );
        TEST_ASSERT_TRUE( array[0] == 1 );
        TEST_ASSERT_TRUE( array[1] == 2 );
        TEST_ASSERT_TRUE( array[2] == 3 );
    }
    {
        // copy constructor
        auto array = utl::array<int,3>{1,2,3};
        auto new_array = utl::array{array};

        const auto& [a,b,c] = new_array;
        TEST_ASSERT_TRUE( array.size() == 3 );
        TEST_ASSERT_TRUE( a == 1 );
        TEST_ASSERT_TRUE( b == 2 );
        TEST_ASSERT_TRUE( c == 3 );
    }
}

void test_either()
{
    {
        using either_t = utl::either<nm::none_t,nmtools_array<nm::uint8_t,3>>;
        auto either = either_t(nmtools_array{(uint8_t)1ul,(uint8_t)1ul,(uint8_t)1ul});

        TEST_ASSERT_TRUE( either.index() == 1 );
    }

    {
        using array_t  = nmtools_array<nm::uint8_t,3>;
        using either_t = utl::either<uint8_t,array_t>;
        auto either = either_t(nmtools_array{(uint8_t)1ul,(uint8_t)1ul,(uint8_t)1ul});

        TEST_ASSERT_TRUE( either.index() == 1 );
        auto lptr = nm::get_if<uint8_t>(&either);
        auto rptr = nm::get_if<array_t>(&either);

        static_assert( meta::is_pointer_v<decltype(lptr)> );
        static_assert( meta::is_pointer_v<decltype(rptr)> );
    }
}

void test_tuple()
{
    {
        auto tp = utl::tuple{1,2,3};
        using new_tuple_t = utl::tuple<int,int,int>;
        new_tuple_t new_tp = tp;

        TEST_ASSERT_EQUAL( new_tp.value1, 1 );
        TEST_ASSERT_EQUAL( new_tp.value2, 2 );
        TEST_ASSERT_EQUAL( new_tp.value3, 3 );
    }
    {
        auto tp = utl::tuple{1,2,3};
        using new_tuple_t = utl::tuple<int,int,int>;
        auto new_tp = new_tuple_t(tp);

        TEST_ASSERT_EQUAL( new_tp.value1, 1 );
        TEST_ASSERT_EQUAL( new_tp.value2, 2 );
        TEST_ASSERT_EQUAL( new_tp.value3, 3 );
    }
    {
        auto tp = utl::tuple{1,1.0,2,3.0,4};
        TEST_ASSERT_EQUAL( tp.value1, 1 );
        TEST_ASSERT_EQUAL( tp.value2, 1 );
        TEST_ASSERT_EQUAL( tp.value3, 2 );
        TEST_ASSERT_EQUAL( tp.value4, 3 );
        TEST_ASSERT_EQUAL( tp.value5, 4 );
    }
    {
        auto tp = utl::tuple{1,2,3};
        using new_tuple_t = utl::tuple<int,int,int>;
        new_tuple_t new_tp;
        new_tp = tp;

        TEST_ASSERT_EQUAL( new_tp.value1, 1 );
        TEST_ASSERT_EQUAL( new_tp.value2, 2 );
        TEST_ASSERT_EQUAL( new_tp.value3, 3 );
    }
}

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    delay(1000);

    UNITY_BEGIN();

    RUN_TEST(test_array);
    RUN_TEST(test_either);
    RUN_TEST(test_tuple);

    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}