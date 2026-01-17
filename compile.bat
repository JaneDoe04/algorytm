@echo off
echo ========================================
echo Kompilacja programu Huffman
echo ========================================
echo.

REM Sprawdzamy czy g++ jest dostępny
where g++ >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Znaleziono g++!
    echo.
    g++ -std=c++11 -Wall -Wextra -O2 -o huffman.exe main.cpp HuffmanNode.cpp HuffmanTree.cpp HuffmanEncoder.cpp HuffmanDecoder.cpp
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo ========================================
        echo Kompilacja zakonczona pomyslnie!
        echo ========================================
        echo.
        echo Aby uruchomic program wpisz: huffman.exe
    ) else (
        echo.
        echo BLAD podczas kompilacji!
    )
) else (
    echo.
    echo BLAD: Nie znaleziono kompilatora g++!
    echo.
    echo Instrukcje instalacji:
    echo 1. Pobierz MinGW-w64 z: https://www.mingw-w64.org/downloads/
    echo 2. Lub zainstaluj przez MSYS2: https://www.msys2.org/
    echo 3. Lub uzyj Visual Studio Community (zawiera kompilator C++)
    echo.
    echo Po instalacji dodaj kompilator do zmiennej PATH.
    pause
)
