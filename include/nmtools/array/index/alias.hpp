#ifndef NMTOOLS_ARRAY_INDEX_ALIAS_HPP
#define NMTOOLS_ARRAY_INDEX_ALIAS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/max.hpp"

namespace nmtools::index
{
    struct alias_t {};

    template <typename operands_ids_t, typename reserved_ids_t>
    constexpr auto alias(const operands_ids_t& operands_ids, const reserved_ids_t& reserved_ids)
    {
        using result_t = meta::resolve_optype_t<alias_t,operands_ids_t,reserved_ids_t>;

        auto result = result_t{};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto size = len(operands_ids);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(size);
            }
            nm_index_t max_reserved_id = [&]{
                if constexpr (is_none_v<reserved_ids_t>) {
                    return -1;
                } else {
                    return max(reserved_ids);
                }
            }();
            nm_index_t max_operands_id = [&]{
                if constexpr (meta::is_constant_index_array_v<operands_ids_t>) {
                    return max(operands_ids);
                } else {
                    return -1;
                }
            }();
            nm_index_t max_id = max_reserved_id > max_operands_id ? max_reserved_id : max_operands_id;
            nm_size_t tracked_id = max_id + 1;
            for (nm_size_t i=0; i<(nm_size_t)size; i++) {
                auto id = at(operands_ids,i);
                if (id < 0) {
                    at(result,i) = tracked_id;
                    tracked_id++;
                } else {
                    at(result,i) = id;
                }
            }
        }

        return result;
    }

    struct generate_alias_t {};

    #ifndef NMTOOLS_ALIAS_DEFAULT_BASE
    #define NMTOOLS_ALIAS_DEFAULT_BASE 512
    #endif

    #ifndef NMTOOLS_ALIAS_DEFAULT_PRIME
    #define NMTOOLS_ALIAS_DEFAULT_PRIME 1033
    #endif

    // polynomial rolling hash
    template <typename aliases_t, typename base_t=meta::ct<NMTOOLS_ALIAS_DEFAULT_BASE>, typename prime_t=meta::ct<NMTOOLS_ALIAS_DEFAULT_PRIME>>
    constexpr auto generate_alias(const aliases_t& aliases, base_t base=base_t{}, prime_t prime=prime_t{})
    {
        using result_t = meta::resolve_optype_t<generate_alias_t,aliases_t,base_t,prime_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            result = 0;
            auto N = len(aliases);
            for (nm_size_t i=0; i<(nm_size_t)N; i++) {
                result = (result * base + at(aliases,i)) % prime;
            }
        }

        return result;
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct ALIAS_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct GENERATE_ALIAS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename operands_ids_t, typename reserved_ids_t>
    struct resolve_optype<
        void, index::alias_t, operands_ids_t, reserved_ids_t
    > {
        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto SIZE   = len_v<operands_ids_t>;
            [[maybe_unused]] constexpr auto B_SIZE = bounded_size_v<operands_ids_t>;
            if constexpr (
                !is_index_array_v<operands_ids_t>
                || !(is_index_array_v<reserved_ids_t> || is_none_v<reserved_ids_t>)
            ) {
                using type = error::ALIAS_UNSUPPORTED<operands_ids_t,reserved_ids_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<operands_ids_t>
                && (is_constant_index_array_v<reserved_ids_t> || is_none_v<reserved_ids_t>)
            ) {
                constexpr auto operands_ids = to_value_v<operands_ids_t>;
                constexpr auto reserved_ids = to_value_v<reserved_ids_t>;
                constexpr auto result = index::alias(operands_ids,reserved_ids);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type   = type_t<decltype(init)>;
                    using result_type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<result_type>;
                },as_value_v<nmtools_tuple<>>);
            } else if constexpr (SIZE > 0) {
                using type = nmtools_array<nm_size_t,SIZE>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_SIZE)>) {
                using type = nmtools_static_vector<nm_size_t,B_SIZE>;
                return as_value_v<type>;
            } else {
                // TODO: support small_vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename aliases_t, typename base_t, typename prime_t>
    struct resolve_optype<
        void, index::generate_alias_t, aliases_t, base_t, prime_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_array_v<aliases_t>
                || !is_index_v<base_t>
                || !is_index_v<prime_t>
            ) {
                using type = error::GENERATE_ALIAS_UNSUPPORTED<aliases_t,base_t,prime_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<aliases_t>
                && is_constant_index_v<base_t>
                && is_constant_index_v<prime_t>
            ) {
                constexpr auto aliases = to_value_v<aliases_t>;
                constexpr auto base    = to_value_v<base_t>;
                constexpr auto prime   = to_value_v<prime_t>;
                constexpr auto result  = index::generate_alias(aliases,base,prime);
                using type = meta::ct<(nm_index_t)result>;
                return as_value_v<type>;
            } else {
                using type = nm_index_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_ALIAS_HPP