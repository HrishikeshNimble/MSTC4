cls
rc.exe resource.rc
link.exe screenone.obj resource.res Winmm.lib User32.lib GDI32.lib kernel32.lib /SUBSYSTEM:WINDOWS
cl.exe /c /EHsc screenone.c
screenone.exe