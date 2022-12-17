package com.example.nmtools_demo;

public class NmTools {
    static {
        System.loadLibrary("nmtools-demo");
    }
    public static native String arange(int start, int stop, int step);
    public static native String random(float min, float max, int[] jshape);
}
