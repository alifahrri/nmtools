#ifndef NMTOOLS_UTL_STATIC_MAP
#define NMTOOLS_UTL_STATIC_MAP

#include "nmtools/def.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/tuple.hpp"

#ifndef NMTOOLS_DEFAULT_STATIC_MAP_MAX_SIZE
#define NMTOOLS_DEFAULT_STATIC_MAP_MAX_SIZE (32)
#endif

namespace nmtools::utl
{
    template <typename key_t, typename T, auto Capacity=NMTOOLS_DEFAULT_STATIC_MAP_MAX_SIZE>
    struct static_map
    {
        using key_vector_type   = utl::static_vector<key_t,Capacity>;
        using value_vector_type = utl::static_vector<T,Capacity>;

        using key_type    = key_t;
        using mapped_type = T;
        using value_type  = utl::tuple<const key_type,T>;

        protected:
        key_vector_type   keys_   = {};
        value_vector_type values_ = {};

        public:
        constexpr static_map() {}

        constexpr auto size() const
        {
            return keys_.size();
        }

        constexpr auto max_size() const
        {
            return Capacity;
        }

        constexpr auto find_index(const key_type& key) const
        {
            static_vector<nm_index_t> key_indices;
            for (nm_size_t i=0; i<(nm_size_t)keys_.size(); i++) {
                if (keys_.at(i) == key) {
                    key_indices.push_back(i);
                }
            }
            return key_indices;
        }

        constexpr auto count(const key_type& key) const
        {
            auto key_indices = find_index(key);
            return key_indices.size();
        }

        constexpr auto erase(const key_type& key)
        {
            auto key_indices = find_index(key);
            auto n = key_indices.size();
            if (n) {
                auto idx = key_indices.at(0);
                auto tmp_keys   = key_vector_type{};
                auto tmp_values = value_vector_type{};
                for (nm_size_t i=0; i<keys_.size(); i++) {
                    if (i == (nm_size_t)idx) {
                        continue;
                    }
                    tmp_keys.push_back(keys_.at(i));
                }
                for (nm_size_t i=0; i<values_.size(); i++) {
                    if (i == (nm_size_t)idx) {
                        continue;
                    }
                    tmp_values.push_back(values_.at(i));
                }
                keys_   = tmp_keys;
                values_ = tmp_values;
            }
            return n;
        }

        constexpr decltype(auto) operator[](const key_type& key)
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                auto size = values_.size();
                values_.resize(size+1);
                keys_.push_back(key);
                return values_[size];
            } else {
                auto idx = key_indices[0];
                return values_[idx];
            }
        }

        constexpr decltype(auto) operator[](const key_type& key) const
        {
            auto key_indices = find_index(key);
            auto idx = key_indices[0];
            return values_[idx];
        }

        constexpr decltype(auto) at(const key_type& key)
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                nmtools_panic( false, "key not found" );
            }
            auto idx = key_indices[0];
            return values_[idx];
        }

        constexpr decltype(auto) at(const key_type& key) const
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                nmtools_panic( false, "key not found" );
            }
            auto idx = key_indices[0];
            return values_[idx];
        }
    };
}

#endif // NMTOOLS_UTL_STATIC_MAP