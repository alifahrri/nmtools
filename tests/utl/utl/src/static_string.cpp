#include "nmtools/utl/static_string.hpp"
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

TEST_CASE("static_string" * doctest::test_suite("utl"))
{
    {
        [[maybe_unused]]
        utl::static_string str;
        NMTOOLS_ASSERT_EQUAL( str.size(), 0 );
    }
    {
        utl::static_string str;
        str = "hello";
        NMTOOLS_ASSERT_EQUAL( str.size(), 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str = "hello";
        [[maybe_unused]]
        utl::static_string other = str;
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( other == "hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str = "hello";
        auto other = str + " " + "world";
        #if !DISABLE_CHECK
        {
            auto isequal = ( other == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str += "hello";
        str += " ";
        str += "world";
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str = "hello";
        str[0] = 'H';
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "Hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str = "hello world";
        auto substr = str.substr(6);
        #if !DISABLE_CHECK
        {
            auto isequal = ( substr == "world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str = "xmplr";
        str.insert(0,"E");
        NMTOOLS_ASSERT_EQUAL( str.size(), 7 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "Exmplr" );
            CHECK( isequal );
        }
        #endif
        {
            auto expect = nmtools_array{'E','x','m','p','l','r','\0'};
            NMTOOLS_ASSERT_EQUAL( str.base(), expect );
        }
        str.insert(2,"e");
        str.insert(6,"a");
        {
            auto expect = nmtools_array{'E','x','e','m','p','l','a','r','\0'};
            NMTOOLS_ASSERT_EQUAL( str.base(), expect );
        }
    }
    {
        utl::static_string str;
        str = "hello world";
        {
            auto pos = str.find("wor");
            NMTOOLS_ASSERT_EQUAL( pos, 6 );
        }
        {
            auto pos = str.find("world!");
            NMTOOLS_ASSERT_EQUAL( pos, utl::static_string::npos );
        }
    }
    {
        utl::static_string str("hello world");
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str("1:-1:");
        {
            auto pos = str.find(":");
            NMTOOLS_ASSERT_EQUAL( pos, 1 );
        }
        {
            auto pos = str.rfind(":");
            NMTOOLS_ASSERT_EQUAL( pos, 4 );
        }
        {
            auto count = str.count(':');
            NMTOOLS_ASSERT_EQUAL( count, 2 );
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
    }
    {
        utl::static_string str;
        str += utl::static_string("hello");
        str += utl::static_string(" ");
        str += utl::static_string("world");
        NMTOOLS_ASSERT_EQUAL( str.size(), 12 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str += 'h';
        NMTOOLS_ASSERT_EQUAL( str.size(), 2 );
        str += 'e';
        NMTOOLS_ASSERT_EQUAL( str.size(), 3 );
        str += 'l';
        NMTOOLS_ASSERT_EQUAL( str.size(), 4 );
        str += 'l';
        NMTOOLS_ASSERT_EQUAL( str.size(), 5 );
        str += 'o';
        NMTOOLS_ASSERT_EQUAL( str.size(), 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str = "hello";
        utl::static_string other;
        other = " world";
        auto concat = str + other;
        NMTOOLS_ASSERT_EQUAL( concat.size(), 12 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( concat == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        utl::static_string str;
        str = "hello world";
        utl::static_string needle;
        needle = "wor";
        auto pos = str.find(needle);
        NMTOOLS_ASSERT_EQUAL( pos, 6 );
        pos = str.find(needle, 3);
        NMTOOLS_ASSERT_EQUAL( pos, 6 );
        pos = str.find(needle, 7);
        NMTOOLS_ASSERT_EQUAL( pos, utl::static_string::npos );
    }
    {
        utl::static_string str;
        str = "hello world";
        {
            auto count = str.count('x');
            NMTOOLS_ASSERT_EQUAL( count, 0 );
        }
        {
            auto splits = str.split(':');
            NMTOOLS_ASSERT_EQUAL( splits.size(), 1 );
            NMTOOLS_ASSERT_EQUAL( splits[0].size(), 12 );
        }
    }
    {
        utl::static_string str;
        str = "hello";
        {
            auto substr = str.substr(0,6);
            #if !DISABLE_CHECK
            {
                auto isequal = ( substr == "hello" );
                CHECK( isequal );
            }
            #endif
        }
    }
    {
        utl::static_string str;
        str = "hello world";
        {
            auto substr = str.substr(6,6);
            #if !DISABLE_CHECK
            {
                auto isequal = ( substr == "world" );
                CHECK( isequal );
            }
            #endif
        }
    }
    {
        utl::static_string str;
        str = "hello";
        CHECK( std::string(str.c_str()) == "hello" );
        CHECK( str.data() == str.c_str() );
        CHECK( str.begin() == str.data() );
        CHECK( str.end() == str.data() + str.size() );
        CHECK( str.at(0) == 'h' );
        CHECK( str[1] == 'e' );
        CHECK( str.is_static() );
    }
    {
        utl::static_string_base<8> str;
        str = "hello";
        utl::static_string_base<16> other = str;
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( other == "hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(nmtools::none_t{});
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "None" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(nmtools::ellipsis_t{});
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "..." );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto array = nmtools_list<int>();
        array.push_back(0);
        array.push_back(-3);
        array.push_back(13);
        auto str = utl::static_string::to_string(array);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "{0,-3,13}" );
            CHECK( isequal );
        }
        #endif
    }
    {
        NMTOOLS_ASSERT_EQUAL( utl::static_string::capacity, NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE );
    }
}

TEST_CASE("constexpr_static_string" * doctest::test_suite("utl"))
{
    {
        [[maybe_unused]]
        constexpr utl::static_string str;
        NMTOOLS_ASSERT_EQUAL( str.size(), 0 );
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello";
            return str;
        }();
        NMTOOLS_ASSERT_EQUAL( str.size(), 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto other = [](){
            utl::static_string str;
            str = "hello";
            utl::static_string other = str;
            return other;
        }();
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( other == "hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto other = [](){
            utl::static_string str;
            str = "hello";
            auto other = str + " " + "world";
            return other;
        }();
        #if !DISABLE_CHECK
        {
            auto isequal = ( other == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str += "hello";
            str += " ";
            str += "world";
            return str;
        }();
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello";
            str[0] = 'H';
            return str;
        }();
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "Hello" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto substr = [](){
            utl::static_string str;
            str = "hello world";
            auto substr = str.substr(6);
            return substr;
        }();
        #if !DISABLE_CHECK
        {
            auto isequal = ( substr == "world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "xmplr";
            str.insert(0,"E");
            str.insert(2,"e");
            str.insert(6,"a");
            return str;
        }();
        {
            auto expect = nmtools_array{'E','x','e','m','p','l','a','r','\0'};
            NMTOOLS_ASSERT_EQUAL( str.base(), expect );
        }
    }
    {
        constexpr auto pos = [](){
            utl::static_string str;
            str = "hello world";
            auto pos = str.find("wor");
            return pos;
        }();
        {
            NMTOOLS_ASSERT_EQUAL( pos, 6 );
        }
    }
    {
        constexpr utl::static_string str("hello world");
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello world";
            utl::static_string other;
            other = "world";
            auto pos = str.find(other);
            return pos;
        }();
        {
            NMTOOLS_ASSERT_EQUAL( str, 6 );
        }
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello";
            str += '!';
            return str;
        }();
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello!" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str += utl::static_string("hello");
            str += utl::static_string(" ");
            str += utl::static_string("world");
            return str;
        }();
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello";
            utl::static_string other;
            other = " world";
            auto concat = str + other;
            return concat;
        }();
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "hello world" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello";
            return str.is_static();
        }();
        CHECK( str );
    }
}

TEST_CASE("static_string::to_string" * doctest::test_suite("utl"))
{
    {
        auto str = utl::static_string::to_string(0);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "0" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(3);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "3" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(13);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "13" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "103" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(1103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1103" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(-3);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-3" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(-13);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-13" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(-103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-103" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::static_string::to_string(-1103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-1103" );
            CHECK( isequal );
        }
        #endif
    }

    // constexpr
    {
        constexpr auto str = utl::static_string::to_string(0);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "0" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(3);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "3" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(13);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "13" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "103" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(1103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1103" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-3);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-3" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-13);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-13" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-103" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-1103);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-1103" );
            CHECK( isequal );
        }
        #endif
    }

    // cout
    {
        auto str = utl::static_string::to_string(100000);
        std::cout << str << std::endl;
    }

    // array
    {
        auto array = nmtools_array{0,-3,13};
        auto str = utl::static_string::to_string(array);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "{0,-3,13}" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto array = nmtools_array{0,-3,13};
        constexpr auto str = utl::static_string::to_string(array);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "{0,-3,13}" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto array = nmtools_static_vector<int,3>();
        array.push_back(0);
        array.push_back(-3);
        array.push_back(13);
        auto str = utl::static_string::to_string(array);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "{0,-3,13}" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto array = [](){
            auto array = nmtools_static_vector<int,3>();
            array.push_back(0);
            array.push_back(-3);
            array.push_back(13);
            return array;
        }();
        constexpr auto str = utl::static_string::to_string(array);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "{0,-3,13}" );
            CHECK( isequal );
        }
        #endif
    }

    // floating point (fixed-point, 6 decimals, similar to std::to_string)
    {
        auto str = utl::to_string(3.14f);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "3.140000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(-2.5f);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-2.500000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(0.0f);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "0.000000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(-0.0f);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-0.000000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(100.0f);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "100.000000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(0.5);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "0.500000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(1.0);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1.000000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(1234.5678);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1234.567800" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(1e-5);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "0.000010" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(2.5e-2);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "0.025000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string(3.25);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "3.250000" );
            CHECK( isequal );
        }
        #endif
    }
    // constexpr floating point
    {
        constexpr auto str = utl::to_string(3.14f);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "3.140000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::to_string(-2.5);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-2.500000" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::to_string(1e-5);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "0.000010" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto str = utl::to_string(1234.5678);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1234.567800" );
            CHECK( isequal );
        }
        #endif
    }
    {
        // note: meta::numeric_limits<float>::max() returns infinity
        auto str = utl::to_string(nmtools::meta::numeric_limits<float>::max());
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "inf" );
            CHECK( isequal );
        }
        #endif
    }
    {
        // note: meta::numeric_limits<double>::max() returns infinity
        auto str = utl::to_string(-nmtools::meta::numeric_limits<double>::max());
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "-inf" );
            CHECK( isequal );
        }
        #endif
    }
    {
        // inf - inf = nan
        auto inf = nmtools::meta::numeric_limits<float>::max();
        auto str = utl::to_string(inf - inf);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "nan" );
            CHECK( isequal );
        }
        #endif
    }
}

