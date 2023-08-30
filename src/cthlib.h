/*
 The MIT License (MIT)

Copyright © 2023 Kasyanov Nikolay ALexeyevich (Unbewohnte)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifdef __STDC_NO_THREADS__
#error "threads.h is not provided on this system!"
#endif


#include <threads.h>
#include <stdint.h>


typedef struct pool_t {
    size_t thread_count;
    thrd_t* threads;
} pool_t;


/*
Creates a new pool.

Returns a pointer to a newly created pool, NULL if an error occurs during creation
*/
pool_t* pool_new();


/*
Frees up memory allocated to store a pool, sets a pointer to NULL as
to show that there is no pool present.
*/
void pool_free(pool_t** pool);


/*
Runs given function with arguments in parallel
*/
void pool_do(pool_t* pool, void* func, void* arg);


/*
Waits for all parallel tasks to finish
*/
void pool_join(pool_t* pool);