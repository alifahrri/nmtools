#include "nmtools/array/eval/simd/index/matmul.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

TEST_CASE("matmul_simd_shape(case1)" * doctest::test_suite("index::matmul_simd_shape"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::matmul_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{3ul,3ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("matmul_simd_inner_size(case1)" * doctest::test_suite("index::matmul_simd_inner_size"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto offset = 5;
    auto size = ix::matmul_simd_inner_size(n_elem_pack,offset,out_shape,lhs_shape,rhs_shape);

    auto expect = 2;
    NMTOOLS_ASSERT_EQUAL( size, expect );
}

TEST_CASE("matmul_simd_inner_size(case2)" * doctest::test_suite("index::matmul_simd_inner_size"))
{
    auto lhs_shape = nmtools_array{3,6};
    auto rhs_shape = nmtools_array{6,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto offset = 5;
    auto size = ix::matmul_simd_inner_size(n_elem_pack,offset,out_shape,lhs_shape,rhs_shape);

    auto expect = 2;
    NMTOOLS_ASSERT_EQUAL( size, expect );
}

TEST_CASE("matmul_simd_inner_size(case3)" * doctest::test_suite("index::matmul_simd_inner_size"))
{
    auto lhs_shape = nmtools_array{3,7};
    auto rhs_shape = nmtools_array{7,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto offset = 5;
    auto size = ix::matmul_simd_inner_size(n_elem_pack,offset,out_shape,lhs_shape,rhs_shape);

    auto expect = 2;
    NMTOOLS_ASSERT_EQUAL( size, expect );
}

TEST_CASE("matmul_simd_inner_size(case4)" * doctest::test_suite("index::matmul_simd_inner_size"))
{
    auto lhs_shape = nmtools_array{3,8};
    auto rhs_shape = nmtools_array{8,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto offset = 5;
    auto size = ix::matmul_simd_inner_size(n_elem_pack,offset,out_shape,lhs_shape,rhs_shape);

    auto expect = 2;
    NMTOOLS_ASSERT_EQUAL( size, expect );
}

TEST_CASE("matmul_simd_inner_size(case5)" * doctest::test_suite("index::matmul_simd_inner_size"))
{
    auto lhs_shape = nmtools_array{3,9};
    auto rhs_shape = nmtools_array{9,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto offset = 5;
    auto size = ix::matmul_simd_inner_size(n_elem_pack,offset,out_shape,lhs_shape,rhs_shape);

    auto expect = 3;
    NMTOOLS_ASSERT_EQUAL( size, expect );
}

TEST_CASE("matmul_simd_inner_size(case6)" * doctest::test_suite("index::matmul_simd_inner_size"))
{
    auto lhs_shape = nmtools_array{2,5};
    auto rhs_shape = nmtools_array{5,2};
    auto out_shape = nmtools_array{2,2};

    auto n_elem_pack = meta::as_type_v<4ul>;
    auto offset = 0;
    auto size = ix::matmul_simd_inner_size(n_elem_pack,offset,out_shape,lhs_shape,rhs_shape);

    auto expect = 2;
    NMTOOLS_ASSERT_EQUAL( size, expect );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("matmul_simd_inner(case1a)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 0;
    auto inner_step = 0;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
    }
}

TEST_CASE("matmul_simd_inner(case1b)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 0;
    auto inner_step = 1;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 4 );
    }
}

TEST_CASE("matmul_simd_inner(case2a)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 1;
    auto inner_step = 0;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 1 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 5 );
    }
}

TEST_CASE("matmul_simd_inner(case2b)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 1;
    auto inner_step = 1;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 1 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 9 );
    }
}

TEST_CASE("matmul_simd_inner(case3a)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 2;
    auto inner_step = 0;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 2 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 10 );
    }
}

TEST_CASE("matmul_simd_inner(case3b)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 2;
    auto inner_step = 1;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 2 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 14 );
    }
}

TEST_CASE("matmul_simd_inner(case4a)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 3;
    auto inner_step = 0;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 3 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 5 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
    }
}

TEST_CASE("matmul_simd_inner(case4b)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 3;
    auto inner_step = 1;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 3 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 9 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 4 );
    }
}

