CC = gcc 
FLAGS = -Wall -Wextra
LIBS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm

gate: main.c 
	$(CC) $(FLAGS) -o $@ render.c buffer.c $^ $(LIBS)

run: gate
	./te
