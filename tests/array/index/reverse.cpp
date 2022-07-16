#include "nmtools/array/index/reverse.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
using namespace nm::literals;
using nmtools::utils::isequal;
using std::tuple;
using std::vector;
using std::array;

TEST_CASE("reverse" * doctest::test_suite("index"))
{
    {
        auto indices  = tuple{1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,tuple{1}) );
    }
    {
        auto indices  = tuple{0,1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,tuple{1,0}) );
    }
    {
        auto indices  = tuple{2,0,1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,tuple{1,0,2}) );
    }
    {
        auto indices  = array{1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,array{1}) );
    }
    {
        auto indices  = array{0,1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,array{1,0}) );
    }
    {
        auto indices  = array{2,0,1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,array{1,0,2}) );
    }
    {
        auto indices  = vector{1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,array{1}) );
    }
    {
        auto indices  = vector{0,1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,array{1,0}) );
    }
    {
        auto indices  = vector{2,0,1};
        auto reversed = nm::index::reverse(indices);
        CHECK( isequal(reversed,array{1,0,2}) );
    }
}