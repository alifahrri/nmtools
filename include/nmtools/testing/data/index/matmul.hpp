#ifndef NMTOOLS_TESTING_DATA_INDEX_MATMUL_HPP
#define NMTOOLS_TESTING_DATA_INDEX_MATMUL_HPP

NMTOOLS_TESTING_DECLARE_CASE(array, shape_matmul)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int lshape[2] = {3,4};
        constexpr inline int rshape[2] = {4,3};
        inline auto lshape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"3:[3]"_ct,"4:[4]"_ct};
        inline auto rshape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto rshape_cl = nmtools_tuple{"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {3,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int lshape[2] = {4,3};
        constexpr inline int rshape[2] = {3,4};
        inline auto lshape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto rshape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"4:[4]"_ct,"3:[3]"_ct};
        inline auto rshape_cl = nmtools_tuple{"3:[3]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int lshape[2] = {4,1};
        constexpr inline int rshape[2] = {1,4};
        inline auto lshape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto rshape_ct = nmtools_tuple{1_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"4:[4]"_ct,"1:[1]"_ct};
        inline auto rshape_cl = nmtools_tuple{"1:[1]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int lshape[2] = {1,4};
        constexpr inline int rshape[2] = {4,1};
        inline auto lshape_ct = nmtools_tuple{1_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{4_ct,1_ct};
        inline auto lshape_cl = nmtools_tuple{"1:[1]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"4:[4]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int lshape[2] =   {4,3};
        constexpr inline int rshape[3] = {2,3,2};
        inline auto lshape_ct = nmtools_tuple{4_ct,3_ct};
        inline auto rshape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto lshape_cl = nmtools_tuple{"4:[4]"_ct,"3:[3]"_ct};
        inline auto rshape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {2,4,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int lshape[3] = {2,3,2};
        constexpr inline int rshape[2] =   {2,4};
        inline auto lshape_ct = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto rshape_ct = nmtools_tuple{2_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        inline auto rshape_cl = nmtools_tuple{"2:[2]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int lshape[4] = {9,5,7,4};
        constexpr inline int rshape[4] = {9,5,4,3};
        inline auto lshape_ct = nmtools_tuple{9_ct,5_ct,7_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{9_ct,5_ct,4_ct,3_ct};
        inline auto lshape_cl = nmtools_tuple{"9:[9]"_ct,"5:[5]"_ct,"7:[7]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"9:[9]"_ct,"5:[5]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int lshape[4] = {1,5,7,4};
        inline int rshape[4] = {9,1,4,3};
        inline auto lshape_ct = nmtools_tuple{1_ct,5_ct,7_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{9_ct,1_ct,4_ct,3_ct};
        inline auto lshape_cl = nmtools_tuple{"1:[1]"_ct,"5:[5]"_ct,"7:[7]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"9:[9]"_ct,"1:[1]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {9,5,7,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int lshape[4] = {9,5,7,4};
        inline int rshape[4] = {5,9,4,3};
        inline auto lshape_ct = nmtools_tuple{9_ct,5_ct,7_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{5_ct,9_ct,4_ct,3_ct};
        inline auto lshape_cl = nmtools_tuple{"9:[9]"_ct,"5:[5]"_ct,"7:[7]"_ct,"4:[4]"_ct};
        inline auto rshape_cl = nmtools_tuple{"5:[5]"_ct,"9:[9]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int lshape[3] = {1,4,3};
        inline int rshape[2] = {3,4};
        inline auto lshape_ct = nmtools_tuple{1_ct,4_ct,3_ct};
        inline auto rshape_ct = nmtools_tuple{3_ct,4_ct};
        inline auto lshape_cl = nmtools_tuple{"1:[1]"_ct,"4:[4]"_ct,"3:[3]"_ct};
        inline auto rshape_cl = nmtools_tuple{"3:[3]"_ct,"4:[4]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[3] = {1,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int lshape[1] = {6};
        inline int rshape[1] = {6};
        inline auto lshape_ct = nmtools_tuple{6_ct};
        inline auto rshape_ct = nmtools_tuple{6_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape)
        NMTOOLS_CAST_INDEX_ARRAYS(rshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int lshape[1] = {6};
        inline int rshape[2] = {6,2};
        inline auto lshape_ct = nmtools_tuple{6_ct};
        inline auto rshape_ct = nmtools_tuple{6_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape)
        NMTOOLS_CAST_INDEX_ARRAYS(rshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int lshape[3] = {2,3,4};
        inline int rshape[1] = {4};
        inline auto lshape_ct = nmtools_tuple{2_ct,3_ct,4_ct};
        inline auto rshape_ct = nmtools_tuple{4};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape)
        NMTOOLS_CAST_INDEX_ARRAYS(rshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int lshape[1] = {6};
        inline int rshape[3] = {1,6,2};
        inline auto lshape_ct = nmtools_tuple{6_ct};
        inline auto rshape_ct = nmtools_tuple{1_ct,6_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape)
        NMTOOLS_CAST_INDEX_ARRAYS(rshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int lshape[1] = {3};
        inline int rshape[4] = {2,1,3,2};
        inline auto lshape_ct = nmtools_tuple{3_ct};
        inline auto rshape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape)
        NMTOOLS_CAST_INDEX_ARRAYS(rshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[3] = {2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int lshape[4] = {2,1,2,3};
        inline int rshape[1] = {3};
        inline auto lshape_ct = nmtools_tuple{2_ct,1_ct,2_ct,3_ct};
        inline auto rshape_ct = nmtools_tuple{3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(lshape)
        NMTOOLS_CAST_INDEX_ARRAYS(rshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[3] = {2,1,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[2] = {0,0};
        inline int  lshape[2] = {4,3};
        inline int  rshape[2] = {3,4};
        inline int   shape[2] = {4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto  left = nmtools_tuple{0,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[2] = {3,2};
        inline int  lshape[2] = {4,3};
        inline int  rshape[2] = {3,4};
        inline int   shape[2] = {4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto  left = nmtools_tuple{3,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},2};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{3},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {0,0,0};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto  left = nmtools_tuple{0,0,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},size_t{0},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3] = {0,3,2};
        inline int  lshape[3] = {1,4,3};
        inline int  rshape[2] =   {3,4};
        inline int   shape[3] = {1,4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto  left = nmtools_tuple{0,3,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{nmtools_tuple{None,None},2};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{0},size_t{3},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{nmtools_tuple{None,None},size_t{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3] = {1,1,0};
        inline int  lshape[2] =   {2,3};
        inline int  rshape[3] = {2,3,2};
        inline int   shape[3] = {2,2,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto  left = nmtools_tuple{1,nmtools_tuple{None,None}};
        inline auto right = nmtools_tuple{1,nmtools_tuple{None,None},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{size_t{1},nmtools_tuple{None,None}};
        inline auto right_v = slices_t{size_t{1},nmtools_tuple{None,None},size_t{0}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int indices[3] = {0,0,0};
        inline int lshape[3]  = {1,4,3};
        inline int rshape[2]  = {3,4};
        inline int shape[3]   = {1,4,4};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(lshape);
        NMTOOLS_CAST_INDEX_ARRAYS(rshape);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        using all_t = nmtools_tuple<none_t,none_t>;
        inline auto left  = nmtools_tuple{0,0,all_t{}};
        inline auto right = nmtools_tuple{all_t{},0};
        using slice_t  = nmtools_either<size_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto left_v  = slices_t{(slice_t)(size_t)0,(slice_t)(size_t)0,(slice_t)all_t{}};
        inline auto right_v = slices_t{(slice_t)all_t{},(slice_t)(size_t)0};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_MATMUL_HPP