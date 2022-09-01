CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g
OBJECTS = ../ej1/set.o ../ej1/change_making.o ../ej2/change_making_dyn.o ../ej1/amount.o ../ej1/currency.o ../ej1/set_elem.o main.o helpers.o
TARGET = change_making

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

valgrind: $(TARGET)
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET) input/example.in

clean:
	rm -f $(TARGET) $(OBJECTS)



