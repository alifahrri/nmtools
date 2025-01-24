#ifndef NMTOOLS_ARRAY_KIND_HPP
#define NMTOOLS_ARRAY_KIND_HPP

namespace nmtools::array::kind
{
    /**
     * @brief helper tag for easy dispatch
     * 
     */
    struct fixed_t {};
    struct hybrid_t {};
    struct dynamic_t {};

    /**
     * @brief helper inline variable for each tag
     * 
     */
    inline constexpr auto fixed   = fixed_t {};
    inline constexpr auto hybrid  = hybrid_t {};
    inline constexpr auto dynamic = dynamic_t {};
} // namespace nmtools::array::kind

#endif // NMTOOLS_ARRAY_KIND_HPP

#ifndef NMTOOLS_ARRAY_UTILITY_CAST_HPP
#define NMTOOLS_ARRAY_UTILITY_CAST_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/apply_resize.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/core/flatten.hpp"
#include "nmtools/core/mutable_flatten.hpp"

#include "nmtools/utility/isequal.hpp"

namespace nmtools
{
    /**
     * @brief tag to resolve return type of cast op
     * 
     */
    struct cast_t {};

    struct cast_kind_t {};

    namespace meta::error
    {
        template <typename...>
        struct CAST_KIND_UNSUPPORTED : detail::fail_t {};
    }
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_CAST_HPP

#ifndef NMTOOLS_ARRAY_CAST_HPP
#define NMTOOLS_ARRAY_CAST_HPP

#include "nmtools/meta.hpp"

#include "nmtools/ndarray/ndarray.hpp"

#ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
#include "nmtools/ndarray/dynamic.hpp"
#endif
#include "nmtools/index/product.hpp"

#include "nmtools/utility/apply_resize.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/core/flatten.hpp"
#include "nmtools/core/mutable_flatten.hpp"

#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/tuple_cat.hpp"

#include "nmtools/utl.hpp"

namespace nmtools::array::kind
{
    // for testing purpose only
    struct nested_vector_t {};
    struct nested_array_t {};

    struct fixed_vec_t {};
    struct dynamic_vec_t {};

    // TODO: rename to vector, drop nested vector support
    inline constexpr auto nested_vec  = nested_vector_t {};
    inline constexpr auto nested_arr  = nested_array_t {};
    inline constexpr auto fixed_vec   = fixed_vec_t {};
    inline constexpr auto dynamic_vec = dynamic_vec_t {};

    // only support index for now
    struct static_vec_t {};
    inline constexpr auto static_vec = static_vec_t {};
} // namespace nmtools::array::kind

namespace nmtools
{
    namespace detail
    {
        template <typename element_t, typename return_t, typename array_t, typename size_type>
        constexpr auto cast_impl(return_t &ret, const array_t& a, size_type n) {
            for (size_t i=0; i<n; i++)
                at(ret,i) = static_cast<element_t>(at(a,i));
        } // cast_impl
    } // namespace detail
}

namespace nmtools
{
    namespace error
    {
        template <typename...>
        struct TESTING_DYNAMIC_ALLOCATION_DISABLED : meta::detail::fail_t {};
    };
    template <typename src_t, typename kind_t>
    struct meta::resolve_optype<
        void, cast_kind_t, src_t, const kind_t
    > : meta::resolve_optype<
        void, cast_kind_t, src_t, kind_t
    >  {};
    template <typename src_t, typename kind_t>
    struct meta::resolve_optype<
        void, cast_kind_t, src_t, kind_t&
    > : meta::resolve_optype<
        void, cast_kind_t, src_t, kind_t
    >  {};

