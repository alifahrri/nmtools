#ifndef NMTOOLS_ARRAY_INDEX_MATMUL_HPP
#define NMTOOLS_ARRAY_INDEX_MATMUL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/split.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    // special tag to resolve shape_matmul return type
    struct shape_matmul_t {};

    /**
     * @brief Computes the resulting shape of matmul, following numpy rules.
     * 
     * @tparam lhs_shape_t 
     * @tparam rhs_shape_t 
     * @param ashape        lhs shape
     * @param bshape        rhs shape
     * @return constexpr auto 
     */
    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto shape_matmul(const lhs_shape_t& ashape, const rhs_shape_t& bshape)
    {
        using result_t = meta::resolve_optype_t<shape_matmul_t,lhs_shape_t,rhs_shape_t>;

        if constexpr (meta::is_constant_index_array_v<result_t> || is_none_v<result_t>) {
            return result_t {};
        } else {
            using return_t = nmtools_maybe<result_t>;

            auto adim = (nm_size_t)len(ashape);
            auto bdim = (nm_size_t)len(bshape);

            auto shape_1 = at(ashape,-1);
            auto shape_2 = bdim == 1 ? at(bshape,0) : at(bshape,-2);
            auto valid_shape = (nm_size_t)shape_1 == (nm_size_t)shape_2;

            auto max_dim = adim > bdim ? adim : bdim;
            auto dst_dim = (adim == 1 || bdim == 1) ? max_dim - 1 : max_dim;

            // check matrix shape
            // broadcast shape, if possible
            auto asplit_axis = adim == 1 ? -1 : -2;
            auto bsplit_axis = bdim == 1 ? -1 : -2;
            const auto [bcast_ashape, mat_ashape] = split(ashape,asplit_axis);
            const auto [bcast_bshape, mat_bshape] = split(bshape,bsplit_axis);
            const auto broadcast_result = index::broadcast_shape(bcast_ashape,bcast_bshape);

            valid_shape = valid_shape && has_value(broadcast_result);

            if (valid_shape) {
                const auto& b_shape = *broadcast_result;
                auto result = result_t{};
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }
                nm_size_t i = 0;
                auto bcast_dim = dst_dim - 2;
                if (adim >= 2 && bdim == 1) {
                    for (; (nm_index_t)i<(nm_index_t)adim-1; i++) {
                        at(result,i) = at(ashape,i);
                    }
                } else if (bdim >= 2 && adim == 1) {
                    nm_size_t idx = 0;
                    for (nm_size_t i=0; i<(nm_size_t)bdim; i++) {
                        if (i==(bdim-2)) {
                            continue;
                        }
                        at(result,idx) = at(bshape,i);
                        idx++;
                    }
                } else {
                    for (; (nm_index_t)i<(nm_index_t)bcast_dim; i++) {
                        at(result,i) = at(b_shape,i);
                    }
                }
                if (bdim >= 2 && adim > 1) {
                    at(result,-1) = at(bshape,-1);
                }
                if (adim >= 2 && bdim > 1) {
                    at(result,-2) = at(ashape,-2);
                }
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        }
    } // shape_matmul

    struct matmul_t {};

    /**
     * @brief Computes the left and right indices for corresponding original array given
     * the resulting matmul indices, src (original) shape, and dst (matmul) shape.
     * 
     * The indices are expected to be used by apply_slice.
     * 
     * @tparam indices_t 
     * @tparam left_shape_t 
     * @tparam right_shape_t 
     * @tparam shape_t 
     * @param indices indices from dst (matmul) shape
     * @param lshape  shape from src (original) left operands
     * @param rshape  shape from src (original) right operands
     * @param shape   resulting matmul shape (from shape_matmul)
     * @return constexpr auto slicing args for left and right operands
     */
    template <typename indices_t, typename left_shape_t, typename right_shape_t, typename shape_t>
    constexpr auto matmul(const indices_t& indices, const left_shape_t& lshape, const right_shape_t& rshape, const shape_t& shape)
    {
        // TODO: properly resolve type

        using result_pack_t = meta::resolve_optype_t<matmul_t,indices_t,left_shape_t,right_shape_t,shape_t>;
        using left_slice_t  = meta::at_t<result_pack_t,0>;
        using right_slice_t = meta::at_t<result_pack_t,1>;

        [[maybe_unused]] const auto row = at(indices,meta::ct_v<-2>);
        [[maybe_unused]] const auto col = at(indices,meta::ct_v<-1>);

        [[maybe_unused]] const auto all = nmtools_tuple{none_t{},none_t{}};

        // TODO: return if result_t is compile-time value

        // matmul slices
        // for example left  -> [?,::]
        //             right -> [::,?]

        // active col/row slices
        // for example left  -> [i_{-2},::]
        //             right -> [::,i_{-1}]

        auto matmul_dim = len(shape);
        auto fill_non_matmul_index = [&](auto& slices, auto i, const auto& src_shape){
            auto offset = matmul_dim - len(src_shape);
            auto si = at(src_shape,i);
            at(slices,i) = (si == 1 ? 0 : at(indices,i+offset));
        };
        auto fill_non_matmul_indices = [&](auto& slices, const auto& src_shape){
            // NOTE: use len, to handle tuple properly, assume 0 is dynamic size
            constexpr auto LEN = meta::len_v<decltype(slices)>;
            if constexpr (LEN == 0) {
                auto dim = len(src_shape);
                // fill non-matmul axes
                for (nm_size_t i=0; (dim > 2) && (i<(dim-2)); i++) {
                    // broadcasted indices can only same or 1
                    fill_non_matmul_index(slices,i,src_shape);
                }
            } else {
                meta::template_for<LEN-2>([&](auto index){
                    fill_non_matmul_index(slices,index,src_shape);
                });
            }
        };

        auto l_slices = [&](){
            auto l_slices = left_slice_t{};
            [[maybe_unused]] auto l_dim = len(lshape);
            if constexpr (meta::is_resizable_v<left_slice_t>) {
                // at this point the value type should be either type
                l_slices.resize(l_dim);
            }

            at(l_slices,meta::ct_v<-1>) = all;
            at(l_slices,meta::ct_v<-2>) = at(indices,meta::ct_v<-2>);

            fill_non_matmul_indices(l_slices,lshape);

            return l_slices;
        }();

        auto r_slices = [&](){
            auto r_slices = right_slice_t{};
            [[maybe_unused]] auto r_dim = len(rshape);
            if constexpr (meta::is_resizable_v<right_slice_t>) {
                r_slices.resize(r_dim);
            }

            at(r_slices,meta::ct_v<-2>) = all;
            at(r_slices,meta::ct_v<-1>) = at(indices,meta::ct_v<-1>);

            fill_non_matmul_indices(r_slices,rshape);

            return r_slices;
        }();

        return nmtools_tuple{l_slices,r_slices};
    } // matmul
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_MATMUL_ERROR : detail::fail_t {};

        template <typename...>
        struct SHAPE_MATMUL_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct MATMUL_ERROR : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief Resolve return type for shape_matmul
     * 
     * @tparam lhs_shape_t 
     * @tparam rhs_shape_t 
     */
    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype< void, index::shape_matmul_t, lhs_shape_t, rhs_shape_t >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_shape_t> || !is_index_array_v<rhs_shape_t>) {
                using type = error::SHAPE_MATMUL_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<lhs_shape_t> && is_constant_index_array_v<rhs_shape_t>) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::shape_matmul(lhs_shape,rhs_shape);
                if constexpr (is_none_v<decltype(result)>) {
                    using type = none_t;
                    return as_value_v<type>;
                } else if constexpr (has_value(result)) {
                    using nmtools::len, nmtools::at;
                    return template_reduce<len(unwrap(result))-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        using type = append_type_t<init_type,ct<at(unwrap(result),index+1)>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<ct<at(unwrap(result),0)>>>);
                } else {
                    using type = error::SHAPE_MATMUL_ERROR<lhs_shape_t,rhs_shape_t>;
                    return as_value_v<type>;
                }
            } else {
                constexpr auto LHS_DIM = len_v<lhs_shape_t>;
                constexpr auto RHS_DIM = len_v<rhs_shape_t>;
                [[maybe_unused]] constexpr auto LHS_B_DIM = bounded_size_v<lhs_shape_t>;
                [[maybe_unused]] constexpr auto RHS_B_DIM = bounded_size_v<rhs_shape_t>;
                if constexpr ((LHS_DIM > 0) && (RHS_DIM > 0)) {
                    constexpr auto MAX_DIM = (LHS_DIM > RHS_DIM) ? LHS_DIM : RHS_DIM;
                    if constexpr ((LHS_DIM == 1) || (RHS_B_DIM == 1)) {
                        constexpr auto DST_DIM = MAX_DIM - 1;
                        if constexpr (DST_DIM >= 1) {
                            using type = nmtools_array<nm_size_t,DST_DIM>;
                            return as_value_v<type>;
                        } else {
                            // 1-dim x 1-dim matmul results in scalar
                            using type = none_t;
                            return as_value_v<type>;
                        }
                    } else {
                        using type = nmtools_array<nm_size_t,MAX_DIM>;
                        return as_value_v<type>;   
                    }
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)> && !is_fail_v<decltype(RHS_B_DIM)>) {
                    constexpr auto MAX_DIM = (LHS_B_DIM > RHS_B_DIM ? LHS_B_DIM : RHS_B_DIM);
                    using type = array::static_vector<nm_size_t,MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    #if 1
    template <typename indices_t, typename left_shape_t, typename right_shape_t, typename shape_t>
    struct resolve_optype<
        void, index::matmul_t, indices_t, left_shape_t, right_shape_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            using index_t = get_index_element_type_t<shape_t>;
            using all_t [[maybe_unused]]   = nmtools_tuple<none_t,none_t>;
            using slice_t [[maybe_unused]] = nmtools_either<index_t,all_t>;
            constexpr auto slice_vtype = [](auto shape_vtype, [[maybe_unused]] auto f_init_vtype){
                using m_shape_t = type_t<decltype(shape_vtype)>;
                constexpr auto f_size = len_v<m_shape_t>;
                [[maybe_unused]] constexpr auto b_size = bounded_size_v<m_shape_t>;
                if constexpr (f_size > 0) {
                    using i_slice_t  = type_t<decltype(f_init_vtype)>;
                    return meta::template_reduce<f_size-2>([](auto init, auto){
                        using concatenated = concat_type_t<nmtools_tuple<index_t>,type_t<decltype(init)>>;
                        return as_value_v<concatenated>;
                    }, as_value_v<i_slice_t>);
                } else if constexpr (!is_fail_v<decltype(b_size)>) {
                    using m_slice_t = replace_value_type_t<m_shape_t,slice_t>;
                    return as_value_v<resize_bounded_size_t<m_slice_t,b_size>>;
                } else {
                    // assume m_shape_t is index array
                    using m_slice_t = replace_value_type_t<m_shape_t,slice_t>;
                    return as_value_v<m_slice_t>;
                }
            };
            constexpr auto left_slice_vtype  = slice_vtype(as_value_v<left_shape_t>,as_value_v<nmtools_tuple<index_t,all_t>>);
            constexpr auto right_slice_vtype = slice_vtype(as_value_v<right_shape_t>,as_value_v<nmtools_tuple<all_t,index_t>>);
            using left_slice_t [[maybe_unused]]  = type_t<decltype(left_slice_vtype)>;
            using right_slice_t [[maybe_unused]] = type_t<decltype(right_slice_vtype)>;

            // TODO: check indices/left/right/shape size compatibility
            // e.g. len(indices) >= {len(left),len(right)}; len(indices) == len(shape); ...
            // assume index array
            if constexpr (
                is_index_array_v<indices_t>
                && is_index_array_v<left_shape_t>
                && is_index_array_v<right_shape_t>
                && is_index_array_v<shape_t>
            ) {
                using slices_t = nmtools_tuple<left_slice_t,right_slice_t>;
                return as_value_v<slices_t>;
            } else {
                return as_value_v<error::MATMUL_ERROR<indices_t,left_shape_t,right_shape_t,shape_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
    #endif
}

#endif // NMTOOLS_ARRAY_INDEX_MATMUL_HPP

#ifndef NMTOOLS_ARRAY_VIEW_MATMUL_HPP
#define NMTOOLS_ARRAY_VIEW_MATMUL_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/has_value.hpp"

namespace nmtools::view
{
    /**
     * @brief Matmul view type constructor.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct matmul_t
    {
        using operands_type = decltype(pack_operands(meta::declval<lhs_t>(),meta::declval<rhs_t>()));
        using array_type    = operands_type;
        using lhs_elem_type = meta::get_element_type_t<lhs_t>;
        using rhs_elem_type = meta::get_element_type_t<rhs_t>;
        using result_type   = meta::common_type_t<lhs_elem_type,rhs_elem_type>;
        using lhs_shape_type = decltype(nmtools::shape<true>(meta::declval<lhs_t>()));
        using rhs_shape_type = decltype(nmtools::shape<true>(meta::declval<rhs_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_matmul_t,lhs_shape_type,rhs_shape_type>;

        operands_type array;
        dst_shape_type shape_;

        constexpr matmul_t(const lhs_t& lhs, const rhs_t& rhs)
            : array(pack_operands(lhs,rhs))
            , shape_(unwrap(index::shape_matmul(
                nmtools::shape<true>(lhs),
                nmtools::shape<true>(rhs))
            ))
        {}

        constexpr auto operands() const noexcept
        {
            return array_type{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto view_at(const size_types&...indices) const
        {
            const auto& lhs = nmtools::get<0>(array);
            const auto& rhs = nmtools::get<1>(array);
            using lhs_type  = meta::remove_cvref_t<decltype(lhs)>;
            using rhs_type  = meta::remove_cvref_t<decltype(rhs)>;

            const auto packed_indices = pack_indices(indices...);
            const auto ashape   = detail::shape(lhs);
            const auto bshape   = detail::shape(rhs);
            auto indices_       = index::matmul(packed_indices,ashape,bshape,shape());
            auto l_slice_indices = at(indices_,meta::ct_v<0>);
            auto r_slice_indices = at(indices_,meta::ct_v<1>);

            auto l_slice = [&](){
                if constexpr (meta::is_pointer_v<lhs_type>) {
                    return apply_slice(*lhs, l_slice_indices);
                } else {
                    return apply_slice(lhs, l_slice_indices);
                }
            }();
            auto r_slice = [&](){
                if constexpr (meta::is_pointer_v<rhs_type>) {
                    return apply_slice(*rhs, r_slice_indices);
                } else {
                    return apply_slice(rhs, r_slice_indices);
                }
            }();
            // element multiplication with broadcasting
            auto multiplied = multiply(l_slice,r_slice);
            auto reduced    = reduce_add(multiplied,/*axis=*/None);
            return unwrap(reduced);
        } // view_at

        template <typename...size_types>
        constexpr auto operator()(const size_types&...indices) const
        {
            auto reduced = view_at(indices...);
            // reduced must be num type
            // the return must be result_type
            return static_cast<result_type>(reduced);
        } // operator()
    }; // matmul_t

    /**
     * @brief Create a view representing matrix product of two arrays.
     * 
     * This view should behave like numpy's matmul,
     * The axis -2..0 are broadcasted.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename lhs_t, typename rhs_t>
    constexpr auto matmul(const lhs_t& lhs, const rhs_t& rhs)
    {
        if constexpr (meta::is_maybe_v<lhs_t> || meta::is_maybe_v<rhs_t>) {
            using result_t = decltype(matmul(unwrap(lhs),unwrap(rhs)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(lhs) && has_value(rhs)
                ? return_t{matmul(unwrap(lhs),unwrap(rhs))}
                : return_t{meta::Nothing}
            );
        } else {
            // TODO: support ufunc datatype promotions
            using view_t = decorator_t<matmul_t, lhs_t, rhs_t>;
            return view_t{{lhs,rhs}};
        }
    } // matmul
} // nmtools::view

namespace nmtools::meta
{

    /**
     * @brief Infer return type of matmul
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct get_element_type<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        using type = typename view::matmul_t<lhs_t,rhs_t>::result_type;
    }; // get_element_type

    template <typename lhs_t, typename rhs_t>
    struct is_ndarray<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        using view_type = view::matmul_t<lhs_t, rhs_t>;
        using dst_shape_type = typename view_type::dst_shape_type;
        static constexpr auto value = is_ndarray_v<lhs_t> && is_ndarray_v<rhs_t> && is_index_array_v<dst_shape_type>;
    }; // is_ndarray

    /**
     * @brief Infer the maximum size of the resulting matmul, at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct bounded_size<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_bounded_size_v<lhs_t> && is_bounded_size_v<rhs_t>) {
                // worst case maximum value
                return bounded_size_v<lhs_t> * bounded_size_v<rhs_t>;
            } else if constexpr (is_fixed_shape_v<lhs_t> && is_bounded_size_v<rhs_t>) {
                constexpr auto shape = fixed_shape_v<lhs_t>;
                return index::product(shape) * bounded_size_v<rhs_t>;
            } else if constexpr (is_bounded_size_v<lhs_t> && is_fixed_shape_v<rhs_t>) {
                constexpr auto shape = fixed_shape_v<rhs_t>;
                return index::product(shape) * bounded_size_v<lhs_t>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view::decorator_t< view::matmul_t, lhs_t, rhs_t >>{};
            }
        }();
    }; // bounded_size

    template <typename lhs_t, typename rhs_t>
    struct fixed_size<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        using view_type  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
        using shape_type = typename view_type::dst_shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size
} // namespace nmtools::meta

/* ========================================================= */

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct matmul_rhs_transpose_t {};

    template <typename rhs_dim_t>
    constexpr auto matmul_rhs_transpose([[maybe_unused]] rhs_dim_t rhs_dim)
    {
        if constexpr (meta::is_maybe_v<rhs_dim_t>) {
            using result_t = decltype(matmul_rhs_transpose(unwrap(rhs_dim)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(rhs_dim)
                ? return_t{matmul_rhs_transpose(unwrap(rhs_dim))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<matmul_rhs_transpose_t,rhs_dim_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(rhs_dim);
                }

                for (nm_size_t i=0; i<(nm_size_t)rhs_dim; i++) {
                    at(result,i) = i;
                }

                if (rhs_dim >= 2) {
                    auto tmp = at(result,-1);
                    at(result,-1) = at(result,-2);
                    at(result,-2) = tmp;
                }
            }

            return result;
        }
    } // matmul_rhs_transpose

    struct matmul_lhs_tile_t {};

    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto matmul_lhs_tile(const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        if constexpr (meta::is_maybe_v<lhs_shape_t> || meta::is_maybe_v<rhs_shape_t>) {
            using result_t = decltype(matmul_lhs_tile(unwrap(lhs_shape),unwrap(rhs_shape)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(lhs_shape) && has_value(rhs_shape)
                ? return_t{matmul_lhs_tile(unwrap(lhs_shape),unwrap(rhs_shape))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<matmul_lhs_tile_t,lhs_shape_t,rhs_shape_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto lhs_dim = len(lhs_shape);
                auto rhs_dim = len(rhs_shape);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(lhs_dim);
                }

                for (nm_size_t i=0; i<(nm_size_t)lhs_dim; i++) {
                    at(result,i) = 1;
                }

                if (lhs_dim >= 2 && rhs_dim >= 2) {
                    at(result,-1) = at(rhs_shape,-1);
                }
            }

            return result;
        }
    } // matmul_lhs_tile

    struct matmul_lhs_reshape_t {};

    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto matmul_lhs_reshape([[maybe_unused]] const lhs_shape_t& lhs_shape, [[maybe_unused]] const rhs_shape_t& rhs_shape)
    {
        if constexpr (meta::is_maybe_v<lhs_shape_t> || meta::is_maybe_v<rhs_shape_t>) {
            using result_t = decltype(matmul_lhs_reshape(unwrap(lhs_shape),unwrap(rhs_shape)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(lhs_shape) && has_value(rhs_shape)
                ? return_t{matmul_lhs_reshape(unwrap(lhs_shape),unwrap(rhs_shape))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<matmul_lhs_reshape_t,lhs_shape_t,rhs_shape_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto lhs_dim = len(lhs_shape);
                auto rhs_dim = len(rhs_shape);

                auto dst_dim = lhs_dim;
                if (lhs_dim >= 2 && rhs_dim >= 2) {
                    dst_dim = dst_dim + 1;
                }

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }

                for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                    at(result,i) = 1;
                }

                for (nm_size_t i=0; i<(nm_size_t)lhs_dim; i++) {
                    at(result,i) = at(lhs_shape,i);
                }

                if (lhs_dim >= 2 && rhs_dim >= 2) {
                    at(result,-1) = at(rhs_shape,-1);
                    auto tmp = at(result,-1);
                    at(result,-1) = at(result,-2);
                    at(result,-2) = tmp;
                }
            }

            return result;
        }
    } // matmul_lhs_reshape

    struct matmul_rhs_reshape_t {};

    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto matmul_rhs_reshape([[maybe_unused]] const lhs_shape_t& lhs_shape, [[maybe_unused]] const rhs_shape_t& rhs_shape)
    {
        if constexpr (meta::is_maybe_v<lhs_shape_t> || meta::is_maybe_v<rhs_shape_t>) {
            using result_t = decltype(matmul_rhs_reshape(unwrap(lhs_shape),unwrap(rhs_shape)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(lhs_shape) && has_value(rhs_shape)
                ? return_t{matmul_rhs_reshape(unwrap(lhs_shape),unwrap(rhs_shape))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<matmul_rhs_reshape_t,lhs_shape_t,rhs_shape_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto lhs_dim = len(lhs_shape);
                auto rhs_dim = len(rhs_shape);

                auto dst_dim = rhs_dim;
                auto sum_dim = 0;

                if (lhs_dim >= 2 && rhs_dim >= 2) {
                    dst_dim = dst_dim + 1;
                    sum_dim = 2;
                }

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }

                for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                    at(result,i) = 1;
                }

                for (nm_size_t i=0; i<(nm_size_t)rhs_dim-sum_dim; i++) {
                    at(result,i) = at(rhs_shape,i);
                }

                for (nm_size_t i=0; i<(nm_size_t)sum_dim; i++) {
                    nm_index_t idx = -(i+1);
                    at(result,idx) = at(rhs_shape,idx);
                }
            }

            return result;
        }
    } // matmul_rhs_reshape
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct MATMUL_RHS_TRANSPOSE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct MATMUL_LHS_TILE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct MATMUL_LHS_RESHAPE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct MATMUL_RHS_RESHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename rhs_dim_t>
    struct resolve_optype<
        void, index::matmul_rhs_transpose_t, rhs_dim_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<rhs_dim_t>) {
                using type = error::MATMUL_RHS_TRANSPOSE_UNSUPPORTED<rhs_dim_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<rhs_dim_t>) {
                constexpr auto rhs_dim = to_value_v<rhs_dim_t>;
                constexpr auto result  = index::matmul_rhs_transpose(clipped_size_t<rhs_dim>(rhs_dim));
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_clipped_index_v<rhs_dim_t>) {
                constexpr auto MAX_DIM = max_value_v<rhs_dim_t>;
                using type = nmtools_static_vector<nm_size_t,MAX_DIM>;
                return as_value_v<type>;
            } else {
                // TODO: use small vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::matmul_rhs_transpose_t

    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype<
        void, index::matmul_lhs_tile_t, lhs_shape_t, rhs_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_shape_t>
                || !is_index_array_v<rhs_shape_t>
            ) {
                using type = error::MATMUL_LHS_TILE_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<lhs_shape_t>
                && is_constant_index_array_v<rhs_shape_t>
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::matmul_lhs_tile(lhs_shape,rhs_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto LHS_B_DIM = bounded_size_v<lhs_shape_t>;
                constexpr auto LHS_DIM   = len_v<lhs_shape_t>;
                if constexpr (LHS_DIM > 0) {
                    using type = nmtools_array<nm_size_t,LHS_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,LHS_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::matmul_lhs_tile_t

    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype<
        void, index::matmul_lhs_reshape_t, lhs_shape_t, rhs_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_shape_t>
                || !is_index_array_v<rhs_shape_t>
            ) {
                using type = error::MATMUL_LHS_RESHAPE_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<lhs_shape_t>
                && is_constant_index_array_v<rhs_shape_t>
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::matmul_lhs_reshape(lhs_shape,rhs_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto LHS_DIM = len_v<lhs_shape_t>;
                constexpr auto RHS_DIM = len_v<rhs_shape_t>;
                [[maybe_unused]] constexpr auto LHS_B_DIM = bounded_size_v<lhs_shape_t>;
                [[maybe_unused]] constexpr auto RHS_B_DIM = bounded_size_v<rhs_shape_t>;
                if constexpr (LHS_DIM > 0 && RHS_DIM > 0) {
                    constexpr auto DST_DIM = (LHS_DIM >= 2 && RHS_DIM >= 2)
                        ? LHS_DIM + 1 : LHS_DIM;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)>
                    && !is_fail_v<decltype(RHS_B_DIM)>
                ) {
                    constexpr auto DST_B_DIM = (LHS_B_DIM >= 2 && RHS_B_DIM >= 2)
                        ? LHS_B_DIM + 1 : LHS_B_DIM;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)>) {
                    constexpr auto DST_B_DIM = LHS_B_DIM + 1;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::matmul_lhs_reshape_t

    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype<
        void, index::matmul_rhs_reshape_t, lhs_shape_t, rhs_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_shape_t>
                || !is_index_array_v<rhs_shape_t>
            ) {
                using type = error::MATMUL_RHS_RESHAPE_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<lhs_shape_t>
                && is_constant_index_array_v<rhs_shape_t>
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::matmul_rhs_reshape(lhs_shape,rhs_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto LHS_DIM = len_v<lhs_shape_t>;
                constexpr auto RHS_DIM = len_v<rhs_shape_t>;
                [[maybe_unused]] constexpr auto LHS_B_DIM = bounded_size_v<lhs_shape_t>;
                [[maybe_unused]] constexpr auto RHS_B_DIM = bounded_size_v<rhs_shape_t>;
                if constexpr (LHS_DIM > 0 && RHS_DIM > 0) {
                    constexpr auto DST_DIM = (LHS_DIM >= 2 && RHS_DIM >= 2)
                        ? RHS_DIM + 1 : RHS_DIM;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)>
                    && !is_fail_v<decltype(RHS_B_DIM)>
                ) {
                    constexpr auto DST_B_DIM = (LHS_B_DIM >= 2 && RHS_B_DIM >= 2)
                        ? RHS_B_DIM + 1 : RHS_B_DIM;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(RHS_B_DIM)>) {
                    constexpr auto DST_B_DIM = RHS_B_DIM + 1;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::matmul_rhs_reshape_t
} // nmtools::meta

/* ========================================================= */

#include "nmtools/array/view/alias.hpp"
#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t>
    constexpr auto matmulv2(const lhs_t& lhs, const rhs_t& rhs)
    {
        // check for maybe here to avoid maybe<tuple<>> from aliasing
        if constexpr (meta::is_maybe_v<lhs_t> || meta::is_maybe_v<rhs_t>) {
            using result_t = decltype(matmulv2(unwrap(lhs),unwrap(rhs)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(lhs) && has_value(rhs)
                ? return_t{matmulv2(unwrap(lhs),unwrap(rhs))}
                : return_t{meta::Nothing}
            );
        } else {
            auto aliased = view::aliased(lhs,rhs);

            auto a_lhs = nmtools::get<0>(aliased);
            auto a_rhs = nmtools::get<1>(aliased);

            auto lhs_shape = shape<true>(lhs);
            auto rhs_shape = shape<true>(rhs);
            // auto lhs_dim = dim<true>(lhs);
            auto rhs_dim = dim<true>(rhs);

            auto sum_axis = meta::ct_v<-1>;

            auto reps = index::matmul_lhs_tile(lhs_shape,rhs_shape);
            auto axes = index::matmul_rhs_transpose(rhs_dim);
            auto tf_lhs_shape = index::matmul_lhs_reshape(lhs_shape,rhs_shape);

            auto a = view::reshape(view::tile(a_lhs,reps),tf_lhs_shape);
            auto b = view::transpose(a_rhs,axes);
            
            auto tf_rhs_shape = index::matmul_rhs_reshape(
                nmtools::shape<true>(a)
                , nmtools::shape<true>(b)
            );

            auto c = view::reshape(b,tf_rhs_shape);

            return view::sum(
                view::multiply(a,c)
                , sum_axis
            );
        }
    } // matmulv2
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MATMUL_HPP