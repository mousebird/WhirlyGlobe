/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_mousebird_maply_QuadLoaderBase */

#ifndef _Included_com_mousebird_maply_QuadLoaderBase
#define _Included_com_mousebird_maply_QuadLoaderBase
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    setFlipY
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_setFlipY
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    setDebugMode
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_setDebugMode
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    geoBoundsForTileNative
 * Signature: (IIILcom/mousebird/maply/Point2d;Lcom/mousebird/maply/Point2d;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_geoBoundsForTileNative
  (JNIEnv *, jobject, jint, jint, jint, jobject, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    boundsForTileNative
 * Signature: (IIILcom/mousebird/maply/Point2d;Lcom/mousebird/maply/Point2d;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_boundsForTileNative
  (JNIEnv *, jobject, jint, jint, jint, jobject, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    displayCenterForTileNative
 * Signature: (IIILcom/mousebird/maply/Point3d;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_displayCenterForTileNative
  (JNIEnv *, jobject, jint, jint, jint, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    cleanupNative
 * Signature: (Lcom/mousebird/maply/ChangeSet;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_cleanupNative
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
