#include "nmtools/utl/tuple.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;

TEST_CASE("tuple" * doctest::test_suite("utl"))
{
    SUBCASE("constructor")
    {
        {
            utl::tuple1<double> tp;
            NMTOOLS_ASSERT_CLOSE( tp.value1, 0.0 );
        }
        {
            utl::tuple2<int,double> tp;
            NMTOOLS_ASSERT_EQUAL( tp.value1, 0 );
            NMTOOLS_ASSERT_CLOSE( tp.value2, 0.0 );

            tp.value1 = 1;
            tp.value2 = 1;
            NMTOOLS_ASSERT_EQUAL( tp.value1, 1 );
            NMTOOLS_ASSERT_CLOSE( tp.value2, 1.0 );
        }
        {
            utl::tuple2<int,double> tp{1,1.0};
            NMTOOLS_ASSERT_EQUAL( tp.value1, 1 );
            NMTOOLS_ASSERT_CLOSE( tp.value2, 1.0 );
        }
        {
            auto tp = utl::tuple{1,1.0};
            NMTOOLS_ASSERT_EQUAL( tp.value1, 1 );
            NMTOOLS_ASSERT_CLOSE( tp.value2, 1.0 );
        }
        {
            auto tp = utl::tuple{1,1.0,2};
            NMTOOLS_ASSERT_EQUAL( tp.value1, 1 );
            NMTOOLS_ASSERT_CLOSE( tp.value2, 1.0 );
            NMTOOLS_ASSERT_EQUAL( tp.value3, 2 );
        }
        {
            auto tp = utl::tuple{1,1.0,2,3.0};
            NMTOOLS_ASSERT_EQUAL( tp.value1, 1 );
            NMTOOLS_ASSERT_CLOSE( tp.value2, 1.0 );
            NMTOOLS_ASSERT_EQUAL( tp.value3, 2 );
            NMTOOLS_ASSERT_CLOSE( tp.value4, 3.0 );
        }
        {
            auto tp = utl::tuple{1,1.0,2,3.0,4};
            NMTOOLS_ASSERT_EQUAL( tp.value1, 1 );
            NMTOOLS_ASSERT_CLOSE( tp.value2, 1.0 );
            NMTOOLS_ASSERT_EQUAL( tp.value3, 2 );
            NMTOOLS_ASSERT_CLOSE( tp.value4, 3.0 );
            NMTOOLS_ASSERT_EQUAL( tp.value5, 4 );
        }

        // copy constructor
        {
            auto tp = utl::tuple{1,2,3};
            using new_tuple_t = utl::tuple<int,int,int>;
            auto new_tp = new_tuple_t(tp);

            NMTOOLS_ASSERT_EQUAL( new_tp.value1, 1 );
            NMTOOLS_ASSERT_EQUAL( new_tp.value2, 2 );
            NMTOOLS_ASSERT_EQUAL( new_tp.value3, 3 );
        }
        {
            auto tp = utl::tuple{1,2,3};
            using new_tuple_t = utl::tuple<int,int,int>;
            new_tuple_t new_tp = tp;

            NMTOOLS_ASSERT_EQUAL( new_tp.value1, 1 );
            NMTOOLS_ASSERT_EQUAL( new_tp.value2, 2 );
            NMTOOLS_ASSERT_EQUAL( new_tp.value3, 3 );
        }
    }

    SUBCASE("get")
    {
        {
            auto tp = utl::tuple{1,1.0};
            NMTOOLS_ASSERT_EQUAL( utl::get<0>(tp), 1 );
            NMTOOLS_ASSERT_CLOSE( utl::get<1>(tp), 1.0 );

            utl::get<0>(tp) = 2;
            utl::get<1>(tp) = 3;

            NMTOOLS_ASSERT_EQUAL( utl::get<0>(tp), 2 );
            NMTOOLS_ASSERT_CLOSE( utl::get<1>(tp), 3.0 );
        }
        {
            auto tp = utl::tuple{1,1.0,2};
            NMTOOLS_ASSERT_EQUAL( utl::get<0>(tp), 1 );
            NMTOOLS_ASSERT_CLOSE( utl::get<1>(tp), 1.0 );
            NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp), 2 );
        }
        {
            auto tp = utl::tuple<int,float,unsigned char>{1,1.0,2};
            NMTOOLS_ASSERT_EQUAL( utl::get<0>(tp), 1 );
            NMTOOLS_ASSERT_CLOSE( utl::get<1>(tp), 1.0 );
            NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp), 2 );
        }
        {
            auto tp = utl::tuple{1,1.0,2,3.0};
            NMTOOLS_ASSERT_EQUAL( utl::get<0>(tp), 1 );
            NMTOOLS_ASSERT_CLOSE( utl::get<1>(tp), 1.0 );
            NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp), 2 );
            NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp), 3.0 );

            [[maybe_unused]] const auto& [a,b,c,d] = tp;

            utl::get<0>(tp) = 2;
            utl::get<1>(tp) = 3;

            // current impl of NMTOOLS_ASSERT_ makes it unusable on clang,
            // complaining about reference to local bindings

            // NMTOOLS_ASSERT_EQUAL( a, 2 );
            // NMTOOLS_ASSERT_CLOSE( b, 3.0 );
            CHECK( a == 2);
        }
        {
            auto tp = utl::tuple{1,1.0,2,3.0,4};
            NMTOOLS_ASSERT_EQUAL( utl::get<0>(tp), 1 );
            NMTOOLS_ASSERT_CLOSE( utl::get<1>(tp), 1.0 );
            NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp), 2 );
            NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp), 3.0 );
            NMTOOLS_ASSERT_EQUAL( utl::get<4>(tp), 4 );
        }
    }
}