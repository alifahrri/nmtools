#ifndef NMTOOLS_ARRAY_RANDOM_ENGINE_HPP
#define NMTOOLS_ARRAY_RANDOM_ENGINE_HPP

#if __has_include(<random>)

#define NMTOOLS_HAS_RANDOM_ENGINE
#include <random>

#include "nmtools/meta.hpp"

namespace nmtools
{
    template <typename T, typename bit_generator_t>
    struct random_engine_t
    {
        static constexpr auto distribution_vtype = [](){
            // TODO: support another kind of distribution: e.g. bernoulli, poisson, normal, sampling
            // https://en.cppreference.com/w/cpp/header/random

            if constexpr (meta::is_integral_v<T>) {
                return meta::as_value_v<std::uniform_int_distribution<T>>;
            } else {
                return meta::as_value_v<std::uniform_real_distribution<T>>;
            }
        }();
        using distribution_t = meta::type_t<decltype(distribution_vtype)>;

        distribution_t dist_;
        bit_generator_t gen_;

        random_engine_t(T min, T max, bit_generator_t gen)
            : dist_(distribution_t{min,max})
            , gen_(gen)
        {}

        auto operator()()
        {
            return dist_(gen_);
        }
    };

    template <typename T=float>
    auto random_engine(T min=T{0}, T max=T{1})
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        return random_engine_t(min,max,gen);
    } // random_engine
}

#endif // __has_include(<random>)

#endif // NMTOOLS_ARRAY_RANDOM_ENGINE_HPP