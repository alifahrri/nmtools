#ifndef NMTOOLS_LINALG_ELIMINATION_HPP
#define NMTOOLS_LINALG_ELIMINATION_HPP

#include "nmtools/utility/helper.hpp"
#include "nmtools/utility/tag.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/blas.hpp"
#include "nmtools/array/utility.hpp"

#include <map>
#include <tuple>
#include <string>
#include <algorithm> // for std::max
#include <unordered_map>

namespace nmtools::linalg {

    /* reduce verbosity for nmtools::blas functions */
    using namespace ::nmtools::blas;

    using std::size;
    using helper::log;

    using std::max;
    using std::tuple;
    using std::is_base_of;
    using std::is_base_of_v;
    using std::common_type_t;
    using std::is_null_pointer_v;

    using meta::get_container_value_type_t;
    using meta::remove_cvref_t;
    using meta::is_multiplicative_v;
    using meta::is_array1d_v;

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
            is_null_pointer_v<Scales>
            || is_array1d_v<Scales>,
            "unsupported type for scales"
        );
        static_assert(
            meta::is_array2d_v<Matrix>
            && is_array1d_v<Vector>
            /* TODO: helpful error message here */
        );
        
        constexpr auto use_scales_v = !is_null_pointer_v<Scales>;

        /* TODO: assert if len(A) == len(b) == len(scales) */
        // auto n = size(A);
        /* TODO: rename to [rows,cols] */
        auto [n,m] = matrix_size(A);
        /* selected pivot row */
        auto p = k;

        /* initial value at init pivot row */
        auto big = fabs(at(A,k,k));
        if constexpr (use_scales_v)
            big = big / at(scales,k);
        
        /* find best pivot point, starting at row k+1 down to n */
        for (auto ii=k+1; ii<n; ii++) {
            auto dummy = fabs(at(A,ii,k));
            if constexpr (use_scales_v)
                dummy = dummy / at(scales,ii);
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
                    auto dummy  = at(A_,p,jj);
                    at(A_,p,jj) = at(A_,k,jj);
                    at(A_,k,jj) = dummy;
                }
                /* TODO: consider using swap() */
                auto dummy = at(b,k);
                at(b_,k)   = at(b,p);
                at(b_,p)   = dummy;

                if constexpr (use_scales_v) {
                    auto dummy = at(scales,k);
                    at(s_,k) = at(scales,p);
                    at(s_,p) = dummy;
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
        //     if constexpr (meta::has_tuple_size_v<Matrix>) {
                
        //     } else {

        //     }        
        // }
        /* only return pivot row index */
        else {
            return p;
        }
    } // constexpr auto partial_pivot(Matrix A, Vector b, auto k, Scales scales=Scales{}, pivot_tag=pivot_tag{})

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

        // using namespace std::string_literals;

        /* make sure elimination tag is valid */
        static_assert(
            is_elimination_v<elimination_tag>, 
            "unsupported forward_elimination tag"
        );

        static_assert(
            meta::is_array2d_v<Matrix>
            && meta::is_array1d_v<Vector>
            /* TODO: helpful error message here */
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

        auto Ae = blas::clone(A);
        auto be = blas::clone(b);

        using matrix_t = remove_cvref_t<decltype(Ae)>;
        using vector_t = remove_cvref_t<decltype(be)>;

        using a_t = meta::get_matrix_value_type_t<matrix_t>;
        using b_t = meta::get_vector_value_type_t<vector_t>;
        using common_t = common_type_t<a_t,b_t>;
        // using mapping_t = std::map<std::string,common_t>;

        /* check if Scales is valid type */
        using scale_t = remove_cvref_t<get_container_value_type_t<Scales>>;
        static_assert(
            is_multiplicative_v<common_t,scale_t>
            || is_null_pointer_v<Scales>, 
            "unsupported type for scales"
        );

        /* check if we should log intermediate value */
        /* TODO: check if logger is actually callable with mapping_t */
        // constexpr auto log_v = !is_null_pointer_v<Logger>;
        
        /* TODO: assert if A is square matrix */
        // auto n = size(A);
        /* TODO: rename to [rows, cols] */
        auto [n,m] = matrix_size(A);

        /* placeholder for result */
        // matrix_t Ae{};
        // vector_t be{};
        // if constexpr (meta::is_bounded_array_v<Matrix>) {
        //     /* convert from raw array to std::array */
        //     for (size_t i=0; i<n; i++) {
        //         be[i] = b[i];
        //         for (size_t j=0; j<size(Ae[0]); j++)
        //             Ae[i][j] = A[i][j];
        //     }
        // } else {
        //     /* we will just copy otherwise */
        //     Ae = A;
        //     be = b;
        // }

        /* scales will be used for determining pivot point,
            but actually optional with default type nullptr_t */
        /* TODO: consider to make distinct no-op type for optional scales */
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
            // if constexpr (log_v)
            //     log(logger, mapping_t{{"k"s, k}});

            /* moves below the pivot to each of subsequent rows where elimination takes place */
            for (size_t i=k+1; i<n; i++) {    // row

                /* compute scale factor that will eliminate row i column k*/
                auto factor = at(Ae,i,k) / at(Ae,k,k);
                // if constexpr (log_v)
                //     log(logger, mapping_t{{"factor"s, factor}, {"i"s, i}});

                /* progresses across column to eliminate or transform the elements */
                for (size_t j=k+1; j<n; j++) {
                    at(Ae,i,j) = at(Ae,i,j) - factor * at(Ae,k,j);
                    /* optional logging */
                    // if constexpr (log_v)
                    //     log(logger, mapping_t{{"A[i][j]"s, Ae[i][j]}, {"j"s, j}});
                }
                at(be,i) = at(be,i) - factor * at(be,k);

                /* conditional compilation to store 
                    lower matrix (esp. for decomposition) */
                if constexpr (keep_lower_v)
                    at(Ae,i,k) = factor;
                else
                    at(Ae,i,k) = 0;
            }
        }

        return std::make_tuple(Ae,be);
    } // constexpr auto forward_elimination

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
        static_assert(
            meta::is_array2d_v<Matrix>
            && meta::is_array1d_v<Vector>
            /* TODO: helpful error message here */
        );
        // using namespace std::string_literals;
        // using mapping_t = std::map<std::string,common_t>;
        /* TODO: make sure A is square matrix */
        // auto n = size(b);
        auto n = vector_size(b);

        /* placeholder for result */
        auto x = zeros_like(b);
        using result_t = remove_cvref_t<decltype(x)>;
        using a_t = meta::get_matrix_value_type_t<Matrix>;
        using b_t = meta::get_vector_value_type_t<Vector>;
        using r_t = meta::get_vector_value_type_t<result_t>;
        using common_t = common_type_t<a_t,b_t,r_t>;
        /* solve first element */
        at(x,n-1) = at(b,n-1) / at(A,n-1,n-1);

        /* check if we should log intermediate value */
        // constexpr auto log = !is_null_pointer_v<Logger>;

        /* TODO: actually log intermediate value */
        for (int i=n-2; i>=0; i--) {
            common_t sum = at(b,i);
            for (int j=i+1; j<n; j++)
                sum -= at(A,i,j) * at(x,j);
            at(x,i) = sum / at(A,i,i);
        }
        return x;
    } // constexpr auto backward_substitution

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
        static_assert(
            meta::is_array2d_v<Matrix>
            && meta::is_array1d_v<Vector>
            /* TODO: helpful error message here */
        );
        auto [Ae,be] = forward_elimination(A,b,logger);
        auto x = backward_substitution(Ae,be);
        return x;
    } // constexpr auto naive_gauss_elimination

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
        static_assert(
            meta::is_array2d_v<Matrix>
            && meta::is_array1d_v<Vector>
            /* TODO: helpful error message here */
        );

        /* TODO: check if A & b has the same row */
        // auto n = size(A);
        auto [rows,cols] = matrix_size(A);

        auto A_abs = fabs(A);
        auto s = zeros_like(b);

        /* TODO: find-out better way to perform this op */
        for (size_t i=0; i<rows; i++)
            for (size_t j=0; j<cols; j++)
                at(s,i) = max(at(A_abs,i,j),at(s,i));
        
        /* perform forward elimination with pivot and scaling */
        using elimination_t = etag::elimination_with_pivot_t;

        auto [Ae, be] = forward_elimination<elimination_t>(A,b,s);
        auto x = backward_substitution(Ae,be);

        return x;
    } // constexpr auto gauss_elimination

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
            is_array1d_v<E>
            && is_array1d_v<F>
            && is_array1d_v<G>,
            "unsupported types for tridiagonal system elimination"
        );

        static_assert(
            is_assert_v<tag_t>,
            "unsupported tag for tridiagonal_decomposition"
        );

        auto ne = vector_size(e);
        auto nf = vector_size(f);
        auto ng = vector_size(g);

        if constexpr (is_tag_enabled_v<size_assert_t,tag_t>) {
            assert( (ne == nf) && (at(e,0)   ==0) );
            assert( (ng == nf) && (at(g,ng-1)==0) );
        }

        auto l = zeros_like(e);
        auto u = zeros_like(f);

        at(u,0) = at(f,0);
        for (int i=1; i<nf; i++) {
            at(l,i) = at(e,i) / at(u,i-1);
            at(u,i) = at(f,i) - at(l,i) * at(g,i-1);
        }

        return std::make_tuple(l,u);
    } // constexpr auto tridiagonal_decomposition

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
            is_array1d_v<L>
            && is_array1d_v<B>,
            "unsupported type E for tridiagonal_substitution"
        );

        auto d = clone(b);
        auto n = vector_size(l);
        for (size_t i=1; i<n; i++)
            at(d,i) = at(b,i) - at(l,i) * at(d,i-1);
        return d;
    } // constexpr auto tridiagonal_substitution

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
            is_array1d_v<U>
            && is_array1d_v<G>
            && is_array1d_v<D>,
            "unsupported types for tridiagonal_backward"
        );

        auto x = zeros_like(d);
        auto n = vector_size(d);
        
        at(x,n-1) = at(d,n-1) / at(u,n-1);
        for (int i=n-2; i>=0; i--)
            at(x,i) = (at(d,i) - at(g,i) * at(x,i+1)) / at(u,i);
        return x;
    } // constexpr auto tridiagonal_backward

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
        static_assert(
            is_array1d_v<E>
            && is_array1d_v<F>
            && is_array1d_v<G>
            && is_array1d_v<B>
            /* TODO: helpful error message here */
        );
        auto [l,u] = tridiagonal_decomposition<tag_t>(e,f,g);
        auto d = tridiagonal_substitution(l,b);
        auto x = tridiagonal_backward(u,g,d);
        return x;
    } // constexpr auto tridiagonal_elimination

} // nmtools::linalg

#endif // NMTOOLS_LINALG_ELIMINATION_HPP