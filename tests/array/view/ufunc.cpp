#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

namespace testing::ufunc
{
    // to check that returned view take ref
    template <typename T>
    inline auto f(const T& array)
    {
        return view::reduce_add(array,0ul);
    }

    template <typename T>
    inline auto g(const T& array)
    {
        auto reduced = f(array);
        auto divided = view::divide(reduced,1);
        return divided;
    }
}

TEST_CASE("ufunc" * doctest::test_suite("view"))
{
    using testing::ufunc::f;
    using testing::ufunc::g;
    SUBCASE("case1")
    {
        auto array = std::array<int,3>{1,2,3};
        auto reduced = view::reduce_add(array,0ul);
        auto lhs_ptr = &array;
        auto rhs_ptr = reduced.array;
        auto is_same = lhs_ptr == rhs_ptr;
        CHECK( is_same );
    }
    SUBCASE("case2")
    {
        auto array = std::array<int,3>{1,2,3};
        auto reduced = f(array);
        auto lhs_ptr = &array;
        auto rhs_ptr = reduced.array;
        auto is_same = lhs_ptr == rhs_ptr;
        CHECK( is_same );
    }
    {
        using array_t = std::array<std::array<int,3>,2>;
        array_t array = {{
            {1,2,3},
            {4,5,6}
        }};
        auto reduced_div = g(array);
        auto lhs_ptr = &array;
        auto rhs_ptr = std::get<0>(reduced_div.operands).array.array;
        auto is_same = lhs_ptr == rhs_ptr;
        CHECK( is_same );
        auto expected = std::array{5ul,7ul,9ul};
        NMTOOLS_ASSERT_EQUAL( reduced_div, expected );
    }
}