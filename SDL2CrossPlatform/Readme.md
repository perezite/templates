# Readme
The solution under build/SDL2CrossPlatform.sln contains a template Visual Studio 2015 solution for SDL 2.0.5, SDL_mixer 2.0.1 and SDL_image 2.0.1 for Android and Visual Studio

# Notes
For Android, the target API level has been set to 26 which seems to be the new requirement by the google play store. So, Android SDK 26 has to be installed.
Android SDK 26 requires Java Development Kit (JDK) version 1.8, which must be installed, so install that and set the path to it under Visual Studio 2015 -> Tools -> Options -> Cross Platform -> C++ -> Android -> Java SE Development Kit (VS 15 installs JDK 1.7 by default)
Also, I set the minimal API version to 19, because the application could not be run on lower versions (at least in the emulator)

In Main.cpp, there are two demos. Activate them by uncommenting them respectively. Demo1 features CrossPlatform OpenGL, Demo2 features Image Loading, Sound and Music from SDL.
You can run Demo1 or Demo2 but not both at the same time!

A compilation script for SDL2/SDL2_image/SDL2_mixer can be found under build/External/Android/lib-build/SDL2-2.0.5
