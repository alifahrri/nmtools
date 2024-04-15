#include "nmtools/array/functional/resize.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/testing/data/array/resize.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/utils/to_string.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(nm::unwrap(result)), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

// error on gcc w/ stl, but ok on gcc no-stl, and clang stl/no-stl
// nmtools/array/functional/functor.hpp:470:79:
//   in 'constexpr' expansion of
// 'nmtools::get<0, std::tuple<const std::tuple<nmtools::meta::integral_constant<long unsigned int, 2>,
//      nmtools::meta::integral_constant<long unsigned int, 2> > > >((* & attributes))'
// /usr/include/c++/9/tuple:1327:36: error: no matching function for call to '__get_helper<0>(const std::tuple<const std::tuple<nmtools::meta::integral_constant<long unsigned int, 2>, nmtools::meta::integral_constant<long unsigned int, 2> > >&)'
//  1327 |     { return std::__get_helper<__i>(__t); }
//       |              ~~~~~~~~~~~~~~~~~~~~~~^~~~~
// /usr/include/c++/9/tuple:1309:5: note: candidate: 'template<long unsigned int __i, class _Head, class ... _Tail> constexpr _Head& std::__get_helper(std::_Tuple_impl<_Idx, _Head, _Tail ...>&)'
//  1309 |     __get_helper(_Tuple_impl<__i, _Head, _Tail...>& __t) noexcept
//       |     ^~~~~~~~~~~~
// /usr/include/c++/9/tuple:1309:5: note:
//    template argument deduction/substitution failed:
// /usr/include/c++/9/tuple:1327:36: note:
//   types 'std::_Tuple_impl<0, _UHead, _UTails ...>' and 'const std::tuple<const std::tuple<nmtools::meta::integral_constant<long unsigned int, 2>, nmtools::meta::integral_constant<long unsigned int, 2> > >' 
// have incompatible cv-qualifiers

#if defined(__clang__) || defined(NMTOOLS_DISABLE_STL)
TEST_CASE("resize(case1)" * doctest::test_suite("functional::resize"))
{
    NMTOOLS_TESTING_DECLARE_NS(resize, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::resize[dst_shape_ct], array );
    FUNCTIONAL_SUBCASE( "case1", fn::resize[dst_shape_ct], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::resize[dst_shape_ct], array_f );
    // FUNCTIONAL_SUBCASE( "case1", fn::resize[dst_shape_ct], array_h );
    // FUNCTIONAL_SUBCASE( "case1", fn::resize[dst_shape_ct], array_d );
}
#endif

namespace view = nmtools::view;

TEST_CASE("resize" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(resize,case1);
    using namespace args;

    auto a = view::resize(array,dst_shape);

    static_assert( meta::is_trivially_destructible_v<decltype(a)> );

    auto function = fn::get_function_composition(a);
    auto expect = fn::resize[dst_shape];

    // TODO: support function isequal with maybe type
    NMTOOLS_ASSERT_EQUAL( *function, expect );
}

// error: initializations for multiple members of
// 'std::_Optional_payload_base<nmtools::view::decorator_t<nmtools::view::indexing_t, int [4][4], nmtools::view::resize_t<std::tuple<nmtools::meta::integral_constant<long unsigned int, 4>, nmtools::meta::integral_constant<long unsigned int, 4> >, std::array<long unsigned int, 2> > > >::_Storage<nmtools::view::decorator_t<nmtools::view::indexing_t
// , int [4][4], nmtools::view::resize_t<std::tuple<nmtools::meta::integral_constant<long unsigned int, 4>, nmtools::meta::integral_constant<long unsigned int, 4> >, std::array<long unsigned int, 2> > >, true>'
//   195 |  union _Storage
#if defined(__clang__) || defined(NMTOOLS_DISABLE_STL)
TEST_CASE("resize" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(resize,case1);
    using namespace args;

    auto a = view::resize(array,dst_shape);

    auto function = fn::get_function_composition(a);

    NMTOOLS_ASSERT_EQUAL( (*function)(array), a );
}
#endif