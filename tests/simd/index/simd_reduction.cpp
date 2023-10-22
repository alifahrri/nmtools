#include "nmtools/array/eval/simd/index.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

using ix::ReductionKind;
using ix::SIMD;

TEST_CASE("reduction_2d_shape(case1a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{1,4};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{3,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("reduction_2d_shape(case1b)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{1,4};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{3,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("reduction_2d_shape(case1a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{4};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{3,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("reduction_2d_shape(case1d)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{4};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{3,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("reduction_2d_shape(case2a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{4,4};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("reduction_2d_shape(case2b)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{4,3};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("reduction_2d_shape(case2c)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{10};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{4,4};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("reduction_2d_shape(case2d)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{10};

    auto result = ix::reduction_2d_shape(reduction_kind,n_elem_pack,inp_shape,out_shape); 
    auto expect = nmtools_array{4,3};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

////////////////////////////////////////////////////////////////////////////////

// VERTICAL REDUCTION
/**
>>> a
array([[ 0,  1,  2,  3],
       [ 4,  5,  6,  7],
       [ 8,  9, 10, 11]])
>>> np.add.reduce(a,axis=0,keepdims=True)
array([[12, 15, 18, 21]])
>>> np.add.reduce(a,axis=0,keepdims=True).shape
(1, 4)
*/

TEST_CASE("reduction_2d(case1a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{1,4};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{0,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 0 );
    }
}

TEST_CASE("reduction_2d(case1b)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{1,4};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{1,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 4 );
    }
}

TEST_CASE("reduction_2d(case1c)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{1,4};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{2,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 8 );
    }
}

TEST_CASE("reduction_2d(case1d)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{4};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{0,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 0 );
    }
}

TEST_CASE("reduction_2d(case1e)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{4};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{1,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 4 );
    }
}

TEST_CASE("reduction_2d(case1f)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{4};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{2,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 8 );
    }
}

// HORIZONTAL REDUCTION
/**
>>> a
array([[ 0,  1,  2,  3],
       [ 4,  5,  6,  7],
       [ 8,  9, 10, 11]])
>>> np.add.reduce(a,axis=1,keepdims=True)
array([[ 6],
       [22],
       [38]])
>>> np.add.reduce(a,axis=1,keepdims=True).shape
(3, 1)
*/

TEST_CASE("reduction_2d(case2a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{3,1};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{0,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 0 );
    }
}

TEST_CASE("reduction_2d(case2b)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{3,1};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{1,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 1 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 4 );
    }
}

TEST_CASE("reduction_2d(case2c)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{3,1};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{2,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 2 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 8 );
    }
}

TEST_CASE("reduction_2d(case2d)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{3};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{0,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 0 );
    }
}

TEST_CASE("reduction_2d(case2e)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{3};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{1,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 1 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 4 );
    }
}

TEST_CASE("reduction_2d(case2f)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{3};
    auto simd_shape  = nmtools_array{3,1};

    auto simd_index = nmtools_array{2,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 2 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 8 );
    }
}

TEST_CASE("reduction_2d(case3a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{0,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 0 );
    }
}

TEST_CASE("reduction_2d(case3b)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{1,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 10 );
    }
}

TEST_CASE("reduction_2d(case3c)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{2,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 20 );
    }
}

TEST_CASE("reduction_2d(case3d)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{3,0};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 30 );
    }
}

TEST_CASE("reduction_2d(case3e)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{0,1};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 4 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 4 );
    }
}

TEST_CASE("reduction_2d(case3f)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{0,2};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 8 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 8 );
    }
}

TEST_CASE("reduction_2d(case3g)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{0,3};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 9 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 9 );
    }
}

TEST_CASE("reduction_2d(case3h)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{1,1};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 4 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 14 );
    }
}

TEST_CASE("reduction_2d(case3i)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{2,1};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
        NMTOOLS_ASSERT_EQUAL( out_offset, 4 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 24 );
    }
}

