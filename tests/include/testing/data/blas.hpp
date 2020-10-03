#ifndef NMTOOLS_TESTING_DATA_BLAS_HPP
#define NMTOOLS_TESTING_DATA_BLAS_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include "testing/data/blas/col_sum.hpp"
#include "testing/data/blas/dot.hpp"
#include "testing/data/blas/matrix_norm.hpp"
#include "testing/data/blas/mmadd.hpp"
#include "testing/data/blas/mmmul.hpp"
#include "testing/data/blas/mvmul.hpp"
#include "testing/data/blas/ones_like.hpp"
#include "testing/data/blas/outer.hpp"
#include "testing/data/blas/row_sum.hpp"
#include "testing/data/blas/sum.hpp"
#include "testing/data/blas/transpose.hpp"
#include "testing/data/blas/vvadd.hpp"
#include "testing/data/blas/zeros_like.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

namespace nmtools::testing::data::blas::vector_norm
{
    template <typename T=double>
    constexpr T x[3] = {1,2,3};

    /**
     * @brief test data for p-2 norm
     * ocvtave:> norm([1,2,3])
     * 
     */
    namespace case1
    {
        namespace args {
            // allow testing using raw array
            using ::nmtools::testing::data::blas::vector_norm::x;
            NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x);
            NMTOOLS_TESTING_DATA_DECLARE_VEC(x,3);
            inline constexpr auto p = 2;
        } // namespace args
        namespace expect {
            constexpr auto norm = 3.741657386773941e+00;
        }
    } // namespace vector_norm_2
    /**
     * @brief test data for p-1 norm
     * ocvtave:> norm([1,2,3],1)
     * 
     */
    namespace case2
    {
        namespace args {
            // allow testing using raw array
            using ::nmtools::testing::data::blas::vector_norm::x;
            NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x);
            NMTOOLS_TESTING_DATA_DECLARE_VEC(x,3);
            inline constexpr auto p = 1;
        } // namespace args
        namespace expect {
            inline constexpr auto norm = 6;
        }
    }
    /**
     * @brief test data for p-inf norm
     * ocvtave:> norm([1,2,3],'inf')
     * 
     */
    namespace case3
    {
        namespace args {
            // allow testing using raw array
            using ::nmtools::testing::data::blas::vector_norm::x;
            NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x);
            NMTOOLS_TESTING_DATA_DECLARE_VEC(x,3);
            inline constexpr auto p = ::nmtools::blas::norm_t::infinity_norm;
        } // namespace args
        namespace expect {
            inline constexpr auto norm = 3;
        }
    }
} // namespace nmtools::testing::data::blas

#endif // NMTOOLS_TESTING_DATA_BLAS_HPP