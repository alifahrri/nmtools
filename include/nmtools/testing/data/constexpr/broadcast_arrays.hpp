#ifndef NMTOOLS_TESTING_DATA_CONSTEXPR_BROADCAST_ARRAYS_HPP
#define NMTOOLS_TESTING_DATA_CONSTEXPR_BROADCAST_ARRAYS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(constexpr_broadcast_arrays)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int lhs[1][3] = {
            {1,2,3}
        };
        constexpr inline int rhs[2][1] = {
            {4},
            {5}
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        constexpr inline int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        constexpr inline auto shape = nmtools_array{2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int lhs[3] = {1,2,3};
        constexpr inline int rhs[2][1] = {
            {4},
            {5}
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        constexpr inline int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        constexpr inline auto shape = nmtools_array{2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int lhs[1][3] = {
            {1,2,3}
        };
        constexpr inline int rhs[1][2][1] = {
            {
                {4},
                {5}
            }
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int lhs[1][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            }
        };
        constexpr inline int rhs[1][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            }
        };
        constexpr inline auto shape = nmtools_array{1,2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int lhs[1][3] = {
            {1,2,3}
        };
        constexpr inline int rhs[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int lhs[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        constexpr inline int rhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr inline auto shape = nmtools_array{2,2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int A[1][3] = {
            {1,2,3}
        };
        constexpr inline int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        constexpr inline int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(A)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(B)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int A[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        constexpr inline int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr inline int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        constexpr inline auto shape = nmtools_array{2,2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int lhs[1][3] = {
            {1,2,3}
        };
        constexpr inline int rhs = 6;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int lhs[1][3] = {
            {1,2,3}
        };
        constexpr inline int rhs[1][3] = {
            {6,6,6}
        };
        constexpr inline auto shape = nmtools_array{1,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int lhs = 6;
        constexpr inline int rhs[1][3] = {
            {1,2,3}
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int lhs[1][3] = {
            {6,6,6}
        };
        constexpr inline int rhs[1][3] = {
            {1,2,3}
        };
        constexpr inline auto shape = nmtools_array{1,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline int lhs = 6;
        constexpr inline int rhs = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline int lhs = 6;
        constexpr inline int rhs = 1;
        constexpr inline auto shape = None;
        constexpr inline auto expected = nmtools_tuple{lhs,rhs};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline int A = 6;
        constexpr inline int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        constexpr inline int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(B)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline int A[2][2][3] = {
            {
                {6,6,6},
                {6,6,6},
            },
            {
                {6,6,6},
                {6,6,6},
            },
        };
        constexpr inline int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr inline int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        constexpr inline auto shape = nmtools_array{2,2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline int A = 1;
        constexpr inline int B = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto shape = None;
        constexpr inline auto expected = nmtools_tuple{1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline int A = 6;
        constexpr inline int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            },
        };
        constexpr inline int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(B)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline int A[2][2][3] = {
            {
                {6,6,6},
                {6,6,6},
            },
            {
                {6,6,6},
                {6,6,6},
            },
        };
        constexpr inline int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr inline int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        constexpr inline auto shape = nmtools_array{2,2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline int lhs[1][3] = {
            {1,2,3}
        };
        constexpr inline int rhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline int lhs[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        constexpr inline int rhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr inline auto shape = nmtools_array{2,2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        constexpr inline int lhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            },
        };
        constexpr inline int rhs[2][3] = {
            {1,2,3},
            {1,2,3}
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline int rhs[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        constexpr inline int lhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr inline auto shape = nmtools_array{2,2,3};
        constexpr inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }
}

#endif // NMTOOLS_TESTING_DATA_CONSTEXPR_BROADCAST_ARRAYS_HPP