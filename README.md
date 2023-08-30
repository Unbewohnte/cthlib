# cthlib
## C threads helper lib

A small library to help with parallel function execution

## Functions

| Funcion | Description |
| --- | ----------- |
| `pool_t* pool_new` | Creates a new pool |
| `void pool_free(pool_t** pool)` | Frees up memory allocated to store a pool |
| `void pool_do(pool_t* pool, void* func, void* arg)` | Runs given function with arguments in parallel |
| `void pool_join(pool_t* pool)` | Waits for all parallel tasks to finish |

## Test example

```c
#include "../src/cthlib.h"
#include <threads.h>
#include <stdio.h>
#include <stdatomic.h>


void job(int* i) {
    printf("start: %d\n", *i);
    thrd_sleep(&(struct timespec){.tv_sec=2}, NULL);
    *i = *i + 1;
    printf("end: %d\n", *i);
}

atomic_int count = 0;

int main() {
    pool_t* p = pool_new();
    
    for (size_t i = 0; i < 5; i++) {
        // Runs in parallel
        pool_do(p, job, (void*) &count);
    }

    pool_join(p);
    pool_free(&p);
}
```

## License 
MIT