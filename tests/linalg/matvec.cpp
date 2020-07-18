#include "nmtools/linalg/matvec.hpp"
#include "nmtools/utility/helper.hpp"
#include <gtest/gtest.h>
#include <array>
#include <vector>

namespace nmt = nmtools;
namespace nla = nmt::linalg;

using std::array;
using std::vector;

using nmt::helper::isclose;

TEST(linalg, zeros_like)
{
    auto a = array<double,3>{ 1, 2, 3 };
    auto v = vector<double>{ 1, 2, 3 };
    constexpr double r[3] = { 1, 2, 3, };
    auto ma = array<array<double,3>,3> {
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
    };
    auto mv = vector<vector<double>> {
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
    };
    constexpr double mr[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    /* test for vector with array container at runtime */
    {
        auto zero = array<double,3>{ 0, 0, 0 };
        auto z = nla::zeros_like(a);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for vector with array container at compile-time */
    {
        constexpr auto zero = array<double,3>{ 0, 0, 0 };
        constexpr auto z = nla::zeros_like(a);
        static_assert(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for vector with vector container at runtime */
    {
        auto zero = vector<double>{ 0, 0, 0 };
        auto z = nla::zeros_like(v);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for vector with raw array at runtime */
    {
        auto zero = array<double,3>{ 0, 0, 0 };
        auto z = nla::zeros_like(r);
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
        EXPECT_TRUE(isclose(z,zero));
    }
    /* test for vector with raw array at compile-time */
    {
        constexpr auto zero = array<double,3>{ 0, 0, 0 };
        constexpr auto z = nla::zeros_like(r);
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
        static_assert(isclose(z,zero));
    }
    /* test for matrix with array container at runtime */
    {
        auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        auto z = nla::zeros_like(ma);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with array container at compile-time */
    {
        constexpr auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        constexpr auto z = nla::zeros_like(ma);
        static_assert(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with vector container at runtime */
    {
        auto zero = vector<vector<double>>{ 
            vector<double>{0, 0, 0 },
            vector<double>{0, 0, 0 },
            vector<double>{0, 0, 0 },
        };
        auto z = nla::zeros_like(mv);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with raw array at runtime */
    {
        auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        auto z = nla::zeros_like(mr);
        EXPECT_TRUE(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
    /* test for matrix with raw array at compile-time */
    {
        constexpr auto zero = array<array<double,3>,3>{ 
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
            array<double,3>{0, 0, 0 },
        };
        constexpr auto z = nla::zeros_like(mr);
        static_assert(isclose(z,zero));
        static_assert(std::is_same_v<decltype(zero),decltype(z)>);
    }
}

TEST(linalg, clone)
{
    constexpr auto a = array<double,3>{ 1, 2, 3 };
    auto v = vector<double>{ 1, 2, 3 };
    constexpr double r[3] = { 1, 2, 3, };
    constexpr auto ma = array<array<double,3>,3> {
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
    };
    auto mv = vector<vector<double>> {
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
    };
    constexpr double mr[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    /* test for vector with array container at runtime */
    {
        using return_t = array<double,3>;
        auto z = nla::clone(a);
        EXPECT_TRUE(isclose(z,a));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for vector with array container at compile-time */
    {
        using return_t = const array<double,3>;
        constexpr auto z = nla::clone(a);
        static_assert(isclose(z,a));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for vector with vector container at runtime */
    {
        using return_t = vector<double>;
        auto z = nla::clone(v);
        EXPECT_TRUE(isclose(z,v));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for vector with raw array at runtime */
    {
        using return_t = array<double,3>;
        auto z = nla::clone(r);
        static_assert(std::is_same_v<return_t,decltype(z)>);
        EXPECT_TRUE(isclose(z,a));
    }
    /* test for vector with raw array at compile-time */
    {
        using return_t = const array<double,3>;
        constexpr auto z = nla::clone(r);
        static_assert(std::is_same_v<return_t,decltype(z)>);
        static_assert(isclose(z,a));
    }
    /* test for matrix with array container at runtime */
    {
        using return_t = array<array<double,3>,3>;
        auto z = nla::clone(ma);
        EXPECT_TRUE(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with array container at compile-time */
    {
        using return_t = const array<array<double,3>,3>;
        constexpr auto z = nla::clone(ma);
        static_assert(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with vector container at runtime */
    {
        using return_t = vector<vector<double>>;
        auto z = nla::clone(mv);
        EXPECT_TRUE(isclose(z,mv));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with raw array at runtime */
    {
        using return_t = array<array<double,3>,3>;
        auto z = nla::clone(mr);
        EXPECT_TRUE(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
    /* test for matrix with raw array at compile-time */
    {
        using return_t = const array<array<double,3>,3>;
        constexpr auto z = nla::clone(mr);
        static_assert(isclose(z,ma));
        static_assert(std::is_same_v<return_t,decltype(z)>);
    }
}

TEST(linalg, identity)
{
    auto ma = array<array<double,3>,3> {
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
    };
    auto mv = vector<vector<double>> {
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
    };
    constexpr double mr[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    /* test for matrix with array container at runtime */
    {
        auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        auto z = nla::identity(ma);
        EXPECT_TRUE(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with array container at compile time */
    {
        constexpr auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        constexpr auto z = nla::identity(ma);
        static_assert(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with vector container at runtime */
    {
        auto i = vector<vector<double>>{
            vector<double>{1, 0, 0 },
            vector<double>{0, 1, 0 },
            vector<double>{0, 0, 1 },
        };
        static_assert(nmt::traits::is_resizeable_v<decltype(mv)>);
        auto z = nla::identity(mv);
        EXPECT_TRUE(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with raw array at runtime */
    {
        auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        auto z = nla::identity(mr);
        EXPECT_TRUE(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
    /* test for matrix with raw array at compile time */
    {
        constexpr auto i = array<array<double,3>,3>{ 
            array<double,3>{1, 0, 0 },
            array<double,3>{0, 1, 0 },
            array<double,3>{0, 0, 1 },
        };
        constexpr auto z = nla::identity(mr);
        static_assert(isclose(z,i));
        static_assert(std::is_same_v<decltype(i),decltype(z)>);
    }
}