#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/maybe.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("constexpr_static_vector" * doctest::test_suite("utl"))
{
    {
        using array_t = utl::static_vector<int>;
        constexpr auto array = array_t(3);
        NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
        static_assert( meta::is_ndarray_v<array_t> );
        static_assert( meta::is_copy_constructible_v<array_t> );
    }

    {
        using array_t = utl::static_vector<int>;
        constexpr auto array = array_t();
        NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 0 );
    }

    {
        constexpr auto f = [](auto size){
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            array.resize(size);
            return array;
        };
        constexpr auto array = f(3);
        NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
    }

    {
        constexpr auto f = [](auto size){
            using array_t = utl::static_vector<int>;
            auto array = array_t(size);
            for (size_t i=0; i<(size_t)size; i++) {
                array[i] = i+1;
            }
            return array;
        };
        constexpr auto array = f(3);
        NMTOOLS_STATIC_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_STATIC_ASSERT_EQUAL( array[0], 1 );
        NMTOOLS_STATIC_ASSERT_EQUAL( array[1], 2 );
        NMTOOLS_STATIC_ASSERT_EQUAL( array[2], 3 );
    }

    {
        using array_t = utl::static_vector<int>;
        constexpr auto array  = array_t(3);
        constexpr auto copied = array_t(array);
        NMTOOLS_STATIC_ASSERT_EQUAL( copied.size(), 3 );
    }

    {
        using array_t = utl::static_vector<int>;
        constexpr auto array  = array_t(3);
        constexpr auto f = [](auto array){
            auto copied = array_t();
            copied = array;
            return copied;
        };
        constexpr auto copied = f(array);
        NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
    }

    {
        constexpr auto f = [](auto value){
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            array.push_back(value);
            return array;
        };

        constexpr auto array = f(3);

        NMTOOLS_ASSERT_EQUAL( array.size(), 1 );
        NMTOOLS_ASSERT_EQUAL( array[0], 3 );
    }
}

TEST_CASE("maybe_static_vector" * doctest::test_suite("utl"))
{
    // TODO: fix for utl
    #ifndef NMTOOLS_DISABLE_STL
    {
        using array_t = utl::static_vector<int>;
        constexpr auto array = nmtools_maybe{array_t(3)};
        NMTOOLS_STATIC_ASSERT_EQUAL( (*array).size(), 3 );
    }

    {
        constexpr auto f = [](auto size){
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            array.resize(size);
            return nmtools_maybe{array};
        };
        constexpr auto array = f(3);
        NMTOOLS_STATIC_ASSERT_EQUAL( (*array).size(), 3 );
    }

    {
        using array_t = utl::static_vector<int>;
        constexpr auto array  = array_t(3);
        constexpr auto copied = nmtools_maybe{array};
        NMTOOLS_STATIC_ASSERT_EQUAL( (*copied).size(), 3 );
    }
    #endif // NMTOOLS_DISABLE_STL
}

template <typename T>
struct wrapped_static_vector
{
    using vector_type = utl::static_vector<T>;

    vector_type vector;
};

constexpr auto push_value = [](auto value1, auto value2){
    using array_t = utl::static_vector<decltype(value1)>;
    auto array = array_t();
    array.push_back(value1);
    array.push_back(value2);
    return array;
};

template <typename T>
struct wrapped_maybe_static_vector
{
    using vector_type = utl::static_vector<T>;
    using maybe_vector_type = nmtools_maybe<vector_type>;

    maybe_vector_type maybe_vector;
};

template <typename T>
struct another_wrapped_maybe_static_vector
{
    using vector_type = utl::static_vector<T>;
    using maybe_vector_type = nmtools_maybe<vector_type>;

    maybe_vector_type maybe_vector;

    constexpr another_wrapped_maybe_static_vector(T t1, T t2)
        : maybe_vector(push_value(t1,t2))
    {}

    constexpr another_wrapped_maybe_static_vector(const maybe_vector_type& other)
        : maybe_vector(other)
    {}
};

