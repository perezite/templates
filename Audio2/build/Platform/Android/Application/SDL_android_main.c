/*
SDL_android_main.c, placed in the public domain by Sam Lantinga  3/13/14
*/

#include "SDL_android_main.h"

/* Include the SDL main definition header */
#include "SDL2/SDL_main.h"

JNIEnv* g_jni;

int main(int argc, char *args[]);

/*******************************************************************************
Functions called by JNI
*******************************************************************************/
#include <jni.h>

JNIEnv* getJavaNativeInterface()
{
	return g_jni;
}

/* Called before SDL_main() to startLevel JNI bindings in SDL library */
extern void SDL_Android_Init(JNIEnv* env, jclass cls);

// release java audio
void releaseJavaAudio(JNIEnv* env)
{	
	jclass theClass = (*env)->FindClass(env,"org/libsdl/app/Audio"); 
	jmethodID methodId = (*env)->GetStaticMethodID(env, theClass, "release", "()V");
	(*env)->CallStaticVoidMethod(env, theClass, methodId);
}

/* Start up the SDL app */
JNIEXPORT int JNICALL Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject array)
{
	int i;
	int argc;
	int status;

	/* This interface could expand with ABI negotiation, callbacks, etc. */
	SDL_Android_Init(env, cls);

	SDL_SetMainReady();

	/* store the jni */
	g_jni = env;

	/* Prepare the arguments. */

	int len = (*env)->GetArrayLength(env, array);
	char* argv[1 + len + 1];
	argc = 0;
	/* Use the name "app_process" so PHYSFS_platformCalcBaseDir() works.
	https://bitbucket.org/MartinFelis/love-android-sdl2/issue/23/release-build-crash-on-start
	*/
	argv[argc++] = SDL_strdup("app_process");
	for (i = 0; i < len; ++i) {
		const char* utf;
		char* arg = NULL;
		jstring string = (*env)->GetObjectArrayElement(env, array, i);
		if (string) {
			utf = (*env)->GetStringUTFChars(env, string, 0);
			if (utf) {
				arg = SDL_strdup(utf);
				(*env)->ReleaseStringUTFChars(env, string, utf);
			}
			(*env)->DeleteLocalRef(env, string);
		}
		if (!arg) {
			arg = SDL_strdup("");
		}
		argv[argc++] = arg;
	}
	argv[argc] = NULL;


	/* Run the application. */
	status = main(argc, argv);

	/* Release the arguments. */

	for (i = 0; i < argc; ++i) {
		SDL_free(argv[i]);
	}

	/* Do not issue an exit or the whole application will terminate instead of just the SDL thread */
	/* Well, actually, we do it anyways, but first, we clean up  the audio*/
	releaseJavaAudio(env);
	exit(status); 

	// return status;
}

/* vi: set ts=4 sw=4 expandtab: */
