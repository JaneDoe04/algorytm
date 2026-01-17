# Instrukcja uruchomienia i testowania programu

## Krok 1: Instalacja kompilatora C++

Jeśli nie masz zainstalowanego kompilatora C++, wybierz jedną z opcji:

### Opcja A: MinGW-w64 (Zalecane)
1. Pobierz instalator z: https://winlibs.com/
2. Wybierz wersję "Release" (np. GCC 13.2.0 + MinGW-w64)
3. Rozpakuj do folderu (np. `C:\mingw64`)
4. Dodaj `C:\mingw64\bin` do zmiennej PATH:
   - Naciśnij Win+R, wpisz `sysdm.cpl`, Enter
   - Zakładka "Zaawansowane" → "Zmienne środowiskowe"
   - W "Zmienne systemu" znajdź "Path" → "Edytuj"
   - "Nowy" → wpisz ścieżkę do `bin` (np. `C:\mingw64\bin`)
   - OK, OK, OK
5. **Ważne:** Zamknij i otwórz ponownie PowerShell/CMD

### Opcja B: MSYS2
1. Pobierz z: https://www.msys2.org/
2. Zainstaluj i uruchom MSYS2 terminal
3. Wykonaj: `pacman -S mingw-w64-x86_64-gcc`
4. Dodaj `C:\msys64\mingw64\bin` do PATH

### Opcja C: Visual Studio Community
1. Pobierz z: https://visualstudio.microsoft.com/
2. Podczas instalacji wybierz "Programowanie aplikacji klasycznych w języku C++"
3. Użyj kompilatora `cl.exe` zamiast `g++`

## Krok 2: Kompilacja programu

### Metoda 1: Użyj skryptu (najłatwiejsze)
```bash
compile.bat
```

### Metoda 2: Ręczna kompilacja
Otwórz PowerShell/CMD w folderze projektu i wykonaj:
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o huffman.exe main.cpp HuffmanNode.cpp HuffmanTree.cpp HuffmanEncoder.cpp HuffmanDecoder.cpp
```

### Metoda 3: Użyj Makefile (jeśli masz make)
```bash
make
```

## Krok 3: Uruchomienie programu

```bash
huffman.exe
```

Program wyświetli menu z opcjami:
1. Kompresja pliku
2. Dekompresja pliku
3. Demonstracja kolejki priorytetowej
4. Wyjście

## Krok 4: Testowanie

### Test 1: Demonstracja kolejki priorytetowej
1. Uruchom program: `huffman.exe`
2. Wybierz opcję `3`
3. Obserwuj demonstrację wszystkich operacji na kolejce

### Test 2: Kompresja pliku
1. Uruchom program: `huffman.exe`
2. Wybierz opcję `1`
3. Podaj nazwę pliku wejściowego: `test_input.txt`
4. Podaj nazwę pliku wyjściowego: `test_compressed.huff`
5. Program powinien wyświetlić: "Kompresja zakończona pomyślnie!"

### Test 3: Dekompresja pliku
1. Uruchom program: `huffman.exe`
2. Wybierz opcję `2`
3. Podaj nazwę pliku skompresowanego: `test_compressed.huff`
4. Podaj nazwę pliku wyjściowego: `test_decompressed.txt`
5. Program powinien wyświetlić: "Dekompresja zakończona pomyślnie!"

### Test 4: Weryfikacja
Porównaj oryginalny i zdekompresowany plik:
```bash
fc test_input.txt test_decompressed.txt
```

Jeśli pliki są identyczne, zobaczysz: "Pliki nie różnią się"

### Test 5: Automatyczny test (jeśli masz skrypt)
```bash
test.bat
```

## Przykładowy test krok po kroku

```bash
# 1. Kompilacja
compile.bat

# 2. Uruchomienie
huffman.exe

# W programie:
# Wybierz: 1 (Kompresja)
# Plik wejściowy: test_input.txt
# Plik wyjściowy: compressed.huff

# Wybierz: 2 (Dekompresja)
# Plik wejściowy: compressed.huff
# Plik wyjściowy: decompressed.txt

# Wybierz: 4 (Wyjście)

# 3. Weryfikacja (w PowerShell)
fc test_input.txt decompressed.txt
```

## Rozwiązywanie problemów

### Problem: "g++ nie jest rozpoznany jako polecenie"
**Rozwiązanie:** 
- Sprawdź czy kompilator jest zainstalowany: `where g++`
- Sprawdź czy ścieżka jest w PATH: `echo %PATH%`
- Zamknij i otwórz ponownie terminal

### Problem: Błędy kompilacji
**Rozwiązanie:**
- Upewnij się, że używasz kompilatora z obsługą C++11
- Sprawdź czy wszystkie pliki źródłowe są w tym samym folderze

### Problem: Program nie znajduje pliku
**Rozwiązanie:**
- Upewnij się, że plik istnieje w folderze z programem
- Użyj pełnej ścieżki do pliku (np. `C:\Users\mojez\Desktop\algorytm\test_input.txt`)

### Problem: Pliki po dekompresji są różne
**Rozwiązanie:**
- Sprawdź czy plik wejściowy nie jest pusty
- Sprawdź czy plik skompresowany nie jest uszkodzony
- Upewnij się, że używasz tego samego programu do kompresji i dekompresji

## Dodatkowe informacje

- Program obsługuje wszystkie znaki: litery, cyfry, spacje, przecinki, kropki itp.
- Pliki skompresowane mają rozszerzenie `.huff` (możesz użyć dowolnego)
- Program działa w trybie binarnym dla efektywności
- Minimalny output na ekranie (zgodnie z wymaganiami)
