CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = pqueue.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = dispatch_patients

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

valgirnd: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET) input/*.in

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)