#include "nmtools/array/index/where.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;
// cant have nice things: error: ‘namespace index = nmtools::nmtools::index;’ redeclared as different kind of entity
// /usr/include/strings.h:50:20: note: previous declaration ‘const char* index(const char*, int)’
// somehow mixed with c string (?) TODO: fix
// namespace index = nm::index;

TEST_CASE("where" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using array_t = nmtools_array<size_t,2>;
        using index_t = size_t;
        using result_t = meta::resolve_optype_t<nm::index::where_t,array_t,index_t>;
        using expected_t = nm::array::hybrid_ndarray<size_t,2,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    SUBCASE("case2")
    {
        using array_t = nmtools_list<size_t>;
        using index_t = size_t;
        using result_t = meta::resolve_optype_t<nm::index::where_t,array_t,index_t>;
        using expected_t = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    SUBCASE("dynamic_ndarray")
    {
        using array_t = nm::array::dynamic_ndarray<size_t>;
        using index_t = size_t;
        using result_t = meta::resolve_optype_t<nm::index::where_t,array_t,index_t>;
        using expected_t = nm::array::dynamic_ndarray<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}