# Testerka do prev

Wystarczy uzupełnić prev.cpp i następnie skompliować całość poprzez `g++ @opcjeCpp main.cpp prev.cpp` (można dodać `-fsanitize=address,leak,undefined` po `@opcjeCpp`). Binarkę (`a.out`) warto odpalić domyślnie z argumentami `-s 100000 -m 1000000 -q 1000000`, flaga `-h` objaśnia możliwe opcje