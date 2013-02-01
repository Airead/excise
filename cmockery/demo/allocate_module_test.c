#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmockery/cmockery.h"

extern void leak_memory();
extern void buffer_overflow();
extern void buffer_underflow();

/* Test case that fails as leak_memory() leaks a dynamically allocated block. */
void leak_memory_test(void **state)
{
    leak_memory();
}

/* Test case that fails as buffer_overflow() corrupts an allocated block.*/
void buffer_overflow_test(void **state)
{
    buffer_overflow();
}

/* Test case that fails as buffer_underflow() corrupts an allocated block */

void buffer_underflow_test(void **state)
{
    buffer_underflow();
}

int main(int argc, char *argv[])
{
    const UnitTest tests[] = {
        unit_test(leak_memory_test),
        unit_test(buffer_overflow_test),
        unit_test(buffer_underflow_test),
    };
    
    return run_tests(tests);
}
