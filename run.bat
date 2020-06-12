mingw32-make -C AVC_robot
mingw32-make -C AVC_server
start /d "AVC_server\" server3.exe
start /d "AVC_robot\" Robot.exe
