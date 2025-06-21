#ifndef NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP
#define NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP

#include "nmtools/index/product.hpp"
#include "nmtools/index/pack.hpp"
#include "nmtools/index/compute_strides.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/reverse.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/at.hpp"
// NOTE: to include nmtools_hybrid_ndarray macro
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/utility/get.hpp"
#include "nmtools/ndarray/base_ndarray.hpp"

// experimental version that combine all three to single class

namespace nmtools
{
    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t=resolve_stride_type_t
        , template <typename...>typename compute_offset_t=row_major_offset_t
        , typename=void>
    struct ndarray_t : base_ndarray_t<ndarray_t<buffer_t, shape_buffer_t, stride_buffer_t, compute_offset_t>>
    {
        using buffer_type = buffer_t;
        using value_type  = meta::get_element_type_t<buffer_type>;
        using shape_type  = shape_buffer_t;
        using index_type  = meta::get_element_or_common_type_t<shape_type>;
        using stride_type = stride_buffer_t<shape_type>;
        using base_type   = base_ndarray_t<ndarray_t>;
        using offset_type = compute_offset_t<shape_type,stride_type>;

        static_assert( meta::is_index_array_v<shape_type>, "unsupported shape_type for ndarray" );
        static_assert( meta::is_index_array_v<stride_type>, "unsupported stride_type for ndarray");

        buffer_type data_;
        shape_type  shape_;
        stride_type strides_;
        offset_type offset_;

        constexpr ndarray_t()
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
    }; // ndarray_t

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t=resolve_stride_type_t
    >
    using column_major_ndarray_t = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,column_major_offset_t>;

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t=resolve_stride_type_t
    >
    using row_major_ndarray_t = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,row_major_offset_t>;

    template <typename type, size_t max_size>
    using static_vector_ndarray_t = ndarray_t<nmtools_array<type,max_size>,nmtools_array<size_t,1>>;
} // namespace nmtools

namespace nmtools
{
    template <size_t I,
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct get_t<I,ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>>
    {
        using array_type = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;

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
    struct get_element_type<ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>>
    {
        using array_type = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
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
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using element_type = typename array_type::value_type;
        static constexpr auto value = is_num_v<element_type>;
    }; // is_ndarray

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_dim<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
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

    // TODO: remove
    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_ndarray_shape<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct fixed_shape<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
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
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
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
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
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
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
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

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto...new_shape>
    struct resize_shape<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , as_type<new_shape...>
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        using new_shape_type = nmtools_tuple<ct<new_shape>...>;

        // TODO: check if buffer type is sufficient
        using type = ndarray_t<buffer_t,new_shape_type,resolve_stride_type_t,offset_compute_t>;
    };

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto new_size>
    struct resize_dim<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , new_size
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;
        using index_type  = typename array_type::index_type;

        using new_shape_type = nmtools_array<index_type,new_size>;

