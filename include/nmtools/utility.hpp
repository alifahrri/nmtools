#ifndef NMTOOLS_UTILITY_HPP
#define NMTOOLS_UTILITY_HPP

#include <map>
#include <ratio>
#include <complex>
#include <vector>
#include <array>
#include <tuple>
#include <type_traits>

#include "nmtools/traits.hpp"

namespace nmtools {

    template <int Num, int Denom>
    using ratio = std::ratio<Num,Denom>;

    namespace helper {

        namespace detail {
            /* helper struct */
            template <size_t order>
            struct Order {};

            constexpr size_t triangular_number(size_t n) {
                return (n>1) ? n + triangular_number(n-1) : 1;
            }

            template <typename Scalar, size_t denom, int ... constants>
            struct Constants {
                constexpr Constants()  {}
                /* TODO : make sure these variables are compile time constants */
                constexpr static size_t N = sizeof...(constants);
                constexpr static Scalar values[sizeof...(constants)] = {
                    (Scalar(std::ratio<constants,denom>::num)/Scalar(std::ratio<constants,denom>::den))...
                };
            };

            template <typename Scalar, typename U>
            auto make_var(std::map<std::string,Scalar> &map, const U& u) {
                map[u.first] = u.second;
            }
            template <typename Scalar, typename U, typename ...T>
            auto make_var(std::map<std::string,Scalar> &map, const U& u, const T&... t) {
                make_var(map, u);
                make_var(map, t...);
            }
            template <typename Scalar, typename ...Args>
            auto log(const Args& ...args) {
                std::map<std::string,Scalar> map;
                make_var(map, args...);
                return map;
            }
        } // namespace detail

        /* TODO: remove */
        template <typename Scalar, typename Logger>
        struct Log {
            template <typename ...Args>
            static auto log(Logger *logger, const Args& ...args) {
                if(!logger) return;
                (*logger)(detail::log<Scalar>(args...));
            }
        };

        /* TODO: remove */
        template <typename Scalar>
        struct Log<Scalar,void> {
            template <typename ...Args>
            static auto log(void*, const Args& ...args) {
                return;
            }
        };

        /**
         * @brief compute nth value of fibonacci sequence
         * 
         * @tparam integer_t whole number
         * @param n
         * @return constexpr integer_t 
         */
        template <typename integer_t>
        constexpr integer_t fibonacci(integer_t n) {
            return n <= 1 ? n : fibonacci(n-1) + fibonacci(n-2);
        }

        /**
         * @brief compute fibonacci sequence up-to n
         * 
         * @tparam integer_t whole number
         * @param n 
         * @return auto 
         */
        template <typename integer_t>
        auto fibonacci_sequence(integer_t n) {
            /* TODO: make this constexpr */
            std::vector<integer_t> sequence;
            for (size_t i=0; i<n; i++)
                sequence.push_back(fibonacci(i));
            return sequence;
        }

        /**
         * @brief constexpr version to compute fibonacci sequence up-to n
         * n is passed as template parameter
         * 
         * @tparam n 
         * @return constexpr std::array<integer_t,n> 
         */
        template <size_t n, typename integer_t = size_t>
        constexpr std::array<integer_t,n> fibonacci_sequence() {
            /* NOTE: workaround for compile-time version since 
                c++17 doesn't have constexpr vector */
            std::array<integer_t,n> sequence{};
            for (size_t i=0; i<n; i++)
                sequence[i] = fibonacci(i);
            return sequence;
        }
    } // namespace helper

    constexpr auto near(auto x, auto y, auto eps=1e-9)
    {
        return fabs(x - y) < eps;
    }
} // namespace nmtools

#define VAR_NAME(X) (#X)
#define VAR_NAME_PAIR(X) std::make_pair(std::string(#X),X)
#define VNP(X) VAR_NAME_PAIR(X)
#define NARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, N, ...) N
#define NARGS(args...) NARGS_(args..., 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define CAT_(a, b) a ## b
#define CAT(a, b) CAT_(a, b)

#define name_1(x)                                                   VNP(x)
#define name_2(x, x2)                                               VNP(x) , VNP(x2)
#define name_3(x, x2, x3)                                           VNP(x) , VNP(x2), VNP(x3)
#define name_4(x, x2, x3, x4)                                       VNP(x) , VNP(x2), VNP(x3), VNP(x4)
#define name_5(x, x2, x3, x4, x5)                                   VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5)
#define name_6(x, x2, x3, x4, x5, x6)                               VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6)
#define name_7(x, x2, x3, x4, x5, x6, x7)                           VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7)
#define name_8(x, x2, x3, x4, x5, x6, x7, x8)                       VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8)
#define name_9(x, x2, x3, x4, x5, x6, x7, x8, x9)                   VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9)
#define name_10(x, x2, x3, x4, x5, x6, x7, x8, x9, x10)             VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9), VNP(x10)
#define name_11(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)        VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9), VNP(x10), VNP(x11)
#define name_12(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)   VNP(x) , VNP(x2), VNP(x3), VNP(x4), VNP(x5), VNP(x6), VNP(x7), VNP(x8), VNP(x9), VNP(x10), VNP(x11), VNP(x12)

#define names(args...) CAT(name_, NARGS(args))(args) 
#define LOGVAR(logger,...) {                                           \
                            helper::Log<Scalar,Logger>::log(        \
                                logger,                             \
                                names(__VA_ARGS__)                  \
                            );                                      \
                        }

#endif // NMTOOLS_UTILITY_HPP