#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmockery/cmockery.h"

/* Ensure add() adds two intergers correctly. */
void test_add(void **state)
{
    assert_int_equal(add(3, 3), 6);
    assert_int_equal(add(3, -3), 0);
}

/* Ensure sub() subtracts two intergers correctly */
void test_sub(void **state)
{
    assert_int_equal(sub(3, 3), 0);
    assert_int_equal(sub(3, -3), 6);
}

int main(int argc, char *argv[])
{
    const UnitTest tests[] = {
        unit_test(test_add),
        unit_test(test_sub),
    };

    return run_tests(tests);
}

