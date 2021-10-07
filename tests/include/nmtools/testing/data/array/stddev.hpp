#ifndef NMTOOLS_TESTING_DATA_ARRAY_STDDEV_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_STDDEV_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#ifndef PLATFORMIO
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);
#else
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_h = cast(name, kind::hybrid);
#endif // PLATFORMIO


NMTOOLS_TESTING_DECLARE_CASE(array, stddev)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = None;
        inline auto ddof = 0;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = 3.452052529534663;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = None;
        inline auto ddof = 0;
        inline auto keepdims = True;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][1][1] = {{{3.452052529534663}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = 0;
        inline auto ddof = 0;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[3][2] = {
            {3.,3.},
            {3.,3.},
            {3.,3.},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = 1;
        inline auto ddof = 0;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[2][2] = {
            {1.63299316, 1.63299316},
            {1.63299316, 1.63299316},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = 2;
        inline auto ddof = 0;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[2][3] = {
            {0.5, 0.5, 0.5},
            {0.5, 0.5, 0.5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = 2;
        inline auto ddof = 1;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline float result[2][3] = {
            {0.70710678, 0.70710678, 0.70710678},
            {0.70710678, 0.70710678, 0.70710678},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = 2;
        inline auto ddof = 1;
        inline auto keepdims = True;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline float result[2][3][1] = {
            {
                {0.70710678},
                {0.70710678},
                {0.70710678}
            },
            {
                {0.70710678},
                {0.70710678},
                {0.70710678}
            },
        };
    }

    using namespace ::nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = 2_ct;
        inline auto ddof = 1;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline float result[2][3] = {
            {0.70710678, 0.70710678, 0.70710678},
            {0.70710678, 0.70710678, 0.70710678},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int array[2][3][2] = {
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
        inline int axis[2] = {0,1};
        inline auto ddof = 1;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline float result[2] = {3.74165739, 3.74165739};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int array[2][3][2] = {
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
        inline int axis[2] = {0,2};
        inline auto ddof = 1;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline float result[3] = {3.51188458, 3.51188458, 3.51188458};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int array[2][3][2] = {
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
        inline int axis[2] = {0,2};
        inline auto ddof = 1;
        inline auto keepdims = True;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline float result[1][3][1] = {
            {
                {3.51188458},
                {3.51188458},
                {3.51188458},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int array[2][3][2] = {
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
        inline int axis[2] = {0,2};
        inline auto ddof = 1;
        inline auto keepdims = true;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline float result[1][3][1] = {
            {
                {3.51188458},
                {3.51188458},
                {3.51188458},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int array[2][3][2] = {
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
        inline int axis[2] = {0,2};
        inline auto ddof = 1;
        inline auto keepdims = false;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline float result[3] = {3.51188458, 3.51188458, 3.51188458};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = std::tuple{0_ct,2_ct};
        inline auto ddof = 1;
        inline auto keepdims = False;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline float result[3] = {3.51188458, 3.51188458, 3.51188458};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = std::tuple{0_ct,2_ct};
        inline auto ddof = 1;
        inline auto keepdims = True;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline float result[1][3][1] = {
            {
                {3.51188458},
                {3.51188458},
                {3.51188458},
            }
        };
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = std::tuple{0_ct,2_ct};
        inline auto ddof = 1;
        inline auto keepdims = false;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline float result[3] = {3.51188458, 3.51188458, 3.51188458};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int array[2][3][2] = {
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
        inline auto axis = std::tuple{0_ct,2_ct};
        inline auto ddof = 1;
        inline auto keepdims = true;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline float result[1][3][1] = {
            {
                {3.51188458},
                {3.51188458},
                {3.51188458},
            }
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_STDDEV_HPP