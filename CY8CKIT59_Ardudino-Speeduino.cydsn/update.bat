del /Q "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\*" /s

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\core" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino" /s /e

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\codegentemp\*.h" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\libpsoc5"

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\codegentemp\Cm3Start.c" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\libpsoc5"

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\codegentemp\*.ld" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\libpsoc5"

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\codegentemp\*Gnu.s" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\libpsoc5\*Gnu.S"

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\codegentemp\*nu*.inc" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\libpsoc5"

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\Libraries" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\libraries" /s

xcopy /Y "C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\CortexM3\ARM_GCC_493\Release\CY8CKIT59_Ardudino-Speeduino.a" "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\variants\CY8CKIT-059-Speeduino"

Rem current removed from the speeduino version
del /Q "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\Arduino_Analog_Out.cpp"
del /Q "C:\Users\Bruger\.platformio\packages\framework-arduinopsoc5\cores\CY8CKIT-059-Speeduino\Arduino_Analog_Out.h"
pause