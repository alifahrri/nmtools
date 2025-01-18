#ifndef NMTOOLS_ARRAY_VIEW_SPLIT_HPP
#define NMTOOLS_ARRAY_VIEW_SPLIT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/array/slice.hpp"

namespace nmtools::view
{
    namespace detail
    {
        struct split_args_t {};

        // TODO: move to index namespace
        /**
         * @brief Given split arguments, create slice arguments
         * 
         * @tparam shape_t 
         * @tparam indices_t 
         * @tparam axis_t 
         * @param shape               input array's shape
         * @param indices_or_sections split args
         * @param axis                on which axis split is to be performed
         * @return constexpr auto 
         */
        template <typename shape_t, typename indices_t, typename axis_t>
        constexpr auto split_args(const shape_t& shape, const indices_t& indices_or_sections, const axis_t& axis)
        {
            using result_t   = meta::resolve_optype_t<split_args_t,shape_t,indices_t,axis_t>;
            auto res = result_t {};

            if constexpr (!meta::is_tuple_v<result_t>) {
                using value_type = meta::remove_cvref_t<meta::get_value_type_t<result_t>>;
                [[maybe_unused]] auto dim = len(shape);

                auto n_split = [&](){
                    if constexpr (meta::is_index_array_v<indices_t>) {
                        return len(indices_or_sections) + 1;
                    } else /* if constexpr (meta::is_index_v<indices_t>) */ {
                        return indices_or_sections;
                    }
                }();

                if constexpr (meta::is_resizable_v<result_t>) {
                    res.resize(n_split);
                }

                using namespace nmtools::literals;

                // normalized axis
                // axis_ should safely cast to size_t
                auto axis_ = (axis >= 0 ? axis : dim + axis);
                auto shape_axis = at(shape,axis_);

                for (size_t i=0; i<(size_t)n_split; i++) {
                    auto& res_i = at(res,i);
                    // NOTE: for dynamic index array, dimension only known at runtime
                    // we must resize to dim for each split arg,
                    if constexpr (meta::is_resizable_v<value_type>) {
                        res_i.resize(dim);
                    }

                    if constexpr (meta::is_index_array_v<indices_t>) {
                        const auto& indices = indices_or_sections;
                        // To avoid instantiating tuple access with runtime value
                        constexpr auto indices_ = meta::to_value_v<indices_t>;
                        // fill for each axis
                        for (size_t j=0; j<(size_t)dim; j++) {
                            // TODO: deduce index type if possible
                            using index_t = size_t;
                            auto start = [&]() -> index_t {
                                if (j!=axis_) {
                                    return 0;
                                } else if (i>0) {
                                    if constexpr (meta::is_constant_index_array_v<indices_t>) {
                                        return at(indices_,i-1);
                                    } else {
                                        return at(indices,i-1);
                                    }
                                } else /* if (i==0) */ {
                                    return 0;
                                }
                            }();
                            auto stop  = [&]() -> index_t {
                                if (j!=axis_) {
                                    return at(shape,j);
                                } else if (i==(n_split-1)) {
                                    return shape_axis;
                                } else /* if (i>0 && i<(n_split-1)) */ {
                                    if constexpr (meta::is_constant_index_array_v<indices_t>) {
                                        return at(indices_,i);
                                    } else {
                                        return at(indices,i);
                                    }
                                }
                            }();

                            // assume inner container (for start,stop pair)
                            // is fixed-size (see resolver metafunction below)
                            // and it is exactly 2
                            auto& res_i_j = at(res_i,j);
                            at(res_i_j,0_ct) = start;
                            at(res_i_j,1_ct) = stop;
                        }
                    } else /* if constexpr (meta::is_index_v<indices_t>) */ {
                        // fill for each axis
                        for (size_t j=0; j<(size_t)dim; j++) {
                            auto range = (j==(size_t)axis_ ? shape_axis / indices_or_sections : shape_axis);
                            // TODO: deduce index type if possible
                            using index_t = size_t;
                            auto start = [&]() -> index_t {
                                if (j!=axis_) {
                                    return 0;
                                } else {
                                    return i * range;
                                }
                            }();
                            auto stop  = [&]() -> index_t {
                                if (j!=axis_) {
                                    return at(shape,j);
                                } else {
                                    return start + range;
                                }
                            }();

                            // assume inner container (for start,stop pair)
                            // is fixed-size (see resolver metafunction below)
                            // and it is exactly 2
                            auto& res_i_j = at(res_i,j);
                            at(res_i_j,0_ct) = start;
                            at(res_i_j,1_ct) = stop;
                        }
                    }
                }
            }

            return res;
        } // split_args

