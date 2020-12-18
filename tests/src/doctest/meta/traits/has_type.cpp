#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <tuple>

namespace meta = nmtools::meta;

TEST_CASE("has_type" * doctest::test_suite("traits"))
{
    {
        using arg_t = std::common_type<int,size_t>;
        STATIC_CHECK(( meta::has_type_v<arg_t> ));
    }
    {
        using arg_t = std::common_type<int,std::tuple<size_t,int>>;
        STATIC_CHECK(( !meta::has_type_v<arg_t> ));
    }
}