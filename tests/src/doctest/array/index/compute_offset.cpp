#include "nmtools/array/index.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <vector>

using nmtools::utils::isequal;
using namespace nmtools::literals;

TEST_CASE("compute_offset" * doctest::test_suite("index"))
{
    {
        auto strides = std::array{2,1};
        {
            auto indices = std::array{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::array{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::array{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::array{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::array{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::array{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = std::array{3,2,3};
        // CHECK( isequal(strides,std::array{6,3,1}) );
        auto strides = std::array{6,3,1};
        {
            auto indices = std::array{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::array{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::array{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::array{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::array{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::array{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::array{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::array{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::array{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::array{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::array{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::array{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::array{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::array{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::array{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::array{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::array{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::array{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}

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
        // auto shape   = std::array{3,2,3};
        // CHECK( isequal(strides,std::array{6,3,1}) );
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

TEST_CASE("compute_offset(std::tuple)" * doctest::test_suite("index"))
{
    {
        auto strides = std::tuple{2,1};
        {
            auto indices = std::tuple{0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::tuple{0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::tuple{1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::tuple{1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::tuple{2,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::tuple{2,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
    }
    {
        // auto shape   = std::array{3,2,3};
        // CHECK( isequal(strides,std::array{6,3,1}) );
        auto strides = std::tuple{6,3,1};
        {
            auto indices = std::tuple{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::tuple{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::tuple{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::tuple{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::tuple{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::tuple{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::tuple{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::tuple{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::tuple{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::tuple{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::tuple{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::tuple{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::tuple{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::tuple{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::tuple{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::tuple{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::tuple{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::tuple{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
    {
        // auto shape   = std::array{3,2,3};
        // CHECK( isequal(strides,std::array{6,3,1}) );
        auto strides = std::vector{6,3,1};
        {
            auto indices = std::tuple{0,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==0 );
        }
        {
            auto indices = std::tuple{0,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==1 );
        }
        {
            auto indices = std::tuple{0,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==2 );
        }
        {
            auto indices = std::tuple{0,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==3 );
        }
        {
            auto indices = std::tuple{0,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==4 );
        }
        {
            auto indices = std::tuple{0,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==5 );
        }
        {
            auto indices = std::tuple{1,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==6 );
        }
        {
            auto indices = std::tuple{1,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==7 );
        }
        {
            auto indices = std::tuple{1,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==8 );
        }
        {
            auto indices = std::tuple{1,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==9 );
        }
        {
            auto indices = std::tuple{1,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==10 );
        }
        {
            auto indices = std::tuple{1,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==11 );
        }
        {
            auto indices = std::tuple{2,0,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==12 );
        }
        {
            auto indices = std::tuple{2,0,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==13 );
        }
        {
            auto indices = std::tuple{2,0,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==14 );
        }
        {
            auto indices = std::tuple{2,1,0};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==15 );
        }
        {
            auto indices = std::tuple{2,1,1};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==16 );
        }
        {
            auto indices = std::tuple{2,1,2};
            auto offset  = nmtools::index::compute_offset(indices,strides);
            CHECK( offset==17 );
        }
    }
}