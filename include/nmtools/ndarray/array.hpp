#ifndef NMTOOLS_NDARRAY_ARRAY_HPP
#define NMTOOLS_NDARRAY_ARRAY_HPP

#include "nmtools/meta.hpp"
#include "nmtools/ndarray/ndarray.hpp"
#include "nmtools/core/alias.hpp"
#include "nmtools/core/reshape.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/amax.hpp"
#include "nmtools/array/ufuncs/amin.hpp"
#include "nmtools/array/ufuncs/clip.hpp"
#include "nmtools/array/ufuncs/greater.hpp"
#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/array/ufuncs/less.hpp"
#include "nmtools/array/ufuncs/less_equal.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/power.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/array/prod.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/var.hpp"

#include "nmtools/array/copy.hpp"
#include "nmtools/array/cumprod.hpp"
#include "nmtools/array/cumsum.hpp"
#include "nmtools/array/diagonal.hpp"
#include "nmtools/array/flatten.hpp"
#include "nmtools/array/repeat.hpp"
#include "nmtools/array/stddev.hpp"
#include "nmtools/array/squeeze.hpp"
#include "nmtools/array/swapaxes.hpp"
#include "nmtools/array/trace.hpp"
#include "nmtools/array/transpose.hpp"

namespace nmtools::tag
{
    // tag for creating array object
    struct array_object_t {};
}

namespace nmtools::view
{
    #define nmtools_ndarray_method(method) \
    template <typename...args_t> \
    constexpr auto method(const args_t&...args) const \
    { \
        auto result = view::method(view_type{*this},args...); \
        using result_t = decltype(unwrap(result)); \
        if constexpr (meta::is_num_v<result_t>) { \
            return result; \
        } else { \
            return view::decorator_t<view::object_t,result_t>{unwrap(result)}; \
        } \
    }

    template <typename array_t, typename id_t=none_t, typename=void>
    struct object_t
    {
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;

        // TODO: assert id is constant index (or none)
        using id_type = id_t;

        static constexpr auto operands_ids = nmtools_tuple{id_type{}};

        // const reference to actual array type
        array_type array;
        id_type id;

        /**
         * @brief construct object view
         * 
         */
        constexpr object_t(const array_t& array, id_t id=id_t{})
            : array(initialize<array_type>(array))
            , id(id)
        {}

        constexpr auto attribute() const noexcept
        {
            return nmtools_tuple{id};
        }

        constexpr auto shape() const
        {
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<array_type>>) {
                return nmtools::shape<true>(*array);
            } else {
                return nmtools::shape<true>(array);
            }
        }

