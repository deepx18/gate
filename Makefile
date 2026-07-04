CC = gcc 
FLAGS = -Wall -Wextra
LIBS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm

te: main.c 
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

run: te
	./te
