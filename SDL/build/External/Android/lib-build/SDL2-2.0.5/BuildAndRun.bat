call ndk-build
call ant debug install
adb shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity
echo Press any key to stop the app
pause
adb shell pm clear org.libsdl.app