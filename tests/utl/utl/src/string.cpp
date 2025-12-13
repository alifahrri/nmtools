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
}

TEST_CASE("string::join" * doctest::test_suite("utl"))
{
    using utl::string;
    {
        auto strs = nmtools_array{string::to_string(1), string::to_string(3), string::to_string(5)};
        auto str = string(",").join(strs);
        CHECK( str.size() == 6 );
        auto isequal = ( str == "1,3,5" );
        CHECK( isequal );
    }
}