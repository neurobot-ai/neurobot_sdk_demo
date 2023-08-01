@echo off
setlocal enabledelayedexpansion
chcp 437
path %path%;C:\Windows\System32\wbem
path %path%;C:\WINDOWS\System32\Wbem
path %path%;C:\WINDOWS\System32

set Ret1=0

for /f %%i in ('where.exe nvidia-smi.exe') do (
for /f "tokens=* delims=," %%i in ('nvidia-smi.exe ^|findstr "Version:"') do (
set Ret1=1
)
)

set rootSource=C:\Progra~1\NVIDIA~1\NVSMI\nvidia-smi.exe
set Source=C:\Program Files\NVIDIA Corporation\NVSMI\nvidia-smi.exe
if exist %Source%(
for /f "tokens=* delims=," %%i in (' %rootSource% ^|findstr "Version:"') do (
set Ret1=1
)
)

rem 是否是英伟达显卡
echo Is NVIDIA:
echo !Ret1!
echo.
rem 在exe内做检测
set Ret2=1

set Ret3=0
for /f %%i in ('wmic os get osarchitecture^|findstr "64"') do (
set Ret3=1
)

rem win是否是64位
echo Is Windows 64
echo !Ret3!
echo.
set Ret4=1
for /f "tokens=* delims=," %%i in ('netsh advfirewall show allprofiles^|findstr "State*"^|findstr "ON" ') do (
set Ret4=0
)
rem 是否关闭防火墙
echo Is ClosedNetWall
echo !Ret4!
echo.
echo.

set Ret5=0
for /f "tokens=* delims=," %%i in ('systeminfo ^|findstr "Windows.10" ') do (
set Ret5=1
)

for /f "tokens=* delims=," %%i in ('systeminfo ^|findstr "Windows.11" ') do (
set Ret5=1
)
rem 是否是win10/win11
echo Is Windows 64V10/11
echo !Ret5!

echo.

set Ret6=0

for /f "tokens=* delims=," %%i in ('wmic cpu list brief^|findstr "GHz"') do (
set tm1=%%i
)

for /f "tokens=16" %%i in ('echo !tm1! ') do (
set tm2=%%i
)
for /f "delims=0G" %%i in ('echo !tm2!') do (
set tm5=%%i
) 

for /f "tokens=17" %%i in ('echo !tm1! ') do (
set tex1=%%i
)
for /f "delims=0G" %%i in ('echo !tex1!') do (
set tex2=%%i
) 


echo Two results:
echo !tm5!
echo !tex2!

echo.

for /f "tokens=1" %%i in ('echo !tm1! ') do (
set tm3=%%i
)
set tm4=!tm3:~0,5%!
echo Intel:
echo !tm3!
echo.
for /f "tokens=1 delims=" %%i in ('wmic cpu get NumberOfCores^|findstr "[0-9]" ') do (
set tm6=%%i
)
echo CPU Core:
echo !tm6!
echo.

if !tm4! EQU Intel (set /a Ret6+=1)
if !tm5! GEQ 2.5 (set /a Ret6+=1)
if !tex2! GEQ 2.5 (set /a Ret6+=1)
if !tm6! GEQ 6 (set /a Ret6+=1)

echo Ret6sum:
echo !Ret6!
echo.
set tth=!Ret6!

if !tth! GEQ 3.0 (set Ret6=1)
if !tth! LSS 3.0 (set Ret6=0)

rem CPU为intel,主频大于2.5,6核心_Re6
echo Is CPU OK
echo !Ret6!

echo.

set Ret7=1

for /f "tokens=* delims=," %%i in ('systeminfo ^|findstr "Virtual.Memory:.Available.*"') do (
set tmpa=%%i
)

for /f "tokens=3 delims=:" %%i in ('echo !tmpa! ') do (
set tmpb=%%i
)

for /f "tokens=1 delims=,M" %%i in ('echo !tmpb!') do (
set tempc=%%i
set tempd=!tempc:~1!
)

for /f "tokens=2 delims=,M" %%i in ('echo !tmpb!') do (
set tempe=%%i
)

set /a tmpg=(!tempd!*1000)+!tempe!

if !tmpg! LSS 8192 (set Ret7=0)

rem 系统内存大于8GB
echo Memory Available 8GB:
echo !Ret7!
echo.
set ShenDuXue=0

