#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/blas.hpp"
// NOTE: need to include utility for std::array fixed_size specialization
#include "nmtools/array/utility.hpp"
#include "testing/testing.hpp"

#include "doctest/doctest.h"
#include <array>

namespace blas = nmtools::blas;
namespace meta = nmtools::meta;
namespace meta = nmtools::meta;

TEST_CASE("mmmul_select_resizeable_t" * doctest::test_suite("blas::mmadd"))
{
    using mvector_t  = std::vector<std::vector<double>>;
    using marray_t   = std::array<std::array<double,3>,5>;
    using fvector_t  = nmtools::array::fixed_vector<double,3>;
    using fmatrix_t  = nmtools::array::fixed_matrix<double,5,3>;
    using dvector_t  = nmtools::array::dynamic_vector<double>;
    using dmatrix_t  = nmtools::array::dynamic_matrix<double>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;

    {
        using lhs_t = dmatrix_t;
        using rhs_t = fmatrix_t;
        using result_t = meta::resolve_optype_t<blas::mmmul_select_resizeable_t,lhs_t,rhs_t>;
        LOG_TYPEINFO(lhs_t);
        LOG_TYPEINFO(rhs_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, dmatrix_t );
    }
    {
        using lhs_t = dmatrix_t;
        using rhs_t = dmatrix_t;
        using result_t = meta::resolve_optype_t<blas::mmmul_select_resizeable_t,lhs_t,rhs_t>;
        LOG_TYPEINFO(lhs_t);
        LOG_TYPEINFO(rhs_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, dmatrix_t );
    }
    {
        using lhs_t = fmatrix_t;
        using rhs_t = fmatrix_t;
        using result_t = meta::resolve_optype_t<blas::mmmul_select_resizeable_t,lhs_t,rhs_t>;
        LOG_TYPEINFO(lhs_t);
        LOG_TYPEINFO(rhs_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, void );
    }
    {
        using lhs_t = mvector_t;
        using rhs_t = marray_t;
        using result_t = meta::resolve_optype_t<blas::mmmul_select_resizeable_t,lhs_t,rhs_t>;
        LOG_TYPEINFO(lhs_t);
        LOG_TYPEINFO(rhs_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, mvector_t );
    }
}