        /**
         * @brief Helper function to call slice on tuple of split arguments
         * 
         * @tparam array_t 
         * @tparam split_args_t 
         * @tparam index_sequence 
         * @tparam Is 
         * @param array 
         * @param split_args 
         * @return constexpr auto 
         */
        template <typename array_t, typename split_args_t, template<auto...>typename index_sequence, auto...Is>
        constexpr auto split(const array_t& array, const split_args_t& split_args, index_sequence<Is...>)
        {
            return nmtools_tuple{apply_slice(array,nmtools::get<Is>(split_args))...};
        }
    } // namespace detail
    
    /**
     * @brief split an array.
     * Construct list/tuple of view.
     * 
     * @tparam array_t 
     * @tparam index_t 
     * @tparam axis_t 
     * @param array                 input array
     * @param indices_or_sections   slice args
     * @param axis                  axis on which split is to be performed
     * @return constexpr auto 
     */
    template <typename array_t, typename index_t, typename axis_t>
    constexpr auto split(const array_t& array, const index_t& indices_or_sections, axis_t axis)
    {
        auto shape = nmtools::shape(array);
        auto split_args = detail::split_args(shape,indices_or_sections,axis);
        using split_args_t = decltype(split_args);
        if constexpr (meta::is_list_v<split_args_t>) {
            using value_type = meta::get_value_type_t<split_args_t>;
            using split_t    = decltype(apply_slice(array, meta::declval<value_type>()));
            using result_t   = meta::replace_value_type_t<split_args_t,split_t>;
            auto res = result_t {};
            auto n = len(split_args);
            // NOTE: the resulting view type default constructor is implicitly deleted
            // (cant construct decorator_t<split_t,...>),
            // so must use push back for now
            // res.resize(n);
            for (size_t i=0; i<n; i++) {
                // TODO: use emplace_back
                res.push_back(apply_slice(array,at(split_args,i)));
                // at(res,i) = apply_slice(array, at(split_args,i));
            }
            return res;
        } else {
            constexpr auto N = meta::len_v<split_args_t>;
            return detail::split(array, split_args, meta::make_index_sequence_v<N>);
        }
    } // split
} // namespace nmtools::view

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SPLIT_ARGS_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<void,view::detail::split_args_t,shape_t,indices_t,axis_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                    is_constant_index_array_v<shape_t>
                && (is_constant_index_array_v<indices_t> || is_constant_index_v<indices_t>)
                &&  is_constant_index_v<axis_t>
            ) {
                constexpr auto shape   = to_value_v<shape_t>;
                // pass indices as it is to avoid dynamic allocation
                constexpr auto indices = indices_t{};
                constexpr auto axis    = to_value_v<axis_t>;
                constexpr auto split_args = view::detail::split_args(shape,indices,axis);
                // type of split_args should be 3-dim nested array
                // with axis=0 represents slices, axis=1 represents original array dimension
                // and axis=2 represent start,stop pair
                constexpr auto n_split  = ::nmtools::len(split_args);
                return template_reduce<n_split>([&](auto init, auto i){
                    // for simplicity use nmtools_tuple
                    constexpr auto split_i   = ::nmtools::at(split_args,i);
                    constexpr auto n_split_i = ::nmtools::len(split_i); // should be the same as array dim
                    // type of split0 should be array of len 2, (start,stop pair)
                    constexpr auto split_i_vtype = template_reduce<n_split_i>([&](auto init, auto j){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto args  = ::nmtools::at(split_i,j);
                        constexpr auto start = ::nmtools::at(args,0);
                        constexpr auto stop  = ::nmtools::at(args,1);
                        using args_t = nmtools_tuple<ct<start>,ct<stop>>;
                        if constexpr (is_none_v<init_t>) {
                            return as_value_v<nmtools_tuple<args_t>>;
                        } else {
                            using type = append_type_t<init_t,args_t>;
                            return as_value_v<type>;
                        }
                    }, as_value_v<none_t>);
                    using split_i_t = type_t<decltype(split_i_vtype)>;
                    using init_t = type_t<decltype(init)>;
                    if constexpr (is_none_v<init_t>) {
                        return as_value_v<nmtools_tuple<split_i_t>>;
                    } else {
                        using type = append_type_t<init_t,split_i_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<none_t>);
            } else if constexpr (is_constant_index_array_v<shape_t>) {
                using type = resolve_optype_t<view::detail::split_args_t,decltype(to_value_v<shape_t>),indices_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                    is_fixed_index_array_v<shape_t>
                && (is_constant_index_array_v<indices_t> || is_constant_index_v<indices_t>)
                &&  is_index_v<axis_t>
            ) {
                constexpr auto dim = len_v<shape_t>;
                using index_t = get_index_element_type_t<shape_t>;
                // we know how many axis at compile-time
                // NOTE: 2 represents start and stop pair
                using slice_t = nmtools_array<nmtools_array<index_t,2>,dim>;
                // but we do not know how many slices until runtime
                // TODO: consider to use tuple template-template-parameter from shape_t
                // if possible
                constexpr auto n_split = [](){
                    if constexpr (is_constant_index_v<indices_t>) {
                        return indices_t::value;
                    } else {
                        return len_v<indices_t> + 1;
                    }
                }();
                using type = nmtools_array<slice_t,n_split>;
                return as_value_v<type>;
            } else if constexpr (
                    is_fixed_index_array_v<shape_t>
                && (is_index_array_v<indices_t> || is_index_v<indices_t>)
                &&  is_index_v<axis_t>
            ) {
                constexpr auto dim = len_v<shape_t>;
                using index_t = get_index_element_type_t<shape_t>;
                // we know how many axis at compile-time
                // NOTE: 2 represents start and stop pair
                using slice_t = nmtools_array<nmtools_array<index_t,2>,dim>;
                // but we do not know how many slices until runtime
                using type = nmtools_list<slice_t>;
                return as_value_v<type>;
            } else if constexpr (
                    is_index_array_v<shape_t>
                && (is_index_array_v<indices_t> || is_index_v<indices_t>)
                &&  is_index_v<axis_t>
            ) {
                using index_t = get_index_element_type_t<shape_t>;
                // we do not know how many axis until runtime
                using slice_t = nmtools_list<nmtools_array<index_t,2>>;
                using type = nmtools_list<slice_t>;
                return as_value_v<type>;
            } else {
                using type = error::SPLIT_ARGS_UNSUPPORTED<shape_t,indices_t,axis_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_SPLIT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SPLIT_HPP
#define NMTOOLS_ARRAY_ARRAY_SPLIT_HPP

#include "nmtools/array/split.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly split an array
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam index_t 
     * @tparam axis_t 
     * @param array 
     * @param indices_or_sections 
     * @param axis 
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename index_t, typename axis_t>
    constexpr auto split(const array_t& array, const index_t& indices_or_sections, axis_t axis
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto split_ = view::split(array,indices_or_sections,axis);
        return apply_eval(split_
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SPLIT_HPP