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
}