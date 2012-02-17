typedef struct DatabaseConnection DatabaseConnection;

/*
 * Function that takes an SQL query string and sets results to an array of
 * pointer with the result of the query. the value returned specifies the number
 * of items in the returned array of results. The returned array of results are
 * statically allocated and should not be deallocated using free()
 */

typedef unsigned int (*QueryDatabase)(
    DatabaseConnection * const connection, const char * const query_string, void *** const results);

/* Connection to a database. */
struct DatabaseConnection {
    const char *url;
    unsigned int port;
    QueryDatabase query_database;
};

/* Connect to a database */
DatabaseConnection *connect_to_database(const char * const url,
                                        const unsigned int port);










