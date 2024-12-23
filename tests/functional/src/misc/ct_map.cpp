#include "nmtools/utility/ct_map.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utility = nm::utility;

using namespace nmtools::literals;

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

TEST_CASE("ct_map")
{
    auto a = nmtools_tuple{1_ct,3_ct};
    auto b = nmtools_tuple{3_ct};

    auto map = utility::ct_map()
        .insert(meta::ct_v<0>,a)
        .insert(meta::ct_v<1>,b)
        .insert(meta::ct_v<3>,nmtools_tuple{})
    ;
    NMTOOLS_ASSERT_EQUAL( map.size(), 3 );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( map.at(meta::ct_v<1>), b );
    static_assert( meta::is_same_v<decltype(map.at(meta::ct_v<3>)),decltype(nmtools_tuple{})> );
    
    auto map_1 = map.erase(3_ct);
    NMTOOLS_ASSERT_EQUAL( map_1.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( map_1.at(meta::ct_v<0>), a );
    NMTOOLS_ASSERT_EQUAL( map_1.at(meta::ct_v<1>), b );

    auto map_2 = map_1.erase(1_ct);
    NMTOOLS_ASSERT_EQUAL( map_2.size(), 1 );
    NMTOOLS_ASSERT_EQUAL( map_2.at(meta::ct_v<0>), a );

    auto map_3 = map_2.insert(4_ct,nmtools::None);
    NMTOOLS_ASSERT_EQUAL( map_3.size(), 2 );
    NMTOOLS_ASSERT_EQUAL( map_3.at(0_ct), a );
    NMTOOLS_ASSERT_EQUAL( map_3.at(4_ct), nmtools::None );
}

TEST_CASE("tuple_filter")
{
    auto init = nmtools_tuple{0_ct,1_ct,2_ct,3_ct};
    auto filter = [](auto element){
        constexpr auto ELEMENT = decltype(element)::value;
        if constexpr ((ELEMENT % 2) == 0) {
            return meta::false_type{};
        } else {
            return meta::true_type{};
        }
    };
    auto result = utility::tuple_filter(init,filter);
    static_assert( meta::is_same_v<decltype(result),decltype(nmtools_tuple{1_ct,3_ct})>);
}

TEST_CASE("tuple_index")
{
    auto init = nmtools_tuple{0_ct,2_ct,3_ct,5_ct};
    auto result = utility::tuple_index(init,3_ct);
    auto expect = 2_ct;
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("tuple_update")
{
    auto init = nmtools_tuple{0_ct,2_ct,3_ct,5_ct};
    auto result = utility::tuple_update(init,1_ct,7_ct);
    auto expect = nmtools_tuple{0_ct,7_ct,3_ct,5_ct};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}