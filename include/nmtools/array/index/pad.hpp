#ifndef NMTOOLS_ARRAY_INDEX_PAD_HPP
#define NMTOOLS_ARRAY_INDEX_PAD_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/ref.hpp"

namespace nmtools::index
{
    struct shape_pad_t {};

    /**
     * @brief Compute the shape of pad view
     * 
     * Note that this fn follows onnx rules rather than numpy rules.
     * 
     * @tparam shape_t 
     * @tparam pad_width_t 
     * @param shape     original array shape
     * @param pad_width desired padding value, following onnx fmt: [axis_0_begin, axis_1_begin,..., axis_0_end,...]
     * @return constexpr auto 
     */
    template <typename shape_t, typename pad_width_t>
    constexpr auto shape_pad(const shape_t& shape_, const pad_width_t& pad_width_)
    {
        using result_t = meta::resolve_optype_t<shape_pad_t,shape_t,pad_width_t>;
        using return_t = nmtools_maybe<result_t>;

        if constexpr (! meta::is_constant_index_array_v<result_t>) {
            // auto ret = return_t {};

            auto pad_width = [&](){
                if constexpr (meta::is_constant_index_array_v<pad_width_t>) {
                    return meta::to_value_v<pad_width_t>;
                } else {
                    // can't just return since may decay raw array to pointer
                    return ref(pad_width_);
                }
            }();

            auto shape = [&](){
                if constexpr (meta::is_constant_index_array_v<shape_t>) {
                    return meta::to_value_v<shape_t>;
                } else {
                    return ref(shape_);
                }
            }();

            auto dim   = len(shape);
            auto n_pad = len(pad_width);

            if (dim*2 == n_pad) {
                auto res = result_t {};
                if constexpr (meta::is_resizable_v<result_t>) {
                    res.resize(dim);
                }
                auto shape_pad_impl = [&](auto i){
                    at(res,i) = at(shape,i) + at(pad_width,i) + at(pad_width,dim+i);
                };
                if constexpr (meta::is_tuple_v<result_t>) {
                    constexpr auto N = meta::len_v<result_t>;
                    meta::template_for<N>(shape_pad_impl);
                } else {
                    for (size_t i=0; i<dim; i++) {
                        shape_pad_impl(i);
                    }   
                }
                // some operator= not usable in constexpr context
                // ret = res;
                return return_t{res};
            } else {
                // ret = meta::Nothing;
                return return_t{};
            }

            // return ret;
        } else {
            // keep using maybe type for less-friction at downstream
            return return_t {result_t{}};
        }
    } // shape_pad

    struct pad_t {};

