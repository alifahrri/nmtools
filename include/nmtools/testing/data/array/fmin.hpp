#ifndef NMTOOLS_TESTING_DATA_ARRAY_FMIN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FMIN_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/constants.hpp" // Include for None, True, False
#include "nmtools/meta.hpp"      // Required for numeric_limits

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
namespace meta = nm::meta; // Alias for convenience

// Define a constant using nmtools::meta for the initial value for fmin
constexpr float fmin_initial = meta::numeric_limits<float>::max();

NMTOOLS_TESTING_DECLARE_CASE(view, fmin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0.f, 1.f, 2.f},
            {3.f, 4.f, 5.f},
            {6.f, 7.f, 8.f},
        };
        inline float b[3] = {0.F,1.f,NAN}; // Use float literals consistently
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::fmin(0.f,0.F), std::fmin(1.f,1.f), std::fmin(2.f,NAN)},
            {std::fmin(3.f,0.F), std::fmin(4.f,1.f), std::fmin(5.f,NAN)},
            {std::fmin(6.f,0.F), std::fmin(7.f,1.f), std::fmin(8.f,NAN)},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[3][3] = {
            {0.f, 1.f, 2.f},
            {3.f, 4.f, 5.f},
            {6.f, 7.f, 8.f},
        };
        inline float b = 1.f;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::fmin(0.f,1.f), std::fmin(1.f,1.f), std::fmin(2.f,1.f)},
            {std::fmin(3.f,1.f), std::fmin(4.f,1.f), std::fmin(5.f,1.f)},
            {std::fmin(6.f,1.f), std::fmin(7.f,1.f), std::fmin(8.f,1.f)},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_fmin)
{
    // Existing cases 1-17
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            {0.f, 1.f},
            {2.f, 3.f},
            {4.f, 5.f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,2};
        inline float result[2][2] = {
            {0.f, 1.f},
            {6.f, 7.f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,3};
        inline float result[2][3] = {
            {0.f, 2.f, 4.f},
            {6.f, 8.f, 10.f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {0,1};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[1] = {2};
        inline float result[2] = {0.f, 1.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {0,2};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[1] = {3};
        inline float result[3] = {0.f, 2.f, 4.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {1,2};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[1] = {2};
        inline float result[2] = {0.f, 6.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {1,2};
        inline auto dtype = nm::dtype_t<long int>{};
        inline auto initial = 5;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[1] = {2};
        inline long int result[2] = {0,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[3] = {1,3,2};
        inline float result[1][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 1;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[2] = {2,2};
        inline float result[2][2] = {
            {0.f, 1.f},
            {6.f, 7.f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 2;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int shape[3] = {2,3,1};
        inline float result[2][3][1] = {
            {{0.f},{2.f},{ 4.f}},
            {{6.f},{8.f},{10.f}}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {0,1};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int shape[1] = {2};
        inline float result[2] = {0.f, 1.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {0,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int shape[3] = {1,3,1};
        inline float result[1][3][1] = {
            {{0.f}, {2.f}, {4.f}}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto shape = None;
        inline float result = 0.f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = -1.0f;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto shape = None;
        inline float result = -1.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = -1.0f;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{-1.0f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = 1.5f;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline auto shape = None;
        inline float result = 0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = 1.5f;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{0.0f}}};
    }

    // New test cases for 'where' argument (mask)
    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = fmin_initial;
        inline auto keepdims = False;
        inline bool mask[2][3][2] = {
            {{true, false}, {true, true}, {false, true}},
            {{true, true}, {false, false}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            { 0.f, 7.f}, { 2.f, 3.f}, {10.f, 5.f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 1;
        inline auto dtype = None;
        inline auto initial = 100.0f;
        inline auto keepdims = True;
        inline bool mask[3][2] = { // Broadcastable mask
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int shape[3] = {2,1,2};
        inline float result[2][1][2] = {
            {{0.f, 3.f}},
            {{6.f, 9.f}},
        };
    }

     NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 2;
        inline auto dtype = None;
        inline auto initial = fmin_initial;
        inline auto keepdims = True;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, false}, {false, true}},
            {{true, false}, {true, true}, {true, false}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int shape[3] = {2,3,1};
        inline float result[2][3][1] = {
             {{0.f}, {2.f}, {5.f}},
             {{6.f}, {8.f}, {10.f}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {0,1};
        inline auto dtype = None;
        inline auto initial = fmin_initial;
        inline auto keepdims = False;
        inline bool mask[2][1][2] = {
            {{true, false}},
            {{false, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int shape[1] = {2};
        inline float result[2] = {0.f, 7.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = -1.0f;
        inline auto keepdims = False;
        inline bool mask[2][3][2] = {
            {{true, false}, {true, true}, {false, true}},
            {{true, true}, {false, false}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            {-1.f, -1.f}, {-1.f, -1.f}, {-1.f, -1.f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = fmin_initial;
        inline auto keepdims = False;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline auto shape = None;
        inline float result = 0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = fmin_initial;
        inline auto keepdims = True;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{0.0f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 1;
        inline auto dtype = None;
        inline auto initial = 5.5f;
        inline auto keepdims = True;
        inline bool mask[2][1][2] = {
            {{true, false}},
            {{false, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int shape[3] = {2,1,2};
        inline float result[2][1][2] = {
            {{0.f, 5.5f}},
            {{5.5f, 5.5f}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = -5.0f;
        inline auto keepdims = True;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, true}, {true, true}},
            {{true, true}, {true, true}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{-5.0f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline auto axis = None;
        inline auto dtype = None;
        inline auto initial = -5.0f;
        inline auto keepdims = False;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, true}, {true, true}},
            {{true, true}, {true, true}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline auto shape = None;
        inline float result = -5.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis[2] = {0, 2}; // Multiple axes
        inline auto dtype = None;
        inline auto initial = fmin_initial;
        inline auto keepdims = False;
        inline bool mask[2][3][1] = { // Broadcastable mask
            {{true}, {false}, {true}},
            {{false}, {true}, {true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int shape[1] = {3};
        inline float result[3] = {0.f, 8.f, 4.f};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_fmin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f}
            },
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0.f, 1.f},
                {0.f, 1.f},
                {0.f, 1.f}
            },
            {
                {6.f, 7.f},
                {6.f, 7.f},
                {6.f, 7.f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[2][3][2] = {
            {
                {0.f, 1.f},
                {2.f, 3.f},
                {4.f, 5.f},
            },
            {
                { 6.f,  7.f},
                { 8.f,  9.f},
                {10.f, 11.f},
            }
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0.f, 0.f},
                {2.f, 2.f},
                {4.f, 4.f}
            },
            {
                { 6.f,  6.f},
                { 8.f,  8.f},
                {10.f, 10.f}
            }
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_fmin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3] = {
            {0, 1, 2},
            {3, 4, 5}
        };
        inline int b[3] = { 6,  7, 8};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,3};
        inline int result[2][3][3] = {
            {
                {0, 0, 0},
                {1, 1, 1},
                {2, 2, 2}
            },
            {
                {3, 3, 3},
                {4, 4, 4},
                {5, 5, 5}
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FMIN_HPP
