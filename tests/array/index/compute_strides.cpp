#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"
#include <array>
#include <vector>

using nmtools::utils::isequal;
using namespace nmtools::literals;

TEST_CASE("compute_strides" * doctest::test_suite("index"))
{
    /**
     * @code{.py}
     * >>> np.ndarray((3,)).shape
     * (8,)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2)).shape
     * (16,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3,2};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,1)).shape
     * (16,8,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3,2,1};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,3)).shape
     * (48, 24, 8)
     * @endcode
     * 
     */
    {
        auto shape   = std::array{3,2,3};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_strides(std::vector)" * doctest::test_suite("index"))
{
    /**
     * @code{.py}
     * >>> np.ndarray((3,)).shape
     * (8,)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2)).shape
     * (16,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3,2};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,1)).shape
     * (16,8,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3,2,1};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,3)).shape
     * (48, 24, 8)
     * @endcode
     * 
     */
    {
        auto shape   = std::vector{3,2,3};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_strides(std::tuple)" * doctest::test_suite("index"))
{
    /**
     * @code{.py}
     * >>> np.ndarray((3,)).shape
     * (8,)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2)).shape
     * (16,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3,2};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,1)).shape
     * (16,8,8)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3,2,1};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1,1}) );
    }
    /**
     * @code{.py}
     * >>> np.ndarray((3,2,3)).shape
     * (48, 24, 8)
     * @endcode
     * 
     */
    {
        auto shape   = std::tuple{3,2,3};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}

TEST_CASE("compute_strides(std::tuple<integral_constant>)" * doctest::test_suite("index"))
{
    {
        auto shape   = std::tuple{3_ct};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{1}) );
    }
    {
        auto shape   = std::tuple{3_ct,2_ct};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1}) );
    }
    {
        auto shape   = std::tuple{3_ct,2_ct,1_ct};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{2,1,1}) );
    }
    {
        auto shape   = std::tuple{3_ct,2_ct,3_ct};
        auto strides = nmtools::index::compute_strides(shape);
        CHECK( isequal(strides,std::array{6,3,1}) );
    }
}