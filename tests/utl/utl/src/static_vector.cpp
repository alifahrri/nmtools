#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("static_vector" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            static_assert( meta::is_ndarray_v<array_t> );
        }
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
        }
    }

    SUBCASE("resize")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            array.resize(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
        {
            using array_t = utl::static_vector<double>;
            auto array = array_t();
            array.resize(12);
            NMTOOLS_ASSERT_EQUAL( array.size(), 12 );
        }
    }

    SUBCASE("assignment")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            array[0] = 1;
            array[1] = 2;
            array[2] = 3;
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
    }

    SUBCASE("copyable")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array  = array_t(3);
            auto copied = array_t(array);
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
        }
    }

    SUBCASE("copy assignment")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array  = array_t(3);
            auto copied = array_t();
            copied = array;
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
    }

    SUBCASE("len")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array  = array_t(3);
            NMTOOLS_ASSERT_EQUAL( nm::len(array), 3 );
        }
    }

    SUBCASE("push_back")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
            array.push_back(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 1 );
            NMTOOLS_ASSERT_EQUAL( array[0], 3 );
        }
    }
}