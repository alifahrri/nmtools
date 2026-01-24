#ifndef NMTOOLS_TILEKIT_THREAD_POOL_HPP
#define NMTOOLS_TILEKIT_THREAD_POOL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/ndarray/array.hpp"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <pthread.h>

#include "nmtools/profiling.hpp"

namespace nmtools::tilekit
{
    template <typename ctx_t>
    class thread_pool
    {
    public:
        thread_pool(size_t num_threads, bool enable_cpu_affinity=true, int stride=1)
        {
            stop = false;
            for (size_t i=0; i<num_threads; i++) {
                workers.emplace_back([this,i,enable_cpu_affinity,stride]{
                    if (enable_cpu_affinity) {
                        int cpu_id = i * stride;

                        cpu_set_t cpuset;
                        CPU_ZERO(&cpuset);

                        CPU_SET(cpu_id,&cpuset);

                        int rc = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
                        if (rc != 0) {
                            std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
                        }
                    }

                    std::string name = "Worker " + std::to_string(i);
                    if (name.length() > 15) {
                        name.resize(15);
                    }
                    #ifdef TRACY_ENABLE
                    tracy::SetThreadName(name.c_str());
                    #else
                    pthread_setname_np(pthread_self(), name.c_str());
                    #endif // TRACY_ENABLE

                    while (true) {
                        std::function<void()> task;

                        {
                            std::unique_lock<decltype(queue_mutex)> lock(queue_mutex);

                            condition.wait(lock, [this]{
                                return stop || !tasks.empty();
                            });

                            if (stop && tasks.empty()) {
                                return;
                            }

                            task = std::move(tasks.front());
                            tasks.pop();
                            #ifdef TRACY_ENABLE
                            TracyPlot("Queue Size", (int64_t)tasks.size());
                            #endif // TRACY_ENABLE
                        }

                        {
                            nmtools_tracy_zone_scoped("Worker Task Processing");
                            task();
                        }
                    }
                });
            }
        }

        ~thread_pool()
        {
            {
                std::unique_lock<decltype(queue_mutex)> lock(queue_mutex);
                stop = true;
            }
            condition.notify_all();
            for (std::thread& worker : workers) {
                worker.join();
            }
        }

        template <typename fun_t, typename...args_t>
        auto enqueue(fun_t&& fun, args_t&&...args)
            -> std::future<std::invoke_result_t<fun_t,args_t...>>
        {
            using return_type = std::invoke_result_t<fun_t,args_t...>;
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<fun_t>(fun), std::forward<args_t>(args)...)
            );

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<decltype(queue_mutex)> lock(queue_mutex);
                tasks.emplace([task](){ (*task)(); });
                #ifdef TRACY_ENABLE
                TracyPlot("Queue Size", (int64_t)tasks.size());
                #endif // TRACY_ENABLE
            }
            condition.notify_one();

            return res;
        }

        size_t num_workers() const
        {
            return workers.size();
        }

        template <typename kernel_t, typename...args_t>
        auto launch(size_t work_size, kernel_t&& kernel, args_t&&...args)
        {
            auto promises = std::vector<std::future<bool>>();
            for (nm_size_t i=0; i<work_size; i++) {
                promises.push_back(this->enqueue([&,i,work_size]{
                    nmtools_tracy_zone_scoped("Kernel run");
                    auto ctx = ctx_t::create_context(i,work_size);
                    kernel(ctx,nmtools::forward<args_t>(args)...);
                    return true;
                }));
            }
            return promises;
        }

        template <typename kernel_t, typename...args_t>
        auto eval(size_t work_size, kernel_t&& kernel, args_t&&...args)
        {
            auto promises = this->launch(work_size
                , nmtools::forward<kernel_t>(kernel)
                , nmtools::forward<args_t>(args)...);
            auto success = true;
            for (nm_size_t i=0; i<work_size; i++) {
                success &= promises[i].get();
            }
            return success;
        }
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;

        #ifdef TRACY_ENABLE
        TracyLockable(std::mutex, queue_mutex);
        #else
        std::mutex queue_mutex;
        #endif
        std::condition_variable_any condition;
        bool stop;
    };
}

#endif // NMTOOLS_TILEKIT_THREAD_POOL_HPP