    template <typename src_t, typename kind_t>
    struct meta::resolve_optype<
        void, cast_kind_t, src_t, kind_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (meta::is_fixed_size_ndarray_v<src_t> && meta::is_same_v<kind_t,array::kind::fixed_t>) {
                using element_t = get_element_type_t<src_t>;
                static_assert( !meta::is_void_v<element_t>, "internal error" );
                // start with arbitrary shaped fixed_ndarray, then resize with src
                using fixed_kind_t = array::fixed_ndarray<element_t,1>;
                using type = resize_fixed_ndarray_t<fixed_kind_t,src_t>;
                return meta::as_value_v<type>;
            }
            else if constexpr (meta::is_fixed_size_ndarray_v<src_t> && meta::is_same_v<kind_t,array::kind::hybrid_t>) {
                using element_t = get_element_type_t<src_t>;
                constexpr auto shape = fixed_ndarray_shape_v<src_t>;
                constexpr auto numel = index::product(shape);
                constexpr auto dim = fixed_ndarray_dim_v<src_t>;
                using type = array::hybrid_ndarray<element_t,numel,dim>;
                return as_value_v<type>;
            }
            else if constexpr (meta::is_fixed_size_ndarray_v<src_t> && meta::is_same_v<kind_t,array::kind::nested_array_t>) {
                using type = meta::transform_bounded_array_t<src_t>;
                return as_value_v<type>;
            }
            else if constexpr (meta::is_same_v<kind_t,array::kind::dynamic_t>) {
                using element_t [[maybe_unused]] = get_element_type_t<src_t>;
        #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
                using type = array::dynamic_ndarray<element_t>;
        #else
                using type = ::nmtools::error::TESTING_DYNAMIC_ALLOCATION_DISABLED<cast_kind_t,src_t,kind_t>;
        #endif // NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
                return meta::as_value_v<type>;
            }
            else if constexpr (meta::is_same_v<kind_t,array::kind::nested_vector_t>) {
                using element_t [[maybe_unused]] = get_element_type_t<src_t>;
                [[maybe_unused]] constexpr auto dim = fixed_dim_v<src_t>;
        #ifndef NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
                using type = meta::make_nested_dynamic_array_t<nmtools_list,element_t,dim>;
        #else
                using type = ::nmtools::error::TESTING_DYNAMIC_ALLOCATION_DISABLED<cast_kind_t,src_t,kind_t>;
        #endif // NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
                return as_value_v<type>;
            } else if constexpr (meta::is_same_v<kind_t,array::kind::static_vec_t>) {
                using element_t [[maybe_unused]] = get_element_type_t<src_t>;
                [[maybe_unused]] constexpr auto dim = fixed_dim_v<src_t>;
                if constexpr (dim != 1) {
                    return as_value_v<error::CAST_KIND_UNSUPPORTED<src_t,kind_t>>;
                } else {
                    constexpr auto length = len_v<src_t>;
                    using type = utl::static_vector<element_t,length>;
                    return as_value_v<type>;
                }
            } else /* */ {
                return as_value_v<error::CAST_KIND_UNSUPPORTED<src_t,kind_t>>;
            }
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // resolve_optype

    /**
     * @brief specialization for cast_t tag
     * 
     * @tparam dst_t destination type
     * @tparam src_t source type
     */
    template <typename dst_t, typename src_t>
    struct meta::resolve_optype<void,cast_t,dst_t,src_t>
    {
        using source_t = meta::transform_bounded_array_t<src_t>;
        static constexpr auto vtype = [](){
            if constexpr (meta::is_num_v<dst_t>) {
                using type = meta::replace_element_type_t<source_t,dst_t>;
                return meta::as_value_v<type>;
            } else {
                using type = dst_t;
                return meta::as_value_v<type>;
            }
        }();
        using type = meta::transform_bounded_array_t<meta::type_t<decltype(vtype)>>;
    }; // resolve_optype