TEST_CASE("matmul_simd_inner(case5a)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 4;
    auto inner_step = 0;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 5 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 5 );
    }
}

TEST_CASE("matmul_simd_inner(case5b)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 4;
    auto inner_step = 1;
    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 9 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 9 );
    }
}

TEST_CASE("matmul_simd_inner(case6a)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{2,5};
    auto rhs_shape = nmtools_array{5,2};
    auto out_shape = nmtools_array{2,2};

    auto n_elem_pack = meta::as_type_v<4ul>;

    auto out_offset = 0;
    auto inner_step = 0;

    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PACKED );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
    }
}

TEST_CASE("matmul_simd_inner(case6b)" * doctest::test_suite("index::matmul_simd_inner"))
{
    auto lhs_shape = nmtools_array{2,5};
    auto rhs_shape = nmtools_array{5,2};
    auto out_shape = nmtools_array{2,2};

    auto n_elem_pack = meta::as_type_v<4ul>;

    auto out_offset = 0;
    auto inner_step = 1;

    auto result = ix::matmul_simd_inner(n_elem_pack,out_offset,inner_step,out_shape,lhs_shape,rhs_shape);

    auto [out_idx,lhs_idx,rhs_idx] = result;
    {
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        CHECK( out_tag == ix::SIMD::SCALAR );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
    }
    {
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        CHECK( lhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
    }
    {
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( rhs_tag == ix::SIMD::PAD_3 );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 4 );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("matmul_simd_inner_enumerator(case1a)" * doctest::test_suite("index::matmul_simd_inner_enumerator"))
{
    auto lhs_shape = nmtools_array{2,5};
    auto rhs_shape = nmtools_array{5,2};
    auto out_shape = nmtools_array{2,2};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto out_offset = 0;

    auto inner_enumerator = ix::matmul_simd_inner_enumerator(n_elem_pack,out_offset,out_shape,lhs_shape,rhs_shape);
    NMTOOLS_ASSERT_EQUAL( inner_enumerator.size(), 2 );
    
    using nmtools::index::SIMD;
    auto i = 0ul;
    auto out_tags = nmtools_array<SIMD,2>{SIMD::SCALAR,SIMD::SCALAR};
    auto lhs_tags = nmtools_array<SIMD,2>{SIMD::PACKED,SIMD::PAD_3};
    auto rhs_tags = nmtools_array<SIMD,2>{SIMD::PACKED,SIMD::PAD_3};
    auto out_ptr_idxs = nmtools_array{0,0};
    auto lhs_ptr_idxs = nmtools_array{0,4};
    auto rhs_ptr_idxs = nmtools_array{0,4};
    for (auto simd_index : inner_enumerator) {
        auto [out_idx,lhs_idx,rhs_idx] = simd_index;
        auto out_tag = nm::get<0>(out_idx); auto out_ptr_idx = nm::get<1>(out_idx);
        auto lhs_tag = nm::get<0>(lhs_idx); auto lhs_ptr_idx = nm::get<1>(lhs_idx);
        auto rhs_tag = nm::get<0>(rhs_idx); auto rhs_ptr_idx = nm::get<1>(rhs_idx);
        CHECK( out_tag == out_tags[i] );
        CHECK( lhs_tag == lhs_tags[i] );
        CHECK( rhs_tag == rhs_tags[i] );
        NMTOOLS_ASSERT_EQUAL( out_ptr_idx, out_ptr_idxs[i] );
        NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, lhs_ptr_idxs[i] );
        NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, rhs_ptr_idxs[i] );
        i++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("matmul_simd_enumerator(case1)" * doctest::test_suite("index::matmul_simd_enumerator"))
{
    auto lhs_shape = nmtools_array{3,5};
    auto rhs_shape = nmtools_array{5,3};
    auto out_shape = nmtools_array{3,3};

    auto n_elem_pack = meta::as_type<4ul>{};

    auto enumerator = ix::matmul_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    NMTOOLS_ASSERT_EQUAL( enumerator.size(), 9 );

    auto i = 0ul;
    for ([[maybe_unused]] const auto [out_tag,out_ptr_idx,inner_enumerator] : enumerator) {
        i++;
    }
}