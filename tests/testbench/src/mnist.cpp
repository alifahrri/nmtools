#include "nmtools/array/array/conv.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/pooling.hpp"
#include "nmtools/array/array/activations/relu.hpp"
#include "nmtools/array/array/softmax.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/matmul.hpp"
#include "nmtools/array/eval.hpp"

#include "nmtools/testing/doctest.hpp"
#include "nmtools/benchmarks/bench.hpp"

#include "data/mnist.hpp"
#include "initializer/mnist.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace bench = nm::benchmarks;

using namespace nmtools::literals;

#undef NMTOOLS_TESTING_OUTPUT_PRECISION
// NOTE: may be because printing weight not precise enough
// TODO: improve precitsion
#define NMTOOLS_TESTING_OUTPUT_PRECISION (1e-3)

namespace testing::graph
{

    template <typename input_t>
    constexpr auto mnist_conv_relu_0(const input_t& input)
    {
        auto Convolution28_Output_0 = view::conv2d(input,initializer::mnist::Parameter5,nm::None,nm::None,2_ct);
        auto Plus30_Output_0        = view::add(Convolution28_Output_0,initializer::mnist::Parameter6);
        auto ReLU32_Output_0        = view::relu(Plus30_Output_0);
        return ReLU32_Output_0;
    }

    template <typename input_t>
    constexpr auto mnist_pool2d_0(const input_t& ReLU32_Output_0)
    {
        auto Pooling66_Output_0 = view::max_pool2d(ReLU32_Output_0,nmtools_tuple{2_ct,2_ct},nmtools_tuple{2_ct,2_ct});
        return Pooling66_Output_0;
    }

    template <typename input_t>
    constexpr auto mnist_conv_relu_pool2d_0(const input_t& input)
    {
        auto Convolution28_Output_0 = view::conv2d(input,initializer::mnist::Parameter5,nm::None,nm::None,2_ct);
        auto Plus30_Output_0        = view::add(Convolution28_Output_0,initializer::mnist::Parameter6);
        auto ReLU32_Output_0        = view::relu(Plus30_Output_0);
        auto Pooling66_Output_0     = view::max_pool2d(ReLU32_Output_0,nmtools_tuple{2_ct,2_ct},nmtools_tuple{2_ct,2_ct});
        // for debugging purpose:
        [[maybe_unused]] auto Convolution28_Output_0_shape = nm::shape(Convolution28_Output_0);
        [[maybe_unused]] auto Plus30_Output_0_shape        = nm::shape(Plus30_Output_0);
        [[maybe_unused]] auto ReLU32_Output_0_shape        = nm::shape(ReLU32_Output_0);
        [[maybe_unused]] auto Pooling66_Output_0_shape     = nm::shape(Pooling66_Output_0);
        return Pooling66_Output_0;
    }

    template <typename input_t>
    constexpr auto mnist_conv_relu_1(const input_t& Pooling66_Output_0)
    {
        auto Convolution110_Output_0 = view::conv2d(Pooling66_Output_0,initializer::mnist::Parameter87,nm::None,nm::None,2_ct);
        auto Plus112_Output_0        = view::add(Convolution110_Output_0,initializer::mnist::Parameter88);
        auto ReLU114_Output_0        = view::relu(Plus112_Output_0);
        return ReLU114_Output_0;
    }

    template <typename input_t>
    constexpr auto mnist_pool2d_1(const input_t& ReLU114_Output_0)
    {
        auto Pooling160_Output_0 = view::max_pool2d(ReLU114_Output_0,nmtools_tuple{3_ct,3_ct},nmtools_tuple{3_ct,3_ct});
        return Pooling160_Output_0;
    }

    template <typename input_t>
    constexpr auto mnist_conv_relu_pool2d_1(const input_t& Pooling66_Output_0)
    {
        auto Convolution110_Output_0 = view::conv2d(Pooling66_Output_0,initializer::mnist::Parameter87,nm::None,nm::None,2_ct);
        auto Plus112_Output_0        = view::add(Convolution110_Output_0,initializer::mnist::Parameter88);
        auto ReLU114_Output_0        = view::relu(Plus112_Output_0);
        auto Pooling160_Output_0     = view::max_pool2d(ReLU114_Output_0,nmtools_tuple{3_ct,3_ct},nmtools_tuple{3_ct,3_ct});
        return Pooling160_Output_0;
    }

    template <typename input_t>
    constexpr auto mnist_matmul_add(const input_t& Pooling160_Output_0)
    {
        auto Pooling160_Output_0_reshape0 = view::reshape(Pooling160_Output_0,initializer::mnist::Pooling160_Output_0_reshape0_shape);
        auto Parameter193_reshape1        = view::reshape(initializer::mnist::Parameter193,initializer::mnist::Parameter193_reshape1_shape);
        auto Times212_Output_0            = view::matmul(Pooling160_Output_0_reshape0,Parameter193_reshape1);
        auto Plus214_Output_0             = view::add(Times212_Output_0,initializer::mnist::Parameter194);
        return Plus214_Output_0;
    }

