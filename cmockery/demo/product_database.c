#include "database.h"

/* Connect to the database containing customer information */
DatabaseConnection *connect_to_product_database()
{
    return connect_to_database("products.abcd.org", 322);
}