TEST_CASE("static_string::join" * doctest::test_suite("utl"))
{
    using utl::static_string;
    {
        auto strs = nmtools_array<static_string,3>{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        auto str = static_string(",").join(strs);
        CHECK( str.size() == 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1,3,5" );
            CHECK( isequal );
        }
        #endif
    }
    {
        constexpr auto strs = nmtools_array<static_string,3>{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        constexpr auto str = static_string(",").join(strs);
        CHECK( str.size() == 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1,3,5" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto strs = nmtools_array<static_string,0>{};
        auto str = static_string(",").join(strs);
        NMTOOLS_ASSERT_EQUAL( str.size(), 0 );
    }
    {
        auto strs = nmtools_array<static_string,1>{static_string::to_string(1)};
        auto str = static_string(",").join(strs);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1" );
            CHECK( isequal );
        }
        #endif
    }
}

TEST_CASE("static_string::stoi" * doctest::test_suite("utl"))
{
    {
        auto str = utl::static_string("3");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 3 );
    }
    {
        auto str = utl::static_string("-5");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, -5 );
    }
    // multi-digit
    {
        auto str = utl::static_string("123");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 123 );
    }
    {
        auto str = utl::static_string("-123");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, -123 );
    }
    // positive sign
    {
        auto str = utl::static_string("+42");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // leading zeros
    {
        auto str = utl::static_string("007");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 7 );
    }
    // leading whitespace
    {
        auto str = utl::static_string("  42");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stops at first non-digit
    {
        auto str = utl::static_string("42abc");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // int range boundaries
    {
        auto str = utl::static_string("2147483647");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, 2147483647 );
    }
    {
        auto str = utl::static_string("-2147483648");
        auto result = utl::stoi(str);
        NMTOOLS_ASSERT_EQUAL( result, -2147483648 );
    }
    // stoi returns int32_t
    {
        auto str = utl::static_string("42");
        auto result = utl::stoi(str);
        STATIC_CHECK_IS_SAME( decltype(result), int32_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stoll returns int64_t
    {
        auto str = utl::static_string("42");
        auto result = utl::stoll(str);
        STATIC_CHECK_IS_SAME( decltype(result), int64_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stoll handles values beyond int32 range
    {
        auto str = utl::static_string("2147483648");
        auto result = utl::stoll(str);
        NMTOOLS_ASSERT_EQUAL( result, 2147483648LL );
    }
    // stoll int64 range boundaries
    {
        auto str = utl::static_string("9223372036854775807");
        auto result = utl::stoll(str);
        NMTOOLS_ASSERT_EQUAL( result, 9223372036854775807LL );
    }
    {
        auto str = utl::static_string("-9223372036854775808");
        auto result = utl::stoll(str);
        NMTOOLS_ASSERT_EQUAL( result, -9223372036854775807LL - 1 );
    }
    // stoint with custom integer type
    {
        auto str = utl::static_string("127");
        auto result = utl::stoint<int8_t>(str);
        STATIC_CHECK_IS_SAME( decltype(result), int8_t );
        NMTOOLS_ASSERT_EQUAL( result, 127 );
    }
    {
        auto str = utl::static_string("-32768");
        auto result = utl::stoint<int16_t>(str);
        STATIC_CHECK_IS_SAME( decltype(result), int16_t );
        NMTOOLS_ASSERT_EQUAL( result, -32768 );
    }
    // stoul returns uint32_t
    {
        auto str = utl::static_string("42");
        auto result = utl::stoul(str);
        STATIC_CHECK_IS_SAME( decltype(result), uint32_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stoull returns uint64_t
    {
        auto str = utl::static_string("42");
        auto result = utl::stoull(str);
        STATIC_CHECK_IS_SAME( decltype(result), uint64_t );
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // uint32 range boundaries
    {
        auto str = utl::static_string("4294967295");
        auto result = utl::stoul(str);
        NMTOOLS_ASSERT_EQUAL( result, 4294967295U );
    }
    // stoull handles values beyond uint32 range
    {
        auto str = utl::static_string("4294967296");
        auto result = utl::stoull(str);
        NMTOOLS_ASSERT_EQUAL( result, 4294967296ULL );
    }
    // uint64 range boundaries
    {
        auto str = utl::static_string("18446744073709551615");
        auto result = utl::stoull(str);
        NMTOOLS_ASSERT_EQUAL( result, 18446744073709551615ULL );
    }
    // positive sign
    {
        auto str = utl::static_string("+42");
        auto result = utl::stoull(str);
        NMTOOLS_ASSERT_EQUAL( result, 42 );
    }
    // stouint with custom unsigned type
    {
        auto str = utl::static_string("255");
        auto result = utl::stouint<uint8_t>(str);
        STATIC_CHECK_IS_SAME( decltype(result), uint8_t );
        NMTOOLS_ASSERT_EQUAL( result, 255 );
    }
    // stof returns float32_t
    {
        auto str = utl::static_string("3.14");
        auto result = utl::stof(str);
        STATIC_CHECK_IS_SAME( decltype(result), float );
        NMTOOLS_ASSERT_CLOSE( result, 3.14f );
    }
    // stod returns float64_t
    {
        auto str = utl::static_string("3.14");
        auto result = utl::stod(str);
        STATIC_CHECK_IS_SAME( decltype(result), double );
        NMTOOLS_ASSERT_CLOSE( result, 3.14 );
    }
    // integer value
    {
        auto str = utl::static_string("42");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, 42.0 );
    }
    // negative
    {
        auto str = utl::static_string("-2.5");
        auto result = utl::stof(str);
        NMTOOLS_ASSERT_CLOSE( result, -2.5f );
    }
    // positive sign
    {
        auto str = utl::static_string("+0.5");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.5 );
    }
    // exponent
    {
        auto str = utl::static_string("1e3");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, 1000.0 );
    }
    {
        auto str = utl::static_string("2.5e-2");
        auto result = utl::stof(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.025f );
    }
    {
        auto str = utl::static_string("-1.5E2");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, -150.0 );
    }
    {
        auto str = utl::static_string("6.022e23");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 6.022e23 );
    }
    // leading dot and trailing dot
    {
        auto str = utl::static_string(".5");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.5 );
    }
    {
        auto str = utl::static_string("3.");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_EQUAL( result, 3.0 );
    }
    // leading whitespace
    {
        auto str = utl::static_string("  3.5");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 3.5 );
    }
    // stops at first non-digit
    {
        auto str = utl::static_string("3.5abc");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 3.5 );
    }
    // small values
    {
        auto str = utl::static_string("1e-5");
        auto result = utl::stod(str);
        NMTOOLS_ASSERT_CLOSE( result, 0.00001 );
    }
    // large values (double)
    {
        auto str = utl::static_string("1e308");
        auto result = utl::stod(str);
        auto is_in_range = (result > 1e307) && (result < 1.7e308);
        NMTOOLS_CHECK_MESSAGE( is_in_range, "stod large value" );
    }
    // large values (float overflows to inf)
    {
        auto str = utl::static_string("1e40");
        auto result = utl::stof(str);
        NMTOOLS_CHECK_MESSAGE( result > 3.402823e38f, "stof overflow to inf" );
    }
    // constexpr
    {
        constexpr auto result = utl::stoi(utl::static_string("-1103"));
        NMTOOLS_ASSERT_EQUAL( result, -1103 );
    }
    // constexpr stoll
    {
        constexpr auto result = utl::stoll(utl::static_string("1103"));
        NMTOOLS_ASSERT_EQUAL( result, 1103 );
    }
    // constexpr stoint
    {
        constexpr auto result = utl::stoint<int8_t>(utl::static_string("-128"));
        NMTOOLS_ASSERT_EQUAL( result, -128 );
    }
    // constexpr stoull
    {
        constexpr auto result = utl::stoull(utl::static_string("1103"));
        NMTOOLS_ASSERT_EQUAL( result, 1103 );
    }
    // constexpr stouint
    {
        constexpr auto result = utl::stouint<uint8_t>(utl::static_string("200"));
        NMTOOLS_ASSERT_EQUAL( result, 200 );
    }
    // constexpr stof
    {
        constexpr auto result = utl::stof(utl::static_string("3.14"));
        NMTOOLS_ASSERT_CLOSE( result, 3.14f );
    }
    // constexpr stod
    {
        constexpr auto result = utl::stod(utl::static_string("2.5e-2"));
        NMTOOLS_ASSERT_CLOSE( result, 0.025 );
    }
}

TEST_CASE("static_string::free_to_string" * doctest::test_suite("utl"))
{
    {
        auto str = utl::to_string<utl::static_string>(3);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "3" );
            CHECK( isequal );
        }
        #endif
    }
    {
        auto str = utl::to_string<utl::static_string>(99);
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "99" );
            CHECK( isequal );
        }
        #endif
    }
}