package com.mouselee.nativegles;

public class JniHelper {
    private JniHelper() {}

    static {
        System.loadLibrary("nativeGL");
    }
}
