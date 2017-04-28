CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
INCS = parse.h
TARGET = parse_main
SOURCES =  parse.c $(TARGET).c
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) parse.txt
