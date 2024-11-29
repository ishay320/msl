#include <stdio.h>

#include "array.h"

int main(int argc, char* argv[])
{
    int* array = array_init(int);
    for (int i = 0; i < 50; i++) {
        array_push(array, i);
    }
    for (size_t i = 0; i < 50; i++) {
        printf("%d\n", array[i]);
    }

    array_push_rval(array, 420);
    printf("%d\n", array[50]);

    array_free(array);
    return 0;
}
