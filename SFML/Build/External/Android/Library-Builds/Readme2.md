# SFML Android 
This suite compiles sfml for android, including a little demo program.
The batch first compiles and installs the library into the /build folder
Then it enters examples/android, compiles the example and installs it on the device attached to the computer

## Prerequisites
- Android NDK and SDK
- Mingw
- An android device attached to the computer and visible when running adb devices
- Path variables to the aformentioned prerequisites set

## Running
Set the variables in BuildAndInstall.bat nad in examples/android/local.properties
Then run BuildAndInstall.bat from the command line.