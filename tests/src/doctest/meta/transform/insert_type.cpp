#include "nmtools/meta.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("insert_type" * doctest::test_suite("meta"))
{
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = double;
        using res_t = meta::insert_type_t<arg_t,new_t,1>;
        using exp_t = std::tuple<size_t,new_t,int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = double;
        using res_t = meta::insert_type_t<arg_t,new_t,0>;
        using exp_t = std::tuple<new_t,size_t,int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = double;
        using res_t = meta::insert_type_t<arg_t,new_t,2>;
        using exp_t = std::tuple<size_t,int,new_t>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = double;
        using res_t = meta::insert_type_t<arg_t,new_t,3>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = double;
        using res_t = meta::insert_type_t<arg_t,new_t,-3>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = meta::ct<1>;
        using res_t = meta::insert_type_t<arg_t,new_t,1>;
        using exp_t = std::tuple<size_t,new_t,int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = meta::ct<1>;
        using res_t = meta::insert_type_t<arg_t,new_t,0>;
        using exp_t = std::tuple<new_t,size_t,int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using arg_t = std::tuple<size_t,int>;        
        using new_t = meta::ct<1>;
        using res_t = meta::insert_type_t<arg_t,new_t,2>;
        using exp_t = std::tuple<size_t,int,new_t>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}