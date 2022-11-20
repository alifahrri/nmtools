//
// Created by fahri on 20/11/22.
//

#include <cstring>
#include <jni.h>
#include <cinttypes>
#include <android/log.h>
#include <string>
#include <sstream>

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
Java_com_example_nmtools_1demo_MainActivity_arange(JNIEnv* env, jobject thiz, jint start, jint stop, jint step) {
    // maximum 6 dimension
    using shape_t  = na::static_vector<size_t,6>;

    LOGI("arange: start: %d; stop: %d", start, stop);

    // TODO: fix for negative step with negative stop (e.g. start=10, stop=-5, step=-1)
    auto array = view::arange((int)start,(int)stop,(int)step,nm::float32);

    auto shape = shape_t{};
    shape.resize(3);
    shape = std::array<size_t,3>{1ul,1ul,array.size()};
    auto reshaped = na::reshape(array, shape);

    auto log = std::stringstream ();
    log << to_string(reshaped) << "\n";

    LOGD("array: %s", log.str().c_str());
    return env->NewStringUTF(log.str().c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_nmtools_1demo_MainActivity_random(JNIEnv* env, jobject thiz, jintArray jshape) {
    auto shape = na::from_java_array(env,jshape);
    auto array = na::random(shape,nm::float32,na::random_engine());

    auto log = std::stringstream ();
    log << to_string(array) << "\n";

    LOGD("array: %s", log.str().c_str());
    return env->NewStringUTF(log.str().c_str());
}