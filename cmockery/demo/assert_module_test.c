#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmockery/cmockery.h"

extern void increment_value(int * const value);
extern void decrement_value(int * const value);

/*
 * This test case will fail but the assert is caught by run_tests and the next
 * test is executed.
 */
void increment_value_fail(void **state)
{
    increment_value(NULL);
}

/*
 * This test case succeeds since increment_value() asserts on the NULL
 * pointer.
 * */
void increment_value_assert(void **state)
{
    expect_assert_failure(increment_value(NULL))
}

/*
 * This test case fails since decrement_value() doesn't assert on a NULL pointer
 */
void decrement_value_fail(void **state)
{
    expect_assert_failure(decrement_value(NULL));
}

int main(int argc, char * argv[])
{
    const UnitTest tests[] = {
        unit_test(increment_value_fail),
        unit_test(increment_value_assert),
        unit_test(decrement_value_fail),
    };

    return run_tests(tests);
}
