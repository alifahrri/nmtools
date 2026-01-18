#ifndef NMTOOLS_TILEKIT_VECTOR_HPP
#define NMTOOLS_TILEKIT_VECTOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/ndarray/array.hpp"

namespace nmtools::tilekit::vector
{
    template <LayoutKind BufferLayout=LayoutKind::RowMajor>
    struct vector_eval_resolver_t {};

    template<typename T, int N>
    struct make_vector {
        using type __attribute__((vector_size(N), aligned(4))) = T;
    };

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t=resolve_stride_type_t
        , template <typename...>typename compute_offset_t=row_major_offset_t
        , template <auto...>typename resolver_t=vector_eval_resolver_t
        , typename=void>
    struct object_t
        : nmtools::object_t<buffer_t,shape_buffer_t,resolve_stride_type_t,row_major_offset_t,resolver_t>
    {
        // TODO: assert size/shape buffer and shape is known at compile-time
        using base_type = nmtools::object_t<buffer_t,shape_buffer_t,resolve_stride_type_t,row_major_offset_t,resolver_t>;
        using value_type = typename base_type::value_type;

        static constexpr auto n_bytes = bit_width / 8;
        using vector_type = typename make_vector<value_type, n_bytes>::type;

        static constexpr auto n_iter = (fixed_size_v<base_type> * sizeof(value_type)) / n_bytes;

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

    template <typename bit_width_t, typename T, typename flat_index_t, typename tile_ndoffset_t, typename tile_shape_t, typename src_shape_t, typename src_strides_t>
    constexpr auto compute_load_offset(dtype_t<T>, bit_width_t, flat_index_t flat_index, const tile_ndoffset_t& tile_ndoffset, const tile_shape_t, const src_shape_t& src_shape, const src_strides_t& src_strides)
    {
        constexpr auto BIT_WIDTH = bit_width_t::value;
        constexpr auto NUMEL = BIT_WIDTH / (sizeof(T) * 8 /*bit*/);
        auto offset = index::compute_offset(tile_ndoffset,src_strides);

        // TODO: generalize to ND
        constexpr auto last_tile = at(tile_shape_t{},ct_v<-1>);
        auto last_dim = at(src_shape,ct_v<-1>) - last_tile;

        auto result = (flat_index * NUMEL) + ((flat_index / (last_tile / NUMEL)) * last_dim) + offset;
        return result;
    }
    
    template <typename bit_width_t, typename T, typename flat_index_t, typename tile_ndoffset_t, typename tile_shape_t, typename src_shape_t>
    constexpr auto compute_load_offset(dtype_t<T> dtype, bit_width_t bit_width, flat_index_t flat_index, const tile_ndoffset_t& tile_ndoffset, const tile_shape_t tile_shape, const src_shape_t& src_shape)
    {
        auto src_strides = index::compute_strides(src_shape);
        return compute_load_offset(dtype,bit_width,flat_index,tile_ndoffset,tile_shape,src_shape,src_strides);
    }

    

    // TODO: rename offset to indices

    template <auto bit_width=128, typename array_t, typename offset_t, typename tile_shape_t, typename axis_t=none_t>
    constexpr auto load(const array_t& array, const offset_t& offset, const tile_shape_t& tile_shape, [[maybe_unused]] const axis_t& axis=axis_t{})
    {
        using element_t = meta::get_element_type_t<array_t>;

        constexpr auto SIZE = index::product(to_value_v<tile_shape_t>);
        using buffer_t = nmtools_array<element_t,SIZE>;
        using shape_buffer_t = tile_shape_t;
        using result_t = object_t<buffer_t,shape_buffer_t,bit_width>;
        using vector_t = typename result_t::vector_type;

        auto result = result_t{};

        auto src_shape   = shape(array);
        auto src_strides = index::compute_strides(src_shape);

        constexpr auto NUM_LANE = bit_width / (sizeof(element_t) * 8 /*bit*/);
        constexpr auto NUM_LOAD = SIZE / NUM_LANE;

        template_for<NUM_LOAD>([&](auto i){
            constexpr auto I = decltype(i)::value;
            auto src_offset  = compute_load_offset(dtype_t<element_t>{},ct_v<bit_width>,i,offset,tile_shape,src_shape,src_strides);
            *((vector_t*)result.data()+I) = *((vector_t*)&array.data()[src_offset]);
        });

        return result;
    }

    template <auto bit_width=128, typename output_t, typename offset_t, typename result_t, typename axis_t=none_t>
    constexpr auto store(output_t& output, const offset_t& offset, const result_t& result, [[maybe_unused]] const axis_t& axis=axis_t{})
    {
        // static_assert( meta::is_fixed_shape_v<result_t> );
        static_assert( meta::is_constant_index_v<axis_t> || is_none_v<axis_t> );

        constexpr auto DIM = meta::len_v<offset_t>;
        static_assert( DIM > 0 );

        using vector_t = typename result_t::vector_type;

        constexpr auto tile_shape = fixed_shape_v<result_t>;
        using element_t = get_element_type_t<result_t>;
        constexpr auto SIZE = index::product(tile_shape);
        constexpr auto NUM_LANE = bit_width / (sizeof(element_t) * 8 /*bit*/);
        constexpr auto NUM_LOAD = SIZE / NUM_LANE;

        auto output_shape   = shape(output);
        auto output_strides = index::compute_strides(output_shape);

        auto dtype = dtype_t<element_t>{};
        auto BIT_WIDTH = ct_v<bit_width>;
        template_for<NUM_LOAD>([&](auto i){
            constexpr auto I = decltype(i)::value;
            auto src_offset  = compute_load_offset(dtype,BIT_WIDTH,i,offset,tile_shape,output_shape,output_strides);
            *((vector_t*)&output.data()[src_offset]) = *((vector_t*)result.data()+I);
        });
    }

    // context
    // TODO: pass bit width
    struct context_t {};

    constexpr inline auto Context = context_t {};
}

namespace nmtools::tilekit
{
    // TODO: specialize eval graph, instead of function

