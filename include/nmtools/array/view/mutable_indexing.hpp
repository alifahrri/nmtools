#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_INDEXING_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_INDEXING_HPP

#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/index/ndenumerate.hpp"
#include "nmtools/utils/isequal/isequal.hpp"

namespace nmtools::view
{
    template <typename array_t, typename indexer_t>
    struct mutable_indexing_t
    {
        using operand_type = meta::fwd_mutable_operand_t<array_t>;
        using array_type   = operand_type;
        using indexer_type = indexer_t;
        using dst_shape_type = typename indexer_type::dst_shape_type;
        using src_shape_type = typename indexer_type::src_shape_type;

        using dst_size_type   = decltype(meta::declval<indexer_t>().size());
        using attributes_type = args::indexing<indexer_type>;

        operand_type array;
        indexer_type indexer;

        constexpr mutable_indexing_t(array_t& array, const indexer_t& indexer)
            : array(fwd_mutable_operand(array))
            , indexer(indexer)
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return attributes_type{indexer};
        }

        constexpr auto shape() const
        {
            return indexer.shape();
        }

        constexpr auto dim() const
        {
            return indexer.dim();
        }

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto dst_indices = pack_indices(indices...);
            auto src_indices = indexer.indices(dst_indices);
            if constexpr (meta::is_pointer_v<array_type>) {
                return apply_at(*array,src_indices);
            } else if constexpr (is_none_v<decltype(src_indices)>) {
                static_assert( meta::is_num_v<array_type>
                    , "invalid source array for mutable_indexing view" );
                return array;
            } else {
                return apply_at(array,src_indices);
            }
        }

        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices)
        {
            auto dst_indices = pack_indices(indices...);
            auto src_indices = indexer.indices(dst_indices);
            static_assert( !meta::is_num_v<decltype(src_indices)>
                , "mutable_indexing view doesn't support assignment to scalar type!" );
            if constexpr (meta::is_pointer_v<array_type>) {
                return apply_at(*array,src_indices);
            } else {
                return apply_at(array,src_indices);
            }
        }

        template <typename other_t, meta::enable_if_t< meta::is_ndarray_v<other_t>, int> =0>
        constexpr auto operator=(const other_t& other)
        {
            // TODO: perform shape check at compile time when possible
            nmtools_cassert(( utils::isequal(indexer.shape(), ::nmtools::shape(other)) ));
            for (const auto& [indices, value] : index::ndenumerate(other)) {
                (*this)(indices) = value;
            }
            return *this;
        } // operator=
    }; // mutable_indexing_t

    template <typename array_t, typename indexer_t>
    constexpr auto mutable_indexing(array_t& array, const indexer_t& indexer)
    {
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type = meta::get_maybe_type_t<array_t>;
            using result_t = decltype(mutable_indexing(meta::declval<array_type>(),indexer));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            if (static_cast<bool>(array)) {
                auto result = mutable_indexing(*array,indexer);
                if constexpr (meta::is_maybe_v<result_t>) {
                    return (result ?
                          return_t{*result}
                        : return_t{meta::Nothing}
                    );
                } else {
                    return return_t{result};
                }
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<indexer_t>) {
            using indexer_type = meta::get_maybe_type_t<indexer_t>;
            using result_t = decltype(mutable_indexing(array,meta::declval<indexer_type>()));
            using return_t = nmtools_maybe<result_t>;
            return (indexer ?
                  return_t{mutable_indexing(array,*indexer)}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = decorator_t<mutable_indexing_t,array_t,indexer_t>;
            return result_t{{array,indexer}};
        }
    }

    template <typename F, typename array_t, typename...args_t>
    constexpr auto lift_mutable_indexing(F&& f, array_t& array, const args_t&...args)
    {
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type = meta::get_maybe_type_t<array_t>;
            using result_t   = decltype(f(meta::declval<array_type>(),args...));
            using return_t   = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            if (static_cast<bool>(array)) {
                auto result = f(*array,args...);
                if constexpr (meta::is_maybe_v<result_t>) {
                    return (result ?
                            return_t{*result}
                        : return_t{meta::Nothing}
                    );
                } else {
                    return return_t{result};
                }
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using l_result_t = decltype(f(meta::declval<left_t>(),args...));
            using r_result_t = decltype(f(meta::declval<right_t>(),args...));
            using return_t   = meta::replace_either_t<array_t,l_result_t,r_result_t>;
            if (auto l_ptr = nmtools::get_if<left_t>(&array)) {
                return return_t{f(*l_ptr,args...)};
            } else {
                auto r_ptr = nmtools::get_if<right_t>(&array);
                return return_t{f(*r_ptr,args...)};
            }
        } else {
            return f(array,args...);
        }
    } // lift_mutable_indexing
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename indexer_t>
    struct is_ndarray<
        view::decorator_t<view::mutable_indexing_t,array_t,indexer_t>
    > {
        using view_type  = view::decorator_t<view::indexing_t,array_t,indexer_t>;
        using shape_type = decltype(meta::declval<view_type>().shape());

        static constexpr auto value = is_ndarray_v<array_t> || (is_num_v<array_t> && is_index_array_v<shape_type>);
    }; // is_ndarray

    template <typename array_t, typename indexer_t>
    struct fixed_shape<
        view::decorator_t<view::mutable_indexing_t,array_t,indexer_t>
    > {
        using view_type = view::decorator_t<view::mutable_indexing_t,array_t,indexer_t>;
        using indexing_type  = view::mutable_indexing_t<array_t,indexer_t>;
        using dst_shape_type = typename indexing_type::dst_shape_type;
        using dst_size_type  = typename indexing_type::dst_size_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return to_value_v<dst_shape_type>;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_shape

    template <typename array_t, typename indexer_t>
    struct fixed_size<
        view::decorator_t<view::mutable_indexing_t,array_t,indexer_t>
    > {
        using view_type = view::decorator_t<view::mutable_indexing_t,array_t,indexer_t>;
        using indexing_type  = view::mutable_indexing_t<array_t,indexer_t>;
        using dst_shape_type = typename indexing_type::dst_shape_type;
        using dst_size_type  = typename indexing_type::dst_size_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_v<dst_size_type>) {
                return to_value_v<dst_size_type>;
            } else if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(to_value_v<dst_shape_type>);
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    template <typename array_t, typename indexer_t>
    struct bounded_size<
        view::decorator_t<view::mutable_indexing_t,array_t,indexer_t>
    > {
        using view_type = view::decorator_t<view::mutable_indexing_t,array_t,indexer_t>;
        using indexing_type  = view::mutable_indexing_t<array_t,indexer_t>;
        using dst_shape_type = typename indexing_type::dst_shape_type;
        using dst_size_type  = typename indexing_type::dst_size_type;

        static constexpr auto value = [](){
            constexpr auto fixed_size = fixed_size_v<view_type>;
            if constexpr (!is_fail_v<decltype(fixed_size)>) {
                return fixed_size;
            } else if constexpr (is_clipped_integer_v<dst_size_type> || is_constant_index_v<dst_size_type>) {
                return to_value_v<dst_size_type>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // bounded_size
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_INDEXING_HPP