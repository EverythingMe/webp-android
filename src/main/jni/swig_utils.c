#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include "swig_utils.h"

#define LOG(x...) __android_log_print(6,"evme.jni",x)

// In the future we can replace it to throwing actual exceptions.
// Right now I think it's better to print the error to the log and return null.
#define ThrowException(jenv,type,msg) LOG("Error: %s(%d) " msg, __FILE__, __LINE__)
#define SWIG_JavaThrowException ThrowException

///////////////// Utilities, taken from SWIG /////////////////////

int SWIG_JavaArrayInSchar (JNIEnv *jenv, jbyte **jarr, unsigned char **carr, jbyteArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetByteArrayElements(jenv, input, 0);
  if (!*jarr) {
	SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "failed to get byte array elements");
    return 0;
  }
  *carr = (unsigned char*) calloc(sz, sizeof(signed char));
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (unsigned char)(*jarr)[i];
  return 1;
}

jbyteArray SWIG_JavaArrayOutSchar (JNIEnv *jenv, unsigned char *result, jsize sz) {
  jbyte *arr;
  int i;
  jbyteArray jresult = (*jenv)->NewByteArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetByteArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jbyte)result[i];
  (*jenv)->ReleaseByteArrayElements(jenv, jresult, arr, 0);
  return jresult;
}

void SWIG_JavaArrayArgoutSchar (JNIEnv *jenv, jbyte *jarr, unsigned char *carr, jbyteArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jbyte)carr[i];
  (*jenv)->ReleaseByteArrayElements(jenv, input, jarr, 0);
}

