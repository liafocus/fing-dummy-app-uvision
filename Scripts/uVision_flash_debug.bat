@ECHO off

REM ******************************************************************
REM * This script initiates the build, flashing, and debugging process 
REM * for the "fing-dummy-app-uvision" project using uVision.
REM *
REM * Script authored by lia@focus.uy
REM ******************************************************************

REM Usage: Test.bat [PATH TO UV4.exe] [PATH TO PROJECT] [TARGET] [TEST_RESULTS_FILE]

REM Set UV4_EXE 
IF "%1"=="" (
    SET UV4_EXE=C:\Keil_v5\UV4\UV4.exe 
) ELSE (
    SET UV4_EXE=%1
)
ECHO Using %UV4_EXE%

REM Set project file path
IF "%2"=="" (
    SET PROJECT_FILE=%~dp0..\fing-dummy-app-uvision.uvprojx
) ELSE (
    SET PROJECT_FILE=%2
)

REM Set axf file path
IF "%2"=="" (
    SET AXF_FILE=%~dp0..\Objects\fing-dummy-app-uvision.axf
) ELSE (
    SET AXF_FILE=%3
)

REM Set target
IF "%3"=="" (
    SET TARGET="STM32F407"
) ELSE (
    SET TARGET=%4
)

REM Set test results file
IF "%4"=="" (
    SET BAT_RESULTS_FILE=%~dp0..\Output_data\Bat_results.txt
) ELSE (
    SET BAT_RESULTS_FILE=%5
)

REM ---------------------------------- BUILD ---------------------------------------------
REM REM Build the application (-b) in headless mode (-j0)
REM ECHO. 
REM ECHO Building application...
REM IF EXIST %AXF_FILE% DEL %AXF_FILE%
REM
REM %UV4_EXE% -b %PROJECT_FILE% -j0
REM
REM REM Check if build was successful
REM IF EXIST %AXF_FILE% (
REM     ECHO Build succeeded
REM ) ELSE (
REM     ECHO Build failed
REM     GOTO :done
REM )
REM ------ Remove one "REM" per row in order to make the script build the program --------
REM --------------------------------------------------------------------------------------

REM ---------------------------------- FLASH ---------------------------------------------
REM REM Flash the application (-b) in headless mode (-j0)
REM ECHO. 
REM ECHO Loading application to target...
REM %UV4_EXE% -f %PROJECT_FILE% -j0
REM IF ERRORLEVEL 1 (
REM     ECHO Flash download failed
REM     GOTO :done
REM ) 
REM ------ Remove one "REM" per row in order to make the script flash the program -------
REM --------------------------------------------------------------------------------------


REM Debug the application (-b) in headless mode (-j0)
ECHO. 
ECHO Debugging on target...
IF EXIST "%BAT_RESULTS_FILE%" DEL "%BAT_RESULTS_FILE%"

%UV4_EXE% -d %PROJECT_FILE% -o %BAT_RESULTS_FILE% -j0

REM Check if test results have been written and display them
IF EXIST "%BAT_RESULTS_FILE%" (
    TYPE "%BAT_RESULTS_FILE%"
) ELSE (
    ECHO. Test ended abnormally - file %BAT_RESULTS_FILE% is not produced
    GOTO :done
)

:done
