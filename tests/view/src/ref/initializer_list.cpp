#include "nmtools/core/ref/initializer_list.hpp"
#include "nmtools/array/flatten.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::unwrap;

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("initializer_list" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<double>{1,2,3,4,5};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view = nmtools::view::ref(list);
    CHECK( unwrap(view)(1)==2 );
    CHECK( nmtools::dim(unwrap(view))==1 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{5}) );
}

TEST_CASE("initializer_list[2]" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<std::initializer_list<double>>{{1,2,3,4,5}};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view = nmtools::view::ref(list);
    CHECK( unwrap(view)(0,1)==2 );
    CHECK( nmtools::dim(unwrap(view))==2 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{1,5}) );
}

TEST_CASE("initializer_list[2]" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<std::initializer_list<double>>{{1,2,3,4,5},{6,7,8,9,10}};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view = nmtools::view::ref(list);
    CHECK( unwrap(view)(1,0)==6 );
    CHECK( nmtools::dim(unwrap(view))==2 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{2,5}) );
}

TEST_CASE("initializer_list[3]" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<std::initializer_list<std::initializer_list<double>>>{{{1,2,3,4,5},{6,7,8,9,10}}};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view = nmtools::view::ref(list);
    CHECK( unwrap(view)(0,1,0)==6 );
    CHECK( nmtools::dim(unwrap(view))==3 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{1,2,5}) );
}

TEST_CASE("ref(ref(ref(initializer_list)))" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<double>{1,2,3,4,5};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view0 = nmtools::view::ref(list);
    auto view1 = nmtools::view::ref(view0);
    auto view  = nmtools::view::ref(view1);
    CHECK(unwrap(view)(1)==2);
    CHECK( nmtools::dim(unwrap(view))==1 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{5}) );
}

TEST_CASE("ref(ref(ref(initializer_list[2])))" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<std::initializer_list<double>>{{1,2,3,4,5},{6,7,8,9,10}};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view0 = nmtools::view::ref(list);
    auto view1 = nmtools::view::ref(view0);
    auto view  = nmtools::view::ref(view1);
    CHECK( unwrap(view)(0,1)==2 );
    CHECK( nmtools::dim(unwrap(view))==2 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{2,5}) );
}

TEST_CASE("ref(ref(ref(initializer_list[3])))" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<std::initializer_list<std::initializer_list<double>>>{{{1,2,3,4,5},{6,7,8,9,10}}};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view0 = nmtools::view::ref(list);
    auto view1 = nmtools::view::ref(view0);
    auto view  = nmtools::view::ref(view1);
    CHECK( unwrap(view)(0,1,0)==6 );
    CHECK( nmtools::dim(unwrap(view))==3 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{1,2,5}) );
}

TEST_CASE("flattten(ref(initializer_list))" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<double>{1,2,3,4,5};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view0 = nmtools::view::ref(list);
    auto view  = nmtools::view::flatten(view0);
    CHECK( unwrap(view)(1)==2 );
    CHECK( nmtools::dim(unwrap(view))==1 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{5}) );
}

TEST_CASE("flattten(ref(initializer_list[2]))" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<std::initializer_list<double>>{{1,2,3,4,5},{6,7,8,9,10}};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view0 = nmtools::view::ref(list);
    auto view  = nmtools::view::flatten(view0);
    CHECK( unwrap(view)(1)==2 );
    CHECK( nmtools::dim(unwrap(view))==1 );
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(view), (std::array{10}) );
}
#endif