@echo off

set LIB_PATH=C:\Users\Mohammed\Documents\Programming\ARM\tiva-c\lib

copy %LIB_PATH%\SYSCNTRL* .
copy %LIB_PATH%\GPIO* .
copy %LIB_PATH%\NVIC* .
copy %LIB_PATH%\Std_Types.h .
copy %LIB_PATH%\Macros.h .

