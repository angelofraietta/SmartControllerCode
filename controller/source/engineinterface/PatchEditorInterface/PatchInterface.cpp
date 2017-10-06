/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Implementation for class PatchInterface */
#include "stdafx.h"
#include "interfacetypes.h"
#include "patchquestion.h"
#include <stdio.h>

/*
 * Class:     Jni_Patch
 * Method:    DetachBaseShellObject
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_DetachBaseShellObject
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint dwpShell)
{
  PatchQuestion::DetachBaseShellObject ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, (P_BASESHELL) dwpShell);
}

/*
 * Class:     Jni_Patch
 * Method:    FindBaseShellPosition
 * Signature: (III)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_FindBaseShellPosition
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint dwpShell)
{
  return PatchQuestion::FindBaseShellPosition ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, (P_BASESHELL) dwpShell);
}

/*
 * Class:     Jni_Patch
 * Method:    AddBaseShell
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_AddBaseShell
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint dwpShell)
{
  PatchQuestion::AddBaseShell ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, (P_BASESHELL) dwpShell);
}

/*
 * Class:     Jni_Patch
 * Method:    NumberBaseShells
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_NumberBaseShells
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch)
{
  return  PatchQuestion::NumberBaseShells ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch);
}

/*
 * Class:     Jni_Patch
 * Method:    FindBaseShell
 * Signature: (III)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_FindBaseShell
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint index)
{
  P_BASESHELL pShell = PatchQuestion::FindBaseShell ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, index);

  return pShell.Key();
}
/*
 * Class:     Jni_Patch
 * Method:    DetachConnector
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_DetachConnector
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint dwpCon)
{
  PatchQuestion::DetachConnector ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, (P_CONNECTOR) dwpCon);
}

/*
 * Class:     Jni_Patch
 * Method:    AddConnector
 * Signature: (III)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_AddConnector
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint dwpCon)
{
  PatchQuestion::AddConnector ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, (P_CONNECTOR) dwpCon);
}


/*
 * Class:     Jni_Patch
 * Method:    NumberConnectors
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_NumberConnectors
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch)
{
  return  PatchQuestion::NumberConnectors ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch);
}


/*
 * Class:     Jni_Patch
 * Method:    FindConnector
 * Signature: (III)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_FindConnector
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint index)
{
  P_CONNECTOR pCon = PatchQuestion::FindConnector ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, index);

  return pCon.Key();
}


/*
 * Class:     Jni_Patch
 * Method:    GetDeadConnector
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_GetDeadConnector
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch)
{
  P_CONNECTOR pCon = PatchQuestion::GetDeadConnector ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch);

  return pCon.Key();
}


/*
 * Class:     Jni_Patch
 * Method:    AddInlet
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_AddInlet
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch)
{
  P_BASESHELL pShell = PatchQuestion::AddInlet ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch);

  return pShell.Key();
}


/*
 * Class:     Jni_Patch
 * Method:    AddOutlet
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_AddOutlet
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch)
{
  P_BASESHELL pShell = PatchQuestion::AddOutlet ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch);

  return pShell.Key();
}


/*
 * Class:     Jni_Patch
 * Method:    MakeNew
 * Signature: (ILjava/lang/String;)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_MakeNew
  (JNIEnv *env, jclass, jint pQuestion, jstring at_value)
{
  const char* name = env->GetStringUTFChars(at_value, NULL);
  P_PATCH pPatch =  PatchQuestion::MakeNew ((PresentationQuestion*) pQuestion,
  name);

  return pPatch.Key();

}

/*
 * Class:     Jni_Patch
 * Method:    SetFileName
 * Signature: (IILjava/lang/String;)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_SetFileName
  (JNIEnv *env, jclass, jint pQuestion, jint pPatch, jstring at_value)
{
  const char* name = env->GetStringUTFChars(at_value, NULL);

  PatchQuestion::SetFileName((PresentationQuestion*) pQuestion,
  (P_PATCH) pPatch, name);
}

/*
 * Class:     Jni_Patch
 * Method:    LoadPatchFile
 * Signature: (ILjava/lang/String;I)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_LoadPatchFile
  (JNIEnv *env, jclass, jint pQuestion, jstring file_name, jint dwpParent)
{
  const char* name = env->GetStringUTFChars(file_name, NULL);
  P_PATCH pPatch = PatchQuestion::LoadPatchFile ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      name, (P_PATCH) dwpParent);
  printf ("Patch Key %u\r\n", pPatch.Key());
  return pPatch.Key();
}
/*
 * Class:     Jni_Patch
 * Method:    GetFileName
 * Signature: (II)Ljava/lang/String;
 */
