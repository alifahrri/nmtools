#include "nmtools/index/repeat.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("repeat" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using shape_t = nmtools_array<size_t,2>;
        using axis_t  = nm::none_t;
        using repeats_t = int;
        using indices_t = nmtools_array<size_t,2>;
        using result_t = meta::resolve_optype_t<nm::index::repeat_t,shape_t,indices_t,repeats_t,axis_t>;
        using expected_t = nmtools_array<size_t,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}

TEST_CASE("shape_repeat" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using shape_t = nmtools_array<size_t,2>;
        using axis_t  = nm::none_t;
        using indices_t = nmtools_array<size_t,2>;
        using result_t = meta::resolve_optype_t<nm::index::shape_repeat_t,shape_t,indices_t,axis_t>;
        using expected_t = nmtools_array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}