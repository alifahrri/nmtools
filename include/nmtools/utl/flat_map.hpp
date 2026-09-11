#ifndef NMTOOLS_UTL_FLAT_MAP_HPP
#define NMTOOLS_UTL_FLAT_MAP_HPP

#include "nmtools/def.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/small_vector.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/tuple.hpp"

#ifndef NMTOOLS_SMALL_FLAT_MAP_DEFAULT_DIM
#define NMTOOLS_SMALL_FLAT_MAP_DEFAULT_DIM 8
#endif // NMTOOLS_SMALL_FLAT_MAP_DEFAULT_DIM

namespace nmtools::utl
{
    template <typename key_t, typename T, auto DIM=NMTOOLS_SMALL_FLAT_MAP_DEFAULT_DIM>
    struct flat_map
    {
        using key_type    = key_t;
        using mapped_type = T;
        using value_type  = utl::tuple<const key_type,mapped_type>;

    protected:
        using storage_type = utl::small_vector<utl::tuple<key_t,T>>;

        storage_type storage_;

    public:
        flat_map() {}

        auto size() const
        {
            return storage_.size();
        }

        auto find_index(const key_type& key) const
        {
            static_vector<nm_index_t> key_indices;
            for (nm_size_t i=0; i<(nm_size_t)storage_.size(); i++) {
                const auto& [k,v] = storage_.at(i);
                if (k == key) {
                    key_indices.push_back((nm_index_t)i);
                }
            }
            return key_indices;
        }

        auto count(const key_type& key) const
        {
            auto key_indices = find_index(key);
            return key_indices.size();
        }

        auto erase(const key_type& key)
        {
            auto key_indices = find_index(key);
            auto n = key_indices.size();
            if (n) {
                auto idx = key_indices.at(0);
                auto tmp_storage = storage_type{};
                for (nm_size_t i=0; i<(nm_size_t)storage_.size(); i++) {
                    if (i == (nm_size_t)idx) {
                        continue;
                    }
                    const auto& [k,v] = storage_.at(i);
                    tmp_storage.push_back(utl::tuple<key_t,T>{k,v});
                }
                storage_ = tmp_storage;
            }
            return n;
        }

        decltype(auto) operator[](const key_type& key)
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                storage_.push_back(utl::tuple<key_t,T>{key,mapped_type{}});
                return utl::get<1>( storage_.at( (nm_size_t)storage_.size()-1 ) );
            } else {
                auto idx = key_indices.at(0);
                return utl::get<1>( storage_.at(idx) );
            }
        }

        decltype(auto) operator[](const key_type& key) const
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                nmtools_panic( false, "key not found" );
            }
            auto idx = key_indices.at(0);
            return utl::get<1>( storage_.at(idx) );
        }

        // TODO: change return to pair<iterator,bool>
        template <typename...args_t>
        auto emplace(const key_type& key, args_t&&...args)
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                storage_.push_back(
                    utl::tuple<key_t,T>{key,mapped_type(nmtools::forward<args_t>(args)...)}
                );
            } else {
                auto idx = key_indices.at(0);
                auto* ptr = &utl::get<1>( storage_.at(idx) );
                new(ptr) mapped_type(nmtools::forward<args_t>(args)...);
            }
        }

        decltype(auto) at(const key_type& key)
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                nmtools_panic( false, "key not found" );
            }
            auto idx = key_indices.at(0);
            return utl::get<1>( storage_.at(idx) );
        }

        decltype(auto) at(const key_type& key) const
        {
            auto key_indices = find_index(key);
            if (!key_indices.size()) {
                nmtools_panic( false, "key not found" );
            }
            auto idx = key_indices.at(0);
            return utl::get<1>( storage_.at(idx) );
        }

        struct iter_t
        {
            const flat_map& map;
            nm_size_t i = 0;

            decltype(auto) operator*() const
            {
                const auto& pair = map.storage_.at(i);
                auto copy = value_type{utl::get<0>(pair),utl::get<1>(pair)};
                return copy;
            }

            auto operator==(const iter_t& rhs) const
            {
                // also check address of map?
                return i == rhs.i;
            }

            auto operator!=(const iter_t& rhs) const
            {
                // also check address of map?
                return i != rhs.i;
            }

            auto operator++()
            {
                i++;
                return *this;
            }
        }; // iter_t

        auto begin() const
        {
            return iter_t{*this,0};
        }

        auto end() const
        {
            return iter_t{*this,size()};
        }
    }; // flat_map

    template <typename key_t, typename T, auto DIM>
    auto begin(const flat_map<key_t,T,DIM>& map)
    {
        return map.begin();
    }

    template <typename key_t, typename T, auto DIM>
    auto end(const flat_map<key_t,T,DIM>& map)
    {
        return map.end();
    }
}

#endif // NMTOOLS_UTL_FLAT_MAP_HPP
