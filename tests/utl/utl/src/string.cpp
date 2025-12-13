#include "nmtools/utl/string.hpp"
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
        #if !IS_ARM_V5
        CHECK( str == "hello" );
        #endif
    }
    {
        utl::string str;
        str = "hello";
        [[maybe_unused]]
        utl::string other = str;
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        #if !IS_ARM_V5
        CHECK( other == "hello" );
        #endif
    }
    {
        utl::string str;
        str = "hello";
        auto other = str + " " + "world";
        NMTOOLS_ASSERT_EQUAL( other.size(), 12 );
        #if !IS_ARM_V5
        CHECK( other == "hello world" );
        #endif
    }
    {
        utl::string str;
        str = "Lorem";
        auto other = str + " " + "ipsum" + " " + "dolor" + " " + "sit amet," + " " + "consectetur adipiscing elit,";
        NMTOOLS_ASSERT_EQUAL( other.size(), 57 );
        #if !IS_ARM_V5
        CHECK( other == "Lorem ipsum dolor sit amet, consectetur adipiscing elit," );
        #endif
    }
    {
        utl::string str;
        str += "hello";
        str += " ";
        str += "world";
        #if !IS_ARM_V5
        CHECK( str == "hello world" );
        #endif
    }
    {
        utl::string str;
        str = "hello";
        str[0] = 'H';
        #if !IS_ARM_V5
        CHECK( str == "Hello" );
        #endif
    }
    {
        utl::string str;
        str = "hello world";
        auto substr = str.substr(6);
        #if !IS_ARM_V5
        CHECK( substr == "world" );
        #endif
    }
    {
        utl::string str;
        str = "xmplr";
        str.insert(0,"E");
        NMTOOLS_ASSERT_EQUAL( str.size(), 7 );
        #if !IS_ARM_V5
        CHECK( str == "Exmplr" );
        #endif
        str.insert(2,"e");
        str.insert(6,"a");
        #if !IS_ARM_V5
        CHECK( str == "Exemplar" );
        #endif
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
    }
    {
        utl::string str("hello world");
        #if !IS_ARM_V5
        CHECK( str == "hello world" );
        #endif
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
}

TEST_CASE("string::to_string" * doctest::test_suite("utl"))
{
    {
        auto str = utl::string::to_string(0);
        #if !IS_ARM_V5
        CHECK( str == "0" );
        #endif
    }
    {
        auto str = utl::string::to_string(3);
        #if !IS_ARM_V5
        CHECK( str == "3" );
        #endif
    }
    {
        auto str = utl::string::to_string(13);
        #if !IS_ARM_V5
        CHECK( str == "13" );
        #endif
    }
    {
        auto str = utl::string::to_string(103);
        #if !IS_ARM_V5
        CHECK( str == "103" );
        #endif
    }
    {
        auto str = utl::string::to_string(1103);
        #if !IS_ARM_V5
        CHECK( str == "1103" );
        #endif
    }
    {
        auto str = utl::string::to_string(-3);
        #if !IS_ARM_V5
        CHECK( str == "-3" );
        #endif
    }
    {
        auto str = utl::string::to_string(-13);
        #if !IS_ARM_V5
        CHECK( str == "-13" );
        #endif
    }
    {
        auto str = utl::string::to_string(-103);
        #if !IS_ARM_V5
        CHECK( str == "-103" );
        #endif
    }
    {
        auto str = utl::string::to_string(-1103);
        #if !IS_ARM_V5
        CHECK( str == "-1103" );
        #endif
    }

    // array
    {
        auto array = nmtools_array{0,-3,13};
        auto str = utl::string::to_string(array);
        #if !IS_ARM_V5
        CHECK( str == "{0,-3,13}" );
        #endif
    }
    {
        auto array = nmtools_list<int>();
        array.push_back(0);
        array.push_back(-3);
        array.push_back(13);
        auto str = utl::string::to_string(array);
        #if !IS_ARM_V5
        CHECK( str == "{0,-3,13}" );
        #endif
    }
}

TEST_CASE("string::join" * doctest::test_suite("utl"))
{
    using utl::string;
    {
        auto strs = nmtools_array{string::to_string(1), string::to_string(3), string::to_string(5)};
        auto str = string(",").join(strs);
        CHECK( str.size() == 6 );
        #if !IS_ARM_V5
        CHECK( str == "1,3,5" );
        #endif
    }
}