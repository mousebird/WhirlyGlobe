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
 * Method:    getFlipY
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_QuadLoaderBase_getFlipY
  (JNIEnv *, jobject);

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

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    mergeLoaderReturn
 * Signature: (Lcom/mousebird/maply/LoaderReturn;Lcom/mousebird/maply/ChangeSet;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_mergeLoaderReturn
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    samplingLayerConnectNative
 * Signature: (Lcom/mousebird/maply/QuadSamplingLayer;Lcom/mousebird/maply/ChangeSet;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_samplingLayerConnectNative
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    samplingLayerDisconnectNative
 * Signature: (Lcom/mousebird/maply/QuadSamplingLayer;Lcom/mousebird/maply/ChangeSet;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_samplingLayerDisconnectNative
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    getFrameID
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_mousebird_maply_QuadLoaderBase_getFrameID
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    getGeneration
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_mousebird_maply_QuadLoaderBase_getGeneration
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    getZoomSlot
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_mousebird_maply_QuadLoaderBase_getZoomSlot
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    reloadNative
 * Signature: (Lcom/mousebird/maply/ChangeSet;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_reloadNative
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_nativeInit
  (JNIEnv *, jclass);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    initialise
 * Signature: (Lcom/mousebird/maply/SamplingParams;II)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_initialise
  (JNIEnv *, jobject, jobject, jint, jint);

/*
 * Class:     com_mousebird_maply_QuadLoaderBase
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_QuadLoaderBase_dispose
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