TEST_CASE("reduction_2d(case3j)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto simd_index = nmtools_array{2,2};

    auto result = ix::reduction_2d(reduction_kind,n_elem_pack,simd_index,simd_shape,out_shape,inp_shape);
    auto [out_index,inp_index] = result;
    {
        const auto out_tag = nmtools::get<0>(out_index);
        const auto out_offset = nmtools::get<1>(out_index);
        CHECK( out_tag == SIMD::ACCUMULATE );
        NMTOOLS_ASSERT_EQUAL( out_offset, 8 );
    }
    {
        const auto inp_tag = nmtools::get<0>(inp_index);
        const auto inp_offset = nmtools::get<1>(inp_index);
        CHECK( inp_tag == SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( inp_offset, 28 );
    }
}

/////////////////////////////////////////////////////////////////////////

TEST_CASE("reduction_2d_enumerator(case1)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{1,4};
    auto simd_shape  = nmtools_array{3,1};

    auto enumerator = ix::reduction_2d_enumerator(reduction_kind,n_elem_pack,out_shape,inp_shape);
    {
        NMTOOLS_ASSERT_EQUAL( enumerator.size(), 3 );
    }
    {
        auto [out_index,inp_index] = enumerator[0];
        {
            const auto out_tag = nmtools::get<0>(out_index);
            const auto out_offset = nmtools::get<1>(out_index);
            CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
            NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
        }
        {
            const auto inp_tag = nmtools::get<0>(inp_index);
            const auto inp_offset = nmtools::get<1>(inp_index);
            CHECK( inp_tag == SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( inp_offset, 0 );
        }
    }
    {
        auto [out_index,inp_index] = enumerator[1];
        {
            const auto out_tag = nmtools::get<0>(out_index);
            const auto out_offset = nmtools::get<1>(out_index);
            CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
            NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
        }
        {
            const auto inp_tag = nmtools::get<0>(inp_index);
            const auto inp_offset = nmtools::get<1>(inp_index);
            CHECK( inp_tag == SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( inp_offset, 4 );
        }
    }
    {
        auto [out_index,inp_index] = enumerator[2];
        {
            const auto out_tag = nmtools::get<0>(out_index);
            const auto out_offset = nmtools::get<1>(out_index);
            CHECK( out_tag == SIMD::ACCUMULATE_PACKED );
            NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
        }
        {
            const auto inp_tag = nmtools::get<0>(inp_index);
            const auto inp_offset = nmtools::get<1>(inp_index);
            CHECK( inp_tag == SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( inp_offset, 8 );
        }
    }
}

TEST_CASE("reduction_2d_enumerator(case2)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{3,4};
    auto out_shape   = nmtools_array{1,4};
    auto simd_shape  = nmtools_array{3,1};

    auto enumerator = ix::reduction_2d_enumerator(reduction_kind,n_elem_pack,out_shape,inp_shape);
    auto inp_tags = nmtools_array{SIMD::PACKED,SIMD::PACKED,SIMD::PACKED};
    auto out_tags = nmtools_array{SIMD::ACCUMULATE,SIMD::ACCUMULATE,SIMD::ACCUMULATE};
    auto inp_offsets = nmtools_array{0,4,8};
    auto out_offsets = nmtools_array{0,1,2};

    for (size_t i=0; i<enumerator.size(); i++) {
        auto [out_pack, inp_pack] = enumerator[i];
        auto [out_tag,out_offset] = out_pack;
        auto [inp_tag,inp_offset] = inp_pack;
        CHECK( out_tag == out_tags[i] );
        CHECK( inp_tag == inp_tags[i] );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( inp_offset, inp_offsets[i] );
    }
}

TEST_CASE("reduction_2d_enumerator(case3a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{1,10};
    auto simd_shape  = nmtools_array{4,4};

    auto enumerator = ix::reduction_2d_enumerator(reduction_kind,n_elem_pack,out_shape,inp_shape);
    auto out_tags = nmtools_array{
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
    };
    auto inp_tags = nmtools_array{
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
    };
    auto inp_offsets = nmtools_array{0,4,8,9,10,14,18,19,20,24,28,29,30,34,38,39};
    auto out_offsets = nmtools_array{0,4,8,9,0,4,8,9,0,4,8,9,0,4,8,9};

    for (size_t i=0; i<enumerator.size(); i++) {
        auto [out_pack, inp_pack] = enumerator[i];
        auto [out_tag,out_offset] = out_pack;
        auto [inp_tag,inp_offset] = inp_pack;
        CHECK( out_tag == out_tags[i] );
        CHECK( inp_tag == inp_tags[i] );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( inp_offset, inp_offsets[i] );
    }
}

TEST_CASE("reduction_2d_enumerator(case3b)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::VERTICAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{10};
    auto simd_shape  = nmtools_array{4,4};

    auto enumerator = ix::reduction_2d_enumerator(reduction_kind,n_elem_pack,out_shape,inp_shape);
    auto out_tags = nmtools_array{
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE_PACKED,
        SIMD::ACCUMULATE,
        SIMD::ACCUMULATE,
    };
    auto inp_tags = nmtools_array{
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::SCALAR,
        SIMD::SCALAR,
    };
    auto inp_offsets = nmtools_array{0,4,8,9,10,14,18,19,20,24,28,29,30,34,38,39};
    auto out_offsets = nmtools_array{0,4,8,9,0,4,8,9,0,4,8,9,0,4,8,9};

    for (size_t i=0; i<enumerator.size(); i++) {
        auto [out_pack, inp_pack] = enumerator[i];
        auto [out_tag,out_offset] = out_pack;
        auto [inp_tag,inp_offset] = inp_pack;
        CHECK( out_tag == out_tags[i] );
        CHECK( inp_tag == inp_tags[i] );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( inp_offset, inp_offsets[i] );
    }
}

TEST_CASE("reduction_2d_enumerator(case4a)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{4,1};
    auto simd_shape  = nmtools_array{4,4};

    auto enumerator = ix::reduction_2d_enumerator(reduction_kind,n_elem_pack,out_shape,inp_shape);
    auto out_tags = nmtools_array{
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
    };
    auto inp_tags = nmtools_array{
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
    };
    auto inp_offsets = nmtools_array{0,4,8,10,14,18,20,24,28,30,34,38};
    auto out_offsets = nmtools_array{0,0,0,1,1,1,2,2,2,3,3,3};


    NMTOOLS_ASSERT_EQUAL( enumerator.size(), inp_offsets.size() );
    for (size_t i=0; i<enumerator.size(); i++) {
        auto [out_pack, inp_pack] = enumerator[i];
        auto [out_tag,out_offset] = out_pack;
        auto [inp_tag,inp_offset] = inp_pack;
        CHECK_MESSAGE( out_tag == out_tags[i], i );
        CHECK_MESSAGE( inp_tag == inp_tags[i], i );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( inp_offset, inp_offsets[i] );
    }
}

TEST_CASE("reduction_2d_enumerator(case4b)" * doctest::test_suite("simd::index"))
{
    auto reduction_kind = meta::as_type_v<ReductionKind::HORIZONTAL>;
    auto n_elem_pack = meta::as_type_v<4>;
    auto inp_shape   = nmtools_array{4,10};
    auto out_shape   = nmtools_array{4};
    auto simd_shape  = nmtools_array{4,4};

    auto enumerator = ix::reduction_2d_enumerator(reduction_kind,n_elem_pack,out_shape,inp_shape);
    auto out_tags = nmtools_array{
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
        SIMD::NOP,
        SIMD::NOP,
        SIMD::ACCUMULATE,
    };
    auto inp_tags = nmtools_array{
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
        SIMD::PACKED,
        SIMD::PACKED,
        SIMD::PAD_2,
    };
    auto inp_offsets = nmtools_array{0,4,8,10,14,18,20,24,28,30,34,38};
    auto out_offsets = nmtools_array{0,0,0,1,1,1,2,2,2,3,3,3};


    NMTOOLS_ASSERT_EQUAL( enumerator.size(), inp_offsets.size() );
    for (size_t i=0; i<enumerator.size(); i++) {
        auto [out_pack, inp_pack] = enumerator[i];
        auto [out_tag,out_offset] = out_pack;
        auto [inp_tag,inp_offset] = inp_pack;
        CHECK_MESSAGE( out_tag == out_tags[i], i );
        CHECK_MESSAGE( inp_tag == inp_tags[i], i );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( inp_offset, inp_offsets[i] );
    }
}