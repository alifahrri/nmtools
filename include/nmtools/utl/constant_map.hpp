#ifndef NMTOOLS_UTL_CONSTANT_MAP_HPP
#define NMTOOLS_UTL_CONSTANT_MAP_HPP

#include "nmtools/def.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/tuple.hpp"
#include "nmtools/utl/static_map.hpp"
#include "nmtools/meta/bits/traits/is_map.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/has_value_type.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/transform/to_value.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/meta/bits/transform/append_type.hpp"

// TODO: add constant string

namespace nmtools::utl
{
    template <typename keys_t, typename values_t>
    struct constant_map
    {
        // TODO: what happened if keys is mixed index array?

        static_assert( is_tuple_v<keys_t>, "constant_map: keys must be a tuple" );
        // static_assert( is_tuple_v<values_t>, "constant_map: values must be a tuple" );
        static_assert( len_v<keys_t> == len_v<values_t>, "constant_map: number of keys and values must match" );

        // TODO: check if to_value_v of keys_t is not fail, but for values mixed with runtime is okay

        using keys_type   = keys_t;
        using values_type = values_t;

        // protected:
        values_type values_ = {};

        // implies keys must have same core type
        static constexpr auto keys_ = to_value_v<keys_t>;

        public:
        // assume keys_ has value_type
        using key_type = typename remove_cvref_t<decltype(keys_)>::value_type;
        static_assert( !is_fail_v<key_type>, "constant_map: keys must have a value type (when converted to value)" );

        // value_type is not a single type, depend on which key, skip

        static constexpr auto SIZE = len_v<keys_t>;
        static_assert( SIZE >= 0, "constant_map: size cannot be negative" );

        public:
        constexpr constant_map() {}

        // keys are compile-time constants, exposed as the constant
        // index tuple they were declared with
        static constexpr auto keys()
        {
            return keys_t{};
        }

        constexpr auto size() const noexcept
        {
            return ct_v<SIZE>;
        }

        // TODO: overload for generic
        static constexpr auto find_index(const key_type& key)
        {
            // TODO: support return constant, whenever possible
            using result_t = static_vector<key_type,SIZE>;
            auto result = result_t{};
            for (nm_size_t i=0; i<(nm_size_t)keys_.size(); i++) {
                if (keys_.at(i) == key) {
                    result.push_back(i);
                }
            }
            return result;
        }

        template <typename key_t>
        static constexpr auto get_key([[maybe_unused]] const key_t key=key_t{})
        {
            if constexpr (is_constant_index_v<key_t>) {
                return key_t::value;
            } else {
                return key;
            }
        }

        // TODO: overload for generic
        constexpr auto count(const key_type& key) const
        {
            auto key_indices = find_index(key);
            return key_indices.size();
        }

        // in-place erase not supported
        // in-place emplace not supported

