#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using namespace nmtools::literals;

TEST_CASE("ndoffset" * doctest::test_suite("tilekit"))
{
    auto tile_shape  = tuple{2_ct,4_ct};
    auto block_shape = tuple{2_ct,3_ct};

    auto ndoffset = tk::ndoffset(block_shape,tile_shape);

    NMTOOLS_ASSERT_EQUAL( ndoffset.size(), 6 );
    NMTOOLS_ASSERT_EQUAL( ndoffset[0], (tuple{0,0}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[1], (tuple{0,4}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[2], (tuple{0,8}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[3], (tuple{2,0}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[4], (tuple{2,4}) );
    NMTOOLS_ASSERT_EQUAL( ndoffset[5], (tuple{2,8}) );
}