#include "nmtools/utl/variant.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/string.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nmtools::utl;

#include <memory>

TEST_CASE("variant" * doctest::test_suite("utl"))
{
    {
        using variant = utl::variant<int,double>;

        auto v1 = variant{1};
        CHECK( v1.index() == 0 );
        CHECK( v1.get_if<int>() );
        CHECK( !(v1.get_if<double>()) );
        CHECK( *v1.get_if<int>() == 1 );

        auto v2 = variant{2.0};
        CHECK( v2.index() == 1 );
        CHECK( !(v2.get_if<int>()) );
        CHECK( v2.get_if<double>() );
        NMTOOLS_ASSERT_CLOSE( *v2.get_if<double>(), 2.0 );

        auto v3 = variant{v2};
        CHECK( v3.index() == 1 );
        CHECK( !(v3.get_if<int>()) );
        CHECK( v3.get_if<double>() );
        NMTOOLS_ASSERT_CLOSE( *v3.get_if<double>(), 2.0 );

        auto v4 = variant();
        CHECK( v4.index() == 0 );
        v4 = v3;
        CHECK( v4.index() == 1 );

        CHECK( nmtools::is_trivially_destructible_v<variant> );
        CHECK( nmtools::variant_size_v<variant> == 2 );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<0,variant>,int> );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<1,variant>,double> );
        CHECK( nmtools::variant_has_type_v<variant,int> == true );
        CHECK( nmtools::variant_has_type_v<variant,double> == true );
        CHECK( nmtools::variant_has_type_v<variant,utl::string> == false );
        CHECK( nmtools::is_either_v<variant> );
        CHECK( nmtools::is_variant_v<variant> );
        CHECK( nmtools::is_same_v<nm::get_either_left_t<variant>,int> );
        CHECK( nmtools::is_same_v<nm::get_either_right_t<variant>,double> );
    }

    {
        using array_type = utl::array<int,3>;
        using variant = utl::variant<int,double,array_type>;

        auto v1 = variant{1};
        CHECK( v1.index() == 0 );
        CHECK( v1.get_if<int>() );
        CHECK( !(v1.get_if<double>()) );
        CHECK( !(v1.get_if<array_type>()) );

        auto v2 = variant{2.0};
        CHECK( v2.index() == 1 );
        CHECK( !(v2.get_if<int>()) );
        CHECK( v2.get_if<double>() );
        CHECK( !(v2.get_if<array_type>()) );

        auto a = array_type{1,2,3};
        auto v3 = variant{a};
        CHECK( v3.index() == 2 );
        CHECK( !(v3.get_if<int>()) );
        CHECK( !(v3.get_if<double>()) );
        CHECK( v3.get_if<array_type>() );

        auto v4 = variant{v3};
        CHECK( v4.index() == 2 );
        CHECK( !(v4.get_if<int>()) );
        CHECK( !(v4.get_if<double>()) );
        CHECK( v4.get_if<array_type>() );

        auto v5 = variant();
        CHECK( v5.index() == 0 );
        v5 = v4;
        CHECK( v5.index() == 2 );
        v5 = v2;
        CHECK( v5.index() == 1 );

        CHECK( nmtools::is_trivially_destructible_v<variant> );
        CHECK( nmtools::variant_size_v<variant> == 3 );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<0,variant>,int> );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<1,variant>,double> );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<2,variant>,array_type> );
        CHECK( nmtools::variant_has_type_v<variant,int> == true );
        CHECK( nmtools::variant_has_type_v<variant,double> == true );
        CHECK( nmtools::variant_has_type_v<variant,array_type> == true );
        CHECK( nmtools::variant_has_type_v<variant,utl::string> == false );
        CHECK( nmtools::is_either_v<variant> == false );
        CHECK( nmtools::is_variant_v<variant> );
    }

    {
        using array_type = utl::array<int,3>;
        using variant = utl::variant<array_type>;

        auto v1 = variant();
        CHECK( v1.index() == 0 );
        v1 = array_type{1,2,3};
        NMTOOLS_ASSERT_EQUAL( *v1.get_if<array_type>(), (array_type{1,2,3}) );

        CHECK( nmtools::is_trivially_destructible_v<variant> );
        CHECK( nmtools::is_either_v<variant> == false );
        CHECK( nmtools::is_variant_v<variant> );
    }

    {
        using string_type = utl::string;
        using variant = utl::variant<int,string_type>;

        auto v1 = variant(0);
        auto v2 = variant{string_type("hello")};

        CHECK( v1.index() == 0 );
        v1 = v2;
        CHECK( v1.index() == 1 );
        CHECK( v1.get_if<string_type>() );
        #if defined(__arm__) && defined(__ARM_ARCH) && __ARM_ARCH == 5
        auto is_same = (*v1.get_if<string_type>() == string_type("hello") );
        CHECK( is_same );
        #else
        CHECK( *v1.get_if<string_type>() == string_type("hello") );
        #endif

        CHECK( !nmtools::is_trivially_destructible_v<variant> );
        CHECK( nmtools::variant_size_v<variant> == 2 );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<0,variant>,int> );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<1,variant>,string_type> );
        CHECK( nmtools::variant_has_type_v<variant,int> == true );
        CHECK( nmtools::variant_has_type_v<variant,double> == false );
        CHECK( nmtools::variant_has_type_v<variant,utl::string> == true );
        CHECK( nmtools::is_either_v<variant> );
        CHECK( nmtools::is_variant_v<variant> );
        CHECK( nmtools::is_same_v<nm::get_either_left_t<variant>,int> );
        CHECK( nmtools::is_same_v<nm::get_either_right_t<variant>,string_type> );
    }

    {
        using string_type = utl::string;
        using array_type  = utl::array<int,3>;
        using variant = utl::variant<int,string_type,array_type>;

        auto v1 = variant(0);
        auto v2 = variant{string_type("hello")};
        auto v3 = variant{array_type{1,2,3}};

        CHECK( v1.index() == 0 );
        v1 = v2;
        CHECK( v1.index() == 1 );
        #if defined(__arm__) && defined(__ARM_ARCH) && __ARM_ARCH == 5
        auto is_same = (*v1.get_if<string_type>() == string_type("hello") );
        CHECK( is_same );
        #else
        CHECK( *v1.get_if<string_type>() == string_type("hello") );
        #endif
        v1 = v3;
        CHECK( v1.index() == 2 );
        CHECK( v1.get_if<array_type>() );
        NMTOOLS_ASSERT_EQUAL( *v1.get_if<array_type>(), (array_type{1,2,3}) );

        CHECK( !nmtools::is_trivially_destructible_v<variant> );
        CHECK( nmtools::variant_size_v<variant> == 3 );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<0,variant>,int> );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<1,variant>,string_type> );
        CHECK( nmtools::is_same_v<nm::variant_alternative_t<2,variant>,array_type> );
        CHECK( nmtools::variant_has_type_v<variant,int> == true );
        CHECK( nmtools::variant_has_type_v<variant,double> == false );
        CHECK( nmtools::variant_has_type_v<variant,utl::string> == true );
        CHECK( nmtools::variant_has_type_v<variant,array_type> == true );
        CHECK( nmtools::is_either_v<variant> == false );
        CHECK( nmtools::is_variant_v<variant> );
    }

    {
        using string_type = utl::string;
        using variant = utl::variant<string_type>;

        auto v1 = variant();
        CHECK( v1.index() == 0 );
        v1 = string_type{"hello"};
        #if defined(__arm__) && defined(__ARM_ARCH) && __ARM_ARCH == 5
        auto is_same = ( *v1.get_if<string_type>() == string_type{"hello"} );
        CHECK( is_same );
        #else
        CHECK( *v1.get_if<string_type>() == string_type{"hello"} );
        #endif

        CHECK( !nmtools::is_trivially_destructible_v<variant> );
        CHECK( nmtools::is_either_v<variant> == false );
        CHECK( nmtools::is_variant_v<variant> );
    }

    {
        using u8_buffer_t  = std::shared_ptr<nmtools_list<uint8_t>>;
        using f32_buffer_t = std::shared_ptr<nmtools_list<float>>;

        using variant = utl::variant<u8_buffer_t,f32_buffer_t>;

        auto v1 = variant(std::make_shared<nmtools_list<uint8_t>>());
        auto v2 = variant(std::make_shared<nmtools_list<float>>());

        CHECK( v1.index() == 0 );
        CHECK( v2.index() == 1 );
    }

    {
        using u8_buffer_t  = std::shared_ptr<nmtools_list<uint8_t>>;
        using u16_buffer_t = std::shared_ptr<nmtools_list<uint16_t>>;
        using u32_buffer_t = std::shared_ptr<nmtools_list<uint32_t>>;
        using u64_buffer_t = std::shared_ptr<nmtools_list<uint64_t>>;
        using f32_buffer_t = std::shared_ptr<nmtools_list<float>>;

        using variant = utl::variant<u8_buffer_t,u16_buffer_t,u32_buffer_t,u64_buffer_t,f32_buffer_t>;

        auto v1 = variant(std::make_shared<nmtools_list<uint8_t>>());
        auto v2 = variant(std::make_shared<nmtools_list<float>>());

        CHECK( v1.index() == 0 );
        CHECK( v2.index() == 4 );
    }
}