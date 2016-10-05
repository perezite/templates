rem # Build
echo Build ...
cd ./jni
call ndk-build
cd ..

rem # Install
echo Install ...
call ant debug install

rem # Run
echo Run ...
call adb shell am start -a android.intent.action.MAIN -n org.libsdl.app/.SDLActivity