#ifndef NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_ARRAYS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_ARRAYS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(broadcast_arrays)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs[1][3] = {
            {1,2,3}
        };
        inline int rhs[2][1] = {
            {4},
            {5}
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        inline int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        inline auto shape = nmtools_array{2,3};
        inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs[3] = {1,2,3};
        inline int rhs[2][1] = {
            {4},
            {5}
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        inline int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        inline auto shape = nmtools_array{2,3};
        inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs[1][3] = {
            {1,2,3}
        };
        inline int rhs[1][2][1] = {
            {
                {4},
                {5}
            }
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int lhs[1][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            }
        };
        inline int rhs[1][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            }
        };
        inline auto shape = nmtools_array{1,2,3};
        inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lhs[1][3] = {
            {1,2,3}
        };
        inline int rhs[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int lhs[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        inline int rhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        inline auto shape = nmtools_array{2,2,3};
        inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int A[1][3] = {
            {1,2,3}
        };
        inline int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        inline int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        NMTOOLS_CAST_ARRAYS(A)
        NMTOOLS_CAST_ARRAYS(B)
        NMTOOLS_CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int A[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        inline int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        inline int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        inline auto shape = nmtools_array{2,2,3};
        inline auto expected = nmtools_tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int lhs[1][3] = {
            {1,2,3}
        };
        inline int rhs = 6;
        NMTOOLS_CAST_ARRAYS(lhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int lhs[1][3] = {
            {1,2,3}
        };
        inline int rhs[1][3] = {
            {6,6,6}
        };
        inline auto shape = nmtools_array{1,3};
        inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int lhs = 6;
        inline int rhs[1][3] = {
            {1,2,3}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int lhs[1][3] = {
            {6,6,6}
        };
        inline int rhs[1][3] = {
            {1,2,3}
        };
        inline auto shape = nmtools_array{1,3};
        inline auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int lhs = 6;
        inline int rhs = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int lhs = 6;
        inline int rhs = 1;
        inline auto shape = None;
        inline auto expected = nmtools_tuple{lhs,rhs};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int A = 6;
        inline int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        inline int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        NMTOOLS_CAST_ARRAYS(B)
        NMTOOLS_CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int A[2][2][3] = {
            {
                {6,6,6},
                {6,6,6},
            },
            {
                {6,6,6},
                {6,6,6},
            },
        };
        inline int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        inline int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        inline auto shape = nmtools_array{2,2,3};
        inline auto expected = nmtools_tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int A = 1;
        inline int B = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto shape = None;
        inline auto expected = nmtools_tuple{1,2};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_ARRAYS_HPP