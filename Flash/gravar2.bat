@echo off 
setlocal enabledelayedexpansion


for /L %%i in (1,1,20) do (
    esptool --port COM%%i chip-id >nul 2>&1
    if !errorlevel! EQU 0 (
        echo Dispositivo encontrado em: COM%%i
        set "porta=COM%%i"
    )
)
pause