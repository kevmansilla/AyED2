
CFFLAGS = -Wall -Werror -Wextra -pedantic -std=c99

SRC = odd.c

OBJS = $(SRC:.c=.0)

objetos:
		gcc $(CFFLAGS) -c $(SRC)

linker: 
		gcc $(CFFLAGS) -o pru *.o main.c


clean:
		rm -f sorter array_helpers.o weather.o weather weather_utils.o weather_cordoba.out

.PHONY: clean

esdebug:
		objdump --syms weather | grep "debug"
		
debugin:
		gcc -g $(CFFLAGS) -c array_helpers.c weather.c
		gcc -g $(CFFLAGS) -o weather *.o main.c
		
