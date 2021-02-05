/**
 * @file transpose.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for transpose view
 * @date 2020-10-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/constants.hpp"

#include "testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

using namespace nmtools::literals;
using nmtools::utils::isclose;
using nmtools::utils::isequal;
using nmtools::array::fixed_vector;
using nmtools::array::fixed_matrix;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_vector;
using nmtools::array::dynamic_matrix;
using nmtools::array::dynamic_ndarray;

NMTOOLS_TESTING_DECLARE_CASE(transpose)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        double array[3] = {1,2,3};
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        auto axes_a  = None;
        auto axes_ct = None;
        auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape_[1] = {3};
        auto shape = cast<int>(shape_);
        double expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        double array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        auto axes_a  = None;
        auto axes_ct = None;
        auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape_[2] = {3,2};
        auto shape = cast<int>(shape_);
        double expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        double array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        int axes[2]  = {0,1};
        auto axes_ct = std::tuple{0_ct,1_ct};
        auto axes_a  = cast<int>(axes);
        auto axes_v  = cast(axes,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape_[2] = {2,3};
        auto shape = cast<int>(shape_);
        double expected[2][3] = {
            {1,2,3},
            {3,4,5}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        double array[2][3] = {
            {1,2,3},
            {3,4,5}
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        int axes[2]  = {1,0};
        auto axes_ct = std::tuple{1_ct,0_ct};
        auto axes_a  = cast<int>(axes);
        auto axes_v  = cast(axes,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape_[2] = {3,2};
        auto shape = cast<int>(shape_);
        double expected[3][2] = {
            {1,3},
            {2,4},
            {3,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        double array[2][2][3] = {
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        auto axes_a  = None;
        auto axes_ct = None;
        auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape_[3] = {3,2,2};
        auto shape = cast<int>(shape_);
        double expected[3][2][2] = {
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
        double array[2][2][3] = {
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        int axes[3]  = {2,0,1};
        auto axes_ct = std::tuple{2_ct,0_ct,1_ct};
        auto axes_a  = cast<int>(axes);
        auto axes_v  = cast(axes,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape_[3] = {3,2,2};
        auto shape = cast<int>(shape_);
        double expected[3][2][2] = {
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
        double array[2][2][3] = {
            {
                {1.,2.,3.},
                {3.,4.,5.}
            },
            {
                {5.,6.,7.},
                {7.,8.,9.}
            },
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        int axes[3]  = {1,2,0};
        auto axes_ct = std::tuple{1_ct,2_ct,0_ct};
        auto axes_a  = cast<int>(axes);
        auto axes_v  = cast(axes,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape_[3] = {2,3,2};
        auto shape = cast<int>(shape_);
        double expected[2][3][2] = {
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
        double array[2][2][1][3] = {
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
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        auto axes_a  = None;
        auto axes_ct = None;
        auto axes_v  = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape_[4] = {3,1,2,2};
        auto shape = cast<int>(shape_);
        double expected[3][1][2][2] = {
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
        double array[2][2][1][3] = {
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
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        int axes[4]  = {0,1,3,2};
        auto axes_ct = std::tuple{0_ct,1_ct,3_ct,2_ct};
        auto axes_a  = cast<int>(axes);
        auto axes_v  = cast(axes,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int shape_[4] = {2,2,3,1};
        auto shape = cast<int>(shape_);
        double expected[2][2][3][1] = {
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
        double array[2][2][1][3] = {
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
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
        int axes[4]  = {1,0,3,2};
        auto axes_ct = std::tuple{1_ct,0_ct,3_ct,2_ct};
        auto axes_a  = cast<int>(axes);
        auto axes_v  = cast(axes,kind::nested_vec);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int shape_[4] = {2,2,3,1};
        auto shape = cast<int>(shape_);
        double expected[2][2][3][1] = {
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

#define TRANSPOSE_SUBCASE(case_name, array, axes) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( transpose, case_name ); \
    auto array_ref = view::transpose(args::array, args::axes); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("transpose(array)" * doctest::test_suite("view::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_a, axes_a );
    TRANSPOSE_SUBCASE( case2, array_a, axes_a );
    TRANSPOSE_SUBCASE( case3, array_a, axes_a );
    TRANSPOSE_SUBCASE( case4, array_a, axes_a );
    TRANSPOSE_SUBCASE( case5, array_a, axes_a );
    TRANSPOSE_SUBCASE( case6, array_a, axes_a );
    TRANSPOSE_SUBCASE( case7, array_a, axes_a );
    TRANSPOSE_SUBCASE( case8, array_a, axes_a );
    TRANSPOSE_SUBCASE( case9, array_a, axes_a );
    TRANSPOSE_SUBCASE( case10, array_a, axes_a );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case2, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case3, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case4, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case5, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case6, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case7, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case8, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case9, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case10, array_a, axes_v );

    TRANSPOSE_SUBCASE( case1, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case2, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case3, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case4, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case5, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case6, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case7, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case8, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case9, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_a, axes_ct );
}

TEST_CASE("transpose(vector)" * doctest::test_suite("view::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_v, axes_a );
    TRANSPOSE_SUBCASE( case2, array_v, axes_a );
    TRANSPOSE_SUBCASE( case3, array_v, axes_a );
    TRANSPOSE_SUBCASE( case4, array_v, axes_a );
    TRANSPOSE_SUBCASE( case5, array_v, axes_a );
    TRANSPOSE_SUBCASE( case6, array_v, axes_a );
    TRANSPOSE_SUBCASE( case7, array_v, axes_a );
    TRANSPOSE_SUBCASE( case8, array_v, axes_a );
    TRANSPOSE_SUBCASE( case9, array_v, axes_a );
    TRANSPOSE_SUBCASE( case10, array_v, axes_a );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case2, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case3, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case4, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case5, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case6, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case7, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case8, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case9, array_v, axes_v );
    // TRANSPOSE_SUBCASE( case10, array_v, axes_v );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case2, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case3, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case4, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case5, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case6, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case7, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case8, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case9, array_v, axes_ct );
    // TRANSPOSE_SUBCASE( case10, array_v, axes_ct );
}

TEST_CASE("transpose(fixed_ndarray)" * doctest::test_suite("view::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_f, axes_a );
    TRANSPOSE_SUBCASE( case2, array_f, axes_a );
    TRANSPOSE_SUBCASE( case3, array_f, axes_a );
    TRANSPOSE_SUBCASE( case4, array_f, axes_a );
    TRANSPOSE_SUBCASE( case5, array_f, axes_a );
    TRANSPOSE_SUBCASE( case6, array_f, axes_a );
    TRANSPOSE_SUBCASE( case7, array_f, axes_a );
    TRANSPOSE_SUBCASE( case8, array_f, axes_a );
    TRANSPOSE_SUBCASE( case9, array_f, axes_a );
    TRANSPOSE_SUBCASE( case10, array_f, axes_a );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case2, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case3, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case4, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case5, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case6, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case7, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case8, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case9, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case10, array_f, axes_v );

    TRANSPOSE_SUBCASE( case1, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case2, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case3, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case4, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case5, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case6, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case7, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case8, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case9, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_f, axes_ct );
}

TEST_CASE("transpose(hybrid_ndarray)" * doctest::test_suite("view::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_h, axes_a );
    TRANSPOSE_SUBCASE( case2, array_h, axes_a );
    TRANSPOSE_SUBCASE( case3, array_h, axes_a );
    TRANSPOSE_SUBCASE( case4, array_h, axes_a );
    TRANSPOSE_SUBCASE( case5, array_h, axes_a );
    TRANSPOSE_SUBCASE( case6, array_h, axes_a );
    TRANSPOSE_SUBCASE( case7, array_h, axes_a );
    TRANSPOSE_SUBCASE( case8, array_h, axes_a );
    TRANSPOSE_SUBCASE( case9, array_h, axes_a );
    TRANSPOSE_SUBCASE( case10, array_h, axes_a );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case2, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case3, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case4, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case5, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case6, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case7, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case8, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case9, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case10, array_h, axes_v );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case2, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case3, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case4, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case5, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case6, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case7, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case8, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case9, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case10, array_h, axes_ct );
}

TEST_CASE("transpose(dynamic_ndarray)" * doctest::test_suite("view::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_d, axes_a );
    TRANSPOSE_SUBCASE( case2, array_d, axes_a );
    TRANSPOSE_SUBCASE( case3, array_d, axes_a );
    TRANSPOSE_SUBCASE( case4, array_d, axes_a );
    TRANSPOSE_SUBCASE( case5, array_d, axes_a );
    TRANSPOSE_SUBCASE( case6, array_d, axes_a );
    TRANSPOSE_SUBCASE( case7, array_d, axes_a );
    TRANSPOSE_SUBCASE( case8, array_d, axes_a );
    TRANSPOSE_SUBCASE( case9, array_d, axes_a );
    TRANSPOSE_SUBCASE( case10, array_d, axes_a );

    TRANSPOSE_SUBCASE( case1, array_d, axes_v );
    TRANSPOSE_SUBCASE( case2, array_d, axes_v );
    TRANSPOSE_SUBCASE( case3, array_d, axes_v );
    TRANSPOSE_SUBCASE( case4, array_d, axes_v );
    TRANSPOSE_SUBCASE( case5, array_d, axes_v );
    TRANSPOSE_SUBCASE( case6, array_d, axes_v );
    TRANSPOSE_SUBCASE( case7, array_d, axes_v );
    TRANSPOSE_SUBCASE( case8, array_d, axes_v );
    TRANSPOSE_SUBCASE( case9, array_d, axes_v );
    TRANSPOSE_SUBCASE( case10, array_d, axes_v );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case2, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case3, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case4, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case5, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case6, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case7, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case8, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case9, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case10, array_d, axes_ct );
}