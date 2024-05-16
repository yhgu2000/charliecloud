clang -c -O0 -g ch_core.c -o ch_core.o
clang -c -O0 -g ch_misc.c -o ch_misc.o
clang -c -O0 -g ch-run.c -o ch-run.o
clang++ -c -std=c++17 -O0 -g girc.cpp -o girc.o
clang++ ch_core.o ch_misc.o ch-run.o girc.o -o a.out
