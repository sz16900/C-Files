CFLAGS = `pkg-config sdl2 --cflags` -O2 -Wall -Werror -Wextra -Wfloat-equal -pedantic -ansi -lm -g
INCS = interp.h
TARGET = interp_main
SOURCES =  interp.c SDL_interp.c initializers.c $(TARGET).c
LIBS =  `pkg-config sdl2 --libs`
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) parse.txt
