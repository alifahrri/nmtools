#include "nmtools/nmtools.hpp"
#include "nmtools/ndarray.hpp"

namespace nm = nmtools;
namespace utils = nmtools::utils;

using namespace nm::literals;
using nmtools_array;
using nmtools_tuple;

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
    auto gen = nm::random_engine();
    auto dtype = nm::float32;
    auto a = nm::Array::random(array{2,3,2},dtype,gen);
    print(a);

    // similar to x[1:,1:,...]
    auto sa = a.slice("1:"_ct,"1:2"_ct,"..."_ct);
    print(sa);

    std::cout << "a:\n";
    a.slice("1:"_ct,"1:2"_ct,"..."_ct) = nm::ones(array{1,1,2});
    print(a);

    std::cout << "b:\n";
    auto b = nm::Array::arange(2,dtype);
    print(b);

    std::cout << "c=dot(a,b):\n";
    auto c = nm::dot(a,b);
    print(c);

    return 0;
}