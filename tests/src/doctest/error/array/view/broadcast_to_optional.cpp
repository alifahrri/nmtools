#define NMTOOLS_USE_OPTIONAL
#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_impl(...) \
nm::view::broadcast_to(__VA_ARGS__);

TEST_CASE("broadcast_to(optional)" * doctest::test_suite("view::broadcast_to"))
{
    SUBCASE("array")
    {
        int x[3] = {1,2,3};
        auto shape = std::array{3,4};
        auto result = RUN_impl(x,shape);
        CHECK( !static_cast<bool>(result) );
    }
}