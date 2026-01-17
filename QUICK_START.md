# Instrukcja Obsługi Programu

## Uruchomienie programu

Program został skompilowany do pliku wykonywalnego `huffman.exe`. Aby go uruchomić, należy:
1. Uruchomić plik `huffman.exe` bezpośrednio z eksploratora plików.
2. Lub uruchomić konsolę (CMD/PowerShell) w folderze projektu i wpisać polecenie:
   ```bash
   .\huffman.exe
   ```

## Funkcjonalności programu

Menu główne programu oferuje następujące opcje:

### 1. Kompresja pliku
Pozwala na skompresowanie dowolnego pliku tekstowego przy użyciu algorytmu Huffmana.
- Należy wybrać opcję `1`.
- Wprowadzić nazwę pliku wejściowego (np. `tekst.txt`).
- Wprowadzić nazwę pliku wyjściowego (np. `wynik.huff`).
- Program utworzy skompresowany plik zawierający słownik oraz zakodowane dane.

### 2. Dekompresja pliku
Pozwala na odtworzenie oryginalnego pliku z pliku skompresowanego.
- Należy wybrać opcję `2`.
- Wprowadzić nazwę pliku skompresowanego (np. `wynik.huff`).
- Wprowadzić nazwę pliku docelowego (np. `odczytany.txt`).

### 3. Demonstracja kolejki priorytetowej
Prezentuje działanie zaimplementowanej struktury danych (kolejki priorytetowej typu min-heap).
- Należy wybrać opcję `3`.
- Program wyświetli sekwencję operacji: budowanie kolejki, dodawanie elementów, usuwanie oraz zmianę priorytetu.

### 4. Wyjście
Zakończenie działania programu.

## Weryfikacja działania

W celu sprawdzenia poprawności działania programu, zaleca się wykonanie następujących kroków:
1. Utworzenie pliku testowego z dowolną zawartością tekstową.
2. Przeprowadzenie kompresji tego pliku.
3. Przeprowadzenie dekompresji uzyskanego pliku wynikowego.
4. Porównanie zawartości pliku oryginalnego z plikiem po dekompresji (powinny być identyczne).

## Uwagi techniczne

- Program obsługuje pliki zawierające znaki drukowalne oraz znaki białe (spacja, tabulator, nowa linia).

