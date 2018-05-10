@echo off
cls

set DRIVE_LETTER=%1:
set IP_ADDRESS=%2:
set PORT_NUM=%3:
set COMPILER_PATH=%DRIVE_LETTER%/TDM-GCC-64
set PATH=%COMPILER_PATH%/bin;%COMPILER_PATH%/wxWidgets-3.1.0/lib;c:/windows

EndeavorClient IP_ADDRESS PORT_NUM
