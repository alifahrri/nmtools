#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <map>
#include <ratio>
#include <complex>
#include <vector>
#include <array>
#include <tuple>
#include <type_traits>

namespace numeric {

    template <int Num, int Denom>
    using ratio = std::ratio<Num,Denom>;

    namespace traits {
        template <typename D, typename = void>
        struct is_std_array : std::false_type {};

        template <typename D>
        struct is_std_array<D, std::enable_if_t<
            std::is_same_v<
                D, std::array<typename D::value_type, std::tuple_size<D>::value>
            > // is_same
        > /* enable_if */ > : std::true_type {};

        template <typename D, typename = void>
        struct is_std_vector : std::false_type {};

        template <typename D>
        struct is_std_vector<D, std::enable_if_t<
            std::is_same_v<
                D, std::vector<typename D::value_type>
            > // is_same
        > /* enable_if */ > : std::true_type {};

        template <typename D, typename = void>
        struct has_push_back_op : std::false_type {};

        template <typename D>
        struct has_push_back_op<D, std::void_t<
                decltype(std::declval<D>().push_back(std::declval<typename D::value_type>()))
        > /* void_t */ > : std::true_type {};

        template <typename T, typename = void>
        struct is_std_complex : std::false_type {};

        template <typename T>
        struct is_std_complex<T, std::enable_if_t<
            std::is_same_v< 
                T, std::complex< typename T::value_type > 
            > // is_same
        > /* enable_if */ > : std::true_type {};

        template <typename T, typename = void, typename = void, typename = void, typename = void>
        struct is_insertable : std::false_type {};

        template <typename T, typename U>
        struct is_insertable<T, U, std::void_t< 
            decltype(std::declval<T>().insert(std::declval<T>().begin(),std::declval<const U&>()))
        >, void, void > : std::true_type {};

        template <typename T, typename I, typename U>
        struct is_insertable<T, I, U, std::void_t< 
            decltype(std::declval<T>().insert(std::declval<I>(),std::declval<const U&>()))
        >, void > : std::true_type {};

        template <typename T, typename I, typename B, typename E>
        struct is_insertable<T, I, B, E, std::void_t< 
            decltype(std::declval<T>().insert(std::declval<I>(),std::declval<B>(),std::declval<E>()))
        > > : std::true_type {};

        template <typename T, typename = void>
        struct is_clearable : std::false_type {};

        template <typename T>
        struct is_clearable<T, std::enable_if_t<
            std::is_same_v<
                decltype(std::declval<T>().clear()),void
            > // is_same
        > /* enable_if */ > : std::false_type {};

        template <typename T, typename = void>
        struct has_ref_square_bracket_operator : std::false_type {};

        template <typename T>
        struct has_ref_square_bracket_operator<T, std::enable_if_t< 
            !std::is_const<decltype(std::declval<T>()[size_t{}])>::value &&
            std::is_reference<decltype(std::declval<T>()[size_t{}])>::value
        > > : std::true_type {};

        template <typename T, typename = void>
        struct is_2d_array : std::false_type {};

        template <typename T>
        struct is_2d_array<T, std::void_t<decltype(std::declval<T>()[0][0])> 
        > : std::true_type {};

        template <typename T, typename U, typename = void>
        struct multiplicative : std::false_type {};

        template <typename T, typename U>
        struct multiplicative<T, U, std::void_t<
            decltype(std::declval<T>() * std::declval<U>())
        > > : std::true_type {};

        template <typename T, typename U, typename = void>
        struct additive : std::false_type {};

        template <typename T, typename U>
        struct additive<T, U, std::void_t<
            decltype(std::declval<T>() + std::declval<U>())
        > > : std::true_type {};

        template <typename F, typename...Args>
        struct is_callable {
        private:
            template <typename FN>
            constexpr static auto test(int) -> decltype(std::declval<FN>()(std::declval<Args>()...), bool()) {
                return true;
            }
            template <typename>
            constexpr static auto test(...) -> decltype(bool()) {
                return false;
            }
        public:
            constexpr static bool value = test<F>(int{});
        };