if not exist .\deploy\template.json ( goto dump )

for /f "tokens=* delims=,:}]" %%i in ('findstr "ocr" .\deploy\template.json') do (
set ShenDuXue=1
)
for /f "tokens=* delims=,:}]" %%i in ('findstr "detection" .\deploy\template.json') do (
set ShenDuXue=1
)
for /f "tokens=* delims=,:}]" %%i in ('findstr "segmentation" .\deploy\template.json') do (
set ShenDuXue=1
)
for /f "tokens=* delims=,:}]" %%i in ('findstr "label_compute" .\deploy\template.json') do (
set ShenDuXue=1
)

:dump
echo Deep Learning:
echo !ShenDuXue!
echo.
echo=>./checked.json
type nul > ./checked.json
echo {>>./checked.json
echo "required":[>>./checked.json
if !ShenDuXue!==0 ( goto dump2 )
echo will check the GPU
echo {>>./checked.json
echo "name":"Is NVIDIA graphics card and driver installed",>>./checked.json
echo "status":!Ret1!,>>./checked.json
echo "key":"isNVIDIA",>>./checked.json
echo "info":"Low code development utilizes deep learning operators. Please check if the computer is equipped with a NVIDIA graphics card and install the relevant drivers correctly">>./checked.json
echo },>>./checked.json
:dump2
echo {>>./checked.json
echo "name":"Does the configuration file or model file exist",>>./checked.json
echo "status":!Ret2!,>>./checked.json
echo "key":"isFileNeed",>>./checked.json
echo "info":"Please copy the downloaded low code development components and models (if there are deep learning operators in the process) to the corresponding folder of the specified deployment package according to the operation manual. The model file needs to be renamed according to the manual requirements. The operation manual can be found in the 2DLowCodeGuide.pdf folder in the deployment package under 'readme'">>./checked.json
echo },>>./checked.json

echo {>>./checked.json
echo "name":"Is the system a Windows 64 bit version",>>./checked.json
echo "status":!Ret3!,>>./checked.json
echo "key":"isWindows64",>>./checked.json
echo "info":"The system does not support Windows 32-bit version. Please replace the system running Windows 64 bit and try again">>./checked.json
echo }>>./checked.json
echo ],>>./checked.json

echo "recommend":[>>./checked.json

echo {>>./checked.json
echo "name":"Turn off firewall or antivirus software",>>./checked.json
echo "status":!Ret4!,>>./checked.json
echo "key":"isClosedNetWall",>>./checked.json
echo "info":"Firewalls or antivirus software may accidentally kill the software or restrict communication. Please add the entire folder of this software, as well as the main programs (noncode. exe, nginx. exe) to the antivirus software whitelist; Or temporarily close the firewall or antivirus software">>./checked.json
echo },>>./checked.json

echo {>>./checked.json
echo "name":"The system is a Windows 10/11 64 bit version",>>./checked.json
echo "status":!Ret5!,>>./checked.json
echo "key":"isWindows64V10",>>./checked.json
echo "info":"This software cannot guarantee compatibility with Windows versions other than Windows 10/11. Please choose the system carefully">>./checked.json
echo },>>./checked.json

echo {>>./checked.json
echo "name":"CPU with Intel main frequency 2.5GHZ 6-core and above versions",>>./checked.json
echo "status":!Ret6!,>>./checked.json
echo "key":"Is CPU OK",>>./checked.json
echo "info":"If the CPU configuration is too low, it may cause slow detection speed or abnormal operation. Suggest choosing a machine with a higher CPU configuration">>./checked.json
echo },>>./checked.json

echo {>>./checked.json
echo "name":"System memory greater than 8GB",>>./checked.json
echo "status":!Ret7!,>>./checked.json
echo "key":"Memory Available 8GB:",>>./checked.json
echo "info":"If the memory capacity is too small, it may cause slow detection speed or abnormal operation. Suggest choosing a machine with larger memory capacity">>./checked.json
echo }>>./checked.json

echo ]>>./checked.json
echo }>>./checked.json

rem check exist

if not exist .checkSetting.json (
echo=>./checkSetting.json
echo {"checkConfigure":{"ignoreRecommend":0,"isAutoEntrance":0}} >>./checkSetting.json
)

