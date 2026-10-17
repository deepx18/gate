CC = gcc 
FLAGS = -Wall -Wextra -ggdb
LIBS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm

gate:
	$(CC) $(FLAGS) -o ./build/$@ ./src/render.c ./src/buffer.c ./src/main.c $(LIBS)

run: gate
	./build/gate ./test.txt
