#include "nmtools/utl/static_string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

#if defined(__arm__) || defined(__thumb__)
    /* We are on an ARM architecture */

    #if __ARM_ARCH == 5
        /* Strictly ARMv5 (generic) */
        #define IS_ARM_V5 1
    #elif defined(__ARM_ARCH_5__)   || \
          defined(__ARM_ARCH_5T__)  || \
          defined(__ARM_ARCH_5E__)  || \
          defined(__ARM_ARCH_5TE__) || \
          defined(__ARM_ARCH_5TEJ__)
        /* Matches various ARMv5 specific variants */
        #define IS_ARM_V5 1
    #else
        #define IS_ARM_V5 0
    #endif

#else
    /* Not ARM */
    #define IS_ARM_V5 0
#endif

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
        #if !IS_ARM_V5
        CHECK( str == "hello" );
        #endif
    }
    {
        utl::static_string str;
        str = "hello";
        [[maybe_unused]]
        utl::static_string other = str;
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        #if !IS_ARM_V5
        CHECK( other == "hello" );
        #endif
    }
    {
        utl::static_string str;
        str = "hello";
        auto other = str + " " + "world";
        #if !IS_ARM_V5
        CHECK( other == "hello world" );
        #endif
    }
    {
        utl::static_string str;
        str += "hello";
        str += " ";
        str += "world";
        #if !IS_ARM_V5
        CHECK( str == "hello world" );
        #endif
    }
    {
        utl::static_string str;
        str = "hello";
        str[0] = 'H';
        #if !IS_ARM_V5
        CHECK( str == "Hello" );
        #endif
    }
    {
        utl::static_string str;
        str = "hello world";
        auto substr = str.substr(6);
        #if !IS_ARM_V5
        CHECK( substr == "world" );
        #endif
    }
    {
        utl::static_string str;
        str = "xmplr";
        str.insert(0,"E");
        NMTOOLS_ASSERT_EQUAL( str.size(), 7 );
        #if !IS_ARM_V5
        CHECK( str == "Exmplr" );
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
        #if !IS_ARM_V5
        CHECK( str == "hello world" );
        #endif
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
        #if !IS_ARM_V5
        CHECK( str == "hello" );
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
        #if !IS_ARM_V5
        CHECK( other == "hello" );
        #endif
    }
    {
        constexpr auto other = [](){
            utl::static_string str;
            str = "hello";
            auto other = str + " " + "world";
            return other;
        }();
        #if !IS_ARM_V5
        CHECK( other == "hello world" );
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
        #if !IS_ARM_V5
        CHECK( str == "hello world" );
        #endif
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello";
            str[0] = 'H';
            return str;
        }();
        #if !IS_ARM_V5
        CHECK( str == "Hello" );
        #endif
    }
    {
        constexpr auto substr = [](){
            utl::static_string str;
            str = "hello world";
            auto substr = str.substr(6);
            return substr;
        }();
        #if !IS_ARM_V5
        CHECK( substr == "world" );
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
        #if !IS_ARM_V5
        CHECK( str == "hello world" );
        #endif
    }
}

TEST_CASE("static_string::to_string" * doctest::test_suite("utl"))
{
    {
        auto str = utl::static_string::to_string(0);
        #if !IS_ARM_V5
        CHECK( str == "0" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(3);
        #if !IS_ARM_V5
        CHECK( str == "3" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(13);
        #if !IS_ARM_V5
        CHECK( str == "13" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(103);
        #if !IS_ARM_V5
        CHECK( str == "103" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(1103);
        #if !IS_ARM_V5
        CHECK( str == "1103" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(-3);
        #if !IS_ARM_V5
        CHECK( str == "-3" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(-13);
        #if !IS_ARM_V5
        CHECK( str == "-13" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(-103);
        #if !IS_ARM_V5
        CHECK( str == "-103" );
        #endif
    }
    {
        auto str = utl::static_string::to_string(-1103);
        #if !IS_ARM_V5
        CHECK( str == "-1103" );
        #endif
    }

    // constexpr
    {
        constexpr auto str = utl::static_string::to_string(0);
        #if !IS_ARM_V5
        CHECK( str == "0" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(3);
        #if !IS_ARM_V5
        CHECK( str == "3" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(13);
        #if !IS_ARM_V5
        CHECK( str == "13" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(103);
        #if !IS_ARM_V5
        CHECK( str == "103" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(1103);
        #if !IS_ARM_V5
        CHECK( str == "1103" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-3);
        #if !IS_ARM_V5
        CHECK( str == "-3" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-13);
        #if !IS_ARM_V5
        CHECK( str == "-13" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-103);
        #if !IS_ARM_V5
        CHECK( str == "-103" );
        #endif
    }
    {
        constexpr auto str = utl::static_string::to_string(-1103);
        #if !IS_ARM_V5
        CHECK( str == "-1103" );
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
        #if !IS_ARM_V5
        CHECK( str == "{0,-3,13}" );
        #endif
    }
    {
        constexpr auto array = nmtools_array{0,-3,13};
        constexpr auto str = utl::static_string::to_string(array);
        #if !IS_ARM_V5
        CHECK( str == "{0,-3,13}" );
        #endif
    }
    {
        auto array = nmtools_static_vector<int,3>();
        array.push_back(0);
        array.push_back(-3);
        array.push_back(13);
        auto str = utl::static_string::to_string(array);
        #if !IS_ARM_V5
        CHECK( str == "{0,-3,13}" );
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
        #if !IS_ARM_V5
        CHECK( str == "{0,-3,13}" );
        #endif
    }
}

TEST_CASE("static_string::join" * doctest::test_suite("utl"))
{
    using utl::static_string;
    {
        auto strs = nmtools_array{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        auto str = static_string(",").join(strs);
        CHECK( str.size() == 6 );
        #if !IS_ARM_V5
        CHECK( str == "1,3,5" );
        #endif
    }
    {
        constexpr auto strs = nmtools_array{static_string::to_string(1), static_string::to_string(3), static_string::to_string(5)};
        constexpr auto str = static_string(",").join(strs);
        CHECK( str.size() == 6 );
        #if !IS_ARM_V5
        CHECK( str == "1,3,5" );
        #endif
    }
}