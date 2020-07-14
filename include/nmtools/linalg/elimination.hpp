#ifndef NMTOOLS_LINALG_ELIMINATION_HPP
#define NMTOOLS_LINALG_ELIMINATION_HPP

#include "nmtools/utility/helper.hpp"
#include "nmtools/linalg/matvec.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/traits.hpp"

#include <map>
#include <tuple>
#include <string>
#include <unordered_map>

namespace nmtools::linalg {

    using std::size;
    using helper::log;

    using std::is_null_pointer_v;
    using std::tuple;
    using std::is_base_of;
    using std::is_base_of_v;
    using std::common_type_t;

    using traits::remove_cvref_t;
    using traits::get_container_value_type_t;
    using traits::is_multiplicative_v;
    using traits::is_array1d_v;

    using std::make_tuple;

    namespace tag {
        using helper::type_in_tuple;
        /**
         * @brief default tag for partial_pivot
         * 
         */
        struct pivot_t {};
        /**
         * @brief tag for in-place version of partial_pivot
         * 
         */
        struct pivot_inplace_t : pivot_t {};
        /**
         * @brief return index mapping for partial_pivot ops
         * 
         */
        struct pivot_index_map_t : pivot_t {};
        /**
         * @brief helper variable template to check 
         * if T is valid pivot tag
         * 
         * @tparam T 
         */
        template <typename T>
        inline constexpr bool is_pivot_v = is_base_of_v<pivot_t,T>;

        /**
         * @brief default tag for forward_elimination
         * 
         */
        struct elimination_t {};
        /**
         * @brief tag for forward_elimination with partial pivoting
         * 
         */
        struct elimination_with_pivot_t : elimination_t {};
        /**
         * @brief tag for forward_elimination to keep lower mat esp. for decomposition
         * 
         */
        struct elimination_keep_lower_mat_t : elimination_t {};
        /**
         * @brief helper variable template to determine 
         * if T is valid elimination tag
         * 
         * @tparam T 
         */
        template <typename T>
        inline constexpr bool is_elimination_v = is_base_of_v<elimination_t,T>;
        /**
         * @brief specialized version of is_elimination_v to handle tuple
         * 
         * @tparam Args 
         */
        template <typename ...Args>
        inline constexpr bool is_elimination_v<tuple<Args...>> = type_in_tuple<is_base_of>(elimination_t{},tuple<Args...>{});

        using traits::is_tuple_v;

        /**
         * @brief check if given tag is present in T
         * in which T could be single type or tuple
         * specialization on tuple checks if tag is
         * presents in any of the tuple's arguments
         * 
         * @tparam tag_t 
         * @tparam T 
         * @tparam void 
         */
        template <typename tag_t, typename T, typename = void>
        struct is_tag_enabled : std::is_same<tag_t,T> {};

        /**
         * @brief partial specialization when T is tuple
         * 
         * @tparam tag_t 
         * @tparam T 
         */
        template <typename tag_t, typename T>
        struct is_tag_enabled<tag_t,T,std::enable_if_t<is_tuple_v<T>> > 
        {
            static constexpr bool value = type_in_tuple(tag_t{},T{});
        };

        /**
         * @brief helper variable template to check if tag_t is enabled, 
         * given T, where T can be single tag or tuple of tag
         * 
         * @tparam tag_t tag to check
         * @tparam T tuple of tag or single tag
         */
        template <typename tag_t, typename T>
        inline constexpr bool is_tag_enabled_v = is_tag_enabled<tag_t,T>::value;
    } // namespace tag

