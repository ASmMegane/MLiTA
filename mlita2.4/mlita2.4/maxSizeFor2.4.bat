echo off & setLocal EnableDelayedExpansion
echo 300000 > input.txt
for /L %%i in (1 1 300000) DO ( echo !random! >> input.txt )
