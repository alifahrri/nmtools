#ifndef TESTBENCH_DATA_MNIST_HPP
#define TESTBENCH_DATA_MNIST_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/array/array/reshape.hpp"

NMTOOLS_TESTING_DECLARE_CASE(testbench, mnist)
{
    using namespace nmtools::literals;

    #include "data/mnist/image_0.hpp"
    #include "data/mnist/image_1.hpp"
    #include "data/mnist/image_2.hpp"

    /**********************************************************************/
    // only fused conv

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_conv_relu_0)
    {
        inline auto input = training_image_0;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_conv_relu_0)
    {
        #include "data/mnist/image_0/ReLU32_Output_0.hpp"
        inline auto result = ReLU32_Output_0;
        inline auto shape  = ReLU32_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_pool2d_0)
    {
        inline auto input = image_0_conv_relu_0::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_pool2d_0)
    {
        #include "data/mnist/image_0/Pooling66_Output_0.hpp"
        inline auto result = Pooling66_Output_0;
        inline auto shape  = Pooling66_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_conv_relu_1)
    {
        inline auto input = image_0_pool2d_0::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_conv_relu_1)
    {
        #include "data/mnist/image_0/ReLU114_Output_0.hpp"
        inline auto result = ReLU114_Output_0;
        inline auto shape  = ReLU114_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_pool2d_1)
    {
        inline auto input = image_0_conv_relu_1::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_pool2d_1)
    {
        #include "data/mnist/image_0/Pooling160_Output_0.hpp"
        inline auto result = Pooling160_Output_0;
        inline auto shape  = Pooling160_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_conv_relu_0)
    {
        inline auto input = training_image_1;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_conv_relu_0)
    {
        #include "data/mnist/image_1/ReLU32_Output_0.hpp"
        inline auto result = ReLU32_Output_0;
        inline auto shape  = ReLU32_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_pool2d_0)
    {
        inline auto input = image_1_conv_relu_0::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_pool2d_0)
    {
        #include "data/mnist/image_1/Pooling66_Output_0.hpp"
        inline auto result = Pooling66_Output_0;
        inline auto shape  = Pooling66_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_conv_relu_1)
    {
        inline auto input = image_1_pool2d_0::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_conv_relu_1)
    {
        #include "data/mnist/image_1/ReLU114_Output_0.hpp"
        inline auto result = ReLU114_Output_0;
        inline auto shape  = ReLU114_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_pool2d_1)
    {
        inline auto input = image_1_conv_relu_1::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_pool2d_1)
    {
        #include "data/mnist/image_1/Pooling160_Output_0.hpp"
        inline auto result = Pooling160_Output_0;
        inline auto shape  = Pooling160_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_conv_relu_0)
    {
        inline auto input = training_image_2;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_conv_relu_0)
    {
        #include "data/mnist/image_2/ReLU32_Output_0.hpp"
        inline auto result = ReLU32_Output_0;
        inline auto shape  = ReLU32_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_pool2d_0)
    {
        inline auto input = image_2_conv_relu_0::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_pool2d_0)
    {
        #include "data/mnist/image_2/Pooling66_Output_0.hpp"
        inline auto result = Pooling66_Output_0;
        inline auto shape  = Pooling66_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_conv_relu_1)
    {
        inline auto input = image_2_pool2d_0::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_conv_relu_1)
    {
        #include "data/mnist/image_2/ReLU114_Output_0.hpp"
        inline auto result = ReLU114_Output_0;
        inline auto shape  = ReLU114_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_pool2d_1)
    {
        inline auto input = image_2_conv_relu_1::expect::result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_pool2d_1)
    {
        #include "data/mnist/image_2/Pooling160_Output_0.hpp"
        inline auto result = Pooling160_Output_0;
        inline auto shape  = Pooling160_Output_0_shape;
    }

    /**********************************************************************/
    // more fused ops

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_conv_relu_maxpool_0)
    {
        inline auto input = training_image_0;
        NMTOOLS_CAST_ARRAYS(input)
        static_assert( !meta::is_dynamic_ndarray_v<decltype(input)> );
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_conv_relu_maxpool_0)
    {
        // intermediate output results
        #include "data/mnist/image_0/Pooling66_Output_0.hpp"
        inline auto result = Pooling66_Output_0;
        inline auto shape  = Pooling66_Output_0_shape;
        static_assert( !meta::is_dynamic_ndarray_v<decltype(Pooling66_Output_0)> );
        static_assert( !meta::is_dynamic_ndarray_v<decltype(result)> );
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_conv_relu_maxpool_1)
    {
        using image_0_conv_relu_maxpool_0::expect::result;
        inline auto input = result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_conv_relu_maxpool_1)
    {
        #include "data/mnist/image_0/Pooling160_Output_0.hpp"
        inline auto result = Pooling160_Output_0;
        inline auto shape  = Pooling160_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_matmul_add)
    {
        using image_0_conv_relu_maxpool_1::expect::result;
        inline auto input = result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_matmul_add)
    {
        #include "data/mnist/image_0/Plus214_Output_0.hpp"
        inline auto result = Plus214_Output_0;
        inline auto shape  = Plus214_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_0_softmax)
    {
        inline auto input = image_0_matmul_add::expect::Plus214_Output_0;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_0_softmax)
    {
        inline float result[1][10] = {{0.,0.,0.,0.,0.,1.,0.,0.,0.,0.}};
        inline auto shape = nmtools_array{1,10};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_conv_relu_maxpool_0)
    {
        inline auto input = training_image_1;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_conv_relu_maxpool_0)
    {
        // intermediate output results
        #include "data/mnist/image_1/Pooling66_Output_0.hpp"
        inline auto result = Pooling66_Output_0;
        inline auto shape  = Pooling66_Output_0_shape;
        static_assert( !meta::is_dynamic_ndarray_v<decltype(Pooling66_Output_0)> );
        static_assert( !meta::is_dynamic_ndarray_v<decltype(result)> );
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_conv_relu_maxpool_1)
    {
        using image_1_conv_relu_maxpool_0::expect::result;
        inline auto input = result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_conv_relu_maxpool_1)
    {
        #include "data/mnist/image_1/Pooling160_Output_0.hpp"
        inline auto result = Pooling160_Output_0;
        inline auto shape  = Pooling160_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_matmul_add)
    {
        using image_1_conv_relu_maxpool_1::expect::result;
        inline auto input = result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_matmul_add)
    {
        #include "data/mnist/image_1/Plus214_Output_0.hpp"
        inline auto result = Plus214_Output_0;
        inline auto shape  = Plus214_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_1_softmax)
    {
        inline auto input = image_1_matmul_add::expect::Plus214_Output_0;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_1_softmax)
    {
        inline float result[1][10] = {{1.,0.,0.,0.,0.,0.,0.,0.,0.,0.}};
        inline auto shape = nmtools_array{1,10};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_conv_relu_maxpool_0)
    {
        inline auto input = training_image_2;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_conv_relu_maxpool_0)
    {
        // intermediate output results
        #include "data/mnist/image_2/Pooling66_Output_0.hpp"
        inline auto result = Pooling66_Output_0;
        inline auto shape  = Pooling66_Output_0_shape;
        static_assert( !meta::is_dynamic_ndarray_v<decltype(Pooling66_Output_0)> );
        static_assert( !meta::is_dynamic_ndarray_v<decltype(result)> );
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_conv_relu_maxpool_1)
    {
        using image_2_conv_relu_maxpool_0::expect::result;
        inline auto input = result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_conv_relu_maxpool_1)
    {
        #include "data/mnist/image_2/Pooling160_Output_0.hpp"
        inline auto result = Pooling160_Output_0;
        inline auto shape  = Pooling160_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_matmul_add)
    {
        using image_2_conv_relu_maxpool_1::expect::result;
        inline auto input = result;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_matmul_add)
    {
        #include "data/mnist/image_2/Plus214_Output_0.hpp"
        inline auto result = Plus214_Output_0;
        inline auto shape  = Plus214_Output_0_shape;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(image_2_softmax)
    {
        inline auto input = image_2_matmul_add::expect::Plus214_Output_0;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(image_2_softmax)
    {
        inline float result[1][10] = {{0.,0.,0.,0.,1.,0.,0.,0.,0.,0.}};
        inline auto shape = nmtools_array{1,10};
    }
}

#endif // TESTBENCH_DATA_MNIST_HPP