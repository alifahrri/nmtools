#ifndef NMTOOLS_TILEKIT_VECTOR_HPP
#define NMTOOLS_TILEKIT_VECTOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core.hpp"
#include "nmtools/core/eval.hpp"
#include "nmtools/core/context.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/index/array.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/ndarray/array.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/scalar.hpp"

#ifndef NMTOOLS_TILEKIT_VECTOR_DEFAULT_BIT_WIDTH
#define NMTOOLS_TILEKIT_VECTOR_DEFAULT_BIT_WIDTH (128)
#endif // NMTOOLS_TILEKIT_VECTOR_DEFAULT_BIT_WIDTH

namespace nmtools::tilekit::vector
{
    template<typename T, int N>
    struct make_vector {
        using type __attribute__((vector_size(N), aligned(4))) = T;
    };

    #define nmtools_ndarray_method(method) \
    template <typename...args_t> \
    constexpr auto method(const args_t&...args) const \
    { \
        auto v = nmtools::view::method(*this,args...); \
        auto result = nmtools::eval(v,Unroll,None); \
        return nmtools::unwrap(result); \
    }

    template <auto bit_width=NMTOOLS_TILEKIT_VECTOR_DEFAULT_BIT_WIDTH>
    struct context_t;

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width=NMTOOLS_TILEKIT_VECTOR_DEFAULT_BIT_WIDTH
        , template <typename...>typename stride_buffer_t=resolve_stride_type_t
        , template <typename...>typename compute_offset_t=row_major_offset_t
        , typename=void>
    struct object_t
        : nmtools::object_t<buffer_t,shape_buffer_t,resolve_stride_type_t,row_major_offset_t,context_t<bit_width>,false>
    {
        using shape_buffer_type = shape_buffer_t;
        static_assert( is_constant_index_array_v<shape_buffer_type>
            , "unsupported shape buffer type for vector::object_t; expected constant index array"
        );
        // TODO: assert shape buffer and shape is known at compile-time
        using base_type     = nmtools::object_t<buffer_t,shape_buffer_t,resolve_stride_type_t,row_major_offset_t,context_t<bit_width>,false>;
        using value_type    = typename base_type::value_type;
        using element_type  = get_element_type_t<buffer_t>;

        static constexpr auto n_bytes = bit_width / 8;
        using vector_type = typename make_vector<value_type, n_bytes>::type;

        static constexpr auto n_iter = (fixed_size_v<base_type> * sizeof(value_type)) / n_bytes;
        static constexpr auto src_shape = shape_buffer_type{};
        static constexpr auto dtype = dtype_t<element_type>{};
        static constexpr auto DIM   = len_v<shape_buffer_type>;
        static constexpr auto NUM_LANE = bit_width / (sizeof(element_type) * 8 /*bit*/);
        static constexpr auto SRC_SIZE = index::product(src_shape);

        template <typename dst_shape_t>
        constexpr auto broadcast_to(const dst_shape_t& dst_shape) const
        {
            auto dst_size = index::product(dst_shape);
            constexpr auto DST_SIZE = decltype(dst_size)::value;
            using dst_buffer_t = nmtools_array<element_type,DST_SIZE>;
            using result_t = object_t<dst_buffer_t,dst_shape_t,bit_width>;

            auto m_src_shape = index::array(src_shape);
            auto lane = [&](){
                if constexpr (DIM == 1) {
                    return nmtools_tuple{ct_v<NUM_LANE>};
                } else {
                    return index::ones(ct_v<DIM-1>).append(ct_v<NUM_LANE>);
                }
            }();
            auto bcast_src_shape = m_src_shape / lane;
            auto src_index = index::ndindex(bcast_src_shape);

            constexpr auto NUM_LOAD   = len_v<decltype(src_index)>;
            constexpr auto NUM_REPEAT = DST_SIZE / SRC_SIZE;

            auto result = result_t {};

            using vector_t = vector_type;
            template_for<NUM_LOAD>([&](auto i){
                constexpr auto I = decltype(i)::value;
                auto v = *((vector_t*)this->data()+I);
                template_for<NUM_REPEAT>([&](auto j){
                    constexpr auto J = decltype(j)::value;
                    *((vector_t*)result.data()+((J*NUM_LOAD)+I)) = v;
                });
            });

            return result;
        }

        template <typename rhs_t>
        constexpr auto add(const rhs_t& rhs) const
        {
            // assume same shape & type
            // TODO: assert same shape & size
            auto result = object_t{};

            using vector_t = vector_type;
            for (nm_size_t i=0; i<n_iter; i++) {
                *((vector_t*)result.data()+i) = *((vector_t*)this->data()+i) + *((vector_t*)rhs.data()+i);
            }

            return result;
        }

        template <typename other_t>
        constexpr auto operator+(const other_t& other) const
        {
            auto result = this->add(other);
            return result;
        }

        template <typename rhs_t>
        constexpr auto subtract(const rhs_t& rhs) const
        {
            // assume same shape & type
            // TODO: assert same shape & size
            auto result = object_t{};

            using vector_t = vector_type;
            for (nm_size_t i=0; i<n_iter; i++) {
                *((vector_t*)result.data()+i) = *((vector_t*)this->data()+i) - *((vector_t*)rhs.data()+i);
            }

            return result;
        }

        template <typename other_t>
        constexpr auto operator-(const other_t& other) const
        {
            auto result = this->subtract(other);
            return result;
        }

        template <typename rhs_t>
        constexpr auto multiply(const rhs_t& rhs) const
        {
            // assume same shape & type
            // TODO: assert same shape & size
            auto result = object_t{};

            using vector_t = vector_type;
            for (nm_size_t i=0; i<n_iter; i++) {
                *((vector_t*)result.data()+i) = *((vector_t*)this->data()+i) * *((vector_t*)rhs.data()+i);
            }

            return result;
        }

        template <typename other_t>
        constexpr auto operator*(const other_t& other) const
        {
            auto result = this->multiply(other);
            return result;
        }

        template <typename rhs_t>
        constexpr auto divide(const rhs_t& rhs) const
        {
            // assume same shape & type
            // TODO: assert same shape & size
            auto result = object_t{};

            using vector_t = vector_type;
            for (nm_size_t i=0; i<n_iter; i++) {
                *((vector_t*)result.data()+i) = *((vector_t*)this->data()+i) / *((vector_t*)rhs.data()+i);
            }

            return result;
        }

        template <typename other_t>
        constexpr auto operator/(const other_t& other) const
        {
            auto result = this->divide(other);
            return result;
        }
    };

