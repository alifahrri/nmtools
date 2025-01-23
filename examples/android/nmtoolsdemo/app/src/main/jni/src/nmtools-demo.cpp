//
// Created by fahri on 20/11/22.
//

#include <cstring>
#include <jni.h>
#include <cinttypes>
#include <android/log.h>
#include <string>
#include <sstream>
#include <chrono>

#include "nmtools/ndarray.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/random.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/sin.hpp"
#include "nmtools/array/array/activations/relu.hpp"
#include "nmtools/array/array/activations/sigmoid.hpp"
#include "nmtools/array/random_engine.hpp"

#include "nmtools/array/index/ndenumerate.hpp"
#include "nmtools/utility/to_string.hpp"
#include "nmtools/platform/jni.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

using nm::utils::to_string;

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "nmtools-libs::", __VA_ARGS__))

#define LOGD(...) \
  ((void)__android_log_print(ANDROID_LOG_DEBUG, "nmtools-libs::", __VA_ARGS__))

template <typename jType>
static auto to_string(JNIEnv* env, jType jdata, jintArray jshape)
{
    auto array = na::from_java_array(env,jdata,jshape);

    auto result = std::stringstream ();
    result << to_string(array) << "\n";

    return env->NewStringUTF(result.str().c_str());
}

static auto arange(JNIEnv* env, jint start, jint stop, jint step)
{
    // maximum 6 dimension
    using shape_t  = na::static_vector<size_t,6>;

    auto t0 = std::chrono::high_resolution_clock::now();

    // TODO: fix for negative step with negative stop (e.g. start=10, stop=-5, step=-1)
    auto array = view::arange((int)start,(int)stop,(int)step,nm::float32);

    auto shape = shape_t{};
    shape.resize(3);
    shape = std::array<size_t,3>{1ul,1ul,array.size()};
    auto reshaped = na::reshape(array, shape);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{reshaped,dt};
}

static auto random(JNIEnv* env, jfloat min, jfloat max, jintArray jshape)
{
    auto shape = na::from_java_array(env,jshape);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto array = na::random(shape,nm::float32,na::random_engine((float)min,(float)max));
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{array,dt};
}