    /**
     * @brief perform partial (row-only) pivoting
     * 
     * @tparam pivot_tag=tag::pivot_t optional tag for return type selection
     * @tparam Matrix matrix-like
     * @tparam Vector vector-like
     * @tparam Scales=std::nullptr_t 
     * @param A system matrix
     * @param b result vector
     * @param k pivoting row
     * @param scales optional scales vector to determine best pivot row
     * @return constexpr auto 
     *  - int p if pivot_tag is default
     *  - tuple [A,b] if pivot_tag is pivot_inplace_t and scales is nullptr (no scaling)
     *  - tuple [A,b,scales] if pivot_tag is pivot_inplace_t and scales is given
     * @cite chapra2014numerical_partial_pivot
     */
    template <typename pivot_tag=tag::pivot_t, typename Matrix, typename Vector, typename Scales=std::nullptr_t>
    constexpr auto partial_pivot(Matrix A, Vector b, auto k, Scales scales=Scales{}, pivot_tag=pivot_tag{})
    {
        static_assert(
            tag::is_pivot_v<pivot_tag>,
            "invalid pivot tag"
        );
        static_assert(
            is_null_pointer_v<Scales> || is_array1d_v<Scales>,
            "unsupported type for scales"
        );
        
        constexpr auto use_scales_v = !is_null_pointer_v<Scales>;

        /* TODO: assert if len(A) == len(b) == len(scales) */
        auto n = size(A);
        /* selected pivot row */
        auto p = k;

        /* initial value at init pivot row */
        auto big = fabs(A[k][k]);
        if constexpr (use_scales_v)
            big = big / scales[k];
        
        /* find best pivot point, starting at row k+1 down to n */
        for (auto ii=k+1; ii<n; ii++) {
            auto dummy = fabs(A[ii][k]);
            if constexpr (use_scales_v)
                dummy = dummy / scales[ii];
            if (dummy > big) {
                p = ii;
                big = dummy;
            }
        }
        /* perform in-place pivoting */
        if constexpr (std::is_same_v<pivot_tag,tag::pivot_inplace_t>) {
            Matrix A_ = A;
            Vector b_ = b;
            Scales s_ = scales;

            if (p != k) {
                /* swap p-th row with k-th row */
                /* TODO: consider using swap() */
                for (auto jj=k; jj<n; jj++) {
                    auto dummy = A_[p][jj];
                    A_[p][jj] = A_[k][jj];
                    A_[k][jj] = dummy;
                }
                /* TODO: consider using swap() */
                auto dummy = b[k];
                b_[k] = b[p];
                b_[p] = dummy;

                if constexpr (use_scales_v) {
                    auto dummy = scales[k];
                    s_[k] = scales[p];
                    s_[p] = dummy;
                }
            }

            /* now k-th row is pivoted, 
                has largest possible point at pivot row */
            if constexpr (use_scales_v)
                return make_tuple(A_,b_,s_);
            else 
                return make_tuple(A_,b_);
        } 
        /* TODO: complete this */
        /* return mapping to index */
        // else if (std::is_same_v<pivot_tag,tag::pivot_index_map_t>) {
        //     using index_t = std::tuple<size_t,size_t>;
        //     if constexpr (traits::has_tuple_size_v<Matrix>) {
                
        //     } else {

        //     }        
        // }
        /* only return pivot row index */
        else {
            return p;
        }
    }

