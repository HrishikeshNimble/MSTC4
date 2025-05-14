cls

del main.exe

rc.exe texture.rc

rc.exe res\Splash_Screen.rc

mkdir temp

cd temp

cl /c /EHsc /I ..\include ..\src\*.cpp

cd ..

link temp/*.obj res/Splash_Screen.res texture.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS /OUT:main.exe

cd res



cd ..

rmdir temp /s /q

main.exe