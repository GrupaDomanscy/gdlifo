#ifndef GD_LIFO_H_
#define GD_LIFO_H_

/**
 * LIFO structure
 */
typedef struct
{
    int first_index;
    int last_index;
    int allocated_size;
    int *list;
    int chunk_size;
} gdlifo_list;


/**
 * Initialize lifo int list
 *
 * @param chunk_size Size of memory chunk
 */
gdlifo_list gdlifo_list_init(int chunk_size);

/**
 * Adds one element to the back of the LIFO structure
 *
 * @param list Pointer to lifo list
 * @param item Item to push back
 */
void gdlifo_list_push_back(gdlifo_list *list, int item);

/**
 * Gets and removes first element from the head of LIFO structure.
 *
 * @param list Pointer to lifo list
 * @return Int pointer with next item value. It can return NULL if list is empty.
 */
int *gdlifo_list_get_next(gdlifo_list *list);

#endif // GD_LIFO_H_