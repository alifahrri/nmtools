#ifndef NMTOOLS_TESTING_DATA_CONSTEXPR_TRANSPOSE_HPP
#define NMTOOLS_TESTING_DATA_CONSTEXPR_TRANSPOSE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(constexpr_transpose)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t array[3] = {1,2,3};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline auto axes_a  = None;
        constexpr inline auto axes_ct = None;
        constexpr inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t shape_[1] = {3};
        constexpr inline int8_t expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int8_t array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline auto axes_a  = None;
        constexpr inline auto axes_ct = None;
        constexpr inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int8_t shape_[2] = {3,2};
        constexpr inline int8_t expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int8_t array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline int8_t axes[2]  = {0,1};
        constexpr inline auto axes_ct = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int8_t shape_[2] = {2,3};
        constexpr inline int8_t expected[2][3] = {
            {1,2,3},
            {3,4,5}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int8_t array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline int8_t axes[2]  = {1,0};
        constexpr inline auto axes_ct = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int8_t shape_[2] = {3,2};
        constexpr inline int8_t expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int8_t array[2][2][3] = {
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline auto axes    = None;
        constexpr inline auto axes_a  = None;
        constexpr inline auto axes_ct = None;
        constexpr inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int8_t shape_[3] = {3,2,2};
        constexpr inline int8_t expected[3][2][2] = {
            {
                {1,5},
                {3,7},
            },
            {
                {2,6},
                {4,8},
            },
            {
                {3,7},
                {5,9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int8_t array[2][2][3] = {
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline int8_t axes[3]  = {2,0,1};
        constexpr inline auto axes_ct = nmtools_tuple{2_ct,0_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int8_t shape_[3] = {3,2,2};
        constexpr inline int8_t expected[3][2][2] = {
            {
                {1,3},
                {5,7},
            },
            {
                {2,4},
                {6,8},
            },
            {
                {3,5},
                {7,9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int8_t array[2][2][3] = {
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline int8_t axes[3]  = {1,2,0};
        constexpr inline auto axes_ct = nmtools_tuple{1_ct,2_ct,0_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int8_t shape_[3] = {2,3,2};
        constexpr inline int8_t expected[2][3][2] = {
            {
                {1,5},
                {2,6},
                {3,7}
            },
            {
                {3,7},
                {4,8},
                {5,9}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline int8_t array[2][2][1][3] = {
            {
                {
                    {1,2,3},
                },
                {
                    {3,4,5}
                }
            },
            {
                {
                    {5,6,7},
                },
                {
                    {7,8,9}
                }
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline auto axes    = None;
        constexpr inline auto axes_a  = None;
        constexpr inline auto axes_ct = None;
        constexpr inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline int8_t shape_[4] = {3,1,2,2};
        constexpr inline int8_t expected[3][1][2][2] = {
            {
                {
                    {1,5},
                    {3,7},
                }
            },
            {
                {
                    {2,6},
                    {4,8},
                }
            },
            {
                {
                    {3,7},
                    {5,9},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline int8_t array[2][2][1][3] = {
            {
                {
                    {1,2,3},
                },
                {
                    {3,4,5}
                }
            },
            {
                {
                    {5,6,7},
                },
                {
                    {7,8,9}
                }
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline int8_t axes[4]  = {0,1,3,2};
        constexpr inline auto axes_ct = nmtools_tuple{0_ct,1_ct,3_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline int8_t shape_[4] = {2,2,3,1};
        constexpr inline int8_t expected[2][2][3][1] = {
            {
                {
                    {1},
                    {2},
                    {3},
                },
                {
                    {3},
                    {4},
                    {5},
                }
            },
            {
                {
                    {5},
                    {6},
                    {7},
                },
                {
                    {7},
                    {8},
                    {9}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline int8_t array[2][2][1][3] = {
            {
                {
                    {1,2,3},
                },
                {
                    {3,4,5}
                }
            },
            {
                {
                    {5,6,7},
                },
                {
                    {7,8,9}
                }
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        constexpr inline int8_t axes[4]  = {1,0,3,2};
        constexpr inline auto axes_ct = nmtools_tuple{1_ct,0_ct,3_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline int8_t shape_[4] = {2,2,3,1};
        constexpr inline int8_t expected[2][2][3][1] = {
            {
                {
                    {1},
                    {2},
                    {3},
                },
                {
                    {5},
                    {6},
                    {7},
                }
            },
            {
                {
                    {3},
                    {4},
                    {5},
                },
                {
                    {7},
                    {8},
                    {9}
                }
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_CONSTEXPR_TRANSPOSE_HPP