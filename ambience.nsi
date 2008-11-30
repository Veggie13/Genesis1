;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"
  !include "registerExtension.nsh"

;--------------------------------
;General

  ;Name and file
  Name "Ambience Sound Studio 1.1 rev 02 beta"
  OutFile "bin\Installer\ambience_1_1_r02_b.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\MeiCor Gaming\Ambience Sound Studio"

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\MeiCor Gaming\Ambience Sound Studio" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Variables

  Var StartMenuFolder

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_COMPONENTS

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\MeiCor Gaming\Ambience Sound Studio"
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "MeiCor Gaming\Ambience Sound Studio"

  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

  !insertmacro MUI_PAGE_INSTFILES



  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Main Install" SecMain

  SectionIn 1 RO

  SetOutPath "$INSTDIR"

  ;ADD YOUR OWN FILES HERE...
  File "bin\Release\ambience.exe"
  File "bin\Release\bass.dll"
  File "bin\Release\mingwm10.dll"
  File "bin\Release\QtCore4.dll"
  File "bin\Release\QtGui4.dll"
  File "bin\Release\QtXml4.dll"
  File "docs\ambience.pdf"
  File "README.txt"

  ${registerExtension} "$INSTDIR\ambience.exe" ".assp" "Ambience Sound Studio Project"

  ;Store installation folder
  WriteRegStr HKCU "Software\MeiCor Gaming\Ambience Sound Studio" "" $INSTDIR

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application

    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Ambience Sound Studio.lnk" "$INSTDIR\ambience.exe"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Documentation.lnk" "$INSTDIR\ambience.pdf"

  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd

Section "Add Desktop Shortcut" SecDesktop

  SectionIn 1

  CreateShortCut "$DESKTOP\Ambience Sound Studio.lnk" "$INSTDIR\ambience.exe" "" "$INSTDIR\ambience.exe" 0 SW_SHOWNORMAL "" "Start Ambience Sound Studio"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecMain ${LANG_ENGLISH} "The main section."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecMain} $(DESC_SecMain)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ${unregisterExtension} ".assp" "Ambience Sound Studio Project"

  ;ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\ambience.exe"
  Delete "$INSTDIR\bass.dll"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  Delete "$INSTDIR\QtXml4.dll"
  Delete "$INSTDIR\ambience.pdf"
  Delete "$INSTDIR\README.txt"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder

  Delete "$SMPROGRAMS\$StartMenuFolder\Ambience Sound Studio.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\Documentation.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"
  Delete "$DESKTOP\Ambience Sound Studio.lnk"

  DeleteRegKey HKCU "Software\MeiCor Gaming\Ambience Sound Studio"
  DeleteRegKey /ifempty HKCU "Software\MeiCor Gaming"

SectionEnd
