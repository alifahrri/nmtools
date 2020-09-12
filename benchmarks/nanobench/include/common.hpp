#ifndef NMTOOLS_BENCH_NANOBENCH_COMMON_HPP
#define NMTOOLS_BENCH_NANOBENCH_COMMON_HPP

#include "nanobench/nanobench.h"
#include <boost/type_index.hpp>
#include <fstream>
#include <sstream>
#include <array>

namespace nmtools::bench::nanobench::common
{
    /**
     * @brief make pretty name for function args typename(s).
     * 
     * @tparam Args function argument(s) to be converted to string
     * @param func function name
     * @return auto string formatted with `func(typename(s)...)`
     */
    template <typename ...Args>
    auto make_func_args(std::string func)
    {
        std::stringstream ss;
        constexpr auto n = (sizeof...(Args));
        auto typenames = std::array<std::string,n>{
            {boost::typeindex::type_id<Args>().pretty_name()...}
        };
        ss << func << '(';
        for (size_t i=0; i<n; i++) {
            ss << typenames[i];
            if (i!=(n-1))
                ss << ",";
        }
        ss << ')';
        return ss.str();
    }

    void gen(std::string const& typeName, char const* mustacheTemplate,
         ankerl::nanobench::Bench const& bench)
    {

        std::ofstream templateOut("mustache.template." + typeName);
        templateOut << mustacheTemplate;

        std::ofstream renderOut("mustache.render." + typeName);
        ankerl::nanobench::render(mustacheTemplate, bench, renderOut);
    }

    void gen(char const* mustacheTemplate,
         ankerl::nanobench::Bench const& bench)
    {
        auto title = bench.title() + ".html";
        std::ofstream templateOut("mustache.template." + title);
        templateOut << mustacheTemplate;

        std::ofstream renderOut("mustache.render." + title);
        ankerl::nanobench::render(mustacheTemplate, bench, renderOut);
    }
} // nmtools::bench::nanobench::common

#define NMTOOLS_BENCH_WRAPPER(ns, func)                 \
template <typename ...Args>                             \
auto func(ankerl::nanobench::Bench *bench, const char* name, const Args&...args) {   \
    bench->run(name, [&](){                             \
        auto x = ns::func(args...);                     \
        ankerl::nanobench::doNotOptimizeAway(x);        \
    });                                                 \
    /* also return result, may be useful for testing */ \
    auto ret = ns::func(args...);                       \
    return ret;                                         \
}                                                       \

/**
 * @brief macro for generating nanobench wrapper function
 * with automatic function-arguments name as benchmark case name.
 * Calls boost typeindex to deduce typename(s).
 */
#define NMTOOLS_BENCH_WRAPPER_TYPEID(ns, func)          \
template <typename ...Args>                             \
auto func(ankerl::nanobench::Bench *bench, const Args&...args) {                   \
    auto name = nmtools::bench::nanobench::common::make_func_args<Args...>(#func); \
    bench->run(name, [&](){                             \
        auto x = ns::func(args...);                     \
        ankerl::nanobench::doNotOptimizeAway(x);        \
    });                                                 \
    /* also return result, may be useful for testing */ \
    auto ret = ns::func(args...);                       \
    return ret;                                         \
}                                                       \

/* TODO: remove, prefer explicit call at caller site */
using nmtools::bench::nanobench::common::gen;

#endif // NMTOOLS_BENCH_NANOBENCH_COMMON_HPP