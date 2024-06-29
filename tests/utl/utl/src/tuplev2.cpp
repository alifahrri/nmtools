#include "nmtools/utl/tuplev2.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace utl = nm::utl;

TEST_CASE("tuplev2(default_constructor)" * doctest::test_suite("utl"))
{
    utl::tuplev2<double> tp{};

    utl::tuplev2<double,int,unsigned int,float> tp4{};

    utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short> tp8{};

    utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short> tp16{};

    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp)>, 1 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp4)>, 4 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp8)>, 8 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp16)>, 16 );

    {
        using element_t = utl::tuple_element_t<0,decltype(tp)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, double );
    }
    {
        using element_t = utl::tuple_element_t<1,decltype(tp4)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using element_t = utl::tuple_element_t<2,decltype(tp4)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, unsigned int );
    }
    {
        using element_t = utl::tuple_element_t<3,decltype(tp4)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, float );
    }
    {
        using element_t = utl::tuple_element_t<4,decltype(tp8)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, char );
    }
    {
        using element_t = utl::tuple_element_t<5,decltype(tp8)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, unsigned char );
    }
    {
        using element_t = utl::tuple_element_t<6,decltype(tp8)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, short );
    }
    {
        using element_t = utl::tuple_element_t<7,decltype(tp8)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, unsigned short );
    }
    {
        using element_t = utl::tuple_element_t<8,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, double );
    }
    {
        using element_t = utl::tuple_element_t<9,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using element_t = utl::tuple_element_t<10,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, unsigned int );
    }
    {
        using element_t = utl::tuple_element_t<11,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, float );
    }
    {
        using element_t = utl::tuple_element_t<12,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, char );
    }
    {
        using element_t = utl::tuple_element_t<13,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, unsigned char );
    }
    {
        using element_t = utl::tuple_element_t<14,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, short );
    }
    {
        using element_t = utl::tuple_element_t<15,decltype(tp16)>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, unsigned short );
    }
}

TEST_CASE("tuplev2(get)" * doctest::test_suite("utl"))
{
    utl::tuplev2<double> tp{};

    utl::tuplev2<double,int,unsigned int,float> tp4{};

    utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short> tp8{};

    utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short> tp16{};

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(tp), 0.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(tp4), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp4), 0 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp4), 0.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(tp8), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(tp8), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(tp8), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(tp8), 0 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(tp16), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(tp16), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(tp16), 0 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(tp16), 0.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(tp16), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(tp16), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(tp16), 0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(tp16), 0 );
}

TEST_CASE("tuplev2(constructor)" * doctest::test_suite("utl"))
{
    using tuple1_t = utl::tuplev2<double>;
    tuple1_t tp{1.};

    using tuple4_t = utl::tuplev2<double,int,unsigned int,float>;
    tuple4_t tp4{1.,2,3,4.};

    using tuple8_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple8_t tp8{1.,2,3,4.,5,6,7,8};

    using tuple16_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple16_t tp16{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp)>, 1 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp4)>, 4 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp8)>, 8 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp16)>, 16 );

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(tp), 1.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(tp4), 2 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp4), 3 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp4), 4.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(tp8), 5 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(tp8), 6 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(tp8), 7 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(tp8), 8 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(tp16), 9 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(tp16), 10 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(tp16), 11 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(tp16), 12.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(tp16), 13 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(tp16), 14 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(tp16), 15 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(tp16), 16 );
}

TEST_CASE("tuplev2(copy_constructor)" * doctest::test_suite("utl"))
{
    using tuple1_t = utl::tuplev2<double>;
    tuple1_t tp{1.};

    using tuple4_t = utl::tuplev2<double,int,unsigned int,float>;
    tuple4_t tp4{1.,2,3,4.};

    using tuple8_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple8_t tp8{1.,2,3,4.,5,6,7,8};

    using tuple16_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple16_t tp16{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    tuple1_t c_tp(tp);
    tuple4_t c_tp4(tp4);
    tuple8_t c_tp8(tp8);
    tuple16_t c_tp16(tp16);

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(c_tp), 1.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(c_tp4), 2 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(c_tp4), 3 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(c_tp4), 4.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(c_tp8), 5 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(c_tp8), 6 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(c_tp8), 7 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(c_tp8), 8 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(c_tp16), 9 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(c_tp16), 10 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(c_tp16), 11 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(c_tp16), 12.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(c_tp16), 13 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(c_tp16), 14 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(c_tp16), 15 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(c_tp16), 16 );
}

