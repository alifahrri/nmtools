#ifndef NMTOOLS_BENCH_NANOBENCH_COMMON_HPP
#define NMTOOLS_BENCH_NANOBENCH_COMMON_HPP

#include "nmtools/traits.hpp"
#include "nmtools/array/utility.hpp"
#include "nanobench/nanobench.h"
#include <fmt/core.h>
#include <boost/type_index.hpp>
#include <fstream>
#include <sstream>
#include <array>
#include <map>
#include <memory>

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
    } // auto make_func_args

    /**
     * @brief make pretty name for function args typename(s) and non-type template paramter(s).
     * 
     * @tparam Args non-type template parameters
     * @param func string represents function name
     * @param args arguments that is intended to be passed to actual func
     * @return auto 
     */
    template <auto...Args>
    auto make_func_args(std::string func, const auto&...args)
    {
        std::stringstream ss;
        constexpr auto n = (sizeof...(args));
        constexpr auto m = (sizeof...(Args));
        auto typenames = std::array<std::string,n>{
            {boost::typeindex::type_id<decltype(args)>().pretty_name()...}
        };
        /* non-type template parameters, assuming can be converted to string*/
        auto tparams = std::array<std::string,m>{
            {std::to_string(Args)...}
        };
        ss << func;
        if constexpr (sizeof...(Args)) {
            ss << '<';
            for (size_t i=0; i<m; i++) {
                ss << tparams[i];
                if (i!=(m-1))
                    ss << ",";
            }
            ss << '>';
        }
        ss << '(';
        for (size_t i=0; i<n; i++) {
            ss << typenames[i];
            if (i!=(n-1))
                ss << ",";
        }
        ss << ')';
        return ss.str();
    } // auto make_func_args

    /**
     * @brief given array-like or scalar `t`,
     * return formatted string with shape information,
     * square brackets indicates array-like
     * while only scalar indicate scalar type.
     * 
     * @tparam T deduced via template argument deduction
     * @param t 
     * @return auto 
     */
    template <typename T>
    auto format_shape(const T& t)
    {
        if constexpr (traits::is_array2d_v<T>) {
            auto [rows,cols] = matrix_size(t);
            return fmt::format("[{},{}]", rows, cols);
        }
        else if constexpr (traits::is_array1d_v<T>) {
            auto n = vector_size(t);
            return fmt::format("[{}]", n);
        }
        else {
            return fmt::format("{}", t);
        }
    } // auto format_shape

    template <typename T, typename...Args>
    auto format_shape(const T& t, const Args&...args)
    {
        return fmt::format("{}, {}", format_shape(t), format_shape(args...));
    }

    inline void gen(std::string const& typeName, char const* mustacheTemplate,
         ankerl::nanobench::Bench const& bench)
    {

        std::ofstream templateOut("mustache.template." + typeName);
        templateOut << mustacheTemplate;

        std::ofstream renderOut("mustache.render." + typeName);
        ankerl::nanobench::render(mustacheTemplate, bench, renderOut);
    }

    inline void gen(char const* mustacheTemplate,
         ankerl::nanobench::Bench const& bench)
    {
        auto title = bench.title() + ".html";
        std::ofstream templateOut("mustache.template." + title);
        templateOut << mustacheTemplate;

        std::ofstream renderOut("mustache.render." + title);
        ankerl::nanobench::render(mustacheTemplate, bench, renderOut);
    }

    /**
     * @brief singleton class to track `ankerl::nanobench::Bench` instances,
     * to make sure relative speed computed properly for the same test case
     * since Bench restarts the relative computation for each new Bench instance created.
     * 
     */
    struct TrackedBench
    {
        public:
            using Bench = ankerl::nanobench::Bench;
            /**
             * @brief Get the instance object
             * 
             * @return TrackedBench& 
             */
            static TrackedBench& get_instance()
            {
                static TrackedBench instance;
                return instance;
            }
            /**
             * @brief Get the bench object
             * 
             * @param title access registered Bench instance, will be created first if it doesn't exist
             * @return std::shared_ptr<Bench> 
             */
            auto get_bench(const std::string& title) -> std::shared_ptr<Bench>
            {
                if (registry.count(title) == 0) {
                    registry[title] = std::make_shared<Bench>();
                    auto b = registry[title];
                    (*b).title(title)
                        .warmup(100)
                        .epochs(1000)
                        .relative(true);
                    (*b).performanceCounters(true);
                }
                return registry.at(title);
            }
        private:
            TrackedBench() {}
            std::map<std::string,std::shared_ptr<Bench>> registry;
    }; // struct TrackedBench
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
template <auto...Args>                                  \
auto func(ankerl::nanobench::Bench *bench, const auto&...args) {                            \
    auto name = nmtools::bench::nanobench::common::make_func_args<Args...>(#func,args...);  \
    bench->run(name, [&](){                             \
        auto x = ns::func<Args...>(args...);            \
        ankerl::nanobench::doNotOptimizeAway(x);        \
    });                                                 \
    /* also return result, may be useful for testing */ \
    auto ret = ns::func<Args...>(args...);              \
    return ret;                                         \
}                                                       \

/**
 * @brief helper macro to simultaneously run benchmark and unit testing
 * 
 */
#define NMTOOLS_BENCH_DOCTEST_SUBCASE(func, expect, ...) \
{   \
    using nmtools::bench::nanobench::common::format_shape;                          \
    using nmtools::bench::nanobench::common::TrackedBench;                          \
    std::string title = fmt::format("{}({})", #func, format_shape(__VA_ARGS__));    \
    auto b = TrackedBench::get_instance().get_bench(title);                         \
    NMTOOLS_TESTING_DOCTEST_SUBCASE(func, expect, b.get(), __VA_ARGS__);            \
}   \

/**
 * @brief define testing using doctest
 * 
 */
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

#include "testing/testing.hpp"

/* TODO: remove, prefer explicit call at caller site */
using nmtools::bench::nanobench::common::gen;

#endif // NMTOOLS_BENCH_NANOBENCH_COMMON_HPP