#include <stdlib.h>
#include <criterion/criterion.h>
#include <gdalloc.h>

#include "lifo_int.h"

Test(StandardInit, WithoutResize) {
    gdlifo_list lifo = gdlifo_list_init(1024);

    gdlifo_list_push_back(&lifo, 1);
    gdlifo_list_push_back(&lifo, 2);
    gdlifo_list_push_back(&lifo, 3);
    gdlifo_list_push_back(&lifo, 4);

    int *result;

    int i = 0;

    while (result = gdlifo_list_get_next(&lifo), result != NULL) {
        i++;

        cr_assert(*result == i);

        free(result);
    }

    cr_assert(i == 4);
}

Test(StandardInit, WithResize) {
    gdlifo_list lifo_buffer_expand = gdlifo_list_init(24);

    for (int i = 1; i <= 72; i++) {
        gdlifo_list_push_back(&lifo_buffer_expand, i);
    }

    int i = 0;

    int *result;
    while (result = gdlifo_list_get_next(&lifo_buffer_expand), result != NULL) {
        i++;
        cr_assert(*result == i);

        free(result);
    }

    cr_assert(i == 72);
}

Test(DynamicInit, WithoutResize) {
    gdlifo_list **lifo = safe_malloc(sizeof(gdlifo_list **));
    gdlifo_list_dynamic_init(lifo, 1024);

    gdlifo_list_push_back(*lifo, 1);
    gdlifo_list_push_back(*lifo, 2);
    gdlifo_list_push_back(*lifo, 3);
    gdlifo_list_push_back(*lifo, 4);

    int *result;

    int i = 0;

    while (result = gdlifo_list_get_next(*lifo), result != NULL) {
        i++;
        cr_assert(*result == i);

        free(result);
    }

    cr_assert(i == 4);
}

Test(DynamicInit, WithResize) {
    gdlifo_list **lifo_buffer_expand = safe_malloc(sizeof(gdlifo_list **));
    gdlifo_list_dynamic_init(lifo_buffer_expand, 24);

    for (int i = 1; i <= 72; i++) {
        gdlifo_list_push_back(*lifo_buffer_expand, i);
    }

    int i = 0;

    int *result;
    while (result = gdlifo_list_get_next(*lifo_buffer_expand), result != NULL) {
        i++;
        cr_assert(*result == i);

        free(result);
    }

    cr_assert(i == 72);
}
