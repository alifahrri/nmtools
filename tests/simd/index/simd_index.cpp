#include "nmtools/array/eval/simd/index.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

TEST_CASE("binary_2d_simd_shape(case1)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{1ul,8ul};
    auto rhs_shape = nmtools_array{2ul,1ul};
    auto out_shape = nmtools_array{2ul,8ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{2ul,2ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case2)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{1ul,8ul};
    auto rhs_shape = nmtools_array{4ul,1ul};
    auto out_shape = nmtools_array{4ul,8ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{4ul,2ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case3)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{1ul,10ul};
    auto rhs_shape = nmtools_array{2ul,1ul};
    auto out_shape = nmtools_array{2ul,10ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{2ul,4ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case4)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{1ul,3ul};
    auto rhs_shape = nmtools_array{4ul,1ul};
    auto out_shape = nmtools_array{4ul,3ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{4ul,3ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case5)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{1ul,3ul};
    auto rhs_shape = nmtools_array{4ul,1ul};
    auto out_shape = nmtools_array{4ul,3ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{4ul,3ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case6)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{2ul,5ul};
    auto rhs_shape = nmtools_array{2ul,5ul};
    auto out_shape = nmtools_array{2ul,5ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{2ul,2ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case7)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{2ul,5ul};
    auto rhs_shape = nmtools_array{1ul,5ul};
    auto out_shape = nmtools_array{2ul,5ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{2ul,2ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case8)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{1ul,5ul};
    auto rhs_shape = nmtools_array{2ul,5ul};
    auto out_shape = nmtools_array{2ul,5ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{2ul,2ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case9)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{1ul,5ul};
    auto rhs_shape = nmtools_array{5ul,1ul};
    auto out_shape = nmtools_array{5ul,5ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{5ul,2ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd_shape(case10)" * doctest::test_suite("index::binary_2d_simd_shape"))
{
    auto lhs_shape = nmtools_array{5ul,1ul};
    auto rhs_shape = nmtools_array{1ul,5ul};
    auto out_shape = nmtools_array{5ul,5ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    auto shape = ix::binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);

    auto expect = nmtools_array{5ul,2ul};
    NMTOOLS_ASSERT_EQUAL( shape, expect );
}

TEST_CASE("binary_2d_simd(case1)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{1ul,8ul};
    auto rhs_shape  = nmtools_array{2ul,1ul};
    auto out_shape  = nmtools_array{2ul,8ul};
    auto simd_shape = nmtools_array{2ul,2ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 8 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 12 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }
}

TEST_CASE("binary_2d_simd(case2)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{1ul,8ul};
    auto rhs_shape  = nmtools_array{4ul,1ul};
    auto out_shape  = nmtools_array{4ul,8ul};
    auto simd_shape = nmtools_array{4ul,2ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 8 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 12 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{2ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 16 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 2 );
        }
    }

    {
        auto simd_indices = nmtools_array{2ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 20 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 2 );
        }
    }

    {
        auto simd_indices = nmtools_array{3ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 24 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 3 );
        }
    }

    {
        auto simd_indices = nmtools_array{3ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 28 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 3 );
        }
    }
}

TEST_CASE("binary_2d_simd(case3)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{1ul,10ul};
    auto rhs_shape  = nmtools_array{2ul,1ul};
    auto out_shape  = nmtools_array{2ul,10ul};
    auto simd_shape = nmtools_array{2ul,4ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,2ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 8 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 8 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,3ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 9 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 9 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 10 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 14 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,2ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 18 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 8 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,3ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 19 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 9 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }
}

TEST_CASE("binary_2d_simd(case4)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{1ul,3ul};
    auto rhs_shape  = nmtools_array{4ul,1ul};
    auto out_shape  = nmtools_array{4ul,3ul};
    auto simd_shape = nmtools_array{4ul,3ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 1 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 1 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,2ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 2 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 2 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 3 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 1 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,2ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 5 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 2 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }
}

TEST_CASE("binary_2d_simd(case5)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{2ul,5ul};
    auto rhs_shape  = nmtools_array{2ul,1ul};
    auto out_shape  = nmtools_array{2ul,5ul};
    auto simd_shape = nmtools_array{2ul,2ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 5 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 5 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 9 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 9 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }
}

TEST_CASE("binary_2d_simd(case6)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{2ul,9ul};
    auto rhs_shape  = nmtools_array{2ul,1ul};
    auto out_shape  = nmtools_array{2ul,9ul};
    auto simd_shape = nmtools_array{2ul,3ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,2ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 8 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 8 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 9 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 9 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 13 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 13 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,2ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 17 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 17 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }
}

TEST_CASE("binary_2d_simd(case6)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{2ul,5ul};
    auto rhs_shape  = nmtools_array{1ul,5ul};
    auto out_shape  = nmtools_array{2ul,5ul};
    auto simd_shape = nmtools_array{2ul,2ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 4 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 5 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 5 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 9 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 9 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 4 );
        }
    }
}

TEST_CASE("binary_2d_simd(case6)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{1ul,5ul};
    auto rhs_shape  = nmtools_array{2ul,5ul};
    auto out_shape  = nmtools_array{2ul,5ul};
    auto simd_shape = nmtools_array{2ul,2ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 4 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 5 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 5 );
        }
    }

    {
        auto simd_indices = nmtools_array{1ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 9 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 9 );
        }
    }
}

TEST_CASE("binary_2d_simd(case7)" * doctest::test_suite("index::binary_2d_simd"))
{
    auto lhs_shape  = nmtools_array{5ul,1ul};
    auto rhs_shape  = nmtools_array{1ul,5ul};
    auto out_shape  = nmtools_array{5ul,5ul};
    auto simd_shape = nmtools_array{5ul,2ul};

    auto n_elem_pack = meta::as_type<4ul>{};
    {
        auto simd_indices = nmtools_array{0ul,0ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto simd_indices = nmtools_array{0ul,1ul};
        auto result = ix::binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        auto [out_idx,lhs_idx,rhs_idx] = result;
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::SCALAR );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 4 );
        }
    }
}

TEST_CASE("binary_2d_simd_enumerator(case1)" * doctest::test_suite("index::binary_2d_simd_enumerator"))
{
    auto lhs_shape   = nmtools_array{1ul,8ul};
    auto rhs_shape   = nmtools_array{2ul,1ul};
    auto out_shape   = nmtools_array{2ul,8ul};
    auto n_elem_pack = meta::as_type<4ul>{};

    auto enumerator = ix::binary_2d_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    NMTOOLS_ASSERT_EQUAL( enumerator.size(), 4 );

    {
        auto [out_idx,lhs_idx,rhs_idx] = enumerator[0];
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 0 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto [out_idx,lhs_idx,rhs_idx] = enumerator[1];
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 4 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 0 );
        }
    }

    {
        auto [out_idx,lhs_idx,rhs_idx] = enumerator[2];
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 8 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 0 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }

    {
        auto [out_idx,lhs_idx,rhs_idx] = enumerator[3];
        {
            auto [out_tag,out_ptr_idx] = out_idx;
            CHECK( out_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( out_ptr_idx, 12 );
        }
        {
            auto [lhs_tag,lhs_ptr_idx] = lhs_idx;
            CHECK( lhs_tag == ix::SIMD::PACKED );
            NMTOOLS_ASSERT_EQUAL( lhs_ptr_idx, 4 );
        }
        {
            auto [rhs_tag,rhs_ptr_idx] = rhs_idx;
            CHECK( rhs_tag == ix::SIMD::BROADCAST );
            NMTOOLS_ASSERT_EQUAL( rhs_ptr_idx, 1 );
        }
    }
}