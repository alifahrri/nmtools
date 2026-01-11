#include "nmtools/nmtools.hpp"
#include "nmtools/core/computational_graph.hpp"

#include <iostream>

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

int main(int argc, char** argv)
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto input = nm::random(array{3,4},dtype,gen);

    auto axis = -1;
    auto res = view::softmax(input,axis);

    /* Static computational graph: */
    auto graph = fn::get_computational_graph(res);

    /* Compile-time computational graph: */
    constexpr auto graph_v = nm::to_value_v<decltype(unwrap(graph))>;

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);
    auto graphviz_v = utils::to_string(unwrap(graph_v),utils::Graphviz);

    std::cout << "input shape: "
        << utils::to_string(nm::shape(input))
        << std::endl;
    
    std::cout << "input:\n"
        << utils::to_string(input)
        << std::endl;
    
    std::cout << "\n============================================================================\n";
    
    std::cout << "result shape: "
        << utils::to_string(nm::shape(res))
        << std::endl;
    
    std::cout << "result:\n"
        << utils::to_string(res)
        << std::endl;
    
    std::cout << "\n============================================================================\n";

    std::cout << "graphviz:\n"
        << graphviz
        << std::endl;
    
    std::cout << "\n============================================================================\n";

    std::cout << "graphviz_v:\n"
        << graphviz_v
        << std::endl;

    return 0;
}