        using type = ndarray_t<buffer_t,new_shape_type,resolve_stride_type_t,offset_compute_t>;
    };

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto new_size>
    struct resize_size<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , new_size
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;
        using value_type  = typename array_type::value_type;

        using new_buffer_type = nmtools_array<value_type,new_size>;

        // TODO: check if shape type is sufficient
        using type = ndarray_t<new_buffer_type,shape_buffer_t,stride_buffer_t,offset_compute_t>;
    };

    namespace error
    {
        template<typename...>
        struct RESIZE_BOUNDED_SIZE_INVALID_SIZE : detail::fail_t {};
    } // namespace error
    

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto new_size>
    struct resize_bounded_size<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , new_size
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;
        using value_type  = typename array_type::value_type;

        using new_buffer_t = nmtools_array<value_type,new_size>;

        using new_hybrid_buffer_t = nmtools_hybrid_ndarray<value_type,new_size,1>;

        static constexpr auto vtype = [](){
            // TODO: consider to replace buffer's size instead of using new_buffer_type, so no need inner brach for is_fixed_size_v
            using hybrid_type [[maybe_unused]] = ndarray_t<new_hybrid_buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
            using fixed_type [[maybe_unused]]  = ndarray_t<new_buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
            if constexpr (is_bounded_size_v<buffer_type> && is_constant_index_array_v<shape_type>) {
                constexpr auto product = index::product(shape_type{});
                if constexpr ((new_size >= product) && is_fixed_size_v<buffer_type>) {
                    return as_value_v<fixed_type>;
                } else if constexpr (new_size >= product) {
                    return as_value_v<hybrid_type>;
                } else {
                    return as_value_v<error::RESIZE_BOUNDED_SIZE_INVALID_SIZE<array_type>>;
                }
            } else if constexpr (is_bounded_size_v<buffer_type>) {
                if constexpr (is_fixed_size_v<buffer_type>) {
                    return as_value_v<fixed_type>;
                } else {
                    return as_value_v<hybrid_type>;
                }
            } else {
                using error_type = error::RESIZE_BOUNDED_SIZE_UNSUPPORTED<array_type>;
                return as_value_v<error_type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // resize_bounded_size

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t
        , auto new_dim>
    struct resize_bounded_dim<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
        , new_dim
    >
    {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;
        using index_type  = typename array_type::index_type;

        using new_shape_t = nmtools_hybrid_ndarray<index_type,new_dim,1>;

        using new_fixed_t = nmtools_array<index_type,new_dim>;

        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                using error_type = error::RESIZE_BOUNDED_DIM_UNSUPPORTED<array_type>;
                return as_value_v<error_type>;
            } else if constexpr (is_fixed_size_v<shape_type>) {
                using type = ndarray_t<buffer_t,new_fixed_t,resolve_stride_type_t,offset_compute_t>;
                return as_value_v<type>;
            } else if constexpr (is_bounded_size_v<shape_type>) {
                using type = ndarray_t<buffer_t,new_shape_t,resolve_stride_type_t,offset_compute_t>;
                return as_value_v<type>;
            } else {
                using error_type = error::RESIZE_BOUNDED_DIM_UNSUPPORTED<array_type>;
                return as_value_v<error_type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // resize_bounded_dim

    template <typename U
        , typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct replace_element_type<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>, U
    >
    {
        using buffer_type = replace_element_type_t<buffer_t,U>;
        using type = ndarray_t<buffer_type,shape_buffer_t,stride_buffer_t,offset_compute_t>;
    }; // replace_element_type

    template <
          typename buffer_t
        , typename shape_buffer_t
        , template <typename...>typename stride_buffer_t
        , template <typename...>typename offset_compute_t>
    struct is_index_array<
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
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
        ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>
    > {
        using array_type  = ndarray_t<buffer_t,shape_buffer_t,stride_buffer_t,offset_compute_t>;
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

// casting
#include "nmtools/utility/cast.hpp"

#ifndef NMTOOLS_CAST_DEFAULT_CLIPPED_VALUE
#define NMTOOLS_CAST_DEFAULT_CLIPPED_VALUE (6)
#endif // NMTOOLS_CAST_DEFAULT_CLIPPED_VALUE

namespace nmtools::kind
{
    enum class BufferKind {
        CONSTANT, // useful for shape, but should not used for buffer
        FIXED,
        DYNAMIC,
        HYBRID,
        CLIPPED, // useful for shape, but should not used for buffer
    };

    template <BufferKind Shape, BufferKind Buffer, typename...>
    struct ndarray_kind_t {};

    constexpr inline auto ndarray_cs_fb = ndarray_kind_t< BufferKind::CONSTANT, BufferKind::FIXED >{};
    constexpr inline auto ndarray_cs_hb = ndarray_kind_t< BufferKind::CONSTANT, BufferKind::HYBRID >{};
    constexpr inline auto ndarray_cs_db = ndarray_kind_t< BufferKind::CONSTANT, BufferKind::DYNAMIC >{};
    constexpr inline auto ndarray_fs_fb = ndarray_kind_t< BufferKind::FIXED,    BufferKind::FIXED >{};
    constexpr inline auto ndarray_fs_hb = ndarray_kind_t< BufferKind::FIXED,    BufferKind::HYBRID >{};
    constexpr inline auto ndarray_fs_db = ndarray_kind_t< BufferKind::FIXED,    BufferKind::DYNAMIC >{};
    constexpr inline auto ndarray_hs_fb = ndarray_kind_t< BufferKind::HYBRID,   BufferKind::FIXED >{};
    constexpr inline auto ndarray_hs_hb = ndarray_kind_t< BufferKind::HYBRID,   BufferKind::HYBRID >{};
    constexpr inline auto ndarray_hs_db = ndarray_kind_t< BufferKind::HYBRID,   BufferKind::DYNAMIC >{};
    constexpr inline auto ndarray_ds_fb = ndarray_kind_t< BufferKind::DYNAMIC,  BufferKind::FIXED >{};
    constexpr inline auto ndarray_ds_hb = ndarray_kind_t< BufferKind::DYNAMIC,  BufferKind::HYBRID >{};
    constexpr inline auto ndarray_ds_db = ndarray_kind_t< BufferKind::DYNAMIC,  BufferKind::DYNAMIC >{};
    // clipped shape
    constexpr inline auto ndarray_ls_fb = ndarray_kind_t< BufferKind::CLIPPED, BufferKind::FIXED, meta::ct<NMTOOLS_CAST_DEFAULT_CLIPPED_VALUE> >{};
    constexpr inline auto ndarray_ls_hb = ndarray_kind_t< BufferKind::CLIPPED, BufferKind::HYBRID, meta::ct<NMTOOLS_CAST_DEFAULT_CLIPPED_VALUE> >{};
    constexpr inline auto ndarray_ls_db = ndarray_kind_t< BufferKind::CLIPPED, BufferKind::DYNAMIC, meta::ct<NMTOOLS_CAST_DEFAULT_CLIPPED_VALUE> >{};
}

namespace nmtools::meta
{
    using kind::BufferKind;

    namespace error
    {
        template <typename...>
        struct CAST_NDARRAY_KIND_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_t, BufferKind ShapeKind, BufferKind SizeKind, typename...Args>
    struct resolve_optype<void, cast_kind_t, src_t, kind::ndarray_kind_t<ShapeKind,SizeKind,Args...>>
    {
        static constexpr auto vtype = [](){
            using element_type = get_element_type_t<src_t>;
            using error_type [[maybe_unused]] = error::CAST_NDARRAY_KIND_UNSUPPORTED<src_t,kind::ndarray_kind_t<ShapeKind,SizeKind,Args...>>;
            constexpr auto shape  = fixed_shape_v<src_t>;
            constexpr auto dim    = fixed_dim_v<src_t>;
            constexpr auto size   = fixed_size_v<src_t>;
            constexpr auto b_dim  = bounded_dim_v<src_t>;
            constexpr auto b_size = bounded_size_v<src_t>;
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
                        return as_value_v<append_type_t<init_type,ct<at(shape,decltype(index)::value+1)>>>;
                    }, as_value_v<nmtools_tuple<ct<at(shape,0)>>>);
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
                    using type = static_vector<size_t,b_dim>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // clipped shape
            constexpr auto cl_shape_vtype = [&](){
                if constexpr (!is_fail_v<shape_type>) {
                    return template_reduce<len(shape)-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        return as_value_v<append_type_t<init_type,clipped_size_t<at(shape,decltype(index)::value+1)>>>;
                    }, as_value_v<nmtools_tuple<clipped_size_t<at(shape,0)>>>);
                } else if constexpr (!is_fail_v<dim_type>) {
                    using args_list = type_list<Args...>;
                    using max_t = at_t<args_list,0>;
                    constexpr auto max = max_t::value;
                    using type = nmtools_array<clipped_size_t<max>,dim>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<b_dim_type>) {
                    using args_list = type_list<Args...>;
                    using max_t = at_t<args_list,0>;
                    constexpr auto max = max_t::value;
                    using type = static_vector<clipped_size_t<max>,b_dim>;
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
                if constexpr (!is_fail_v<b_size_type>) {
                    using type = static_vector<element_type,b_size>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // dynamic buffer

            using c_shape_type  [[maybe_unused]] = type_t<decltype(c_shape_vtype)>;
            using f_shape_type  [[maybe_unused]] = type_t<decltype(f_shape_vtype)>;
            using b_shape_type  [[maybe_unused]] = type_t<decltype(b_shape_vtype)>;
            using cl_shape_type [[maybe_unused]] = type_t<decltype(cl_shape_vtype)>;
            using f_buffer_type [[maybe_unused]] = type_t<decltype(f_buffer_vtype)>;
            using b_buffer_type [[maybe_unused]] = type_t<decltype(b_buffer_vtype)>;
            using d_buffer_type [[maybe_unused]] = nmtools_list<element_type>;
            using d_shape_type  [[maybe_unused]] = nmtools_list<size_t>;

            if constexpr (
                    (ShapeKind == BufferKind::CONSTANT)
                &&  (SizeKind  == BufferKind::FIXED) // buffer can't be constant
                && !(is_fail_v<c_shape_type>)
                && !(is_fail_v<f_buffer_type>)
            ) {
                using type = ndarray_t<f_buffer_type,c_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::CONSTANT)
                &&  (SizeKind  == BufferKind::HYBRID)
                && !(is_fail_v<c_shape_type>)
                && !(is_fail_v<b_buffer_type>)
            ) {
                using type = ndarray_t<b_buffer_type,c_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::CONSTANT)
                &&  (SizeKind  == BufferKind::DYNAMIC)
                && !(is_fail_v<c_shape_type>)
                && !(is_fail_v<d_buffer_type>)
            ) {
                using type = ndarray_t<d_buffer_type,c_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::FIXED)
                &&  (SizeKind  == BufferKind::FIXED)
                && !(is_fail_v<f_shape_type>)
                && !(is_fail_v<f_buffer_type>)
            ) {
                using type = ndarray_t<f_buffer_type,f_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::FIXED)
                &&  (SizeKind  == BufferKind::HYBRID)
                && !(is_fail_v<f_shape_type>)
                && !(is_fail_v<b_buffer_type>)
            ) {
                using type = ndarray_t<b_buffer_type,f_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::FIXED)
                &&  (SizeKind  == BufferKind::DYNAMIC)
                && !(is_fail_v<f_shape_type>)
                && !(is_fail_v<d_buffer_type>)
            ) {
                using type = ndarray_t<d_buffer_type,f_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::HYBRID)
                &&  (SizeKind  == BufferKind::FIXED)
                && !(is_fail_v<b_shape_type>)
                && !(is_fail_v<f_buffer_type>)
            ) {
                using type = ndarray_t<f_buffer_type,b_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::HYBRID)
                &&  (SizeKind  == BufferKind::HYBRID)
                && !(is_fail_v<b_shape_type>)
                && !(is_fail_v<b_buffer_type>)
            ) {
                using type = ndarray_t<b_buffer_type,b_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::HYBRID)
                &&  (SizeKind  == BufferKind::DYNAMIC)
                && !(is_fail_v<b_shape_type>)
                && !(is_fail_v<d_buffer_type>)
            ) {
                using type = ndarray_t<d_buffer_type,b_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::DYNAMIC)
                &&  (SizeKind  == BufferKind::FIXED)
                && !(is_fail_v<d_shape_type>)
                && !(is_fail_v<f_buffer_type>)
            ) {
                using type = ndarray_t<f_buffer_type,d_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::DYNAMIC)
                &&  (SizeKind  == BufferKind::HYBRID)
                && !(is_fail_v<d_shape_type>)
                && !(is_fail_v<b_buffer_type>)
            ) {
                using type = ndarray_t<b_buffer_type,d_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                    (ShapeKind == BufferKind::DYNAMIC)
                &&  (SizeKind  == BufferKind::DYNAMIC)
                && !(is_fail_v<d_shape_type>)
                && !(is_fail_v<d_buffer_type>)
            ) {
                using type = ndarray_t<d_buffer_type,d_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                   (ShapeKind == BufferKind::CLIPPED)
                && (SizeKind == BufferKind::FIXED)
                && !(is_fail_v<cl_shape_type>)
                && !(is_fail_v<f_buffer_type>)
            ) {
                using type = ndarray_t<f_buffer_type,cl_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                   (ShapeKind == BufferKind::CLIPPED)
                && (SizeKind == BufferKind::HYBRID)
                && !(is_fail_v<cl_shape_type>)
                && !(is_fail_v<b_buffer_type>)
            ) {
                using type = ndarray_t<b_buffer_type,cl_shape_type>;
                return as_value_v<type>;
            } else if constexpr (
                   (ShapeKind == BufferKind::CLIPPED)
                && (SizeKind == BufferKind::DYNAMIC)
                && !(is_fail_v<cl_shape_type>)
                && !(is_fail_v<d_buffer_type>)
            ) {
                using type = ndarray_t<d_buffer_type,cl_shape_type>;
                return as_value_v<type>;
            } else {
                return as_value_v<error_type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_NDARRAY_NDARRAY_HPP