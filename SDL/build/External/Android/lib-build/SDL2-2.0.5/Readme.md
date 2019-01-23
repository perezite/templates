# Readme
This is the android library build for SDL2-2.0.5 with SDL2_mixer-2.0.1 and SDL2_image-2.0.1
Note that serveral soundfile formats in SDL_mixer-2.0.1/Android.mk have been disabled because I could not get them to compile. Among the deactivated ones are MP3 and FLAC.
Also, the webp format in SDL_image-2.0.1/Android.mk has been disabled for the same reason.

# Compile
Install the android native c++ developer suite in Visual Studio 2015
Go to $Android-SDK\SDK Manager.exe and open it as Admin. Install API 26 (this is the target platform for this library build). Also make sure that Android SDK Tools are installed and up to date
Set a path variable JAVA_HOME pointing to the path in Visual Studio 2015 -> Settings -> Options -> Cross Platform -> C++ -> Android -> Java SE Development Kit

Run BuildAndRun.bat to build the libraries and a test program. The test program is executed automatically if exactly on Android device is attached.
OR 
Simply run ndk-build to build the library