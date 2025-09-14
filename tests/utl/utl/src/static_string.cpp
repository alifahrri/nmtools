#include "nmtools/utl/static_string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

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
        CHECK( str == "hello" );
    }
    {
        utl::static_string str;
        str = "hello";
        [[maybe_unused]]
        utl::static_string other = str;
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        CHECK( other == "hello" );
    }
    {
        utl::static_string str;
        str = "hello";
        auto other = str + " " + "world";
        CHECK( other == "hello world" );
    }
    {
        utl::static_string str;
        str += "hello";
        str += " ";
        str += "world";
        CHECK( str == "hello world" );
    }
    {
        utl::static_string str;
        str = "hello";
        str[0] = 'H';
        CHECK( str == "Hello" );
    }
    {
        utl::static_string str;
        str = "hello world";
        auto substr = str.substr(6);
        CHECK( substr == "world" );
    }
    {
        utl::static_string str;
        str = "xmplr";
        str.insert(0,"E");
        NMTOOLS_ASSERT_EQUAL( str.size(), 7 );
        CHECK( str == "Exmplr" );
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
        CHECK( str == "hello world" );
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
        CHECK( str == "hello" );
    }
    {
        constexpr auto other = [](){
            utl::static_string str;
            str = "hello";
            utl::static_string other = str;
            return other;
        }();
        NMTOOLS_ASSERT_EQUAL( other.size(), 6 );
        CHECK( other == "hello" );
    }
    {
        constexpr auto other = [](){
            utl::static_string str;
            str = "hello";
            auto other = str + " " + "world";
            return other;
        }();
        CHECK( other == "hello world" );
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str += "hello";
            str += " ";
            str += "world";
            return str;
        }();
        CHECK( str == "hello world" );
    }
    {
        constexpr auto str = [](){
            utl::static_string str;
            str = "hello";
            str[0] = 'H';
            return str;
        }();
        CHECK( str == "Hello" );
    }
    {
        constexpr auto substr = [](){
            utl::static_string str;
            str = "hello world";
            auto substr = str.substr(6);
            return substr;
        }();
        CHECK( substr == "world" );
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
        CHECK( str == "hello world" );
    }
}