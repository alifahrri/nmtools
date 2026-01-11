#include "nmtools/nmtools.hpp"
#include "nmtools/ndarray.hpp"

namespace nm = nmtools;
namespace utils = nmtools::utils;

using namespace nm::literals;
using nmtools_array;

template <typename array_t>
auto print(const array_t& x)
{
    std::cout << "shape: " << utils::to_string(nm::shape(x))
        << std::endl
        << utils::to_string(x)
        << std::endl;
}

int main(int argc, char** argv)
{
    auto x = nm::array.arange(15, /*dtype=*/nm::float32).reshape(array{3,5});
    auto t1 = (x - x.max(/*axis=*/1,/*dtype=*/nm::None,/*initial=*/nm::None,/*keepdims=*/true)).exp();
    auto t2 = t1.sum(-1,nm::None,nm::None,true);
    auto softmax = t1 / t2;

    print(x);
    print(t1);
    print(t2);
    print(softmax);

    return 0;
}