    /**
     * @brief forward elimination of unknowns
     * \f{eqnarray*}{
     *      a_{11}x_1 + a_{12}x_2}     + ... + a_{1n}x_n       &=& b_1
     *                  a^{'}_{22}x_2} + ... + a^{'}_{2n}x_n   &=& b^{'}_2
     *                                 + ... + a^{''}_{3n}x_n  &=& b^{''}_3
     *                                              \vdot      &=& \vdot
     *                                       + a^{n-1}_{nn}x_n &=& b^{n-1}_n
     * \f}
     *
     * @tparam elimination_tag=tag::elimination_t 
     * @tparam Logger=std::nullptr_t  
     * @tparam Matrix matrix-like
     * @tparam Vector vector-like
     * @tparam Scales=std::nullptr_t 
     * @param A matrix A
     * @param b vector b
     * @param scales optional scales for determining pivot point
     * @param logger optional logging
     * @return constexpr auto [A,b]
     * @cite chapra2014numerical_forward_elimination
     */
    template <typename elimination_tag=tag::elimination_t, typename Logger=std::nullptr_t, typename Matrix, typename Vector, typename Scales=std::nullptr_t>
    constexpr auto forward_elimination(const Matrix& A, const Vector& b, Scales scales=Scales{}, Logger logger=Logger{}, elimination_tag=elimination_tag{})
    {
        using tag::elimination_with_pivot_t;
        using tag::elimination_keep_lower_mat_t;
        using tag::is_elimination_v;
        using tag::is_tag_enabled_v;

        using namespace std::string_literals;

        /* make sure elimination tag is valid */
        static_assert(
            is_elimination_v<elimination_tag>, 
            "unsupported forward_elimination tag"
        );

        /* check if we should use pivot */
        constexpr bool use_pivot_v = is_tag_enabled_v<elimination_with_pivot_t,elimination_tag>;

        /* check if we should store lower mat */
        constexpr bool keep_lower_v = is_tag_enabled_v<elimination_keep_lower_mat_t,elimination_tag>;

        /* for now, keep_lower_mat can't be used together with pivot */
        static_assert(
            (use_pivot_v && !keep_lower_v) || (!use_pivot_v && keep_lower_v) || (!use_pivot_v && !keep_lower_v),
            "cant use pivot together with keep lower mat"
        );

        using common_t = common_type_t<decltype(A[0][0]),decltype(b[0])>;
        using mapping_t = std::map<std::string,common_t>;

        /* check if Scales is valid type */
        using scale_t = remove_cvref_t<get_container_value_type_t<Scales>>;
        static_assert(
            is_multiplicative_v<common_t,scale_t> || is_null_pointer_v<Scales>, 
            "unsupported type for scales"
        );

        /* check if we should log intermediate value */
        /* TODO: check if logger is actually callable with mapping_t */
        constexpr auto log_v = !is_null_pointer_v<Logger>;
        
        /* TODO: assert if A is square matrix */
        auto n = size(A);

        using traits::remove_cvref_t;
        using detail::transform_bounded_array_t;
        using matrix_t = transform_bounded_array_t<remove_cvref_t<Matrix>>;
        using vector_t = transform_bounded_array_t<remove_cvref_t<Vector>>;

        /* placeholder for result */
        matrix_t Ae{};
        vector_t be{};
        if constexpr (traits::is_bounded_array_v<Matrix>) {
            /* convert from raw array to std::array */
            for (size_t i=0; i<n; i++) {
                be[i] = b[i];
                for (size_t j=0; j<size(Ae[0]); j++)
                    Ae[i][j] = A[i][j];
            }
        } else {
            /* we will just copy otherwise */
            Ae = A;
            be = b;
        }
        Scales se = scales;

        /* perform forward elimination */

        /* moves down the matrix from one pivot to the next, e.g. (0,0), (1,1) ... */
        for (size_t k=0; k<(n-1); k++) {    // column

            /* conditional compilation if pivot is enabled */
            if constexpr (use_pivot_v) {
                /* TODO: support index mapping pivot */
                /* perform partial pivot inplace with optional scales (disabled by default) */
                auto tuple = partial_pivot<tag::pivot_inplace_t>(Ae,be,k,se);

                /* when pivot is enabled, set A and B to pivoted mat/vec */
                Ae = std::get<0>(tuple);
                be = std::get<1>(tuple);

                /* if scales is provided */
                if constexpr (!is_null_pointer_v<Scales>)
                    se = std::get<2>(tuple);
            }

            /* optional logging */
            if constexpr (log_v)
                log(logger, mapping_t{{"k"s, k}});

            /* moves below the pivot to each of subsequent rows where elimination takes place */
            for (size_t i=k+1; i<n; i++) {    // row

                /* compute scale factor that will eliminate row i column k*/
                auto factor = Ae[i][k] / Ae[k][k];
                if constexpr (log_v)
                    log(logger, mapping_t{{"factor"s, factor}, {"i"s, i}});

                /* progresses across column to eliminate or transform the elements */
                for (size_t j=k+1; j<n; j++) {
                    Ae[i][j] = Ae[i][j] - factor * Ae[k][j];
                    /* optional logging */
                    if constexpr (log_v)
                        log(logger, mapping_t{{"A[i][j]"s, Ae[i][j]}, {"j"s, j}});
                }
                be[i] = be[i] - factor * be[k];

                /* conditional compilation to store 
                    lower matrix (esp. for decomposition) */
                if constexpr (keep_lower_v)
                    Ae[i][k] = factor;
                else
                    Ae[i][k] = 0;
            }
        }

        return std::make_tuple(Ae,be);
    }

