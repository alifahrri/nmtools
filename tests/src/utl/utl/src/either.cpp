#include "nmtools/utl/either.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

using nm::none_t;

TEST_CASE("either" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using either_t = utl::either<int,double>;
            auto either = either_t{1};

            CHECK( either.index() == 0 );
        }
        {
            using either_t = utl::either<int,double>;
            auto either = either_t{1.0};

            CHECK( either.index() == 1 );
        }
        {
            using either_t = utl::either<int,double>;
            auto either = either_t{1.f};

            CHECK( either.index() == 1 );
        }
        {
            // NOTE: fail on 32-bit platform (android 32bit,)
            // using either_t = utl::either<none_t,nmtools_array<size_t,3>>;
            // auto either = either_t(nmtools_array{1ul,1ul,1ul});

            using array_t  = nmtools_array<size_t,3>;
            using either_t = utl::either<none_t,array_t>;
            auto either = either_t(array_t{1,1,1});

            CHECK( either.index() == 1 );
        }
        // ambiguous
        // {
        //     using either_t = utl::either<int,double>;
        //     auto either = either_t{1ul};

        //     CHECK( either.index() == 1 );
        // }
    }

    SUBCASE("assignment")
    {
        {
            using either_t = utl::either<int,double>;
            auto either = either_t{1};

            CHECK( either.index() == 0 );

            either = 1.;
            CHECK( either.index() == 1 );
            CHECK( either.get_if<double>() );
            CHECK( !either.get_if<int>() );
        }
        {
            using either_t = utl::either<int,double>;
            auto either = either_t{1.0};

            CHECK( either.index() == 1 );

            either = 1;
            CHECK( either.index() == 0 );
            CHECK( either.get_if<int>() );
            CHECK( !either.get_if<double>() );
        }
    }

    SUBCASE("get_if")
    {
        {
            using either_t = utl::either<int,double>;
            auto either = either_t{1};

            CHECK( either.index() == 0 );
            auto lptr = nm::get_if<int>(&either);
            using lptr_t = decltype(lptr);

            static_assert( meta::is_pointer_v<lptr_t> );
        }
    }
}