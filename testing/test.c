/*
 The MIT License (MIT)

Copyright © 2023 Kasyanov Nikolay ALexeyevich (Unbewohnte)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


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
        pool_do(p, job, (void*) &count);
    }

    pool_join(p);
    pool_free(&p);
}