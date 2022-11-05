#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>
#include <vector>

using nmtools::utils::isequal;
using namespace nmtools::literals;

// TODO: refactor testing data & test cases impl

NMTOOLS_TESTING_DECLARE_CASE(index, compute_offset)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int strides[2] = {2,1};
        inline int indices[3] = {0,0};
        inline auto strides_ct = nmtools_tuple{2_ct,1_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct};
        NMTOOLS_CAST_ARRAYS(strides);
        NMTOOLS_CAST_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 0;
    }
}

TEST_CASE("compute_offset" * doctest::test_suite("index"))
{
    {
        auto strides = nmtools_array{2,1};
        {
            auto indices = nmtools_array{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_array{6,3,1};
        {
            auto indices = nmtools_array{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_array{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_array{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_array{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_array{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_array{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_array{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_array{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_array{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_array{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_array{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_array{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_array{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }

    using namespace nmtools::literals;

    // clipped shape
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_tuple{"6:[6]"_ct,"3:[3]"_ct,"1:[1]"_ct};
        {
            auto indices = nmtools_array{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_array{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_array{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_array{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_array{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_array{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_array{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_array{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_array{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_array{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_array{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_array{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_array{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    // clipped shape
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_array{"6:[6]"_ct,"3:[6]"_ct,"1:[6]"_ct};
        {
            auto indices = nmtools_array{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_array{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_array{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_array{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_array{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_array{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_array{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_array{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_array{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_array{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_array{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_array{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_array{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_array{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_array{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_array{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_array{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_array{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}

#if 0
TEST_CASE("compute_offset(std::vector)" * doctest::test_suite("index"))
{
    {
        auto shape   = std::vector{3,2};
        auto strides = std::vector{2,1};
        {
            auto indices = std::vector{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::vector{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::vector{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::vector{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::vector{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::vector{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = std::vector{6,3,1};
        {
            auto indices = std::vector{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::vector{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::vector{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::vector{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::vector{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::vector{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::vector{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::vector{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::vector{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::vector{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::vector{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::vector{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::vector{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::vector{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::vector{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::vector{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::vector{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::vector{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}
#endif

TEST_CASE("compute_offset(nmtools_tuple)" * doctest::test_suite("index"))
{
    {
        auto strides = nmtools_tuple{2,1};
        {
            auto indices = nmtools_tuple{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_tuple{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_tuple{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_tuple{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_tuple{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_tuple{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = nmtools_tuple{6,3,1};
        {
            auto indices = nmtools_tuple{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_tuple{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_tuple{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_tuple{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_tuple{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_tuple{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_tuple{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_tuple{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_tuple{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_tuple{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_tuple{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_tuple{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_tuple{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_tuple{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_tuple{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_tuple{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_tuple{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_tuple{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    #if 0
    {
        // auto shape   = nmtools_array{3,2,3};
        // CHECK( isequal(strides,nmtools_array{6,3,1}) );
        auto strides = std::vector{6,3,1};
        {
            auto indices = nmtools_tuple{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = nmtools_tuple{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = nmtools_tuple{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = nmtools_tuple{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = nmtools_tuple{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = nmtools_tuple{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = nmtools_tuple{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = nmtools_tuple{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = nmtools_tuple{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = nmtools_tuple{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = nmtools_tuple{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = nmtools_tuple{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = nmtools_tuple{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = nmtools_tuple{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = nmtools_tuple{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = nmtools_tuple{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = nmtools_tuple{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = nmtools_tuple{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    #endif
}