    /**
     * @brief perform backward substitution on upper tridiagonal matrix & modified vector
     * 
     * @tparam Matrix matrix-like
     * @tparam Vector vector-like
     * @tparam Logger=std::nullptr_t 
     * @param A upper tridiagonal matrix
     * @param b modified vector
     * @param logger optional logging
     * @return constexpr auto solution vector x
     * @cite chapra2014numerical_backward_substitution
     */
    template <typename Matrix, typename Vector, typename Logger=std::nullptr_t>
    constexpr auto backward_substitution(const Matrix& A, const Vector& b, Logger logger=Logger{})
    {
        using namespace std::string_literals;
        using common_t = common_type_t<decltype(A[0][0]),decltype(b[0])>;
        using mapping_t = std::map<std::string,common_t>;
        /* TODO: make sure A is square matrix */
        auto n = size(b);

        /* placeholder for result */
        auto x = zeros_like(b);
        /* solve first element */
        x[n-1] = b[n-1] / A[n-1][n-1];

        /* check if we should log intermediate value */
        constexpr auto log = !is_null_pointer_v<Logger>;

        /* TODO: actually log intermediate value */
        for (int i=n-2; i>=0; i--) {
            common_t sum = b[i];
            for (int j=i+1; j<n; j++) {
                sum -= A[i][j] * x[j];
            }
            x[i] = sum / A[i][i];
        }
        return x;
    }

    /**
     * @brief solve linear system Ax=b using naive gauss elimination
     * 
     * @tparam Matrix 
     * @tparam Vector 
     * @tparam Logger=std::nullptr_t 
     * @param A 
     * @param b 
     * @param logger 
     * @return constexpr auto solution vector x
     * @cite chapra2014numerical_forward_elimination
     */
    template <typename Matrix, typename Vector, typename Logger=std::nullptr_t>
    constexpr auto naive_gauss_elimination(const Matrix& A, const Vector& b, Logger logger=Logger{})
    {
        auto [Ae,be] = forward_elimination(A,b,logger);
        auto x = backward_substitution(Ae,be);
        return x;
    }

    /**
     * @brief solve linear system Ax=b using 
     * gauss elimination with partial-pivoting with scales
     * 
     * @tparam Matrix 
     * @tparam Vector 
     * @tparam Logger=std::nullptr_t 
     * @param A 
     * @param b 
     * @param logger 
     * @return constexpr auto solution vector x
     * @cite chapra2014numerical_partial_pivot
     */
    template <typename Matrix, typename Vector, typename Logger=std::nullptr_t>
    constexpr auto gauss_elimination(const Matrix& A, const Vector& b, Logger logger=Logger{})
    {
        /* TODO: check if A & b has the same row */
        auto n = size(A);

        auto A_abs = fabs(A);
        Vector s = zeros_like(b);
        for (size_t i=0; i<n; i++)
            s[i] = max(A_abs[i]);
        
        /* perform forward elimination with pivot and scaling */
        using elimination_t = tag::elimination_with_pivot_t;

        auto [Ae, be] = forward_elimination<elimination_t>(A,b,s,logger);
        auto x = backward_substitution(Ae,be);

        return x;
    }

} // nmtools::linalg

#endif // NMTOOLS_LINALG_ELIMINATION_HPP