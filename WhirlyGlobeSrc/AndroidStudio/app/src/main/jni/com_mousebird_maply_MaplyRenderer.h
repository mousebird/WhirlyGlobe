/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_mousebird_maply_MaplyRenderer */

#ifndef _Included_com_mousebird_maply_MaplyRenderer
#define _Included_com_mousebird_maply_MaplyRenderer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    setScene
 * Signature: (Lcom/mousebird/maply/Scene;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_setScene
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    setViewNative
 * Signature: (Lcom/mousebird/maply/View;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_setViewNative
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    setClearColor
 * Signature: (FFFF)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_setClearColor
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    teardown
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_MaplyRenderer_teardown
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    resize
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_MaplyRenderer_resize
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    render
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_render
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    setPerfInterval
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_setPerfInterval
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_nativeInit
  (JNIEnv *, jclass);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    initialise
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_initialise
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_MaplyRenderer
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_MaplyRenderer_dispose
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
