// TODO: move common utility to nmtools main dir

package com.example.nmtools_demo;

public class NmTools {
    static {
        System.loadLibrary("nmtools-demo");
    }

    public static native String to_string(int[] data, int[] shape);
    public static native String to_string(float[] data, int[] shape);

    static public int[] parse_shape(String shape_str)
    {
        String[] dims_str = shape_str.split(",");
        int[] shape = new int[dims_str.length];
        for (int i=0; i<shape.length; i++) {
            shape[i] = Integer.parseInt(dims_str[i]);
        }
        return shape;
    }

    static public class NDArrayFloat {
        private float[] data;
        private int[] shape;

        public NDArrayFloat() {}
        public NDArrayFloat(float[] data, int[] shape)
        {
            this.data = data;
            this.shape = shape;
        }

        public String to_string()
        {
            return NmTools.to_string(this.data,this.shape);
        }

        public float[] get_data()
        {
            return data;
        }

        public int[] get_shape()
        {
            return shape;
        }
    }

    public static native NDArrayFloat arange(int start, int stop, int step);
    public static native NDArrayFloat random(float min, float max, int[] jshape);
    public static native NDArrayFloat sin(float[] jarray, int[] jshape);
    public static native NDArrayFloat relu(float[] jarray, int[] jshape);
    public static native NDArrayFloat sigmoid(float[] jarray, int[] jshape);
    public static native NDArrayFloat add(float[] jarray_lhs, int[] jshape_lhs, float[] jarray_rhs, int[] jshape_rhs);
    public static native NDArrayFloat subtract(float[] jarray_lhs, int[] jshape_lhs, float[] jarray_rhs, int[] jshape_rhs);
    public static native NDArrayFloat multiply(float[] jarray_lhs, int[] jshape_lhs, float[] jarray_rhs, int[] jshape_rhs);
    public static native NDArrayFloat reduce_add(float[] jarray_lhs, int[] jshape_lhs, int[] jaxis, boolean keepdims);
    public static native NDArrayFloat reduce_multiply(float[] jarray_lhs, int[] jshape_lhs, int[] jaxis, boolean keepdims);

    public static NDArrayFloat sin(NDArrayFloat ndarray)
    {
        return sin(ndarray.get_data(), ndarray.get_shape());
    }

    public static NDArrayFloat relu(NDArrayFloat ndarray)
    {
        return relu(ndarray.get_data(), ndarray.get_shape());
    }

    public static NDArrayFloat sigmoid(NDArrayFloat ndarray)
    {
        return sigmoid(ndarray.get_data(), ndarray.get_shape());
    }

    public static NDArrayFloat add(NDArrayFloat lhs, NDArrayFloat rhs)
    {
        return add(lhs.get_data(), lhs.get_shape(), rhs.get_data(), rhs.get_shape());
    }

    public static NDArrayFloat multiply(NDArrayFloat lhs, NDArrayFloat rhs)
    {
        return multiply(lhs.get_data(), lhs.get_shape(), rhs.get_data(), rhs.get_shape());
    }

    public static NDArrayFloat subtract(NDArrayFloat lhs, NDArrayFloat rhs)
    {
        return subtract(lhs.get_data(), lhs.get_shape(), rhs.get_data(), rhs.get_shape());
    }

    public static NDArrayFloat reduce_add(NDArrayFloat array, int[] axis, boolean keepdims)
    {
        return reduce_add(array.get_data(), array.get_shape(), axis, keepdims);
    }

    public static NDArrayFloat reduce_multiply(NDArrayFloat array, int[] axis, boolean keepdims)
    {
        return reduce_multiply(array.get_data(), array.get_shape(), axis, keepdims);
    }
}
