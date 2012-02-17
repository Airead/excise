#include <stddef.h>
#include <stdio.h>
#include "database.h"

/* Connection to the database containing customer infromation. */
DatabaseConnection *connect_to_customer_database()
{
    return connect_to_database("customers.abcd.org", 321);
}

/*
 * Find the ID of a customer by his/her name returning a value > 0 if
 * successful, 0 otherwise
 */
unsigned int get_customer_id_by_name(
    DatabaseConnection * const connection,
    const char * const customer_name)
{
    char query_string[256];
    int number_of_results;
    void **results;

    snprintf(query_string, sizeof(query_string),
              "SELECT ID FROM CUSTOMERS WHERE NAME = %s", customer_name);
    number_of_results = connection->query_database(connection, query_string, &results);

    if (number_of_results != 1) {
        return -1;
    }

    return (unsigned int)results[0];
}
