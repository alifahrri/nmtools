#include "nmtools/array/index.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <vector>

using nmtools::utils::isequal;
using namespace nmtools::literals;

TEST_CASE("compute_indices" * doctest::test_suite("index"))
{
    {
        auto shape   = std::array{3,2};
        auto strides = std::array{2,1};
        {
            auto offset = 0;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1}) );
        }
    }
    {
        auto shape   = std::array{3,2,3};
        // CHECK( isequal(strides,std::array{6,3,1}) );
        {
            auto offset = 0;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,2}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,0}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,1}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,2}) );
        }
        {
            auto offset = 6;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,0}) );
        }
        {
            auto offset = 7;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,1}) );
        }
        {
            auto offset = 8;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,2}) );
        }
        {
            auto offset = 9;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,0}) );
        }
        {
            auto offset = 10;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,1}) );
        }
        {
            auto offset = 11;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,2}) );
        }
        {
            auto offset = 12;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,0}) );
        }
        {
            auto offset = 13;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,1}) );
        }
        {
            auto offset = 14;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,2}) );
        }
        {
            auto offset = 15;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,0}) );
        }
        {
            auto offset = 16;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,1}) );
        }
        {
            auto offset = 17;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,2}) );
        }
    }
}

TEST_CASE("compute_indices(std::vector)" * doctest::test_suite("index"))
{
    {
        auto shape   = std::vector{3,2};
        auto strides = std::vector{2,1};
        {
            auto offset = 0;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1}) );
        }
    }
    {
        auto shape   = std::vector{3,2,3};
        // CHECK( isequal(strides,std::array{6,3,1}) );
        {
            auto offset = 0;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,2}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,0}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,1}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,2}) );
        }
        {
            auto offset = 6;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,0}) );
        }
        {
            auto offset = 7;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,1}) );
        }
        {
            auto offset = 8;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,2}) );
        }
        {
            auto offset = 9;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,0}) );
        }
        {
            auto offset = 10;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,1}) );
        }
        {
            auto offset = 11;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,2}) );
        }
        {
            auto offset = 12;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,0}) );
        }
        {
            auto offset = 13;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,1}) );
        }
        {
            auto offset = 14;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,2}) );
        }
        {
            auto offset = 15;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,0}) );
        }
        {
            auto offset = 16;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,1}) );
        }
        {
            auto offset = 17;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,2}) );
        }
    }
}

TEST_CASE("compute_indices(std::tuple)" * doctest::test_suite("index"))
{
    {
        auto shape   = std::tuple{3,2};
        auto strides = std::tuple{2,1};
        {
            auto offset = 0;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1}) );
        }
    }
    {
        auto shape   = std::tuple{3,2,3};
        // CHECK( isequal(strides,std::array{6,3,1}) );
        {
            auto offset = 0;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,2}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,0}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,1}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,2}) );
        }
        {
            auto offset = 6;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,0}) );
        }
        {
            auto offset = 7;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,1}) );
        }
        {
            auto offset = 8;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,2}) );
        }
        {
            auto offset = 9;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,0}) );
        }
        {
            auto offset = 10;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,1}) );
        }
        {
            auto offset = 11;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,2}) );
        }
        {
            auto offset = 12;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,0}) );
        }
        {
            auto offset = 13;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,1}) );
        }
        {
            auto offset = 14;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,2}) );
        }
        {
            auto offset = 15;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,0}) );
        }
        {
            auto offset = 16;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,1}) );
        }
        {
            auto offset = 17;
            auto indices = nmtools::index::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,2}) );
        }
    }
}