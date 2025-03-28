#include "nmtools/evaluator/simd/index.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

using ix::ReductionKind;
using ix::SIMD;

TEST_CASE("outer_simd_shape(case1a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{5};
    auto rhs_shape = nmtools_array{4};
    auto out_shape = nmtools_array{5,4};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{5,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case1b)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{4};
    auto rhs_shape = nmtools_array{5};
    auto out_shape = nmtools_array{4,5};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case1c)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{4};
    auto rhs_shape = nmtools_array{6};
    auto out_shape = nmtools_array{4,6};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case1d)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{4};
    auto rhs_shape = nmtools_array{7};
    auto out_shape = nmtools_array{4,7};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case1e)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{4};
    auto rhs_shape = nmtools_array{8};
    auto out_shape = nmtools_array{4,8};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case2a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,4};
    auto rhs_shape = nmtools_array{5};
    auto out_shape = nmtools_array{2,4,5};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case2b)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,4};
    auto rhs_shape = nmtools_array{6};
    auto out_shape = nmtools_array{2,4,6};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case2c)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,4};
    auto rhs_shape = nmtools_array{7};
    auto out_shape = nmtools_array{2,4,7};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case2d)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,4};
    auto rhs_shape = nmtools_array{8};
    auto out_shape = nmtools_array{2,4,8};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,4,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case2e)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,4};
    auto rhs_shape = nmtools_array{9};
    auto out_shape = nmtools_array{2,4,9};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,4,3};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case3a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2};
    auto rhs_shape = nmtools_array{4,4};
    auto out_shape = nmtools_array{2,4,4};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,4,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case3b)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2};
    auto rhs_shape = nmtools_array{5,4};
    auto out_shape = nmtools_array{2,5,4};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,5,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case3c)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{3};
    auto rhs_shape = nmtools_array{5,6};
    auto out_shape = nmtools_array{3,5,6};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{3,5,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case4a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{5,4};
    auto out_shape = nmtools_array{2,3,5,4};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,3,5,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case4b)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{5,5};
    auto out_shape = nmtools_array{2,3,5,5};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,3,5,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case4c)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{5,6};
    auto out_shape = nmtools_array{2,3,5,6};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,3,5,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case4d)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{5,7};
    auto out_shape = nmtools_array{2,3,5,7};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,3,5,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case5a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{1,2,3};
    auto rhs_shape = nmtools_array{5,4};
    auto out_shape = nmtools_array{1,2,3,5,4};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{1,2,3,5,1};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case5b)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{1,2,3};
    auto rhs_shape = nmtools_array{5,5};
    auto out_shape = nmtools_array{1,2,3,5,5};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{1,2,3,5,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case6a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{2,7,5,6};
    auto out_shape = nmtools_array{2,3,2,7,5,6};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,3,2,7,5,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

TEST_CASE("outer_simd_shape(case6b)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{2,7,1,5,7};
    auto out_shape = nmtools_array{2,3,2,7,1,5,7};

    auto n_elem_pack = meta::as_type_v<4>;

    auto result = ix::outer_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    auto expect = nmtools_array{2,3,2,7,1,5,2};
    NMTOOLS_ASSERT_EQUAL( result, expect );
}

///////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("outer_simd(case1a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{5};
    auto rhs_shape = nmtools_array{4};
    auto out_shape = nmtools_array{5,4};

    auto n_elem_pack = meta::as_type_v<4>;

    [[maybe_unused]] auto simd_shape = nmtools_array{5,1};

    {
        auto simd_index = nmtools_array{0,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 0 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{1,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 4 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 1 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{2,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 8 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 2 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{3,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 12 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 3 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{4,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 16 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 4 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
}

TEST_CASE("outer_simd(case2a)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{4};
    auto rhs_shape = nmtools_array{5};
    auto out_shape = nmtools_array{4,5};

    auto n_elem_pack = meta::as_type_v<4>;

    [[maybe_unused]] auto simd_shape = nmtools_array{4,2};

    {
        auto simd_index = nmtools_array{0,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 0 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 0 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{0,1};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PAD_3 );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PAD_3 );

        NMTOOLS_ASSERT_EQUAL( out_offset, 4 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 0 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 4 );
    }
    {
        auto simd_index = nmtools_array{1,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 5 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 1 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{1,1};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PAD_3 );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PAD_3 );

        NMTOOLS_ASSERT_EQUAL( out_offset, 9 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 1 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 4 );
    }
    {
        auto simd_index = nmtools_array{2,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 10 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 2 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{2,1};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PAD_3 );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PAD_3 );

        NMTOOLS_ASSERT_EQUAL( out_offset, 14 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 2 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 4 );
    }
    {
        auto simd_index = nmtools_array{3,0};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PACKED );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PACKED );

        NMTOOLS_ASSERT_EQUAL( out_offset, 15 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 3 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 0 );
    }
    {
        auto simd_index = nmtools_array{3,1};

        auto [out_index,lhs_index,rhs_index] = ix::outer_simd(n_elem_pack,simd_index,simd_shape,out_shape,lhs_shape,rhs_shape);

        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == SIMD::PAD_3 );
        CHECK( lhs_tag == SIMD::BROADCAST );
        CHECK( rhs_tag == SIMD::PAD_3 );

        NMTOOLS_ASSERT_EQUAL( out_offset, 19 );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, 3 );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, 4 );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("outer_simd_enumerator(case1)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{5};
    auto rhs_shape = nmtools_array{4};
    auto out_shape = nmtools_array{5,4};

    auto n_elem_pack = meta::as_type_v<4>;

    [[maybe_unused]] auto simd_shape = nmtools_array{5,1};

    auto out_tags = nmtools_array<SIMD,5>{SIMD::PACKED,SIMD::PACKED,SIMD::PACKED,SIMD::PACKED,SIMD::PACKED};
    auto lhs_tags = nmtools_array<SIMD,5>{SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST};
    auto rhs_tags = nmtools_array<SIMD,5>{SIMD::PACKED,SIMD::PACKED,SIMD::PACKED,SIMD::PACKED,SIMD::PACKED};
    auto out_offsets = nmtools_array{0,4,8,12,16};
    auto lhs_offsets = nmtools_array{0,1,2,3,4};
    auto rhs_offsets = nmtools_array{0,0,0,0,0};

    auto enumerator = ix::outer_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    NMTOOLS_ASSERT_EQUAL( enumerator.size(), out_tags.size() );
    for (size_t i=0; i<out_tags.size(); i++) {
        auto [out_index,lhs_index,rhs_index] = enumerator[i];
        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == out_tags[i] );
        CHECK( lhs_tag == lhs_tags[i] );
        CHECK( rhs_tag == rhs_tags[i] );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, lhs_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, rhs_offsets[i] );
    }
}

