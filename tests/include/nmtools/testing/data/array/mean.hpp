#ifndef NMTOOLS_TESTING_DATA_ARRAY_MEAN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MEAN_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(array, mean)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto shape  = None;
        inline auto result = 5.5f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            {2,3},
            {8,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[2] = {2,3};
        inline float result[2][3] = {
            {0.5f,2.5f, 4.5f},
            {6.5f,8.5f,10.5f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using namespace literals;
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{5.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{5.5f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto shape = None;
        inline float result = 5.5f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 1;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int shape[3] = {2,1,2};
        inline int result[2][1][2] = {
            {
                {2,3},
            },
            {
                {8,9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 2;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int shape[3] = {2,3,1};
        inline float result[2][3][1] = {
            {
                {0.5f},
                {2.5f},
                { 4.5f}
            },
            {
                {6.5f},
                {8.5f},
                {10.5f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using namespace literals;
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0_ct;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 1;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int shape[3] = {2,1,2};
        inline int result[2][1][2] = {
            {
                {2,3},
            },
            {
                {8,9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 2;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int shape[3] = {2,3,1};
        inline float result[2][3][1] = {
            {
                {0.5f},
                {2.5f},
                { 4.5f}
            },
            {
                {6.5f},
                {8.5f},
                {10.5f}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using namespace literals;
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0_ct;
        inline auto keepdims = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                {3,4},
                {5,6},
                {7,8}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 1;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            {2,3},
            {8,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 2;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int shape[2] = {2,3};
        inline float result[2][3] = {
            {0.5f,2.5f, 4.5f},
            {6.5f,8.5f,10.5f}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        using namespace literals;
        inline int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        CAST_ARRAYS(a)
        inline auto axis = 0_ct;
        inline auto keepdims = false;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            {3,4},
            {5,6},
            {7,8}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MEAN_HPP