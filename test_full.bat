@echo off
echo ========================================
echo Pelny test programu Huffman
echo ========================================
echo.

if not exist huffman.exe (
    echo BLAD: Program huffman.exe nie istnieje!
    echo Najpierw uruchom compile.bat
    pause
    exit /b 1
)

echo [1/4] Test demonstracji kolejki priorytetowej...
echo 3 > test_temp.txt
echo 4 >> test_temp.txt
huffman.exe < test_temp.txt >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo OK: Demonstracja kolejki dziala
) else (
    echo BLAD: Demonstracja kolejki nie dziala
)
del test_temp.txt

echo.
echo [2/4] Test kompresji...
echo 1 > test_temp.txt
echo test_input.txt >> test_temp.txt
echo test_compressed.huff >> test_temp.txt
echo 4 >> test_temp.txt
huffman.exe < test_temp.txt >nul 2>&1
if exist test_compressed.huff (
    echo OK: Kompresja zakonczona pomyslnie
) else (
    echo BLAD: Kompresja nie powiodla sie
)
del test_temp.txt

echo.
echo [3/4] Test dekompresji...
echo 2 > test_temp.txt
echo test_compressed.huff >> test_temp.txt
echo test_decompressed.txt >> test_temp.txt
echo 4 >> test_temp.txt
huffman.exe < test_temp.txt >nul 2>&1
if exist test_decompressed.txt (
    echo OK: Dekompresja zakonczona pomyslnie
) else (
    echo BLAD: Dekompresja nie powiodla sie
)
del test_temp.txt

echo.
echo [4/4] Porownanie plikow...
fc /B test_input.txt test_decompressed.txt >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo OK: Pliki sa IDENTYCZNE! Test pomyslny!
) else (
    echo BLAD: Pliki roznia sie!
    echo Sprawdz zawartosc plikow recznie
)

echo.
echo ========================================
echo Test zakonczony
echo ========================================
pause
