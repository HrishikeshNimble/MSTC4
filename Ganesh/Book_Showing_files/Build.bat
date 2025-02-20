cl.exe /c /EHsc project.c
rc.exe resource.rc
link.exe project.obj resource.res Winmm.lib User32.lib GDI32.lib kernel32.lib /SUBSYSTEM:WINDOWS

