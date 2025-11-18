# Microsoft Developer Studio Project File - Name="BitMe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BitMe - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BitMe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BitMe.mak" CFG="BitMe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BitMe - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BitMe - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BitMe - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Build/Release"
# PROP Intermediate_Dir "../Build/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1c09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1c09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ../Build/Release/Build.obj /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
# Begin Special Build Tool
OutDir=.\../Build/Release
SOURCE="$(InputPath)"
PreLink_Desc=Incrementing build number
PreLink_Cmds="..\Build\Release\Radiance.exe"	cl /nologo /c /Zl /Fo$(OutDir)\ Build.c
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BitMe - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Build/Debug"
# PROP Intermediate_Dir "../Build/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1c09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1c09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../Build/Debug/Build.obj /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\../Build/Debug
SOURCE="$(InputPath)"
PreLink_Desc=Incrementing build number
PreLink_Cmds="..\Build\Debug\Radiance.exe"	cl /nologo /c /Zl /Fo$(OutDir)\ Build.c
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "BitMe - Win32 Release"
# Name "BitMe - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Alloc.cpp
# End Source File
# Begin Source File

SOURCE=.\Application.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\AsfInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\AviInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\BitMe.cpp
# End Source File
# Begin Source File

SOURCE=.\BitMe.rc
# End Source File
# Begin Source File

SOURCE=.\BitMeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\BitrateModel.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Checksum.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\ContainerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\ContainerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\File.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\FilePointer.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\FlvInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Font.cpp
# End Source File
# Begin Source File

SOURCE=.\Glue.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\HtmlWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\Interfaces\Information.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Language.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Library.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\M2tsInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Maths.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\MatroskaInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\Mp4Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\MpgInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\MtsInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\MxfInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\OggInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\Report.cpp
# End Source File
# Begin Source File

SOURCE=.\ResCalcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResolutionModel.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\ResourceString.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\RmInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\SettingsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Library\StringDictionary.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\StrW.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\TestInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\TmpLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Unicode.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\VAlloc.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculation\VobInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\Win32Library.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\Library\Alloc.h
# End Source File
# Begin Source File

SOURCE=.\Application.h
# End Source File
# Begin Source File

SOURCE=.\Library\array.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\AsfInterface.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\AviInterface.h
# End Source File
# Begin Source File

SOURCE=.\BitMe.h
# End Source File
# Begin Source File

SOURCE=.\BitMeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\BitrateModel.h
# End Source File
# Begin Source File

SOURCE=.\Library\Checksum.h
# End Source File
# Begin Source File

SOURCE=.\Library\Configuration.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\ContainerInterface.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\ContainerManager.h
# End Source File
# Begin Source File

SOURCE=.\Library\File.h
# End Source File
# Begin Source File

SOURCE=.\Library\FilePointer.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\FlvInterface.h
# End Source File
# Begin Source File

SOURCE=.\Library\Font.h
# End Source File
# Begin Source File

SOURCE=.\Glue.h
# End Source File
# Begin Source File

SOURCE=.\Library\HtmlWriter.h
# End Source File
# Begin Source File

SOURCE=.\Interfaces\Information.h
# End Source File
# Begin Source File

SOURCE=.\Library\Language.h
# End Source File
# Begin Source File

SOURCE=.\Library\LibAll.h
# End Source File
# Begin Source File

SOURCE=.\Library\Library.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\M2tsInterface.h
# End Source File
# Begin Source File

SOURCE=.\Library\Maths.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\MatroskaInterface.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\Mp4Interface.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\MpgInterface.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\MtsInterface.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\MxfInterface.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\OggInterface.h
# End Source File
# Begin Source File

SOURCE=.\Library\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\Report.h
# End Source File
# Begin Source File

SOURCE=.\ResCalcDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResolutionModel.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Library\ResourceString.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\RmInterface.h
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Library\SettingsManager.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Library\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Library\String.h
# End Source File
# Begin Source File

SOURCE=.\Library\StringDictionary.h
# End Source File
# Begin Source File

SOURCE=.\Library\StringList.h
# End Source File
# Begin Source File

SOURCE=.\Library\StrW.h
# End Source File
# Begin Source File

SOURCE=.\Library\Templates.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\TestInterface.h
# End Source File
# Begin Source File

SOURCE=.\TmpLibrary.h
# End Source File
# Begin Source File

SOURCE=.\Library\Types.h
# End Source File
# Begin Source File

SOURCE=.\Library\Unicode.h
# End Source File
# Begin Source File

SOURCE=.\Library\VAlloc.h
# End Source File
# Begin Source File

SOURCE=.\Calculation\VobInterface.h
# End Source File
# Begin Source File

SOURCE=.\Library\Win32Library.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BitMe.ico
# End Source File
# Begin Source File

SOURCE=.\res\BitMe.rc2
# End Source File
# End Group
# End Target
# End Project
