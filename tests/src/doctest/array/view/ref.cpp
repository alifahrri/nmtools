#include "doctest/doctest.h"
#include "nmtools/array/view.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/utility/helper.hpp"
#include "testing/testing.hpp"

#include <array>
#include <vector>

namespace view = nmtools::view;
using nmtools::helper::isclose;
using nmtools::array::fixed_vector;
using nmtools::array::fixed_matrix;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_vector;
using nmtools::array::dynamic_matrix;
using nmtools::array::dynamic_ndarray;

TEST_CASE("view::ref")
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( array_ref(0)==1 );

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );
}

TEST_CASE("view::ref")
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::ref(array);
    CHECK(array_ref.dim()==2);
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{2,3}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );
}

TEST_CASE("view::ref")
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( array_ref(0)==1 );
    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );
}

TEST_CASE("view::ref")
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(),std::array{2,3}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );
}

TEST_CASE("view::ref")
{
    auto array = fixed_vector<double,3>{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    CHECK( array_ref(0)==1 );
    CHECK( nmtools::at(array_ref,0)==1 );

    nmtools::at(array,0) = 3;

    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );
}

TEST_CASE("view::ref")
{
    auto array = fixed_matrix<double,3,2>{};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(), std::array{3,2}) );
}

TEST_CASE("view::ref")
{
    auto array = dynamic_vector{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( nmtools::at(array_ref,0)==1 );

    nmtools::at(array,0) = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );
}

TEST_CASE("view::ref")
{
    auto array = dynamic_matrix{
        {1.,2.,3.},
        {3.,4.,5.},
    };
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(), std::array{2,3}) );
}

TEST_CASE("view::ref")
{
    auto array = fixed_ndarray<double,3>{1.,2.,3.};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    array = std::array{1.,2.,3.};
}

TEST_CASE("view::ref")
{
    auto array = fixed_ndarray<double,3,2>{};
    auto array_ref = view::ref(array);

    array = std::array{
        std::array{1.,2.},
        std::array{3.,4.},
        std::array{4.,5.},
    };

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(),std::array{3,2}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );
}

TEST_CASE("view::ref")
{
    auto array = fixed_ndarray<double,3,2,4>{};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isclose(array_ref.shape(),std::array{3,2,4}) );

    // @todo provide constructor/assignment op from 3D array

    nmtools::at(array,0,1,0) = 6;
    CHECK( array_ref(0,1,0)==6 );
}

TEST_CASE("view::ref")
{
    auto array = fixed_ndarray<double,3,2,4,1>{};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isclose(array_ref.shape(),std::array{3,2,4,1}) );

    // @todo provide constructor/assignment op from 3D array

    nmtools::at(array,0,1,3,0) = 6;
    CHECK( array_ref(0,1,3,0)==6 );
}

TEST_CASE("view::ref")
{
    auto array = dynamic_ndarray({1.,2.,3.});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );
}

TEST_CASE("view::ref")
{
    auto array = dynamic_ndarray({
        {1.,2.,3.},
        {3.,4.,5.}
    });
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(),std::array{2,3}) );
}

TEST_CASE("view::ref")
{
    auto array = dynamic_ndarray({1.,2.,3.},{1,3,1});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isclose(array_ref.shape(),std::array{1,3,1}) );

    // @todo provide constructor/assignment op from 3D array
}

TEST_CASE("view::ref")
{
    auto array = dynamic_ndarray({1.,2.,3.,4.},{1,2,2,1});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isclose(array_ref.shape(),std::array{1,2,2,1}) );

    // @todo provide constructor/assignment op from 3D array

    CHECK( array_ref(0,1,1,0)==4 );
    nmtools::at(array,0,1,1,0) = 6;
    CHECK( array_ref(0,1,1,0)==6 );
}