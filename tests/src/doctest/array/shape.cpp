#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
using nmtools::utils::isequal;
using nm::meta::index_constant;
using nm::array::fixed_vector;
using nm::array::fixed_matrix;
using nm::array::fixed_ndarray;
using nm::array::dynamic_vector;
using nm::array::dynamic_matrix;
using nm::array::dynamic_ndarray;
using std::array;
using std::tuple;
