// TODO: support dynamic size array for at
#define NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY
// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

TEST_CASE("at" * doctest::test_suite("utility"))
{
    namespace nm = nmtools;

    {
        auto array  = nmtools_array{1,2,3,4};
        auto result = nm::at<2>(array);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    #if 0
    {
        auto array  = nmtools_tuple{1,2,3,4};
        auto result = nm::at<2>(array);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    #endif
    {
        auto array  = nmtools_list{1,2,3,4};
        auto result = nm::at<2>(array);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = nmtools_array{1,2,3,4};
        nm::at<2>(array) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }
    #if 0
    {
        auto array  = nmtools_tuple{1,2,3,4};
        nm::at<2>(array) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }
    #endif
    {
        auto array  = nmtools_list{1,2,3,4};
        nm::at<2>(array) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }
    {
        auto array = nmtools_array{1,2,3,4};
        nm::at(array,nm::Last) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,3,5}));
    }
    {
        auto array = nmtools_list{1,2,3,4};
        nm::at(array,nm::Last) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_list{1,2,3,5}));
    }
    {
        auto array  = nmtools_array{1,2,3,4};
        auto index  = -1;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,3,5}) );
    }
    {
        auto array  = nmtools_list{1,2,3,4};
        auto index  = -1;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,3,5}) );
    }
    {
        auto array  = nmtools_array{1,2,3,4};
        auto index  = -2;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }
    {
        auto array  = nmtools_list{1,2,3,4};
        auto index  = -2;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }

    using namespace nm::literals;
    {
        auto array  = nmtools_array{1,2,3,4};
        auto index  = 2_ct;
        auto result = nm::at(array, index);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = nmtools_tuple{1,2,3,4};
        auto index  = 2_ct;
        auto result = nm::at(array, index);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = nmtools_list{1,2,3,4};
        auto index  = 2_ct;
        auto result = nm::at(array, index);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = nmtools_array{1,2,3,4};
        auto index  = 2_ct;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }
    #if 0
    {
        auto array  = nmtools_tuple{1,2,3,4};
        auto index  = 2_ct;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }
    #endif
    {
        auto array  = nmtools_list{1,2,3,4};
        auto index  = 2_ct;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (nmtools_array{1,2,5,4}) );
    }
}