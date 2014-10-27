media-controller
================

media controller used to discover media server and media render, 
brow all shared directory on media server, 
send controll command to render like open, play, pause or stop. 
so that render can play audio or video which shared on media server.

media controller with PlatinumKit shared library. 

shell command to get source code in linux OS:
git clone git@github.com:hucy001/media-controller.git

step to build UPNP shared library and android application:
1. download soure code for PlatinumKit, it's an opensource project
2. download android-ndk; 
3. edit ".bashrc": ANDROID_NDK_ROOT=/yours dir/android-ndk-r8e   export ANDROID_NDK_ROOT
4. build PlatinumKit: cd /home/xxxx/PlatinumKit/Platinum    scons target=arm-android-linux build_config=Release
5. build shared library: replace directory /home/xxxx/PlatinumKit/Platinum/Source/Platform/Android with that from github, then  type "$ANDROID_NDK_ROOT/ndk-build NDK_DEBUG=0 -B".
6. build android application: use "eclipse" tool to build projects under "/home/xxxx/PlatinumKit/Platinum/Source/Platform/Android".
