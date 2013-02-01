#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmockery/cmockery.h"
#include "database.h"

extern DatabaseConnection* connect_to_customer_database();
extern unsigned int get_customer_id_by_name(
    DatabaseConnection * const connection, const char * const customer_name);

/* Mock query database fucntion. */
unsigned int mock_query_database(
    DatabaseConnection * const connection, const char * const query_string, void ***results)
{
    *results = (void **)mock();
    return (unsigned int)mock();
}

/* Mock of the connect to database function. */
DatabaseConnection *connect_to_database(const char *const database_url,
                                        const unsigned int port)
{
    return (DatabaseConnection *)mock();
}

void test_connect_to_customer_database(void **state)
{
    will_return(connect_to_database, 0x0DA7ABA53);
    assert_true(connect_to_customer_database() == (DatabaseConnection *)0x0DA7ABA53);
}

/* This test fails as the mock function connect_to_database() will have no value
 * to return. */
void fail_connect_to_customer_database(void **state)
{
    assert_true(connect_to_customer_database() == (DatabaseConnection *)0x0DA7ABA53);
}

void test_get_customer_id_by_name(void **state)
{
    DatabaseConnection connection = {
        "somedatabase.somewhere.com", 12345678, mock_query_database
    };
    /* Return a single customer ID when mock_query_database() is called. */
    int customer_ids = 543;
    will_return(mock_query_database, &customer_ids);
    will_return(mock_query_database, 1);
    assert_int_equal(get_customer_id_by_name(&connection, "john doe"), 543);
}

int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_connect_to_customer_database),
        unit_test(fail_connect_to_customer_database),
        unit_test(test_get_customer_id_by_name),
    };
    return run_tests(tests);
}