    /**
     * @brief cast array of type srt_t to array of type dst_t
     * 
     * @tparam dst_t destination type
     * @tparam src_t source type
     * @param array array to be casted
     * @return constexpr auto 
     */
    template <typename dst_t, typename src_t>
    constexpr auto cast(const src_t& array)
    {
        static_assert (meta::is_ndarray_v<src_t> || meta::is_num_v<src_t>
            , "unsupported cast, expects source type to be ndarray or arithmetic"
        );
        static_assert (meta::is_ndarray_v<dst_t> || meta::is_num_v<dst_t>
            , "unsupported cast, expects destination type to be ndarray or arithmetic"
        );
        static_assert ((meta::is_num_v<src_t> == meta::is_num_v<dst_t>) || (meta::is_ndarray_v<src_t>)
            , "unsupported cast, expects destination type to be arithmetic when source type is arithmetic"
        );

        if constexpr (meta::is_num_v<src_t> && meta::is_num_v<dst_t>)
            return static_cast<dst_t>(array);
        else {
            using detail::cast_impl;
            using return_t = meta::resolve_optype_t<cast_t,dst_t,src_t>;

            auto ret = return_t{};
            if constexpr (meta::is_resizable_v<return_t>) {
                auto shape = ::nmtools::shape<true>(array);
                ret = detail::apply_resize(ret, shape);
            }
            else if constexpr (meta::is_fixed_size_ndarray_v<return_t> && meta::is_fixed_size_ndarray_v<src_t>) {
                constexpr auto src_shape = meta::fixed_ndarray_shape_v<src_t>;
                constexpr auto dst_shape = meta::fixed_ndarray_shape_v<return_t>;
                static_assert (utils::isequal(src_shape,dst_shape)
                    , "unsupported cast, mismatched shape for cast"
                );
            }
            using element_t = meta::get_element_type_t<return_t>;
            auto ret_view = unwrap(view::mutable_flatten(ret));
            auto arr_view = unwrap(view::flatten(array));
            auto n = len(arr_view);
            cast_impl<element_t>(ret_view,arr_view,n);
            return ret;
        }
    } // cast

    /**
     * @brief Overloaded version of cast that accept type as second params.
     * 
     * @tparam src_t source array type
     * @tparam dst_t desired array type
     * @param array source array
     * @return constexpr auto 
     */
    template <typename src_t, typename dst_t>
    constexpr auto cast(const src_t& array, const meta::as_value<dst_t>)
    {
        // assume dst_t is default-constructible
        auto ret = dst_t{};
        if constexpr (meta::is_resizable_v<dst_t>) {
            detail::apply_resize(ret, ::nmtools::shape(array));
        }
        auto ret_view = unwrap(view::mutable_flatten(ret));
        auto arr_view = unwrap(view::flatten(array));
        auto n = len(arr_view);

        for (size_t i=0; i<n; i++) {
            at(ret_view,i) = at(arr_view,i);
        }

        return ret;
    }
} // namespace nmtools

namespace nmtools
{
    template <typename src_t, typename kind_t>
    constexpr auto cast(const src_t& src, const kind_t&)
    {
        using ret_t = meta::resolve_optype_t<cast_kind_t,src_t,kind_t>;
        return cast(src, meta::as_value_v<ret_t>);
    } // cast

    template <typename T>
    constexpr auto to_clipped(const T&)
    {
        if constexpr (meta::is_constant_index_v<T>) {
            constexpr auto I = T::value;
            constexpr auto MAX = (I > 0 ? I : 1);
            if constexpr (I<0) {
                return clipped_int64_t<I,MAX>(I);
            } else {
                return clipped_size_t<MAX>(I);
            }
        } else {
            constexpr auto array = meta::to_value_v<T>;
            constexpr auto N = meta::len_v<T>;
            return meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto I = at(array,index);
                constexpr auto vtype = [](){
                    constexpr auto MAX = (I > 0 ? I : 1);
                    if constexpr (I<0) {
                        return meta::as_value_v<clipped_int64_t<I,MAX>>;
                    } else {
                        return meta::as_value_v<clipped_size_t<MAX>>;
                    }
                }();
                using type = meta::type_t<decltype(vtype)>;
                return utility::tuple_append(init,type(I));
            }, nmtools_tuple<>{});
        }
    }

    template <typename T, auto N, template<typename,auto>typename array_t>
    constexpr auto to_list(const array_t<T,N>& array)
    {
        auto res = nmtools_list<T>{};
        res.resize(N);
        for (size_t i=0; i<N; i++) {
            res.at(i) = array.at(i);
        }
        return res;
    }
} // namespace nmtools

#endif // NMTOOLS_ARRAY_CAST_HPP