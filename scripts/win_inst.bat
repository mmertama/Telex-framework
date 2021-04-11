@echo off
echo This file is run in elevated mode due it will install libaries into system.
echo The location is documented along GnuInstallDirs.
cd %1
cmake --install .

