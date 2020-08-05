#include <jni.h>
#include <string>
#include <stdio.h>
#include "gempyre.h"
#include "gempyre_utils.h"

JNIEnv* Androidenv;
jobject Androidobj;

void Gempyre::setJNIENV(void* env, void* obj) {
    Androidenv = static_cast<JNIEnv*>(env);
    Androidobj = static_cast<jobject>(obj);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* /*vm*/, void* /*reserved*/) {
    return JNI_VERSION_1_6;
}
    
int androidLoadUi(const std::string& url) {
    if(nullptr == Androidenv || nullptr == Androidobj) {
        GempyreUtils::log(GempyreUtils::LogLevel::Fatal, "setJNIENV not called");
        return 0;
    }
    jstring urlString = Androidenv->NewStringUTF(url.c_str());
    jclass cls = Androidenv->GetObjectClass(Androidobj);
    jmethodID methodId = Androidenv->GetMethodID(cls, "onUiLoad", "([Ljava/lang/String;)I");
    if (methodId == 0) {
        return -99;
    }
    return Androidenv->CallIntMethod(Androidobj, methodId, urlString);
}
