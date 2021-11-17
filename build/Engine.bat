@echo off

if not exist "OyunEngine" mkdir OyunEngine

cd OyunEngine

cmake ..\..

timeout 4