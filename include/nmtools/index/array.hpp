#ifndef NMTOOLS_INDEX_ARRAY_HPP
#define NMTOOLS_INDEX_ARRAY_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/get.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/has_value.hpp"

#include "nmtools/index/add_indices.hpp"
#include "nmtools/index/append.hpp"
#include "nmtools/index/subtract_indices.hpp"
#include "nmtools/index/multiply_indices.hpp"
#include "nmtools/index/divide_indices.hpp"
#include "nmtools/index/remove_dims.hpp"

namespace nmtools::index
{
    template <typename buffer_t>
    constexpr auto array(const buffer_t& index_array);

    template <typename buffer_t>
    struct array_t
    {
        static constexpr auto DIM = len_v<buffer_t>;
        using buffer_type = conditional_t<
            is_bounded_array_v<buffer_t>
            , nmtools_array<nm_size_t,(DIM < 0 ? 0 : DIM)>
            , buffer_t
        >;
        using element_type = get_element_type_t<buffer_type>;

        buffer_type data_;

        constexpr array_t()
            : data_{}
        {}

        constexpr array_t(const buffer_type& buffer)
            : data_(buffer)
        {}

        // TODO: create constructor to handle raw bounded array


        template <typename other_t>
        constexpr auto append(other_t other) const
        {
            auto result = index::append(data_,other);
            return array(result);
        }

        template <typename axis_t, typename keepdims_t=meta::false_type>
        constexpr auto remove_dims(const axis_t& axis, keepdims_t keepdims=keepdims_t{}) const noexcept
        {
            auto result = index::remove_dims(data_,axis,keepdims);
            return array(result);
        }

        template <typename rhs_t>
        constexpr auto add(const rhs_t& rhs) const noexcept
        {
            auto result = add_indices(data_,rhs);
            return array(result);
        }

        template <typename rhs_t>
        constexpr auto multiply(const rhs_t& rhs) const noexcept
        {
            auto result = multiply_indices(data_,rhs);
            return array(result);
        }

        template <typename rhs_t>
        constexpr auto subtract(const rhs_t& rhs) const noexcept
        {
            auto result = subtract_indices(data_,rhs);
            return array(result);
        }

        template <typename rhs_t>
        constexpr auto divide(const rhs_t& rhs) const noexcept
        {
            auto result = divide_indices(data_,rhs);
            return array(result);
        }

