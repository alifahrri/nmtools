#include "nmtools/array/array/transpose.hpp"
#include "nmtools/array/array/zeros.hpp"
#include "nmtools/array/array/where.hpp"
#include "nmtools/array/array/tile.hpp"
#include "nmtools/array/array/take.hpp"
#include "nmtools/array/array/squeeze.hpp"
#include "nmtools/array/array/slice.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/repeat.hpp"
#include "nmtools/array/array/pad.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/full.hpp"
#include "nmtools/array/array/flip.hpp"
#include "nmtools/array/array/flatten.hpp"
#include "nmtools/array/array/expand_dims.hpp"
#include "nmtools/array/array/concatenate.hpp"
#include "nmtools/array/array/compress.hpp"
#include "nmtools/array/array/broadcast_to.hpp"
#include "nmtools/array/array/atleast_3d.hpp"
#include "nmtools/array/array/atleast_2d.hpp"
#include "nmtools/array/array/atleast_1d.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/split.hpp"

#include "nmtools/array/view/mutable_flatten.hpp"
#include "nmtools/array/array/flatten.hpp"

#include "nmtools/utils/to_string.hpp"
#include "nmtools/utils/apply_to_string.hpp"

#include <Arduino.h>

namespace nm = nmtools;
namespace view = nm::view;

using nm::utils::to_string, nm::None, nm::shape, nm::utils::apply_to_string;

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

// some array with fixed shape
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

using namespace nmtools::literals;

// demonstrate the laziness of array view
auto flattened  = view::flatten(a);
auto transposed = view::transpose(a);
// reshape to new shape (2,6)
auto reshaped   = view::reshape(a, nmtools_array{2,6});
// pad the array at axis 0: (0,1), axis 1: (0,0), axis 2: (1,0)
auto padded     = view::pad(a, nmtools_array{0,0,1,1,0,0});
auto flipped    = view::flip(a, None);
auto atleast1d  = view::atleast_1d(b);
auto bcasted    = view::broadcast_to(b, nmtools_array{2,3,1});
// concat arrays must have same dim
auto concat     = view::concatenate(a,bcasted,2);
// split
auto split = view::split(a,3_ct,1_ct);

// mutable view has prefix mutable_*
auto mut_flat = view::mutable_flatten(a); 

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    // simply print the view, changes to referenced array should be reflected here
    Serial.println("========================\n");
    Serial.print("flattened:  \nshape: ");
    Serial.println(to_string(flattened).c_str());
    Serial.println(to_string(shape(flattened)).c_str());
    Serial.print("transposed: \nshape: ");
    Serial.println(to_string(shape(transposed)).c_str());
    Serial.println(to_string(transposed).c_str());
    Serial.print("reshaped:   \nshape: ");
    Serial.println(to_string(shape(reshaped)).c_str());
    Serial.println(to_string(reshaped).c_str());
    Serial.print("padded:     \nshape: ");
    Serial.println(to_string(shape(padded)).c_str());
    Serial.println(to_string(padded).c_str());
    Serial.print("flipped:    \nshape: ");
    Serial.println(to_string(shape(flipped)).c_str());
    Serial.println(to_string(flipped).c_str());
    Serial.print("concat:     \nshape: ");
    Serial.println(to_string(shape(concat)).c_str());
    Serial.println(to_string(concat).c_str());
    Serial.print("split: ");
    Serial.println(apply_to_string(split).c_str());
    Serial.println("========================\n\n");

    // increment first element
    nm::at(a,0,0,0) += 1;

    // increment last element via mutable view
    mut_flat(11) += 1;

    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}