    template <typename array_t, typename offset_t, typename shape_t, typename axis_t=none_t>
    constexpr auto load(vector::context_t, const array_t& array, const offset_t& offset, const shape_t& shape, const axis_t& axis=axis_t{})
    {
        return vector::load(array,offset,shape,axis);
    }

    template <typename output_t, typename offset_t, typename result_t, typename axis_t=none_t>
    constexpr auto store(vector::context_t, output_t& output, const offset_t& offset, const result_t& result, [[maybe_unused]] const axis_t& axis=axis_t{})
    {
        return vector::store(output,offset,result,axis);
    }
}

namespace nmtools
{
    template <size_t I,
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , template <auto...>typename resolver_t>
    struct get_t<I,tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t,resolver_t>>
        : get_t<I,object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t,resolver_t>> {};
    
}

namespace nmtools::meta
{
    // TODO parametrize, unify with array version
    template <LayoutKind BufferLayout, typename view_t>
    struct resolve_optype<
        void, tilekit::vector::vector_eval_resolver_t<BufferLayout>, view_t, none_t
    >
    {
        template <typename buffer_t, typename shape_buffer_t>
        static constexpr auto make_ndarray(as_value<buffer_t>, as_value<shape_buffer_t>)
        {
            // TODO: parametrize bit_width
            constexpr auto bit_width = 128;
            if constexpr (BufferLayout == LayoutKind::RowMajor) {
                using type = tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,resolve_stride_type_t,row_major_offset_t>;
                return as_value_v<type>;
            } else if constexpr (BufferLayout == LayoutKind::ColumnMajor) {
                using type = tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,resolve_stride_type_t,column_major_offset_t>;
                return as_value_v<type>;
            } else {
                using type = error::EVAL_RESULT_UNSUPPORTED<view_t,none_t,as_type<BufferLayout>>;
                return as_value_v<type>;
            }
        }

        static constexpr auto vtype = [](){
            using element_type = get_element_type_t<view_t>;
            using error_type [[maybe_unused]] = error::EVAL_RESULT_UNSUPPORTED<view_t,none_t,as_type<BufferLayout>>;
            // TODO: remove, try to read from `nmtools::shape(declval<view_t>())` instead
            // the following is kept for temporary backward compatibility
            constexpr auto shape  = fixed_shape_v<view_t>;
            constexpr auto dim    = fixed_dim_v<view_t>;
            constexpr auto size   = fixed_size_v<view_t>;
            constexpr auto b_dim  = bounded_dim_v<view_t>;
            constexpr auto b_size = bounded_size_v<view_t>;
            using shape_type  = decltype(shape);
            using dim_type    = decltype(dim);
            using size_type   = decltype(size);
            using b_dim_type  = decltype(b_dim);
            using b_size_type = decltype(b_size);
            using nmtools::len, nmtools::at;
            // constant shape
            constexpr auto c_shape_vtype = [&](){
                if constexpr (!is_fail_v<shape_type>) {
                    return template_reduce<len(shape)-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        return as_value_v<append_type_t<init_type,ct<(size_t)at(shape,ct_v<decltype(index)::value+1>)>>>;
                    }, as_value_v<nmtools_tuple<ct<(size_t)at(shape,ct_v<0>)>>>);
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // clipped shape
            constexpr auto cl_shape_vtype = [&](){
                using shape_t = decltype(nmtools::shape(declval<view_t>()));
                if constexpr (is_clipped_index_array_v<shape_t>) {
                    return as_value_v<shape_t>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // fixed shape
            constexpr auto f_shape_vtype = [&](){
                if constexpr (!is_fail_v<dim_type>) {
                    using type = nmtools_array<size_t,dim>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // bounded shape (for bounded dim)
            constexpr auto b_shape_vtype = [&](){
                if constexpr (!is_fail_v<b_dim_type>) {
                    using type = nmtools_static_vector<size_t,b_dim>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // fixed buffer
            constexpr auto f_buffer_vtype = [&](){
                if constexpr (!is_fail_v<size_type>) {
                    using type = nmtools_array<element_type,size>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // bounded buffer
            constexpr auto b_buffer_vtype = [&](){
                if constexpr (!is_fail_v<type_t<decltype(cl_shape_vtype)>>) {
                    constexpr auto size = index::product(to_value_v<type_t<decltype(cl_shape_vtype)>>);
                    using type = nmtools_static_vector<element_type,size>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<b_size_type>) {
                    using type = nmtools_static_vector<element_type,b_size>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();

            using c_shape_type  [[maybe_unused]] = type_t<decltype(c_shape_vtype)>;
            using l_shape_type  [[maybe_unused]] = type_t<decltype(cl_shape_vtype)>;
            using f_shape_type  [[maybe_unused]] = type_t<decltype(f_shape_vtype)>;
            using b_shape_type  [[maybe_unused]] = type_t<decltype(b_shape_vtype)>;
            using f_buffer_type [[maybe_unused]] = type_t<decltype(f_buffer_vtype)>;
            using b_buffer_type [[maybe_unused]] = type_t<decltype(b_buffer_vtype)>;
            // dynamic buffer
            using d_buffer_type [[maybe_unused]] = nmtools_list<element_type>;
            // TODO: add small vector optimization fo shape
            using d_shape_type  [[maybe_unused]] = nmtools_list<size_t>;

            if constexpr (is_num_v<view_t>) {
                return as_value_v<element_type>;
            // prefer constant-shape, no-dynamic allocation
            } else if constexpr (
                !is_fail_v<c_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<c_shape_type>);
            } else if constexpr (
                !is_fail_v<c_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<c_shape_type>);
            } else if constexpr (
                !is_fail_v<l_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<l_shape_type>);
            } else if constexpr (
                !is_fail_v<l_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<l_shape_type>);
            } else if constexpr (
                !is_fail_v<f_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<f_shape_type>);
            } else if constexpr (
                !is_fail_v<f_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<f_shape_type>);
            }
            // bounded shape
            else if constexpr (
                !is_fail_v<b_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<b_shape_type>);
            } else if constexpr (
                !is_fail_v<b_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<b_shape_type>);
            }
            // dynamic shape
            else if constexpr (
                !is_fail_v<d_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<d_shape_type>);
            } else if constexpr (
                !is_fail_v<d_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<d_shape_type>);
            } else if constexpr (
                !is_fail_v<c_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<c_shape_type>);
            } else if constexpr (
                !is_fail_v<l_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<l_shape_type>);
            } else if constexpr (
                !is_fail_v<f_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<f_shape_type>);
            } else if constexpr (
                !is_fail_v<b_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<b_shape_type>);
            } else if constexpr (
                !is_fail_v<d_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<d_shape_type>);
            } else {
                return as_value_v<error_type>;
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
        , template <typename...>typename offset_compute_t
        , template <auto...>typename resolver_t>
    struct get_element_type<tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t,resolver_t>>
        : get_element_type<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t,resolver_t>> {};
    
    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , template <auto...>typename resolver_t>
    struct is_ndarray<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t,resolver_t>
    > : is_ndarray<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t,resolver_t>> {};

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , template <auto...>typename resolver_t>
    struct fixed_dim<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t,resolver_t>
    > : fixed_dim<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t,resolver_t>> {};

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , template <auto...>typename resolver_t>
    struct fixed_shape<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t,resolver_t>
    > : fixed_shape<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t,resolver_t>> {};

    template <
          typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , template <auto...>typename resolver_t>
    struct fixed_size<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t,resolver_t>
    > : fixed_size<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t,resolver_t>> {};

        template <typename U
        , typename buffer_t
        , typename shape_buffer_t
        , auto bit_width
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , template <auto...>typename resolver_t>
    struct replace_element_type<
        tilekit::vector::object_t<buffer_t,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t,resolver_t>, U
    >
    {
        using buffer_type = replace_element_type_t<buffer_t,U>;
        using type = tilekit::vector::object_t<buffer_type,shape_buffer_t,bit_width,stride_buffer_t,offset_compute_t>;
    }; // replace_element_type
}

#endif // NMTOOLS_TILEKIT_VECTOR_HPP