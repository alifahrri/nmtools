#include "nmtools/def.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::f2;
using namespace nmtools::literals;

TEST_CASE("f2")
{
    {
        auto a = f2{0b0101};
        auto b = f2{0b0011};
        auto c = a + b;
        CHECK( c.i == 0b0110 );
        CHECK( int(f2(5) + f2(3)) == 6 );
    }
    {
        CHECK( int(f2(11) + f2(7)) == 12 );
    }
    {
        CHECK( f2(7) + f2(7) == f2(0) );
        CHECK( f2(7) - f2(7) == f2(0) );
    }
    {
        CHECK( (f2(0b011) * 0b011) == f2(0b101) );
        CHECK( (f2(0b011) * f2(0b011)) == f2(0b101) );
        CHECK( (f2(3) * f2(3)) == f2(5) );
    }
    {
        CHECK( f2(0b101) * f2(0b100) == f2(0b10100) );
        CHECK( f2(5) * 4 == 20 );
    }
    {
        CHECK( f2(5) * 1 == f2(5) );
        CHECK( f2(5) * f2(1) == f2(5) );
    }
    {
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_f2_num, f2<int> );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_num, f2<int> );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_integer, f2<int> );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index, f2<int> );
    }
    {
        using type = nmtools_array<f2<int>,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index_array, type );
        NMTOOLS_STATIC_CHECK_IS_SAME( nmtools::get_element_type_t<type>, f2<int> );
        NMTOOLS_STATIC_CHECK_IS_SAME( nmtools::get_index_element_type_t<type>, f2<int> );
    }
    {
        auto lhs = nmtools_array{f2(2),f2(11),f2(16)};
        auto rhs = nmtools_array{2,11,16};
        NMTOOLS_ASSERT_EQUAL( lhs, rhs );
        for (nm_size_t i=0; i<3; i++) {
            NMTOOLS_ASSERT_EQUAL( lhs[i], rhs[i] );
        }
    }
    {
        auto a = f2{5_ct};
        auto b = f2{3_ct};
        auto c = a + b;
        CHECK( c.i == 0b0110 );
        CHECK( f2(5_ct) + f2(3_ct) == 6 );
        CHECK( f2(5_ct) + f2(3_ct) == f2(6_ct) );

        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_f2_num, decltype(a) );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_num, decltype(a) );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_integral_constant, decltype(a) );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index, decltype(a) );
    }
    {
        CHECK( (f2(3_ct) * f2(3_ct)) == f2(5) );
        CHECK( (f2(3_ct) * f2(3)) == f2(5) );
        CHECK( (f2(3) * f2(3_ct)) == f2(5) );
    }
    {
        auto stride = nmtools_tuple{f2(9_ct),f2(1_ct)};

        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_constant_index_array, decltype(stride) );
        NMTOOLS_STATIC_CHECK_IS_SAME( nmtools::get_index_element_type_t<decltype(stride)>, f2<nm_size_t> );

        constexpr auto STRIDE = nmtools::to_value_v<decltype(stride)>;
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_index_array, decltype(STRIDE) );
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_f2_num, nmtools::get_value_type_t<decltype(STRIDE)> );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( nmtools::meta::is_constant_index, nmtools::get_value_type_t<decltype(STRIDE)> );
        NMTOOLS_ASSERT_EQUAL( stride, STRIDE );
    }
    {
        using common_t = nmtools::meta::common_type_t<decltype(f2(9_ct)),f2<int>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( common_t, f2<int> );
    }
    {
        using common_t = nmtools::meta::common_type_t<decltype(f2(9_ct)),int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( common_t, int );
        CHECK( nmtools::can_cast_v<decltype(f2(9_ct)),int> );
        CHECK( nmtools::can_cast_v<decltype(f2(9_ct)),f2<int>> );
        CHECK( !nmtools::can_cast_v<int,decltype(f2(9_ct))> );
    }
}