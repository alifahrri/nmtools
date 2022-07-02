#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("promote_index(case1)" * doctest::test_suite("meta::promote_index"))
{
    {
        using left_t   = unsigned int;
        using right_t  = unsigned int;
        using result_t = meta::promote_index_t<left_t,right_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, unsigned int );
    }
}