        template <typename key>
        constexpr decltype(auto) operator[]([[maybe_unused]] const key k)
        {
            if constexpr (has_value_type_v<values_type>) {
                // runtime keys & runtime values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                return values_.at(idx);
            } else if constexpr (is_constant_index_v<key>) {
                // constant key: fully compile-time lookup
                constexpr auto key_indices = find_index(get_key<key>());
                if constexpr (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                constexpr auto idx = key_indices[0];
                return nmtools::get<idx>(values_);
            } else {
                // runtime key over constant values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                const values_type& cvalues = values_;
                return nmtools::at(cvalues,idx);
            }
        }

        template <typename key>
        constexpr decltype(auto) operator[]([[maybe_unused]] const key k) const
        {
            if constexpr (has_value_type_v<values_type>) {
                // runtime keys & runtime values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                return values_.at(idx);
            } else if constexpr (is_constant_index_v<key>) {
                // constant key: fully compile-time lookup
                constexpr auto key_indices = find_index(get_key<key>());
                if constexpr (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                constexpr auto idx = key_indices[0];
                return nmtools::get<idx>(values_);
            } else {
                // runtime key over constant values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                return nmtools::at(values_,idx);
            }
        }

        // same lookup as operator[]: panic on missing key (insertion impossible
        // in a constant map, so there's no non-const form like flat_map's),
        // provided for map-like familiarity.
        template <typename key>
        constexpr decltype(auto) at(const key k)
        {
            if constexpr (has_value_type_v<values_type>) {
                // runtime keys & runtime values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                return values_.at(idx);
            } else if constexpr (is_constant_index_v<key>) {
                // constant key: fully compile-time lookup
                constexpr auto key_indices = find_index(get_key<key>());
                if constexpr (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                constexpr auto idx = key_indices[0];
                return nmtools::get<idx>(values_);
            } else {
                // runtime key over constant values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                const values_type& cvalues = values_;
                return nmtools::at(cvalues,idx);
            }
        }

        template <typename key>
        constexpr decltype(auto) at(const key k) const
        {
            if constexpr (has_value_type_v<values_type>) {
                // runtime keys & runtime values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                return values_.at(idx);
            } else if constexpr (is_constant_index_v<key>) {
                // constant key: fully compile-time lookup
                constexpr auto key_indices = find_index(get_key<key>());
                if constexpr (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                constexpr auto idx = key_indices[0];
                return nmtools::get<idx>(values_);
            } else {
                // runtime key over constant values
                auto key_indices = find_index(k);
                if (!key_indices.size()) {
                    nmtools_panic( key_indices.size()
                        , "key empty" );
                }
                auto idx = key_indices[0];
                return nmtools::at(values_,idx);
            }
        }

        // out of place insert
        template <typename new_key_t, typename new_value_t>
        constexpr auto insert(const new_key_t&, const new_value_t& new_value)
        {
            constexpr auto key_indices = find_index(new_key_t::value);
            if constexpr (!key_indices.size()) {
                using new_keys_t   = append_type_t<keys_t,new_key_t>;
                using new_values_t = append_type_t<values_t,new_value_t>;

                using new_map_t = constant_map<new_keys_t,new_values_t>;

                auto result = new_map_t{};

                template_for<SIZE>([&](auto i){
                    constexpr auto I = decltype(i)::value;
                    nmtools::get<I>(result.values_) = nmtools::get<I>(values_);
                });
                nmtools::get<SIZE>(result.values_) = new_value;

                return result;
            } else {
                // assume at specific key is mutable
                // TODO: support type overwrite/replace?
                at(new_key_t{}) = new_value;
                return *this;
            }
        }
    }; // constant_map
}

namespace nmtools::meta
{
    template <typename keys_t, typename values_t>
    struct is_map<utl::constant_map<keys_t,values_t>> : true_type {};

    // number of keys == number of values
    template <typename keys_t, typename values_t>
    struct len<utl::constant_map<keys_t,values_t>>
    {
        static constexpr auto value = len_v<keys_t>;
    };

    template <typename keys_t, typename values_t>
    struct is_constant_map<utl::constant_map<keys_t,values_t>> : true_type {};

    template <typename keys_t, typename values_t>
    struct to_value<utl::constant_map<keys_t,values_t>>
    {
        static constexpr auto value = [](){
            auto keys   = to_value_v<keys_t>;
            auto values = to_value_v<values_t>;

            using v_keys_t   = typename decltype(keys)::value_type;
            using v_values_t = typename decltype(values)::value_type;

            constexpr auto N = len_v<keys_t>;
            using map_t = utl::static_map<v_keys_t,v_values_t,N>;

            auto map = map_t{};

            for (nm_size_t i=0; i<(nm_size_t)N; i++) {
                auto key = keys.at(i);
                auto value = values.at(i);
                // this require placement new
                // map.emplace(key,value);
                map[key] = value;
            }

            return map;
        }();
    };
} // namespace nmtools::meta

#endif // NMTOOLS_UTL_CONSTANT_MAP_HPP