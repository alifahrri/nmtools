#ifndef NMTOOLS_ARRAY_AT_HPP
#define NMTOOLS_ARRAY_AT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

// TODO: move to nmtools/utility/

namespace nmtools::impl
{
    namespace error
    {
        template <typename...>
        struct AT_UNSUPPORTED : meta::detail::fail_t {};
    }

    /**
     * @brief Customization point for actual at implementation
     * 
     * @tparam array_t 
     * @tparam index_type 
     */
    template <typename array_t, typename index_type>
    struct at_t
    {
        constexpr decltype(auto) operator()([[maybe_unused]] const array_t& a, [[maybe_unused]] index_type i) const
        {
            if constexpr (meta::is_constant_index_array_v<array_t> && meta::is_index_v<index_type>) {
                // allow accessing constant index array using index type for const only
                constexpr auto array = meta::to_value_v<array_t>;
                // TODO: return constant index if index_type is constant index
                return at_t<meta::remove_cvref_t<decltype(array)>,index_type>{}(array,i);
            } else if constexpr (meta::has_at_v<const array_t&,index_type>) {
                return a.at(i);
            } else if constexpr (meta::has_square_bracket_v<const array_t&,index_type>) {
                return a[i];
            } else if constexpr (meta::has_bracket_v<const array_t&,index_type>) {
                return a(i);
            } else {
                return error::AT_UNSUPPORTED<const array_t&,index_type>{};
            }
        }

        constexpr decltype(auto) operator()(array_t& a, [[maybe_unused]] index_type i) const
        {
            if constexpr (meta::has_at_v<array_t&,index_type>) {
                return a.at(i);
            } else if constexpr (meta::has_square_bracket_v<array_t&,index_type>) {
                return a[i];
            } else if constexpr (meta::has_bracket_v<array_t&,index_type>) {
                return a(i);
            } else {
                return error::AT_UNSUPPORTED<array_t&,index_type>{};
            }
        }
    };

    template <typename array_t, typename index_type>
    constexpr inline auto at_v = at_t<array_t, index_type>{};
}

namespace nmtools
{

    /** @addtogroup utility
     * @ingroup array
     * Collections of utility functions for array-like objects
     * @{
     */

    // NOTE: forward declare here since definition at shape.hpp
    // includes this file.
    // this implies the usage of "at" which compile-time branch chooses to call "len"
    // must also include shape.hpp
    template <typename array_t>
    constexpr auto len(const array_t& array);

    template <auto i, typename array_t>
    constexpr decltype(auto) at(const array_t& a)
    {
        using index_type = decltype(i);

        if constexpr (meta::has_template_get_v<const array_t&,i>) {
            // use nmtools::get to avoid ambiguous call with stl get
            return nmtools::get<i>(a);
        } else {
            constexpr auto at = impl::at_v<array_t,index_type>;
            return at(a,i);
        }
    } // at

    template <auto i, typename array_t>
    constexpr decltype(auto) at(array_t& a)
    {
        using index_type = decltype(i);

        if constexpr (meta::has_template_get_v<array_t&,i>) {
            return nmtools::get<i>(a);   
        } else {
            constexpr auto at = impl::at_v<array_t,index_type>;
            return at(a,i);
        }
    } // at

    using last_type = meta::remove_cvref_t<decltype(Last)>;

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam array_t 
     * @tparam index_type 
     * @param a 
     * @param i 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type>
    constexpr decltype(auto) at(const array_t& a, [[maybe_unused]] index_type i)
    {
        // TODO (wrap std metafunctions): wrap as meta::is_same_v
        if constexpr (meta::is_same_v<meta::remove_cvref_t<index_type>,last_type>) {
            const auto N = len(a);
            const auto index = N - 1;
            return at(a,index);
        } else if constexpr (meta::is_constant_index_v<index_type>) {
            // assume constant index has static member value
            constexpr auto index = index_type::value;
            if constexpr (index < 0) {
                const auto N = len(a) + index;
                return at(a,meta::make_unsigned_t<decltype(N)>{N});
            } else {
                return at<index>(a);
            }
        } else if constexpr (meta::is_signed_v<index_type>) {
            // NOTE: make index to be unsigned to avoid infinite recursion
            using index_t = meta::make_unsigned_t<index_type>;
            // NOTE: avoid recurse that triggers error: use of 'constexpr decltype(auto) nmtools::at before deduction of 'auto'
            // on arm gcc 9.2.1 (stm32 target)
            // use function object impl::at instead
            constexpr auto at = impl::at_v<array_t,index_t>;
            if (i < 0) {
                const auto N = len(a);
                // N should be usigned at this point so no infinite recursion,
                // but len may not be returning unsigned hence makes index to be
                // unsigned so cast anyway
                const auto index = N + i; // i < 0
                return at(a,static_cast<index_t>(index));
            } else {
                return at(a,static_cast<index_t>(i));
            }
        } else {
            constexpr auto at = impl::at_v<array_t,index_type>;
            return at(a,i);
        }
    } // at

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam array_t 
     * @tparam index_type 
     * @param a 
     * @param i 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type>
    constexpr decltype(auto) at(array_t& a, [[maybe_unused]] index_type i)
    {
        if constexpr (meta::is_same_v<meta::remove_cvref_t<index_type>,last_type>) {
            const auto N = len(a);
            const auto index = N - 1;
            return at(a,index);
        } else if constexpr (meta::is_constant_index_v<index_type>) {
            // assume constant index has static member value
            constexpr auto index = index_type::value;
            if constexpr (index < 0) {
                const auto N = len(a) + index;
                return at(a,meta::make_unsigned_t<decltype(N)>{N});
            } else {
                return at<index>(a);
            }
        } else if constexpr (meta::is_signed_v<index_type>) {
            using index_t = meta::make_unsigned_t<index_type>;
            // NOTE: avoid recurse that triggers error: use of 'constexpr decltype(auto) nmtools::at before deduction of 'auto'
            // on arm gcc 9.2.1 (stm32 target)
            // use function object impl::at instead
            constexpr auto at = impl::at_v<array_t,index_t>;
            if (i < 0) {
                const auto N = len(a);
                const auto index = N + i; // i < 0
                return at(a,static_cast<index_t>(index));
            } else {
                return at(a,static_cast<index_t>(i));
            }
        } else {
            constexpr auto at = impl::at_v<array_t,index_type>;
            return at(a,i);
        }
    } // constexpr decltype(auto) at

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam array_t 
     * @tparam index_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type, typename...index_types>
    constexpr decltype(auto) at(const array_t& a, index_type i, index_types...indices)
    {
        if constexpr (meta::has_atnd_v<const array_t&,index_type,index_types...>) {
            return a.at(i,indices...);
        } else if constexpr (meta::has_bracketnd_v<const array_t&,index_type,index_types...>) {
            return a.operator[](i,indices...);
        } else if constexpr (meta::has_funcnd_v<const array_t&,index_type,index_types...>) {
            return a(i,indices...);
        } else {
            return at(at(a,i),indices...);
        }
    } // at(a,...)

