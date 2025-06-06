#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CURRY_BINARY_SUBCASE(subcase_name, function, lhs, rhs) \
SUBCASE(subcase_name) \
{ \
    auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, multiply)
    NMTOOLS_TESTING_USE_CASE(view, multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a, b );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_a, b_a );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_f, b_f );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_h, b_h );
    FUNCTIONAL_SUBCASE( "case1", fn::multiply, a_d, b_d );

    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a, b );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_a, b_a );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_f, b_f );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_h, b_h );
    CURRY_BINARY_SUBCASE( "case1", fn::multiply, a_d, b_d );
}

TEST_CASE("reduce_multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::reduce_multiply[axis], a_d );
}

TEST_CASE("reduce_multiply(case4)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case4);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_a );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_f );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_h );
    FUNCTIONAL_SUBCASE( "case4", fn::reduce_multiply[axis], a_d );
}

TEST_CASE("reduce_multiply(case8)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case8);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_a );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_f );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_h );
    FUNCTIONAL_SUBCASE( "case8", fn::reduce_multiply[axis][dtype][initial], a_d );
}

TEST_CASE("reduce_multiply(case9)" * doctest::test_suite("functional::multiply"))
{
    // TODO: rename namespace to (array, reduce_multiply)
    NMTOOLS_TESTING_USE_CASE(view, reduce_multiply, case9);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case9", fn::reduce_multiply[axis][dtype][initial][keepdims], a_d );
}

TEST_CASE("accumulate_multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    NMTOOLS_TESTING_USE_CASE(view, accumulate_multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::accumulate_multiply[axis], a_d );
}

TEST_CASE("outer_multiply(case1)" * doctest::test_suite("functional::multiply"))
{
    NMTOOLS_TESTING_USE_CASE(view, outer_multiply, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a, b );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_a, b_a );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_f, b_f );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_h, b_h );
    FUNCTIONAL_SUBCASE( "case1", fn::outer_multiply, a_d, b_d );

    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a, b );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_a, b_a );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_f, b_f );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_h, b_h );
    CURRY_BINARY_SUBCASE( "case1", fn::outer_multiply, a_d, b_d );
}

namespace view = nmtools::view;

TEST_CASE("multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,multiply,case1);
    using namespace args;

    auto array = view::multiply(a,b);

    auto function = fn::get_function_composition(array);
    auto expect = fn::broadcast_binary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

namespace view = nmtools::view;
namespace kwargs = nmtools::args;

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto array = view::reduce_multiply(a,axis,dtype,initial,keepdims);

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs::reduce{
        axis
        , dtype
        , initial
        , keepdims
        , view::multiply_t<>{}
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto op = view::multiply_t<>{};
    auto array = view::reduce(a,op,kwargs::reduce{axis,dtype,initial,keepdims});

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs::reduce{
        axis
        , dtype
        , initial
        , keepdims
        , op
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto op = view::multiply_t<>{};
    auto array = view::reduce(a,op,kwargs::reduce{axis,dtype,initial,keepdims});

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[op][kwargs::reduce{
        axis
        , dtype
        , initial
        , keepdims
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}



#ifdef NMTOOLS_TESTING_KWARGS_INIT
#ifndef __clang__
TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto kwargs = kwargs::reduce{
          .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
        , .op=view::multiply_t<>{}
    };

    auto array = view::reduce_multiply(a,axis,dtype,initial,keepdims);

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto array = view::reduce_multiply(a,axis,dtype,initial,keepdims);

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs::reduce{
          .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
        , .op=view::multiply_t<>{}
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto op = view::multiply_t<>{};

    auto array = view::reduce(a,kwargs::reduce{axis,dtype,initial,keepdims,op});

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs::reduce{
          .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
        , .op=view::multiply_t<>{}
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto op = view::multiply_t<>{};

    auto array = view::reduce(a,kwargs::reduce{
        .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
        , .op=op
    });

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs::reduce{
          .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
        , .op=view::multiply_t{}
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto array = view::reduce_multiply(a,kwargs::reduce{
        .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
    });

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs::reduce{
          .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
        , .op=view::multiply_t{}
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto op = view::multiply_t{};
    auto array = view::reduce(a,op,kwargs::reduce{
        .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
    });

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[kwargs::reduce{
        .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
        , .op=op
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

TEST_CASE("reduce_multiply" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,reduce_multiply,case9);
    using namespace args;

    auto op = view::multiply_t{};
    auto array = view::reduce(a,op,kwargs::reduce{
        .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
    });

    auto function = fn::get_function_composition(array);
    auto expected = fn::reduce[op][kwargs::reduce{
        .axis=axis
        , .dtype=dtype
        , .initial=initial
        , .keepdims=keepdims
    }];

    NMTOOLS_ASSERT_EQUAL( function, expected );
    NMTOOLS_ASSERT_CLOSE( function (a), expect::result );
}

#endif // __clang__
#endif // NMTOOLS_TESTING_KWARGS_INIT