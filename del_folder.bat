@echo off
for /f "delims=" %%i in ('dir /b/s/ad e:\') do echo (rd /s /q %%i\d)
pause