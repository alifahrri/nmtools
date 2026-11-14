#include "nmtools/meta.hpp"
#include "nmtools/utl/constant_map.hpp"
#include "nmtools/utl/flat_map.hpp"
#include "nmtools/utl/static_map.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
namespace utl = nm::utl;

using nmtools_tuple, nmtools::ct, nmtools::ct_v;
using nmtools_array;
using namespace nmtools::literals;

using cm_t   = utl::constant_map<tuple<ct<2>,ct<3>,ct<5>>,tuple<ct<1>,int,ct<4>>>;
using fm_t   = utl::flat_map<int,int>;
using sm_t   = utl::static_map<int,int>;

TEST_CASE("is_map" * doctest::test_suite("utl"))
{
    // true for the three map types
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_map_v<cm_t>, true );
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_map_v<fm_t>, true );
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_map_v<sm_t>, true );

    // cv-ref qualified map is still a map
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_map_v<const sm_t&>, true );

    // false for non-map types, even when indexable (has_at satisfied)
    NMTOOLS_STATIC_ASSERT_EQUAL( (meta::is_map_v<nmtools_tuple<int,int>>), false );
    NMTOOLS_STATIC_ASSERT_EQUAL( (meta::is_map_v<nmtools_array<int,3>>), false );
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_map_v<int>, false );}

TEST_CASE("is_constant_map" * doctest::test_suite("utl"))
{
    // only true for constant_map
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_constant_map_v<cm_t>, true );
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_constant_map_v<const cm_t&>, true );

    // false for the other maps, even though they are is_map
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_constant_map_v<fm_t>, false );
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_constant_map_v<sm_t>, false );
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_constant_map_v<int>, false );
}
