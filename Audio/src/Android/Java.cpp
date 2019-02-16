#ifdef __ANDROID__
#include "Java.h"
#include "../../build/Platform/Android/Application/SDL_android_main.h"
#include "../Logger.h"
#include <stdarg.h>

namespace sb
{
	std::map<std::string, jclass> Java::m_classes;
	std::map<JavaMethod, jmethodID> Java::m_methods;

	jint Java::callStaticIntMethod(std::string classDescriptor, std::string methodName, std::string methodDescriptor, ...)
	{
		static JNIEnv* jni = getJavaNativeInterface();

		if (m_classes.find(classDescriptor) == m_classes.end())
			loadClass(classDescriptor);

		JavaMethod method { m_classes[classDescriptor], methodName, methodDescriptor };
		if (m_methods.find(method) == m_methods.end())
			loadStaticMethod(method);

		va_list args;
		va_start(args, methodDescriptor);
			jint result = jni->CallStaticIntMethodV(m_classes[classDescriptor], m_methods[method], args);
		va_end(args);	

		return result;
	}

	jstring Java::newUtfString(std::string string) {
		static JNIEnv* jni = getJavaNativeInterface();
		return jni->NewStringUTF(string.c_str());
	}

	void Java::loadClass(std::string classDescriptor)
	{
		static JNIEnv* jni = getJavaNativeInterface();
		jclass theClass = jni->FindClass(classDescriptor.c_str());
		SB_ERROR_IF(theClass == NULL) << "unable to load java android class with descriptor " << classDescriptor << std::endl;

		m_classes[classDescriptor] = theClass;
	}

	void Java::loadStaticMethod(JavaMethod javaMethod)
	{
		static JNIEnv* jni = getJavaNativeInterface();
		jmethodID methodId = jni->GetStaticMethodID(javaMethod.theClass, javaMethod.name.c_str(), javaMethod.descriptor.c_str());
		SB_ERROR_IF(methodId == NULL) << "unable to load java android method " << javaMethod.name << std::endl;

		m_methods[javaMethod] = methodId;
	}
}

#endif