    #undef nmtools_ndarray_method

    struct compute_src_indices_t {};

    template <
        typename tile_indices_t
        , typename src_ndoffset_t
        , typename num_lane_t>
    constexpr auto compute_src_indices(
        const tile_indices_t& tile_indices
        , const src_ndoffset_t& src_ndoffset
        , const num_lane_t num_lane)
    {
        using result_t = resolve_optype_t<compute_src_indices_t,tile_indices_t,src_ndoffset_t,num_lane_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            constexpr auto DIM = len_v<tile_indices_t>;
            [[maybe_unused]] auto dim = len(src_ndoffset);
            if constexpr (is_resizable_v<result_t>) {
                result.resize(dim);
            }

            if constexpr (DIM > 0) {
                template_for<DIM-1>([&](auto i){
                    auto& result_i = at(result,i);
                    if constexpr (!is_constant_index_v<decltype(result_i)>) {
                        auto src_i = at(src_ndoffset,i);
                        auto tile_i = at(tile_indices,i);
                        if (has_value(src_i) && has_value(tile_i)) {
                            at(result,i) = tile_i + src_i;
                        }
                    }
                });
                auto i = ct_v<DIM-1>;
                auto& result_i = at(result,i);
                if constexpr (!is_constant_index_v<decltype(result_i)>) {
                    auto src_i = at(src_ndoffset,i);
                    auto tile_i = at(tile_indices,i);
                    if (has_value(src_i) && has_value(tile_i)) {
                        at(result,i) = (tile_i * num_lane) + src_i;
                    }
                }
            } else {
                nm_size_t i = 0;
                for (; i<(nm_size_t)dim-1; i++) {
                    auto src_i = at(src_ndoffset,i);
                    auto tile_i = at(tile_indices,i);
                    if (has_value(src_i) && has_value(tile_i)) {
                        at(result,i) = tile_i + src_i;
                    }
                }
                auto src_i = at(src_ndoffset,i);
                auto tile_i = at(tile_indices,i);
                if (has_value(src_i) && has_value(tile_i)) {
                    at(result,i) = (tile_i * num_lane) + src_i;
                }
            }
        }

