#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <tuple>
#include <ratio>
#include <utility>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("accumulate(add)" * doctest::test_suite("meta"))
{
    {
        using arg_t      = std::tuple<meta::ct<1>,meta::ct<3>>;
        using result_t   = meta::apply_accumulate_t<meta::add,arg_t>;
        using expected_t = std::tuple<meta::ct<1>,meta::ct<4>>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    // @note fail on gcc, success on clang
    // {
    //     using arg_t = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<7>>;
    //     using result_t = meta::apply_accumulate_t<meta::add,arg_t>;
    //     using expected_t = std::tuple<meta::ct<1>,meta::ct<4>,meta::ct<11>>;
    //     STATIC_CHECK_IS_SAME( result_t, expected_t );
    // }
    // {
    //     using arg_t = std::tuple<meta::ct<1>,std::ratio<1,3>,meta::ct<2>>;
    //     using result_t = meta::apply_accumulate_t<meta::add,arg_t>;
    //     using expected_t = std::tuple<meta::ct<1>,std::ratio<4,3>,std::ratio<10,3>>;
    //     STATIC_CHECK_IS_SAME( result_t, expected_t );
    // }
}