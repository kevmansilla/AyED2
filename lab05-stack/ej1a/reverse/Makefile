CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = ../stack.c reverse.c array_helpers.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = reverse

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

TARGET1 = test
SOURCES1 = ../stack.c test.c array_helpers.c
OBJECTS1 = $(SOURCES1:.c=.o)

test: $(TARGET1)

$(TARGET1): $(OBJECTS1)
	$(CC) $(CFLAGS) -c test.c -o test.o
	$(CC) $(CFLAGS) -o test ../stack.o test.o array_helpers.o

clean:
	$(RM) $(OBJECTS) $(TARGET) test test.o