        template <typename other_t>
        constexpr auto operator+(const other_t& other) const
        {
            auto result = this->add(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator*(const other_t& other) const
        {
            auto result = this->multiply(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator-(const other_t& other) const
        {
            auto result = this->subtract(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator/(const other_t& other) const
        {
            auto result = this->divide(other);
            return result;
        }

        template <typename index_t>
        constexpr decltype(auto) operator[](index_t i) noexcept
        {
            return (at(data_,i));
        }

        template <typename index_t>
        constexpr decltype(auto) operator[](index_t i) const noexcept
        {
            return (at(data_,i));
        }

        constexpr auto size() const
        {
            return len(data_);
        }

        template <nm_size_t I>
        constexpr decltype(auto) get()
        {
            return nmtools::get<I>(data_);
        }

        template <nm_size_t I>
        constexpr decltype(auto) get() const
        {
            return nmtools::get<I>(data_);
        }
    };

    template <typename buffer_t>
    constexpr auto array(const buffer_t& index_array)
    {
        using result_t = array_t<buffer_t>;

        auto result = result_t(index_array);

        return result;
    }

    template <typename buffer_t>
    constexpr auto array(const array_t<buffer_t>& index_array)
    {
        return index_array;
    }

    // TODO: fix to_string
} // namespace nmtools::index

namespace nmtools
{
    template <nm_size_t I, typename buffer_t>
    struct get_t<I,index::array_t<buffer_t>>
    {
        constexpr decltype(auto) operator()(index::array_t<buffer_t>& array) noexcept
        {
            return array.template get<I>();
        }

        constexpr decltype(auto) operator()(const index::array_t<buffer_t>& array) const noexcept
        {
            return array.template get<I>();
        }
    };
}

#if __has_include(<tuple>)
#include <tuple>
#else
namespace std
{
    template <typename T>
    struct tuple_size;

    template <nm_size_t I, typename T>
    struct tuple_element
}
#endif

template <typename T>
struct std::tuple_size<nmtools::index::array_t<T>>
{
    static constexpr auto value = nmtools::len_v<T>;
};

template <nm_size_t I, typename T>
struct std::tuple_element<I,nmtools::index::array_t<T>>
    : std::tuple_element<I,T> {};

namespace nmtools::index
{
    struct full_t {};

    template <typename dim_t, typename value_t>
    constexpr auto full(dim_t dim, value_t value)
    {
        using result_t = resolve_optype_t<full_t,dim_t,value_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            if constexpr (is_resizable_v<result_t>) {
                result.resize(dim);
            }
            for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                at(result,i) = value;
            }
        }

        return array(result);
    }

    template <typename dim_t>
    constexpr auto zeros(dim_t dim)
    {
        return full(dim,ct_v<(nm_size_t)0>);
    }

    template <typename dim_t>
    constexpr auto ones(dim_t dim)
    {
        return full(dim,ct_v<(nm_size_t)1>);
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_FULL_UNSUPPORTED : detail::fail_t {};
    }

    template <typename dim_t, typename value_t>
    struct resolve_optype<
        void, index::full_t, dim_t, value_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<dim_t>
                || !is_index_v<value_t>
            ) {
                using type = error::INDEX_FULL_UNSUPPORTED<dim_t,value_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<dim_t>
                && is_constant_index_v<value_t>
            ) {
                constexpr auto value  = to_value_v<value_t>;
                constexpr auto result = unwrap(index::full(dim_t{},value));
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    using type_i = ct<at(result,I)>;
                    using type = append_type_t<init_t,type_i>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_constant_index_v<dim_t>) {
                constexpr auto DIM = dim_t::value;
                using type = nmtools_array<nm_size_t,DIM>;
                return as_value_v<type>;
            } else {
                // TODO: use small vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

// TODO: move out from impl namespace
namespace nmtools::impl
{
    template <typename buffer_t>
    struct len_t<
        index::array_t<buffer_t>
    > {
        constexpr auto operator()(const index::array_t<buffer_t>& a) const noexcept
        {
            return nmtools::len(a.data_);
        }
    };
}

namespace nmtools::meta
{
    template <typename buffer_t>
    struct is_index_array<index::array_t<buffer_t>>
        : is_index_array<buffer_t> {};
    
    template <typename buffer_t>
    struct is_constant_index_array<index::array_t<buffer_t>>
        : is_constant_index_array<buffer_t> {};

    template <typename buffer_t>
    struct is_clipped_index_array<index::array_t<buffer_t>>
        : is_clipped_index_array<buffer_t> {};

    template <typename buffer_t>
    struct is_dynamic_index_array<index::array_t<buffer_t>>
        : is_dynamic_index_array<buffer_t> {};

    template <typename buffer_t>
    struct is_fixed_index_array<index::array_t<buffer_t>>
        : is_fixed_index_array<buffer_t> {};
    
    template <typename buffer_t>
    struct is_hybrid_index_array<index::array_t<buffer_t>>
        : is_hybrid_index_array<buffer_t> {};
    
    template <typename buffer_t>
    struct is_mixed_index_array<index::array_t<buffer_t>>
        : is_mixed_index_array<buffer_t> {};
    
    template <typename buffer_t>
    struct is_nullable_index_array<index::array_t<buffer_t>>
        : is_nullable_index_array<buffer_t> {};
    
    template <typename buffer_t>
    struct len<index::array_t<buffer_t>>
        : len<buffer_t> {};
    
    template <typename buffer_t>
    struct max_len<index::array_t<buffer_t>>
        : max_len<buffer_t> {};
    
    template <typename buffer_t>
    struct get_element_or_common_type<index::array_t<buffer_t>>
        : get_element_or_common_type<buffer_t> {};
    
    template <typename buffer_t>
    struct to_value<index::array_t<buffer_t>>
        : to_value<buffer_t> {};
    
    // TODO: remove fixed_index_array_size
    template <typename buffer_t>
    struct fixed_index_array_size<index::array_t<buffer_t>>
        : fixed_index_array_size<buffer_t> {};
}

#endif // NMTOOLS_INDEX_ARRAY_HPP