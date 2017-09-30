@echo off

mkdir build
chdir build

mkdir mak.mingw
chdir mak.mingw

::del CMakeCache.txt

cmake -G "MinGW Makefiles" ../../

if %errorlevel% NEQ 0 goto error
goto end

:error
echo Houve um erro. Pressione qualquer tecla para finalizar.
pause >nul

:end