TEST_CASE("wrapped_static_vector" * doctest::test_suite("utl"))
{
    {
        using wrapped_type = wrapped_static_vector<int>;
        auto wrapped = wrapped_type{3};
        NMTOOLS_ASSERT_EQUAL( wrapped.vector.size(), 3 );
    }
    {
        using wrapped_type = wrapped_static_vector<int>;
        constexpr auto wrapped = wrapped_type{3};
        NMTOOLS_STATIC_ASSERT_EQUAL( wrapped.vector.size(), 3 );
    }

    // works on stl, doesn't work on nostl build
    // TODO: support for utl::maybe
    // {
    //     using wrapped_type = wrapped_maybe_static_vector<int>;
    //     auto wrapped = wrapped_type{3};
    //     NMTOOLS_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 3 );
    // }
    // {
    //     using wrapped_type = wrapped_maybe_static_vector<int>;
    //     constexpr auto wrapped = wrapped_type{3};
    //     NMTOOLS_STATIC_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 3 );
    // }

    {
        using wrapped_type = wrapped_maybe_static_vector<int>;
        auto wrapped = wrapped_type{utl::static_vector<int>(3)};
        NMTOOLS_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 3 );
    }

    {
        using wrapped_type = another_wrapped_maybe_static_vector<int>;
        auto wrapped = wrapped_type(3,2);
        NMTOOLS_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 2 );
    }
    {
        using wrapped_type = another_wrapped_maybe_static_vector<int>;
        auto other = nmtools_maybe{utl::static_vector<int>(2)};
        auto wrapped = wrapped_type(other);
        NMTOOLS_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 2 );
    }
    // TODO: fix for utl
    #ifndef NMTOOLS_DISABLE_STL
    {
        using wrapped_type = another_wrapped_maybe_static_vector<int>;
        constexpr auto wrapped = wrapped_type(3,2);
        NMTOOLS_STATIC_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 2 );
    }
    {
        constexpr auto f = [](auto t1, auto t2){
            using wrapped_type = another_wrapped_maybe_static_vector<int>;
            return wrapped_type(t1,t2);
        };
        constexpr auto wrapped = f(3,2);
        NMTOOLS_STATIC_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 2 );
    }
    #endif

    // can't make the following to work, maybe needs newer version of c++
    #if 0
    {
        using wrapped_type = another_wrapped_maybe_static_vector<int>;
        constexpr auto other = nmtools_maybe{utl::static_vector<int>(2)};
        constexpr auto wrapped = wrapped_type(other);
        NMTOOLS_STATIC_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 2 );
    }
    {
        constexpr auto f = [](auto t1, auto t2){
            using wrapped_type = another_wrapped_maybe_static_vector<int>;
            auto wrapped = wrapped_type(t1,t2);
            return wrapped;
        };
        constexpr auto wrapped = f(3,2);
        NMTOOLS_STATIC_ASSERT_EQUAL( (*wrapped.maybe_vector).size(), 2 );
    }
    #endif
}

TEST_CASE("static_vector" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            static_assert( meta::is_ndarray_v<array_t> );
            static_assert( meta::is_copy_constructible_v<array_t> );
        }
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
        }
    }

    SUBCASE("resize")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            array.resize(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
        {
            using array_t = utl::static_vector<double,12>;
            auto array = array_t();
            array.resize(12);
            NMTOOLS_ASSERT_EQUAL( array.size(), 12 );
        }
    }

    SUBCASE("assignment")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            array[0] = 1;
            array[1] = 2;
            array[2] = 3;
            NMTOOLS_ASSERT_EQUAL( array[0], 1 );
            NMTOOLS_ASSERT_EQUAL( array[1], 2 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
    }

    SUBCASE("copyable")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array  = array_t(3);
            auto copied = array_t(array);
            NMTOOLS_ASSERT_EQUAL( copied.size(), 3 );
        }
    }

    SUBCASE("copy assignment")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array  = array_t(3);
            auto copied = array_t();
            copied = array;
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
        }
    }

    SUBCASE("len")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array  = array_t(3);
            NMTOOLS_ASSERT_EQUAL( nm::len(array), 3 );
        }
    }

    SUBCASE("push_back")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
            array.push_back(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 1 );
            NMTOOLS_ASSERT_EQUAL( array[0], 3 );
        }
    }

    SUBCASE("emplace")
    {
        {
            using array_t = utl::static_vector<int>;
            auto array = array_t();
            NMTOOLS_ASSERT_EQUAL( array.size(), 0 );
            array.emplace_back(3);
            NMTOOLS_ASSERT_EQUAL( array.size(), 1 );
            NMTOOLS_ASSERT_EQUAL( array[0], 3 );
            array.emplace(0,9);
            NMTOOLS_ASSERT_EQUAL( array.size(), 2 );
            NMTOOLS_ASSERT_EQUAL( array[0], 9 );
            NMTOOLS_ASSERT_EQUAL( array[1], 3 );
            array.emplace(1,7);
            NMTOOLS_ASSERT_EQUAL( array.size(), 3 );
            NMTOOLS_ASSERT_EQUAL( array[0], 9 );
            NMTOOLS_ASSERT_EQUAL( array[1], 7 );
            NMTOOLS_ASSERT_EQUAL( array[2], 3 );
        }
    }
}