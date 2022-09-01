CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = queue.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = queue_check

SOURCES_TEST = queue.c test.c
OBJECTS_TEST = $(SOURCES_TEST:.c=.o) 
TARGET_TEST = test


.PHONY: clean

all: $(TARGET)

$(TARGET_TEST): $(OBJECTS_TEST)
	$(CC) $(CFLAGS) -o $(TARGET_TEST) $(OBJECTS_TEST) $(LFLAGS) $(LIBS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(OBJECTS_TEST) $(TARGET) $(TARGET_TEST)
