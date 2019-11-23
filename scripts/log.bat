@ECHO OFF

IF %1=="" (
"%~dp0XbSymbolUnitTest.exe" > "%~dp0UnitTest.log"
) ELSE (
"%~dp0XbSymbolUnitTest.exe" %1 > "%~dp0UnitTest.log"
)
