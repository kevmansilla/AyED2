#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include "helpers.h"
#include "../ej1/currency.h"
#include "../ej1/amount.h"
#include "../ej1/set.h"
#include "../ej1/change_making.h"
#include "../ej2/change_making_dyn.h"

#define MAX_FILES 100

void show_usage(const char *path)
{
    printf("Usage:\n");
    printf("%s <option>\n", path);
    printf("-f <files> Run algorithms on the all the files listed. Stdin is used by default\n");
    printf("-b Enable backtracking algorithm\n");
    printf("-d Enable dynamic algorithm\n");
    printf("-t Enable testing (checks COIN field on the first line of each input file)\n");
    printf("-c <arg> Force charge to [arg]. ");
    printf("Reads CHARGE field on first line of each input file by default\n\r");
    printf("Example: %s -bd -f input/example*.in\n", path);
}

//open a file with the given name, or select stdin if null.
FILE* open_file(const char* filename)
{
    FILE* file = NULL;
    if (filename == NULL)
    {
        file = stdin;
    }
    else
    {
        file = fopen(filename, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error opening file %s.\n", filename);
            exit(1);
        }
    }
    return (file);
}

//close file if not stdin
void close_file(FILE* file)
{
    if (file != stdin)
    {
        fclose(file);
    }
}

//parse an unsigned int from a string
unsigned int uint_from_string(const char* str)
{
    char* data = NULL;
    unsigned long int conv = strtoul(str, &data, 10);
    unsigned int res = 0;
    if ((data != NULL && *data != 0) || (conv > UINT_MAX))
    {
        fprintf(stderr, "INVALID UNSIGNED INT (INPUT \"%s\")\n", str);
        exit(1);
    }
    else
    {
        res = (unsigned int) conv;
    }
    return (res);
}

//parse an unsigned int from a string
amount_t amount_from_string(const char* str)
{
    amount_t res=0;
    if (str[0] == '#')
    {
        res = amount_inf();
    }
    else
    {
        res = (amount_t) uint_from_string(str);
    }
    return (res);
}

//parse first line of a file. Looks for a line starting with '#'
//then the KNAPSACK field with the desired capacity, and VALUE with the
//expected value.
void parse_first_line(FILE* file, currency_t* charge,
                      amount_t* expected, bool* test)
{
    char* line = readline(file);
    if (line != NULL)
    {
        char* token = strtok(line, " :\t\n");
        if (token != NULL && strcmp(token, "#") == 0)
        {
            char* wtoken = strtok(NULL, " :\t\n");
            if (wtoken != NULL && (strcmp(wtoken, "CHARGE") == 0))
            {
                char* w_str = strtok(NULL, " :\t\n");
                if (w_str != NULL && strlen(w_str) > 0)
                {
                    *charge = uint_from_string(w_str);
                }
            }
            wtoken = strtok(NULL, " :\t\n");
            if (wtoken != NULL && (strcmp(wtoken, "COINS") == 0))
            {
                char* w_str = strtok(NULL, " :\t\n");
                if (w_str != NULL && strlen(w_str) > 0)
                {
                    *expected = amount_from_string(w_str);
                }
            }
            else
            {
                if (*test)
                {
                    printf("-t option expects COINS field in the first line\n");
                    *test = false;
                }
            }
        }
        else
        {
            //no # line, file should point at the beginning.
            rewind(file);
        }
        free(line);
    }
}

coin_t *coin_read_from_file(FILE *file, unsigned int *array_length)
{
    assert(file != NULL);
    coin_t* coins = NULL;
    unsigned int count = 0;
    while (!feof(file))
    {
        int readed=0;
        coin_t coin;
        readed = fscanf(file,"%u", &coin);
        if (readed != 1 && !feof(file))
        {
            printf("Invalid file!\n");
            exit(EXIT_FAILURE);
        } else if (readed == 1) {
            count++;
            //improve me: too many realloc calls.
            coins = realloc(coins, count * sizeof(coin_t));
            assert(coins != NULL);
            coins[count - 1] = coin;
        }
    }

    *array_length = count;
    return (coins);
}

