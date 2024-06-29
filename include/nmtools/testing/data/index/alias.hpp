#ifndef NMTOOLS_TESTING_DATA_INDEX_ALIAS_HPP
#define NMTOOLS_TESTING_DATA_INDEX_ALIAS_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,alias)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int operands[1] = {-1};
        inline auto reserved_ids = None;
        inline auto operands_ct = nmtools_tuple{meta::ct_v<-1>};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int operands[1] = {-1};
        inline int reserved_ids[3] = {2,0,1};
        inline auto operands_ct = nmtools_tuple{meta::ct_v<-1>};
        inline auto reserved_ids_ct = nmtools_tuple{2_ct,0_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int operands[3] = {-1,2,-1};
        inline int reserved_ids[2] = {3,1};
        inline auto operands_ct = nmtools_tuple{meta::ct_v<-1>,2_ct,meta::ct_v<-1>};
        inline auto reserved_ids_ct = nmtools_tuple{3_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {4,2,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int operands[3] = {-1,2,-1};
        inline auto reserved_ids = nmtools_tuple{};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int operands[3] = {3,2,4};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index,generate_alias)
{
    using namespace literals;
    using meta::ct_v;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int aliases[1] = {0};
        inline int base  = 256;
        inline int prime = 101;
        inline auto aliases_ct = nmtools_tuple{0_ct};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 101_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int aliases[2] = {0,-1};
        inline int base  = 256;
        inline int prime = 101;
        inline auto aliases_ct = nmtools_tuple{0_ct,ct_v<-1>};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 101_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = 100;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int aliases[3] = {100,0,-1};
        inline int base  = 256;
        inline int prime = 101;
        inline auto aliases_ct = nmtools_tuple{100_ct,0_ct,ct_v<-1>};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 101_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = 12;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int aliases[4] = {12,100,0,-1};
        inline int base  = 256;
        inline int prime = 101;
        inline auto aliases_ct = nmtools_tuple{12_ct,100_ct,0_ct,ct_v<-1>};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 101_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = 72;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int aliases[5] = {72,12,100,0,-1};
        inline int base  = 256;
        inline int prime = 101;
        inline auto aliases_ct = nmtools_tuple{72,12,100,0,ct_v<-1>};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 101_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = 19;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int aliases[7] = {3,0,1,2,3,4,-1};
        inline int base  = 256;
        inline int prime = 503;
        inline auto aliases_ct = nmtools_tuple{3_ct,0_ct,1_ct,2_ct,3_ct,4_ct,ct_v<-1>};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 503_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = 172;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int aliases[7] = {2,0,1,2,3,4,-1};
        inline int base  = 256;
        inline int prime = 503;
        inline auto aliases_ct = nmtools_tuple{2_ct,0_ct,1_ct,2_ct,3_ct,4_ct,ct_v<-1>};
        inline int base_ct  = 256_ct;
        inline int prime_ct = 503_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto result = 97;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int aliases[7] = {1,0,1,2,3,4,-1};
        inline int base  = 256;
        inline int prime = 503;
        inline auto aliases_ct = nmtools_tuple{1_ct,0_ct,1_ct,2_ct,3_ct,4_ct,ct_v<-1>};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 503_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto result = 22;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int aliases[7] = {4,0,1,2,3,4,-1};
        inline int base  = 256;
        inline int prime = 503;
        inline auto aliases_ct = nmtools_tuple{4_ct,0_ct,1_ct,2_ct,3_ct,4_ct,ct_v<-1>};
        inline auto base_ct  = 256_ct;
        inline auto prime_ct = 503_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = 247;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_ALIAS_HPP