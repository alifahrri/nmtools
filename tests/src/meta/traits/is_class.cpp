#include "nmtools/meta/bits/traits/is_class.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

class Empty
{
};

// causes link error from boost type index
// class NotEmpty
// {
//     virtual ~NotEmpty();
// };

class NotEmpty
{
    public:
        int value;
};

union Union {};

struct bit_zero
{
    int :  0;
};

class Abstract
{
    virtual ~Abstract() = 0;
};

enum Enum {zero, one};
struct incomplete_type;

typedef void (*FunctionPtr)();

TEST_CASE("is_class" * doctest::test_suite("meta"))
{
    {
        using type = Empty;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_class, type );
    }
    {
        using type = NotEmpty;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_class, type );
    }
    {
        using type = bit_zero;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_class, type );
    }
    {
        using type = Abstract;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_class, type );
    }
    {
        using type = incomplete_type;
        // boost type index can't print incomplete type
        // NMTOOLS_STATIC_CHECK_TRAIT( meta::is_class, type );
        NMTOOLS_STATIC_ASSERT_EQUAL( meta::is_class_v<type>, true );
    }

    {
        using type = void;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = int;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = int&;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = int&&;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = int*;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = double;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = const int*;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = char[3];
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = char[];
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = Enum;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = Union;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
    {
        using type = FunctionPtr;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_class, type );
    }
}