        return result;
    }
    

    // TODO: rename offset to indices

    template <auto bit_width=128, typename array_t, typename offset_t, typename tile_shape_t, typename padding_t=ct<0>>
    constexpr auto load(const array_t& array, const offset_t& offset, const tile_shape_t& tile_shape, [[maybe_unused]] padding_t padding=padding_t{})
    {
        using element_t = meta::get_element_type_t<array_t>;

        constexpr auto SIZE = index::product(to_value_v<tile_shape_t>);
        using buffer_t = nmtools_array<element_t,SIZE>;
        using shape_buffer_t = tile_shape_t;
        using result_t = object_t<buffer_t,shape_buffer_t,bit_width>;
        using vector_t = typename result_t::vector_type;

        auto result = result_t{};

        const auto src_shape   = nmtools::shape(array);
        const auto src_strides = index::compute_strides(src_shape);

        constexpr auto NUM_LANE = bit_width / (sizeof(element_t) * 8 /*bit*/);
        constexpr auto NUM_LOAD = SIZE / NUM_LANE;

        constexpr auto DIM = len_v<tile_shape_t>;
        constexpr auto v_lane = [&](){
            if constexpr (DIM == 1) {
                return nmtools_tuple{ct_v<NUM_LANE>};
            } else {
                return index::ones(ct_v<DIM-1>).append(ct_v<NUM_LANE>);
            }
        }();
        constexpr auto v_tile_shape = index::array(tile_shape_t{}) / v_lane;
        constexpr auto v_tile_strides = index::compute_strides(v_tile_shape);

        auto vectorized_load = [&](){
            template_for<NUM_LOAD>([&](auto i){
                constexpr auto I = decltype(i)::value;
                auto tile_indices = index::compute_indices(i,v_tile_shape,v_tile_strides);
                auto src_indices  = vector::compute_src_indices(tile_indices,offset,ct_v<NUM_LANE>);
                auto src_offset   = index::compute_offset(src_indices,src_strides);
                *((vector_t*)result.data()+I) = *((vector_t*)&array.data()[src_offset]);
            });
        };
        using scalar_loader_t = load_t<scalar_t,array_t,tile_shape_t,padding_t>;

        if constexpr (!padding_t::value) {
            vectorized_load();
        } else {
            const auto start_index  = 0;
            const auto tile_stride  = index::compute_strides(tile_shape);
            const auto tile_indices = index::compute_indices(start_index,tile_shape,tile_stride);
            const auto src_indices  = index::add_indices(tile_indices,offset);
            const auto dim = len(src_indices);
            auto valid = true;
            for (nm_size_t j=0; (j<dim) && valid; j++) {
                valid = valid && ((nm_size_t)(at(src_indices,j) + at(tile_shape,j)) < (nm_size_t)at(src_shape,j));
            }
            if (valid) {
                vectorized_load();
            } else {
                scalar_loader_t::load(scalar_t{},result,array,src_shape,offset,tile_shape,tile_stride,padding);
            }
        }

        return result;
    }

    template <auto bit_width=128, typename output_t, typename offset_t, typename result_t, typename padding_t=ct<0>>
    constexpr auto store(output_t& output, const offset_t& offset, const result_t& result, [[maybe_unused]] padding_t padding=padding_t{})
    {
        // static_assert( meta::is_fixed_shape_v<result_t> );
        static_assert( meta::is_constant_index_v<padding_t> || is_none_v<padding_t> );

        constexpr auto DIM = meta::len_v<offset_t>;
        static_assert( DIM > 0 );

        using vector_t = typename result_t::vector_type;

        constexpr auto tile_shape = fixed_shape_v<result_t>;
        using element_t = get_element_type_t<result_t>;
        constexpr auto SIZE = index::product(tile_shape);
        constexpr auto NUM_LANE = bit_width / (sizeof(element_t) * 8 /*bit*/);
        constexpr auto NUM_LOAD = SIZE / NUM_LANE;

        // TODO: paraametrize this
        constexpr auto allow_small_load = 1;
        static_assert( (NUM_LOAD > 0) || allow_small_load );

        const auto output_shape   = nmtools::shape(output);
        const auto output_strides = index::compute_strides(output_shape);

        using tile_shape_t = decltype(result.shape());
        constexpr auto v_lane = [&](){
            if constexpr (DIM == 1) {
                return nmtools_tuple{ct_v<NUM_LANE>};
            } else {
                return index::ones(ct_v<DIM-1>).append(ct_v<NUM_LANE>);
            }
        }();
        constexpr auto v_tile_shape = index::array(tile_shape_t{}) / v_lane;
        constexpr auto v_tile_strides = index::compute_strides(v_tile_shape);

        using scalar_store_t = store_t<scalar_t,output_t,padding_t>;
        auto vectorized_store = [&](){
            if constexpr (NUM_LOAD > 0) {
                template_for<NUM_LOAD>([&](auto i){
                    constexpr auto I = decltype(i)::value;
                    auto tile_indices = index::compute_indices(i,v_tile_shape,v_tile_strides);
                    auto src_indices  = vector::compute_src_indices(tile_indices,offset,ct_v<NUM_LANE>);
                    auto src_offset   = index::compute_offset(src_indices,output_strides);
                    *((vector_t*)&output.data()[src_offset]) = *((vector_t*)result.data()+I);
                });
            } else {
                // size < num_lane
                scalar_store_t::store(scalar_t{},output,output_shape,offset,result,padding);
            }
        };

        if constexpr (!padding_t::value) {
            vectorized_store();
        } else {
            const auto start_index  = 0;
            const auto tile_stride  = index::compute_strides(tile_shape);
            const auto tile_indices = index::compute_indices(start_index,tile_shape,tile_stride);
            const auto src_indices  = index::add_indices(tile_indices,offset);
            const auto dim = len(src_indices);
            auto valid = true;
            for (nm_size_t j=0; (j<dim) && valid; j++) {
                valid = valid && ((nm_size_t)(at(src_indices,j) + at(tile_shape,j)) < (nm_size_t)at(output_shape,j));
            }
            if (valid) {
                vectorized_store();
            } else {
                scalar_store_t::store(scalar_t{},output,output_shape,offset,result,padding);
            }
        }
    }

    // context
    // TODO: mark this as kernel_context (context for kernel, not lancher/host)
    template <auto bit_width>
    struct context_t
        : base_context_t<context_t<bit_width>>
    {
        static constexpr auto object_enable = true;
        static constexpr auto unroll_enable = true;
        template <typename... args_t>
        using layout_t = row_major_offset_t<args_t...>;

        using base_type    = base_context_t<context_t>;

        static constexpr auto BIT_WIDTH = bit_width;
        nm_size_t worker_id = 0;
        nm_size_t worker_size = 1;

        constexpr context_t() {}

        constexpr context_t(const context_t& other)
            : worker_id(other.worker_id)
            , worker_size(other.worker_size)
        {}

        constexpr context_t(nm_size_t worker_id, nm_size_t worker_size)
            : worker_id(worker_id)
            , worker_size(worker_size)
        {}

        constexpr decltype(auto) operator=(const context_t& other)
        {
            this->worker_id = other.worker_id;
            this->worker_size = other.worker_size;
            return *this;
        }

        static auto create_context(nm_size_t worker_id, nm_size_t worker_size)
        {
            return context_t{worker_id, worker_size};
        }

        template <typename buffer_t, typename shape_t>
        constexpr auto create(as_value<buffer_t>, as_value<shape_t>) const noexcept
        {
            static_assert( is_constant_index_array_v<shape_t> || !unroll_enable );

            using result_t = object_t<buffer_t,shape_t,BIT_WIDTH,resolve_stride_type_t,layout_t>;

            auto result = result_t {};
            return result;
        }

        template <typename buffer_t, typename shape_t>
        constexpr auto create(as_value<buffer_t>, const shape_t& shape) const
        {
            static_assert( is_constant_index_array_v<shape_t> || !unroll_enable );

            using result_t = object_t<buffer_t,shape_t,BIT_WIDTH,resolve_stride_type_t,layout_t>;

            auto result = result_t {};
            if constexpr (!is_constant_index_array_v<shape_t>) {
                result.resize(shape);
            }
            return result;
        }

        template <typename T, typename shape_t, typename m_size_t=none_t>
        constexpr auto create(
            [[maybe_unused]] dtype_t<T> dtype
            , [[maybe_unused]] const shape_t& shape
            , [[maybe_unused]] const m_size_t size=m_size_t{}) const
        {
            if constexpr (is_none_v<shape_t>) {
                return T{0};
            } else {
                auto buffer_vtype = base_type::get_buffer_vtype(dtype,shape,size);
                return this->create(buffer_vtype, shape);
            }
        }

        template <typename T, typename shape_t>
        constexpr auto full(const shape_t& shape, T t) const
        {
            auto buffer_vtype = base_type::get_buffer_vtype(as_value_v<T>, shape);
            auto result = this->create(buffer_vtype,shape);
            for (nm_size_t i=0; i<result.size(); i++) {
                result.data_[i] = t;
            }
            return result;
        }

        template <typename shape_t, typename T=float>
        constexpr auto zeros(const shape_t& shape, dtype_t<T> = dtype_t<T>{}) const
        {
            return this->full(shape, static_cast<T>(0));
        }

        template <typename shape_t, typename T=float>
        constexpr auto ones(const shape_t& shape, dtype_t<T> = dtype_t<T>{}) const
        {
            return this->full(shape, static_cast<T>(1));
        }

        template <typename view_t>
        constexpr auto eval(none_t, const view_t& view) const
        {
            return this->eval(view);
        }

        template <typename output_t, typename view_t>
        constexpr auto eval(output_t& output, const view_t& view) const
            -> enable_if_t<is_num_v<output_t> && is_num_v<view_t>>
        {
            output = static_cast<output_t>(view);
        }

        template <typename output_t, typename view_t>
        constexpr auto eval(output_t& output, const view_t& view) const
            -> enable_if_t<!is_none_v<output_t> && !is_num_v<output_t>>
        {
            auto out_shape = nmtools::shape(output);
            auto inp_shape = nmtools::shape(unwrap(view));
            auto is_equal  = utils::isequal(out_shape,inp_shape);
            if (!is_equal) {
                nmtools_assert( is_equal
                    , "mismatched shape for eval"
                );
            }

            auto out_index = index::ndindex(out_shape);
            auto inp_index = index::ndindex(inp_shape);

            if constexpr (!unroll_enable) {
                auto n = inp_index.size();
                for (size_t i=0; i<n; i++) {
                    // while the shape is the same,
                    // the underlying type of indexing may be not
                    auto inp_idx = inp_index[i];
                    auto out_idx = out_index[i];
                    apply_at(output,out_idx) = apply_at(unwrap(view),inp_idx);
                }
            } else {
                constexpr auto OUT_SIZE = len_v<decltype(out_index)>;
                constexpr auto INP_SIZE = len_v<decltype(inp_index)>;
                static_assert( (OUT_SIZE > 0) && (INP_SIZE > 0) );

                const auto out_stride = index::compute_strides(out_shape);
                // const auto inp_stride = index::compute_strides(inp_shape);
                template_for<OUT_SIZE>([&](auto i){
                    auto inp_idx = inp_index[i];
                    auto out_idx = out_index[i];
                    // auto flat_inp_idx = index::compute_offset(inp_idx,inp_stride);
                    auto flat_out_idx = index::compute_offset(out_idx,out_stride);
                    output.data()[flat_out_idx] = apply_at(view,inp_idx);
                });
            }
        }

        template <typename view_t>
        constexpr auto eval(const view_t& view) const
        {
            if constexpr (meta::is_either_v<view_t>) {
                using left_t   = meta::get_either_left_t<view_t>;
                using right_t  = meta::get_either_right_t<view_t>;
                // deduce return type for each type
                using rleft_t  = decltype(this->eval(meta::declval<left_t>()));
                using rright_t = decltype(this->eval(meta::declval<right_t>()));
                constexpr auto vtype = [](){
                    if constexpr (meta::is_same_v<rleft_t,rright_t>) {
                        return meta::as_value_v<rleft_t>;
                    } else {
                        using either_t = meta::replace_either_t<view_t,rleft_t,rright_t>;
                        return meta::as_value_v<either_t>;
                    }
                }();
                using return_t = meta::type_t<decltype(vtype)>;
                // match either type at runtime
                if (auto view_ptr = nmtools::get_if<left_t>(&view)) {
                    return return_t{this->eval(*view_ptr)};
                } else /* if (auto view_ptr = get_if<right_t>(&view)) */ {
                    auto view_rptr = nmtools::get_if<right_t>(&view);
                    return return_t{this->eval(*view_rptr)};
                }
            } else if constexpr (meta::is_maybe_v<view_t> && !object_enable) {
                using view_type   = meta::get_maybe_type_t<view_t>;
                using result_type = decltype(this->eval(meta::declval<view_type>()));
                static_assert(!meta::is_maybe_v<result_type>);
                using return_type = nmtools_maybe<result_type>;
                return (view
                    ? return_type{this->eval(*view)}
                    : return_type{meta::Nothing}
                );
            } else {
                auto shape = nmtools::shape<true>(unwrap(view));
                auto size  = nmtools::size<true>(unwrap(view));
                using T = get_element_type_t<remove_cvref_t<decltype(unwrap(view))>>;
                using element_t = conditional_t<is_same_v<T,bool>,nm_bool_t,T>;

                auto result = this->create(dtype_t<element_t>{},shape,size);
                this->eval(result,unwrap(view));

                return result;
            }
        }
    };

    constexpr inline auto Context = context_t<> {};
}

