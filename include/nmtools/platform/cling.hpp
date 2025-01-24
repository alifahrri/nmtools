#ifndef NMTOOLS_PLATFORM_CLING_HPP
#define NMTOOLS_PLATFORM_CLING_HPP

#include <string>
#include <fstream>

#include "xtl/xbase64.hpp"
#include "nlohmann/json.hpp"

namespace nl = nlohmann;

namespace im
{
    struct image
    {
        inline image(const std::string& filename)
        {
            std::ifstream fin(filename, std::ios::binary);
            m_buffer << fin.rdbuf();
        }

        std::stringstream m_buffer;
    };

    nl::json mime_bundle_repr(const image& i)
    {
        auto bundle = nl::json::object();
        bundle["image/png"] = xtl::base64encode(i.m_buffer.str());
        return bundle;
    }
}

#include "nmtools/utility/to_string.hpp"

namespace nmtools
{
    template <typename graph_t>
    inline auto save_graph(const graph_t& graph, const std::string& filename)
    {
        std::ofstream file(filename);
        file << utils::to_string(graph,utils::Graphviz);
        return true;
    }

    inline auto save_graph(const std::string& graph, const std::string& filename)
    {
        std::ofstream file(filename);
        file << graph;
        return true;
    }
}

#endif // NMTOOLS_PLATFORM_CLING_HPP