TEST_CASE("outer_simd_enumerator(case2)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{4};
    auto rhs_shape = nmtools_array{5};
    auto out_shape = nmtools_array{4,5};

    auto n_elem_pack = meta::as_type_v<4>;

    [[maybe_unused]] auto simd_shape = nmtools_array{4,2};

    auto out_tags = nmtools_array<SIMD,8>{SIMD::PACKED,SIMD::PAD_3,SIMD::PACKED,SIMD::PAD_3,SIMD::PACKED,SIMD::PAD_3,SIMD::PACKED,SIMD::PAD_3};
    auto lhs_tags = nmtools_array<SIMD,8>{SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST,SIMD::BROADCAST};
    auto rhs_tags = nmtools_array<SIMD,8>{SIMD::PACKED,SIMD::PAD_3,SIMD::PACKED,SIMD::PAD_3,SIMD::PACKED,SIMD::PAD_3,SIMD::PACKED,SIMD::PAD_3};
    auto out_offsets = nmtools_array{0,4,5,9,10,14,15,19};
    auto lhs_offsets = nmtools_array{0,0,1,1,2,2,3,3};
    auto rhs_offsets = nmtools_array{0,4,0,4,0,4,0,4};

    auto enumerator = ix::outer_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    NMTOOLS_ASSERT_EQUAL( enumerator.size(), out_tags.size() );
    for (size_t i=0; i<out_tags.size(); i++) {
        auto [out_index,lhs_index,rhs_index] = enumerator[i];
        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK( out_tag == out_tags[i] );
        CHECK( lhs_tag == lhs_tags[i] );
        CHECK( rhs_tag == rhs_tags[i] );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, lhs_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, rhs_offsets[i] );
    }
}