    template <typename input_t>
    constexpr auto mnist_softmax(const input_t& Plus214_Output_0)
    {
        return view::softmax(Plus214_Output_0,/*dim*/1_ct);
    }

    template <typename input_t>
    constexpr auto mnist(const input_t& input)
    {
        auto Pooling66_Output_0  = na::eval(mnist_conv_relu_pool2d_0(input));
        auto Pooling160_Output_0 = na::eval(mnist_conv_relu_pool2d_1(Pooling66_Output_0));
        auto Plus214_Output_0    = mnist_matmul_add(Pooling160_Output_0);
        return Plus214_Output_0;
    }
}

#define RUN_SUBCASE(case_name, fn, input) \
SUBCASE(case_name) \
{ \
const auto bench_title = std::string(#fn); \
auto result = testing::graph::fn(input); \
NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
auto fn = [&](){ return na::eval(result); }; \
auto result_typename = std::string(NMTOOLS_TESTING_GET_TYPENAME(decltype(na::eval(result)))); \
auto input_typename  = std::string(NMTOOLS_TESTING_GET_TYPENAME(decltype(input))); \
nmtools::testing::remove_string(result_typename,std::string("nmtools::array::")); \
nmtools::testing::remove_string(input_typename,std::string("nmtools::array::")); \
nmtools::testing::remove_string(result_typename,std::string("std::")); \
nmtools::testing::remove_string(input_typename,std::string("std::")); \
auto signature = "(" + input_typename + ") -> " + result_typename; \
auto m_result_ = bench::TrackedBench::run(bench_title, signature, fn); \
NMTOOLS_ASSERT_CLOSE( m_result_, expect::result ); \
}

TEST_CASE("conv_relu_0" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_conv_relu_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_0, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_conv_relu_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_0, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_conv_relu_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_0, input_d)
    }
}

TEST_CASE("pool2d_0" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_pool2d_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_pool2d_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_pool2d_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_pool2d_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_pool2d_0, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_pool2d_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_pool2d_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_pool2d_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_pool2d_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_pool2d_0, input_d)
    }
        {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_pool2d_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_pool2d_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_pool2d_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_pool2d_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_pool2d_0, input_d)
    }
}

TEST_CASE("conv_relu_1" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_conv_relu_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_1, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_conv_relu_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_1, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_conv_relu_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_1, input_d)
    }
}

TEST_CASE("pool2d_1" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_pool2d_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_pool2d_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_pool2d_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_pool2d_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_pool2d_1, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_pool2d_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_pool2d_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_pool2d_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_pool2d_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_pool2d_1, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_pool2d_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_pool2d_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_pool2d_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_pool2d_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_pool2d_1, input_d)
    }
}

TEST_CASE("conv_relu_pool2d_0" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_conv_relu_maxpool_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_pool2d_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_pool2d_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_pool2d_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_pool2d_0, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_conv_relu_maxpool_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_pool2d_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_pool2d_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_pool2d_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_pool2d_0, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_conv_relu_maxpool_0);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_pool2d_0, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_pool2d_0, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_pool2d_0, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_pool2d_0, input_d)
    }
}

TEST_CASE("conv_relu_pool2d_1" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_conv_relu_maxpool_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_pool2d_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_pool2d_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_pool2d_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_pool2d_1, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_conv_relu_maxpool_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_pool2d_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_pool2d_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_pool2d_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_pool2d_1, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_conv_relu_maxpool_1);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_conv_relu_pool2d_1, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_conv_relu_pool2d_1, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_conv_relu_pool2d_1, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_conv_relu_pool2d_1, input_d)
    }
}

TEST_CASE("matmul_add" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_matmul_add);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_matmul_add, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_matmul_add, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_matmul_add, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_matmul_add, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_matmul_add);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_matmul_add, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_matmul_add, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_matmul_add, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_matmul_add, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_matmul_add);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_matmul_add, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_matmul_add, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_matmul_add, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_matmul_add, input_d)
    }
}

TEST_CASE("softmax" * doctest::test_suite("mnist"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_0_softmax);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_softmax, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_softmax, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_softmax, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_softmax, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_1_softmax);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_softmax, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_softmax, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_softmax, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_softmax, input_d)
    }
    {
        NMTOOLS_TESTING_DECLARE_NS(testbench, mnist, image_2_softmax);
        using namespace args;

        RUN_SUBCASE("hybrid_ndarray_input", mnist_softmax, input_h)
        RUN_SUBCASE("fixed_ndarray_input",  mnist_softmax, input_f)
        RUN_SUBCASE("nested_array_input",   mnist_softmax, input_a)
        RUN_SUBCASE("dynamic_ndarray_input", mnist_softmax, input_d)
    }
}