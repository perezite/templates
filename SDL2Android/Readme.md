# Content
* Features a deployable NDK app
* Features linking an external precompiled libaray (OpenGLEngine) to the app

# Build and Run
cd OpenGLEngine/jni
ndk-build
Copy: OpenGLEngine/Engine/engine.h -> Application/jni/src/include
Copy: OpenGLEngine/libs -> Application/jni/src/libs
cd Application
build-and-run.bat

# Debug
build-and-run.bat debug

# Reference
https://www.youtube.com/watch?v=iVir4N55YQg
http://stackoverflow.com/questions/9026152/how-to-run-an-android-app-on-the-device-with-ant