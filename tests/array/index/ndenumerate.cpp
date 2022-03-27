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
    // newer doctest CHECK macro definition breaks the following :(
    #ifdef __clang__
    [[maybe_unused]] auto idx = std::get<0>(pack[3]);
    auto val = std::get<1>(pack[3]);
    #else
    auto [idx, val] = pack[3];
    #endif
    CHECK( val == 3 );

    for (size_t i=0; i<pack.size(); i++) {
        // newer doctest CHECK macro definition breaks the following :(
        #ifdef __clang__
        [[maybe_unused]] auto idx = std::get<0>(pack[i]);
        auto value = std::get<1>(pack[i]);
        #else
        auto [idx, value] = pack[i];
        #endif
        auto v = apply_at(array,indices[i]);
        CHECK( value == v );
    }

    // newer doctest CHECK macro definition breaks the following :(
    #ifndef __clang__
    for (auto [idx,value] : pack) {
        auto v = apply_at(array,idx);
        CHECK( value == v );
    }
    #endif

    {
        const auto& p = pack[2];
        const auto& v = std::get<1>(p);
        array[0][0][2] = 10;
        CHECK( v == 10 );
    }
}