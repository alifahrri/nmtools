#include "nmtools/utl/format.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nmtools::utl;

TEST_CASE("format" * doctest::test_suite("utl"))
{
    {
        auto fmt_args = utl::make_format_args(1,2.f);
        CHECK( fmt_args.size() == 2 );

        CHECK( fmt_args[0].get_if<int>() );
        CHECK( fmt_args[1].get_if<float>() );

        CHECK( !fmt_args[0].get_if<float>() );
        CHECK( !fmt_args[1].get_if<int>() );
    }
    {
        auto fmt_args = utl::make_format_args(1,2.f,3ul,4.);
        CHECK( fmt_args.size() == 4 );

        CHECK( fmt_args[0].get_if<int>() );
        CHECK( fmt_args[1].get_if<float>() );
        CHECK( fmt_args[2].get_if<uint64_t>() );
        CHECK( fmt_args[3].get_if<double>() );

        CHECK( !fmt_args[0].get_if<float>() );
        CHECK( !fmt_args[1].get_if<int>() );
    }
    {
        auto fmt_args = utl::make_format_args(1,2.f,3ul,4.,int8_t(5),uint8_t(6),int16_t(7),uint16_t(8));
        CHECK( fmt_args.size() == 8 );

        CHECK( fmt_args[0].get_if<int>() );
        CHECK( fmt_args[1].get_if<float>() );
        CHECK( fmt_args[2].get_if<uint64_t>() );
        CHECK( fmt_args[3].get_if<double>() );
        CHECK( fmt_args[4].get_if<int8_t>() );
        CHECK( fmt_args[5].get_if<uint8_t>() );
        CHECK( fmt_args[6].get_if<int16_t>() );
        CHECK( fmt_args[7].get_if<uint16_t>() );

        CHECK( *fmt_args[0].get_if<int>() == 1);
        CHECK( *fmt_args[1].get_if<float>() == 2.f );
        CHECK( *fmt_args[2].get_if<uint64_t>() == 3ul );
        CHECK( *fmt_args[3].get_if<double>() == 4. );
        CHECK( *fmt_args[4].get_if<int8_t>() == 5 );
        CHECK( *fmt_args[5].get_if<uint8_t>() == 6 );
        CHECK( *fmt_args[6].get_if<int16_t>() == 7 );
        CHECK( *fmt_args[7].get_if<uint16_t>() == 8 );
    }
    {
        auto string = utl::format(utl::string("hello {}"), 3);
        auto expected = utl::string("hello 3");
        CHECK( string.size() == expected.size() );
        for (nm_size_t i=0; (i<string.size()) && (i<expected.size()); i++) {
            CHECK( string[i] == expected[i] );
        }
        for (nm_size_t i=expected.size(); i<string.size(); i++) {
            CHECK( string[i] == 0 );
        }
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    using types = nm::type_list<
        nm::int8_t,nm::int16_t,nm::int32_t,nm::int64_t
        , nm::uint8_t,nm::uint16_t,nm::uint32_t,nm::uint64_t>;
    nm::template_for<nm::len_v<types>>([](auto i){
        constexpr auto I = decltype(i)::index;
        using type  = nm::at_t<types,I>;
        auto number = (type)3;
        auto string = utl::format("hello {}", number);
        auto expected = utl::string("hello 3");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    });

    // floating point
    {
        auto string = utl::format("hello {}", 3.14f);
        auto expected = utl::string("hello 3.140000");
        CHECK( string.size() == expected.size() );
        auto is_same = string == expected;
        CHECK( is_same );
        // CHECK( string == expected );
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format("hello {}", 3.14);
        auto expected = utl::string("hello 3.140000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format("hello {}", -2.5f);
        auto expected = utl::string("hello -2.500000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format("hello {}", 1234.5678);
        auto expected = utl::string("hello 1234.567800");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format<utl::string_base<64>>("{} + {} + {}", 1, 2.5, 3.14f);
        auto expected = utl::string("1 + 2.500000 + 3.140000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        // note: meta::numeric_limits<float>::max() returns infinity
        auto string = utl::format("hello {}", nm::meta::numeric_limits<float>::max());
        auto expected = utl::string("hello inf");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        // note: meta::numeric_limits<double>::max() returns infinity
        auto string = utl::format("hello {}", -nm::meta::numeric_limits<double>::max());
        auto expected = utl::string("hello -inf");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        // inf - inf = nan
        auto inf = nm::meta::numeric_limits<float>::max();
        auto string = utl::format("hello {}", inf - inf);
        auto expected = utl::string("hello nan");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }

    // string
    {
        auto string = utl::format("hello {}", utl::string("world"));
        auto expected = utl::string("hello world");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        // argument order specified in the placeholder
        auto string = utl::format<utl::string_base<64>>("second: {1} first {0}", 3.f, 4);
        auto expected = utl::string("second: 4 first 3.000000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format("{1} then {0}", 3.f, 4);
        auto expected = utl::string("4 then 3.000000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format("{} {} {0}", utl::string("x"), utl::string("y"));
        auto expected = utl::string("x y x");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format<utl::string_base<64>>("hello {1} and {0}", utl::string_base<64>("x"), utl::string_base<64>("y"));
        auto expected = utl::string("hello y and x");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format("{} {} {}", utl::string("n"), utl::string("="), 3);
        auto expected = utl::string("n = 3");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        auto string = utl::format("{} {}", utl::string("pi~"), 3.14);
        auto expected = utl::string("pi~ 3.140000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }

    // constexpr with static_string output
    {
        constexpr auto string = utl::format<utl::static_string>("hello {}", 3);
        auto expected = utl::static_string("hello 3");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        // argument order specified in the placeholder
        constexpr auto string = utl::format<utl::static_string>("second: {1} first {0}", 3.f, 4);
        auto expected = utl::static_string("second: 4 first 3.000000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        // same argument used multiple times
        constexpr auto string = utl::format<utl::static_string>("{1} {1} {0} {0}", utl::static_string("x"), utl::static_string("y"));
        auto expected = utl::static_string("y y x x");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        constexpr auto string = utl::format<utl::static_string>("hello {}", 3.14f);
        auto expected = utl::static_string("hello 3.140000");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        constexpr auto string = utl::format<utl::static_string>("hello {}", utl::static_string("world"));
        auto expected = utl::static_string("hello world");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        constexpr auto string = utl::format<utl::static_string>("{} + {} + {}", 1, 2.5, utl::static_string("x"));
        auto expected = utl::static_string("1 + 2.500000 + x");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
    {
        // note: meta::numeric_limits<float>::max() returns infinity
        constexpr auto string = utl::format<utl::static_string>("hello {}", nm::meta::numeric_limits<float>::max());
        auto expected = utl::static_string("hello inf");
        CHECK( string.size() == expected.size() );
        #if defined(__arm__) && defined(__ARM_ARCH)
        auto is_same = string == expected;
        CHECK( is_same );
        #else
        CHECK( string == expected );
        #endif
        std::cout << string << std::endl;
    }
}