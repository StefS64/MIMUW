W razie zauważenia błędów proszę o kontakt ze mną.

W celu przetestowania swojego rozwiązania umieść je w tym folderze pod nazwą `prev.cpp`.

Jeśli brakuje Ci uprawnień do użycia pliku `prev.sh` możesz je uzyskać używając komendy `chmod +x prev.sh`.

W celu przetestowania rozwiązania bez użycia valgrinda wpisz w konsolę `./prev.sh` bądź `./prev.sh -v false`.
W celu przetestowania rozwiązania z użyciem valgrinda wpisz w konsolę `./prev.sh -v true`.
Aby powyższe komendy zadziałały musisz w konsoli znajdować się w tym folderze.

Struktura wejścia wygląda następująco:
`
N - liczba operacji na wejściu
n - długość początkowego ciągu
3 -9 1 23 777 -1932 - początkowy ciąg
A v - dodaj v na koniec ciągu
Q i lo hi - zapytanie `prevInRange(i, lo, hi)`
`

Domyślnie testy mają do 2000 zapytań, początkowy ciąg ma do 2000 liczb, a każda liczba w ciągu jest z przedziału [INT_MIN, INT_MAX].
Możesz zmienić te parametry zmieniając stałe przed `int main()` w pliku `prevG.cpp`.
Średnio 1/3 zapytań jest postaci `A` i 2/3 są postaci `Q`.
Możesz to zmienić zmieniając pętlę odpowiadającą za generację kolejnych operacji w tym samym pliku.