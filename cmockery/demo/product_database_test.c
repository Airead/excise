#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmockery/cmockery.h"
#include "database.h"

/* Mock connect to database function.
 * NOTE: This mock function is very general could be shared between tests
 * that use the imaginary database.h module. */
DatabaseConnection* connect_to_database(const char * const url,
                                        const unsigned int port) {
    check_expected(url);
    check_expected(port);
    return (DatabaseConnection*)mock();
}

void test_connect_to_product_database(void **state) {
    expect_string(connect_to_database, url, "products.abcd.org");
    expect_value(connect_to_database, port, 322);
    will_return(connect_to_database, 0xDA7ABA53);
    assert_int_equal(connect_to_product_database(), 0xDA7ABA53);
}

/* This test will fail since the expected URL is different to the URL that is
 * passed to connect_to_database() by connect_to_product_database(). */
void test_connect_to_product_database_bad_url(void **state) {
    expect_string(connect_to_database, url, "products.abcd.com");
    expect_value(connect_to_database, port, 322);
    will_return(connect_to_database, 0xDA7ABA53);
    assert_int_equal((int)connect_to_product_database(), 0xDA7ABA53);
}

/* This test will fail since the mock connect_to_database() will attempt to
 * retrieve a value for the parameter port which isn't specified by this
 * test function. */
void test_connect_to_product_database_missing_parameter(void **state) {
    expect_string(connect_to_database, url, "products.abcd.org");
    will_return(connect_to_database, 0xDA7ABA53);
    assert_int_equal((int)connect_to_product_database(), 0xDA7ABA53);
}

int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_connect_to_product_database),
        unit_test(test_connect_to_product_database_bad_url),
        unit_test(test_connect_to_product_database_missing_parameter),
    };
    return run_tests(tests);
}
