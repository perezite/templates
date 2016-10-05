LOCAL_PATH := $(call my-dir)

# External module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := openGLSharedLibrary
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../lib/OpenGLEngine/$(TARGET_ARCH_ABI)/libOpenGLEngine.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../include/OpenGLEngine
include $(PREBUILT_SHARED_LIBRARY)

# Application Module
#####################
include $(CLEAR_VARS)
LOCAL_MODULE := main

SDL_PATH := ../SDL2
MY_CODE_PATH := $(LOCAL_PATH)/../../../../../src
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
    $(MY_CODE_PATH)/main.cpp

LOCAL_SHARED_LIBRARIES := SDL2 openGLSharedLibrary

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
