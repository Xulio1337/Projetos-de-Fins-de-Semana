@echo off 
setlocal enabledelayedexpansion


for /L %%i in (1,1,20) do (
    esptool --port COM%%i chip-id >nul 2>&1
    if !errorlevel! EQU 0 (
        echo Dispositivo encontrado em: COM%%i
        set "porta=COM%%i"
    )
)

esptool.exe --chip esp32s3 --port !porta! --baud 921600 write-flash -z ^
 0x0 bootloader.bin ^
 0x8000 partitions.bin ^
 0x10000 firmware.bin 

pause