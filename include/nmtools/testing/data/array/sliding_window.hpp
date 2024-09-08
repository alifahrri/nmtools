#ifndef NMTOOLS_TESTING_DATA_ARRAY_SLIDING_WINDOW_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SLIDING_WINDOW_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, sliding_window)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int x[6] = {0,1,2,3,4,5};
        inline int window_shape = 3;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[4][3] = {
            {0,1,2},
            {1,2,3},
            {2,3,4},
            {3,4,5}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int x[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        inline int window_shape[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[2][3][2][2] = {
            {
                {
                    {0,1},
                    {4,5},
                },
                {
                    {1,2},
                    {5,6},
                },
                {
                    {2,3},
                    {6,7},
                }
            },
            {
                {
                    {4,5},
                    {8,9},
                },
                {
                    {5, 6},
                    {9,10},
                },
                {
                    { 6, 7},
                    {10,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int x[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        inline int window_shape = 3;
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int expected[1][4][3] = {
            {
                {0, 4, 8},
                {1, 5, 9},
                {2, 6,10},
                {3, 7,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int x[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int expected[3][1][2][3] = {
            {
                {
                    {0,1,2},
                    {1,2,3},
                }
            },
            {
                {
                    {4,5,6},
                    {5,6,7},
                }
            },
            {
                {
                    {8, 9,10},
                    {9,10,11}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[2] = {2,3};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int expected[3][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            },
            {
                {
                    {3,4,5},
                    {6,7,8},
                }
            },
            {
                {
                    {6, 7, 8},
                    {9,10,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {0,0};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int expected[1][3][2][3] = {
            {
                {
                    {0,3,6},
                    {3,6,9},
                },
                {
                    {1,4, 7},
                    {4,7,10},
                },
                {
                    {2,5, 8},
                    {5,8,11},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[3] = {2,2,2};
        inline int axis[3] = {0,0,0};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int expected[1][3][2][2][2] = {
            {
                {
                    {
                        {0,3},
                        {3,6},
                    },
                    {
                        {3,6},
                        {6,9},
                    },
                },
                {
                    {
                        {1,4},
                        {4,7},
                    },
                    {
                        {4, 7},
                        {7,10},
                    }
                },
                {
                    {
                        {2,5},
                        {5,8},
                    },
                    {
                        {5,8},
                        {8,11},
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[3] = {2,2,2};
        inline int axis[3] = {0,1,0};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int expected[2][2][2][2][2] = {
            {
                {
                    {
                        {0,3},
                        {1,4},
                    },
                    {
                        {3,6},
                        {4,7},
                    }
                },
                {
                    {
                        {1,4},
                        {2,5},
                    },
                    {
                        {4,7},
                        {5,8},
                    }
                }
            },
            {
                {
                    {
                        {3,6},
                        {4,7},
                    },
                    {
                        {6, 9},
                        {7,10},
                    }
                },
                {
                    {
                        {4,7},
                        {5,8},
                    },
                    {
                        {7,10},
                        {8,11},
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int x[2][4][3] = {
            {
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
                {9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
                {18,19,20},
                {21,22,23},
            }
        };
        inline int window_shape[3] = {2,2,2};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int expected[1][3][2][2][2][2] = {
            {
                {
                    {
                        {
                            {0,1},
                            {3,4},
                        },
                        {
                            {12,13},
                            {15,16},
                        }
                    },
                    {
                        {
                            {1,2},
                            {4,5},
                        },
                        {
                            {13,14},
                            {16,17},
                        }
                    }
                },
                {
                    {
                        {
                            {3,4},
                            {6,7},
                        },
                        {
                            {15,16},
                            {18,19},
                        }
                    },
                    {
                        {
                            {4,5},
                            {7,8},
                        },
                        {
                            {16,17},
                            {19,20},
                        }
                    }
                },
                {
                    {
                        {
                            {6, 7},
                            {9,10},
                        },
                        {
                            {18,19},
                            {21,22},
                        }
                    },
                    {
                        {
                            { 7, 8},
                            {10,11},
                        },
                        {
                            {19,20},
                            {22,23},
                        }
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int x[2][4][3] = {
            {
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
                {9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
                {18,19,20},
                {21,22,23},
            }
        };
        inline int window_shape[3] = {2,3,2};
        inline int axis[3] = {2,1,0};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int expected[1][2][2][2][3][2] = {
            {
                {
                    {
                        {
                            {0,12},
                            {3,15},
                            {6,18},
                        },
                        {
                            {1,13},
                            {4,16},
                            {7,19},
                        }
                    },
                    {
                        {
                            {1,13},
                            {4,16},
                            {7,19},
                        },
                        {
                            {2,14},
                            {5,17},
                            {8,20},
                        }
                    }
                },
                {
                    {
                        {
                            {3,15},
                            {6,18},
                            {9,21},
                        },
                        {
                            { 4,16},
                            { 7,19},
                            {10,22},
                        }
                    },
                    {
                        {
                            { 4,16},
                            { 7,19},
                            {10,22},
                        },
                        {
                            {5,17},
                            {8,20},
                            {11,23},
                        }
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int x[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int window_shape = 3;
        inline int axis = -1;
        inline auto window_shape_ct = 3_ct;
        inline auto axis_ct = meta::ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int expected[1][5][2][3] = {
            {
                {
                    {0,1,2},
                    {1,2,3},
                },
                {
                    {4,5,6},
                    {5,6,7},
                },
                {
                    {8, 9,10},
                    {9,10,11},
                },
                {
                    {12,13,14},
                    {13,14,15},
                },
                {
                    {16,17,18},
                    {17,18,19},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int x[1][1][5][4] = {
            {
                {
                    { 0, 1, 2, 3},
                    { 4, 5, 6, 7},
                    { 8, 9,10,11},
                    {12,13,14,15},
                    {16,17,18,19},
                }
            }
        };
        inline int window_shape = 3;
        inline int axis = -1;
        inline auto window_shape_ct = 3_ct;
        inline auto axis_ct = meta::ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int expected[1][1][5][2][3] = {
            {
                {
                    {
                        {0,1,2},
                        {1,2,3},
                    },
                    {
                        {4,5,6},
                        {5,6,7},
                    },
                    {
                        {8, 9,10},
                        {9,10,11},
                    },
                    {
                        {12,13,14},
                        {13,14,15},
                    },
                    {
                        {16,17,18},
                        {17,18,19},
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int x[1][5][3] = {
            {
                { 0, 1, 2},
                { 3, 4, 5},
                { 6, 7, 8},
                { 9,10,11},
                {12,13,14},
            }
        };
        inline int window_shape = 3;
        inline int axis = -1;
        inline auto window_shape_ct = 3_ct;
        inline auto axis_ct = meta::ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int expected[1][5][1][3] = {
            {
                {
                    { 0, 1, 2},
                },
                {
                    { 3, 4, 5},
                },
                {
                    { 6, 7, 8},
                },
                {
                    { 9,10,11},
                },
                {
                    {12,13,14},
                },
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SLIDING_WINDOW_HPP