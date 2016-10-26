LOCAL_PATH := $(call my-dir)

# OpenGLEngine module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := openGLSharedLibrary
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../lib/OpenGLEngine/$(TARGET_ARCH_ABI)/libOpenGLEngine.so
include $(PREBUILT_SHARED_LIBRARY)

# SDL2 module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := SDL2
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../lib/SDL2/$(TARGET_ARCH_ABI)/libSDL2.so
include $(PREBUILT_SHARED_LIBRARY)

# Application Module
#####################
include $(CLEAR_VARS)
LOCAL_MODULE := main
MY_CODE_PATH := $(LOCAL_PATH)/../../../../src
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include
LOCAL_SRC_FILES := $(MY_CODE_PATH)/SDL_android_main.c \
    $(MY_CODE_PATH)/SDL_main.cpp
LOCAL_SHARED_LIBRARIES := SDL2 openGLSharedLibrary
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)