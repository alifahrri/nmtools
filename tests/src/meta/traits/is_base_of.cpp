#include "nmtools/meta/bits/traits/is_base_of.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

struct B {};
struct B1 : B {};
struct B2 : B {};
struct D : private B1, private B2 {};
struct E : private B1 {};
struct I0; // incomplete

TEST_CASE("is_base_of" * doctest::test_suite("meta"))
{
    {
        using Base = B;
        using Derived = D;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), true );
    }
    {
        using Base = B1;
        using Derived = D;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), true );
    }
    {
        using Base = B1;
        using Derived = E;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), true );
    }
    {
        using Base = B2;
        using Derived = D;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), true );
    }
    {
        using Base = B;
        using Derived = B1;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), true );
    }
    {
        using Base = B;
        using Derived = B2;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), true );
    }
    {
        using Base = B;
        using Derived = B;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), true );
    }


    {
        using Base = D;
        using Derived = B;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = B&;
        using Derived = D&;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = B[3];
        using Derived = D[3];
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = int;
        using Derived = int;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }

    {
        using Base = int;
        using Derived = B;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = int;
        using Derived = B1;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = int;
        using Derived = B2;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = int;
        using Derived = D;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = int;
        using Derived = I0;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }

    {
        using Base = B;
        using Derived = int;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = B1;
        using Derived = int;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = B2;
        using Derived = int;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = D;
        using Derived = int;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
    {
        using Base = I0;
        using Derived = int;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }

    {
        using Base = meta::detail::fail_t;
        using Derived = std::tuple<int,int,int>;
        NMTOOLS_STATIC_ASSERT_EQUAL( (meta::internal::is_base_of_v<Base,Derived>), false );
    }
}