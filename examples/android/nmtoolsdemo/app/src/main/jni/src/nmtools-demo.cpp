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

#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/array/random.hpp"
#include "nmtools/array/random_engine.hpp"

#include "nmtools/array/index/ndenumerate.hpp"
#include "nmtools/utils/to_string.hpp"
#include "nmtools/array/utility/jni.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

using nm::utils::to_string;

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "nmtools-libs::", __VA_ARGS__))

#define LOGD(...) \
  ((void)__android_log_print(ANDROID_LOG_DEBUG, "nmtools-libs::", __VA_ARGS__))

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_nmtools_1demo_NmTools_arange(JNIEnv* env, jobject thiz, jint start, jint stop, jint step) {
    // maximum 6 dimension
    using shape_t  = na::static_vector<size_t,6>;

    LOGI("arange: start: %d; stop: %d", start, stop);
    auto t0 = std::chrono::high_resolution_clock::now();

    // TODO: fix for negative step with negative stop (e.g. start=10, stop=-5, step=-1)
    auto array = view::arange((int)start,(int)stop,(int)step,nm::float32);

    auto shape = shape_t{};
    shape.resize(3);
    shape = std::array<size_t,3>{1ul,1ul,array.size()};
    auto reshaped = na::reshape(array, shape);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    LOGD("array size: %d", nm::size(array));
    LOGD("dt: %fms", dt.count());

    auto log = std::stringstream ();
    log << to_string(reshaped) << "\n";

    LOGD("array: %s", log.str().c_str());
    return env->NewStringUTF(log.str().c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_nmtools_1demo_NmTools_random(JNIEnv* env, jobject thiz, jfloat min, jfloat  max, jintArray jshape) {
    auto shape = na::from_java_array(env,jshape);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto array = na::random(shape,nm::float32,na::random_engine((float)min,(float)max));
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(t1 - t0);

    LOGD("array size: %d", nm::size(array));
    LOGD("dt: %fms", dt.count());

    auto log = std::stringstream ();
    log << to_string(array) << "\n";

    LOGD("array: %s", log.str().c_str());
    return env->NewStringUTF(log.str().c_str());
}