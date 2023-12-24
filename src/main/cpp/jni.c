#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <stdlib.h>
#include <hl.h>
#include "out/_std/String.h"
#include <stdlib.h>

#define JNI_TAG "JNI"

extern int main(int argc, char *argv[]); // assuming that haxe->hl/c entry point is included (which includes hlc_main.c which includes the main function)

AAssetManager * _assetsManager;
char* storagePath;

int _tmpSize;

char* _JString2CStr(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env,"GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if(alen > 0) {
        rtn = (char*)malloc(alen+1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen]=0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba,0);
    return rtn;
}

JNIEXPORT int JNICALL Java_org_haxe_HashLinkActivity_startHL(JNIEnv* env, jclass cls) {
    return main(0, NULL);
}

/** 初始Assets */
JNIEXPORT void JNICALL Java_org_haxe_HashLinkActivity_initAssets(JNIEnv *env, jclass type, jobject assetManager, jstring strDir_) {
    __android_log_print(ANDROID_LOG_VERBOSE, JNI_TAG,"initAssets");
    _assetsManager = AAssetManager_fromJava(env, assetManager);
    storagePath = _JString2CStr(env, strDir_);
}

/** 获取创建的副本大小 */
JNIEXPORT jint JNICALL Java_org_haxe_HashLinkActivity_tmpSize() {
    return _tmpSize;
}

/** 通过路径读取assets资源 */
JNIEXPORT jbyteArray JNICALL Java_org_haxe_HashLinkActivity_getAssetBytes(String path){
    char* utf8path = hl_to_utf8(path->bytes);
    AAsset* asset = AAssetManager_open(_assetsManager, utf8path, AASSET_MODE_UNKNOWN);
    if (NULL != asset)
    {
        off_t bufSize = AAsset_getLength(asset);
        // vbyte *pBuf = (vbyte *) malloc(bufSize + 1);
        vbyte *pBuf = (vbyte *) hl_gc_alloc_noptr(bufSize + 1);
//        memset(pBuf, 0, bufSize + 1);
        _tmpSize = AAsset_read(asset, pBuf, bufSize);
//        free(pBuf);
        AAsset_close(asset);
        return pBuf;
    }
    else
    {
        __android_log_print(ANDROID_LOG_ERROR, JNI_TAG, "Assets load fail:%s", utf8path);
        return NULL;
    }
}

JNIEXPORT vbyte* JNICALL Java_org_haxe_HashLinkActivity_loadAndroid(vstring* name) {

    char savepath[1024];
    sprintf(savepath, "%s/%s", storagePath, "prefs.json");

    FILE* f;
    f = fopen(savepath, "rb");
    if (f == NULL) {
        return "";
    }
    int sz = 0;
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* c = (char*)hl_gc_alloc_noptr(sz + 1);
    c[sz] = 0;
    fread(c, 1, sz, f);
    fclose(f);
    return c;

    // (*jvm)->AttachCurrentThread(jvm, &thisEnv, 0); // this is important to avoid threading errors
    // if (thisEnv != NULL) {
    //     jclass cls = (*thisEnv)->FindClass(thisEnv, "org/haxe/HashLinkActivity");
    //     jmethodID method = (*thisEnv)->GetStaticMethodID(thisEnv, cls, "loadData", "(Ljava/lang/String;)Ljava/lang/String;");
    // }

    // char* cname = hl_to_utf8(name->bytes);
    // __android_log_print(ANDROID_LOG_DEBUG, "JNI.c", "loading... %s", cname);

    // // Is this necessary? Who knows! Better safe than seg fault though.
    // char* buf = strdup(cname);
    // jstring jstrBuf = (*thisEnv)->NewStringUTF(thisEnv, buf);

    // jstring result = (*thisEnv)->NewStringUTF(thisEnv, "null");
    // if (method > 0)
    //     result = (jstring)(*thisEnv)->CallStaticObjectMethod(thisEnv, cls, method, jstrBuf);

    // char* cresult = (*thisEnv)->GetStringUTFChars(thisEnv, result, 0);
    // __android_log_print(ANDROID_LOG_DEBUG, "JNI.c", "returned... %s", cresult);

    // free(buf); // Free the string
    // return cresult;
    return "";
}

JNIEXPORT jstring JNICALL Java_org_haxe_HashLinkActivity_saveAndroid(vstring* name, vstring* data) {
    // (*jvm)->AttachCurrentThread(jvm, &thisEnv, 0); // this is important to avoid threading errors
    // jclass cls = (*thisEnv)->FindClass(thisEnv, "org/haxe/HashLinkActivity");
    // jmethodID method = (*thisEnv)->GetStaticMethodID(thisEnv, cls, "saveData", "(Ljava/lang/String;Ljava/lang/String;)V");

    char* cname = hl_to_utf8(name->bytes);
    char* cdata = hl_to_utf8(data->bytes);

    char* bname = strdup(cname);
    char* bdata = strdup(cdata);

    __android_log_print(ANDROID_LOG_DEBUG, "JNI.c", "saving %s: %s", bname, bdata);

    // jstring jname = (*thisEnv)->NewStringUTF(thisEnv, bname);
    // jstring jdata = (*thisEnv)->NewStringUTF(thisEnv, bdata);

    // if (method > 0)
    //    (*thisEnv)->CallStaticVoidMethod(thisEnv, cls, method, jname, jdata);

    char savepath[1024];
    sprintf(savepath, "%s/%s", storagePath, "prefs.json");

    FILE* f;
    f = fopen(savepath, "wb");
    fwrite(bdata, 1, strlen(bdata), f);
    fclose(f);
    

    free(bname);
    free(bdata);
}

DEFINE_PRIM(_BYTES, hl_get_storage_path, _NO_ARG);

HL_PRIM vbyte* HL_NAME(hl_get_storage_path)() { return storagePath; }