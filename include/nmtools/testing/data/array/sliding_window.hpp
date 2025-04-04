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

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int x[6] = {0,1,2,3,4,5};
        inline int window_shape = 3;
        inline auto axis = None;
        inline int stride = 2;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int expected[2][3] = {
            {0,1,2},
            {2,3,4},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int x[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        inline int window_shape[2] = {2,2};
        inline auto axis = None;
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int expected[1][2][2][2] = {
            {
                {
                    {0,1},
                    {4,5},
                },
                {
                    {2,3},
                    {6,7},
                }
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15b)
    {
        inline int x[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        inline int window_shape[2] = {2,2};
        inline auto axis = None;
        inline int stride = 2;
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15b)
    {
        inline int expected[1][2][2][2] = {
            {
                {
                    {0,1},
                    {4,5},
                },
                {
                    {2,3},
                    {6,7},
                }
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int x[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        inline int window_shape = 3;
        inline int axis = 0;
        inline int stride = 2;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
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

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int x[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {1,1};
        inline int stride = 2;
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
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

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[2] = {2,3};
        inline auto axis = None;
        inline int stride[2] = {3,2};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int expected[1][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {0,0};
        inline int stride = 2;
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
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

    NMTOOLS_TESTING_DECLARE_ARGS(case19b)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[2] = {2,3};
        inline int axis[2] = {0,0};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19b)
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

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[3] = {2,2,2};
        inline int axis[3] = {0,0,0};
        inline int stride[3] = {2,2,2};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
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

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int x[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int window_shape[3] = {2,2,2};
        inline int axis[3] = {0,1,0};
        inline int stride[3] = {1,2,1};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int expected[2][1][2][2][2] = {
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
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
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
        inline auto axis = None;
        inline int stride[3] = {1,2,3};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int expected[1][2][1][2][2][2] = {
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
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
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
        inline int stride[3] = {1,2,3};
        // inline int axis[3] = {0,1,2};
        // inline int stride[3] = {3,2,1};
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int expected[1][1][2][2][3][2] = {
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
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
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
        inline int stride = 2;

        inline auto window_shape_ct = 3_ct;
        inline auto axis_ct = meta::ct_v<-1>;
        inline auto stride_ct = 2_ct;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int expected[1][5][1][3] = {
            {
                {
                    {0,1,2},
                },
                {
                    {4,5,6},
                },
                {
                    {8, 9,10},
                },
                {
                    {12,13,14},
                },
                {
                    {16,17,18},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
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
        inline int stride = 2;
        inline auto window_shape_ct = 3_ct;
        inline auto axis_ct = meta::ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int expected[1][1][5][1][3] = {
            {
                {
                    {
                        {0,1,2},
                    },
                    {
                        {4,5,6},
                    },
                    {
                        {8, 9,10},
                    },
                    {
                        {12,13,14},
                    },
                    {
                        {16,17,18},
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
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
        inline int stride = 2;
        inline auto window_shape_ct = 3_ct;
        inline auto axis_ct = meta::ct_v<-1>;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
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

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    { 0, 1, 2, 3},
                    { 4, 5, 6, 7},
                    { 8, 9,10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {3,3};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {1,1};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,2};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int expected[1][1][2][2][3][3] = {
            {
                {
                    {
                        {
                            {0,1, 2},
                            {4,5, 6},
                            {8,9,10},
                        },
                        {
                            {1, 2, 3},
                            {5, 6, 7},
                            {9,10,11},
                        },
                    },
                    {
                        {
                            { 4, 5, 6},
                            { 8, 9,10},
                            {12,13,14},
                        },
                        {
                            { 5, 6, 7},
                            { 9,10,11},
                            {13,14,15},
                        }
                    },
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    { 0, 1, 2, 3},
                    { 4, 5, 6, 7},
                    { 8, 9,10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {3,3};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {1,1};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {1,1};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int expected[1][1][2][2][3][3] = {
            {
                {
                    {
                        {
                            {0,1, 2},
                            {4,5, 6},
                            {8,9,10},
                        },
                        {
                            {1, 2, 3},
                            {5, 6, 7},
                            {9,10,11},
                        },
                    },
                    {
                        {
                            { 4, 5, 6},
                            { 8, 9,10},
                            {12,13,14},
                        },
                        {
                            { 5, 6, 7},
                            { 9,10,11},
                            {13,14,15},
                        }
                    },
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {3,3};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {1,1};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {1,2};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int expected[1][1][2][2][3][3] = {
            {
                {
                    {
                        {
                            {0,1, 2},
                            {4,5, 6},
                            {8,9,10},
                        },
                        {
                            {1, 2, 3},
                            {5, 6, 7},
                            {9,10,11},
                        },
                    },
                    {
                        {
                            { 4, 5, 6},
                            { 8, 9,10},
                            {12,13,14},
                        },
                        {
                            { 5, 6, 7},
                            { 9,10,11},
                            {13,14,15},
                        }
                    },
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {3,3};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {1,1};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,1};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        inline int expected[1][1][2][2][3][3] = {
            {
                {
                    {
                        {
                            {0,1, 2},
                            {4,5, 6},
                            {8,9,10},
                        },
                        {
                            {1, 2, 3},
                            {5, 6, 7},
                            {9,10,11},
                        },
                    },
                    {
                        {
                            { 4, 5, 6},
                            { 8, 9,10},
                            {12,13,14},
                        },
                        {
                            { 5, 6, 7},
                            { 9,10,11},
                            {13,14,15},
                        }
                    },
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {3,3};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {2,1};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,1};
        // inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        inline int expected[1][1][1][2][3][3] = {
            {
                {
                    {
                        {
                            {0,1, 2},
                            {4,5, 6},
                            {8,9,10},
                        },
                        {
                            {1, 2, 3},
                            {5, 6, 7},
                            {9,10,11},
                        },
                    }
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {3,3};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {1,2};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {1,2};
        // inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        inline int expected[1][1][2][1][3][3] = {
            {
                {
                    {
                        {
                            {0,1, 2},
                            {4,5, 6},
                            {8,9,10},
                        },
                    },
                    {
                        {
                            { 4, 5, 6},
                            { 8, 9,10},
                            {12,13,14},
                        },
                    },
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {2,2};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {1,1};
        // inline int kernel_size[2] = {2,2};
        // inline int stride[2] = {1,1};
        // inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        inline int expected[1][1][3][3][2][2] = {
            {
                {
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
                        },
                    },
                    {
                        {
                            {4,5},
                            {8,9},
                        },
                        {
                            { 5, 6},
                            { 9,10},
                        },
                        {
                            { 6, 7},
                            {10,11},
                        },
                    },
                    {
                        {
                            { 8, 9},
                            {12,13},
                        },
                        {
                            { 9,10},
                            {13,14},
                        },
                        {
                            {10,11},
                            {14,15},
                        },
                    },
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case34)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {2,2};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {2,2};
        // inline int kernel_size[2] = {2,2};
        // inline int stride[2] = {2,2};
        // inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case34)
    {
        inline int expected[1][1][2][2][2][2] = {
            {
                {
                    {
                        {
                            {0,1},
                            {4,5},
                        },
                        {
                            {2,3},
                            {6,7},
                        }
                    },
                    {
                        {
                            { 8, 9},
                            {12,13},
                        },
                        {
                            {10,11},
                            {14,15},
                        },
                    },
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case35)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {2,2};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {3,3};
        // inline int kernel_size[2] = {2,2};
        // inline int stride[2] = {3,3};
        // inline auto ceil_mode = False;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case35)
    {
        inline int expected[1][1][1][1][2][2] = {
            {
                {
                    {
                        {
                            {0,1},
                            {4,5},
                        },
                    },
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case36)
    {
        inline int x[1][1][4][4] = {
            {
                {
                    {0, 1,  2, 3},
                    {4, 5,  6, 7},
                    {8, 9, 10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int window_shape[2] = {2,2};
        inline int axis[2] = {-2,-1};
        inline int stride[2] = {2,2};
        // inline int kernel_size[2] = {2,2};
        // inline int stride[2] = {3,3};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case36)
    {
        inline int expected[1][1][2][2][2][2] = {
            {
                {
                    {
                        {
                            {0,1},
                            {4,5},
                        },
                        {
                            {2,3},
                            {6,7},
                        }
                    },
                    {
                        {
                            { 8, 9},
                            {12,13},
                        },
                        {
                            {10,11},
                            {14,15},
                        },
                    },
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case37)
    {
        inline int x[1][1][6][6] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5},
                    { 6,  7,  8,  9, 10, 11},
                    {12, 13, 14, 15, 16, 17},
                    {18, 19, 20, 21, 22, 23},
                    {24, 25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34, 35}
                }
            }
        };
        inline int window_shape[2] = {3, 3};
        inline int axis[2] = {-2, -1};
        inline int stride[2] = {2, 2};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,2};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case37)
    {
        inline int expected[1][1][3][3][3][3] = {
            {
                {
                    {
                        {
                            { 0,  1,  2},
                            { 6,  7,  8},
                            {12, 13, 14}
                        },
                        {
                            { 2,  3,  4},
                            { 8,  9, 10},
                            {14, 15, 16}
                        },
                        {
                            { 4,  5, -1}, // padding is not done here.
                            {10, 11, -1}, // padding is not done here.
                            {16, 17, -1} // padding is not done here.
                        }
                    },
                    {
                        {
                            {12, 13, 14},
                            {18, 19, 20},
                            {24, 25, 26}
                        },
                        {
                            {14, 15, 16},
                            {20, 21, 22},
                            {26, 27, 28}
                        },
                        {
                            {16, 17, -1}, // padding is not done here.
                            {22, 23, -1}, // padding is not done here.
                            {28, 29, -1} // padding is not done here.
                        }
                    },
                    {
                        {
                            {24, 25, 26},
                            {30, 31, 32},
                            {-1, -1, -1} // padding is not done here.
                        },
                        {
                            {26, 27, 28},
                            {32, 33, 34},
                            {-1, -1, -1} // padding is not done here.
                        },
                        {
                            {28, 29, -1}, // padding is not done here.
                            {34, 35, -1}, // padding is not done here.
                            {-1, -1, -1} // padding is not done here.
                        }
                    }
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case38)
    {
        inline int x[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int window_shape[2] = {3, 3};
        inline int axis[2]         = {-2, -1};
        inline int stride[2]       = {2, 2};
        inline int dilation[2]     = {2,2};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,2};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case38)
    {
        inline int expected[1][1][2][2][3][3] = {
            {
                {
                    {
                        {
                            { 0, 2, 4},
                            {14,16,18},
                            {28,30,32},
                        },
                        {
                            { 2, 4, 6},
                            {16,18,20},
                            {30,32,34},
                        },
                    },
                    {
                        {
                            {14,16,18},
                            {28,30,32},
                            {42,44,46},
                        },
                        {
                            {16,18,20},
                            {30,32,34},
                            {44,46,48},
                        },
                    },
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case39)
    {
        inline int x[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int window_shape[2] = { 3, 3};
        inline int axis[2]         = {-2,-1};
        inline int stride[2]       = { 1, 1};
        inline int dilation[2]     = { 2, 2};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,2};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case39)
    {
        inline int expected[1][1][3][3][3][3] = {
            {
                {
                    {
                        {
                            { 0, 2, 4},
                            {14,16,18},
                            {28,30,32},
                        },
                        {
                            { 1, 3, 5},
                            {15,17,19},
                            {29,31,33},
                        },
                        {
                            { 2, 4, 6},
                            {16,18,20},
                            {30,32,34},
                        },
                    },
                    {
                        {
                            { 7, 9,11},
                            {21,23,25},
                            {35,37,39},
                        },
                        {
                            { 8,10,12},
                            {22,24,26},
                            {36,38,40},
                        },
                        {
                            { 9,11,13},
                            {23,25,27},
                            {37,39,41},
                        },
                    },
                    {
                        {
                            {14,16,18},
                            {28,30,32},
                            {42,44,46},
                        },
                        {
                            {15,17,19},
                            {29,31,33},
                            {43,45,47},
                        },
                        {
                            {16,18,20},
                            {30,32,34},
                            {44,46,48},
                        },
                    },
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case40)
    {
        inline int x[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int window_shape[2] = {3, 3};
        inline int axis[2]         = {-2, -1};
        inline int stride[2]       = {1, 1};
        inline int dilation[2]     = {3,3};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,2};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case40)
    {
        inline int expected[1][1][1][1][3][3] = {
            {
                {
                    {
                        {
                            { 0, 3, 6},
                            {21,24,27},
                            {42,45,48},
                        },
                    },
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case41)
    {
        inline int x[1][1][7][7] = {
            {
                {
                    { 0,  1,  2,  3,  4,  5,  6},
                    { 7,  8,  9, 10, 11, 12, 13},
                    {14, 15, 16, 17, 18, 19, 20},
                    {21, 22, 23, 24, 25, 26, 27},
                    {28, 29, 30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39, 40, 41},
                    {42, 43, 44, 45, 46, 47, 48}
                }
            }
        };
        inline int window_shape[2] = {3, 3};
        inline int axis[2]         = {-2, -1};
        inline int stride[2]       = {2, 2};
        inline int dilation[2]     = {3,3};
        // inline int kernel_size[2] = {3,3};
        // inline int stride[2] = {2,2};
        // inline auto ceil_mode = True;
        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(window_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(dilation)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case41)
    {
        inline int expected[1][1][1][1][3][3] = {
            {
                {
                    {
                        {
                            { 0, 3, 6},
                            {31,24,27},
                            {42,45,48},
                        },
                    },
                }
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SLIDING_WINDOW_HPP