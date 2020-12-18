#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <tuple>
#include <array>

namespace meta = nmtools::meta;

TEST_CASE("apply" * doctest::test_suite("meta"))
{
    {
        using arg_t      = std::tuple<int,size_t>;
        using result_t   = meta::apply_t<std::common_type,arg_t>;
        using expected_t = std::common_type_t<int,size_t>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg_t      = std::tuple<int,std::tuple<size_t,int>>;
        using result_t   = meta::apply_t<std::common_type,arg_t>;
        // using expected_t = std::common_type_t<int,size_t>;
        STATIC_CHECK_IS_SAME( result_t, void );
    }
}