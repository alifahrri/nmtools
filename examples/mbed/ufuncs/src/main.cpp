#define MBED_NO_GLOBAL_USING_DIRECTIVE
#include <mbed.h>

#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/mean.hpp"
#include "nmtools/array/array/sum.hpp"
#include "nmtools/array/array/matmul.hpp"

#include "nmtools/ndarray/fixed.hpp"

#include "nmtools/utility/to_string.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

using nm::utils::to_string, nm::None, nm::shape, nm::True;
using namespace nm::literals;

mbed::DigitalOut led1(LED1);

int main()
{
    int a[2][3][2] = {
        {
            {0,1},
            {2,3},
            {4,5},
        },
        {
            { 6, 7},
            { 8, 9},
            {10,11},
        }
    };
    int b = 13;
    
    auto c = na::fixed_ndarray{{
        {0,1,3},
        {2,3,4},
    }};

    auto a_plus_b = view::add(a,b);
    auto a_mul_b  = view::multiply(a,b);
    auto mean_a   = view::mean(a,None);
    auto sum_all  = view::sum(a,None);
    auto sum_a_0  = view::sum(a,0_ct);
    auto matmul   = view::matmul(a,c);

    while (true)
    {
        printf("===================\n");
        printf("a+b: \n%s\n", to_string(a_plus_b).c_str());
        printf("a*b: \n%s\n", to_string(a_mul_b).c_str());
        printf("mean(a): \n%s\n",  to_string(mean_a).c_str());
        printf("sum(a): \n%s\n",   to_string(sum_all).c_str());
        printf("sum(a,0): \n%s\n", to_string(sum_a_0).c_str());
        // TODO: fix
        // printf("matmul: \n%s\n",   to_string(matmul).c_str());
        printf("===================\n");

        // increment first element
        nm::at(a,0,0,0) += 1;

        led1 = !led1;
        thread_sleep_for(1000);
    }
}