//execute algorithms on the given file.
int run_file(const char* filename,
             bool do_backtracking,
             bool do_dynamic,
             bool test,
             currency_t charge)
{
    FILE* file = NULL;
    int fails = 0;
    amount_t expected = 0;
    unsigned int array_length = 0;
    file = open_file(filename);
    if (file != stdin)
    {
        //if not stdin, parse first line, starting with #
        currency_t aux = 0;
        parse_first_line(file, &aux, &expected, &test);
        if (charge == 0)   //not -w option, or -w 0.
        {
            printf("Reading CHARGE from file...\n");
            charge = aux;
        }
    }
    printf("Reading COINS from %s...\n", file == stdin ? "stdin" : "file");
    coin_t * coins = coin_read_from_file(file, &array_length);
    close_file(file);
    printf("charge: %u\n", charge);
    printf("denominations: ");
    for (unsigned int i=0; i < array_length; i++) {
        coin_dump(coins[i]);
        printf(" ");
    }
    printf("\n");
    amount_t backtracking_value = 0;
    if (do_backtracking)
    {
        set coin_set=set_empty();
        for (unsigned int i=0u; i < array_length; i++) {
            coin_set = set_add(coin_set, coins[i]);
        }
     //if backtracking is enabled, run it.
        printf("Backtracking solution...\n");
        amount_t value = change_making(charge, coin_set);
        printf("minimun amount of coins: ");
        amount_dump(value);
        printf("\n");
        coin_set = set_destroy(coin_set);
        if (test)
        {
            printf("Test - Value matches expected: %s\n",
                   value == expected ? "OK" : "FAIL");
            fails = fails + (value == expected ? 0 : 1);
        }
        backtracking_value = value;
    }
    if (do_dynamic)
    {
        //if dynamic is enabled, run it.
        printf("Dynamic solution...\n");
        amount_t value = 0;

        value = change_making_dyn(charge, coins, array_length);
        printf("minimun amount of coins: ");
        amount_dump(value);
        printf("\n");
        if (test)
        {
            printf("Test - Value matches expected: %s\n",
                   value == expected ? "OK" : "FAIL");
            fails = fails + (value == expected ? 0 : 1);
            if (do_backtracking)
            {
                printf("Test - Matches backtracking value: %s\n",
                       value == backtracking_value ? "OK" : "FAIL");
                fails = fails + (value == backtracking_value ? 0 : 1);
            }
        }
    }
    free(coins);
    return (fails);
}

bool is_option(const char* str)
{
    return (*str == '-' && strlen(str) == 2);
}

int main(int argc, char** argv)
{
    char* filenames[MAX_FILES];
    int c = 0;
    bool do_backtracking = false;
    bool do_dynamic = false;
    bool test = false;
    currency_t charge = 0;
    unsigned int files_count = 0;
    if (argc == 1)
    {
        show_usage(argv[0]);
        exit(1);
    }
    while ((c = getopt(argc, argv, "f:c:bdt")) != -1)
    {
        switch (c)
        {
            case 'b':
                do_backtracking = true;
                break;
            case 'd':
                do_dynamic = true;
                break;
            case 'f':
                optind--;
                while (optind < argc && !is_option(argv[optind]) &&
                        files_count < MAX_FILES)
                {
                    files_count++;
                    filenames[files_count - 1] = argv[optind];
                    optind++;
                }
                break;
            case 'c':
                charge = uint_from_string(optarg);
                break;
            case 't':
                test = true;
                break;
            case '?':
                show_usage(argv[0]);
                exit(1);
                break;
            default:
                break;
        }
    }
    if (files_count == 0)
    {
        filenames[0] = NULL;
        files_count = 1;
        test = false;
    }
    int fails = 0;
    for (unsigned int i = 0; i < files_count; i++)
    {
        printf("READING %s\n", filenames[i] == NULL ? "stdin" : filenames[i]);
        fails = run_file(filenames[i], do_backtracking,
                         do_dynamic, test, charge);
        printf("DONE %s.\n\n", filenames[i] == NULL ? "stdin" : filenames[i]);
    }
    if (fails > 0 && test)
    {
        printf("\n\n FAILS: %d \n\n", fails);
    }
    else if (test)
    {
        printf("\n\n ALL TESTS OK \n\n");
    }
    return 0;
}