        constexpr auto dim() const
        {
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<array_type>>) {
                return nmtools::dim<true>(*array);
            } else {
                return nmtools::dim<true>(array);
            }
        }

        constexpr auto size() const
        {
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<array_type>>) {
                return nmtools::size<true>(*array);
            } else {
                return nmtools::size<true>(array);
            }
        }

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        } // operands

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            return pack_indices(indices...);
        } // index

        using view_type = decorator_t<object_t,array_t,id_t>;

        nmtools_ndarray_method(add)
        nmtools_ndarray_method(subtract)
        nmtools_ndarray_method(multiply)
        nmtools_ndarray_method(divide)

        nmtools_ndarray_method(less)
        nmtools_ndarray_method(less_equal)
        nmtools_ndarray_method(greater)
        nmtools_ndarray_method(greater_equal)

        nmtools_ndarray_method(clip)
        nmtools_ndarray_method(cumprod)
        nmtools_ndarray_method(cumsum)
        nmtools_ndarray_method(diagonal)
        nmtools_ndarray_method(reshape)
        nmtools_ndarray_method(repeat)
        nmtools_ndarray_method(squeeze)
        nmtools_ndarray_method(swapaxes)
        nmtools_ndarray_method(trace)
        nmtools_ndarray_method(transpose)

        nmtools_ndarray_method(max)
        nmtools_ndarray_method(min)
        nmtools_ndarray_method(prod)
        nmtools_ndarray_method(sum)
        nmtools_ndarray_method(flatten)
        nmtools_ndarray_method(mean)
        nmtools_ndarray_method(var)
        nmtools_ndarray_method(std)

        template <typename other_t>
        constexpr auto operator+(const other_t& other) const
        {
            auto result = this->add(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator-(const other_t& other) const
        {
            auto result = this->subtract(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator*(const other_t& other) const
        {
            auto result = this->multiply(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator/(const other_t& other) const
        {
            auto result = this->divide(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator>(const other_t& other) const
        {
            return this->greater(other);
        }
        
        template <typename other_t>
        constexpr auto operator>=(const other_t& other) const
        {
            return this->greater_equal(other);
        }

        template <typename other_t>
        constexpr auto operator<(const other_t& other) const
        {
            return this->less(other);
        }
        
        template <typename other_t>
        constexpr auto operator<=(const other_t& other) const
        {
            return this->less_equal(other);
        }
    }; // object_t

    #undef nmtools_ndarray_method

    // TODO: drop none default, make id mandatory
    template <typename array_t, typename id_t=meta::ct<0>>
    constexpr auto array(const array_t& array, id_t id=id_t{})
    {
        // TODO: handle either type
        if constexpr (meta::is_maybe_v<array_t> || meta::is_maybe_v<id_t>) {
            return view::array(unwrap(array),unwrap(id));
        } else if constexpr (meta::is_same_view_v<object_t,array_t> && !is_none_v<id_t>) {
            // Quick-hack: arraying an array will rename
            const auto& m_array = array.array;
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<decltype(m_array)>>) {
                return view::array(*array.array,id);
            } else {
                return view::array(array.array,id);
            }
        } else if constexpr (meta::is_view_v<array_t>) {
            // view is already arrayed
            static_assert( array_t::id_type::value == id_t::value );
            return array;
        } else {
            return decorator_t<object_t,array_t,id_t>{{array,id}};
        }
    } // array

    template <typename...arrays_t>
    constexpr auto arrays(const arrays_t&...arrays)
    {
        auto array_pack = pack_operands(arrays...);
        auto f = [](const auto& array_pack){
            constexpr auto N = sizeof...(arrays);
            constexpr auto initial_ids = meta::template_reduce<N>([&](auto init, auto index){
                using array_type = decltype(unwrap(at(array_pack,index)));
                constexpr auto id = get_id_v<meta::remove_cvref_pointer_t<array_type>>;
                return utility::tuple_append(init,meta::ct_v<(nm_index_t)id>);
            },nmtools_tuple{});
            constexpr auto max_id    = index::max(meta::to_value_v<decltype(initial_ids)>);
            constexpr auto offset_id = max_id + 1; // if max_id: -1, then offset 0
            constexpr auto final_ids = meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto id = at(initial_ids,index);
                constexpr auto final_id = ((id < 0) ? (offset_id + index) : id);
                return utility::tuple_append(init,meta::ct_v<final_id>);
            },nmtools_tuple{});
            auto arrays = meta::template_reduce<N>([&](auto init, auto index){
                const auto& array = at(array_pack,index);
                if constexpr (meta::is_pointer_v<meta::remove_cvref_pointer_t<decltype(array)>>) {
                    return append_operands(init,view::array(*array,at(final_ids,index)));
                } else {
                    return append_operands(init,view::array(array,at(final_ids,index)));
                }
            },nmtools_tuple{});
            if constexpr (N == 1) {
                return nmtools::get<0>(arrays);
            } else {
                return arrays;
            }
        };
        return f(unwrap(array_pack));
    } // arrays
} // nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename...args_t>
    struct is_ndarray< view::decorator_t<view::object_t, array_t, args_t...> >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    template <typename array_t, typename...args_t>
    struct is_num< view::decorator_t<view::object_t, array_t, args_t...> >
    {
        static constexpr auto value = is_num_v<array_t>;
    };

    // specialization for ptr
    template <typename array_t, typename...args_t>
    struct is_ndarray< view::decorator_t<view::object_t, array_t*, args_t...> >
    {
        static constexpr auto value = is_num_v<array_t>;
    };

    template <typename array_t, typename...args_t>
    struct get_element_type<
        view::decorator_t<view::object_t, array_t, args_t...>
    >
    {
        using type = get_element_type_t<array_t>;
    };

    template <typename T, typename...args_t>
    struct get_element_type<
        view::decorator_t<view::object_t,T*,args_t...>
    >
    {
        using type = meta::remove_address_space_t<T>;
    };
} // namespace nmtools::meta

namespace nmtools
{
    // TODO: propagate evaluator context
    #define nmtools_ndarray_method(method) \
    template <typename...args_t> \
    constexpr auto method(const args_t&...args) const \
    { \
        auto v = view::method(*this,args...); \
        auto result = nmtools::eval(v); \
        return result; \
    }

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t=resolve_stride_type_t
        , template <typename...>typename compute_offset_t=row_major_offset_t
        , typename=void>
    struct object_t : base_ndarray_t<object_t<buffer_t, shape_buffer_t, stride_buffer_t, compute_offset_t>>
    {
        using buffer_type = buffer_t;
        using value_type  = meta::get_element_type_t<buffer_type>;
        using shape_type  = shape_buffer_t;
        using index_type  = meta::get_element_or_common_type_t<shape_type>;
        using stride_type = stride_buffer_t<shape_type>;
        using base_type   = base_ndarray_t<object_t>;
        using offset_type = compute_offset_t<shape_type,stride_type>;

        static_assert( meta::is_index_array_v<shape_type>, "unsupported shape_type for ndarray" );
        static_assert( meta::is_index_array_v<stride_type>, "unsupported stride_type for ndarray");

        buffer_type data_;
        shape_type  shape_;
        stride_type strides_;
        offset_type offset_;

        constexpr object_t()
            : data_     (base_type::template initialize_data<buffer_type>())
            , shape_    (base_type::template initialize_shape<shape_type>(data_))
            , strides_  (base_type::template compute_strides<stride_type>(shape_))
            , offset_   (shape_,strides_)
        {
            if constexpr (meta::is_resizable_v<buffer_type>) {
                auto numel = index::product(shape_);
                // shape may be fixed while data is resizable
                if (len(data_) != numel) {
                    data_.resize(numel);
                }
            }
        }

        template <typename size_type, typename...size_types>
        constexpr auto resize([[maybe_unused]] const size_type& size, const size_types&...sizes)
            -> meta::enable_if_t<
                   (meta::is_index_v<size_type> || meta::is_index_array_v<size_type>)
                && (meta::is_index_v<size_types> && ...)
                && (!meta::is_constant_index_array_v<shape_type>)
            , bool>
        {
            const auto sizes_  = index::pack_indices(size,sizes...);
            const auto numel   = index::product(sizes_);
            // since size may be packed, the proper way to read dim is using len instead of sizes..+1
            auto new_dim = len(sizes_);
            if constexpr (meta::is_resizable_v<shape_type>) {
                shape_.resize(new_dim);
            }
            if constexpr (meta::is_resizable_v<buffer_type>) {
                data_.resize(numel);
            }
            auto same_dim   = (size_t)len(shape_) == (size_t)new_dim;
            auto same_numel = [&](){
                // NOTE: fixed buffer is used to indicate fixed size
                // , to use fixed dim dynamic size, use static_vector as buffer
                #if 0
                // NOTE: to allow fixed buffer, fixed dim, dynamic shape
                if (meta::is_resizable_v<buffer_type>) {
                    // buffer is resizable, can deduce numel from len(data_)
                    return (size_t)len(data_) == (size_t)numel;
                } else if (same_dim) {
                    // same dim and can assign value to shape
                    return !meta::is_constant_index_array_v<shape_type>;
                } else {
                    return false;
                }
                #else
                return (size_t)len(data_) == (size_t)numel;
                #endif
            }();
            if (!same_numel) {
                return false;
            }
            if (!same_dim) {
                return false;
            }
            if constexpr (meta::is_clipped_index_array_v<shape_type>) {
                constexpr auto max_sizes = meta::to_value_v<shape_type>;
                if ((size_t)len(sizes_) != (size_t)len(max_sizes)) {
                    return false;
                }
                if ((size_t)index::product(sizes_) > (size_t)index::product(max_sizes)) {
                    return false;
                }
                for (size_t i=0; i<len(max_sizes); i++) {
                    if ((size_t)at(sizes_,i) > (size_t)at(max_sizes,i)) {
                        return false;
                    }
                }
            }
            if constexpr (meta::is_tuple_v<shape_type>) {
                // this may be the case for clipped_shape
                constexpr auto N = meta::len_v<shape_type>;
                meta::template_for<N>([&](auto index){
                    at(shape_,index) = at(sizes_,index);
                });
            } else {
                for (nm_size_t i=0; i<new_dim; i++) {
                    const auto si = at(sizes_,i);
                    at(shape_,i) = si;
                }
            }
            // NOTE: using operator= directly may cause unusable for constexpr, (e.g. std::tuple)
            // quick workaround just use assignment of the elements
            auto m_strides_ = base_type::template compute_strides<stride_type>(shape_);
            if constexpr (meta::is_tuple_v<stride_type>) {
                constexpr auto N = meta::len_v<stride_type>;
                meta::template_for<N>([&](auto I){
                    at(strides_,I) = at(m_strides_,I);
                });
            } else {
                if constexpr (meta::is_resizable_v<stride_type>) {
                    strides_.resize(len(m_strides_));
                }
                for (size_t i=0; i<(size_t)len(m_strides_); i++) {
                    at(strides_,i) = at(m_strides_,i);
                }
            }
            offset_ = offset_type(shape_,strides_);
            return true;
        } // resize

        nmtools_ndarray_method(add)
        nmtools_ndarray_method(subtract)
        nmtools_ndarray_method(multiply)
        nmtools_ndarray_method(divide)

        nmtools_ndarray_method(less)
        nmtools_ndarray_method(less_equal)
        nmtools_ndarray_method(greater)
        nmtools_ndarray_method(greater_equal)

        nmtools_ndarray_method(clip)
        nmtools_ndarray_method(cumprod)
        nmtools_ndarray_method(cumsum)
        nmtools_ndarray_method(diagonal)
        nmtools_ndarray_method(reshape)
        nmtools_ndarray_method(repeat)
        nmtools_ndarray_method(squeeze)
        nmtools_ndarray_method(swapaxes)
        nmtools_ndarray_method(trace)
        nmtools_ndarray_method(transpose)

        nmtools_ndarray_method(max)
        nmtools_ndarray_method(min)
        nmtools_ndarray_method(prod)
        nmtools_ndarray_method(sum)
        nmtools_ndarray_method(flatten)
        nmtools_ndarray_method(mean)
        nmtools_ndarray_method(var)
        nmtools_ndarray_method(std)

        template <typename other_t>
        constexpr auto operator+(const other_t& other) const
        {
            auto result = this->add(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator-(const other_t& other) const
        {
            auto result = this->subtract(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator*(const other_t& other) const
        {
            auto result = this->multiply(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator/(const other_t& other) const
        {
            auto result = this->divide(other);
            return result;
        }

        template <typename other_t>
        constexpr auto operator>(const other_t& other) const
        {
            return this->greater(other);
        }
        
        template <typename other_t>
        constexpr auto operator>=(const other_t& other) const
        {
            return this->greater_equal(other);
        }

        template <typename other_t>
        constexpr auto operator<(const other_t& other) const
        {
            return this->less(other);
        }
        
        template <typename other_t>
        constexpr auto operator<=(const other_t& other) const
        {
            return this->less_equal(other);
        }
    }; // object_t

    #undef nmtools_ndarray_method

    template <LayoutKind BufferLayout=LayoutKind::RowMajor>
    struct object_eval_resolver_t {};
} // nmtools

namespace nmtools::meta
{
    template <LayoutKind BufferLayout, typename view_t>
    struct resolve_optype<
        void, object_eval_resolver_t<BufferLayout>, view_t, none_t
    >
    {
        template <typename buffer_t, typename shape_buffer_t>
        static constexpr auto make_ndarray(as_value<buffer_t>, as_value<shape_buffer_t>)
        {
            if constexpr (BufferLayout == LayoutKind::RowMajor) {
                using type = object_t<buffer_t,shape_buffer_t,resolve_stride_type_t,row_major_offset_t>;
                return as_value_v<type>;
            } else if constexpr (BufferLayout == LayoutKind::ColumnMajor) {
                using type = object_t<buffer_t,shape_buffer_t,resolve_stride_type_t,column_major_offset_t>;
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

namespace nmtools
{
    template <typename array_t>
    constexpr auto array(const array_t& array)
    {
        auto resolver = meta::as_value_v<object_eval_resolver_t<LayoutKind::RowMajor>>;
        auto dst = nmtools::copy(unwrap(array),None,None,resolver);
        return dst;
    }
}

namespace nmtools
{
    template <size_t I,
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct get_t<I,object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>>
    {
        using array_type = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;

        static constexpr auto vtype = [](){
            constexpr auto dim = meta::len_v<shape_buffer_t>;
            if constexpr (meta::is_constant_index_array_v<shape_buffer_t> && (dim==1)) {
                using type = meta::get_element_type_t<buffer_t>;
                return meta::as_value_v<type>;
            } else {
                using type = meta::error::TEMPLATE_GET_UNSUPPORTED<array_type,meta::as_type<I>>;
                return meta::as_value_v<type>;
            }
        }();

        using type = meta::type_t<decltype(vtype)>;

        constexpr decltype(auto) operator()([[maybe_unused]] const array_type& t) const noexcept
        {
            if constexpr (meta::is_fail_v<type>) {
                return type{};
            } else {
                return t(I);
            }
        }

        constexpr decltype(auto) operator()([[maybe_unused]] array_type& t) const noexcept
        {
            if constexpr (meta::is_fail_v<type>) {
                return type{};
            } else {
                return t(I);
            }
        }
    };
}

namespace nmtools::meta
{
    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct get_element_type<object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>>
    {
        using array_type = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        static constexpr auto vtype = [](){
            using T = typename array_type::value_type;
            if constexpr (is_num_v<T>) {
                return as_value_v<T>;
            } else {
                return as_value_v<error::GET_ELEMENT_TYPE_UNSUPPORTED<array_type>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_element_type

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct is_ndarray<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using element_type = typename array_type::value_type;
        static constexpr auto value = is_num_v<element_type>;
    }; // is_ndarray

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_dim<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_index_array_v<shape_type>) {
                return len_v<shape_type>;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_dim

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_shape<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_shape

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_size<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_size_v<buffer_type>) {
                return fixed_size_v<buffer_type>;
            } else if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_size

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct bounded_dim<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<shape_type>) {
                return bounded_size_v<shape_type>;
            } else if constexpr (is_fixed_size_v<shape_type>) {
                // TODO: consider to add error mapping fn so this else-if/else block not needed
                return fixed_size_v<shape_type>;
            } else {
                return error::BOUNDED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // bounded_dim

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct bounded_size<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<buffer_type>) {
                return bounded_size_v<buffer_type>;
            } else if constexpr (is_fixed_size_v<array_type>) {
                return fixed_size_v<array_type>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    };

    template <typename U
        , typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct replace_element_type<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>, U
    >
    {
        using buffer_type = replace_element_type_t<buffer_t,U>;
        using type = object_t<buffer_type,shape_buffer_t,stride_buffer_t,offset_compute_t>;
    }; // replace_element_type

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct is_index_array<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        static constexpr auto value = [](){
            constexpr auto dim = len_v<shape_buffer_t>;
            return (dim == 1)
                && is_index_v<get_element_type_t<buffer_t>>
            ;
        }();
    }; // is_index_array

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct contiguous_axis<
        object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    > {
        using array_type  = object_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using offset_type = typename array_type::offset_type;
        static constexpr auto value = [](){
            if constexpr (is_row_major_offset_v<offset_type>) {
                return -1;
            } else if constexpr (is_column_major_offset_v<offset_type>) {
                return 0;
            } else {
                return error::CONTIGUOUS_AXIS_UNSUPPORTED<array_type>{};
            }
        }();
    };
} // namespace nmtools::meta

#endif // NMTOOLS_NDARRAY_ARRAY_HPP