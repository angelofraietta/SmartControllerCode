/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "stdafx.h"
#include "smutility.h"
#include "baseshellquestion.h"
/* implmentation for class BaseShellInterface */

/*
 * Class:     Jni_BaseShell
 * Method:    GetNumAttributes
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetNumAttributes
  (JNIEnv *, jclass, jint pQuestion, jint objKey)
{
  return BaseShellQuestion::GetNumAttributes ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey	// The key associated with the Identity
      );
}


/*
 * Class:     Jni_BaseShell
 * Method:    GetAttributeName
 * Signature: (IIILjava/lang/String;I)V
 */
extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetAttributeName
  (JNIEnv * env, jclass, jint pQuestion, jint objKey, jint attribute_key)
{
  char buf [256];
  *buf = 0;
  
  BaseShellQuestion::GetAttributeName ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) attribute_key, 	// The key associated with the attribute
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      );

  jstring ret = env->NewStringUTF(buf);
  return ret;
}

/*
 * Class:     Jni_BaseShell
 * Method:    GetAttribute
 * Signature: (IIILjava/lang/String;I)Z
 */
extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetAttribute
  (JNIEnv * env, jclass, jint pQuestion, jint objKey, jint attribute_key)
{
  char buf [256];
  *buf = 0;
  jstring ret = 0;
  
  if (BaseShellQuestion::GetAttribute ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) attribute_key, 	// The key associated with the attribute
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      ))
  {
     ret = env->NewStringUTF(buf);
  }
  return ret;
}


/*
 * Class:     Jni_BaseShell
 * Method:    SetAttribute
 * Signature: (IIILjava/lang/String;)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_BaseShell_SetAttribute
  (JNIEnv *env, jclass, jint pQuestion, jint objKey, jint attribute_key, jstring at_value)
{
  const char* new_value = env->GetStringUTFChars(at_value, NULL);
  return BaseShellQuestion::SetAttribute ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) attribute_key, 	// The key associated with the attribute
      new_value	// This has the attribute value returned as a null
      	// terminated string
      );
}  

/*
 * Class:     Jni_BaseShell
 * Method:    GetNumResetAttributes
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetNumResetAttributes
  (JNIEnv *, jclass, jint pQuestion, jint objKey)
{
  return BaseShellQuestion::GetNumResetAttributes ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey	// The key associated with the Identity
      );
}

/*
 * Class:     Jni_BaseShell
 * Method:    GetResetAttributeName
 * Signature: (IIILjava/lang/String;I)V
 */
extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetResetAttributeName
  (JNIEnv * env, jclass, jint pQuestion, jint objKey, jint attribute_key)
{
  char buf [256];
  *buf = 0;

  BaseShellQuestion::GetResetAttributeName ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) attribute_key, 	// The key associated with the attribute
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      );

  jstring ret = env->NewStringUTF(buf);
  return ret;
}

/*
 * Class:     Jni_BaseShell
 * Method:    GetResetAttribute
 * Signature: (IIILjava/lang/String;I)Z
 */
extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetResetAttribute
  (JNIEnv * env, jclass, jint pQuestion, jint objKey, jint attribute_key)
{
  char buf [256];
  *buf = 0;
  jstring ret = 0;

  if (BaseShellQuestion::GetResetAttribute ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) attribute_key, 	// The key associated with the attribute
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      ))
  {
    ret = env->NewStringUTF(buf);
  }
  
  return ret;
}

/*
 * Class:     Jni_BaseShell
 * Method:    SetResetAttribute
 * Signature: (IIILjava/lang/String;)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_BaseShell_SetResetAttribute
  (JNIEnv *env, jclass, jint pQuestion, jint objKey, jint attribute_key, jstring at_value)
{
  const char* new_value = env->GetStringUTFChars(at_value, NULL);
  return BaseShellQuestion::SetResetAttribute ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) attribute_key, 	// The key associated with the attribute
      new_value	// This has the attribute value returned as a null
      	// terminated string
      );
}

/*
 * Class:     Jni_BaseShell
 * Method:    Reset
 * Signature: (II)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_BaseShell_Reset
  (JNIEnv *, jclass, jint pQuestion, jint objKey)
{
  BaseShellQuestion::Reset ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey);
}

/*
 * Class:     Jni_BaseShell
 * Method:    Send
 * Signature: (II)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_BaseShell_Send
  (JNIEnv *, jclass, jint pQuestion, jint objKey)
{
  BaseShellQuestion::Send ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey);
}


/*
 * Class:     Jni_BaseShell
 * Method:    Create
 * Signature: (ILjava/lang/String;I)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_Create
  (JNIEnv *env, jclass, jint pQuestion, jstring j_type, jint pParent)
{
    const char* object_type = env->GetStringUTFChars(j_type, NULL);
    
    P_BASESHELL ret = BaseShellQuestion::Create ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      object_type, (P_PATCH) pParent);

   return ret.Key();
}

/*
 * Class:     Jni_BaseShell
 * Method:    GetNumInlets
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetNumInlets
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell)
{
  return BaseShellQuestion::GetNumInlets ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell);
  }

/*
 * Class:     Jni_BaseShell
 * Method:    GetNumOutlets
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetNumOutlets
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell)
{
  return BaseShellQuestion::GetNumOutlets ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell);
  }


/*
 * Class:     Jni_BaseShell
 * Method:    GetInletName
 * Signature: (IIILjava/lang/String;I)V
 */
extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetInletName
  (JNIEnv * env, jclass, jint pQuestion, jint objKey, jint inlet_num)
{
  char buf [256];

  BaseShellQuestion::GetInletName ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) inlet_num, 	// The key associated with the attribute
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      );

  jstring ret = env->NewStringUTF(buf);
  return ret;
}


/*
 * Class:     Jni_BaseShell
 * Method:    GetOutletName
 * Signature: (IIILjava/lang/String;I)V
 */
extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetOutletName
  (JNIEnv * env, jclass, jint pQuestion, jint objKey, jint outlet_num)

{
  char buf [256];

  BaseShellQuestion::GetOutletName ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) outlet_num, 	// The key associated with the attribute
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      );

  jstring ret = env->NewStringUTF(buf);
  return ret;
}


/*
 * Class:     Jni_BaseShell
 * Method:    GetNumInletConnectors
 * Signature: (III)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetNumInletConnectors
  (JNIEnv *, jclass, jint pQuestion, jint objKey, jint inlet_num)
{
  return BaseShellQuestion::GetNumInletConnectors ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) inlet_num 	// The key associated with the attribute
      );

}

/*
 * Class:     Jni_BaseShell
 * Method:    GetNumOutletConnectors
 * Signature: (III)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetNumOutletConnectors
  (JNIEnv *, jclass, jint pQuestion, jint objKey, jint outlet_num)
{
  return BaseShellQuestion::GetNumOutletConnectors ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      (unsigned) outlet_num 	// The key associated with the attribute
      );

}


/*
 * Class:     Jni_BaseShell
 * Method:    CanConnectInlet
 * Signature: (IIII)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_BaseShell_CanConnectInlet
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell, jint wSocketNum, jint dwpCon)
{
  return BaseShellQuestion::CanConnectInlet ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell, wSocketNum, (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_BaseShell
 * Method:    CanConnectOutlet
 * Signature: (IIII)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_BaseShell_CanConnectOutlet
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell, jint wSocketNum, jint dwpCon)
{
  return BaseShellQuestion::CanConnectOutlet ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell, wSocketNum, (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_BaseShell
 * Method:    GetInletConnector
 * Signature: (IIII)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetInletConnector
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell, jint wSocketNum, jint Index)
{
  P_CONNECTOR pCon = BaseShellQuestion::GetInletConnector ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell, wSocketNum, Index);

  return pCon.Key();
}

/*
 * Class:     Jni_BaseShell
 * Method:    GetOutletConnector
 * Signature: (IIII)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetOutletConnector
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell, jint wSocketNum, jint Index)
{
  P_CONNECTOR pCon = BaseShellQuestion::GetOutletConnector ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell, wSocketNum, Index);

  return pCon.Key();
}


/*
 * Class:     Jni_BaseShell
 * Method:    FindInletConnectorIndex
 * Signature: (IIII)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_FindInletConnectorIndex
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell, jint wSocketNum, jint dwpCon)
{
  return BaseShellQuestion::FindInletConnectorIndex ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell, wSocketNum, (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_BaseShell
 * Method:    FindOutletConnectorIndex
 * Signature: (IIII)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_FindOutletConnectorIndex
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell, jint wSocketNum, jint dwpCon)
{
  return BaseShellQuestion::FindOutletConnectorIndex ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell, wSocketNum, (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_BaseShell
 * Method:    SwapOutletConnector
 * Signature: (IIIII)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_BaseShell_SwapOutletConnector
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell, jint outlet_number, jint connector1_index, jint connector2_index)
{
  BaseShellQuestion::SwapOutletConnector ((PresentationQuestion*) pQuestion, 	
      (P_BASESHELL) dwpShell, 	// The BaseShell key
      outlet_number, 	// The outlet number containg the connectors
      connector1_index, 	// The index of the first connector within the outlet
      connector2_index	// The index of the second connector within the outlet
      );
}


extern "C" JNIEXPORT jint JNICALL Java_Jni_BaseShell_GetNumObjectTypes
  (JNIEnv *, jclass, jint pQuestion)
{
  return BaseShellQuestion::GetNumObjectTypes ((PresentationQuestion* )pQuestion 	// Pointer to the Presentation Question used to get the
      	// answer
      );
}


extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetObjectType
  (JNIEnv * env, jclass, jint pQuestion, jint attribute_key)
{
  char buf [256];

  BaseShellQuestion::GetObjectType ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (unsigned) attribute_key, 	// The key associated with the attribute
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      );

  jstring ret = env->NewStringUTF(buf);
  return ret;
}

extern "C" JNIEXPORT jboolean JNICALL Java_Jni_BaseShell_CanHaveChildren
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell)
{
	return   BaseShellQuestion::CanHaveChildren ((PresentationQuestion*) pQuestion, 	
																									 (P_BASESHELL) dwpShell);

}

/*
 * Class:     Jni_BaseShell
 * Method:    CanChangeSize
 * Signature: (II)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_BaseShell_CanChangeSize
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell)
{
	return   BaseShellQuestion::CanChangeSize ((PresentationQuestion*) pQuestion, 	
																									 (P_BASESHELL) dwpShell);

}

extern "C" JNIEXPORT jstring JNICALL Java_Jni_BaseShell_GetDefaultAttribute
  (JNIEnv * env, jclass, jint pQuestion, jint objKey)
{
  char buf [256];
  *buf = 0;
  jstring ret = 0;

  if (BaseShellQuestion::GetDefaultAttribute ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) objKey, 	// The key associated with the Identity
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      ))
  {
     ret = env->NewStringUTF(buf);
  }
  return ret;
}

