@echo off 
set dir=%cd%
set src=%cd%\Client
set dst=%cd%\Client2\Client

del /s /q %dst%
rmdir /s /q %dst%
mkdir %dst%

Xcopy %src% %dst% /E /H /C /I
