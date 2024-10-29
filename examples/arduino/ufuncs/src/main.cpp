#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/sum.hpp"
#include "nmtools/array/array/matmul.hpp"
#include "nmtools/array/array/mean.hpp"
#include "nmtools/utility/to_string.hpp"

#include <Arduino.h>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

using nm::utils::to_string, nm::None;
using namespace nm::literals;

#ifndef LED_BUILTIN
#define LED_BUILTIN PC13
#endif

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.begin(115200);

    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
}

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

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("==========================");
    Serial.println("a+b:");
    Serial.println(to_string(a_plus_b).c_str());

    Serial.println("a*b:");
    Serial.println(to_string(a_mul_b).c_str());

    Serial.println("mean(a):");
    Serial.println(mean_a);

    Serial.println("sum(a):");
    Serial.println(to_string(sum_all).c_str());

    Serial.println("sum(a,0):");
    Serial.println(to_string(sum_a_0).c_str());

    Serial.println("matmul:");
    Serial.println(to_string(matmul).c_str());
    Serial.println("==========================");

    nm::at(a,0,0,0) += 1;

    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}