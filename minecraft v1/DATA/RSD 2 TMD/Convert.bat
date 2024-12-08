echo off
echo.
echo //////////////////////////////////////
echo.
echo ////    What is the file name?    ////
echo.
echo //////////////////////////////////////
echo.
set /P name=" "
rsdlink -s 1024 -o %name%.tmd %name%.rsd
pause
