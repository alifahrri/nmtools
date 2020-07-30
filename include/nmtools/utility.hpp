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

        namespace tag {
            struct insert {};
            struct raw {};

            template <typename T, typename V, typename = void>
            struct resolve_insert_tag {};

            template <typename T, typename V>
            struct resolve_insert_tag<T,V
                , std::void_t<decltype(std::declval<T>().insert(std::declval<T>().end(),std::declval<V>()))>
            > { using type = insert; };

            template <typename T, typename V>
            struct resolve_insert_tag<T,V
                , std::enable_if_t< std::is_same_v<T,std::array<typename T::value_type,std::tuple_size<T>::value> > 
                > /* enable_if */
            > { using type = raw; };
        } // namespace tag

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

            /* TODO: remove */
            /* BEGIN : inserter boilerplate */
            template <typename Container, typename Value>
            auto insert(Container &d, Value v, tag::insert) 
                /* This decltype is actually redundant (?) */
                -> decltype(d.insert(std::begin(d),v),void()) 
            {
                d.insert(std::begin(d),v);
            }

            template <typename Container, typename Value>
            auto insert(Container &d, Value v, tag::raw) 
                /* This decltype is actually redundant (?) */
                -> decltype(*std::begin(d)=v,void()) 
            {
                *std::begin(d)=v;
            }

            template <typename Container, typename Value, typename Iterator>
            auto insert(Container &d, Iterator pos, Value v, tag::insert) 
                /* This decltype is actually redundant (?) */
                -> decltype(d.insert(pos,v),void()) 
            {
                d.insert(pos,v);
            }

            template <typename Container, typename Value, typename Iterator>
            auto insert(Container &d, Iterator pos, Value v, tag::raw) 
                /* This decltype is actually redundant (?) */
                -> decltype(*pos=v,void()) 
            {
                *pos=v;
            }

            template <typename Container, typename InputIterator, typename Iterator>
            auto insert(Container &d, Iterator pos, InputIterator begin, InputIterator end, tag::insert) 
                -> decltype(d.insert(pos,begin,end),void()) 
            {
                d.insert(pos,begin,end);
            }

            template <typename Container, typename InputIterator, typename Iterator>
            auto insert(Container &d, Iterator pos, InputIterator begin, InputIterator end, tag::raw) 
                -> decltype(begin != end, begin++, pos++, *pos = *begin, void())
            {
                auto p = pos;
                for (auto it = begin; (it != end) && (pos != std::end(d)); it++) {
                    *p = *it; p++;
                }
            }
            /* END : inserter boilerplate */

            template <size_t N, size_t ...I>
            auto append_array(auto a, std::index_sequence<I...>, auto value) 
                -> std::array<typename decltype(a)::value_type, N>
            {
                return {a[I]..., value};
            }
        } // namespace detail 

        /* TODO: remove */
        /* entrypoints */
        template <typename Container, typename Value>
        auto insert(Container &d, Value v) 
        -> decltype(detail::insert(d,v,typename tag::resolve_insert_tag<Container,Value>::type{})) {
            using insert_tag = typename tag::resolve_insert_tag<Container,Value>::type;
            detail::insert(d,v,insert_tag{});
        }
        template <typename Container, typename Value, typename Iterator>
        auto insert(Container &d, Iterator pos, Value v) 
        -> decltype(detail::insert(d,pos,v,typename tag::resolve_insert_tag<Container,Value>::type{})) 
        {
            using insert_tag = typename tag::resolve_insert_tag<Container,Value>::type;
            detail::insert(d,pos,v,insert_tag{});
        }
        template <typename Container, typename InputIterator, typename Iterator>
        auto insert(Container &d, Iterator pos, InputIterator begin, InputIterator end)
        -> decltype(detail::insert(d,pos,begin,end,typename tag::resolve_insert_tag<Container,decltype(*begin)>::type{})) {
            using insert_tag = typename tag::resolve_insert_tag<Container,decltype(*begin)>::type;
            detail::insert(d,pos,begin,end,insert_tag{});
        }

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

        /* Collection of adaptor */

        template <typename StateType>
        constexpr auto transpose(StateType &&x) {
            static_assert(
                traits::is_transposeable<StateType>::value,
                "unsupported transpose operation"
            );
            if constexpr (traits::has_transpose_op<StateType>::value) {
                return x.transpose();
            } else if (std::is_arithmetic<StateType>::value) {
                return x;
            }
        }

        /* TODO: remove */
        template <typename Container, typename value_type = typename Container::value_type>
        constexpr auto append(Container &container, const value_type &value) 
            -> std::enable_if_t<
                traits::has_push_back_op<Container>::value, std::add_lvalue_reference_t<Container>
            > /* enable_if */
        {
            container.push_back(value);
            return (container);
        }

        /* TODO: remove */
        template <typename Container, typename value_type = typename Container::value_type>
        constexpr auto append(Container &container, const value_type &value) 
            -> std::enable_if_t<
                /* Container == std::array */           /* return type : std::array (+1 size) */
                traits::is_std_array<Container>::value, std::array<value_type,std::tuple_size<Container>::value+1>
            > /* enable_if */
        {
            constexpr size_t N = std::tuple_size<Container>::value + 1;
            using indexes = std::make_index_sequence<std::tuple_size<Container>::value>;
            return detail::append_array<N>(container, indexes{}, value);
        }

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