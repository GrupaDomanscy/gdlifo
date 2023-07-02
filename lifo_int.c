#include <stdlib.h>
#include <string.h>
#include "gdalloc.h"
#include "lifo_int.h"

gdlifo_list gdlifo_list_init(int chunk_size) {
    gdlifo_list gdlifo_list;
    gdlifo_list.first_index = -1;
    gdlifo_list.last_index = -1;
    gdlifo_list.allocated_size = 0;
    gdlifo_list.list = NULL;
    gdlifo_list.chunk_size = chunk_size;

    return gdlifo_list;
}

/**
 * Get total of items in the list
 *
 * @param gdlifo_list List pointer
 * @return How much items is in the list
 */
int gdlifo_list_get_total_items(gdlifo_list *gdlifo_list) {
    return gdlifo_list->last_index - gdlifo_list->first_index + 1;
}

/**
 * Expand the list in memory
 *
 * @param gdlifo_list List pointer
 */
void gdlifo_list_make_bigger(gdlifo_list *gdlifo_list) {
    gdlifo_list->allocated_size += gdlifo_list->chunk_size;
    if (gdlifo_list->list == NULL) {
        gdlifo_list->list = safe_malloc(gdlifo_list->allocated_size * sizeof(int));
    } else {
        gdlifo_list->list = safe_realloc(gdlifo_list->list, gdlifo_list->allocated_size * sizeof(int));
    }
}

void gdlifo_list_push_back(gdlifo_list *gdlifo_list, int item) {
    // If list is empty (no items / list is not allocated in memory), return
    if (gdlifo_list->list == NULL) {
        gdlifo_list_make_bigger(gdlifo_list);
        gdlifo_list->first_index = 0;
        gdlifo_list->last_index = 0;
    } else {
        // If we can't push, because next index will be outside allocated memory, we extend it.
        if (gdlifo_list->last_index + 1 == gdlifo_list->allocated_size) {
            gdlifo_list_make_bigger(gdlifo_list);
        }

        gdlifo_list->last_index += 1;
    }

    // Modify last index and add the element to LIFO structure
    gdlifo_list->list[gdlifo_list->last_index] = item;
}

int *gdlifo_list_get_next(gdlifo_list *gdlifo_list) {
    // if list doesn't have any items, return NULL
    if (gdlifo_list->list == NULL) {
        return NULL;
    }

    int *result = (int *) safe_malloc(sizeof(int));
    int total_items = gdlifo_list_get_total_items(gdlifo_list);

    // if we are getting last item from the list, deallocate the list and return the item
    if (total_items == 1) {
        *result = gdlifo_list->list[gdlifo_list->first_index];

        gdlifo_list->first_index = -1;
        gdlifo_list->last_index = -1;
        gdlifo_list->allocated_size = 0;
        free(gdlifo_list->list);
        gdlifo_list->list = NULL;
    } else {
        // if we are getting the item without edge cases, return item and increase first index by 1
        *result = gdlifo_list->list[gdlifo_list->first_index];
        gdlifo_list->first_index += 1;
        total_items -= 1;

        // check if we can reallocate whole array because of the hole in the beggining of array
        int allocated_chunks = gdlifo_list->allocated_size / gdlifo_list->chunk_size;
        int required_chunks = ((total_items - 1) / gdlifo_list->chunk_size) + 1;

        if (required_chunks < allocated_chunks) {
            gdlifo_list->allocated_size = required_chunks * gdlifo_list->chunk_size;

            memmove(gdlifo_list->list + 0, gdlifo_list->list + gdlifo_list->first_index, gdlifo_list->allocated_size * sizeof(int));
            gdlifo_list->list = safe_realloc(gdlifo_list->list, gdlifo_list->allocated_size * sizeof(int));

            gdlifo_list->first_index = 0;
            gdlifo_list->last_index = total_items - 1;
        }
    }

    return result;
}