    // TODO: remove
    template <auto i, auto j, typename array_t>
    constexpr decltype(auto) at(const array_t& a)
    {
        // TODO (wrap std metafunctions): wrap as meta::common_type_t
        using index_type = meta::promote_index_t<decltype(i),decltype(j)>;
        if constexpr (meta::has_square_bracket2d_v<const array_t&,index_type>) {
            return a[{i,j}];
        } else if constexpr (meta::has_bracket2d_v<const array_t&,index_type>) {
            return a(i,j);
        } else {
            return at<j>(at<i>(a));
        }
    } // constexpr decltype(auto) at(const array_t& a, index_type i, index_type j)

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam array_t 
     * @tparam index_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type, typename...index_types>
    constexpr decltype(auto) at(array_t& a, index_type i, index_types...indices)
    {
        if constexpr (meta::has_atnd_v<array_t&,index_type,index_types...>) {
            return a.at(i,indices...);
        } else if constexpr (meta::has_bracketnd_v<array_t&,index_type,index_types...>) {
            return a.operator[](i,indices...);
        } else if constexpr (meta::has_funcnd_v<array_t&,index_type,index_types...>) {
            return a(i,indices...);
        } else {
            return at(at(a,i),indices...);
        }
    } // at(a,...)

    /** @} */ // end group utility
} // namespace nmtools

namespace nmtools
{
    namespace detail
    {
        /**
         * @brief actual implementation of apply_at
         * 
         * @tparam array_t array type
         * @tparam type_list packed indices type
         * @tparam Is compile-time index sequence
         * @param array array to be accessed
         * @param indices packed indices to access array
         * @return constexpr decltype(auto) 
         */
        template <typename array_t, typename type_list, size_t...Is, template <auto...> typename sequence>
        constexpr decltype(auto) apply_at_impl(const array_t& array, const type_list& indices, sequence<Is...>)
        {
            return nmtools::at(array, nmtools::get<Is>(indices)...);
        } // apply_at_impl

        // NOTE: avoid forwarding reference to avoid using stl forward
        template <typename array_t, typename type_list, size_t...Is, template <auto...> typename sequence>
        constexpr decltype(auto) apply_at_impl(array_t& array, const type_list& indices, sequence<Is...>)
        {
            return nmtools::at(array, nmtools::get<Is>(indices)...);
        } // apply_at_impl
    } //  namespace detail

    /**
     * @brief given indices packed as tuple, unpacks and call at
     * 
     * @tparam array_t 
     * @tparam type_list template template parameter, e.g. tuple
     * @tparam size_types template parameter to type_list
     * @param array array to be accessed
     * @param indices packed indices to access array
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename indices_t>
    constexpr decltype(auto) apply_at(const array_t& array, const indices_t& indices)
    {
        if constexpr (meta::len_v<indices_t> > 0) {
            constexpr auto N = meta::len_v<indices_t>;
            using sequence_t = meta::make_index_sequence<N>;
            return detail::apply_at_impl(array,indices,sequence_t{});
        }
        else {
            return at(array, indices);
        }
    } // apply_at

    template <typename array_t, typename indices_t>
    constexpr decltype(auto) apply_at(array_t& array, const indices_t& indices)
    {
        if constexpr (meta::len_v<indices_t> > 0) {
            constexpr auto N = meta::len_v<indices_t>;
            using sequence_t = meta::make_index_sequence<N>;
            return detail::apply_at_impl(array,indices,sequence_t{});
        }
        else {
            return at(array, indices);
        }
    } // apply_at
} // namespace nmtools

#endif // NMTOOLS_ARRAY_AT_HPP