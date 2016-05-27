cls
rem @echo off
SET program="%1"
if %program% == "" goto err

%program% input1.txt output1.txt
if ERRORLEVEL 1 goto testFailed
fc /b output1.txt reference/output1.txt
if ERRORLEVEL 1 goto testFailed

%program% input2.txt output2.txt
if ERRORLEVEL 1 goto testFailed
fc /b output2.txt reference/output2.txt
if ERRORLEVEL 1 goto testFailed

%program% input3.txt output3.txt
if ERRORLEVEL 1 goto testFailed
fc /b output3.txt reference/output3.txt
if ERRORLEVEL 1 goto testFailed

%program% inputMIN.txt outputMIN.txt
if ERRORLEVEL 1 goto testFailed
fc /b outputMIN.txt reference/outputMIN.txt
if ERRORLEVEL 1 goto testFailed

echo OK
exit /b

:testFailed
echo Testing failed
exit /b

:err
echo Usage: test.bat <Path to program>