static auto sin(JNIEnv* env, jfloatArray jarray, jintArray jshape)
{
    auto array = na::from_java_array(env,jarray,jshape);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::sin(array);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

static auto relu(JNIEnv* env, jfloatArray jarray, jintArray jshape)
{
    auto array = na::from_java_array(env,jarray,jshape);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::relu(array);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

static auto sigmoid(JNIEnv* env, jfloatArray jarray, jintArray jshape)
{
    auto array = na::from_java_array(env,jarray,jshape);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::sigmoid(array);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

static auto add(JNIEnv* env, jfloatArray jarray_lhs, jintArray jshape_lhs, jfloatArray jarray_rhs, jintArray jshape_rhs)
{
    auto lhs = na::from_java_array(env,jarray_lhs,jshape_lhs);
    auto rhs = na::from_java_array(env,jarray_rhs,jshape_rhs);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::add(lhs,rhs);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

static auto subtract(JNIEnv* env, jfloatArray jarray_lhs, jintArray jshape_lhs, jfloatArray jarray_rhs, jintArray jshape_rhs)
{
    auto lhs = na::from_java_array(env,jarray_lhs,jshape_lhs);
    auto rhs = na::from_java_array(env,jarray_rhs,jshape_rhs);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::subtract(lhs,rhs);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

static auto multiply(JNIEnv* env, jfloatArray jarray_lhs, jintArray jshape_lhs, jfloatArray jarray_rhs, jintArray jshape_rhs)
{
    auto lhs = na::from_java_array(env,jarray_lhs,jshape_lhs);
    auto rhs = na::from_java_array(env,jarray_rhs,jshape_rhs);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::multiply(lhs,rhs);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

static auto reduce_add(JNIEnv *env, jfloatArray jarray, jintArray jshape, jintArray jaxis, jboolean jkeepdims)
{
    auto array = na::from_java_array(env,jarray,jshape);
    auto axis = na::from_java_array<nm::none_t,nmtools_array<size_t,1>>(env,jaxis);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::add.reduce(array,axis,/*dtype*/nm::None,/*initial*/nm::None,bool(jkeepdims));
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

static auto reduce_multiply(JNIEnv *env, jfloatArray jarray, jintArray jshape, jintArray jaxis, jboolean jkeepdims)
{
    auto array = na::from_java_array(env,jarray,jshape);
    auto axis = na::from_java_array<nm::none_t,nmtools_array<size_t,1>>(env,jaxis);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto result = na::multiply.reduce(array,axis,/*dtype*/nm::None,/*initial*/nm::None,bool(jkeepdims));
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    return std::tuple{result,dt};
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    to_string
 * Signature: ([I[I)Ljava/lang/String;
 */
extern "C"
JNIEXPORT jstring JNICALL Java_com_example_nmtools_1demo_NmTools_to_1string___3I_3I
        (JNIEnv *env, jclass, jintArray jdata, jintArray jshape)
{
    return to_string(env,jdata,jshape);
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    to_string
 * Signature: ([F[I)Ljava/lang/String;
 */
extern "C"
JNIEXPORT jstring JNICALL Java_com_example_nmtools_1demo_NmTools_to_1string___3F_3I
        (JNIEnv *env, jclass, jfloatArray jdata, jintArray jshape)
{
    return to_string(env,jdata,jshape);
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    arange2
 * Signature: (III)Lcom/example/nmtools_demo/NmTools/NDArray;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_arange
        (JNIEnv *env, jclass, jint start, jint stop, jint step)
{
    const auto& [array, dt] = arange(env,start,stop,step);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    random2
 * Signature: (FF[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_random
        (JNIEnv *env, jclass, jfloat min, jfloat max, jintArray jshape)
{
    const auto& [array, dt] = random(env,min,max,jshape);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    sin
 * Signature: ([F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_sin
        (JNIEnv * env, jclass, jfloatArray jarray, jintArray jshape)
{
    const auto& [array, dt] = sin(env,jarray,jshape);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    relu
 * Signature: ([F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_relu
        (JNIEnv *env, jclass, jfloatArray jarray, jintArray jshape)
{
    const auto& [array, dt] = relu(env,jarray,jshape);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    sigmoid
 * Signature: ([F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_sigmoid
        (JNIEnv *env, jclass, jfloatArray jarray, jintArray jshape)
{
    const auto& [array, dt] = sigmoid(env,jarray,jshape);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    add
 * Signature: ([F[I[F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_add
        (JNIEnv *env, jclass, jfloatArray jarray_lhs, jintArray jshape_lhs, jfloatArray jarray_rhs, jintArray jshape_rhs)
{
    // TODO: error handling
    const auto& [array, dt] = add(env,jarray_lhs,jshape_lhs,jarray_rhs,jshape_rhs);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    subtract
 * Signature: ([F[I[F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_subtract
        (JNIEnv *env, jclass, jfloatArray jarray_lhs, jintArray jshape_lhs, jfloatArray jarray_rhs, jintArray jshape_rhs)
{
    // TODO: error handling
    const auto& [array, dt] = subtract(env,jarray_lhs,jshape_lhs,jarray_rhs,jshape_rhs);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    multiply
 * Signature: ([F[I[F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_multiply
        (JNIEnv *env, jclass, jfloatArray jarray_lhs, jintArray jshape_lhs, jfloatArray jarray_rhs, jintArray jshape_rhs)
{
    // TODO: error handling
    const auto& [array, dt] = multiply(env,jarray_lhs,jshape_lhs,jarray_rhs,jshape_rhs);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}


/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    reduce_add
 * Signature: ([F[I[IZ)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_reduce_1add
        (JNIEnv *env, jclass, jfloatArray jarray, jintArray jshape, jintArray jaxis, jboolean jkeepdims)
{
    const auto& [array, dt] = reduce_add(env,jarray,jshape,jaxis,jkeepdims);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    reduce_multiply
 * Signature: ([F[I[IZ)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
extern "C"
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_reduce_1multiply
        (JNIEnv *env, jclass, jfloatArray jarray, jintArray jshape, jintArray jaxis, jboolean jkeepdims)
{
    const auto& [array, dt] = reduce_multiply(env,jarray,jshape,jaxis,jkeepdims);
    LOGD("dt: %fms", dt.count());

    auto [flat,shape] = na::to_java(env,array);

    jclass NDArrayFloat = env->FindClass("com/example/nmtools_demo/NmTools$NDArrayFloat");

    jmethodID constructor = env->GetMethodID(NDArrayFloat, "<init>", "([F[I)V");

    jobject result = env->NewObject(NDArrayFloat, constructor, flat, shape);
    return result;
}