namespace nmtools::tilekit
{
    template <auto bit_width, typename array_t, typename tile_shape_t, typename padding_t>
    struct load_t<
        vector::context_t<bit_width>, array_t, tile_shape_t, padding_t
    > {
        using context_type    = vector::context_t<bit_width>;
        using tile_shape_type = tile_shape_t;
        using array_type   = array_t;
        using element_type = get_element_type_t<array_t>;

        static constexpr auto SIZE = index::product(to_value_v<tile_shape_type>);
        using buffer_type = nmtools_array<element_type,SIZE>;
        using shape_buffer_type = tile_shape_type;
        using result_type = vector::object_t<buffer_type,shape_buffer_type,bit_width>;
        using vector_type = typename result_type::vector_type;

        template <typename ctx_t, typename offset_t>
        static auto load(ctx_t, const array_type& array, const offset_t& offset, const tile_shape_type& tile_shape, padding_t padding)
        {
            return vector::load<bit_width>(array,offset,tile_shape,padding);
        }

        template <typename ctx_t, typename offset_t>
        auto operator()(ctx_t, const array_type& array, const offset_t& offset, const tile_shape_type& tile_shape, padding_t padding) const
        {
            return load(ctx_t{},array,offset,tile_shape,padding);
        }
    };

    template <auto bit_width, typename output_t, typename padding_t>
    struct store_t<
        vector::context_t<bit_width>, output_t, padding_t
    > {
        using context_type = vector::context_t<bit_width>;
        using padding_type = padding_t;
        using output_type  = output_t;

        template <typename offset_t, typename result_t>
        auto operator()(context_type, output_type& output, const offset_t& offset, const result_t& result, padding_type padding) const
        {
            return vector::store<bit_width>(output,offset,result,padding);
        }
    };

