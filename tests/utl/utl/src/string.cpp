#include "nmtools/utl/string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

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
        CHECK( str == "hello" );
    }
    {
        utl::string str;
        str = "hello";
        [[maybe_unused]]
        utl::string other = str;
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        CHECK( other == "hello" );
    }
    {
        utl::string str;
        str = "hello";
        auto other = str + " " + "world";
        NMTOOLS_ASSERT_EQUAL( other.size(), 12 );
        CHECK( other == "hello world" );
    }
    {
        utl::string str;
        str = "Lorem";
        auto other = str + " " + "ipsum" + " " + "dolor" + " " + "sit amet," + " " + "consectetur adipiscing elit,";
        NMTOOLS_ASSERT_EQUAL( other.size(), 57 );
        CHECK( other == "Lorem ipsum dolor sit amet, consectetur adipiscing elit," );
    }
    {
        utl::string str;
        str += "hello";
        str += " ";
        str += "world";
        CHECK( str == "hello world" );
    }
    {
        utl::string str;
        str = "hello";
        str[0] = 'H';
        CHECK( str == "Hello" );
    }
    {
        utl::string str;
        str = "hello world";
        auto substr = str.substr(6);
        CHECK( substr == "world" );
    }
    {
        utl::string str;
        str = "xmplr";
        str.insert(0,"E");
        NMTOOLS_ASSERT_EQUAL( str.size(), 7 );
        CHECK( str == "Exmplr" );
        str.insert(2,"e");
        str.insert(6,"a");
        CHECK( str == "Exemplar" );
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
        CHECK( str == "hello world" );
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
        CHECK( str == "0" );
    }
    {
        auto str = utl::string::to_string(3);
        CHECK( str == "3" );
    }
    {
        auto str = utl::string::to_string(13);
        CHECK( str == "13" );
    }
    {
        auto str = utl::string::to_string(103);
        CHECK( str == "103" );
    }
    {
        auto str = utl::string::to_string(1103);
        CHECK( str == "1103" );
    }
    {
        auto str = utl::string::to_string(-3);
        CHECK( str == "-3" );
    }
    {
        auto str = utl::string::to_string(-13);
        CHECK( str == "-13" );
    }
    {
        auto str = utl::string::to_string(-103);
        CHECK( str == "-103" );
    }
    {
        auto str = utl::string::to_string(-1103);
        CHECK( str == "-1103" );
    }

    // array
    {
        auto array = nmtools_array{0,-3,13};
        auto str = utl::string::to_string(array);
        CHECK( str == "{0,-3,13}" );
    }
    {
        auto array = nmtools_list<int>();
        array.push_back(0);
        array.push_back(-3);
        array.push_back(13);
        auto str = utl::string::to_string(array);
        CHECK( str == "{0,-3,13}" );
    }
}

TEST_CASE("string::join" * doctest::test_suite("utl"))
{
    using utl::string;
    {
        auto strs = nmtools_array{string::to_string(1), string::to_string(3), string::to_string(5)};
        auto str = string(",").join(strs);
        CHECK( str.size() == 6 );
        CHECK( str == "1,3,5" );
    }
}