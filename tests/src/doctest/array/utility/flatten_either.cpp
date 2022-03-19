#include "nmtools/utility/flatten_either.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>

namespace nm = nmtools;

using nmtools_array;

TEST_CASE("flatten_either")
{
    {
        using either_t = nmtools_either<float,array<float,2>>;
        auto either = either_t{1.2f};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd] = nm::flatten_either(either);
        #endif
        CHECK(  static_cast<bool>(ptr_1st) );
        CHECK( !static_cast<bool>(ptr_2nd) );
    }
    {
        using array_t  = array<float,2>;
        using either_t = nmtools_either<float,array_t>;
        auto either = either_t{array_t{1.2f,3.4f}};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd] = nm::flatten_either(either);
        #endif
        CHECK( !static_cast<bool>(ptr_1st) );
        CHECK(  static_cast<bool>(ptr_2nd) );
    }
    {
        using array_t  = array<float,2>;
        using vector_t = std::vector<int>;
        using right_t  = nmtools_either<array_t,vector_t>;
        using either_t = nmtools_either<float,right_t>;
        auto either = either_t{right_t{array_t{1.2f,3.4f}}};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        auto ptr_3rd = nm::get<2>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd, ptr_3rd] = nm::flatten_either(either);
        #endif
        CHECK( !static_cast<bool>(ptr_1st) );
        CHECK(  static_cast<bool>(ptr_2nd) );
        CHECK( !static_cast<bool>(ptr_3rd) );
    }
    {
        using array_t  = array<float,2>;
        using vector_t = std::vector<int>;
        using right_t  = nmtools_either<array_t,vector_t>;
        using either_t = nmtools_either<float,right_t>;
        auto either = either_t{right_t{vector_t{1,3}}};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        auto ptr_3rd = nm::get<2>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd, ptr_3rd] = nm::flatten_either(either);
        #endif
        CHECK( !static_cast<bool>(ptr_1st) );
        CHECK( !static_cast<bool>(ptr_2nd) );
        CHECK(  static_cast<bool>(ptr_3rd) );
    }
    {
        using array_t  = array<float,2>;
        using vector_t = std::vector<int>;
        using right_t  = nmtools_either<array_t,vector_t>;
        using either_t = nmtools_either<float,right_t>;
        auto either = either_t{1.2f};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        auto ptr_3rd = nm::get<2>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd, ptr_3rd] = nm::flatten_either(either);
        #endif
        CHECK(  static_cast<bool>(ptr_1st) );
        CHECK( !static_cast<bool>(ptr_2nd) );
        CHECK( !static_cast<bool>(ptr_3rd) );
    }
    {
        using l_array_t  = array<float,2>;
        using l_vector_t = std::vector<int>;
        using r_array_t  = array<int,2>;
        using r_vector_t = std::vector<float>;
        using left_t   = nmtools_either<l_array_t,l_vector_t>;
        using right_t  = nmtools_either<r_array_t,r_vector_t>;
        using either_t = nmtools_either<left_t,right_t>;
        auto either = either_t{left_t{l_array_t{1.2f,3.4f}}};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        auto ptr_3rd = nm::get<2>(nm::flatten_either(either));
        auto ptr_4th = nm::get<3>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd, ptr_3rd, ptr_4th] = nm::flatten_either(either);
        #endif
        CHECK(  static_cast<bool>(ptr_1st) );
        CHECK( !static_cast<bool>(ptr_2nd) );
        CHECK( !static_cast<bool>(ptr_3rd) );
        CHECK( !static_cast<bool>(ptr_4th) );
    }
    {
        using l_array_t  = array<float,2>;
        using l_vector_t = std::vector<int>;
        using r_array_t  = array<int,2>;
        using r_vector_t = std::vector<float>;
        using left_t   = nmtools_either<l_array_t,l_vector_t>;
        using right_t  = nmtools_either<r_array_t,r_vector_t>;
        using either_t = nmtools_either<left_t,right_t>;
        auto either = either_t{left_t{l_vector_t{1,3}}};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        auto ptr_3rd = nm::get<2>(nm::flatten_either(either));
        auto ptr_4th = nm::get<3>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd, ptr_3rd, ptr_4th] = nm::flatten_either(either);
        #endif
        CHECK( !static_cast<bool>(ptr_1st) );
        CHECK(  static_cast<bool>(ptr_2nd) );
        CHECK( !static_cast<bool>(ptr_3rd) );
        CHECK( !static_cast<bool>(ptr_4th) );
    }
    {
        using l_array_t  = array<float,2>;
        using l_vector_t = std::vector<int>;
        using r_array_t  = array<int,2>;
        using r_vector_t = std::vector<float>;
        using left_t   = nmtools_either<l_array_t,l_vector_t>;
        using right_t  = nmtools_either<r_array_t,r_vector_t>;
        using either_t = nmtools_either<left_t,right_t>;
        auto either = either_t{right_t{r_array_t{1,3}}};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        auto ptr_3rd = nm::get<2>(nm::flatten_either(either));
        auto ptr_4th = nm::get<3>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd, ptr_3rd, ptr_4th] = nm::flatten_either(either);
        #endif
        CHECK( !static_cast<bool>(ptr_1st) );
        CHECK( !static_cast<bool>(ptr_2nd) );
        CHECK(  static_cast<bool>(ptr_3rd) );
        CHECK( !static_cast<bool>(ptr_4th) );
    }
    {
        using l_array_t  = array<float,2>;
        using l_vector_t = std::vector<int>;
        using r_array_t  = array<int,2>;
        using r_vector_t = std::vector<float>;
        using left_t   = nmtools_either<l_array_t,l_vector_t>;
        using right_t  = nmtools_either<r_array_t,r_vector_t>;
        using either_t = nmtools_either<left_t,right_t>;
        auto either = either_t{right_t{r_vector_t{1,3}}};
        // newer doctest (v2.4.8) CHECK macro def breaks this on clang :(
        #if __clang__
        auto ptr_1st = nm::get<0>(nm::flatten_either(either));
        auto ptr_2nd = nm::get<1>(nm::flatten_either(either));
        auto ptr_3rd = nm::get<2>(nm::flatten_either(either));
        auto ptr_4th = nm::get<3>(nm::flatten_either(either));
        #else
        auto [ptr_1st, ptr_2nd, ptr_3rd, ptr_4th] = nm::flatten_either(either);
        #endif
        CHECK( !static_cast<bool>(ptr_1st) );
        CHECK( !static_cast<bool>(ptr_2nd) );
        CHECK( !static_cast<bool>(ptr_3rd) );
        CHECK(  static_cast<bool>(ptr_4th) );
    }
}