    template <auto bit_width=128>
    inline auto worker_id(vector::context_t<bit_width> ctx)
    {
        return nmtools_tuple{ctx.worker_id};
    }

    template <auto bit_width=128>
    inline auto worker_size(vector::context_t<bit_width> ctx)
    {
        return nmtools_tuple{ctx.worker_size};
    }
}

namespace nmtools
{
    template <size_t I,
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct get_t<I,tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>>
        : get_t<I,object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>> {};
    
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct VECTOR_COMPUTE_SRC_INDICES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename tile_indices_t, typename src_ndoffset_t, typename num_lane_t>
    struct resolve_optype<
        void, tilekit::vector::compute_src_indices_t, tile_indices_t, src_ndoffset_t, num_lane_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<tile_indices_t>
                || !is_index_array_v<src_ndoffset_t>
                || !is_constant_index_v<num_lane_t>
            ) {
                using type = error::VECTOR_COMPUTE_SRC_INDICES_UNSUPPORTED<tile_indices_t,src_ndoffset_t,num_lane_t>;
                return as_value_v<type>;
            } else if constexpr ((is_constant_index_array_v<tile_indices_t> || is_mixed_index_array_v<tile_indices_t>)
                && (is_constant_index_array_v<src_ndoffset_t> || is_mixed_index_array_v<src_ndoffset_t>)
            ) {
                constexpr auto tile_indices = to_value_v<tile_indices_t>;
                constexpr auto src_ndoffset = to_value_v<src_ndoffset_t>;
                constexpr auto num_lane = num_lane_t{};
                constexpr auto result = unwrap(tilekit::vector::compute_src_indices(tile_indices,src_ndoffset,num_lane));
                using nmtools::at, nmtools::len;
                constexpr auto N = len(result);
                // check if should return array
                constexpr auto return_array = [&](){
                    auto all_none = !has_value(at(result,0));
                    for (nm_size_t i=1; i<(nm_size_t)N; i++) {
                        all_none &= !has_value(at(result,i));
                    }
                    return all_none;
                }();
                if constexpr (return_array) {
                    using type = nmtools_array<nm_size_t,N>;
                    return as_value_v<type>;
                } else {
                    return template_reduce<N>([&](auto init, auto index){
                        constexpr auto i = decltype(index)::value;
                        using init_t = type_t<decltype(init)>;
                        constexpr auto result_i = at(result,i);
                        if constexpr (has_value(result_i)) {
                            using type_i = ct<(nm_size_t)result_i>;
                            using type   = append_type_t<init_t,type_i>;
                            return as_value_v<type>;
                        } else {
                            using type_i = nm_size_t;
                            using type   = append_type_t<init_t,type_i>;
                            return as_value_v<type>;
                        }
                    }, as_value_v<nmtools_tuple<>>);
                }
            } else {
                constexpr auto TILE_DIM = len_v<tile_indices_t>;
                constexpr auto SRC_DIM  = len_v<src_ndoffset_t>;
                using element_t = conditional_t<
                    (is_mixed_index_array_v<tile_indices_t> || is_mixed_index_array_v<src_ndoffset_t>)
                    || (is_nullable_index_array_v<tile_indices_t> || is_nullable_index_array_v<src_ndoffset_t>)
                    , nullable_size_t
                    , nm_size_t
                >;
                [[maybe_unused]] constexpr auto MAX_TILE_DIM = max_len_v<tile_indices_t>;
                [[maybe_unused]] constexpr auto MAX_SRC_DIM  = max_len_v<src_ndoffset_t>;
                if constexpr ((TILE_DIM > 0) && (SRC_DIM > 0)) {
                    // assume the same
                    using type = nmtools_array<element_t,TILE_DIM>;
                    return as_value_v<type>;
                } else if constexpr ((MAX_TILE_DIM > 0) || (MAX_SRC_DIM > 0)) {
                    constexpr auto MAX_DIM = (MAX_TILE_DIM > 0 ? MAX_TILE_DIM : MAX_SRC_DIM);
                    using type = nmtools_static_vector<element_t,MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

namespace nmtools::meta
{
    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct get_element_type<tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>>
        : get_element_type<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>> {};
    
    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct is_ndarray<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>
    > : is_ndarray<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>> {};

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_dim<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>
    > : fixed_dim<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>> {};

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_shape<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>
    > : fixed_shape<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>> {};

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_size<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>
    > : fixed_size<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>> {};

        template <typename U
        , typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct replace_element_type<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>, U
    >
    {
        using buffer_type = replace_element_type_t<buffer_t,U>;
        using type = tilekit::vector::object_t<buffer_type,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>;
    }; // replace_element_type
}

#endif // NMTOOLS_TILEKIT_VECTOR_HPP