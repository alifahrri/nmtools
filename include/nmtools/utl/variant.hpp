#ifndef NMTOOLS_UTL_VARIANT_HPP
#define NMTOOLS_UTL_VARIANT_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_trivially_destructible.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"
#include "nmtools/meta/bits/transform/type_list_at.hpp"

/*************************************************************************** */

namespace nmtools::utl
{
    template <typename always_void,typename first_t, typename...args_t>
    struct nontrivial_variant;

    template <typename element_t>
    struct nontrivial_variant<void,element_t>
    {
        using element_type = element_t;

        union
        {
            element_type element;
        };

        constexpr nontrivial_variant() noexcept
            : element{}
        {}

        // TODO: delete element
        ~nontrivial_variant() {}

        constexpr nontrivial_variant(const nontrivial_variant& other)
            : element{other.element}
        {}

        constexpr nontrivial_variant(const element_t& element)
            : element{element}
        {}

        constexpr auto index() const noexcept
        {
            return 0;
        }

        constexpr nontrivial_variant& operator=(const nontrivial_variant& other)
        {
            if constexpr (!is_trivially_destructible_v<element_type>) {
                auto* ptr = &element;
                ptr->~element_type();
            }

            new(&element) element_type(other.element);

            return *this;
        }

        template <typename T>
        constexpr nontrivial_variant& operator=(const T& val)
        {
            static_assert( is_same_v<T,element_type>
                , "unsupported type for variant assignment" );
            
            element = val;

            return *this;
        }

        template <typename T>
        constexpr auto* get_if() noexcept
        {
            static_assert( is_same_v<T,element_type>
                , "unsupported type passed to get_if" );
            
            using ptr_type = element_type*;

            return ptr_type{&element};
        }

        template <auto I>
        constexpr auto* get_if() noexcept
        {
            static_assert( I < 1 );

            using ptr_type = element_type*;

            return ptr_type{&element};
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            static_assert( is_same_v<T,element_type>
                , "unsupported type passed to get_if" );
            
            using ptr_type = element_type*;

            return ptr_type{&element};
        }

        template <auto I>
        constexpr auto* get_if() const noexcept
        {
            static_assert( I < 1 );

            using ptr_type = element_type*;

            return ptr_type{&element};
        }
    };

    template <typename first_t, typename second_t>
    struct nontrivial_variant<void,first_t,second_t>
    {
        using first_type  = first_t;
        using second_type = second_t;

        // TODO: check all type unique
        union
        {
            first_type  first;
            second_type second;
        };
        nm_size_t tag = 0;

        constexpr nontrivial_variant() noexcept
            : first{}
            , tag{0}
        {}

        // TODO: make this only in not trivially destructible type to make it constexpr
        ~nontrivial_variant() {}

        constexpr nontrivial_variant(const nontrivial_variant& other)
            : tag{other.tag}
        {
            if (tag == 0) {
                new(&first) first_type(other.first);
            } else {
                new(&second) second_type(other.second);
            }
        }

        constexpr nontrivial_variant(const first_t& first)
            : first(first)
            , tag{0}
        {}

        constexpr nontrivial_variant(const second_t& second)
            : second(second)
            , tag{1}
        {}

        constexpr auto index() const noexcept
        {
            return tag;
        }

        constexpr nontrivial_variant& operator=(const nontrivial_variant& other)
        {
            if (tag == other.tag) {
                if (tag == 0) {
                    first = other.first;
                } else {
                    second = other.second;
                }
            } else {
                if (tag == 0) {
                    if constexpr (!is_trivially_destructible_v<first_type>) {
                        auto* ptr = &first;
                        ptr->~first_type();
                    }
                } else if (tag == 1) {
                    if constexpr (!is_trivially_destructible_v<second_type>) {
                        auto* ptr = &second;
                        ptr->~second_type();
                    }
                }
                if (other.tag == 0) {
                    new(&first) first_type(other.first);
                    tag = 0;
                } else {
                    new(&second) second_type(other.second);
                    tag = 1;
                }
            }
            return *this;
        }

        // TODO: use universal reference
        template <typename T>
        constexpr nontrivial_variant& operator=(const T& val)
        {
            // assume copy assignment supported on both first & second
            // TODO: better error or proper handling
            static_assert(
                is_same_v<T,first_type> || is_same_v<T,second_type>
                , "unsupported type for variant assignment"
            );
            *this = nontrivial_variant(val);
            return *this;
        }

