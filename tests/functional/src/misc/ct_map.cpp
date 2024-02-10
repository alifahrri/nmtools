#include "nmtools/utility/ct_map.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utility = nm::utility;

TEST_CASE("ct_map")
{
    auto a = nmtools_array{1,2,3,4};
    auto b = nmtools_array{5,6};

    auto map = utility::ct_map()
        .insert(meta::ct_v<0>,a)
        .insert(meta::ct_v<1>,b)
    ;
    NMTOOLS_ASSERT_EQUAL( map.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<1>), b );
}

TEST_CASE("ct_map")
{
    auto a = nmtools_array{1,2,3,4};
    auto b = nmtools_array{5,6};

    auto map = utility::ct_map()
        .insert(meta::ct_v<0>,&a)
        .insert(meta::ct_v<1>,&b)
    ;
    NMTOOLS_ASSERT_EQUAL( map.size(), 2 );
    CHECK( map.at(meta::ct_v<0>) == &a );
    CHECK( map.at(meta::ct_v<1>) == &b );
    NMTOOLS_ASSERT_EQUAL( *map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( *map.at(meta::ct_v<1>), b );
}

TEST_CASE("ct_map")
{
    auto a = nmtools_array{1,2,3,4};
    auto b = nmtools_array{5,6};

    auto map = utility::ct_map()
        .insert(meta::ct_v<0>,a)
        .insert(meta::ct_v<1>,b)
    ;
    NMTOOLS_ASSERT_EQUAL( map.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<1>), b );

    // different type but equal
    auto c = nmtools_list{5,6};
    auto new_map = map.update(meta::ct_v<1>,c);
    NMTOOLS_ASSERT_EQUAL( new_map.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( new_map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( new_map.at(meta::ct_v<1>), c );
    NMTOOLS_STATIC_CHECK_IS_SAME( decltype(new_map.at(meta::ct_v<1>)), decltype(c) );
}

TEST_CASE("ct_map")
{
    auto a = nmtools_array{1,2,3,4};
    auto b = nmtools_array{5,6};

    auto map = utility::ct_map()
        .insert(meta::ct_v<0>,&a)
        .insert(meta::ct_v<1>,&b)
    ;
    NMTOOLS_ASSERT_EQUAL( map.size(), 2 );
    CHECK( map.at(meta::ct_v<0>) == &a );
    CHECK( map.at(meta::ct_v<1>) == &b );
    NMTOOLS_ASSERT_EQUAL( *map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( *map.at(meta::ct_v<1>), b );

    // different type but equal
    auto c = nmtools_list{5,6};
    auto new_map = map.update(meta::ct_v<1>,&c);
    NMTOOLS_ASSERT_EQUAL( new_map.size(), 2 );
    CHECK( new_map.at(meta::ct_v<1>) == &c ); 
    NMTOOLS_ASSERT_EQUAL( *new_map.at(meta::ct_v<1>), c );
    NMTOOLS_STATIC_CHECK_IS_SAME( meta::remove_cvref_pointer_t<decltype(new_map.at(meta::ct_v<1>))>, decltype(c) );
}

TEST_CASE("ct_map")
{
    constexpr auto a = nmtools_array{1,2,3,4};
    constexpr auto b = nmtools_array{5,6};

    constexpr auto map = utility::ct_map()
        .insert(meta::ct_v<0>,a)
        .insert(meta::ct_v<1>,b)
    ;
    NMTOOLS_ASSERT_EQUAL( map.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<1>), b );

    // different type but equal
    constexpr auto c = nmtools_tuple{meta::ct_v<5>,meta::ct_v<6>};
    constexpr auto new_map = map.update(meta::ct_v<1>,c);
    NMTOOLS_ASSERT_EQUAL( new_map.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( new_map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( new_map.at(meta::ct_v<1>), c );
}