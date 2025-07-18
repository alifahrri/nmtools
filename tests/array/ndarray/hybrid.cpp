#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;

TEST_CASE("hybrid_ndarray(1)" * doctest::test_suite("hybrid_ndarray"))
{
    // TODO: fix assignment operator=
    #if 0
    {
        auto array = na::hybrid_ndarray<double,3,1>{};
        auto shape = nmtools_array{3};
        NMTOOLS_ASSERT_EQUAL( array.shape(), shape );
        NMTOOLS_ASSERT_EQUAL( array.dim(),   1 );
        array = {1,2,3};
        double expected[3] = {1,2,3};
        NMTOOLS_ASSERT_CLOSE( array, expected );
        array(0) = 4;
        // @note no matching call
        // array(0,0) = 4;
        NMTOOLS_ASSERT_CLOSE( array(0), 4 );
        array.at({0}) = 4;
        NMTOOLS_ASSERT_CLOSE( array.at({0}), 4 );
    }
    #endif
    {
        auto array = na::hybrid_ndarray({1,2,3,4,5,6});
        using array_t = decltype(array);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_resizable, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_hybrid_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_IS_SAME( meta::get_element_type_t<array_t>, int );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::has_tuple_size, array_t );

        double expected[6] = {1,2,3,4,5,6};
        NMTOOLS_ASSERT_CLOSE( array, expected );
    }
    {
        auto array = na::hybrid_ndarray({1,2,3,4,5,6});
        array.resize(3);
        double expected[3] = {1,2,3};
        NMTOOLS_ASSERT_CLOSE( array, expected );
    }
}

TEST_CASE("hybrid_ndarray(2)" * doctest::test_suite("hybrid_ndarray"))
{
    // TODO: fix assignment operator=
    #if 0
    {
        auto array = na::hybrid_ndarray<double,6,2>{};
        auto shape = nmtools_array{6,1};
        NMTOOLS_ASSERT_EQUAL( array.shape(), shape );
        NMTOOLS_ASSERT_EQUAL( array.dim(),   2 );
        // @note assertion fail
        // array = {
        //     {1,2,3},
        //     {4,5,6}
        // };
        // @note ambiguous call
        // array = {
        //     {1},
        //     {2},
        //     {3},
        //     {4},
        //     {5},
        //     {6}
        // };
        double tmp[6][1] = {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6}
        };
        array = std::move(tmp);
        double e1[6][1] = {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6}
        };
        NMTOOLS_ASSERT_CLOSE( array, e1 );
        array.resize(2,3);
        array = {
            {1,2,3},
            {4,5,6}
        };
        double e2[2][3] = {
            {1,2,3},
            {4,5,6}
        };
        NMTOOLS_ASSERT_CLOSE( array, e2 );
        array(0,0) = 4;
        // @note no matching call
        // array(0) = 4;
        NMTOOLS_ASSERT_CLOSE( array(0,0), 4 );
        array.at({0,0}) = 4;
        NMTOOLS_ASSERT_CLOSE( array.at({0,0}), 4 );
    }
    #endif
    // TODO: fix
    #if 0
    {
        auto array = na::hybrid_ndarray({
            {1,2,3},
            {4,5,6}
        });
        using array_t = decltype(array);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_resizable, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_hybrid_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_IS_SAME( meta::get_element_type_t<array_t>, int );
        double expected[2][3] = {
            {1,2,3},
            {4,5,6}
        };
        NMTOOLS_ASSERT_EQUAL( nm::shape(array), nm::shape(expected) );
        NMTOOLS_ASSERT_CLOSE( array, expected );
    }
    #endif
    {
        auto array = na::hybrid_ndarray({
            {1,2,3},
            {4,5,6}
        });
        array.resize(1,3);
        double e1[1][3] = {
            {1,2,3},
        };
        NMTOOLS_ASSERT_CLOSE( array, e1 );
        array.resize(3,1);
        // @note assertion fail
        // NMTOOLS_ASSERT_CLOSE( array, e1 );
        double e2[3][1] = {
            {1},
            {2},
            {3},
        };
        NMTOOLS_ASSERT_CLOSE( array, e2 );
    }
}

TEST_CASE("hybrid_ndarray(3)" * doctest::test_suite("hybrid_ndarray"))
{
    {
        auto array = na::hybrid_ndarray<double,6,3>{};
        auto shape = nmtools_array{6,1,1};
        NMTOOLS_ASSERT_EQUAL( array.shape(), shape );
        NMTOOLS_ASSERT_EQUAL( array.dim(),   3 );

        double tmp[6][1][1] = {
            {
                {1}
            },
            {
                {2}
            },
            {
                {3}
            },
            {
                {4}
            },
            {
                {5}
            },
            {
                {6}
            }
        };
        array = std::move(tmp);
        array.resize(1,1,6);
        #if 0
        array = {{
            {1,2,3,4,5,6}
        }};
        #else
        {
            double a[1][1][6] = {{
                {1,2,3,4,5,6}
            }};
            array = a;
        }
        #endif
        double e1[1][1][6] = {{
            {1,2,3,4,5,6}
        }};
        NMTOOLS_ASSERT_CLOSE( array, e1 );
        array.resize(1,3,2);
        #if 0
        array = {
            {
                {1,2},
                {3,4},
                {5,6}
            }
        };
        #else
        {
            double a[1][3][2] = {
                {
                    {1,2},
                    {3,4},
                    {5,6}
                }
            };
            array = a;
        }
        #endif
        double e2[1][3][2] = {
            {
                {1,2},
                {3,4},
                {5,6}
            }
        };
        NMTOOLS_ASSERT_CLOSE( array, e2 );
        array.resize(1,1,3);
        #if 0
        array = {
            {
                {1,3,5}
            }
        };
        #else
        {
            double a[1][1][3] = {
                {
                    {1,3,5}
                }
            };
            array = a;
        }
        #endif
        double e3[1][1][3] = {
            {
                {1,3,5}
            }
        };
        NMTOOLS_ASSERT_CLOSE( array, e3 );
        array(0,0,0) = 4;
        // @note no matching call
        // array(0,0) = 4;
        NMTOOLS_ASSERT_CLOSE( array(0,0,0), 4 );
        array.at({0,0,0}) = 4;
        NMTOOLS_ASSERT_CLOSE( array.at({0,0,0}), 4 );
    }
    
    // TODO: fix
    #if 0
    {
        auto array = na::hybrid_ndarray({
            {
                {1,2,3},
                {4,5,6}
            }
        });
        using array_t = decltype(array);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_resizable, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_hybrid_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, array_t );
        NMTOOLS_STATIC_CHECK_IS_SAME( meta::get_element_type_t<array_t>, int );

        double expected[1][2][3] = {
            {
                {1,2,3},
                {4,5,6}
            }
        };
        NMTOOLS_ASSERT_EQUAL( nm::shape(array), nm::shape(expected) );
        NMTOOLS_ASSERT_CLOSE( array, expected );
    }
    #endif
}