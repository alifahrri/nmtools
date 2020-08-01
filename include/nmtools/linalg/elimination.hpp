#ifndef NMTOOLS_LINALG_ELIMINATION_HPP
#define NMTOOLS_LINALG_ELIMINATION_HPP

#include "nmtools/utility/helper.hpp"
#include "nmtools/linalg/matvec.hpp"
#include "nmtools/utility/tag.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

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
    /* make sure use common tag namespace */
    using ::nmtools::tag::is_tag_enabled_v;
    using ::nmtools::tag::size_assert_t;
    using ::nmtools::tag::is_assert_v;

    using std::make_tuple;

    namespace elimination_tag {
        using meta::type_in_tuple;

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
    } // namespace elimination_tag

    namespace etag = elimination_tag;

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
    template <typename pivot_tag=etag::pivot_t, typename Matrix, typename Vector, typename Scales=std::nullptr_t>
    constexpr auto partial_pivot(Matrix A, Vector b, auto k, Scales scales=Scales{}, pivot_tag=pivot_tag{})
    {
        static_assert(
            etag::is_pivot_v<pivot_tag>,
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
        if constexpr (std::is_same_v<pivot_tag,etag::pivot_inplace_t>) {
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
    template <typename elimination_tag=etag::elimination_t, typename Logger=std::nullptr_t, typename Matrix, typename Vector, typename Scales=std::nullptr_t>
    constexpr auto forward_elimination(const Matrix& A, const Vector& b, Scales scales=Scales{}, Logger logger=Logger{}, elimination_tag=elimination_tag{})
    {
        using etag::elimination_with_pivot_t;
        using etag::elimination_keep_lower_mat_t;
        using etag::is_elimination_v;

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
        using meta::transform_bounded_array_t;
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
                auto tuple = partial_pivot<etag::pivot_inplace_t>(Ae,be,k,se);

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
        using elimination_t = etag::elimination_with_pivot_t;

        auto [Ae, be] = forward_elimination<elimination_t>(A,b,s,logger);
        auto x = backward_substitution(Ae,be);

        return x;
    }

    /**
     * @brief perform decomposition for tridiagonal system
     * 
     * @tparam E vector-like
     * @tparam F vector-like
     * @tparam G vector-like
     * @param e lower elements (A_{1,0}, A_{2,0}, ...), e[0] should be zero
     * @param f diagonal elements (A_{0,0}, A_{1,1}, ...)
     * @param g upper elements (A_{0,1}, A{1,2}, ...), g[n-1] should be zero
     * @return constexpr auto [l,u], 
     *  l: lower entry of decomposed matrix,
     *  u: upper entry of decomposed matrix,
     * @cite chapra2014numerical_tridiagonal_systems
     */
    template <typename tag_t=size_assert_t, typename E, typename F, typename G>
    constexpr auto tridiagonal_decomposition(const E& e, const F& f, const G& g)
    {
        static_assert(
            is_array1d_v<E> && is_array1d_v<F> && is_array1d_v<G>,
            "unsupported types for tridiagonal system elimination"
        );

        static_assert(
            is_assert_v<tag_t>,
            "unsupported tag for tridiagonal_decomposition"
        );

        auto ne = size(e);
        auto nf = size(f);
        auto ng = size(g);

        if constexpr (is_tag_enabled_v<size_assert_t,tag_t>) {
            assert( (ne == nf) && (e[0]   ==0) );
            assert( (ng == nf) && (g[ng-1]==0) );
        }

        auto l = zeros_like(e);
        auto u = zeros_like(f);

        u[0] = f[0];
        for (int i=1; i<nf; i++) {
            l[i] = e[i] / u[i-1];
            u[i] = f[i] - l[i] * g[i-1];
        }

        return std::make_tuple(l,u);
    }

    /**
     * @brief perform forward substitution for tridiagonal system
     * 
     * @tparam L vector-like
     * @tparam B vector-like
     * @param l decomposed lower diagonal entry
     * @param b original result vector
     * @return constexpr auto L, substituted result vector
     * @cite chapra2014numerical_tridiagonal_systems
     */
    template <typename L, typename B>
    constexpr auto tridiagonal_substitution(const L& l, const B& b)
    {
        static_assert(
            is_array1d_v<L> && is_array1d_v<B>,
            "unsupported type E for tridiagonal_substitution"
        );

        auto d = clone(b);
        auto n = size(l);
        for (size_t i=1; i<n; i++)
            d[i] = b[i] - l[i] * d[i-1];
        return d;
    }

    /**
     * @brief perfom backward substitution for tridiagonal sytem
     * 
     * @tparam U vector-like
     * @tparam G vector-like
     * @tparam D vector-like
     * @param u upper elements of decomposed matrix
     * @param g upper element of original matrix
     * @param d substituted result vector
     * @return constexpr auto 
     * @cite chapra2014numerical_tridiagonal_systems
     */
    template <typename U, typename G, typename D>
    constexpr auto tridiagonal_backward(const U& u, const G& g, const D& d)
    {
        static_assert(
            is_array1d_v<U> && is_array1d_v<G> && is_array1d_v<D>,
            "unsupported types for tridiagonal_backward"
        );

        auto x = zeros_like(d);
        auto n = size(d);
        
        x[n-1] = d[n-1] / u[n-1];
        for (int i=n-2; i>=0; i--)
            x[i] = (d[i] - g[i] * x[i+1]) / u[i];
        return x;
    }

    /**
     * @brief perform elimination on tridiagonal system
     * 
     * @tparam E vector-like
     * @tparam F vector-like
     * @tparam G vector-like
     * @tparam B vector-like
     * @param e lower elements (A_{1,0}, A_{2,0}, ...), e[0] should be zero
     * @param f diagonal elements (A_{0,0}, A_{1,1}, ...)
     * @param g upper elements (A_{0,1}, A{1,2}, ...), g[n-1] should be zero
     * @param b right hand side vector
     * @return constexpr auto x
     * @cite chapra2014numerical_tridiagonal_systems
     */
    template <typename tag_t=size_assert_t, typename E, typename F, typename G, typename B>
    constexpr auto tridiagonal_elimination(const E& e, const F& f, const G& g, const B& b)
    {
        auto [l,u] = tridiagonal_decomposition<tag_t>(e,f,g);
        auto d = tridiagonal_substitution(l,b);
        auto x = tridiagonal_backward(u,g,d);
        return x;
    }

} // nmtools::linalg

#endif // NMTOOLS_LINALG_ELIMINATION_HPP