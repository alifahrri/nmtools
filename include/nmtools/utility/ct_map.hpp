#ifndef NMTOOLS_UTILITY_CT_MAP_HPP
#define NMTOOLS_UTILITY_CT_MAP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/tuple_cat.hpp"
#include "nmtools/utility/get.hpp"
#include "nmtools/utility/isequal/isequal.hpp"

namespace nmtools::utility
{
    namespace error
    {
        template <typename...>
        struct CT_MAP_OUT_OF_RANGE : meta::detail::fail_t {};
    }

    template <typename keys_t=nmtools_tuple<>, typename values_t=nmtools_tuple<>>
    struct ct_map
    {
        // TODO: assert keys to be tuple of constant index
        static_assert( meta::is_constant_index_array_v<keys_t>, "keys must be known at compile time" );
        static_assert( meta::is_tuple_v<keys_t>, "expect keys to be tuple" );
        static_assert( meta::is_tuple_v<values_t>, "expect values to be tuple" );
        static_assert( meta::len_v<keys_t> == meta::len_v<values_t>, "expect keys and values to be same size" );

        using keys_type = const keys_t;
        using values_type = const values_t;

        keys_type keys_;
        values_type values_;

        constexpr ct_map(const keys_t& keys, const values_t& values)
            : keys_(keys)
            , values_(values)
        {}

        template <typename other_keys_t, meta::enable_if_t<utils::isequal(meta::to_value_v<keys_t>,meta::to_value_v<other_keys_t>),int> =0 >
        constexpr ct_map(const other_keys_t&, const values_t& values)
            : keys_{}
            , values_(values)
        {}

        constexpr ct_map()
            : keys_{}
            , values_{}
        {}

        static constexpr auto SIZE = meta::len_v<keys_t>;

        constexpr auto size() const noexcept
        {
            return meta::ct_v<SIZE>;
        }

        constexpr auto keys() const noexcept
        {
            return keys_;
        }

        template <typename key_t>
        constexpr auto contains(key_t key) const noexcept
        {
            constexpr auto KEY = decltype(key)::value;
            return meta::template_reduce<SIZE>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto key_i = meta::remove_cvref_t<decltype(get<I>(this->keys_))>::value;
                if constexpr (key_i == KEY) {
                    return meta::true_type{};
                } else {
                    return init;
                }
            }, meta::false_type{});
        }

        template <typename key_t>
        constexpr auto at(key_t key) const noexcept
        {
            constexpr auto KEY = decltype(key)::value;
            return meta::template_reduce<SIZE>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto key_i = meta::remove_cvref_t<decltype(get<I>(keys_))>::value;
                if constexpr (key_i == KEY) {
                    return get<I>(values_);
                } else {
                    return init;
                }
            }, error::CT_MAP_OUT_OF_RANGE{});
        }

        template <typename key_t, typename value_t>
        constexpr auto insert(key_t key, [[maybe_unused]] value_t value) const noexcept
        {
            auto contain_key = contains(key);
            if constexpr (decltype(contain_key)::value) {
                return *this;
            } else {
                auto new_keys   = tuple_append(keys_,key);
                auto new_values = tuple_append(values_,value);
                using new_keys_t   = meta::remove_cvref_t<decltype(new_keys)>;
                using new_values_t = meta::remove_cvref_t<decltype(new_values)>;
                return ct_map<new_keys_t,new_values_t>{
                    new_keys,
                    new_values
                };
            }
        }

        template <typename key_t>
        constexpr auto erase(key_t key) const noexcept
        {
            // keep the order
            constexpr auto KEY = decltype(key)::value;
            auto init = ct_map<nmtools_tuple<>,nmtools_tuple<>>();
            return meta::template_reduce<SIZE>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto key_i = meta::remove_cvref_t<decltype(get<I>(keys_))>::value;
                if constexpr (key_i == KEY) {
                    return init;
                } else {
                    auto ct_key = meta::ct_v<key_i>;
                    return init.insert(ct_key,at(ct_key));
                }
            }, init);
        }

        template <typename key_t, typename value_t>
        constexpr auto update(key_t key, value_t value) const noexcept
        {
            auto contain_key = contains(key);
            if constexpr (!decltype(contain_key)::value) {
                return insert(key, value);
            } else {
                // keep the order
                constexpr auto KEY = decltype(key)::value;
                auto init = ct_map<nmtools_tuple<>,nmtools_tuple<>>();
                return meta::template_reduce<SIZE>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    constexpr auto key_i = meta::remove_cvref_t<decltype(get<I>(keys_))>::value;
                    if constexpr (key_i == KEY) {
                        return init.insert(key,value);
                    } else {
                        auto ct_key = meta::ct_v<key_i>;
                        return init.insert(ct_key,at(ct_key));
                    }
                }, init);
            }
        }
    };

    template <typename keys_t, typename values_t>
    ct_map(const keys_t&, const values_t&) -> ct_map<keys_t,values_t>;
} // namespace nmtools::utility

#endif // NMTOOLS_UTILITY_CT_MAP_HPP