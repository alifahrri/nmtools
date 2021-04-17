#include "nmtools/array/index/ndenumerate.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;

TEST_CASE("ndenumerate" * doctest::test_suite("index"))
{
    using nm::index::ndenumerate;
    using nm::index::ndindex;
    using nm::apply_at;

    int array[1][2][3] = {
        {
            {0,1,2},
            {3,4,5},
        }
    };
    auto shape_ = nm::shape(array);
    // NOTE: this is use-after-scope error
    // since ndindex takes reference to shape now to support raw array
    // TODO: detect if temporary, and use copy instead of ref
    // auto indices = ndindex(nm::shape(array));
    auto indices = ndindex(shape_);
    auto pack = ndenumerate(array);
    CHECK( pack.size() == 6 );
    auto [idx, val] = pack[3];
    CHECK( val == 3 );

    for (size_t i=0; i<pack.size(); i++) {
        auto [idx, value] = pack[i];
        auto v = apply_at(array,indices[i]);
        CHECK( value == v );
    }

    for (auto [idx,value] : pack) {
        auto v = apply_at(array,idx);
        CHECK( value == v );
    }

    {
        const auto& p = pack[2];
        const auto& v = std::get<1>(p);
        array[0][0][2] = 10;
        CHECK( v == 10 );
    }
}