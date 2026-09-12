#ifndef NMTOOLS_INDEX_HASH_HPP
#define NMTOOLS_INDEX_HASH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/def.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::index
{
    struct hash_combine_t {};

    template <typename seed_t, typename value_t>
    constexpr auto hash_combine(const seed_t seed, const value_t value)
    {
        using result_t = resolve_optype_t<hash_combine_t,seed_t,value_t>;

        auto result = result_t {};

        if constexpr (!is_constant_index_v<result_t> && is_index_v<seed_t>) {
            // assume 64-bit
            constexpr auto golden_ratio = 0x9e3779b97f4a7c15;

            auto shl = (seed << 6) & 0xFFFFFFFFFFFFFFFF;
            auto shr = (seed >> 2) & 0xFFFFFFFFFFFFFFFF;

            auto mix = (value + golden_ratio + shl + shr) & 0xFFFFFFFFFFFFFFFF;
            result = seed ^ mix;
        }

        return result;
    }

    struct fnv1a_t {};

    template <typename to_hash_t>
    constexpr auto fnv1a(const to_hash_t& s)
    {
        using result_t = resolve_optype_t<fnv1a_t,to_hash_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_v<result_t>
        ) {
            constexpr auto fnv_offset_basis = 0xcbf29ce484222325;
            constexpr auto fnv_prime = 0x100000001b3;

            auto hash_val = fnv_offset_basis;

            auto n = s.size();
            for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                auto c = at(s,i);
                hash_val ^= c;
                hash_val = (hash_val * fnv_prime) & 0xFFFFFFFFFFFFFFFF;
            }
            result = hash_val;
        }

        return result;
    } // fnv1a

    struct hash_t {};

    template <typename to_hash_t>
    constexpr auto hash([[maybe_unused]] const to_hash_t& s)
    {
        using result_t = resolve_optype_t<hash_t,to_hash_t>;

        auto result = result_t {};

        if constexpr (!is_constant_index_v<result_t>
            && is_index_array_v<to_hash_t>
            && !is_fail_v<result_t>
        ) {

            // assume s is index array
            auto dim  = len(s);
            auto seed = hash_combine(0,dim);

            for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                auto s_i = at(s,i);
                seed = hash_combine(seed,s_i);
            }

            result = seed;
        } else if constexpr (is_string_v<to_hash_t>
            && !is_constant_index_v<result_t>
            && !is_fail_v<result_t>
        ) {
            result = fnv1a(s);
        } else if constexpr (is_runtime_dtype_v<to_hash_t>
            && !is_constant_index_v<result_t>
            && !is_fail_v<result_t>
        ) {
            if (is_floating_point(s)) {
                nm_size_t e {};
                nm_size_t m {};
                nm_size_t b {};
                nm_size_t n_bytes {};
                if (s == DType::Float32) {
                    using type = float;
                    e = num_exponent_bits_v<type>;
                    m = num_mantissa_bits_v<type>;
                    b = get_bias_v<type>;
                    n_bytes = 32;
                } else /* if (s == DType::Float32) */ {
                    using type = double;
                    e = num_exponent_bits_v<type>;
                    m = num_mantissa_bits_v<type>;
                    b = get_bias_v<type>;
                    n_bytes = 64;
                }
                auto to_hash = nmtools_array<nm_size_t,5>{(nm_size_t)'f',(nm_size_t)n_bytes,(nm_size_t)m,(nm_size_t)e,(nm_size_t)b};
                result = hash(to_hash);
            } else if (is_integer(s)) {
                nm_size_t sgn {};
                nm_size_t n_bytes {};
                switch (s) {
                case DType::UInt8:
                    sgn = 0;
                    n_bytes = 8;
                    break;
                case DType::UInt16:
                    sgn = 0;
                    n_bytes = 16;
                    break;
                case DType::UInt32:
                    sgn = 0;
                    n_bytes = 32;
                    break;
                case DType::UInt64:
                    sgn = 0;
                    n_bytes = 64;
                    break;
                case DType::Int8:
                    sgn = 1;
                    n_bytes = 8;
                    break;
                case DType::Int16:
                    sgn = 1;
                    n_bytes = 16;
                    break;
                case DType::Int32:
                    sgn = 1;
                    n_bytes = 32;
                    break;
                case DType::Int64:
                    sgn = 1;
                    n_bytes = 64;
                    break;
                default:
                    break;
                }
                auto to_hash = nmtools_array<nm_size_t,2>{sgn ? (nm_size_t)'i' : (nm_size_t)'u',(nm_size_t)n_bytes};
                result = hash(to_hash);
            }
        } else if constexpr (is_dtype_v<to_hash_t>
            && !is_constant_index_v<result_t>
            && !is_fail_v<result_t>
        ) {
            using type = typename to_hash_t::type;
            constexpr auto n_bytes = sizeof(type)*8;

            if constexpr (is_floating_point_v<type>) {
                constexpr auto e = num_exponent_bits_v<type>;
                constexpr auto m = num_mantissa_bits_v<type>;
                constexpr auto b = get_bias_v<type>;
                // bias can be deduced but here used to differentiate
                auto to_hash = nmtools_array<nm_size_t,5>{(nm_size_t)'f',(nm_size_t)n_bytes,(nm_size_t)m,(nm_size_t)e,(nm_size_t)b};
                result = hash(to_hash);
            } else if constexpr (is_integer_v<type>) {
                constexpr auto sgn = is_signed_v<type>;
                auto to_hash = nmtools_array<nm_size_t,2>{sgn ? (nm_size_t)'i' : (nm_size_t)'u',(nm_size_t)n_bytes};
                result = hash(to_hash);
            }
            // TODO: handle other type (e.g. nullable, clipped, etc.) 
        }

        return result;
    }
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct HASH_COMBINE_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct HASH_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct FNV1A_UNSUPPORTED : detail::fail_t {};
    }

    template <typename seed_t, typename value_t>
    struct resolve_optype<
        void, index::hash_combine_t, seed_t, value_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<seed_t>
                || !is_index_v<value_t>
            ) {
                using type = error::HASH_COMBINE_UNSUPPORTED<seed_t,value_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<seed_t>
                && is_constant_index_v<value_t>
            ) {
                constexpr auto seed   = to_value_v<seed_t>;
                constexpr auto value  = to_value_v<value_t>;
                constexpr auto result = index::hash_combine(seed,value);
                return as_value_v<ct<(nm_size_t)result>>;
            } else {
                using type = nm_size_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename to_hash_t>
    struct resolve_optype<
        void, index::hash_t, to_hash_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!(
                is_index_array_v<to_hash_t>
                || is_dtype_v<to_hash_t>
                || is_runtime_dtype_v<to_hash_t>
                || is_string_v<to_hash_t>
            )) {
                using type = error::HASH_UNSUPPORTED<to_hash_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<to_hash_t>) {
                constexpr auto to_hash = to_value_v<to_hash_t>;
                constexpr auto result  = index::hash(to_hash);
                return as_value_v<ct<result>>;
            } else {
                // TODO: compile-time compute for dtype
                using type = nm_size_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename to_hash_t>
    struct resolve_optype<
        void, index::fnv1a_t, to_hash_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_string_v<to_hash_t>) {
                using type = error::FNV1A_UNSUPPORTED<to_hash_t>;
                return as_value_v<type>;
            } else {
                // TODO: compile-time compute for "constant string"
                using type = nm_size_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_INDEX_HASH_HPP