TEST_CASE("outer_simd_enumerator(case3)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,4};
    auto rhs_shape = nmtools_array{5};
    auto out_shape = nmtools_array{2,4,5};

    auto n_elem_pack = meta::as_type_v<4>;

    [[maybe_unused]] auto simd_shape = nmtools_array{2,4,2};

    auto out_tags = nmtools_array<SIMD,16>{
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
    };
    auto lhs_tags = nmtools_array<SIMD,16>{
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
    };
    auto rhs_tags = nmtools_array<SIMD,16>{
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
        SIMD::PACKED,SIMD::PAD_3,
    };
    auto out_offsets = nmtools_array{0,4,5,9,10,14,15,19,20,24,25,29,30,34,35,39};
    auto lhs_offsets = nmtools_array{0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7};
    auto rhs_offsets = nmtools_array{0,4,0,4,0,4,0,4,0,4,0,4,0,4,0,4};

    auto enumerator = ix::outer_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    NMTOOLS_ASSERT_EQUAL( enumerator.size(), out_tags.size() );
    for (size_t i=0; i<out_tags.size(); i++) {
        auto [out_index,lhs_index,rhs_index] = enumerator[i];
        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK_MESSAGE( out_tag == out_tags[i], i );
        CHECK_MESSAGE( lhs_tag == lhs_tags[i], i );
        CHECK_MESSAGE( rhs_tag == rhs_tags[i], i );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, lhs_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, rhs_offsets[i] );
    }
}

TEST_CASE("outer_simd_enumerator(case4)" * doctest::test_suite("simd::index"))
{
    auto lhs_shape = nmtools_array{2,4};
    auto rhs_shape = nmtools_array{6};
    auto out_shape = nmtools_array{2,4,6};

    auto n_elem_pack = meta::as_type_v<4>;

    [[maybe_unused]] auto simd_shape = nmtools_array{2,4,2};

    auto out_tags = nmtools_array<SIMD,16>{
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
    };
    auto lhs_tags = nmtools_array<SIMD,16>{
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
        SIMD::BROADCAST,SIMD::BROADCAST,
    };
    auto rhs_tags = nmtools_array<SIMD,16>{
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
        SIMD::PACKED,SIMD::PAD_2,
    };
    auto out_offsets = nmtools_array{0,4,6,10,12,16,18,22,24,28,30,34,36,40,42,46};
    auto lhs_offsets = nmtools_array{0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7};
    auto rhs_offsets = nmtools_array{0,4,0,4,0,4,0,4,0,4,0,4,0,4,0,4};

    auto enumerator = ix::outer_simd_enumerator(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    NMTOOLS_ASSERT_EQUAL( enumerator.size(), out_tags.size() );
    for (size_t i=0; i<out_tags.size(); i++) {
        auto [out_index,lhs_index,rhs_index] = enumerator[i];
        const auto out_tag = nm::get<0>(out_index);
        const auto lhs_tag = nm::get<0>(lhs_index);
        const auto rhs_tag = nm::get<0>(rhs_index);
        const auto out_offset = nm::get<1>(out_index);
        const auto lhs_offset = nm::get<1>(lhs_index);
        const auto rhs_offset = nm::get<1>(rhs_index);
        CHECK_MESSAGE( out_tag == out_tags[i], i );
        CHECK_MESSAGE( lhs_tag == lhs_tags[i], i );
        CHECK_MESSAGE( rhs_tag == rhs_tags[i], i );
        NMTOOLS_ASSERT_EQUAL( out_offset, out_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( lhs_offset, lhs_offsets[i] );
        NMTOOLS_ASSERT_EQUAL( rhs_offset, rhs_offsets[i] );
    }
}