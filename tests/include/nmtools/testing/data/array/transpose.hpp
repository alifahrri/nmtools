#ifndef NMTOOLS_TESTING_DATA_ARRAY_TRANSPOSE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TRANSPOSE_HPP

#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/testing/testing.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
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

NMTOOLS_TESTING_DECLARE_CASE(transpose)
{
    using namespace nmtools::literals;
    using nmtools::utils::isclose;
    using nmtools::utils::isequal;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double array[3] = {1,2,3};
        CAST_ARRAYS(array)
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape_[1] = {3};
        inline auto shape = cast<int>(shape_);
        inline double expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline double array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        CAST_ARRAYS(array)
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape_[2] = {3,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline double array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        CAST_ARRAYS(array)
        inline int axes[2]  = {0,1};
        inline auto axes_ct = std::tuple{0_ct,1_ct};
        CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape_[2] = {2,3};
        inline auto shape = cast<int>(shape_);
        inline double expected[2][3] = {
            {1,2,3},
            {3,4,5}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline double array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        CAST_ARRAYS(array)
        inline int axes[2]  = {1,0};
        inline auto axes_ct = std::tuple{1_ct,0_ct};
        CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape_[2] = {3,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline double array[2][2][3] = {
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        };
        CAST_ARRAYS(array)
        inline auto axes    = None;
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape_[3] = {3,2,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[3][2][2] = {
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
        inline double array[2][2][3] = {
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        };
        CAST_ARRAYS(array)
        inline int axes[3]  = {2,0,1};
        inline auto axes_ct = std::tuple{2_ct,0_ct,1_ct};
        CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape_[3] = {3,2,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[3][2][2] = {
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
        inline double array[2][2][3] = {
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        };
        CAST_ARRAYS(array)
        inline int axes[3]  = {1,2,0};
        inline auto axes_ct = std::tuple{1_ct,2_ct,0_ct};
        CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape_[3] = {2,3,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[2][3][2] = {
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
        inline double array[2][2][1][3] = {
            {
                {
                    {1.,2.,3.},
                },
                {
                    {3.,4.,5.}
                }
            },
            {
                {
                    {5.,6.,7.},
                },
                {
                    {7.,8.,9.}
                }
            },
        };
        CAST_ARRAYS(array)
        inline auto axes    = None;
        inline auto axes_a  = None;
        inline auto axes_ct = None;
        inline auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape_[4] = {3,1,2,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[3][1][2][2] = {
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
        inline double array[2][2][1][3] = {
            {
                {
                    {1.,2.,3.},
                },
                {
                    {3.,4.,5.}
                }
            },
            {
                {
                    {5.,6.,7.},
                },
                {
                    {7.,8.,9.}
                }
            },
        };
        CAST_ARRAYS(array)
        inline int axes[4]  = {0,1,3,2};
        inline auto axes_ct = std::tuple{0_ct,1_ct,3_ct,2_ct};
        CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape_[4] = {2,2,3,1};
        inline auto shape = cast<int>(shape_);
        inline double expected[2][2][3][1] = {
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
        inline double array[2][2][1][3] = {
            {
                {
                    {1.,2.,3.},
                },
                {
                    {3.,4.,5.}
                }
            },
            {
                {
                    {5.,6.,7.},
                },
                {
                    {7.,8.,9.}
                }
            },
        };
        CAST_ARRAYS(array)
        inline int axes[4]  = {1,0,3,2};
        inline auto axes_ct = std::tuple{1_ct,0_ct,3_ct,2_ct};
        CAST_ARRAYS(axes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int shape_[4] = {2,2,3,1};
        inline auto shape = cast<int>(shape_);
        inline double expected[2][2][3][1] = {
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

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_TRANSPOSE_HPP