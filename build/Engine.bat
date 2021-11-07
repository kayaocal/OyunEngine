@echo off

if not exist "Engine" mkdir Engine

cd Engine

cmake ..\..

timeout 4