        template <typename T, typename = void>
        struct has_transpose_op : std::false_type {};

        template <typename T>
        struct has_transpose_op<T, std::void_t<
            decltype(std::declval<T>().transpose())
        > > : std::true_type {};

        template <typename T, typename = void>
        struct is_transposeable : std::false_type {};

        template <typename T>
        struct is_transposeable<T, std::enable_if_t< 
            std::is_arithmetic_v<T> || has_transpose_op<T>::value 
        > > : std::true_type {};

        /* TODO : move (?) */
        using std::begin;
        using std::end;

        template <typename T>
        struct is_iterable {
        private:
            template <typename It>
            static constexpr auto test(int)
                -> decltype(begin(std::declval<It>()), end(std::declval<It>()), bool())
            { return true; }
            template <typename It>
            static constexpr auto test(char)
            { return false; }
        public:
            constexpr static bool value = test<T>(int());
        };

        template <typename T, typename = void>
        struct is_indexable : std::false_type {};
        template <typename T>
        struct is_indexable<T, std::void_t<decltype(std::declval<T>()[size_t{}])> > : std::true_type {};

        template <typename T, typename = void>
        struct is_resizeable : std::false_type {};
        template <typename T>
        struct is_resizeable<T, 
            std::void_t<decltype(std::declval<T>().resize(std::declval<typename T::size_type>()))> >
        : std::true_type {};

        template <typename ...T>
        struct all_iterable {
            constexpr static bool value = std::conjunction_v<is_iterable<T>...>;
        };

        template <typename ...T>
        struct all_indexable {
            constexpr static bool value = std::conjunction_v<is_indexable<T>...>;
        };

        template <typename ...T>
        constexpr bool all_iterable_v = all_iterable<T...>::value;

        template <typename ...T>
        constexpr bool all_indexable_v = all_indexable<T...>::value;

        template <typename T>
        using is_std_array_or_vector = std::disjunction<is_std_array<std::decay_t<T>>,is_std_vector<std::decay_t<T>>>;

    } // namespace traits

    namespace mpl {
        template <typename T, typename V, size_t, typename=void>
        struct copy_std_container {
            using type = std::enable_if_t<
                traits::is_std_array_or_vector<T>::value, std::vector<std::decay_t<V>>
            >;
        };
        template <typename T, typename V>
        struct copy_std_container<T,V,0,std::enable_if_t<traits::is_std_array<T>::value>> {
            using type = std::enable_if_t<
                traits::is_std_array_or_vector<T>::value, std::array<std::decay_t<V>,std::tuple_size<T>::value>
            >;
        };
        template <typename T, typename V, size_t n>
        struct copy_std_container<T,V,n,std::enable_if_t<traits::is_std_array<T>::value>> {
            using type = std::enable_if_t<
                traits::is_std_array_or_vector<T>::value, std::array<std::decay_t<V>,n>
            >;
        };
        template <typename T, typename V, size_t n=0>
        using copy_std_container_t = typename copy_std_container<T,V,n>::type;
    } // namespace mpl

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

        template <typename Scalar, typename Logger>
        struct Log {
            template <typename ...Args>
            static auto log(Logger *logger, const Args& ...args) {
                if(!logger) return;
                (*logger)(detail::log<Scalar>(args...));
            }
        };

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

        template <typename Container, typename value_type = typename Container::value_type>
        constexpr auto append(Container &container, const value_type &value) 
            -> std::enable_if_t<
                traits::has_push_back_op<Container>::value, std::add_lvalue_reference_t<Container>
            > /* enable_if */
        {
            container.push_back(value);
            return (container);
        }

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
    } // namespace helper
} // namespace numeric

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

#endif // UTILITY_HPP