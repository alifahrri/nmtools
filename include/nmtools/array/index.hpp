#ifndef NMTOOLS_ARRAY_INDEX_HPP
#define NMTOOLS_ARRAY_INDEX_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    using std::size;
    using std::get;
    using std::common_type_t;
    using meta::remove_cvref_t;

    /**
     * @brief special tag to represent end index, used for slicing.
     * 
     * @see nmtools::slice
     */
    struct end_t {};

    inline constexpr auto end = end_t{};

    /**
     * @brief helper function to create compile-time slice index
     * 
     * @tparam i non-type template parameter representing slicing index
     * @return constexpr auto meta::index_constant
     * @see nmtools::slice
     * @see nmtools::meta::index_constant
     */
    template <auto i>
    constexpr auto make_slice_index()
    {
        return meta::index_constant<i>{};
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice index
     * 
     * @tparam i template parameter representing slicing index
     * @return constexpr auto meta::index_constant
     * @see nmtools::slice
     * @see nmtools::meta::index_constant
     * @todo constraint to nmtools::end_t only
     */
    template <typename i>
    constexpr auto make_slice_index()
    {
        return i{};
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices,
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a value
     * @tparam j index of 2nd axis, expects a value
     * @return constexpr auto tuple of meta::index_constant
     * @see nmtools::meta::index_constant
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <auto i, auto j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(meta::index_constant<i>{},meta::index_constant<j>{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a type, e.g. nmtools::end_t
     * @tparam j index of 2nd axis, expects a type, e.g. nmtools::end_t
     * @return constexpr auto tuple of meta::index_constant
     * @see nmtools::end_t
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <typename i, typename j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(i{},j{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a value
     * @tparam j index of 2nd axis, expects a type, e.g. nmtools::end_t
     * @return constexpr auto tuple of meta::index_constant and given type
     * @see nmtools::end_t
     * @see nmtools::meta::index_constant
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <auto i, typename j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(meta::index_constant<i>{},j{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a type, e.g. nmtools::end_t
     * @tparam j index of 2nd axis, expects a value
     * @return constexpr auto tuple of given type and meta::index_constant
     * @see nmtools::end_t
     * @see nmtools::meta::index_constant
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <typename i, auto j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(i{},meta::index_constant<j>{});
    } // make_slice_index

    /**
     * @brief indices_pack to support dynamic dimension
     * 
     * @tparam shape_t 
     * @tparam typename 
     * @todo remove, unify with fixed-dim version
     */
    template <typename shape_t, typename=void>
    struct indices_pack_t
    {
        using shape_type = shape_t;
        using stride_type = shape_t;
        using size_type = typename shape_type::value_type;

        shape_type shape;
        stride_type stride;

        /**
         * @brief Construct a new indices pack t object
         * 
         * @param shape original array shape
         */
        constexpr indices_pack_t(shape_type shape)
            : shape(shape), stride(array::detail::compute_strides(shape))
        {
            // @note: this prevents indices_pack_t to be used in constexpr
            // gcc error: must be initialized by mem-initializer
            // stride = array::detail::compute_strides(shape);
        }

        /**
         * @brief return the number of element
         * 
         * @return auto 
         */
        constexpr decltype(auto) size() const noexcept
        {
            // compute product
            auto identity = static_cast<size_type>(1);
            for (const auto s : shape)
                identity *= s;
            return identity;
        } // size

        /**
         * @brief get the packed indices from flat indices
         * 
         * @param i flat index
         * @return auto 
         */
        constexpr inline decltype(auto) operator[](size_t i)
        {
            using array::detail::compute_indices;
            // map offset (flat index) back to indices
            return compute_indices(i,shape,stride);
        } // operator[]
    }; // indices_pack_t

    /**
     * @brief indices transformer
     * 
     * Adapter from N-dimensional indices to packed 1-D indices,
     * can be used to transform nested N loop to 1 flat loop.
     * Only support fixed-dimensional array for now.
     * 
     * @tparam array_t compile-time array type to represent shape_type and stride_type
     * @tparam T
     * @tparam N number of dimension
     * @see nmtools::apply_at
     */
    template <template<typename,size_t> typename array_t, typename T, size_t N>
    struct indices_pack_t<array_t<T,N>>
    {
        using shape_type = array_t<T,N>;
        using stride_type = array_t<T,N>;
        using size_type = typename shape_type::value_type;

        shape_type shape;
        stride_type stride;

        /**
         * @brief Construct a new indices pack t object
         * 
         * @param shape original array shape
         */
        constexpr indices_pack_t(shape_type shape)
            : shape(shape), stride(array::detail::compute_strides(shape))
        {
            // @note: this prevents indices_pack_t to be used in constexpr
            // gcc error: must be initialized by mem-initializer
            // stride = array::detail::compute_strides(shape);
        }

        /**
         * @brief return the number of element
         * 
         * @return auto 
         */
        constexpr decltype(auto) size() const noexcept
        {
            // compute product
            auto identity = static_cast<size_type>(1);
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                identity *= std::get<i>(shape);
            });
            return identity;
        } // size

        /**
         * @brief get the packed indices from flat indices
         * 
         * @param i flat index
         * @return auto 
         */
        constexpr inline decltype(auto) operator[](size_t i)
        {
            using array::detail::compute_indices;
            using detail::as_tuple;
            // map offset (flat index) back to indices
            return as_tuple(compute_indices(i,shape,stride));
        } // operator[]
    }; // indices_pack_t

    /**
     * @brief make indices_pack from array representing shape
     * 
     * @tparam T element type of shape
     * @tparam N number of dimension
     * @param shape original array shape
     * @return constexpr auto indices transformer
     * @see indices_pack_t
     */
    template <typename shape_t>
    constexpr auto indices_pack(shape_t shape)
    {
        if constexpr (meta::is_specialization_v<shape_t,std::tuple> || meta::is_specialization_v<shape_t,std::pair>) {
            auto shape_ = detail::make_array<std::array>(shape);
            return indices_pack_t(shape_);
        }
        else return indices_pack_t(shape);
    } // indices_pack

    namespace detail {
        using std::is_same_v;
        using std::is_integral_v;
        using meta::is_array2d_v;
        using meta::is_array1d_v;
        using meta::is_fixed_size_matrix_v;
        using meta::is_fixed_size_vector_v;
        using meta::is_integral_constant_v;

        /**
         * @brief reverse array (of indices)
         * 
         * @tparam indices_t array of same type
         * @tparam Is index sequence
         * @param indices 
         * @return constexpr auto 
         */
        template <typename indices_t, size_t...Is>
        constexpr auto reverse(const indices_t& indices, std::index_sequence<Is...>)
        {
            // assuming same shape
            return indices_t{std::get<Is>(indices)...};
        } // reverse

        /**
         * @brief entrypoint for reversing array (of indices)
         * 
         * @tparam indices_t array of same type
         * @param indices 
         * @return constexpr auto 
         */
        template <typename indices_t>
        constexpr auto reverse(const indices_t& indices)
        {
            if constexpr (meta::has_tuple_size_v<indices_t>) {
                constexpr auto N = std::tuple_size_v<indices_t>;
                using reverse_t = meta::make_reversed_index_sequence<N>;
                return reverse(indices, reverse_t{});
            }
            else {
                auto ret = indices_t{};
                if constexpr (meta::is_resizeable_v<indices_t>)
                    ret.resize(indices.size());
                auto n = indices.size();
                for (size_t i=0; i<n; i++)
                    ret.at(i) = indices.at(n-1-i);
                return ret;
            }
        } // reverse

        /**
         * @brief perform gather op
         *
         * perform the following op: `ret[i] = vec[idx[i]]`, reverse of scatter
         * 
         * @tparam vector_t type of vec
         * @tparam indices_t type of indices
         * @param vec 
         * @param indices 
         * @return constexpr auto 
         * @see scatter
         */
        template <typename vector_t, typename indices_t>
        constexpr auto gather(const vector_t& vec, const indices_t& indices)
        {
            constexpr auto indices_is_tuple = meta::is_specialization_v<vector_t,std::tuple> 
                || meta::is_specialization_v<vector_t,std::tuple>;
            constexpr auto order_is_tuple = meta::is_specialization_v<indices_t,std::tuple> 
                || meta::is_specialization_v<indices_t,std::tuple>;
            // get the size of vec
            auto n = [&](){
                if constexpr (meta::has_tuple_size_v<vector_t>)
                    return std::tuple_size_v<vector_t>;
                else return vec.size();
            }();
            // get the size of indices
            auto m = [&](){
                if constexpr (meta::has_tuple_size_v<indices_t>)
                    return std::tuple_size_v<indices_t>;
                else return indices.size();
            }();
            // @todo static assert whenever possible
            assert (n == m
                // , "unsupported permute, mismatched dimension between vec and indices"
            );

            // assume return type is same
            auto ret = vector_t{};

            if constexpr (meta::is_resizeable_v<vector_t>)
                ret.resize(vec.size()); // assuming indicesh has size

            // std::array type has value_type
            using element_t = meta::get_element_type_t<vector_t>;
            using common_t = std::conditional_t<
                std::is_void_v<element_t>,
                meta::apply_t<std::common_type,vector_t>,
                element_t
            >;

            // handle tuple if it has common_type
            if constexpr (meta::has_tuple_size_v<vector_t> && !std::is_void_v<common_t>) {
                constexpr auto N = std::tuple_size_v<vector_t>;
                meta::template_for<N>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    // get index (idx = indices.at(i))
                    // @todo make at support compile-time index
                    auto idx = [&](){
                        if constexpr (meta::has_tuple_size_v<indices_t>)
                            return std::get<i>(indices);
                        else return indices.at(i);
                    }();
                    // get value using iile
                    // note that n is runtime value while tuple access must be at compile time
                    // access tuple element at runtime by assuming the elements of tuple has common type
                    auto v = [&](){
                        // access tuple element at runtime
                        auto value = common_t{};
                        // @note to check to N since n may be > i
                        meta::template_for<N>([&](auto index){
                            constexpr auto ii = decltype(index)::value;
                            if (idx==ii)
                                value = static_cast<common_t>(std::get<ii>(vec));
                        });
                        return value;
                    }();
                    // store value to return
                    std::get<i>(ret) = v;
                });
            }
            else {
                for (size_t i=0; i<m; i++) {
                    auto idx = indices.at(i);
                    auto v = vec.at(idx);
                    ret.at(i) = v;
                }
            }
            return ret;
        } // gather

        /**
         * @brief perform scatter op
         * 
         * perform `ret[idx[i]] = vec[i]` aka reverse of gather
         *
         * @tparam vector_t type of vec
         * @tparam indices_t type of indices
         * @param vec 
         * @param indices 
         * @return constexpr auto 
         * @see gather
         */
        template <typename vector_t, typename indices_t>
        constexpr auto scatter(const vector_t& vec, const indices_t& indices)
        {
            constexpr auto indices_is_tuple = meta::is_specialization_v<vector_t,std::tuple> 
                || meta::is_specialization_v<vector_t,std::tuple>;
            constexpr auto order_is_tuple = meta::is_specialization_v<indices_t,std::tuple> 
                || meta::is_specialization_v<indices_t,std::tuple>;
            // get the size of vec
            auto n = [&](){
                if constexpr (meta::has_tuple_size_v<vector_t>)
                    return std::tuple_size_v<vector_t>;
                else return vec.size();
            }();
            // get the size of indices
            auto m = [&](){
                if constexpr (meta::has_tuple_size_v<indices_t>)
                    return std::tuple_size_v<indices_t>;
                else return indices.size();
            }();
            // @todo static assert whenever possible
            assert (n == m
                // , "unsupported permute, mismatched dimension between vec and indices"
            );

            // assume return type is same
            auto ret = vector_t{};

            if constexpr (meta::is_resizeable_v<vector_t>)
                ret.resize(vec.size()); // assuming indicesh has size

            // std::array type has value_type
            using element_t = meta::get_element_type_t<vector_t>;
            using common_t = std::conditional_t<
                std::is_void_v<element_t>,
                meta::apply_t<std::common_type,vector_t>,
                element_t
            >;

            // handle tuple if it has common_type
            if constexpr (meta::has_tuple_size_v<vector_t> && !std::is_void_v<common_t>) {
                constexpr auto N = std::tuple_size_v<vector_t>;
                meta::template_for<N>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    // get index (idx = indices.at(i))
                    // @todo make at support compile-time index
                    auto idx = [&](){
                        if constexpr (meta::has_tuple_size_v<indices_t>)
                            return std::get<i>(indices);
                        else return indices.at(i);
                    }();
                    auto v = std::get<i>(vec);
                    // store value to return
                    meta::template_for<N>([&](auto index){
                        constexpr auto j = decltype(index)::value;
                        if (idx==j)
                            std::get<j>(ret) = v;
                    });
                });
            }
            else {
                for (size_t i=0; i<m; i++) {
                    auto v = vec.at(i);
                    auto idx = indices.at(i);
                    ret.at(idx) = v;
                }
            }
            return ret;
        } // scatter

        /**
         * @brief return type for unpack_slice_indices for 2D array
         * 
         */
        using array2d_slice_indices_t = std::tuple<std::tuple<size_t,size_t>,std::tuple<size_t,size_t>>;
        /**
         * @brief return type for unpack_slice_indices for 1D array
         * 
         */
        using array1d_slice_indices_t = std::tuple<size_t,size_t>;

        template <typename rows_t, typename cols_t, typename row_stop_t, typename col_stop_t>
        constexpr auto make_stop_indices(rows_t rows, cols_t cols, const row_stop_t& row_stop_, const col_stop_t& col_stop_)
        {
            if constexpr (is_same_v<row_stop_t,end_t> && is_same_v<col_stop_t,end_t>)
                return std::make_tuple(rows, cols);
            // only row is end tag, col stop is compile time constant
            else if constexpr (is_same_v<row_stop_t,end_t> && is_integral_constant_v<col_stop_t>)
                return std::make_tuple(rows, col_stop_());
            // only col is end tag, row stop is compile time constant
            else if constexpr (is_integral_constant_v<row_stop_t> && is_same_v<col_stop_t,end_t>)
                return std::make_tuple(row_stop_(), cols);
            // both is compile time constant
            else if constexpr (is_integral_constant_v<row_stop_t> && is_integral_constant_v<col_stop_t>)
                return std::make_tuple(row_stop_(), col_stop_());
            // only row is end tag, col stop is simply integer
            else if constexpr (is_same_v<row_stop_t,end_t> && is_integral_v<col_stop_t>)
                return std::make_tuple(rows, col_stop_);
            // only col is end tag, row stop is simply integer
            else if constexpr (is_integral_v<row_stop_t> && is_same_v<col_stop_t,end_t>)
                return std::make_tuple(row_stop_, cols);
            // both is simpy integer
            else if constexpr (is_integral_v<row_stop_t> && is_integral_v<col_stop_t>)
                return std::make_tuple(row_stop_, col_stop_);
        } // make_stop_indices

        /**
         * @brief helper function to unpack slice indices for 2D array
         * in which start & stop may be pair of integral_constant & special tag end_t
         * 
         * @tparam Array fixed-size 2D array
         * @param start compile-time start indices pair
         * @param stop compile-time stop indices pair
         * @return std::enable_if_t<is_array2d_v<Array>,array2d_slice_indices_t> 
         * @see array2d_slice_indices_t
         * @see slice
         */
        template <typename Array, typename start_t, typename stop_t>
        constexpr auto unpack_slice_indices(const Array& a, start_t start, stop_t stop)
            -> std::enable_if_t<is_array2d_v<Array>, array2d_slice_indices_t>
        {
            // unpack start & stop
            auto [row_start_, col_start_] = start;
            auto [row_stop_, col_stop_] = stop;
            using row_start_t = decltype(row_start_);
            using col_start_t = decltype(col_start_);
            using row_stop_t  = decltype(row_stop_);
            using col_stop_t  = decltype(col_stop_);
            constexpr bool valid_row_stop = is_integral_v<row_stop_t> || is_integral_constant_v<row_stop_t> || is_same_v<row_stop_t,end_t>;
            constexpr bool valid_col_stop = is_integral_v<col_stop_t> || is_integral_constant_v<col_stop_t> || is_same_v<col_stop_t,end_t>;
            // assuming 2D array
            // make sure valid type, strictly integral_constant for start
            // while stop is possibly contains end_t
            static_assert (
                meta::is_array2d_v<Array>
                && (is_integral_constant_v<row_start_t> || is_integral_v<row_start_t>)
                && (is_integral_constant_v<col_start_t> || is_integral_v<col_start_t>)
                && valid_row_stop && valid_col_stop,
                "failed to unpack slice indices, expects packed type of "
                " start_t is integral_constant and"
                " packed type of stop_t may be integral_constant or end_t"
            );
            auto [rows, cols] = matrix_size(a);
            // unpack integral constant type to value
            // use immediately invoked lambda to expose variable to outer scope while actual packing is
            // dispatched based on the type using constexpr if
            // workaround for error: reference to local binding declared in enclosing function
            auto istart = [&,row_start_=row_start_,col_start_=col_start_](){
                if constexpr (is_integral_constant_v<row_start_t> && is_integral_constant_v<col_start_t>)
                    return std::make_tuple(row_start_(), col_start_());
                else
                    return std::make_tuple(row_start_, col_start_);
            }();
            // workaround for error: reference to local binding declared in enclosing function
            // but doesnt work on gcc: istop has incomplete type
            // auto istop = [&,row_start_=row_start_,col_start_=col_start_,row_stop_=row_stop_,col_stop_=col_stop_,rows=rows,cols=cols](){
            // auto istop = [&](){
            //     // both stop is end tag
            //     if constexpr (is_same_v<row_stop_t,end_t> && is_same_v<col_stop_t,end_t>)
            //         return std::make_tuple(rows, cols);
            //     // only row is end tag, col stop is compile time constant
            //     else if constexpr (is_same_v<row_stop_t,end_t> && is_integral_constant_v<col_stop_t>)
            //         return std::make_tuple(rows, col_stop_());
            //     // only col is end tag, row stop is compile time constant
            //     else if constexpr (is_integral_constant_v<row_stop_t> && is_same_v<col_stop_t,end_t>)
            //         return std::make_tuple(row_stop_(), cols);
            //     // both is compile time constant
            //     else if constexpr (is_integral_constant_v<row_stop_t> && is_integral_constant_v<col_stop_t>)
            //         return std::make_tuple(row_stop_(), col_stop_());
            //     // only row is end tag, col stop is simply integer
            //     else if constexpr (is_same_v<row_stop_t,end_t> && is_integral_v<col_stop_t>)
            //         return std::make_tuple(rows, col_stop_);
            //     // only col is end tag, row stop is simply integer
            //     else if constexpr (is_integral_v<row_stop_t> && is_same_v<col_stop_t,end_t>)
            //         return std::make_tuple(row_stop_, cols);
            //     // both is simpy integer
            //     else if constexpr (is_integral_v<row_stop_t> && is_integral_v<col_stop_t>)
            //         return std::make_tuple(row_stop_, col_stop_);
            // }();
            auto istop = make_stop_indices(rows,cols,row_stop_,col_stop_);
            return std::make_tuple(istart, istop);
        } // constexpr auto unpack_slice_indices

        /**
         * @brief helper function to unpack slice indices for 1D array
         * in which start is integral_constant and stop may be integral_constant or special tag end_t
         * 
         * @tparam Array fixed-size 1D array
         * @param start compile-time start index
         * @param stop compile-time stop index
         * @return std::enable_if_t<!is_array2d_v<Array> && is_array1d_v<Array>,array1d_slice_indices_t> 
         */
        template <typename Array, typename start_t, typename stop_t>
        constexpr auto unpack_slice_indices(const Array& a, start_t start, stop_t stop)
            -> std::enable_if_t<!is_array2d_v<Array> && is_array1d_v<Array>,array1d_slice_indices_t>
        {
            auto n = vector_size(a);
            if constexpr (is_integral_constant_v<start_t> && is_same_v<stop_t,end_t>)
                return std::make_tuple(start(),n);
            else if constexpr (is_integral_constant_v<start_t> && is_integral_constant_v<stop_t>)
                return std::make_tuple(start(),stop());
            else if constexpr (is_integral_v<start_t> && is_same_v<stop_t,end_t>)
                return std::make_tuple(start,n);
            else if constexpr (is_integral_v<start_t> && is_integral_v<stop_t>)
                return std::make_tuple(start,stop);
        } // constexpr auto unpack_slice_indices
    } // namespace detail
} // namespace nmtools

#endif // NMTOOLS_ARRAY_INDEX_HPP