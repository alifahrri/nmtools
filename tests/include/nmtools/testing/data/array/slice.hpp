#ifndef NMTOOLS_TESTING_DATA_ARRAY_SLICE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SLICE_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <tuple>

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

NMTOOLS_TESTING_DECLARE_CASE(array, slice)
{
    using std::tuple;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][1][2] = {
            {{0,1}},

            {{6,7}}
        };
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{1,2};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][1][2] = {{{6,7}}};
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{1,3};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][1][2] = {{{6,7}}};
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{0,2};
        inline auto slice2 = tuple{None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2][2][1] = {
            {
                {0},
                {2},
            },
            {
                {6},
                {8},
            }
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = 0;
        inline auto slice2 = tuple{None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2][1] = {
            {0},
            {6},
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = tuple{0,2};
        inline auto slice2 = tuple{None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[2][1] = {
            {6},
            {8},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2][3][2] = {
            {
                {6,7},
                {8,9},
                {10,11},
            },
            {
                {0,1},
                {2,3},
                {4,5},
            }
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None,-1};
        inline auto slice2 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[2][3][2] = {
            {
                {4,5},
                {2,3},
                {0,1},
            },
            {
                {10,11},
                {8,9},
                {6,7},
            }
        };
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
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[2][3][2] = {
            {
                {7,6},
                {9,8},
                {11,10},
            },
            {
                {1,0},
                {3,2},
                {5,4},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{None,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[2][2] = {
            {0,1},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{None,2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[2][2] = {
            {0,1},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{1,None};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[2][1] = {
            {1},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{1,None,2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[2][1] = {
            {1},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{None,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[2][1] = {
            {7},
            {3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{3,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[2][1] = {
            {7},
            {3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{3,None,2};
        inline auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int result[1][1] = {{7}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{1,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int result[1][1] = {{3}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{2,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int result[2][1] = {
            {5},
            {1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int array[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{1,None,4};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int result[4][1] = {
            {1},
            {3},
            {5},
            {7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = std::tuple{None,None};
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = tuple{None,Last};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int result[2][3][1] = {
            {
                {0},
                {2},
                {4},
            },
            {
                {6},
                {8},
                {10},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = tuple{0,Last};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int result[2][3][1] = {
            {
                {0},
                {2},
                {4},
            },
            {
                {6},
                {8},
                {10},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = tuple{0ul,Last};
        inline auto slice1 = Elipsis;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int result[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 0ul;
        inline auto slice1 = Elipsis;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int result[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int result[2][3] = {
            {0,2,4},
            {6,8,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 0;
        inline auto slice1 = Elipsis;
        inline auto slice2 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int result[3] = {0,2,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int result[2][1][3] = {
            {
                {0,2,4}
            },
            {
                {6,8,10}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = 1;
        inline auto slice2 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int result[2][1] = {
            {2},
            {8}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Elipsis;
        inline auto slice2 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        inline int result[1][3] = {
            {6,8,10}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = -1;
        inline auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        inline int result[2][2] = {
            {5,4},
            {11,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = -2;
        inline auto slice2 = tuple{None,None,-1};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        inline int result[2][2] = {
            {3,2},
            {9,8},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            }
        };
        inline auto slice0 = 0;
        inline auto slice1 = Elipsis;
        inline auto slice2 = -1;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        inline int result[3] = {1,3,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case34)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = -1;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case34)
    {
        inline int result[2][1][3] = {
            {
                {1,3,5},
            },
            {
                {7,9,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case35)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = Elipsis;
        inline auto slice1 = -1;
        inline auto slice2 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case35)
    {
        inline int result[2][1] = {
            {4},
            {10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case36)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = -1;
        inline auto slice1 = Elipsis;
        inline auto slice2 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case36)
    {
        inline int result[1][3] = {
            {6,8,10}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case37)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Elipsis;
        inline auto slice2 = tuple{None,None,-1};
        inline auto slice3 = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case37)
    {
        inline int result[1][3] = {
            {10,8,6}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case38)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    {6,7},
                    {8,9},
                    {10,11},
                }
            }
        };
        inline auto slice0 = 1;
        inline auto slice1 = Elipsis;
        inline auto slice2 = tuple{None,None,1};
        inline auto slice3 = 1;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case38)
    {
        inline int result[1][3] = {
            {7,9,11}
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_SLICE_HPP