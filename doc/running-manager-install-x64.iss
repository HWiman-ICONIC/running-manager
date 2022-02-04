; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=RunningManager
AppVerName=RunningManager 1.8
AppVersion=1.8
AppCopyright=�2022 H�kan Wiman
AppPublisher=H�kan Wiman
AppPublisherURL=http://www.wiman.nu/rm
AppSupportURL=http://www.wiman.nu/rm
AppUpdatesURL=http://www.wiman.nu/rm
DefaultDirName={commonpf}\RunningManager
DefaultGroupName=RunningManager
Compression=lzma
SolidCompression=true
WizardImageFile=sample.bmp
UninstallDisplayIcon={app}\RunningManager.exe
VersionInfoVersion=1.8
VersionInfoCompany=H�kan Wiman
VersionInfoDescription=RunningManager Setup
VersionInfoTextVersion=1, 8
LicenseFile=license.txt
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64
OutputBaseFilename=rm_setup
PrivilegesRequired=admin
DisableWelcomePage=yes

[Tasks]
; NOTE: The following entry contains English phrases ("Create a desktop icon" and "Additional icons"). You are free to translate them into another language if required.
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"

[Files]
Source: "../out/build/x64-Release/RunningManager.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "../out/build/x64-Release/*.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "./rmhelp.zip"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\RunningManager"; Filename: "{app}\RunningManager.exe"
; NOTE: The following entry contains an English phrase ("Uninstall"). You are free to translate it into another language if required.
Name: "{group}\Uninstall RunningManager"; Filename: "{uninstallexe}"
Name: "{userdesktop}\RunningManager"; Filename: "{app}\RunningManager.exe"; Tasks: desktopicon

[Run]
; NOTE: The following entry contains an English phrase ("Launch"). You are free to translate it into another language if required.
Filename: "{app}\RunningManager.exe"; Description: "Launch Running Manager";  Flags: nowait postinstall 
