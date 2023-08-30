/*
 The MIT License (MIT)

Copyright © 2023 Kasyanov Nikolay ALexeyevich (Unbewohnte)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include "cthlib.h"
#include <stdlib.h>


/*
Creates a new pool.

Returns a pointer to a newly created pool, NULL if an error occurs during creation
*/
pool_t* pool_new() {
    pool_t* pool = NULL;

    pool = malloc(sizeof(pool_t));    
    if (!pool) {
        return NULL;
    }

    pool->thread_count = 0;
    pool->threads = NULL;

    return pool;
}


/*
Frees up memory allocated to store a pool, sets a pointer to NULL as
to show that there is no pool present.
*/
void pool_free(pool_t** pool) {
    if (!pool) {
        return;
    }
    if (!(*pool)) {
        return;
    }

    free(*pool);
    *pool = NULL;

    return;
}


/*
Runs given function with arguments in parallel
*/
void pool_do(pool_t* pool, void* func, void* arg) {
    if (!pool | !func | !arg) {
        return;
    }

    pool->threads = realloc(pool->threads, sizeof(thrd_t) * (pool->thread_count+1));
    thrd_create(&(pool->threads[pool->thread_count]), (thrd_start_t) func, arg);
    pool->thread_count++;

    return;
}


/*
Waits for all parallel tasks to finish
*/
void pool_join(pool_t* pool) {
    if (!pool) {
        return;
    }

    for (size_t i = 0; i < pool->thread_count; i++) {
        thrd_join(pool->threads[i], NULL);
    }

    return;
}