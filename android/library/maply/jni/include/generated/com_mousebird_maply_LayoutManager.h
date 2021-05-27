/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_mousebird_maply_LayoutManager */

#ifndef _Included_com_mousebird_maply_LayoutManager
#define _Included_com_mousebird_maply_LayoutManager
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    setMaxDisplayObjects
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_LayoutManager_setMaxDisplayObjects
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    updateLayout
 * Signature: (Lcom/mousebird/maply/ViewState;Lcom/mousebird/maply/ChangeSet;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_LayoutManager_updateLayout
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    hasChanges
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_LayoutManager_hasChanges
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    addClusterGenerator
 * Signature: (Lcom/mousebird/maply/ClusterGenerator;IZDD)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_LayoutManager_addClusterGenerator
  (JNIEnv *, jobject, jobject, jint, jboolean, jdouble, jdouble);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    removeClusterGenerator
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_LayoutManager_removeClusterGenerator
        (JNIEnv *, jobject, jint);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    clearClusterGenerators
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_LayoutManager_clearClusterGenerators
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_LayoutManager_nativeInit
  (JNIEnv *, jclass);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    initialise
 * Signature: (Lcom/mousebird/maply/Scene;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_LayoutManager_initialise
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_LayoutManager
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_LayoutManager_dispose
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
