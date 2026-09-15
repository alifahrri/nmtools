#include "nmtools/utility/fwd.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

TEST_CASE("fwd_attribute(case1)" * doctest::test_suite("utility"))
{
    auto src = 3ul;
    auto dst = nm::fwd_attribute(src);

    static_assert( nm::is_num_v<decltype(dst)> );
    NMTOOLS_ASSERT_EQUAL( dst, src );
}

TEST_CASE("fwd_attribute(case2)" * doctest::test_suite("utility"))
{
    auto src = nmtools_array{1,2,3};
    auto dst = nm::fwd_attribute(src);

    static_assert( nm::is_index_array_v<decltype(dst)> );
    NMTOOLS_ASSERT_EQUAL( dst, src );
}

TEST_CASE("fwd_operand(case1)" * doctest::test_suite("utility"))
{
    auto src = 3ul;
    auto dst = nm::fwd_operand(src);

    static_assert( nm::is_index_v<decltype(dst)> );
    static_assert( !nm::is_reference_v<decltype(dst)> );
    static_assert( !nm::is_pointer_v<decltype(dst)> );
    NMTOOLS_ASSERT_EQUAL( src, dst );
}

TEST_CASE("fwd_operand(case2)" * doctest::test_suite("utility"))
{
    auto src = nmtools_array{1,2,3};
    auto dst = nm::fwd_operand(src);

    static_assert( nm::is_pointer_v<decltype(dst)> );
    static_assert( nm::is_index_array_v<nm::remove_cvref_pointer_t<decltype(dst)>> );
    NMTOOLS_ASSERT_EQUAL( *dst, src );
}

TEST_CASE("fwd_operand(case3)" * doctest::test_suite("utility"))
{
    using buffer_t = nmtools_list<int>;
    auto src = buffer_t{1,2,3};
    auto dst = nm::fwd_operand(src);

    static_assert( nm::is_pointer_v<decltype(dst)> );
    static_assert( nm::is_index_array_v<nm::remove_cvref_pointer_t<decltype(dst)>> );
    NMTOOLS_ASSERT_EQUAL( *dst, src );
}

TEST_CASE("fwd_operand(case4)" * doctest::test_suite("utility"))
{
    using buffer_t = nmtools_list<int>;
    auto src = std::make_shared<buffer_t>(3);
    auto dst = nm::fwd_operand(src);

    // static_assert( nm::is_pointer_v<decltype(src)> );
    // static_assert( nm::is_pointer_v<decltype(dst)> );

    static_assert( nm::is_shared_ptr_v<decltype(src)> );
    static_assert( nm::is_ndarray_v<nm::remove_pointer_t<decltype(src)>> );
    static_assert( nm::is_shared_ptr_v<decltype(dst)> );
    static_assert( nm::is_index_array_v<nm::remove_cvref_pointer_t<decltype(dst)>> );
    NMTOOLS_ASSERT_EQUAL( *dst, *src );
}