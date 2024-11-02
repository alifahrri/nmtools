#include "nmtools/utility/data.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("data(case1)" * doctest::test_suite("utility"))
{
    constexpr auto dim   = 3;
    constexpr auto numel = 12;

    using data_t  = float;
    using index_t = size_t;

    using data_buffer_t  = nmtools_array<data_t,numel>;
    using shape_buffer_t = nmtools_array<index_t,dim>;

    using ndarray = na::ndarray_t<data_buffer_t,shape_buffer_t>;

    auto array = ndarray{};
    data_t* data = nm::data(array);
    NMTOOLS_REQUIRE_EQUAL( array.dim(), 3 );
    NMTOOLS_REQUIRE_EQUAL( array.shape(), (nmtools_array{1,1,12}) );
    NMTOOLS_REQUIRE_EQUAL( array.size(), 12 );

    for (size_t i=0; i<12; i++) {
        data[i] = i;
    }

    const data_t* const_data = nm::data(array);
    for (size_t i=0; i<12; i++) {
        NMTOOLS_ASSERT_CLOSE( const_data[i], i );
    }
}