# GDLIFO

Automatically resizable integer LIFO structure used internally by Grupa Domańscy company.

When you get next element and remove it from the structure, it checks if list can be resized to be smaller in memory.
Same for pushing to the list but vice-versa.

## WARNING

This library uses [GDALLOC](https://github.com/GrupaDomanscy/gdalloc) under the hood. It is going to terminate your program if `malloc`, `calloc` or `realloc` function returns NULL pointer (computer out of memory).

## Installation

You have to install dependencies first:
    - [GDALLOC](https://github.com/GrupaDomanscy/gdalloc)
    - [CRITERION](https://github.com/Snaipe/Criterion)

Then you run `make` and `sudo make install`

Installation process tested on Fedora Workstation 37 x86_64 KDE Plasma  
Kernel: 6.3.7-100.fc37.x86_64

## How it works?

1. Initialize the LIFO and provide the chunk size. It's a number by which library will expand or decrease size of 
structure in memory. We recommend using it with 1024 or 512 (or any large number). At minimum you can use 2, it will 
probably be ok, but your program can do lots of `malloc` and `realloc` operations. We did not test it with 1, but in 
theory it can work too. Providing anything less or equal to 0 will lead to undefined behaviour.
```c
#include "libs/gdlifo/lifo_int.h"   

int main() {
    gdlifo_list lifo = gdlifo_list_init(1024);

    return 0;
}
```

2. Push elements to the structure
```c
#include "libs/gdlifo/lifo_int.h"

int main() {
    gdlifo_list lifo = gdlifo_list_init(1024);

    gdlifo_list_push_back(&lifo, 1);
    gdlifo_list_push_back(&lifo, 2);
    gdlifo_list_push_back(&lifo, 3);
    gdlifo_list_push_back(&lifo, 4);

    return 0;
}
```

3. Get items until null value is returned (no more items inside). Remember that int pointer is returned. 
Under the hood it calls `malloc`, so you have to free it after using it. 
```c
#include "libs/gdlifo/lifo_int.h"

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
    
    return 0;
}
```

One more example is in main.c, you can check it out.