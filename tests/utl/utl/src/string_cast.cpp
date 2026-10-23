#include "nmtools/utl/string_cast.hpp"
#include "nmtools/testing/doctest.hpp"

namespace utl = nmtools::utl;

TEST_CASE("string_cast static_string to string")
{
    auto ss = utl::static_string("hi!");

    // static -> dynamic
    auto dyn = utl::string_cast<utl::string>(ss);
    CHECK( dyn == "hi!" );
    // dynamic strings also exclude the trailing '\0' from size
    CHECK( dyn.size() == 3 );

    // dynamic -> static roundtrip
    auto back = utl::string_cast<utl::static_string>(dyn);
    CHECK( back == "hi!" );
    // static strings exclude the trailing '\0' from size
    CHECK( back.size() == 3 );
}

TEST_CASE("string_cast static_string to static_string")
{
    auto ss = utl::static_string("hello");

    // same capacity
    auto same = utl::string_cast<utl::static_string>(ss);
    CHECK( same == "hello" );

    // different capacity
    using small_t = utl::static_string_base<8, char>;
    auto small = utl::string_cast<small_t>(ss);
    CHECK( small == "hello" );
    CHECK( small.size() == 5 );

    // overflowing capacity panics
    using tiny_t = utl::static_string_base<5, char>;
    CHECK_THROWS_AS( (void)utl::string_cast<tiny_t>(ss), std::runtime_error );
}

TEST_CASE("string_cast empty string")
{
    auto ss = utl::static_string();
    CHECK( ss.size() == 0 );

    auto dyn = utl::string_cast<utl::string>(ss);
    auto back = utl::string_cast<utl::static_string>(dyn);
    CHECK( back.size() == 0 );

    auto empty_dyn = utl::string();
    auto to_static = utl::string_cast<utl::static_string>(empty_dyn);
    CHECK( to_static.size() == 0 );
}

TEST_CASE("string_cast constexpr static_string")
{
    constexpr auto cs = [](){
        auto s = utl::static_string("abc");
        return utl::string_cast<utl::static_string>(s);
    }();
    static_assert(cs.size() == 3, "constexpr cast failed");

    using small_t = utl::static_string_base<8, char>;
    constexpr auto cc = [](){
        auto s = utl::static_string("abc");
        return utl::string_cast<small_t>(s);
    }();
    static_assert(cc == "abc", "constexpr capacity cast failed");
}

TEST_CASE("string_cast truncate flag")
{
    auto ss = utl::static_string("hello world");

    // constant index true: overflowing static destination truncates
    using tiny_t = utl::static_string_base<6, char>;
    auto t = utl::string_cast<tiny_t, nmtools::meta::true_type>(ss);
    CHECK( t.size() == 5 );
    CHECK( t == "hello" );

    // explicit false keeps the panicking behavior
    auto cast_strict = [&](){ return (void)utl::string_cast<tiny_t, nmtools::meta::false_type>(ss); };
    CHECK_THROWS_AS( cast_strict(), std::runtime_error );

    // fitting destination is unaffected
    using big_t = utl::static_string_base<64, char>;
    auto b = utl::string_cast<big_t, nmtools::meta::true_type>(ss);
    CHECK( b == "hello world" );

    // dynamic destination never truncates nor panics
    auto d = utl::string_cast<utl::string, nmtools::meta::true_type>(ss);
    CHECK( d == "hello world" );

    // dynamic source is clamped when casting into a static destination
    // with truncate flag, and panics without it
    auto dyn = utl::string("hello world");
    auto dt = utl::string_cast<tiny_t, nmtools::meta::true_type>(dyn);
    CHECK( dt.size() == 5 );
    CHECK( dt == "hello" );
    auto dyn_strict = [&](){ return (void)utl::string_cast<tiny_t>(dyn); };
    CHECK_THROWS_AS( dyn_strict(), std::runtime_error );
}

#if NMTOOLS_UTL_HAS_STD_STRING
TEST_CASE("string_cast std::string")
{
    auto ss = utl::static_string("hi!");

    // utl -> std::string drops the trailing '\0'
    auto stdstr = utl::string_cast<std::string>(ss);
    CHECK( stdstr == "hi!" );
    CHECK( stdstr.size() == 3 );

    // std::string -> utl appends the trailing '\0'
    auto back_static = utl::string_cast<utl::static_string>(stdstr);
    CHECK( back_static == "hi!" );
    CHECK( back_static.size() == 3 );

    auto back_dyn = utl::string_cast<utl::string>(stdstr);
    CHECK( back_dyn == "hi!" );
    CHECK( back_dyn.size() == 3 );

    // dynamic destination grows past its small string buffer
    auto long_std = std::string("hello world, long enough to grow");
    auto dyn = utl::string_cast<utl::string>(long_std);
    CHECK( dyn == "hello world, long enough to grow" );
    CHECK( dyn.size() == long_std.size() );

    // dynamic -> std::string roundtrip
    auto std2 = utl::string_cast<std::string>(dyn);
    CHECK( std2 == long_std );

    // empty std::string
    auto empty_static = utl::string_cast<utl::static_string>(std::string());
    CHECK( empty_static.size() == 0 );
    auto empty_std = utl::string_cast<std::string>(empty_static);
    CHECK( empty_std.size() == 0 );

    // overflowing capacity panics
    using tiny_t = utl::static_string_base<3, char>;
    CHECK_THROWS_AS( (void)utl::string_cast<tiny_t>(stdstr), std::runtime_error );

    // std::string source is clamped when casting into a static destination
    // with truncate flag
    auto st = utl::string_cast<tiny_t, nmtools::meta::true_type>(stdstr);
    CHECK( st.size() == 2 );
    CHECK( st == "hi" );
    CHECK_THROWS_AS( (void)utl::string_cast<tiny_t>(std::string("abcd")), std::runtime_error );
}
#endif // NMTOOLS_UTL_HAS_STD_STRING
