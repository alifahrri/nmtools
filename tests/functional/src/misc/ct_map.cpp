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