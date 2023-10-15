#ifndef NMTOOLS_ARRAY_EVAL_SIMD_INDEX_COMMON_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_INDEX_COMMON_HPP

namespace nmtools::index
{
    enum SIMD : int
    {
        BROADCAST=-3,
        SCALAR=-2, // assign scalar
        ACCUMULATE=-1, // accumulate result, maybe for partial application
        PACKED=0,
        PAD_1=1,
        PAD_2=2,
        PAD_3=3,
        PAD_4=4,
        PAD_5=5,
        PAD_6=6,
        PAD_7=7,
        PAD_8=8,
    };
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_EVAL_SIMD_INDEX_COMMON_HPP