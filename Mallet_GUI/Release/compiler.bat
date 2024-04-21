set current=%cd%
set dots=\..\..\..\

powershell.exe -ep bypass "& 'C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1'; cd %cd%%dots%MalletRun; devenv .\MalletRun.sln /Build"

copy ..\..\..\MalletRun\x64\Debug\MalletRun.exe ..\..\..\Output\

exit