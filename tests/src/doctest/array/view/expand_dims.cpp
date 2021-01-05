#include "nmtools/array/view/expand_dims.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;

TEST_CASE("expand_dims(raw(6)->(1x6))" * doctest::test_suite("view::expand_dims"))
{
    double array[6] = {1,2,3,4,5,6};
    double expected[1][6] = {{1,2,3,4,5,6}};
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(raw(6)->(6x1))" * doctest::test_suite("view::expand_dims"))
{
    double array[6] = {1,2,3,4,5,6};
    auto axis = std::array{1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[6][1] = {
        {1},{2},{3},{4},{5},{6}
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(raw(6)->(1x1x6))" * doctest::test_suite("view::expand_dims"))
{
    double array[6] = {1,2,3,4,5,6};
    auto axis = std::array{0,1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,1,6};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][1][6] = {
        {
            {1,2,3,4,5,6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(raw(6)->(1x6x1))" * doctest::test_suite("view::expand_dims"))
{
    double array[6] = {1,2,3,4,5,6};
    auto axis = std::array{0,2};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][6][1] = {
        {
            {1},{2},{3},{4},{5},{6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(vector(6)->(1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::vector{1,2,3,4,5,6};
    double expected[1][6] = {{1,2,3,4,5,6}};
    {
        auto axis = std::vector{0};
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
    {
        auto axis = 0;
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
}

TEST_CASE("expand_dims(vector(6)->(6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::vector{1,2,3,4,5,6};
    auto axis = std::vector{1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[6][1] = {
        {1},{2},{3},{4},{5},{6}
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(vector(6)->(1x1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::vector{1,2,3,4,5,6};
    auto axis = std::vector{0,1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,1,6};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][1][6] = {
        {
            {1,2,3,4,5,6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(vector(6)->(1x6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::vector{1,2,3,4,5,6};
    auto axis = std::vector{0,2};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][6][1] = {
        {
            {1},{2},{3},{4},{5},{6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(array(6)->(1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::array{1,2,3,4,5,6};
    double expected[1][6] = {{1,2,3,4,5,6}};
    {
        auto axis = std::array{0};
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
    {
        auto axis = 0;
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
}

TEST_CASE("expand_dims(array(6)->(6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::array{1,2,3,4,5,6};
    auto axis = std::array{1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[6][1] = {
        {1},{2},{3},{4},{5},{6}
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(array(6)->(1x1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::array{1,2,3,4,5,6};
    auto axis = std::array{0,1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,1,6};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][1][6] = {
        {
            {1,2,3,4,5,6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(array(6)->(1x6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = std::array{1,2,3,4,5,6};
    auto axis = std::array{0,2};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][6][1] = {
        {
            {1},{2},{3},{4},{5},{6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(fixed_vector(6)->(1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_vector{{1,2,3,4,5,6}};
    double expected[1][6] = {{1,2,3,4,5,6}};
    {
        auto axis = std::array{0};
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
    {
        auto axis = 0;
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
}

TEST_CASE("expand_dims(fixed_vector(6)->(6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_vector{{1,2,3,4,5,6}};
    auto axis = std::array{1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[6][1] = {
        {1},{2},{3},{4},{5},{6}
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(fixed_vector(6)->(1x1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_vector{{1,2,3,4,5,6}};
    auto axis = std::array{0,1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,1,6};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][1][6] = {
        {
            {1,2,3,4,5,6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(fixed_vector(6)->(1x6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_vector{{1,2,3,4,5,6}};
    auto axis = std::array{0,2};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][6][1] = {
        {
            {1},{2},{3},{4},{5},{6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(dynamic_vector(6)->(1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_vector({1,2,3,4,5,6});
    double expected[1][6] = {{1,2,3,4,5,6}};
    {
        auto axis = std::array{0};
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
    {
        auto axis = 0;
        auto squeezed = view::expand_dims(array,axis);
        using squeezed_t = decltype(squeezed);

        auto shape = std::array{1,6};
        NMTOOLS_ASSERT_EQUAL( squeezed.dim(), 2 );
        NMTOOLS_ASSERT_EQUAL( squeezed.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( squeezed, expected );
    }
}

TEST_CASE("expand_dims(dynamic_vector(6)->(6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_vector({1,2,3,4,5,6});
    auto axis = std::array{1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 2 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[6][1] = {
        {1},{2},{3},{4},{5},{6}
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(dynamic_vector(6)->(1x1x6))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_vector({1,2,3,4,5,6});
    auto axis = std::array{0,1};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,1,6};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][1][6] = {
        {
            {1,2,3,4,5,6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(dynamic_vector(6)->(1x6x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_vector({1,2,3,4,5,6});
    auto axis = std::array{0,2};
    auto array_ref = view::expand_dims(array,axis);
    using squeezed_t = decltype(array_ref);

    auto shape = std::array{1,6,1};
    NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

    double expected[1][6][1] = {
        {
            {1},{2},{3},{4},{5},{6}
        }
    };

    NMTOOLS_ASSERT_CLOSE( array_ref, expected );
}

TEST_CASE("expand_dims(raw(3x2)->(1x3x2))" * doctest::test_suite("view::expand_dims"))
{
    double array[3][2] = {
        {1,2},
        {3,4},
        {5,6}
    };
    double expected[1][3][2] = {
        {
            {1,2},
            {3,4},
            {5,6}
        }
    };
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(raw(3x2)->(3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    double array[3][2] = {
        {1,2},
        {3,4},
        {5,6}
    };
    double expected[3][1][2] = {
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    };
    {
        auto axis = std::array{1};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 1;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(raw(3x2)->(3x2x1))" * doctest::test_suite("view::expand_dims"))
{
    double array[3][2] = {
        {1,2},
        {3,4},
        {5,6}
    };
    double expected[3][2][1] = {
        {
            {1},
            {2}
        },
        {
            {3},
            {4}
        },
        {
            {5},
            {6}
        }
    };
    {
        auto axis = std::array{2};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 2;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(array(3x2)->(1x3x2))" * doctest::test_suite("view::expand_dims"))
{
    std::array<std::array<double,2>,3> array = {{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[1][3][2] = {
        {
            {1,2},
            {3,4},
            {5,6}
        }
    };
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(array(3x2)->(3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    std::array<std::array<double,2>,3> array = {{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[3][1][2] = {
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    };
    {
        auto axis = std::array{1};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 1;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(array(3x2)->(3x2x1))" * doctest::test_suite("view::expand_dims"))
{
    std::array<std::array<double,2>,3> array = {{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[3][2][1] = {
        {
            {1},
            {2}
        },
        {
            {3},
            {4}
        },
        {
            {5},
            {6}
        }
    };
    {
        auto axis = std::array{2};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 2;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(vector(3x2)->(1x3x2))" * doctest::test_suite("view::expand_dims"))
{
    std::vector<std::vector<double>> array = {
        {1,2},
        {3,4},
        {5,6}
    };
    double expected[1][3][2] = {
        {
            {1,2},
            {3,4},
            {5,6}
        }
    };
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(vector(3x2)->(3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    std::vector<std::vector<double>> array = {
        {1,2},
        {3,4},
        {5,6}
    };
    double expected[3][1][2] = {
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    };
    {
        auto axis = std::array{1};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 1;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(vector(3x2)->(3x2x1))" * doctest::test_suite("view::expand_dims"))
{
    std::vector<std::vector<double>> array = {
        {1,2},
        {3,4},
        {5,6}
    };
    double expected[3][2][1] = {
        {
            {1},
            {2}
        },
        {
            {3},
            {4}
        },
        {
            {5},
            {6}
        }
    };
    {
        auto axis = std::array{2};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 2;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(fixed_matrix(3x2)->(1x3x2))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_matrix{{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[1][3][2] = {
        {
            {1,2},
            {3,4},
            {5,6}
        }
    };
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(fixed_matrix(3x2)->(3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_matrix{{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[3][1][2] = {
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    };
    {
        auto axis = std::array{1};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 1;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(fixed_matrix(3x2)->(3x2x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_matrix{{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[3][2][1] = {
        {
            {1},
            {2}
        },
        {
            {3},
            {4}
        },
        {
            {5},
            {6}
        }
    };
    {
        auto axis = std::array{2};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 2;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(dynamic_matrix(3x2)->(1x3x2))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_matrix{{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[1][3][2] = {
        {
            {1,2},
            {3,4},
            {5,6}
        }
    };
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(dynamic_matrix(3x2)->(3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_matrix{{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[3][1][2] = {
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    };
    {
        auto axis = std::array{1};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 1;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(dynamic_matrix(3x2)->(3x2x1))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_matrix{{
        {1,2},
        {3,4},
        {5,6}
    }};
    double expected[3][2][1] = {
        {
            {1},
            {2}
        },
        {
            {3},
            {4}
        },
        {
            {5},
            {6}
        }
    };
    {
        auto axis = std::array{2};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 2;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{3,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 3 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(raw(3x1x2)->(1x3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    double array[3][1][2] = {
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    };
    double expected[1][3][1][2] = {{
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    }};
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 4 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 4 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(fixed_ndarray(3x1x2)->(1x3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::fixed_ndarray{{
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    }};
    double expected[1][3][1][2] = {{
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    }};
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 4 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 4 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(fixed_ndarray(3x1x1x2)->(1x3x1x2x1))" * doctest::test_suite("view::expand_dims"))
{
    {
        auto array = na::fixed_ndarray{{
            {
                {
                    {1,2},
                }
            },
            {
                {
                    {3,4},
                }
            },
            {
                {
                {5,6}
                }
            }
        }};
        double expected[1][3][1][1][2][1] = {{
            {
                {
                    {{1},{2}},
                }
            },
            {
                {
                    {{3},{4}},
                }
            },
            {
                {
                    {{5},{6}}
                }
            }
        }};
        auto axis = std::array{0,5};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,1,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 6 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(dynamic_ndarray(3x1x2)->(1x3x1x2))" * doctest::test_suite("view::expand_dims"))
{
    auto array = na::dynamic_ndarray{{
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    }};
    double expected[1][3][1][2] = {{
        {
            {1,2},
        },
        {
            {3,4},
        },
        {
            {5,6}
        }
    }};
    {
        auto axis = std::array{0};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 4 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
    {
        auto axis = 0;
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,2};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 4 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}

TEST_CASE("expand_dims(dynamic_ndarray(3x1x1x2)->(1x3x1x2x1))" * doctest::test_suite("view::expand_dims"))
{
    {
        // clang complains that this is ambiguous, gcc works fine
        // note: candidate constructor [with Rows = 3, Cols = 1]
        // note: candidate constructor [with Shape1 = 3, Shape2 = 1, Shape3 = 1, Shape4 = 2]
        // auto array = na::dynamic_ndarray{{
        //     {
        //         {
        //             {1,2},
        //         }
        //     },
        //     {
        //         {
        //             {3,4},
        //         }
        //     },
        //     {
        //         {
        //             {5,6}
        //         }
        //     }
        // }};
        double initializer[3][1][1][2] = {
            {
                {
                    {1,2},
                }
            },
            {
                {
                    {3,4},
                }
            },
            {
                {
                    {5,6}
                }
            }
        };
        // note that initializer must be moved
        auto array = na::dynamic_ndarray{std::move(initializer)};
        double expected[1][3][1][1][2][1] = {{
            {
                {
                    {{1},{2}},
                }
            },
            {
                {
                    {{3},{4}},
                }
            },
            {
                {
                    {{5},{6}}
                }
            }
        }};
        auto axis = std::array{0,5};
        auto array_ref = view::expand_dims(array,axis);
        using squeezed_t = decltype(array_ref);

        auto shape = std::array{1,3,1,1,2,1};
        NMTOOLS_ASSERT_EQUAL( array_ref.dim(), 6 );
        NMTOOLS_ASSERT_EQUAL( array_ref.shape(), shape );

        NMTOOLS_ASSERT_CLOSE( array_ref, expected );
    }
}