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
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <vector>

using nmtools::utils::isequal;
using namespace nmtools::literals;

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
        CHECK( isequal(strides,std::array{1}) );
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
        CHECK( isequal(strides,std::array{2,1}) );
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
        CHECK( isequal(strides,std::array{2,1,1}) );
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
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_strides(std::vector)" * doctest::test_suite("array::detail"))
{
    /**
     * @code{.py}
     * >>> np.ndarray((3,)).shape
     * (8,)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2)).shape
     * (16,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3,2};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,1)).shape
     * (16,8,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3,2,1};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,3)).shape
     * (48, 24, 8)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3,2,3};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_strides(std::tuple)" * doctest::test_suite("array::detail"))
{
    /**
     * @code{.py}
     * >>> np.ndarray((3,)).shape
     * (8,)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2)).shape
     * (16,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3,2};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,1)).shape
     * (16,8,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3,2,1};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,3)).shape
     * (48, 24, 8)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3,2,3};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_strides(std::tuple<integral_constant>)" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::tuple{3_ct};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{1}) );
    }
    {
        auto shape   = std::tuple{3_ct,2_ct};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1}) );
    }
    {
        auto shape   = std::tuple{3_ct,2_ct,1_ct};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1,1}) );
    }
    {
        auto shape   = std::tuple{3_ct,2_ct,3_ct};
        auto strides = nmtools::array::detail::compute_strides(shape);
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_offset" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::array{3,2};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{2,1}) );
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
        // CHECK( isequal(strides,std::array{6,3,1}) );
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

TEST_CASE("compute_offset(std::vector)" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::vector{3,2};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{2,1}) );
        auto strides = std::vector{2,1};
        {
            auto indices = std::vector{0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::vector{0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::vector{1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::vector{1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::vector{2,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::vector{2,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = std::array{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{6,3,1}) );
        auto strides = std::vector{6,3,1};
        {
            auto indices = std::vector{0,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::vector{0,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::vector{0,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::vector{0,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::vector{0,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::vector{0,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::vector{1,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::vector{1,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::vector{1,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::vector{1,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::vector{1,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::vector{1,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::vector{2,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::vector{2,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::vector{2,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::vector{2,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::vector{2,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::vector{2,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}

TEST_CASE("compute_offset(std::tuple)" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::tuple{3,2};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{2,1}) );
        auto strides = std::tuple{2,1};
        {
            auto indices = std::tuple{0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::tuple{0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::tuple{1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::tuple{1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::tuple{2,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::tuple{2,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = std::array{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{6,3,1}) );
        auto strides = std::tuple{6,3,1};
        {
            auto indices = std::tuple{0,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::tuple{0,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::tuple{0,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::tuple{0,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::tuple{0,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::tuple{0,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::tuple{1,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::tuple{1,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::tuple{1,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::tuple{1,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::tuple{1,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::tuple{1,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::tuple{2,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::tuple{2,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::tuple{2,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::tuple{2,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::tuple{2,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::tuple{2,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    {
        // auto shape   = std::array{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{6,3,1}) );
        auto strides = std::vector{6,3,1};
        {
            auto indices = std::tuple{0,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::tuple{0,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::tuple{0,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::tuple{0,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::tuple{0,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::tuple{0,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::tuple{1,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::tuple{1,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::tuple{1,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::tuple{1,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::tuple{1,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::tuple{1,1,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::tuple{2,0,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::tuple{2,0,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::tuple{2,0,2};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::tuple{2,1,0};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::tuple{2,1,1};
            auto offset  = nmtools::array::detail::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::tuple{2,1,2};
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
        // CHECK( isequal(strides,std::array{2,1}) );
        auto strides = std::array{2,1};
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1}) );
        }
    }
    {
        auto shape   = std::array{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{6,3,1}) );
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,2}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,0}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,1}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,2}) );
        }
        {
            auto offset = 6;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,0}) );
        }
        {
            auto offset = 7;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,1}) );
        }
        {
            auto offset = 8;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,2}) );
        }
        {
            auto offset = 9;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,0}) );
        }
        {
            auto offset = 10;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,1}) );
        }
        {
            auto offset = 11;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,2}) );
        }
        {
            auto offset = 12;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,0}) );
        }
        {
            auto offset = 13;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,1}) );
        }
        {
            auto offset = 14;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,2}) );
        }
        {
            auto offset = 15;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,0}) );
        }
        {
            auto offset = 16;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,1}) );
        }
        {
            auto offset = 17;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,2}) );
        }
    }
}

TEST_CASE("compute_indices(std::vector)" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::vector{3,2};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{2,1}) );
        auto strides = std::vector{2,1};
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1}) );
        }
    }
    {
        auto shape   = std::vector{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{6,3,1}) );
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,2}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,0}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,1}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,2}) );
        }
        {
            auto offset = 6;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,0}) );
        }
        {
            auto offset = 7;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,1}) );
        }
        {
            auto offset = 8;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,2}) );
        }
        {
            auto offset = 9;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,0}) );
        }
        {
            auto offset = 10;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,1}) );
        }
        {
            auto offset = 11;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,2}) );
        }
        {
            auto offset = 12;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,0}) );
        }
        {
            auto offset = 13;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,1}) );
        }
        {
            auto offset = 14;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,2}) );
        }
        {
            auto offset = 15;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,0}) );
        }
        {
            auto offset = 16;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,1}) );
        }
        {
            auto offset = 17;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,2}) );
        }
    }
}

TEST_CASE("compute_indices(std::tuple)" * doctest::test_suite("array::detail"))
{
    {
        auto shape   = std::tuple{3,2};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{2,1}) );
        auto strides = std::tuple{2,1};
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1}) );
        }
    }
    {
        auto shape   = std::tuple{3,2,3};
        // auto strides = nmtools::array::detail::compute_strides(shape);
        // CHECK( isequal(strides,std::array{6,3,1}) );
        {
            auto offset = 0;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,0}) );
        }
        {
            auto offset = 1;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,1}) );
        }
        {
            auto offset = 2;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,0,2}) );
        }
        {
            auto offset = 3;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,0}) );
        }
        {
            auto offset = 4;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,1}) );
        }
        {
            auto offset = 5;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{0,1,2}) );
        }
        {
            auto offset = 6;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,0}) );
        }
        {
            auto offset = 7;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,1}) );
        }
        {
            auto offset = 8;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,0,2}) );
        }
        {
            auto offset = 9;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,0}) );
        }
        {
            auto offset = 10;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,1}) );
        }
        {
            auto offset = 11;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{1,1,2}) );
        }
        {
            auto offset = 12;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,0}) );
        }
        {
            auto offset = 13;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,1}) );
        }
        {
            auto offset = 14;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,0,2}) );
        }
        {
            auto offset = 15;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,0}) );
        }
        {
            auto offset = 16;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,1}) );
        }
        {
            auto offset = 17;
            auto indices = nmtools::array::detail::compute_indices(offset,shape);
            NMTOOLS_ASSERT_EQUAL( indices, (std::array{2,1,2}) );
        }
    }
}