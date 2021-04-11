@echo off
if "%VSCMD_ARG_HOST_ARCH%"=="x64" goto pass_ver
echo Execute in the x64 Native tools command prompt.
echo "msvc_install.bat <DIR>"
echo DIR is optional and points to the install dir, defaults defined in GnuInstallDirs where the find_package should find it.
goto exit
:pass_ver
if not exist "build" mkdir build
pushd build
set PREFIX=
if not "%1"=="" set PREFIX=-DCMAKE_INSTALL_PREFIX=%1
if "%1"=="" set PREFIX=-UCMAKE_INSTALL_PREFIX
cmake .. -DCMAKE_BUILD_TYPE=Release -DHAS_AFFILIATES=OFF -DHAS_TEST=OFF -DHAS_EXAMPLES=OFF %PREFIX%
cmake --build . --config Release
set BUILD_PATH=%CD%
popd
echo Start an elevated prompt for an install.
powershell -Command "Start-Process scripts\win_inst.bat -ArgumentList %BUILD_PATH% -Verb RunAs"
echo done
:exit
