#include "nmtools/tilekit/scalar.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple, nmtools_array;
using namespace nmtools::literals;

TEST_CASE("repeat(case1)" * doctest::test_suite("tilekit::scalar"))
{
    using buffer_t  = nmtools_array<float,4>;
    using shape_t   = nmtools_tuple<nm::ct<1>,nm::ct<4>>;
    using f32x4x1_t = nm::object_t<buffer_t,shape_t>;

    // TODO: make convinient operator= overload
    auto f32x4x1 = f32x4x1_t{};
    f32x4x1.data()[0] = 1.f;
    f32x4x1.data()[1] = 2.f;
    f32x4x1.data()[2] = 3.f;
    f32x4x1.data()[3] = 4.f;
    {
        auto repeats = 2_ct;
        auto axis = 0_ct;
        auto f32x2x4 = f32x4x1.repeat(repeats,axis);
        float expected[2][4] = {
            {1,2,3,4},
            {1,2,3,4},
        };
        NMTOOLS_ASSERT_CLOSE( f32x2x4, expected );
    }
}

TEST_CASE("tile(case1)" * doctest::test_suite("tilekit::scalar"))
{
    using buffer_t  = nmtools_array<float,4>;
    using shape_t   = nmtools_tuple<nm::ct<1>,nm::ct<4>>;
    using f32x4x1_t = nm::object_t<buffer_t,shape_t>;

    // TODO: make convinient operator= overload
    auto f32x4x1 = f32x4x1_t{};
    f32x4x1.data()[0] = 1.f;
    f32x4x1.data()[1] = 2.f;
    f32x4x1.data()[2] = 3.f;
    f32x4x1.data()[3] = 4.f;
    {
        auto f32x2x4 = f32x4x1.tile(tuple{2_ct});
        float expected[1][8] = {
            {1,2,3,4,1,2,3,4},
        };
        NMTOOLS_ASSERT_CLOSE( f32x2x4, expected );
    }
}

TEST_CASE("tile(case2)" * doctest::test_suite("tilekit::scalar"))
{
    using buffer_t  = nmtools_array<float,4>;
    using shape_t   = nmtools_tuple<nm::ct<1>,nm::ct<4>>;
    using f32x4x1_t = nm::object_t<buffer_t,shape_t>;

    // TODO: make convinient operator= overload
    auto f32x4x1 = f32x4x1_t{};
    f32x4x1.data()[0] = 1.f;
    f32x4x1.data()[1] = 2.f;
    f32x4x1.data()[2] = 3.f;
    f32x4x1.data()[3] = 4.f;
    {
        auto f32x2x4 = f32x4x1.tile(tuple{2_ct}).reshape(tuple{2_ct,4_ct});
        float expected[2][4] = {
            {1,2,3,4},
            {1,2,3,4},
        };
        NMTOOLS_ASSERT_CLOSE( f32x2x4, expected );
    }
}

using namespace nmtools::literals;
using nmtools_tuple, nmtools_array;

