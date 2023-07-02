#include <stdlib.h>
#include <stdio.h>
#include "lifo_int.h"

int main() {
    gdlifo_list lifo = gdlifo_list_init(1024);

    gdlifo_list_push_back(&lifo, 1);
    gdlifo_list_push_back(&lifo, 2);
    gdlifo_list_push_back(&lifo, 3);
    gdlifo_list_push_back(&lifo, 4);

    int *result;

    while (result = gdlifo_list_get_next(&lifo), result != NULL) {
        printf("%d\n", *result);

        free(result);
    }

    gdlifo_list lifo_buffer_expand = gdlifo_list_init(24);

    for (int i = 1; i <= 72; i++) {
        gdlifo_list_push_back(&lifo_buffer_expand, i);
    }

    while (result = gdlifo_list_get_next(&lifo_buffer_expand), result != NULL) {
        printf("%d \n", *result);

        free(result);
    }

    return 0;
}