extern "C" JNIEXPORT jstring JNICALL Java_Jni_Patch_GetFileName
  (JNIEnv * env, jclass, jint pQuestion, jint objKey)
{
  char buf [256];

  PatchQuestion::GetFileName ((PresentationQuestion* )pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) objKey, 	// The key associated with the Identity
      buf, 	// This has the attribute value returned as a null
      	// terminated string
      sizeof(buf)	// The length of the ret_value buffer
      );

  jstring ret = env->NewStringUTF(buf);
  return ret;
}


/*
 * Class:     Jni_Patch
 * Method:    Save
 * Signature: (IILjava/lang/String;)Z
 */
extern "C" JNIEXPORT jboolean JNICALL Java_Jni_Patch_Save
  (JNIEnv *env, jclass, jint pQuestion, jint dwpPatch, jstring file_name)
{
    const char* name = env->GetStringUTFChars(file_name, NULL);

    return PatchQuestion::Save ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, name);

}

/*
 * Class:     Jni_Patch
 * Method:    Destroy
 * Signature: (II)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_Destroy
  (JNIEnv *, jclass, jint pQuestion, jint pPatch)
{
  PatchQuestion::Destroy((PresentationQuestion*) pQuestion,
  (P_PATCH) pPatch);
}


/*
 * Class:     Jni_Patch
 * Method:    SwapOutlets
 * Signature: (IIII)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_SwapOutlets
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint Outlet1, jint Outlet2)
{
  PatchQuestion::SwapOutlets ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, Outlet1, Outlet2);
}

/*
 * Class:     Jni_Patch
 * Method:    SwapInlets
 * Signature: (IIII)V
 */
extern "C" JNIEXPORT void JNICALL Java_Jni_Patch_SwapInlets
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint inlet1, jint inlet2)
{
  PatchQuestion::SwapInlets ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, inlet1, inlet2);
}


/*
 * Class:     Jni_Patch
 * Method:    GetInlet
 * Signature: (III)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_GetInlet
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint SocketNum)
{
  P_BASESHELL pShell = PatchQuestion::GetInlet ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, SocketNum);
  return pShell.Key();
}
/*
 * Class:     Jni_Patch
 * Method:    GetOutlet
 * Signature: (III)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_GetOutlet
  (JNIEnv *, jclass, jint pQuestion, jint dwpPatch, jint SocketNum)
{
  P_BASESHELL pShell = PatchQuestion::GetOutlet ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_PATCH) dwpPatch, SocketNum);
  return pShell.Key();
}

/*
 * Class:     Jni_Patch
 * Method:    GetOutletPortNumber
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_GetOutletPortNumber
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell)
{
  return  PatchQuestion::GetOutletPortNumber ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell);
}

/*
 * Class:     Jni_Patch
 * Method:    GetInletPortNumber
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_GetInletPortNumber
  (JNIEnv *, jclass, jint pQuestion, jint dwpShell)
{
  return  PatchQuestion::GetInletPortNumber ((PresentationQuestion*) pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      (P_BASESHELL) dwpShell);
}


/*
 * Class:     Jni_Patch
 * Method:    NumberPatches
 * Signature: (I)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_NumberPatches
  (JNIEnv *, jclass, jint pQuestion)
{
  return PatchQuestion::NumberPatches((PresentationQuestion*) pQuestion);
}

/*
 * Class:     Jni_Patch
 * Method:    GetPatch
 * Signature: (II)I
 */
extern "C" JNIEXPORT jint JNICALL Java_Jni_Patch_GetPatch
  (JNIEnv *, jclass, jint pQuestion, jint index)
{
  P_PATCH pPatch = PatchQuestion::GetPatch((PresentationQuestion*) pQuestion, index);
  return pPatch.Key();
}