TEST_CASE("tuplev2(copy_assignment)" * doctest::test_suite("utl"))
{
    using tuple1_t = utl::tuplev2<double>;
    tuple1_t tp{1.};

    using tuple4_t = utl::tuplev2<double,int,unsigned int,float>;
    tuple4_t tp4{1.,2,3,4.};

    using tuple8_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple8_t tp8{1.,2,3,4.,5,6,7,8};

    using tuple16_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple16_t tp16{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    tuple1_t c_tp{};
    c_tp = tp;

    tuple4_t c_tp4{};
    c_tp4 = tp4;

    tuple8_t c_tp8{};
    c_tp8 = tp8;

    tuple16_t c_tp16{};
    c_tp16 = tp16;

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(c_tp), 1.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(c_tp4), 2 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(c_tp4), 3 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(c_tp4), 4.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(c_tp8), 5 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(c_tp8), 6 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(c_tp8), 7 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(c_tp8), 8 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(c_tp16), 9 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(c_tp16), 10 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(c_tp16), 11 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(c_tp16), 12.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(c_tp16), 13 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(c_tp16), 14 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(c_tp16), 15 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(c_tp16), 16 );
}

TEST_CASE("tuplev2(constructor)" * doctest::test_suite("utl"))
{
    using tuple1_t = utl::tuplev2<double>;
    constexpr tuple1_t tp{1.};

    using tuple4_t = utl::tuplev2<double,int,unsigned int,float>;
    constexpr tuple4_t tp4{1.,2,3,4.};

    using tuple8_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    constexpr tuple8_t tp8{1.,2,3,4.,5,6,7,8};

    using tuple16_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    constexpr tuple16_t tp16{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp)>, 1 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp4)>, 4 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp8)>, 8 );
    NMTOOLS_ASSERT_EQUAL( utl::tuple_size_v<decltype(tp16)>, 16 );

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(tp), 1.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(tp4), 2 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp4), 3 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp4), 4.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(tp8), 5 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(tp8), 6 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(tp8), 7 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(tp8), 8 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(tp16), 9 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(tp16), 10 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(tp16), 11 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(tp16), 12.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(tp16), 13 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(tp16), 14 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(tp16), 15 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(tp16), 16 );
}

TEST_CASE("tuplev2(copy_constructor)" * doctest::test_suite("utl"))
{
    using tuple1_t = utl::tuplev2<double>;
    constexpr tuple1_t tp{1.};

    using tuple4_t = utl::tuplev2<double,int,unsigned int,float>;
    constexpr tuple4_t tp4{1.,2,3,4.};

    using tuple8_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    constexpr tuple8_t tp8{1.,2,3,4.,5,6,7,8};

    using tuple16_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    constexpr tuple16_t tp16{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    constexpr tuple1_t c_tp(tp);
    constexpr tuple4_t c_tp4(tp4);
    constexpr tuple8_t c_tp8(tp8);
    constexpr tuple16_t c_tp16(tp16);

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(c_tp), 1.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(c_tp4), 2 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(c_tp4), 3 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(c_tp4), 4.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(c_tp8), 5 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(c_tp8), 6 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(c_tp8), 7 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(c_tp8), 8 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(c_tp16), 9 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(c_tp16), 10 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(c_tp16), 11 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(c_tp16), 12.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(c_tp16), 13 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(c_tp16), 14 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(c_tp16), 15 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(c_tp16), 16 );
}

TEST_CASE("tuplev2(constructor)" * doctest::test_suite("utl"))
{
    auto tp   = utl::tuplev2{1.f};
    auto tp4  = utl::tuplev2{1.,2,3,4.};
    auto tp8  = utl::tuplev2{1.,2,3,4.,5,6,7,8};
    auto tp16 = utl::tuplev2{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(tp), 1.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(tp4), 2 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp4), 3 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp4), 4.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(tp8), 5 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(tp8), 6 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(tp8), 7 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(tp8), 8 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(tp16), 9 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(tp16), 10 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(tp16), 11 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(tp16), 12.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(tp16), 13 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(tp16), 14 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(tp16), 15 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(tp16), 16 );
}

