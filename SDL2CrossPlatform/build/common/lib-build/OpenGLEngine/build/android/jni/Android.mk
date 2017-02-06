LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := OpenGLEngine

CODE_PATH := ../../../src

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(CODE_PATH)

LOCAL_SRC_FILES := $(CODE_PATH)/engine.cpp

LOCAL_LDLIBS := -lGLESv2

NDK_LIBS_OUT := $(LOCAL_PATH)/test

include $(BUILD_SHARED_LIBRARY)
