CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g
OBJECTS = solve_knapsack.o set.o item.o string.o helpers.o main.o set_elem.o knapsack.o
TARGET = knapsack

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

valgrind: $(TARGET)
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET) input/example_graph_1.in

clean:
	rm -f $(TARGET) $(OBJECTS)



