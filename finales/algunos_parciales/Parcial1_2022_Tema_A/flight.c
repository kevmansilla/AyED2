/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 3 ;

Flight flight_from_file(FILE* file, char code)
{
    Flight flight;
    flight.code = code;

    int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT, &flight.type, &flight.hour, &flight.passengers_amount);
    // printf("code=%c, type=%u, hour=%u, am=%u\n", flight.code, flight.type, flight.hour, flight.passengers_amount);
    // me da invalid array
    if (res != AMOUNT_OF_FLIGHT_VARS) {
      fprintf(stderr, "Invalid array.\n");
      exit(EXIT_FAILURE);
    }

    return flight;
}
