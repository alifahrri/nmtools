#include "nmtools/array/view/mutable_slice.hpp"
#include "nmtools/array/array/copy.hpp"
#include "nmtools/testing/data/array/slice.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

NMTOOLS_TESTING_DECLARE_CASE(array, slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int rhs[2][1][2] = {
            {{12,13}},

            {{14,15}},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int modified[2][3][2] = {
            {
                {12,13},
                { 2, 3},
                { 4, 5},
            },
            {
                {14,15},
                { 8, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int rhs[2][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17},
            },
            {
                {18,19},
                {20,21},
                {22,23},
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int modified[2][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17},
            },
            {
                {18,19},
                {20,21},
                {22,23},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int rhs[1][1][2] = {{{12,13}}};
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int modified[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {12,13},
                { 8, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int rhs[1][1][2] = {{{12,13}}};
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        using case3::expect::modified;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int rhs[2][2][1] = {
            {
                {12},
                {13},
            },
            {
                {14},
                {15},
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int modified[2][3][2] = {
            {
                {12,1},
                {13,3},
                { 4,5},
            },
            {
                {14, 7},
                {15, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int rhs[2][1] = {
            {12},
            {13},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int modified[2][3][2] = {
            {
                {12,1},
                { 2,3},
                { 4,5},
            },
            {
                {13,7},
                { 8,9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int rhs[2][1] = {
            {12},
            {13},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int modified[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {12,7},
                {13,9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int rhs[2][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17},
            },
            {
                {18,19},
                {20,21},
                {22,23}
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int modified[2][3][2] = {
            {
                {18,19},
                {20,21},
                {22,23}
            },
            {
                {12,13},
                {14,15},
                {16,17},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using case8::args::rhs;
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int modified[2][3][2] = {
            {
                {16,17},
                {14,15},
                {12,13},
            },
            {
                {22,23},
                {20,21},
                {18,19},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using case8::args::rhs;
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int modified[2][3][2] = {
            {
                {19,18},
                {21,20},
                {23,22},
            },
            {
                {13,12},
                {15,14},
                {17,16},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int rhs[2][2] = {
            {12,13},
            {14,15}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int modified[4][2] = {
            {12,13},
            { 2, 3},
            {14,15},
            { 6, 7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using case11::args::rhs;
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        using case11::expect::modified;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int rhs[2][1] = {
            {12},
            {13},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int modified[4][2] = {
            {0,12},
            {2, 3},
            {4,13},
            {6, 7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        using case13::args::rhs;
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        using case13::expect::modified;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int rhs[2][1] = {
            {12},
            {13},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int modified[4][2] = {
            {0, 1},
            {2,13},
            {4, 5},
            {6,12},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using case15::args::rhs;
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        using case15::expect::modified;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int rhs[1][1] = {{12}};
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int modified[4][2] = {
            {0, 1},
            {2, 3},
            {4, 5},
            {6,12},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int rhs[1][1] = {{12}};
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int modified[4][2] = {
            {0, 1},
            {2,12},
            {4, 5},
            {6, 7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int rhs[2][1] = {
            {12},
            {13}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int modified[4][2] = {
            {0,13},
            {2, 3},
            {4,12},
            {6, 7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int rhs[4][1] = {
            {12},
            {13},
            {14},
            {15}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int modified[4][2] = {
            {0,12},
            {2,13},
            {4,14},
            {6,15},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int rhs[2][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17},
            },
            {
                {18,19},
                {20,21},
                {22,23},
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int modified[2][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17},
            },
            {
                {18,19},
                {20,21},
                {22,23},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int rhs[2][3][1] = {
            {
                {12},
                {13},
                {14}
            },
            {
                {15},
                {16},
                {17}
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int modified[2][3][2] = {
            {
                {12,1},
                {13,3},
                {14,5},
            },
            {
                {15, 7},
                {16, 9},
                {17,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        using case22::args::rhs;
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        using case22::expect::modified;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int rhs[1][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17}
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int modified[2][3][2] = {
            {
                {12,13},
                {14,15},
                {16,17},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline int rhs[3][2] = {
            {12,13},
            {14,15},
            {16,17}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        using case24::expect::modified;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline int rhs[2][3] = {
            {12,13,14},
            {15,16,17},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int modified[2][3][2] = {
            {
                {12,1},
                {13,3},
                {14,5},
            },
            {
                {15, 7},
                {16, 9},
                {17,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int rhs[3] = {12,13,14};
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int modified[2][3][2] = {
            {
                {12,1},
                {13,3},
                {14,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int rhs[2][1][3] = {
            {
                {12,13,14},
            },
            {
                {15,16,17},
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {12,1},
                    {13,3},
                    {14,5},
                }
            },
            {
                {
                    {15, 7},
                    {16, 9},
                    {17,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline int rhs[2][1] = {
            {12},
            {13}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    { 0,1},
                    {12,3},
                    { 4,5},
                }
            },
            {
                {
                    { 6, 7},
                    {13, 9},
                    {10,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        inline int rhs[1][3] = {
            {12,13,14}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {12, 7},
                    {13, 9},
                    {14,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        inline int rhs[2][2] = {
            {12,13},
            {14,15},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        inline int modified[2][3][2] = {
            {
                { 0, 1},
                { 2, 3},
                {13,12},
            },
            {
                { 6, 7},
                { 8, 9},
                {15,14},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        inline int rhs[2][2] = {
            {12,13},
            {14,15},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        inline int modified[2][3][2] = {
            {
                { 0, 1},
                {13,12},
                { 4, 5},
            },
            {
                { 6, 7},
                {15,14},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        inline int rhs[3] = {12,13,14};
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        inline int modified[2][3][2] = {
            {
                {0,12},
                {2,13},
                {4,14},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case34)
    {
        inline int rhs[2][1][3] = {
            {
                {12,13,14},
            },
            {
                {15,16,17},
            }
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case34)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {0,12},
                    {2,13},
                    {4,14},
                }
            },
            {
                {
                    { 6,15},
                    { 8,16},
                    {10,17},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case35)
    {
        inline int rhs[2][1] = {
            {12},
            {13},
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case35)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    { 0,1},
                    { 2,3},
                    {12,5},
                }
            },
            {
                {
                    { 6, 7},
                    { 8, 9},
                    {13,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case36)
    {
        inline int rhs[1][3] = {
            {12,13,14}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case36)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {12, 7},
                    {13, 9},
                    {14,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case37)
    {
        inline int rhs[1][3] = {
            {12,13,14}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case37)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {14, 7},
                    {13, 9},
                    {12,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case38)
    {
        inline int rhs[1][3] = {
            {12,13,14}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case38)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    { 6,12},
                    { 8,13},
                    {10,14},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_EXPECT(case39)
    {
        inline int rhs[1][2] = {
            {12,13}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case39)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    { 6, 7},
                    {13, 9},
                    {12,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case40)
    {
        inline int rhs[1][2] = {
            {12,13}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case40)
    {
        inline int modified[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {12, 7},
                    {13, 9},
                    {10,11},
                }
            }
        };
    }
}

#define RUN_mutable_slice_impl(...) \
nm::view::mutable_slice(__VA_ARGS__);

#define RUN_apply_mutable_slice_impl(...) \
nm::view::apply_mutable_slice(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs mutable_slice fn to callable lambda
#define RUN_mutable_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("mutable_slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_mutable_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#define RUN_apply_mutable_slice(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("apply_mutable_slice-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_apply_mutable_slice_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_mutable_slice(case_name, ...) \
RUN_mutable_slice_impl(__VA_ARGS__);
#define RUN_apply_mutable_slice(case_name, ...) \
RUN_apply_mutable_slice_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SLICE_SUBCASE(case_name, input, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, slice, case_name); \
    using namespace args; \
    auto input_ = na::copy(input); \
    auto result = RUN_mutable_slice(case_name, input_, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define MUTABLE_SLICE_SUBCASE(case_name, input, rhs, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, slice, case_name); \
    using namespace args; \
    auto input_ = na::copy(array); \
    auto result = RUN_mutable_slice(case_name, input_, __VA_ARGS__ ); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
    result = rhs; \
    NMTOOLS_ASSERT_EQUAL( input_, expect::modified ); \
}

#define APPLY_MUTABLE_SLICE_SUBCASE(case_name, input, rhs, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, slice, case_name); \
    using namespace args; \
    auto input_ = na::copy(array); \
    auto result = RUN_apply_mutable_slice(case_name, input_, __VA_ARGS__ ); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
    result = rhs; \
    NMTOOLS_ASSERT_EQUAL( input_, expect::modified ); \
}

TEST_CASE("mutable_slice(case1)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case1,   array,   rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case1, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case1, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case1, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case1, array_h, rhs_h, slice0, slice1, slice2);

    APPLY_MUTABLE_SLICE_SUBCASE(case1,   array, rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case1,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case1,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case1, array_h, rhs_h, dslices);
}

TEST_CASE("mutable_slice(case2)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case2,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case2, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case2, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case2, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case2, array_h, rhs_h, slice0, slice1, slice2);

    APPLY_MUTABLE_SLICE_SUBCASE(case2,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case2,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case2,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case2, array_h, rhs_h, dslices);
}

TEST_CASE("mutable_slice(case3)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case3,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case3, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case3, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case3, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case3, array_h, rhs_h, slice0, slice1, slice2);

    APPLY_MUTABLE_SLICE_SUBCASE(case3,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case3,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case3,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case3, array_h, rhs_h, dslices);
}

TEST_CASE("mutable_slice(case4)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case4,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case4, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case4, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case4, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case4, array_h, rhs_h, slice0, slice1, slice2);

    APPLY_MUTABLE_SLICE_SUBCASE(case4,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case4,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case4,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case4, array_h, rhs_h, dslices);
}

TEST_CASE("mutable_slice(case5)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case5,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case5, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case5, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case5, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case5, array_h, rhs_h, slice0, slice1, slice2);

    APPLY_MUTABLE_SLICE_SUBCASE(case5,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_h, rhs_h, slices);

// TODO: fix shape_dynamic_slice for negative stop
#if 0
    APPLY_MUTABLE_SLICE_SUBCASE(case5,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_h, rhs_h, dslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case5,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case5, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case6)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case6,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case6, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case6, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case6, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case6, array_h, rhs_h, slice0, slice1, slice2);

// TODO: fix negative stop
#if 0
    APPLY_MUTABLE_SLICE_SUBCASE(case6,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case6,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case6,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case6, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case7)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case7,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case7, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case7, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case7, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case7, array_h, rhs_h, slice0, slice1, slice2);

// TODO: fix shape_dynamic slice for negative stop
#if 0
    APPLY_MUTABLE_SLICE_SUBCASE(case7,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case7,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case7,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case7, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case8)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case8,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case8, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case8, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case8, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case8, array_h, rhs_h, slice0, slice1, slice2);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case8,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case8,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case8,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case8, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case9)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case9,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case9, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case9, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case9, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case9, array_h, rhs_h, slice0, slice1, slice2);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case9,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case9,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case9,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case9, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case10)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case10,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case10, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case10, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case10, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case10, array_h, rhs_h, slice0, slice1, slice2);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case10,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case10,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case10,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case10, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case11)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case11,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case11, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case11, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case11, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case11, array_h, rhs_h, slice0, slice1);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case11,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case11,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case11,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case11, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case12)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case12,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case12, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case12, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case12, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case12, array_h, rhs_h, slice0, slice1);
}

TEST_CASE("mutable_slice(case13)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case13,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case13, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case13, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case13, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case13, array_h, rhs_h, slice0, slice1);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case13,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case13,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case13,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case13, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case14)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case14,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case14, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case14, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case14, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case14, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case14,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case14,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case14,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case14, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case15)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case15,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case15, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case15, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case15, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case15, array_h, rhs_h, slice0, slice1);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case15,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case15,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case15,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case15, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case16)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case16,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case16, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case16, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case16, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case16, array_h, rhs_h, slice0, slice1);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case16,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case16,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case16,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case16, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case17)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case17,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case17, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case17, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case17, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case17, array_h, rhs_h, slice0, slice1);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case17,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case17,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case17,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case17, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case18)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case18,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case18, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case18, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case18, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case18, array_h, rhs_h, slice0, slice1);

#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case18,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case18,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case18,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case18, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case19)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case19,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case19, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case19, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case19, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case19, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case19,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case19,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case19,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case19, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case20)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case20,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case20, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case20, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case20, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case20, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case20,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case20,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case20,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case20, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case21)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case21,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case21, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case21, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case21, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case21, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case21,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case21,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case21,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case21, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case22)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case22,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case22, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case22, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case22, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case22, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case22,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case22,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case22,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case22, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case23)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case23,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case23, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case23, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case23, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case23, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case23,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case23,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case23,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case23, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case24)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case24,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case24, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case24, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case24, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case24, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case24,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case24,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case24,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case24, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case25)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case25,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case25, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case25, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case25, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case25, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case25,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case25,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case25,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case25, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case26)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case26,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case26, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case26, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case26, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case26, array_h, rhs_h, slice0, slice1);
#if 1
    APPLY_MUTABLE_SLICE_SUBCASE(case26,   array,   rhs, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_a, rhs_a, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_f, rhs_f, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_d, rhs_d, slices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_h, rhs_h, slices);

    APPLY_MUTABLE_SLICE_SUBCASE(case26,   array,   rhs, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_a, rhs_a, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_f, rhs_f, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_d, rhs_d, aslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_h, rhs_h, aslices);

    APPLY_MUTABLE_SLICE_SUBCASE(case26,   array,   rhs, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_a, rhs_a, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_f, rhs_f, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_d, rhs_d, dslices);
    APPLY_MUTABLE_SLICE_SUBCASE(case26, array_h, rhs_h, dslices);
#endif
}

TEST_CASE("mutable_slice(case27)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case27,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case27, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case27, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case27, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case27, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case28)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case28,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case28, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case28, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case28, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case28, array_h, rhs_h, slice0, slice1);
}

TEST_CASE("mutable_slice(case29)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case29,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case29, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case29, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case29, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case29, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case30)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case30,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case30, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case30, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case30, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case30, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case31)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case31,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case31, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case31, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case31, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case31, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case32)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case32,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case32, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case32, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case32, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case32, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case33)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case33,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case33, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case33, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case33, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case33, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case34)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case34,   array, rhs, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case34, array_a, rhs_a, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case34, array_f, rhs_f, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case34, array_d, rhs_d, slice0, slice1);
    MUTABLE_SLICE_SUBCASE(case34, array_h, rhs_h, slice0, slice1);
}

TEST_CASE("mutable_slice(case35)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case35,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case35, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case35, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case35, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case35, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case36)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case36,   array, rhs, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case36, array_a, rhs_a, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case36, array_f, rhs_f, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case36, array_d, rhs_d, slice0, slice1, slice2);
    MUTABLE_SLICE_SUBCASE(case36, array_h, rhs_h, slice0, slice1, slice2);
}

TEST_CASE("mutable_slice(case37)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case37,   array, rhs, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case37, array_a, rhs_a, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case37, array_f, rhs_f, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case37, array_d, rhs_d, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case37, array_h, rhs_h, slice0, slice1, slice2, slice3);
}

TEST_CASE("mutable_slice(case38)" * doctest::test_suite("view::mutable_slice"))
{
    MUTABLE_SLICE_SUBCASE(case38,   array, rhs, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case38, array_a, rhs_a, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case38, array_f, rhs_f, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case38, array_d, rhs_d, slice0, slice1, slice2, slice3);
    MUTABLE_SLICE_SUBCASE(case38, array_h, rhs_h, slice0, slice1, slice2, slice3);
}