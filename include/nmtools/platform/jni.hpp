#ifndef NMTOOLS_ARRAY_UTILITY_JNI_HPP
#define NMTOOLS_ARRAY_UTILITY_JNI_HPP

#include <jni.h>
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/view/flatten.hpp"

namespace nmtools::array
{
    template <typename BufferType=none_t,
        typename ShapeType=none_t,
        typename JavaArray>
    auto from_java_array(JNIEnv* env, const JavaArray& j_array)
    {
        using meta::as_value_v;
        constexpr auto src_vtype = [](){
            if constexpr (meta::is_same_v<JavaArray,jintArray>) {
                return as_value_v<int>;
            } else if constexpr (meta::is_same_v<JavaArray,jlongArray>) {
                return as_value_v<long>;
            } else if constexpr (meta::is_same_v<JavaArray,jfloatArray>) {
                return as_value_v<float>;
            } else /* if constexpr (meta::is_same_v<JavaArray,jdoubleArray>) */ {
                return as_value_v<double>;
            }
            // TODO: unsupported
        }();
        using src_element_t = meta::type_t<decltype(src_vtype)>;

        constexpr auto buffer_vtype = [](){
            if constexpr (is_none_v<BufferType>) {
                return as_value_v<nmtools_list<src_element_t>>;
            } else /* if constexpr (is_ndarray_v<BufferType>) */ {
                return as_value_v<BufferType>;
            }
        }();

        constexpr auto shape_vtype = [](){
            if constexpr (is_none_v<ShapeType>) {
                return as_value_v<nmtools_array<size_t,1>>;
            } else /* if constexpr (is_index_array_v<ShapeType>) */ {
                return as_value_v<ShapeType>;
            }
        }();

        using buffer_t = meta::type_t<decltype(buffer_vtype)>;
        using shape_t  = meta::type_t<decltype(shape_vtype)>;

        using array_t   = ndarray_t<buffer_t,shape_t>;
        using element_t = typename array_t::value_type;

        auto array = array_t{};
        
        jsize len = env->GetArrayLength(j_array);
        if constexpr (meta::is_resizable_v<array_t>) {
            array.resize((size_t)len);
        }

        auto array_body = [&](){
            if constexpr (meta::is_same_v<JavaArray,jintArray>) {
                return env->GetIntArrayElements(j_array,0);
            } else if constexpr (meta::is_same_v<JavaArray,jlongArray>) {
                return env->GetLongArrayElements(j_array,0);
            } else if constexpr (meta::is_same_v<JavaArray,jfloatArray>) {
                return env->GetFloatArrayElements(j_array,0);
            } else /* if constexpr (meta::is_same_v<JavaArray,jdoubleArray>) */ {
                return env->GetDoubleArrayElements(j_array,0);
            }
        }();

        for (size_t i=0; i<len; i++) {
            at(array,i) = (element_t)array_body[i];
        }

        return array;
    } // from_java_array

    template <typename JavaArray>
    auto from_java_array(JNIEnv* env, const JavaArray& j_data, const jintArray& j_shape)
    {
        auto data = from_java_array(env,j_data);
        auto shape = from_java_array(env,j_shape);
        return reshape(data,shape);
    }

    template <typename Array>
    auto to_java(JNIEnv* env, const Array& array)
    {
        using element_type = meta::get_element_type_t<Array>;
        auto size  = nmtools::size(array);
        auto shape = nmtools::shape(array);
        auto dim   = nmtools::dim(array);
        auto flat  = view::flatten(array);
        jintArray jshape = env->NewIntArray(dim);
        {
            // temporary
            auto fill = nmtools_list<jint>(dim);
            for (size_t i=0; i<dim; i++) {
                at(fill,i) = at(shape,i);
            }
            env->SetIntArrayRegion(jshape,0,dim,fill.data());
        }

        if constexpr (meta::is_integer_v<element_type>) {
            // for simplicity just convert to jintArray
            // TODO: check if jintArray / jlongArray,...

            jintArray result = env->NewIntArray(size);

            {
                // temporary
                auto fill = nmtools_list<jint>(size);
                for (size_t i=0; i<size; i++) {
                    at(fill,i) = at(flat,i);
                }
                env->SetIntArrayRegion(result,0,size,fill.data());
            }

            return nmtools_tuple{result,jshape};
        } else {
            // assume float
            // TODO: check if jfloatArray / jdoubleArray

            jfloatArray result = env->NewFloatArray(size);

            {
                // temporary
                auto fill = nmtools_list<jfloat>(size);
                for (size_t i=0; i<size; i++) {
                    at(fill,i) = at(flat,i);
                }
                env->SetFloatArrayRegion(result,0,size,fill.data());
            }

            return nmtools_tuple{result,jshape};
        }
    }
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_UTILITY_JNI_HPP