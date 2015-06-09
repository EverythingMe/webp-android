#ifndef _SWIG_UTILS_H_
#define _SWIG_UTILS_H_

#include <stdlib.h>
#include <jni.h>
#include <android/log.h>

#define LOG(x...) __android_log_print(6,"evme.jni",x)

// In the future we can replace it to throwing actual exceptions.
// Right now I think it's better to print the error to the log and return null.
#define ThrowException(jenv,type,msg) LOG("Error: %s(%d) " msg, __FILE__, __LINE__)
#define SWIG_JavaThrowException ThrowException

///////////////// Utilities, taken from SWIG /////////////////////

#ifdef __cplusplus
extern "C" {
#endif

int SWIG_JavaArrayInSchar (JNIEnv *jenv, jbyte **jarr, unsigned char **carr, jbyteArray input);

jbyteArray SWIG_JavaArrayOutSchar (JNIEnv *jenv, unsigned char *result, jsize sz);

void SWIG_JavaArrayArgoutSchar (JNIEnv *jenv, jbyte *jarr, unsigned char *carr, jbyteArray input);

#ifdef __cplusplus
}
#endif
#endif
