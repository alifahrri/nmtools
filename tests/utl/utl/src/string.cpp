#include "nmtools/utl/string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

#if defined(__arm__) || defined(__thumb__)
    #if __ARM_ARCH == 5
        #define IS_ARMV5 1
    #elif __ARM_ARCH == 7
        #define IS_ARMV7 1
    #else
        #define IS_ARMV5 0
        #define IS_ARMV7 0
    #endif
    #define IS_ARM 1
#else
    #define IS_ARM 0
#endif

#ifdef __riscv
    #if __riscv_xlen == 64
        #define IS_RISCV64 1
    #elif __riscv_xlen == 32
        #define IS_RISCV32 1
    #endif
    #define IS_RISCV 1
#else
    #define IS_RISCV 0
#endif

#define DISABLE_CHECK (IS_ARMV5 || IS_ARMV7 || IS_RISCV)

TEST_CASE("string" * doctest::test_suite("utl"))
{
    {
        [[maybe_unused]]
        utl::string str;
        NMTOOLS_ASSERT_EQUAL( str.size(), 0 );
    }
    {
        utl::string str;
        str = "hello";
        NMTOOLS_ASSERT_EQUAL( str.size(), 6 );
        auto isequal = str == "hello";
        CHECK( isequal );
    }
    {
        utl::string str;
        str = "hello";
        [[maybe_unused]]
        utl::string other = str;
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        auto isequal = other == "hello";
        CHECK( isequal );
    }
    {
        utl::string str;
        str = "hello";
        auto other = str + " " + "world";
        NMTOOLS_ASSERT_EQUAL( other.size(), 12 );
        auto isequal = other == "hello world";
        CHECK( isequal );
    }
    {
        utl::string str;
        str = "Lorem";
        auto other = str + " " + "ipsum" + " " + "dolor" + " " + "sit amet," + " " + "consectetur adipiscing elit,";
        NMTOOLS_ASSERT_EQUAL( other.size(), 57 );
        auto isequal ( other == "Lorem ipsum dolor sit amet, consectetur adipiscing elit," );
        CHECK( isequal );
    }
    {
        utl::string str;
        str += "h";
        str += "e";
        str += "l";
        str += "l";
        str += "o";
        auto expected = utl::string("hello");
        for (nm_size_t i=0; i<str.size() && i<expected.size(); i++) {
            CHECK( str[i] == expected[i] );
        }
        #if defined(__arm__) && defined(__ARM_ARCH) && __ARM_ARCH == 5
        auto is_same = (str == "hello");
        CHECK( is_same );
        #else
        CHECK( str == "hello" );
        #endif
    }
    {
        utl::string str;
        str += utl::string("h");
        str += utl::string("e");
        str += utl::string("l");
        str += utl::string("l");
        str += utl::string("o");
        auto expected = utl::string("hello");
        for (nm_size_t i=0; i<str.size() && i<expected.size(); i++) {
            CHECK( str[i] == expected[i] );
        }
        #if defined(__arm__) && defined(__ARM_ARCH) && __ARM_ARCH == 5
        auto is_same = (str == "hello");
        CHECK( is_same );
        #else
        CHECK( str == "hello" );
        #endif
    }
    {
        utl::string str;
        str += 'h';
        CHECK( str.size() == 2 );
        str += 'e';
        CHECK( str.size() == 3 );
        str += 'l';
        CHECK( str.size() == 4 );
        str += 'l';
        CHECK( str.size() == 5 );
        str += 'o';
        CHECK( str.size() == 6 );
        auto expected = utl::string("hello");
        for (nm_size_t i=0; i<str.size() && i<expected.size(); i++) {
            CHECK( str[i] == expected[i] );
        }
        #if defined(__arm__) && defined(__ARM_ARCH) && __ARM_ARCH == 5
        auto is_same = (str == "hello");
        CHECK( is_same );
        #else
        CHECK( str == "hello" );
        #endif
    }
    {
        utl::string str;
        str += utl::string("h");
        CHECK( str.size() == 2 );
        str += utl::string("e");
        CHECK( str.size() == 3 );
        str += utl::string("l");
        CHECK( str.size() == 4 );
        str += utl::string("l");
        CHECK( str.size() == 5 );
        str += utl::string("o");
        CHECK( str.size() == 6 );
        auto expected = utl::string("hello");
        for (nm_size_t i=0; i<str.size() && i<expected.size(); i++) {
            CHECK( str[i] == expected[i] );
        }
        #if defined(__arm__) && defined(__ARM_ARCH) && __ARM_ARCH == 5
        auto is_same = (str == "hello");
        CHECK( is_same );
        #else
        CHECK( str == "hello" );
        #endif
    }
    {
        auto str = utl::to_string<utl::string>(3);
        CHECK( str.size() == 2 );
        auto is_same = (str == "3");
        CHECK( is_same );
    }
    {
        utl::string str;
        str += "hello";
        str += " ";
        str += "world";
        auto isequal = ( str == "hello world" );
        CHECK( isequal );
    }
    {
        utl::string str;
        str = "hello";
        str[0] = 'H';
        auto isequal = ( str == "Hello" );
        CHECK( isequal );
    }
    {
        utl::string str;
        str = "hello world";
        auto substr = str.substr(6);
        auto isequal = ( substr == "world" );
        CHECK( isequal );
    }
    {
        utl::string str;
        str = "xmplr";
        str.insert(0,"E");
        NMTOOLS_ASSERT_EQUAL( str.size(), 7 );
        auto isequal = ( str == "Exmplr" );
        CHECK( isequal );
        str.insert(2,"e");
        str.insert(6,"a");
        {
            auto isequal = ( str == "Exemplar" );
            CHECK( isequal );
        }
    }
    {
        utl::string str;
        str = "hello world";
        {
            auto pos = str.find("wor");
            NMTOOLS_ASSERT_EQUAL( pos, 6 );
        }
        {
            auto pos = str.find("world!");
            NMTOOLS_ASSERT_EQUAL( pos, utl::string::npos );
        }
        {
            auto pos = str.find("wor", 3);
            NMTOOLS_ASSERT_EQUAL( pos, 6 );
        }
    }
    {
        utl::string str = "hello {}, {}";
        {
            auto pos = str.find("{");
            NMTOOLS_ASSERT_EQUAL( pos, 6);
        }
        {
            auto pos = str.find("{",7);
            NMTOOLS_ASSERT_EQUAL( pos, 10);
        }
    }
    {
        utl::string str("hello world");
        auto isequal = ( str == "hello world" );
        CHECK( isequal );
    }

    {
        utl::string str("hello world!");
        std::cout << str << std::endl;
    }
    {
        utl::string str("Lorem ipsum dolor sit amet, consectetur adipiscing elit,");
        std::cout << str << std::endl;
    }
    {
        utl::string str(R"(Lorem ipsum dolor sit amet,\n
            consectetur adipiscing elit, \n
            sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \n
            Ut enim ad minim veniam, \n
            quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \n
            Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. \n
            Excepteur sint occaecat cupidatat non proident, \n
            sunt in culpa qui officia deserunt mollit anim id est laborum.)");
        std::cout << str << std::endl;
    }
    {
        utl::string str;
        CHECK( str.is_static() );
        str.push_back('a');
        str.push_back('\0');
        auto isequal = ( str == "a" );
        CHECK( isequal );
        // grow beyond default static capacity
        for (int i=0; i<20; i++) {
            str.push_back('x');
        }
        NMTOOLS_ASSERT_EQUAL( str.size(), 22 );
        CHECK( !str.is_static() );
    }
    {
        utl::string str;
        str = "hello";
        str.resize(3);
        NMTOOLS_ASSERT_EQUAL( str.size(), 3 );
        CHECK( str.at(0) == 'h' );
        CHECK( str.at(1) == 'e' );
        CHECK( str.at(2) == 'l' );
        str.resize(6);
        NMTOOLS_ASSERT_EQUAL( str.size(), 6 );
    }
    {
        utl::string str;
        str = "hello";
        CHECK( std::string(str.c_str()) == "hello" );
        CHECK( std::string(str.data()) == "hello" );
        CHECK( str.begin() == str.data() );
        CHECK( str.end() == str.data() + str.size() );
        CHECK( str.at(0) == 'h' );
        CHECK( str[1] == 'e' );
    }
    {
        utl::string str;
        str = "hello";
        utl::string other;
        other = "hello";
        {
            auto isequal = ( str == other );
            CHECK( isequal );
        }
        other = "world";
        {
            auto isequal = ( str == other );
            CHECK( !isequal );
        }
        // cross-capacity equality
        {
            auto small = utl::string_base<8>("hello");
            auto isequal = ( str == small );
            CHECK( isequal );
        }
    }
    {
        utl::string str;
        str = "hello world";
        utl::string needle;
        needle = "wor";
        auto pos = str.find(needle);
        NMTOOLS_ASSERT_EQUAL( pos, 6 );
        // find with start
        pos = str.find(needle, 3);
        NMTOOLS_ASSERT_EQUAL( pos, 6 );
        pos = str.find(needle, 7);
        NMTOOLS_ASSERT_EQUAL( pos, utl::string::npos );
    }
    {
        utl::string str("1:-1:");
        {
            auto pos = str.rfind(":");
            NMTOOLS_ASSERT_EQUAL( pos, 4 );
        }
        {
            auto count = str.count(':');
            NMTOOLS_ASSERT_EQUAL( count, 2 );
        }
        {
            auto count = str.count('x');
            NMTOOLS_ASSERT_EQUAL( count, 0 );
        }
        {
            auto splits = str.split(':');
            NMTOOLS_ASSERT_EQUAL( splits.size(), 3 );
            {
                auto isequal = splits[0] == "1";
                CHECK( isequal );
            }
            {
                auto isequal = splits[1] == "-1";
                CHECK( isequal );
            }
            {
                auto isequal = splits[2] == "";
                CHECK( isequal );
            }
        }
        {
            auto splits = str.split('x');
            NMTOOLS_ASSERT_EQUAL( splits.size(), 1 );
            NMTOOLS_ASSERT_EQUAL( splits[0].size(), 6 );
        }
    }
    {
        utl::string str;
        str = "hello";
        {
            auto substr = str.substr(0,6);
            auto isequal = ( substr == "hello" );
            CHECK( isequal );
        }
    }
    {
        utl::string str;
        str = "hello world";
        {
            auto substr = str.substr(6,6);
            auto isequal = ( substr == "world" );
            CHECK( isequal );
        }
    }
    {
        utl::string str;
        str = "hello";
        utl::string other;
        other = " world";
        auto concat = str + other;
        {
            auto isequal = ( concat == "hello world" );
            CHECK( isequal );
        }
        // concat of larger capacity
        auto concat2 = utl::string_base<8>("hello") + utl::string_base<8>(" world");
        {
            auto isequal = ( concat2 == "hello world" );
            CHECK( isequal );
        }
    }
    {
        auto str = utl::string::to_string(nmtools::none_t{});
        auto isequal = ( str == "None" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(nmtools::ellipsis_t{});
        auto isequal = ( str == "..." );
        CHECK( isequal );
    }
    {
        NMTOOLS_ASSERT_EQUAL( utl::string::capacity, NMTOOLS_DEFAULT_STRING_STATIC_SIZE );
    }
}

TEST_CASE("string::to_string" * doctest::test_suite("utl"))
{
    {
        auto str = utl::string::to_string(0);
        auto isequal = ( str == "0" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(3);
        auto isequal = ( str == "3" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(13);
        auto isequal = ( str == "13" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(103);
        auto isequal = ( str == "103" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(1103);
        auto isequal = ( str == "1103" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(-3);
        auto isequal = ( str == "-3" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(-13);
        auto isequal = ( str == "-13" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(-103);
        auto isequal = ( str == "-103" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(-1103);
        auto isequal = ( str == "-1103" );
        CHECK( isequal );
    }

    // integral_constant
    {
        auto str = utl::string::to_string(nmtools::meta::integral_constant<int,13>{});
        auto isequal = ( str == "13" );
        CHECK( isequal );
    }

    // array
    {
        auto array = nmtools_array{0,-3,13};
        auto str = utl::string::to_string(array);
        auto isequal = ( str == "{0,-3,13}" );
        CHECK( isequal );
    }
    {
        auto array = nmtools_list<int>();
        array.push_back(0);
        array.push_back(-3);
        array.push_back(13);
        auto str = utl::string::to_string(array);
        auto isequal = ( str == "{0,-3,13}" );
        CHECK( isequal );
    }

    // floating point (fixed-point, 6 decimals, similar to std::to_string)
    {
        auto str = utl::string::to_string(3.14f);
        auto isequal = ( str == "3.140000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(-2.5f);
        auto isequal = ( str == "-2.500000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(0.0f);
        auto isequal = ( str == "0.000000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(-0.0f);
        auto isequal = ( str == "-0.000000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(100.0f);
        auto isequal = ( str == "100.000000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(0.5);
        auto isequal = ( str == "0.500000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(1.0);
        auto isequal = ( str == "1.000000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(1234.5678);
        auto isequal = ( str == "1234.567800" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(1e-5);
        auto isequal = ( str == "0.000010" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(2.5e-2);
        auto isequal = ( str == "0.025000" );
        CHECK( isequal );
    }
    {
        auto str = utl::string::to_string(3.25);
        auto isequal = ( str == "3.250000" );
        CHECK( isequal );
    }
    {
        // note: meta::numeric_limits<float>::max() returns infinity
        auto str = utl::string::to_string(nmtools::meta::numeric_limits<float>::max());
        auto isequal = ( str == "inf" );
        CHECK( isequal );
    }
    {
        // note: meta::numeric_limits<double>::max() returns infinity
        auto str = utl::string::to_string(-nmtools::meta::numeric_limits<double>::max());
        auto isequal = ( str == "-inf" );
        CHECK( isequal );
    }
    {
        // inf - inf = nan
        auto inf = nmtools::meta::numeric_limits<float>::max();
        auto str = utl::string::to_string(inf - inf);
        auto isequal = ( str == "nan" );
        CHECK( isequal );
    }
}

TEST_CASE("string::join" * doctest::test_suite("utl"))
{
    using utl::string;
    {
        auto strs = nmtools_array<string,3>{string::to_string(1), string::to_string(3), string::to_string(5)};
        auto str = string(",").join(strs);
        CHECK( str.size() == 6 );
        auto isequal = ( str == "1,3,5" );
        CHECK( isequal );
    }
    {
        auto strs = nmtools_array<string,0>{};
        auto str = string(",").join(strs);
        NMTOOLS_ASSERT_EQUAL( str.size(), 0 );
    }
    {
        auto strs = nmtools_array<string,1>{string::to_string(1)};
        auto str = string(",").join(strs);
        auto isequal = ( str == "1" );
        CHECK( isequal );
    }
}

TEST_CASE("string::stoi" * doctest::test_suite("utl"))
{
    {
        utl::string str = "3";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 3 );
    }
    {
        utl::string str = "-5";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, -5 );
    }
    // multi-digit
    {
        utl::string str = "123";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 123 );
    }
    {
        utl::string str = "-123";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, -123 );
    }
    // positive sign
    {
        utl::string str = "+42";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // leading zeros
    {
        utl::string str = "007";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 7 );
    }
    // leading whitespace
    {
        utl::string str = "  42";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stops at first non-digit
    {
        utl::string str = "42abc";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // int range boundaries
    {
        utl::string str = "2147483647";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 2147483647 );
    }
    {
        utl::string str = "-2147483648";
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, -2147483648 );
    }
    // stoi returns int32_t
    {
        utl::string str = "42";
        auto result = utl::stoi(str);
        STATIC_CHECK_IS_SAME( decltype(result), int32_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stoll returns int64_t
    {
        utl::string str = "42";
        auto result = utl::stoll(str);
        STATIC_CHECK_IS_SAME( decltype(result), int64_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stoll handles values beyond int32 range
    {
        utl::string str = "2147483648";
        auto result = utl::stoll(str);
        NMTOOLS_ASSERT_EQUAL( result, 2147483648LL );
    }
    // stoll int64 range boundaries
    {
        utl::string str = "9223372036854775807";
        auto result = utl::stoll(str);
        NMTOOLS_ASSERT_EQUAL( result, 9223372036854775807LL );
    }
    {
        utl::string str = "-9223372036854775808";
        auto result = utl::stoll(str);
        NMTOOLS_ASSERT_EQUAL( result, -9223372036854775807LL - 1 );
    }
    // stoint with custom integer type
    {
        utl::string str = "127";
        auto result = utl::stoint<int8_t>(str);
        STATIC_CHECK_IS_SAME( decltype(result), int8_t );
        NMTOOLS_ASSERT_EQUAL( result, 127 );
    }
    {
        utl::string str = "-32768";
        auto result = utl::stoint<int16_t>(str);
        STATIC_CHECK_IS_SAME( decltype(result), int16_t );
        NMTOOLS_ASSERT_EQUAL( result, -32768 );
    }
    // stoul returns uint32_t
    {
        utl::string str = "42";
        auto result = utl::stoul(str);
        STATIC_CHECK_IS_SAME( decltype(result), uint32_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stoull returns uint64_t
    {
        utl::string str = "42";
        auto result = utl::stoull(str);
        STATIC_CHECK_IS_SAME( decltype(result), uint64_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // uint32 range boundaries
    {
        utl::string str = "4294967295";
        auto result = utl::stoul(str);
        NMTOOLS_ASSERT_EQUAL( result, 4294967295U );
    }
    // stoull handles values beyond uint32 range
    {
        utl::string str = "4294967296";
        auto result = utl::stoull(str);
        NMTOOLS_ASSERT_EQUAL( result, 4294967296ULL );
    }
    // uint64 range boundaries
    {
        utl::string str = "18446744073709551615";
        auto result = utl::stoull(str);
        NMTOOLS_ASSERT_EQUAL( result, 18446744073709551615ULL );
    }
    // positive sign
    {
        utl::string str = "+42";
        auto result = utl::stoull(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stouint with custom unsigned type
    {
        utl::string str = "255";
        auto result = utl::stouint<uint8_t>(str);
        STATIC_CHECK_IS_SAME( decltype(result), uint8_t );
        NMTOOLS_ASSERT_EQUAL( result, 255 );
    }
    // stof returns float32_t
    {
        utl::string str = "3.14";
        auto result = utl::stof(str);
        STATIC_CHECK_IS_SAME( decltype(result), float );
        NMTOOLS_ASSERT_CLOSE( result, 3.14f );
    }
    // stod returns float64_t
    {
        utl::string str = "3.14";
        auto result = utl::stod(str);
        STATIC_CHECK_IS_SAME( decltype(result), double );
        NMTOOLS_ASSERT_CLOSE( result, 3.14 );
    }
    // integer value
    {
        utl::string str = "42";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, 42.0 );
    }
    // negative
    {
        utl::string str = "-2.5";
        auto result = utl::stof(str);
        NMTOOLS_ASSERT_CLOSE( result, -2.5f );
    }
    // positive sign
    {
        utl::string str = "+0.5";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.5 );
    }
    // exponent
    {
        utl::string str = "1e3";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, 1000.0 );
    }
    {
        utl::string str = "2.5e-2";
        auto result = utl::stof(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.025f );
    }
    {
        utl::string str = "-1.5E2";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, -150.0 );
    }
    {
        utl::string str = "6.022e23";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 6.022e23 );
    }
    // leading dot and trailing dot
    {
        utl::string str = ".5";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.5 );
    }
    {
        utl::string str = "3.";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, 3.0 );
    }
    // leading whitespace
    {
        utl::string str = "  3.5";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 3.5 );
    }
    // stops at first non-digit
    {
        utl::string str = "3.5abc";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 3.5 );
    }
    // small values
    {
        utl::string str = "1e-5";
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.00001 );
    }
    // large values (double)
    {
        utl::string str = "1e308";
        auto result = utl::stod(str);
        auto is_in_range = (result > 1e307) && (result < 1.7e308);
        NMTOOLS_CHECK_MESSAGE( is_in_range, "stod large value" );
    }
    // large values (float overflows to inf)
    {
        utl::string str = "1e40";
        auto result = utl::stof(str);
        NMTOOLS_CHECK_MESSAGE( result > 3.402823e38f, "stof overflow to inf" );
    }
}