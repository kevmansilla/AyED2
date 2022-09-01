#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>

#include "string.h"

int main() {
    string str1 = string_create("mansilla");
    string str2 = string_create("mansillv");

    printf("Result string_eq():\n");
    if (string_eq(str1, str2) == 1){
      printf("String are equal\n");
    } else{
      printf("String are not equal\n");
    }
    printf("\n");
    printf("Result string_eq():\n");
    if (string_less(str1, str2)){
      printf("true => str1 < str2\n");
    } else {
      printf("false => str1 > str2\n");
    }

    str1 = string_destroy(str1);
    str2 = string_destroy(str2);

    return (EXIT_SUCCESS);
}
