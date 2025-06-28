#ifndef NMTOOLS_TESTING_DATA_ARRAY_TRANSPOSE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TRANSPOSE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(transpose)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t array[3] = {1,2,3};
        NMTOOLS_CAST_ARRAYS(array)
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape_[1] = {3};
        inline int8_t expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        NMTOOLS_CAST_ARRAYS(array)
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape_[2] = {3,2};
        inline int8_t expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int8_t array[2][2][3] = {
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        };
        NMTOOLS_CAST_ARRAYS(array)
        inline auto axes    = None;
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int8_t shape_[3] = {3,2,2};
        inline int8_t expected[3][2][2] = {
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

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int8_t array[2][2][1][3] = {
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
        NMTOOLS_CAST_ARRAYS(array)
        inline auto axes    = None;
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int8_t shape_[4] = {3,1,2,2};
        inline int8_t expected[3][1][2][2] = {
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

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int8_t array[2][2][1][3] = {
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
        NMTOOLS_CAST_ARRAYS(array)
        inline int8_t axes[4]  = {1,0,3,2};
        inline auto axes_ct = nmtools_tuple{1_ct,0_ct,3_ct,2_ct};
        inline auto axes_cl = nmtools_tuple{"1:[1]"_ct,"0:[1]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int8_t shape_[4] = {2,2,3,1};
        inline int8_t expected[2][2][3][1] = {
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

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        NMTOOLS_CAST_ARRAYS(array)
        inline int8_t axes[2]  = {0,1};
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t shape_[2] = {2,3};
        inline int8_t expected[2][3] = {
            {1,2,3},
            {3,4,5}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        NMTOOLS_CAST_ARRAYS(array)
        inline int8_t axes[2]  = {1,0};
        inline auto axes_ct = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t shape_[2] = {3,2};
        inline int8_t expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int8_t array[2][2][3] = {
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        };
        NMTOOLS_CAST_ARRAYS(array)
        inline int8_t axes[3]  = {2,0,1};
        inline auto axes_ct = nmtools_tuple{2_ct,0_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int8_t shape_[3] = {3,2,2};
        inline int8_t expected[3][2][2] = {
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
        inline int8_t array[2][2][3] = {
            {
                {1,2,3},
                {3,4,5}
            },
            {
                {5,6,7},
                {7,8,9}
            },
        };
        NMTOOLS_CAST_ARRAYS(array)
        inline int8_t axes[3]  = {1,2,0};
        inline auto axes_ct = nmtools_tuple{1_ct,2_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int8_t shape_[3] = {2,3,2};
        inline int8_t expected[2][3][2] = {
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
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int8_t array[2][2][1][3] = {
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
        NMTOOLS_CAST_ARRAYS(array)
        inline int8_t axes[4]  = {0,1,3,2};
        inline auto axes_ct = nmtools_tuple{0_ct,1_ct,3_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int8_t shape_[4] = {2,2,3,1};
        inline int8_t expected[2][2][3][1] = {
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
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TRANSPOSE_HPP