TEST_CASE("tuplev2(test1)" * doctest::test_suite("utl"))
{
    auto tp   = utl::tuplev2{1.f};
    auto tp4  = utl::tuplev2{1.,2,3,4.};
    auto tp8  = utl::tuplev2{1.,2,3,4.,5,6,7,8};
    auto tp16 = utl::tuplev2{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    utl::get<0>(tp)    = 17;
    utl::get<1>(tp4)   = 18;
    utl::get<2>(tp4)   = 19;
    utl::get<3>(tp4)   = 20;
    utl::get<4>(tp8)   = 21;
    utl::get<5>(tp8)   = 22;
    utl::get<6>(tp8)   = 23;
    utl::get<7>(tp8)   = 24;
    utl::get<8>(tp16)  = 25;
    utl::get<9>(tp16)  = 26;
    utl::get<10>(tp16) = 27;
    utl::get<11>(tp16) = 28;
    utl::get<12>(tp16) = 29;
    utl::get<13>(tp16) = 30;
    utl::get<14>(tp16) = 31;
    utl::get<15>(tp16) = 32;

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(tp),    17 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(tp4),   18 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp4),   19 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp4),   20 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(tp8),   21 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(tp8),   22 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(tp8),   23 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(tp8),   24 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(tp16),  25 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(tp16),  26 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(tp16), 27 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(tp16), 28 );
    NMTOOLS_ASSERT_EQUAL( utl::get<12>(tp16), 29 );
    NMTOOLS_ASSERT_EQUAL( utl::get<13>(tp16), 30 );
    NMTOOLS_ASSERT_EQUAL( utl::get<14>(tp16), 31 );
    NMTOOLS_ASSERT_EQUAL( utl::get<15>(tp16), 32 );
}

TEST_CASE("tuplev2(test2)" * doctest::test_suite("utl"))
{
    // converting constructor
    
    using tuple1_t = utl::tuplev2<double>;
    tuple1_t tp{1.};

    using tuple4_t = utl::tuplev2<double,int,unsigned int,float>;
    tuple4_t tp4{1.,2,3,4.};

    using tuple8_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple8_t tp8{1.,2,3,4.,5,6,7,8};

    using tuple16_t = utl::tuplev2<double,int,unsigned int,float,char,unsigned char,short,unsigned short,double,int,unsigned int,float,char,unsigned char,short,unsigned short>;
    tuple16_t tp16{1.,2,3,4.,5,6,7,8,9.,10,11,12.,13,14,15,16};

    using tuple1a_t = utl::tuplev2<float>;
    tuple1a_t tp_a{tp};

    using tuple4a_t = utl::tuplev2<float,short,unsigned short,double>;
    tuple4a_t tp4_a{tp4};

    using tuple8a_t = utl::tuplev2<float,short,unsigned short,double,int,unsigned int,unsigned short,short>;
    tuple8a_t tp8_a{tp8};

    using tuple16a_t = utl::tuplev2<float,short,unsigned short,double,int,unsigned int,unsigned short,short,double,unsigned long,long,float,float,float,double,double>;
    tuple16a_t tp16_a{tp16};

    NMTOOLS_ASSERT_CLOSE( utl::get<0>(tp_a),    1.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<1>(tp4_a),   2 );
    NMTOOLS_ASSERT_EQUAL( utl::get<2>(tp4_a),   3 );
    NMTOOLS_ASSERT_CLOSE( utl::get<3>(tp4_a),   4.0 );
    NMTOOLS_ASSERT_EQUAL( utl::get<4>(tp8_a),   5 );
    NMTOOLS_ASSERT_EQUAL( utl::get<5>(tp8_a),   6 );
    NMTOOLS_ASSERT_EQUAL( utl::get<6>(tp8_a),   7 );
    NMTOOLS_ASSERT_EQUAL( utl::get<7>(tp8_a),   8 );
    NMTOOLS_ASSERT_CLOSE( utl::get<8>(tp16_a),  9 );
    NMTOOLS_ASSERT_EQUAL( utl::get<9>(tp16_a),  10 );
    NMTOOLS_ASSERT_EQUAL( utl::get<10>(tp16_a), 11 );
    NMTOOLS_ASSERT_CLOSE( utl::get<11>(tp16_a), 12.0 );
    NMTOOLS_ASSERT_CLOSE( utl::get<12>(tp16_a), 13 );
    NMTOOLS_ASSERT_CLOSE( utl::get<13>(tp16_a), 14 );
    NMTOOLS_ASSERT_CLOSE( utl::get<14>(tp16_a), 15 );
    NMTOOLS_ASSERT_CLOSE( utl::get<15>(tp16_a), 16 );
}