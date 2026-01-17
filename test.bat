@echo off
echo ========================================
echo Test programu Huffman
echo ========================================
echo.

if not exist huffman.exe (
    echo BLAD: Program huffman.exe nie istnieje!
    echo Najpierw uruchom compile.bat
    pause
    exit /b 1
)

echo 1. Test kompresji...
echo.
echo test_input.txt ^> test_compressed.huff
echo.
huffman.exe < test_input.txt >nul 2>&1
if exist test_compressed.huff (
    echo OK: Plik skompresowany utworzony
) else (
    echo BLAD: Nie udalo sie skompresowac pliku
)

echo.
echo 2. Test dekompresji...
echo.
echo test_compressed.huff ^> test_decompressed.txt
echo.
if exist test_compressed.huff (
    echo OK: Plik zdekompresowany utworzony
) else (
    echo BLAD: Nie udalo sie zdekompresowac pliku
)

echo.
echo 3. Porownanie plikow...
echo.
fc test_input.txt test_decompressed.txt >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo OK: Pliki sa identyczne! Test pomyslny!
) else (
    echo UWAGA: Pliki roznia sie
)

echo.
echo ========================================
echo Test zakonczony
echo ========================================
pause
