#include <jni.h>
#include <string>
#include <stdio.h>

JNIEnv* Androidenv;
jobject Androidobj;


extern int main(int, char**);


JNIEXPORT jint JNICALL
Java_com_gempyre_myapp_MainActivity_callMain
(JNIEnv* env, jobject obj) {
    Androidenv = env;
    Androidobj = obj;
    return main(0, nullptr);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    return JNI_VERSION_1_6;
}
    
int androidLoadUi(const std::string& url) {
    jstring urlString = Androidenv->NewStringUTF(url.c_str());
    jclass cls = Androidenv->GetObjectClass(Androidobj);
    jmethodID methodId = Androidenv->GetMethodID(cls, "onUiLoad", "([Ljava/lang/String;)I");
    if (methodId == 0) {
        return -99;
    }
    return Androidenv->CallIntMethod(Androidobj, methodId, urlString);
}
