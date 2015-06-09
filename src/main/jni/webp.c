#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <webp/decode.h>
#include "swig_utils.h"

JNIEXPORT
jbyteArray Java_me_everything_common_graphics_WebPDecoder_decodeRGBAnative( JNIEnv *jenv, jclass jcls,
		jbyteArray jencoded, jlong jencodedLength,
		jintArray jwidth, jintArray jheight)
{
	jbyteArray jresult = 0 ;
	uint8_t *encoded = (uint8_t *) 0 ;
	size_t encodedLength ;
	int *width = (int *) 0 ;
	int *height = (int *) 0 ;
	jbyte *jarr1 ;
	int temp3 ;
	int temp4 ;
	uint8_t *result = 0 ;

	if (!SWIG_JavaArrayInSchar(jenv, &jarr1, &encoded, jencoded)) return 0;
	encodedLength = (size_t)jencodedLength;
	{
		if (!jwidth) {
			ThrowException(jenv, SWIG_JavaNullPointerException, "array null");
			return 0;
		}
		if ((*jenv)->GetArrayLength(jenv, jwidth) == 0) {
			ThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
			return 0;
		}
		width = &temp3;
	}
	{
		if (!jheight) {
			ThrowException(jenv, SWIG_JavaNullPointerException, "array null");
			return 0;
		}
		if ((*jenv)->GetArrayLength(jenv, jheight) == 0) {
			ThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
			return 0;
		}
		height = &temp4;
	}
	result = (uint8_t *)WebPDecodeARGB((uint8_t const *)encoded,encodedLength,width,height);
	jresult = SWIG_JavaArrayOutSchar(jenv, result, result ? (*width) * (*height) * 4 : 0);
	SWIG_JavaArrayArgoutSchar(jenv, jarr1, encoded, jencoded);
	{
		jint jvalue = (jint)temp3;
		(*jenv)->SetIntArrayRegion(jenv, jwidth, 0, 1, &jvalue);
	}
	{
		jint jvalue = (jint)temp4;
		(*jenv)->SetIntArrayRegion(jenv, jheight, 0, 1, &jvalue);
	}
	free(encoded);

	free(result);
	return jresult;

	return 0;
}
