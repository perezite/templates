echo Note: Set the Environment variables in this batch variable first!
echo Note: Also set the variables in examples/android/local.properties first!
pause

rem Environment variables
set NdkPath=C:/ProgramData/Microsoft/AndroidNDK64/android-ndk-r11c
set makeCommand=mingw32-make

rem Compile SFML
cd Build/armeabi-v7a
cmake -G "MinGW Makefiles" -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=%NdkPath% -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_BUILD_TYPE=Debug ../..
%makeCommand% && %makeCommand% install

cd ../x86
cmake -G "MinGW Makefiles" -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=%NdkPath% -DCMAKE_ANDROID_ARCH_ABI=x86 -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_BUILD_TYPE=Debug ../..
%makeCommand% && %makeCommand% install

cd ../..

rem Compile Example for armeabi-v7a
cd examples/android
call gradlew assembleDebug
call gradlew installDebug

cd ../..
