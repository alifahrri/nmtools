#include "nmtools/array/index/choose.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("choose(array,array)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = std::array<size_t,4>;
        using arr_t = std::array<double,4>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(vector,vector)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = std::vector<size_t>;
        using arr_t = std::vector<double>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(tuple,tuple)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = std::tuple<size_t,size_t,size_t,size_t>;
        using arr_t = std::tuple<double,double,double>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(vector,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = std::vector<size_t>;
        using arr_t = std::array<double,4>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::vector<size_t>;
        using arr_t = std::tuple<double,float,double>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::vector<size_t>;
        using arr_t = std::tuple<size_t,float,double,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::vector<size_t>;
        using arr_t = std::tuple<size_t,float,double,int,std::vector<int>>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::vector<size_t>;
        using arr_t = na::hybrid_ndarray<double,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(array,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = std::array<size_t,4>;
        using arr_t = std::vector<double>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::array<size_t,4>;
        using arr_t = std::tuple<double,float,double>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::array<size_t,3>;
        using arr_t = std::tuple<double,float,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::array<size_t,3>;
        using arr_t = std::tuple<double,float,std::tuple<int>>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::array<size_t,3>;
        using arr_t = na::hybrid_ndarray<double,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(tuple,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = std::tuple<size_t,size_t,size_t,size_t>;
        using arr_t = std::vector<double>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::tuple<size_t,size_t,size_t>;
        using arr_t = std::array<double,4>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = std::tuple<size_t,size_t,size_t>;
        using arr_t = na::hybrid_ndarray<double,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(hybrid_ndarray,hybrid_ndarray)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = na::hybrid_ndarray<double,5,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = na::hybrid_ndarray<double,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(hybrid_ndarray,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = std::vector<double>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = na::hybrid_ndarray<double,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = std::array<double,5>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = na::hybrid_ndarray<double,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = std::tuple<double,int,float>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = na::hybrid_ndarray<double,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = std::tuple<double,int,float,std::tuple<int>>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}