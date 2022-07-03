#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

// from en cpp reference

struct Foo {
   std::string str;
   ~Foo() noexcept {};
};

struct Bar {
    ~Bar() = default;
};

TEST_CASE("is_trivially_destructible(case1)" * doctest::test_suite("meta"))
{
    {
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_trivially_destructible, Foo );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_trivially_destructible, Bar );
    }
}