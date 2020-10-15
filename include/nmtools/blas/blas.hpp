#ifndef NMTOOLS_BLAS_BLAS_HPP
#define NMTOOLS_BLAS_BLAS_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools::blas {

    namespace detail {
        /**
         * @brief make array
         * 
         * @tparam Args 
         * @param args 
         * @return std::array<std::common_type_t<Args...>, sizeof...(Args)> 
         * @todo remove
         */
        template <typename... Args>
        constexpr auto make_array(Args&&... args)
        {
            using common_t = std::common_type_t<Args...>;
            using return_t = std::array<common_t, sizeof...(Args)>;
            return return_t{{std::forward<Args>(args)...}};
        } // constexpr auto make_array(Args&&... args)

    } // namespace detail

    /* make symbols accessible for unqualified-lookup */
    using std::get;
    using std::size;
    using std::fabs;
    using std::sqrt;
    using std::tuple_size;
    using std::tuple_size_v;

    /** @defgroup blas
    * Collections of blas functions.
    * @{
    */
    
    /**
     * @brief make zeros array
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::zeros;

    /**
     * @brief zeros_like
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::zeros_like;

    /**
     * @brief create matrix/vector filled with 1s
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::ones_like;

    /**
     * @brief compute matrix transpose
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::transpose;

    /**
     * @brief clone
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::clone;

    /**
     * @brief make identity matrix
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::identity;

    /**
     * @brief max-element
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::max;

    /**
     * @brief sum-element
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::sum;

    /**
     * @brief sumsq
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::sumsq;

    /**
     * @brief perform row sum operation, similar to `sum(A,1)` in octave.
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::row_sum;

    /**
     * @brief perform column sum operation
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::col_sum;

    /**
     * @brief elementwise absolute value
     * 
     * @note implementation moved to array utility, provided here as backward-compatibility
     * @todo remove
     */
    using nmtools::fabs;

    /** @} */ // end group blas
} // namespace nmtools::blas

#include "nmtools/blas/blas/tag.hpp"

#include "nmtools/blas/blas/dot.hpp"
#include "nmtools/blas/blas/outer.hpp"
#include "nmtools/blas/blas/vsmul.hpp"
#include "nmtools/blas/blas/msmul.hpp"
#include "nmtools/blas/blas/mvmul.hpp"
#include "nmtools/blas/blas/mmmul.hpp"
#include "nmtools/blas/blas/vvadd.hpp"
#include "nmtools/blas/blas/mmadd.hpp"

#include "nmtools/blas/blas/mul.hpp"
#include "nmtools/blas/blas/add.hpp"
#include "nmtools/blas/blas/saxpy.hpp"
#include "nmtools/blas/blas/gaxpy.hpp"
#include "nmtools/blas/blas/norm.hpp"

namespace std {
    /**
     * @ingroup blas
     * @brief overload to std::to_string for nmtools::blas::norm_t
     * 
     * @param norm norm kind
     * @return std::string "infinity" or "frobenius"
     * @note defined as inline to avoid linking error
     */
    inline std::string to_string(nmtools::blas::norm_t norm) {
        using nmtools::blas::norm_t;
        if (norm == norm_t::infinity_norm)
            return "infinity_norm";
        else if (norm == norm_t::frobenius_norm)
            return "frobenius_norm";
    }
}

#endif // NMTOOLS_BLAS_BLAS_HPP
