#ifndef NMTOOLS_BENCHMARKS_BENCH_HPP
#define NMTOOLS_BENCHMARKS_BENCH_HPP

// prefer nanobench/nanobench.h (maybe system installed)
// over nanobench.h
#if __has_include("nanobench/nanobench.h")
    #include "nanobench/nanobench.h"
#else
    #include "nanobench.h"
#endif

#include <fstream>
#include <sstream>
#include <array>
#include <map>
#include <memory>
#include <cstdlib>

namespace nmtools::benchmarks
{
    /**
     * @brief singleton class to track `ankerl::nanobench::Bench` instances,
     * to make sure relative speed computed properly for the same test case
     * since Bench restarts the relative computation for each new Bench instance created.
     *
     * This singleton listens to the following environment variables:
     * - `NMTOOLS_TESTBENCH_QUIET` : Do not print to cout.
     * - `NMTOOLS_TESTBENCH_EPOCHS` : Controls number of epochs, the number of measurements to perform, expects integer.
     * - `NMTOOLS_TESTBENCH_WARMUP` : Sets a number of iterations that are initially performed without any measurements, expects integer.
     * - `NMTOOLS_TESTBENCH_OUTPUT_DIR` : Output directory.
     * - `NMTOOLS_TESTBENCH_OUTPUT_CSV` : Save results to csv format.
     * - `NMTOOLS_TESTBENCH_OUTPUT_JSON` : Save results to json format.
     * - `NMTOOLS_TESTBENCH_OUTPUT_BOXPLOT` : Save results to boxplot html format.
     * - `NMTOOLS_TESTBENCH_OUTPUT_ALL` : Enable all outputs.
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
            } // get_instance

            /**
             * @brief Run and benchmark a function with given title and name.
             *
             * Title will determine the benchmark object, use same title to compare
             * various function call. The title will also determine the output filename.
             * 
             * @tparam dont_optimize 
             * @tparam F 
             * @param title benchmark title
             * @param name case name
             * @param f function to be benchmarked
             * @return auto 
             */
            template <bool dont_optimize=true, typename F>
            static auto run(const std::string& title, const std::string& name, F& f)
            {
                auto bench = benchmarks::TrackedBench::get_instance().get_bench(title);
                bench->run(name, [&](){
                    [[maybe_unused]] auto x = f();
                    if constexpr (dont_optimize)
                        ankerl::nanobench::doNotOptimizeAway(x);
                });
                return f();
            } // run
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
                        .warmup(warmup)
                        .epochs(epochs)
                        .relative(true);
                    (*b).performanceCounters(true);
                    if (quiet)
                        (*b).output(nullptr);
                }
                return registry.at(title);
            } // get_bench
        private:
            TrackedBench()
            {
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_QUIET"); env)
                    quiet = static_cast<bool>(std::stol(env));
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_EPOCHS"); env)
                    epochs = std::stol(env);
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_WARMUP"); env)
                    warmup = std::stol(env);
            }
            ~TrackedBench()
            {
                bool output_csv     = false;
                bool output_json    = false;
                bool output_pyperf  = false;
                bool output_boxplot = false;
                std::string output_dir("./");
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_OUTPUT_CSV"); env)
                    output_csv = static_cast<bool>(std::stol(env));
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_OUTPUT_JSON"); env)
                    output_json = static_cast<bool>(std::stol(env));
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_OUTPUT_BOXPLOT"); env)
                    output_boxplot = static_cast<bool>(std::stol(env));
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_OUTPUT_PYPERF"); env)
                    output_pyperf = static_cast<bool>(std::stol(env));
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_OUTPUT_ALL"); env) {
                    auto output_all = static_cast<bool>(std::stol(env));
                    if (output_all) {
                        output_csv     = true;
                        output_json    = true;
                        output_boxplot = true;
                        output_pyperf  = true;
                    }
                }
                if (auto env = std::getenv("NMTOOLS_TESTBENCH_OUTPUT_DIR"); env) {
                    output_dir = env;
                    // make sure like directory
                    output_dir += "/";
                }
                for (const auto& [title, bench] : registry)
                {
                    if (output_csv) {
                        auto fmt = ankerl::nanobench::templates::csv();
                        std::ofstream output(output_dir+title+".csv");
                        (*bench).render(fmt,output);
                    }
                    if (output_json) {
                        auto fmt = ankerl::nanobench::templates::json();
                        std::ofstream output(output_dir+title+".json");
                        (*bench).render(fmt,output);
                    }
                    if (output_boxplot) {
                        auto fmt = ankerl::nanobench::templates::htmlBoxplot();
                        std::ofstream output(output_dir+title+".html");
                        (*bench).render(fmt,output);
                    }
                    // only available on certain version of nanobench
                    #if (ANKERL_NANOBENCH_VERSION_MAJOR < 4)
                    #else 
                    #if (ANKERL_NANOBENCH_VERSION_MAJOR==4 && ANKERL_NANOBENCH_VERSION_MINOR >= 3) || (ANKERL_NANOBENCH_VERSION_MAJOR > 4)
                    if (output_pyperf) {
                        auto fmt = ankerl::nanobench::templates::pyperf();
                        for (const auto& result : (*bench).results()) {
                            auto case_name = result.config().mBenchmarkName;
                            auto output_path = output_dir+title+"-"+case_name+"-pyperf.json";
                            std::ofstream output(output_path);
                            ankerl::nanobench::render(fmt,{result},output);
                        }
                    }
                    #endif
                    #endif // ANKERL_NANOBENCH_VERSION_MAJOR
                }
                // mustache templates
                if (output_csv) {
                    auto fmt = ankerl::nanobench::templates::csv();
                    std::ofstream templ(output_dir+"mustache-template.csv");
                    templ << fmt;
                }
                if (output_json) {
                    auto fmt = ankerl::nanobench::templates::json();
                    std::ofstream templ(output_dir+"mustache-template.json");
                    templ << fmt;
                }
                if (output_boxplot) {
                    auto fmt = ankerl::nanobench::templates::htmlBoxplot();
                    std::ofstream templ(output_dir+"mustache-template.html");
                    templ << fmt;
                }
            }
            std::map<std::string,std::shared_ptr<Bench>> registry;
            bool quiet    = false;
            size_t epochs = 1000;
            size_t warmup = 10;
    }; // struct TrackedBench
} // namespace nmtools::benchmarks

#endif // NMTOOLS_TESTING_BENCHMARKS_BENCH_HPP