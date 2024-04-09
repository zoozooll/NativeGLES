#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

JavaVM *g_JVM = nullptr;

AAssetManager *g_AssetManager = nullptr;

char *g_InternalPath = nullptr;

char *g_ExternalPath = nullptr;

// 加载lib库的时候首先被回调的方法
extern "C" jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    // 生成 jni环境变量
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    // 保存全局的 JVM 虚拟机对象
    g_JVM = vm;
    return JNI_VERSION_1_6;
}

// 释放 lib 库的时候系统回调方法
extern "C" void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    g_AssetManager = nullptr;
    g_InternalPath = nullptr;
    g_JVM = nullptr;
}
