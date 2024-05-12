#include "nmtools/utl/either.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

#include <string>

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

using nm::none_t;

class StringWrapper {
public:
    // User-defined constructor (not trivial)
    StringWrapper(const std::string& str) : data(str) {}

private:
    std::string data;
};

TEST_CASE("either" * doctest::test_suite("utl"))
{
    {
        using either_t = utl::either<int,double>;
        static_assert( !meta::is_trivially_constructible_v<either_t> );
        static_assert( !std::is_trivially_constructible_v<either_t> );

        static_assert( meta::is_trivially_copy_constructible_v<either_t> );
        static_assert( std::is_trivially_copy_constructible_v<either_t> );

        static_assert( meta::is_default_constructible_v<either_t> );
        static_assert( std::is_default_constructible_v<either_t> );

        static_assert( meta::is_copy_constructible_v<either_t> );
        static_assert( std::is_copy_constructible_v<either_t> );

        static_assert( meta::is_move_constructible_v<either_t> );
        static_assert( std::is_move_constructible_v<either_t> );

        static_assert( meta::is_constructible_v<either_t,int> );
        static_assert( std::is_constructible_v<either_t,int> );

        static_assert( meta::is_constructible_v<either_t,double> );
        static_assert( std::is_constructible_v<either_t,double> );
    }
    {
        using either_t = utl::either<StringWrapper,double>;
        static_assert( !meta::is_trivially_constructible_v<either_t> );
        static_assert( !std::is_trivially_constructible_v<either_t> );

        static_assert( meta::is_default_constructible_v<either_t> );
        static_assert( std::is_default_constructible_v<either_t> );

        static_assert( meta::is_copy_constructible_v<either_t> );
        static_assert( std::is_copy_constructible_v<either_t> );

        static_assert( meta::is_move_constructible_v<either_t> );
        static_assert( std::is_move_constructible_v<either_t> );

        static_assert( meta::is_constructible_v<either_t,int> );
        static_assert( std::is_constructible_v<either_t,int> );

        static_assert( meta::is_constructible_v<either_t,double> );
        static_assert( std::is_constructible_v<either_t,double> );
    }
}

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

    SUBCASE("array")
    {
        using array_t  = utl::array<size_t,3>;
        using index_t  = size_t;
        using slice_t  = utl::either<index_t,array_t>;
        using slices_t = utl::array<slice_t,3>;
        [[maybe_unused]] auto arr1 = slice_t(array_t{0ul,1ul,1ul});
        [[maybe_unused]] auto arr2 = slice_t(array_t{0ul,3ul,1ul});
        [[maybe_unused]] auto arr3 = slice_t(array_t{0ul,3ul,1ul});
        auto result = slices_t{arr1,arr2,arr3};
        // auto result = slices_t{array_t{0ul,1ul,1ul},array_t{0ul,3ul,1ul},array_t{0ul,3ul,1ul}};
        NMTOOLS_ASSERT_EQUAL( (nm::at(result,0)), (array_t{0,1,1}) );
    }
}