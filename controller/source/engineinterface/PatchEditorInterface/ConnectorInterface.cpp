/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* implmentation for class ConnectorInterface */
#include "stdafx.h"
#include "smutility.h"
#include "typedefs.h"
#include "interfacetypes.h"
#include "connectorquestion.h"

#include "presentationquestion.h"
/*
 * Class:     Jni_Connector
 * Method:    IsValid
 * Signature: (II)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_Connector_IsValid
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  return ConnectorQuestion::IsValid (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);
  }

/*
 * Class:     Jni_Connector
 * Method:    Create
 * Signature: (I)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Connector_Create
  (JNIEnv *, jclass, jint pQuestion)
{
  P_CONNECTOR pCon = ConnectorQuestion::Create(getPresentation (pQuestion));
  return pCon.Key();
  
}

/*
 * Class:     Jni_Connector
 * Method:    Delete
 * Signature: (II)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Connector_Delete
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  ConnectorQuestion::Delete (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_Connector
 * Method:    SetOutletNum
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Connector_SetOutletNum
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon, jint wSocketNum)
{
  ConnectorQuestion::SetOutletNum (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon, wSocketNum);
}

/*
 * Class:     Jni_Connector
 * Method:    SetOutletBase
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Connector_SetOutletBase
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon, jint dwpShell)
{
  ConnectorQuestion::SetOutletBase (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon, (P_BASESHELL) dwpShell);
}

/*
 * Class:     Jni_Connector
 * Method:    SetInletNum
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Connector_SetInletNum
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon, jint wSocketNum)
{
  ConnectorQuestion::SetInletNum (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon, wSocketNum);
}
/*
 * Class:     Jni_Connector
 * Method:    SetInletBase
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Connector_SetInletBase
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon, jint dwpShell)
{
  ConnectorQuestion::SetInletBase (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon, (P_BASESHELL) dwpShell);
}

/*
 * Class:     Jni_Connector
 * Method:    MakeConnection
 * Signature: (II)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_Connector_MakeConnection
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  return ConnectorQuestion::MakeConnection (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_Connector
 * Method:    GetOutletNum
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Connector_GetOutletNum
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  return ConnectorQuestion::GetOutletNum (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_Connector
 * Method:    GetOutletIndex
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Connector_GetOutletIndex
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  return ConnectorQuestion::GetOutletIndex (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);
}


/*
 * Class:     Jni_Connector
 * Method:    GetInletNum
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Connector_GetInletNum
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  return ConnectorQuestion::GetInletNum (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_Connector
 * Method:    GetOutletBase
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Connector_GetOutletBase
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  P_BASESHELL dwpShell = ConnectorQuestion::GetOutletBase (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);

  return dwpShell.Key();
}


/*
 * Class:     Jni_Connector
 * Method:    GetInletBase
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Connector_GetInletBase
  (JNIEnv *, jclass, jint pQuestion, jint dwpCon)
{
  P_BASESHELL dwpShell = ConnectorQuestion::GetInletBase (getPresentation (pQuestion), 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_CONNECTOR) dwpCon);

  return dwpShell.Key();
}


