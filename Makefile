all:
	gcc -O3 -W nb.c -g -o nb.bin `sdl-config --cflags` `sdl-config --libs` -lm
