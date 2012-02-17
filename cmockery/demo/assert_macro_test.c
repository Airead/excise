#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <google/cmockery.h>

extern const char * get_status_code_string(const unsigned int status_code);
extern unsigned int string_to_status_code(const char *const status_code_string);

/*
 * This test will fail since the string returned by get_status_code_string(0)
 * doesn't match "Connection timed out".
 */
void get_status_code_string_test(void **state)
{
    assert_string_equal(get_status_code_string(0), "Address not found");
    assert_string_equal(get_status_code_string(1), "Connection time out");
}

/*
 * This test will fail since the status code of "Connection timed out" isn't 1
 */
void string_to_status_code_test(void **state)
{
    assert_int_equal(string_to_status_code("Address not found"), 0);

    assert_int_equal(string_to_status_code("Connetion time out"), 1);
}

int main(int argc, char *argv[])
{
    const UnitTest tests[] = {
        unit_test(get_status_code_string_test),
        unit_test(string_to_status_code_test),
    };

    return run_tests(tests);
}
