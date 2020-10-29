/**
 * @file detail.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for array detail
 * @date 2020-10-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "nmtools/array/detail.hpp"
#include "nmtools/utility/helper.hpp"
#include "testing/doctest.hpp"
#include <array>

using nmtools::helper::isclose;

TEST_CASE("compute_strides" * doctest::test_suite("array::detail"))
{
    /**
     * @code{.py}
     * >>> np.ndarray((3,)).shape
     * (8,)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isclose(strides,std::array{1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2)).shape
     * (16,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3,2};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isclose(strides,std::array{2,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,1)).shape
     * (16,8,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3,2,1};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isclose(strides,std::array{2,1,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,3)).shape
     * (48, 24, 8)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3,2,3};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isclose(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_offset" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::array{3,2};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isclose(strides,std::array{2,1}) );
        auto strides = std::array{2,1};
        {
            auto indices = std::array{0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::array{0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::array{1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::array{1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::array{2,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::array{2,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = std::array{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isclose(strides,std::array{6,3,1}) );
        auto strides = std::array{6,3,1};
        {
            auto indices = std::array{0,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::array{0,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::array{0,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::array{0,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::array{0,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::array{0,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::array{1,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::array{1,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::array{1,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::array{1,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::array{1,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::array{1,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::array{2,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::array{2,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::array{2,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::array{2,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::array{2,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::array{2,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}

TEST_CASE("compute_indices" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::array{3,2};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isclose(strides,std::array{2,1}) );
        auto strides = std::array{2,1};
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,0}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,1}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,0}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,1}) );
        }
    }
    {
        auto shape   = std::array{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isclose(strides,std::array{6,3,1}) );
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,0,2}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,1,0}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,1,1}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{0,1,2}) );
        }
        {
            auto offset = 6;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,0,0}) );
        }
        {
            auto offset = 7;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,0,1}) );
        }
        {
            auto offset = 8;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,0,2}) );
        }
        {
            auto offset = 9;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,1,0}) );
        }
        {
            auto offset = 10;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,1,1}) );
        }
        {
            auto offset = 11;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{1,1,2}) );
        }
        {
            auto offset = 12;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,0,0}) );
        }
        {
            auto offset = 13;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,0,1}) );
        }
        {
            auto offset = 14;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,0,2}) );
        }
        {
            auto offset = 15;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,1,0}) );
        }
        {
            auto offset = 16;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,1,1}) );
        }
        {
            auto offset = 17;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_CLOSE( indices, (std::array{2,1,2}) );
        }
    }
}