#define NMTOOLS_USE_OPTIONAL
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_impl(...) \
nm::view::broadcast_arrays(__VA_ARGS__);

TEST_CASE("broadcast_arrays(exception)" * doctest::test_suite("view::broadcast_arrays"))
{
    SUBCASE("array")
    {
        // int x[3] = {1,2,3};
        auto x = std::vector{1,2,3};
        int y[3][2] = {{1,2},{3,4},{5,6}};
        auto result = RUN_impl(x,y);
        CHECK( !static_cast<bool>(result) );
    }
}