TEST_CASE("matmul(case1)" * doctest::test_suite("tilekit::scalar"))
{
    int a[3][4] = {
        {0,1, 2, 3},
        {4,5, 6, 7},
        {8,9,10,11},
    };
    int b[4][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {9,10,11},
    };
    int c[3][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
    };

    auto ctx = tk::Scalar;

    auto m_block = 1_ct;
    auto n_block = 1_ct;
    auto k_block = 2_ct;

    auto lhs_tile = tuple{m_block,k_block};
    auto rhs_tile = tuple{k_block,n_block};
    auto acc_tile = tuple{m_block,k_block,n_block};

    auto dtype = nm::int32;
    auto accumulator = nm::Array::zeros(acc_tile,dtype,ctx);

    // 1st iteration
    // (0,0)
    {
        auto lhs_ndoffset = tuple{0,0};
        auto rhs_ndoffset = tuple{0,0};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {0,1}
            };
            int expect_b[2][1] = {
                {0},
                {3},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        {
            int expect_a[1][2][1] = {
                {
                    {0},
                    {1},
                },
            };
            int expect_b[1][2][1] = {
                {
                    {0},
                    {3},
                },
            };

            NMTOOLS_ASSERT_EQUAL( tmp2a, expect_a );
            NMTOOLS_ASSERT_EQUAL( tmp2b, expect_b );
        }

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {0},
                    {3},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (0,1)
    {
        auto lhs_ndoffset = tuple{0,2};
        auto rhs_ndoffset = tuple{2,0};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {2,3}
            };
            int expect_b[2][1] = {
                {6},
                {9},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        {
            int expect_a[1][2][1] = {
                {
                    {2},
                    {3},
                },
            };
            int expect_b[1][2][1] = {
                {
                    {6},
                    {9},
                },
            };

            NMTOOLS_ASSERT_EQUAL( tmp2a, expect_a );
            NMTOOLS_ASSERT_EQUAL( tmp2b, expect_b );
        }

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {12},
                    {27},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    {12},
                    {30},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store
    {
        auto out_offset = tuple{0,0};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            {42,0,0},
            { 0,0,0},
            { 0,0,0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (0,1)
    {
        auto lhs_ndoffset = tuple{0,0};
        auto rhs_ndoffset = tuple{0,1};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {0,1}
            };
            int expect_b[2][1] = {
                {1},
                {4},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {0},
                    {4},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (2,1)
    {
        auto lhs_ndoffset = tuple{0,2};
        auto rhs_ndoffset = tuple{2,1};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {2,3}
            };
            int expect_b[2][1] = {
                { 7},
                {10},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {14},
                    {30},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    {14},
                    {34},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store
    {
        auto out_offset = tuple{0,1};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            {42,48,0},
            { 0, 0,0},
            { 0, 0,0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (0,2)
    {
        auto lhs_ndoffset = tuple{0,0};
        auto rhs_ndoffset = tuple{0,2};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {0,1}
            };
            int expect_b[2][1] = {
                {2},
                {5},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {0},
                    {5},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (2,1)
    {
        auto lhs_ndoffset = tuple{0,2};
        auto rhs_ndoffset = tuple{2,2};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {2,3}
            };
            int expect_b[2][1] = {
                { 8},
                {11},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {16},
                    {33},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    {16},
                    {38},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store
    {
        auto out_offset = tuple{0,2};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            {42,48,54},
            { 0, 0, 0},
            { 0, 0, 0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (1,0)
    {
        auto lhs_ndoffset = tuple{1,0};
        auto rhs_ndoffset = tuple{0,0};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {4,5}
            };
            int expect_b[2][1] = {
                {0},
                {3},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    { 0},
                    {15},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (1,1)
    {
        auto lhs_ndoffset = tuple{1,2};
        auto rhs_ndoffset = tuple{2,0};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {6,7}
            };
            int expect_b[2][1] = {
                {6},
                {9},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {36},
                    {63},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    {36},
                    {78},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store
    {
        auto out_offset = tuple{1,0};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            { 42,48,54},
            {114, 0, 0},
            {  0, 0, 0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (1,0) x (0,1)
    {
        auto lhs_ndoffset = tuple{1,0};
        auto rhs_ndoffset = tuple{0,1};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {4,5}
            };
            int expect_b[2][1] = {
                {1},
                {4},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    { 4},
                    {20},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (1,1) x (1,1)
    {
        auto lhs_ndoffset = tuple{1,2};
        auto rhs_ndoffset = tuple{2,1};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {6,7}
            };
            int expect_b[2][1] = {
                { 7},
                {10},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {42},
                    {70},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    {46},
                    {90},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store: (1,1)
    {
        auto out_offset = tuple{1,1};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            { 42, 48,54},
            {114,136, 0},
            {  0,  0, 0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (1,0) x (0,2)
    {
        auto lhs_ndoffset = tuple{1,0};
        auto rhs_ndoffset = tuple{0,2};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {4,5}
            };
            int expect_b[2][1] = {
                {2},
                {5},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    { 8},
                    {25},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (1,1) x (1,2)
    {
        auto lhs_ndoffset = tuple{1,2};
        auto rhs_ndoffset = tuple{2,2};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {6,7}
            };
            int expect_b[2][1] = {
                { 8},
                {11},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {48},
                    {77},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    { 56},
                    {102},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store: (1,2)
    {
        auto out_offset = tuple{1,2};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            { 42, 48, 54},
            {114,136,158},
            {  0,  0,  0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (2,0) x (0,0)
    {
        auto lhs_ndoffset = tuple{2,0};
        auto rhs_ndoffset = tuple{0,0};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {8,9}
            };
            int expect_b[2][1] = {
                {0},
                {3},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    { 0},
                    {27},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }


    // (2,2) x (2,0)
    {
        auto lhs_ndoffset = tuple{2,2};
        auto rhs_ndoffset = tuple{2,0};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {10,11}
            };
            int expect_b[2][1] = {
                {6},
                {9},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {60},
                    {99},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    { 60},
                    {126},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store: (2,0)
    {
        auto out_offset = tuple{2,0};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            { 42, 48, 54},
            {114,136,158},
            {186,  0,  0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (2,0) x (0,1)
    {
        auto lhs_ndoffset = tuple{2,0};
        auto rhs_ndoffset = tuple{0,1};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {8,9}
            };
            int expect_b[2][1] = {
                {1},
                {4},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    { 8},
                    {36},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (2,2) x (2,1)
    {
        auto lhs_ndoffset = tuple{2,2};
        auto rhs_ndoffset = tuple{2,1};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {10,11}
            };
            int expect_b[2][1] = {
                { 7},
                {10},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    { 70},
                    {110},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    { 78},
                    {146},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store: (2,1)
    {
        auto out_offset = tuple{2,1};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            { 42, 48, 54},
            {114,136,158},
            {186,224,  0},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }

    // (2,0) x (0,2)
    {
        auto lhs_ndoffset = tuple{2,0};
        auto rhs_ndoffset = tuple{0,2};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {8,9}
            };
            int expect_b[2][1] = {
                {2},
                {5},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    {16},
                    {45},
                },
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, expect );
        }
    }

    // (2,2) x (2,2)
    {
        auto lhs_ndoffset = tuple{2,2};
        auto rhs_ndoffset = tuple{2,2};

        auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
        auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

        {
            int expect_a[1][2] = {
                {10,11}
            };
            int expect_b[2][1] = {
                { 8},
                {11},
            };

            NMTOOLS_ASSERT_EQUAL( block_a, expect_a );
            NMTOOLS_ASSERT_EQUAL( block_b, expect_b );
        }

        auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
        auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

        auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
        auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

        auto result = tmp2a * tmp2b;
        accumulator = accumulator + result;
        {
            int expect[1][2][1] = {
                {
                    { 80},
                    {121},
                },
            };
            int acc_expect[1][2][1] = {
                {
                    { 96},
                    {166},
                }
            };
            NMTOOLS_ASSERT_EQUAL( result, expect );
            NMTOOLS_ASSERT_EQUAL( accumulator, acc_expect );
        }
    }

    // store: (2,2)
    {
        auto out_offset = tuple{2,2};
        auto result = accumulator.sum(-2_ct);
        tk::store(ctx,c,out_offset,result);
        int expect[3][3] = {
            { 42, 48, 54},
            {114,136,158},
            {186,224,262},
        };
        NMTOOLS_ASSERT_EQUAL( c, expect );

        // clear accumulator after store
        accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
    }
}

TEST_CASE("matmul(case2)" * doctest::test_suite("tilekit::scalar"))
{
    int a[3][4] = {
        {0,1, 2, 3},
        {4,5, 6, 7},
        {8,9,10,11},
    };
    int b[4][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {9,10,11},
    };
    int c[3][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
    };

    auto ctx = tk::Scalar;

    auto m_block = 1_ct;
    auto n_block = 1_ct;
    auto k_block = 2_ct;

    auto lhs_tile = tuple{m_block,k_block};
    auto rhs_tile = tuple{k_block,n_block};
    auto acc_tile = tuple{m_block,k_block,n_block};

    auto dtype = nm::int32;

    auto a_shape = nm::shape<true>(a);
    auto c_shape = nm::shape<true>(c);

    auto M = nm::at(c_shape,-2_ct) / m_block;
    auto K = nm::at(a_shape,-1_ct) / k_block;
    auto N = nm::at(c_shape,-1_ct) / n_block;

    for (nm_size_t m=0; m<M; m++) {
        for (nm_size_t n=0; n<N; n++) {
            auto accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
            for (nm_size_t k=0; k<K; k++) {
                auto lhs_ndoffset = tuple{m,k*k_block};
                auto rhs_ndoffset = tuple{k*k_block,n};
                
                auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
                auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

                auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
                auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

                auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
                auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

                auto result = tmp2a * tmp2b;
                accumulator = accumulator + result;
            }
            auto out_offset = tuple{m,n};
            auto result = accumulator.sum(-2_ct);
            tk::store(ctx,c,out_offset,result);
        }
    }

    int expect[3][3] = {
        { 42, 48, 54},
        {114,136,158},
        {186,224,262},
    };
    NMTOOLS_ASSERT_EQUAL( c, expect );
}

TEST_CASE("matmul(case3)" * doctest::test_suite("tilekit::scalar"))
{
    int a[4][4] = {
        { 0, 1, 2, 3},
        { 4, 5, 6, 7},
        { 8, 9,10,11},
        {12,13,14,15}
    };
    int b[4][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {9,10,11},
    };
    int c[4][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    };

    auto ctx = tk::Scalar;

    auto m_block = 2_ct;
    auto n_block = 1_ct;
    auto k_block = 2_ct;

    auto lhs_tile = tuple{m_block,k_block};
    auto rhs_tile = tuple{k_block,n_block};
    auto acc_tile = tuple{m_block,k_block,n_block};
    auto out_tile = tuple{m_block,n_block};

    auto dtype = nm::int32;

    auto a_shape = tk::shape(a);
    auto b_shape = tk::shape(b);
    auto c_shape = tk::shape(c);

    auto a_nditer = tk::nditer(a_shape,lhs_tile);
    auto b_nditer = tk::nditer(b_shape,rhs_tile);
    auto c_nditer = tk::nditer(c_shape,out_tile);

    auto M = nm::at(c_shape,-2_ct) / m_block;
    auto K = nm::at(a_shape,-1_ct) / k_block;
    auto N = nm::at(c_shape,-1_ct) / n_block;

    for (nm_size_t m=0; m<M; m++) {
        for (nm_size_t n=0; n<N; n++) {
            auto accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
            for (nm_size_t k=0; k<K; k++) {
                auto lhs_ndoffset = tk::packed_at(a_nditer,m,k);
                auto rhs_ndoffset = tk::packed_at(b_nditer,k,n);
                
                auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
                auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

                auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
                auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

                auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
                auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

                auto result = tmp2a * tmp2b;
                accumulator = accumulator + result;
            }
            auto out_offset = tk::packed_at(c_nditer,m,n);
            auto result = accumulator.sum(-2_ct);
            tk::store(ctx,c,out_offset,result);
        }
    }

    int expect[4][3] = {
        { 42, 48, 54},
        {114,136,158},
        {186,224,262},
        {258,312,366},
    };
    NMTOOLS_ASSERT_EQUAL( c, expect );
}

TEST_CASE("matmul(case3)" * doctest::test_suite("tilekit::scalar"))
{
    int a[4][4] = {
        { 0, 1, 2, 3},
        { 4, 5, 6, 7},
        { 8, 9,10,11},
        {12,13,14,15}
    };
    int b[4][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {9,10,11},
    };
    int c[4][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    };

    auto ctx = tk::Scalar;

    auto m_block = 2_ct;
    auto n_block = 3_ct;
    auto k_block = 2_ct;

    auto lhs_tile = tuple{m_block,k_block};
    auto rhs_tile = tuple{k_block,n_block};
    auto acc_tile = tuple{m_block,k_block,n_block};
    auto out_tile = tuple{m_block,n_block};

    auto dtype = nm::int32;

    auto a_shape = tk::shape(a);
    auto b_shape = tk::shape(b);
    auto c_shape = tk::shape(c);

    auto a_nditer = tk::nditer(a_shape,lhs_tile);
    auto b_nditer = tk::nditer(b_shape,rhs_tile);
    auto c_nditer = tk::nditer(c_shape,out_tile);

    auto M = nm::at(c_shape,-2_ct) / m_block;
    auto K = nm::at(a_shape,-1_ct) / k_block;
    auto N = nm::at(c_shape,-1_ct) / n_block;

    for (nm_size_t m=0; m<M; m++) {
        for (nm_size_t n=0; n<N; n++) {
            auto accumulator = nm::Array::zeros(acc_tile,dtype,ctx);
            for (nm_size_t k=0; k<K; k++) {
                auto lhs_ndoffset = tk::packed_at(a_nditer,m,k);
                auto rhs_ndoffset = tk::packed_at(b_nditer,k,n);
                
                auto block_a = tk::load(ctx,a,lhs_ndoffset,lhs_tile);
                auto block_b = tk::load(ctx,b,rhs_ndoffset,rhs_tile);

                auto tmp1a = block_a.reshape(tuple{m_block,k_block,1_ct});
                auto tmp1b = block_b.reshape(tuple{1_ct,k_block,n_block});

                auto tmp2a = tmp1a.broadcast_to(tuple{m_block,k_block,n_block});
                auto tmp2b = tmp1b.broadcast_to(tuple{m_block,k_block,n_block});

                auto result = tmp2a * tmp2b;
                accumulator = accumulator + result;
            }
            auto out_offset = tk::packed_at(c_nditer,m,n);
            auto result = accumulator.sum(-2_ct);
            tk::store(ctx,c,out_offset,result);
        }
    }

    int expect[4][3] = {
        { 42, 48, 54},
        {114,136,158},
        {186,224,262},
        {258,312,366},
    };
    NMTOOLS_ASSERT_EQUAL( c, expect );
}