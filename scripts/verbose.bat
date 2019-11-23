@ECHO OFF

IF %1=="" (
"%~dp0XbSymbolUnitTest.exe"
) ELSE (
"%~dp0XbSymbolUnitTest.exe" %1
)

PAUSE
