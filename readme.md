# Multiple Small Libraries

This repo contains my standard libraries in c that help me not write everything from scratch every time because c...


## Array

A simple dynamic array implementation that works with any data type.

### Key Features:

- Dynamically resizable to accommodate varying data sizes.
- Type-agnostic: Operates based on the size of the stored data, allowing flexibility without hardcoding types.
- Lightweight: Focused on speed and efficiency.

>Important Note:
This library does not perform runtime type checks. The correct type and size must be carefully managed to avoid runtime errors.

### Usage:

```c
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

    array_free(array);
    return 0;
}
```
