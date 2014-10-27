/*****************************************************************
|
|      Android JNI Interface
|
|      (c) 2002-2012 Plutinosoft LLC
|      Author: Sylvain Rebaud (sylvain@plutinosoft.com)
|
 ****************************************************************/

/*----------------------------------------------------------------------
|       includes
+---------------------------------------------------------------------*/
#include <assert.h>
#include <jni.h>
#include <string.h>
#include <sys/types.h>

#include "platinum-jni.h"
#include "Platinum.h"
#include "PltMicroMediaController.h"

#include <android/log.h>

/*----------------------------------------------------------------------
|   logging
+---------------------------------------------------------------------*/
NPT_SET_LOCAL_LOGGER("platinum.android.jni")

typedef NPT_Reference<PLT_MicroMediaController> PLT_MicroMediaControllerReference;

PLT_CtrlPointReference g_ctrlpoint;
PLT_MicroMediaControllerReference g_usrCP;

/*----------------------------------------------------------------------
|   functions
+---------------------------------------------------------------------*/
__attribute__((constructor)) static void onDlOpen(void)
{
}

/*----------------------------------------------------------------------
|    JNI_OnLoad
+---------------------------------------------------------------------*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    NPT_LogManager::GetDefault().Configure("plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.outputs=2;.ConsoleHandler.colors=false;.ConsoleHandler.filter=59");

    //save pointer "JavaVM"

    return JNI_VERSION_1_4;
}

/*
 * Class:     com_plutinosoft_platinum_UPnP
 * Method:    _init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_plutinosoft_platinum_UPnP__1init(JNIEnv *env, jclass)
{
    NPT_LOG_INFO("init");
    PLT_UPnP* self = new PLT_UPnP();

    // Create control point
    NPT_LOG_INFO("Create control point");
    PLT_CtrlPointReference ctrlPoint(new PLT_CtrlPoint());
    g_ctrlpoint = ctrlPoint;

    // Create controller
    NPT_LOG_INFO("Create controller");
    PLT_MicroMediaControllerReference controller(new PLT_MicroMediaController(ctrlPoint));
    g_usrCP = controller;

    NPT_LOG_INFO("Add control point");
    self->AddCtrlPoint(ctrlPoint);    

    return (jlong)self;
}

/*
 * Class:     com_plutinosoft_platinum_UPnP
 * Method:    _start
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_plutinosoft_platinum_UPnP__1start(JNIEnv *, jclass, jlong _self)
{
    NPT_LOG_INFO("start");
    PLT_UPnP* self = (PLT_UPnP*)_self;
    
    return self->Start();
}

/*
 * Class:     com_plutinosoft_platinum_UPnP
 * Method:    _stop
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_plutinosoft_platinum_UPnP__1stop(JNIEnv *, jclass, jlong _self)
{
    NPT_LOG_INFO("stop");
    PLT_UPnP* self = (PLT_UPnP*)_self;
    
    return self->Stop();
}

JNIEXPORT jint 
JNICALL Java_com_plutinosoft_platinum_UPnP__1setServerId(JNIEnv *env, jclass, jstring _self)
{
    jboolean  ret;
    const char* uuid = env->GetStringUTFChars(_self, &ret);
    NPT_LOG_INFO_1("set meida server id:%s\n",uuid);

    if (!g_usrCP.IsNull()){
    	g_usrCP->SetUUIDServer(uuid);
    }else{
	NPT_LOG_INFO("g_usrCP is null");
    }

    return 0;
}

JNIEXPORT jint 
JNICALL Java_com_plutinosoft_platinum_UPnP__1setRenderId(JNIEnv *env, jclass, jstring _self)
{
    jboolean ret;
    const char* uuid = env->GetStringUTFChars(_self, &ret);
    NPT_LOG_INFO_1("set meida render id:%s\n",uuid);

    if (!g_usrCP.IsNull()){
    	g_usrCP->SetUUIDRender(uuid);
    }else{
	NPT_LOG_INFO("g_usrCP is null");
    }

    return 0;
}


