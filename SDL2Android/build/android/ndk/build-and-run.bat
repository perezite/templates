@echo off
cls

rem # Init
SET userParameter=%1
SET debugMode=0
IF "%userParameter%"=="debug" (
    SET debugMode=1
)

rem # Build
echo Build ...
cd ./jni
IF %debugMode%==1 (
    @echo on
    call ndk-build NDK_DEBUG=1
    @echo off
) ELSE (
    @echo on
    call ndk-build
    @echo off
)
cd ..
pause

rem # Install
echo Install ...
@echo on
call ant debug install
@echo off

rem # Run
echo Run ...
@echo on
call adb shell am start -a android.intent.action.MAIN -n org.libsdl.app/.SDLActivity
@echo off

rem # Debug
IF %debugMode%==1 (
    call ndk-gdb
)