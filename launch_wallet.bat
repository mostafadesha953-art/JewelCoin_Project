@echo off
title Jewl Sovereign Wallet Launcher 2026
color 0A
echo -------------------------------------------------------
echo  [!] Starting Jewel Core Node...
echo  [!] Activating AES-512 Encryption & RandomX CPU Mining
echo -------------------------------------------------------

:: 1.  ‘€Ì· «·‰Ê«… ›Ì «·Œ·›Ì… («·„Õ—ﬂ)
start /min Jewel_core.exe

:: 2. «·«‰ Ÿ«— ·À«‰Ì… ·÷„«‰ › Õ «·„‰›– 18081
timeout /t 2 /nobreak >nul

:: 3. › Õ Ê«ÃÂ… «·„Õ›Ÿ… ›Ì «·„ ’›Õ «·«› —«÷Ì
echo [!] Opening Sovereign Interface...
start index.html

echo -------------------------------------------------------
echo  [OK] System is Running. Do not close this window.
echo -------------------------------------------------------
pause