        template <typename T>
        constexpr auto* get_if() noexcept
        {
            static_assert( is_same_v<T,first_type> || is_same_v<T,second_type>
                , "unsupported type passed to get_if" );

            if constexpr (is_same_v<T,first_type>) {
                using ptr_type = first_type*;
                if (tag == 0) {
                    return ptr_type{&first};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = second_type*;
                if (tag == 1) {
                    return ptr_type{&second};
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            static_assert( is_same_v<T,first_type> || is_same_v<T,second_type>
                , "unsupported type passed to get_if" );

            if constexpr (is_same_v<T,first_type>) {
                using ptr_type = const first_type*;
                if (tag == 0) {
                    return ptr_type{&first};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = const second_type*;
                if (tag == 1) {
                    return ptr_type{&second};
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <auto I>
        constexpr auto* get_if() noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t>,I>;
            return get_if<T>();
        }

        template <auto I>
        constexpr auto* get_if() const noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t>,I>;
            return get_if<T>();
        }
    };

    template <typename first_t, typename second_t, typename...args_t>
    struct nontrivial_variant<enable_if_t<(sizeof...(args_t))>,first_t,second_t,args_t...>
    {
        // TODO: check all type unique
        using head_type = first_t;
        // TODO: support trivial_variant
        using rest_type = nontrivial_variant<void,second_t,args_t...>;
        union
        {
            head_type head;
            rest_type rest;
        };
        nm_size_t tag = 0;

        constexpr nontrivial_variant() noexcept
            : head{}
            , tag{0}
        {}

        // TODO: make this only in not trivially destructible type to make it constexpr
        ~nontrivial_variant() {}

        constexpr nontrivial_variant(const nontrivial_variant& other)
            : tag{other.tag}
        {
            if (tag == 0) {
                new(&head) head_type(other.head);
            } else {
                new(&rest) rest_type(other.rest);
            }
        }

        constexpr nontrivial_variant(const first_t& first)
            : head(first)
            , tag(0)
        {}

        template <typename arg_t>
        constexpr nontrivial_variant(const arg_t& arg)
            : rest(arg)
            , tag(1)
        {}

        constexpr auto index() const noexcept
        {
            if (tag == 0) {
                return tag;
            } else {
                return 1+rest.index();
            }
        }

        constexpr nontrivial_variant& operator=(const nontrivial_variant& other)
        {
            if (tag == other.tag) {
                if (tag == 0) {
                    head = other.head;
                } else {
                    rest = other.rest;
                }
            } else {
                if (tag == 0) {
                    if constexpr (!is_trivially_destructible_v<head_type>) {
                        auto* ptr = &head;
                        ptr->~head_type();
                    }
                } else if (tag == 1) {
                    if constexpr (!is_trivially_destructible_v<rest_type>) {
                        auto *ptr = &rest;
                        ptr->~rest_type();
                    }
                }
                if (other.tag == 0) {
                    new(&head) head_type(other.head);
                    tag = 0;
                } else {
                    new(&rest) rest_type(other.rest);
                    tag = 1;
                }
            }
            return *this;
        }

        // TODO: use universal reference
        template <typename T>
        constexpr nontrivial_variant& operator=(const T& val)
        {
            *this = nontrivial_variant(val);
            return *this;
        }

        template <typename T>
        constexpr auto* get_if() noexcept
        {
            if constexpr (is_same_v<T,head_type>) {
                using ptr_type = head_type*;
                if (tag == 0) {
                    return ptr_type{&head};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = T*;
                if (tag == 1) {
                    return rest.template get_if<T>();
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            if constexpr (is_same_v<T,head_type>) {
                using ptr_type = const head_type*;
                if (tag == 0) {
                    return ptr_type{&head};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = const T*;
                if (tag == 1) {
                    return rest.template get_if<T>();
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <auto I>
        constexpr auto* get_if() noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t,args_t...>,I>;
            return get_if<T>();
        }

        template <auto I>
        constexpr auto* get_if() const noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t,args_t...>,I>;
            return get_if<T>();
        }
    };
}

/*************************************************************************** */

namespace nmtools::utl
{
    template <typename always_void, typename first_t, typename...args_t>
    struct trivial_variant;

    template <typename element_t>
    struct trivial_variant<void,element_t>
    {
        using element_type = element_t;

        union
        {
            element_type element;
        };

        constexpr trivial_variant() noexcept
            : element{}
        {}

        constexpr trivial_variant(const trivial_variant& other)
            : element{other.element}
        {}

        constexpr trivial_variant(const element_t& element)
            : element{element}
        {}

        constexpr auto index() const noexcept
        {
            return 0;
        }

        constexpr trivial_variant& operator=(const trivial_variant& other)
        {
            if constexpr (!is_trivially_destructible_v<element_type>) {
                auto* ptr = &element;
                ptr->~element_type();
            }

            new(&element) element_type(other.element);

            return *this;
        }

        template <typename T>
        constexpr trivial_variant& operator=(const T& val)
        {
            static_assert( is_same_v<T,element_type>
                , "unsupported type for variant assignment" );
            
            element = val;

            return *this;
        }

        template <typename T>
        constexpr auto* get_if() noexcept
        {
            static_assert( is_same_v<T,element_type>
                , "unsupported type passed to get_if" );
            
            using ptr_type = element_type*;

            return ptr_type{&element};
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            static_assert( is_same_v<T,element_type>
                , "unsupported type passed to get_if" );
            
            using ptr_type = const element_type*;

            return ptr_type{&element};
        }

        template <auto I>
        constexpr auto* get_if() noexcept
        {
            static_assert( I == 0
                , "unsupported index passed to get_if" );
            
            using ptr_type = element_type*;

            return ptr_type{&element};
        }

        template <auto I>
        constexpr auto* get_if() const noexcept
        {
            static_assert( I == 0
                , "unsupported index passed to get_if" );
            
            using ptr_type = const element_type*;

            return ptr_type{&element};
        }
    };

    template <typename first_t, typename second_t>
    struct trivial_variant<void,first_t,second_t>
    {
        using first_type  = first_t;
        using second_type = second_t;

        // TODO: check all type unique
        union
        {
            first_type  first;
            second_type second;
        };
        nm_size_t tag = 0;

        constexpr trivial_variant() noexcept
            : first{}
            , tag{0}
        {}

        constexpr trivial_variant(const trivial_variant& other)
            : tag{other.tag}
        {
            if (tag == 0) {
                new(&first) first_type(other.first);
            } else {
                new(&second) second_type(other.second);
            }
        }

        constexpr trivial_variant(const first_t& first)
            : first(first)
            , tag{0}
        {}

        constexpr trivial_variant(const second_t& second)
            : second(second)
            , tag{1}
        {}

        constexpr auto index() const noexcept
        {
            return tag;
        }

        constexpr trivial_variant& operator=(const trivial_variant& other)
        {
            if (tag == other.tag) {
                if (tag == 0) {
                    first = other.first;
                } else {
                    second = other.second;
                }
            } else {
                if (other.tag == 0) {
                    new(&first) first_type(other.first);
                    tag = 0;
                } else {
                    new(&second) second_type(other.second);
                    tag = 1;
                }
            }
            return *this;
        }

        // TODO: use universal reference
        template <typename T>
        constexpr trivial_variant& operator=(const T& val) noexcept
        {
            // assume copy assignment supported on both first & second
            // TODO: better error or proper handling
            static_assert(
                is_same_v<T,first_type> || is_same_v<T,second_type>
                , "unsupported type for variant assignment"
            );
            if constexpr (is_same_v<T,first_type>) {
                first = val;
                tag = 0;
            } else /* if constexpr (is_same_v<T,second_type>) */ {
                second = val;
                tag = 1;
            }
            return *this;
        }

        template <typename T>
        constexpr auto* get_if() noexcept
        {
            static_assert( is_same_v<T,first_type> || is_same_v<T,second_type>
                , "unsupported type passed to get_if" );

            if constexpr (is_same_v<T,first_type>) {
                using ptr_type = first_type*;
                if (tag == 0) {
                    return ptr_type{&first};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = second_type*;
                if (tag == 1) {
                    return ptr_type{&second};
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            static_assert( is_same_v<T,first_type> || is_same_v<T,second_type>
                , "unsupported type passed to get_if" );

            if constexpr (is_same_v<T,first_type>) {
                using ptr_type = const first_type*;
                if (tag == 0) {
                    return ptr_type{&first};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = const second_type*;
                if (tag == 1) {
                    return ptr_type{&second};
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <auto I>
        constexpr auto* get_if() noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t>,I>;
            return get_if<T>();
        }

        template <auto I>
        constexpr auto* get_if() const noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t>,I>;
            return get_if<T>();
        }
    };

    template <typename first_t, typename second_t, typename...args_t>
    struct trivial_variant<enable_if_t<(sizeof...(args_t))>,first_t,second_t,args_t...>
    {
        // TODO: check all type unique
        using head_type = first_t;
        using rest_type = trivial_variant<void,second_t,args_t...>;
        union
        {
            head_type head;
            rest_type rest;
        };
        nm_size_t tag = 0;

        constexpr trivial_variant() noexcept
            : head{}
            , tag{0}
        {}

        constexpr trivial_variant(const trivial_variant& other)
            : tag{other.tag}
        {
            if (tag == 0) {
                new(&head) head_type(other.head);
            } else {
                new(&rest) rest_type(other.rest);
            }
        }

        constexpr trivial_variant(const first_t& first)
            : head(first)
            , tag(0)
        {}

        template <typename arg_t>
        constexpr trivial_variant(const arg_t& arg)
            : rest(arg)
            , tag(1)
        {}

        constexpr auto index() const noexcept
        {
            if (tag == 0) {
                return tag;
            } else {
                return 1+rest.index();
            }
        }

        constexpr trivial_variant& operator=(const trivial_variant& other)
        {
            if (tag == other.tag) {
                if (tag == 0) {
                    head = other.head;
                } else {
                    rest = other.rest;
                }
            } else {
                // new(&rest) rest_type(other.rest);
                // tag = other.tag;
                if (other.tag == 0) {
                    new(&head) head_type(other.head);
                    tag = 0;
                } else {
                    new(&rest) rest_type(other.rest);
                    tag = 1;
                }
            }
            return *this;
        }

        // TODO: use universal reference
        template <typename T>
        constexpr trivial_variant& operator=(const T& val)
        {
            if constexpr (is_same_v<T,head_type>) {
                head = val;
                tag = 0;
            } else {
                rest = val;
                tag = 1;
            }
            return *this;
        }

        template <typename T>
        constexpr auto* get_if() noexcept
        {
            if constexpr (is_same_v<T,head_type>) {
                using ptr_type = head_type*;
                if (tag == 0) {
                    return ptr_type{&head};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = T*;
                if (tag == 1) {
                    return rest.template get_if<T>();
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            if constexpr (is_same_v<T,head_type>) {
                using ptr_type = const head_type*;
                if (tag == 0) {
                    return ptr_type{&head};
                } else {
                    return ptr_type{nullptr};
                }
            } else {
                using ptr_type = const T*;
                if (tag == 1) {
                    return rest.template get_if<T>();
                } else {
                    return ptr_type{nullptr};
                }
            }
        }

        template <auto I>
        constexpr auto* get_if() noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t,args_t...>,I>;
            return get_if<T>();
        }

        template <auto I>
        constexpr auto* get_if() const noexcept
        {
            using T = at_t<meta::type_list<first_t,second_t,args_t...>,I>;
            return get_if<T>();
        }
    };
}

/*************************************************************************** */

namespace nmtools::utl
{
    template <typename first_t, typename...args_t>
    using variant = conditional_t<
        (is_trivially_destructible_v<first_t> && (is_trivially_destructible_v<args_t> && ...))
        , trivial_variant<void,first_t,args_t...>
        , nontrivial_variant<void,first_t,args_t...>
    >;
}

namespace nmtools::meta
{
    using utl::trivial_variant;
    using utl::nontrivial_variant;

    template <typename T>
    struct variant_size;

    template <typename...args_t>
    struct variant_size<trivial_variant<void,args_t...>>
    {
        static constexpr auto value = sizeof...(args_t);
    };

    template <typename...args_t>
    struct variant_size<nontrivial_variant<void,args_t...>>
    {
        static constexpr auto value = sizeof...(args_t);
    };

    template <typename T>
    constexpr inline auto variant_size_v = variant_size<T>::value;

    template <nm_size_t I, typename T>
    struct variant_alternative;

    template <nm_size_t I, typename...args_t>
    struct variant_alternative<I,trivial_variant<void,args_t...>>
    {
        using type = at_t<meta::type_list<args_t...>,I>;
    };

    template <nm_size_t I, typename...args_t>
    struct variant_alternative<I,nontrivial_variant<void,args_t...>>
    {
        using type = at_t<meta::type_list<args_t...>,I>;
    };

    template <nm_size_t I, typename T>
    using variant_alternative_t = type_t<variant_alternative<I,T>>;

    template <typename V, typename T>
    struct variant_has_type : false_type {};

    template <typename T, typename...args_t>
    struct variant_has_type<
        trivial_variant<void,args_t...>
        , T
    > {
        static constexpr auto value = (is_same_v<T,args_t> || ...);
    };

    template <typename T, typename...args_t>
    struct variant_has_type<
        nontrivial_variant<void,args_t...>
        , T
    > {
        static constexpr auto value = (is_same_v<T,args_t> || ...);
    };

    template <typename V, typename T>
    constexpr inline auto variant_has_type_v = variant_has_type<V,T>::value;
}

namespace nmtools
{
    using meta::variant_size_v;
    using meta::variant_alternative_t;
    using meta::variant_has_type_v;
}

#endif // NMTOOLS_UTL_VARIANT_HPP