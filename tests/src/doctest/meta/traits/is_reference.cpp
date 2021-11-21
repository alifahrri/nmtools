#include "nmtools/meta/bits/traits/is_reference.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

union Union {};
struct BitZero { int: 0; };
class Abstract { virtual ~Abstract() = 0; };

enum Enum { one, two };
struct Incomplete;

typedef void (*FunctionPtr)();

TEST_CASE("is_lvalue_reference" * doctest::test_suite("meta"))
{
    {
        using arg_t = int&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_lvalue_reference, arg_t );
    }

    {
        using arg_t = int;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = int*;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = int&&;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = double;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = const int*;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = char[3];
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = char[];
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = Union;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = Enum;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = FunctionPtr;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = BitZero;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = Abstract;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
    }
    {
        using arg_t = Incomplete;
        // nmtools macro will print the type, which must be complete
        // NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_lvalue_reference, arg_t );
        static_assert( !meta::is_lvalue_reference_v<arg_t> );
    }
}

TEST_CASE("is_rvalue_reference" * doctest::test_suite("meta"))
{
    {
        using arg_t = int&&;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_rvalue_reference, arg_t );
    }

    {
        using arg_t = int;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = int*;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = int&;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = double;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = const int*;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = char[3];
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = char[];
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = Union;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = Enum;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = FunctionPtr;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = BitZero;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = Abstract;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
    }
    {
        using arg_t = Incomplete;
        // nmtools macro will print the type, which must be complete
        // NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_rvalue_reference, arg_t );
        static_assert( !meta::is_rvalue_reference_v<arg_t> );
    }
}