    /**
     * @brief Transform index in dst domain (padded) to src domain (original).
     * 
     * @tparam index_t 
     * @tparam src_shape_t 
     * @tparam dst_shape_t 
     * @tparam pad_width_t 
     * @param index         index in padded shape
     * @param src_shape     original array shape
     * @param dst_shape     padded array shape
     * @param pad_width     pad width argument (that is used to compute dst shape)
     * @return constexpr auto 
     */
    template <typename index_t, typename src_shape_t, typename dst_shape_t, typename pad_width_t>
    nmtools_index_attribute
    constexpr auto pad(const index_t& index, const src_shape_t& src_shape
        , const dst_shape_t& /*dst_shape*/, const pad_width_t& pad_width)
    {
        using result_t = meta::resolve_optype_t<pad_t,index_t,src_shape_t,dst_shape_t,pad_width_t>;
        // use maybe type to indicate out of bound index (of src shape)
        using return_t = meta::make_maybe_type_t<result_t>;
        using idx_t    = meta::get_index_element_type_t<result_t>;
        using s_idx_t  = meta::make_signed_t<idx_t>;

        auto res = result_t {};

        auto idx_dim = len(index);

        // auto dst_dim = len(dst_shape);
        // auto n_pad    = len(pad_width);
        // assume src_dim*2 == n_pad, dst_dim == src_dim == idx_dim

        if constexpr (meta::is_resizable_v<result_t>) {
            auto src_dim = len(src_shape);
            res.resize(src_dim);
        }

        bool out_of_bound = false;
        auto pad_impl = [&](auto i){
            auto idx = static_cast<s_idx_t>(at(index,i));
            auto s_i = static_cast<s_idx_t>(at(src_shape,i));
            auto p_i = static_cast<s_idx_t>(at(pad_width,i));
            auto r_bound =  idx >= (s_i + p_i);
            auto l_bound = (idx - p_i) < 0;
            if (l_bound || r_bound) {
                out_of_bound = true;
            } else {
                at(res,i) = idx - p_i;
            }
        };
        if constexpr (meta::is_tuple_v<result_t>) {
            constexpr auto N = meta::len_v<result_t>;
            meta::template_for<N>(pad_impl);
        } else {
            for (size_t i=0; (i<idx_dim) && (!out_of_bound); i++) {
                pad_impl(i);
            }
        }

        if (!out_of_bound) {
            return return_t{res};
        } else {
            return return_t{meta::Nothing};
        }
    } // pad
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_PAD_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct PAD_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct SHAPE_PAD_INVALID : detail::fail_t {};
    } // namespace error

    /**
     * @brief Resolve return type of index::shape_pad
     * 
     * @tparam shape_t 
     * @tparam pad_width_t 
     */
    template <typename shape_t, typename pad_width_t>
    struct resolve_optype<
        void, index::shape_pad_t, shape_t, pad_width_t
    >
    {
        static constexpr auto vtype = [](){
            // NOTE: clipped index array is when the array has fixed size and may contains clipped integer
            // so, static vector of clipped integer is not considered clipped index array
            // static vector of clipped integer can be handled as follows:
            // - check of bounded size of array
            // - then check if element is clipped integer
            if constexpr (
                (is_constant_index_array_v<shape_t> || is_clipped_index_array_v<shape_t>)
                && (is_constant_index_array_v<pad_width_t> || is_clipped_index_array_v<pad_width_t>)
            ) {
                constexpr auto shape     = to_value_v<shape_t>;
                constexpr auto pad_width = to_value_v<pad_width_t>;
                constexpr auto result    = index::shape_pad(shape,pad_width);
                if constexpr (static_cast<bool>(result)) {
                    constexpr auto shape = *result;
                    return template_reduce<nmtools::len(shape)>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        constexpr auto I = nmtools::at(shape,index);
                        if constexpr (is_constant_index_array_v<shape_t> && is_constant_index_array_v<pad_width_t>) {
                            return as_value_v<append_type_t<init_type,ct<I>>>;
                        } else {
                            return as_value_v<append_type_t<init_type,clipped_size_t<I>>>;
                        }
                    }, as_value_v<nmtools_tuple<>>);
                } else {
                    return as_value_v<error::SHAPE_PAD_INVALID<shape_t,pad_width_t>>;
                }
            } else if constexpr (is_fixed_index_array_v<shape_t> && is_index_array_v<pad_width_t>) {
                using index_t = get_index_element_type_t<pad_width_t>;
                return as_value_v<nmtools_array<index_t,len_v<shape_t>>>;
            } else if constexpr (is_index_array_v<shape_t> && is_index_array_v<pad_width_t>) {
                using type = transform_bounded_array_t<shape_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::SHAPE_PAD_UNSUPPORTED<shape_t,pad_width_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    /**
     * @brief Resolve return type of index::pad
     * 
     * @tparam index_t 
     * @tparam src_shape_t 
     * @tparam dst_shape_t 
     * @tparam pad_width_t 
     */
    template <typename index_t, typename src_shape_t, typename dst_shape_t, typename pad_width_t>
    struct resolve_optype<
        void, index::pad_t, index_t, src_shape_t, dst_shape_t, pad_width_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<src_shape_t>) {
                // simply recurse for now
                using shape_t = remove_cvref_t<decltype(to_value_v<src_shape_t>)>;
                using type = resolve_optype_t<index::pad_t,index_t,shape_t,dst_shape_t,pad_width_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<src_shape_t> && is_index_array_v<dst_shape_t> && is_index_array_v<pad_width_t>) {
                // follow src shape
                using type = transform_bounded_array_t<src_shape_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::PAD_UNSUPPORTED<index_t,src_shape_t,dst_shape_t,pad_width_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_PAD_HPP