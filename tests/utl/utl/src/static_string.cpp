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
}

TEST_CASE("static_string::join" * doctest::test_suite("utl"))
{
    using utl::static_string;
    {
        #ifndef __HIPCC__
        auto strs = nmtools_array{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        #else
        auto strs = nmtools_array<static_string,3>{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        #endif // __HIPCC__
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
        #ifndef __HIPCC__
        constexpr auto strs = nmtools_array{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        #else
        constexpr auto strs = nmtools_array<static_string,3>{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        #endif // __HIPCC__
        constexpr auto str = static_string(",").join(strs);
        CHECK( str.size() == 6 );
        #if !DISABLE_CHECK
        {
            auto isequal = ( str == "1,3,5" );
            CHECK( isequal );
        }
        #endif
    }
}