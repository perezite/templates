@echo off
:loop
timeout 50
taskkill /im vcpkgsrv.exe /f
goto loop