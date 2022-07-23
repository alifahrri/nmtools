#include "nmtools/array/view/ref/initializer_list.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/testing/doctest.hpp"

TEST_CASE("initializer_list" * doctest::test_suite("view::ref"))
{
    using nmtools::view::ref_t;
    // @note initializer_list cant be ctad-ed on clang
    auto list = std::initializer_list<double>{1,2,3,4,5};
    // @note somehow wont compile, cant find specialization of initializer_list
    // @todo fix
    // auto view = nmtools::view::make_view<ref_t>(list);
    auto view = nmtools::view::ref(list);
    CHECK( view(1)==2 );
    CHECK( view.dim()==1 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{5}) );
    // should fail
    // CHECK(view(1,0)==2);
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);

    
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using array_t = nmtools::meta::get_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<double>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<double>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK( view(0,1)==2 );
    CHECK( view.dim()==2 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{1,5}) );
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using array_t = nmtools::meta::get_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<double>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<double>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK( view(1,0)==6 );
    CHECK( view.dim()==2 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{2,5}) );
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using array_t = nmtools::meta::get_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<double>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<double>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK( view(0,1,0)==6 );
    CHECK( view.dim()==3 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{1,2,5}) );
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    STATIC_CHECK(!nmtools::meta::is_array1d_v<decltype(view)>);
    
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using array_t = nmtools::meta::get_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<std::initializer_list<double>>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<std::initializer_list<double>>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK(view(1)==2);
    CHECK( view.dim()==1 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{5}) );
    // should fail
    // CHECK(view(1,0)==2);
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<double>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK( view(0,1)==2 );
    CHECK( view.dim()==2 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{2,5}) );
    // should fail
    // CHECK(view(1,0)==2);
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view1)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view0)>);
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<double>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK( view(0,1,0)==6 );
    CHECK( view.dim()==3 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{1,2,5}) );
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    STATIC_CHECK(!nmtools::meta::is_array1d_v<decltype(view)>);
    
    // LOG_TYPEINFO( decltype(view) );
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<std::initializer_list<double>>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK( view(1)==2 );
    CHECK( view.dim()==1 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{5}) );
    // should fail
    // CHECK(view(1,0)==2);
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    
    
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using nmtools::view::decorator_t;
        using nmtools::view::ref_t;
        using array_t = nmtools::meta::get_array_type_t<decltype(view)>;
        using expected_t = const decorator_t<ref_t,std::initializer_list<double>>;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<double>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
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
    CHECK( view(1)==2 );
    CHECK( view.dim()==1 );
    NMTOOLS_ASSERT_EQUAL( view.shape(), (std::array{10}) );
    // should fail
    // CHECK(view(1,0)==2);
    STATIC_CHECK( nmtools::meta::has_shape_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::has_dim_v<decltype(view)>);
    
    
    STATIC_CHECK( nmtools::meta::is_ndarray_v<decltype(view)>);
    STATIC_CHECK( nmtools::meta::is_view_v<decltype(view)>);
    {
        using nmtools::view::decorator_t;
        using nmtools::view::ref_t;
        using array_t = nmtools::meta::get_array_type_t<decltype(view)>;
        using expected_t = const decorator_t<ref_t,std::initializer_list<std::initializer_list<double>>>;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using array_t = nmtools::meta::get_underlying_array_type_t<decltype(view)>;
        using expected_t = const std::initializer_list<std::initializer_list<double>>&;
        STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}