#include <gtest/gtest.h>
#include "nmtools/utility.hpp"
#include <vector>
#include <array>

TEST(utility,inserter) {
    using namespace nmtools::helper;
    std::vector<double> w{2,3,4};
    std::vector<double> v;
    insert(v,double{1});
    insert(v,v.end(),double{2});
    insert(v,v.end(),w.begin(),w.end());
    EXPECT_EQ(v.size(),5);
    EXPECT_EQ(v[0],1.);
    EXPECT_EQ(v[1],2.);
    EXPECT_EQ(v[2],2.);
    EXPECT_EQ(v[3],3.);
    EXPECT_EQ(v[4],4.);
}