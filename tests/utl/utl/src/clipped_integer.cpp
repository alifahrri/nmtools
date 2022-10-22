#include "nmtools/meta.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace utl = nm::utl;

using namespace nm::literals;

TEST_CASE("array(case1)" * doctest::test_suite("clipped_integer"))
{
    {
        using value_t = nm::clipped_size_t<3>;
        using array_t = utl::array<value_t,3>;

        auto array = array_t{1,2,3};
        NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( array[0], 1 );
        NMTOOLS_ASSERT_EQUAL( array[1], 2 );
        NMTOOLS_ASSERT_EQUAL( array[2], 3 );
    }
    {
        auto array = utl::array{"0:[3]"_ct,"1:[3]"_ct,"2:[3]"_ct};
        NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( array[0], 0 );
        NMTOOLS_ASSERT_EQUAL( array[1], 1 );
        NMTOOLS_ASSERT_EQUAL( array[2], 2 );
    }
    {
        using value_t = nm::clipped_size_t<3>;
        using array_t = utl::array<value_t,3>;

        auto array = array_t{};
        for (size_t i=0; i<array.size(); i++) {
            array[i] = i;
        }
        NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( array[0], 0 );
        NMTOOLS_ASSERT_EQUAL( array[1], 1 );
        NMTOOLS_ASSERT_EQUAL( array[2], 2 );
    }
}