#ifndef NMTOOLS_ARRAY_VIEW_PAD_HPP
#define NMTOOLS_ARRAY_VIEW_PAD_HPP

#include "nmtools/array/view/decorator.hpp"
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
    constexpr auto shape_pad(const shape_t& shape, const pad_width_t& pad_width_)
    {
        using result_t = meta::resolve_optype_t<shape_pad_t,shape_t,pad_width_t>;
        using return_t = meta::make_maybe_type_t<result_t>;

        // auto ret = return_t {};

        auto pad_width = [&](){
            if constexpr (meta::is_constant_index_array_v<pad_width_t>) {
                return meta::to_value_v<pad_width_t>;
            } else {
                // can't just return since may decay raw array to pointer
                return ref(pad_width_);
            }
        }();

        auto dim   = len(shape);
        auto n_pad = len(pad_width);

        if (dim*2 == n_pad) {
            auto res = result_t {};
            if constexpr (meta::is_resizeable_v<result_t>) {
                res.resize(dim);
            }
            for (size_t i=0; i<dim; i++) {
                at(res,i) = at(shape,i) + at(pad_width,i) + at(pad_width,dim+i);
            }
            // some operator= not usable in constexpr context
            // ret = res;
            return return_t{res};
        } else {
            // ret = meta::nothing;
            return return_t{meta::nothing};
        }

        // return ret;
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
    constexpr auto pad(const index_t& index, const src_shape_t& src_shape
        , const dst_shape_t& dst_shape, const pad_width_t& pad_width)
    {
        using result_t = meta::resolve_optype_t<pad_t,index_t,src_shape_t,dst_shape_t,pad_width_t>;
        // use maybe type to indicate out of bound index (of src shape)
        using return_t = meta::make_maybe_type_t<result_t>;
        using idx_t    = meta::get_element_type_t<result_t>;
        using s_idx_t  = meta::make_signed_t<idx_t>;

        auto ret = return_t {};
        auto res = result_t {};

        auto idx_dim = len(index);

        // auto dst_dim = len(dst_shape);
        // auto n_pad    = len(pad_width);
        // assume src_dim*2 == n_pad, dst_dim == src_dim == idx_dim

        if constexpr (meta::is_resizeable_v<result_t>) {
            auto src_dim = len(src_shape);
            res.resize(src_dim);
        }

        bool out_of_bound = false;
        for (size_t i=0; (i<idx_dim) && (!out_of_bound); i++) {
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
        }

        if (!out_of_bound) {
            ret = res;
        } else {
            ret = meta::nothing;
        }

        return ret;
    } // pad
} // namespace nmtools::index


namespace nmtools::view
{
    // only support constant pad for now
    enum class PADDING_MODE
    {
        CONSTANT,
    };

    /**
     * @brief Type constructor for pad view.
     * 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     */
    template <typename array_t, typename pad_width_t, typename value_t>
    struct pad_t
    {
        using array_type     = resolve_array_type_t<array_t>;
        using pad_width_type = resolve_attribute_type_t<pad_width_t>;
        using pad_value_type = resolve_attribute_type_t<value_t>;
        using value_type     = meta::get_element_type_t<array_t>;

        array_type     array;
        pad_width_type pad_width;
        pad_value_type pad_value;

        // only support constant pad for now
        // TODO: add reflect and edge mode
        const PADDING_MODE mode = PADDING_MODE::CONSTANT;

        constexpr pad_t(const array_t& array, const pad_width_t& pad_width, const value_t pad_value)
            : array(initialize(array, meta::as_value_v<array_type>))
            , pad_width(init_attribute(pad_width, meta::as_value_v<pad_width_type>))
            , pad_value(init_attribute(pad_value, meta::as_value_v<pad_value_type>)) {}
        
        constexpr auto shape() const
        {
            auto shape_ = detail::shape(array);
            auto maybe_shape = index::shape_pad(shape_,pad_width);
            // must have value, should only construct view if
            // original shape and pad_width is valid
            return *maybe_shape;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto indices_   = pack_indices(indices...);
            auto tf_indices = index::pad(indices_,detail::shape(array),shape(),pad_width);

            // TODO: consider to provide view_at with either type [apply_at(...),value_type]
            // by doing so, it may help the evaluator dealing with inner loop
            if (static_cast<bool>(tf_indices)) {
                return static_cast<value_type>(detail::apply_at(array,*tf_indices));
            } else {
                return static_cast<value_type>(pad_value);
            }
        } // operator()
    }; // pad_t

    /**
     * @brief Create a padded view to an array.
     * 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     * @param array     input array
     * @param pad_width number of padding to be applied to each edge of the axes.
     * @param value     constant value
     * @return constexpr auto 
     */
    template <typename array_t, typename pad_width_t, typename value_t=float>
    constexpr auto pad(const array_t& array, const pad_width_t& pad_width, value_t value=static_cast<value_t>(0))
    {
        // TODO: error handling using maybe, check the shape, if success the proceed
        using view_t = decorator_t<pad_t,array_t,pad_width_t,value_t>;
        return view_t{{array,pad_width,value}};
    } // pad
} // namespace nmtools::view

namespace nmtools::meta
{
    namespace error
    {
        struct SHAPE_PAD_UNSUPPORTED : detail::fail_t {};
        struct PAD_UNSUPPORTED : detail::fail_t {};
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
            if constexpr (is_index_array_v<shape_t> && is_index_array_v<pad_width_t>) {
                using type = transform_bounded_array_t<shape_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::SHAPE_PAD_UNSUPPORTED>;
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
            if constexpr (is_index_array_v<src_shape_t> && is_index_array_v<dst_shape_t> && is_index_array_v<pad_width_t>) {
                // follow src shape
                using type = transform_bounded_array_t<src_shape_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::PAD_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    /**
     * @brief Infer the shape of pad view at compile-time.
     * 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     */
    template <typename array_t, typename pad_width_t, typename value_t>
    struct fixed_ndarray_shape<
        view::pad_t< array_t, pad_width_t, value_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<array_t> && is_constant_index_array_v<pad_width_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto pad_width = to_value_v<pad_width_t>;
                constexpr auto padded = index::shape_pad(shape,pad_width);
                if constexpr (static_cast<bool>(padded)) {
                    return *padded;
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the dimension of pad view at compile-time.
     * 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     */
    template <typename array_t, typename pad_width_t, typename value_t>
    struct fixed_dim<
        view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >
    >
    {
        static inline constexpr auto value = [](){
            // padding doesn't change dimension, only change shape
            if constexpr (is_fixed_dim_ndarray_v<array_t>) {
                return fixed_dim_v<array_t>;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: consider to use fail type to indicate fail instead of void
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    }; // fixed_dim
    
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_PAD_HPP