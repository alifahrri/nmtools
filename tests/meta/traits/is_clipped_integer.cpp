#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nmtools::meta;

TEST_CASE("is_clipped_integer" * doctest::test_suite("traits"))
{
    {
        using type = nm::clipped_size_t<3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_clipped_integer, type );
    }
    {
        using type = nm::clipped_int8_t<3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_clipped_integer, type );
    }
}