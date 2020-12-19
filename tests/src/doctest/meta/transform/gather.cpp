#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>

namespace nm   = nmtools;
namespace meta = nmtools::meta;
using meta::ct;
using std::tuple;

TEST_CASE("gather" * doctest::test_suite("meta"))
{
    {
        using arg_t      = tuple<int,size_t>;
        using idx_t      = meta::sequence_t<0,1>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = arg_t;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<int,size_t>;
        using idx_t      = meta::sequence_t<1,0>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<size_t,int>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<int,size_t,double>;
        using idx_t      = meta::sequence_t<0,1,2>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = arg_t;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<int,size_t,double>;
        using idx_t      = meta::sequence_t<0,2,1>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<int,double,size_t>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<int,size_t,double>;
        using idx_t      = meta::sequence_t<2,1,0>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<double,size_t,int>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<int,size_t,double>;
        using idx_t      = meta::sequence_t<2,0,1>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<double,int,size_t>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<int,size_t,double>;
        using idx_t      = meta::sequence_t<1,0,2>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<size_t,int,double>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }

    using c_1 = ct<1>;
    using c_2 = ct<2>;
    using c_3 = ct<3>;

    {
        using arg_t      = tuple<c_1,c_2,c_3>;
        using idx_t      = meta::sequence_t<0,1,2>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = arg_t;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<c_1,c_2,c_3>;
        using idx_t      = meta::sequence_t<0,2,1>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<c_1,c_3,c_2>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<c_1,c_2,c_3>;
        using idx_t      = meta::sequence_t<1,0,2>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<c_2,c_1,c_3>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<c_1,c_2,c_3>;
        using idx_t      = meta::sequence_t<1,2,0>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<c_2,c_3,c_1>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<c_1,c_2,c_3>;
        using idx_t      = meta::sequence_t<2,1,0>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<c_3,c_2,c_1>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
    {
        using arg_t      = tuple<c_1,c_2,c_3>;
        using idx_t      = meta::sequence_t<2,0,1>;
        using ret_t      = meta::gather_t<arg_t,idx_t>;
        using expected_t = tuple<c_3,c_1,c_2>;
        STATIC_CHECK_IS_SAME( ret_t, expected_t );
    }
}