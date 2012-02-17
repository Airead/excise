#include <assert.h>

#define UNIT_TESTING 1

/* if unit testing is enable override assert with mock_assert(). */
#if UNIT_TESTING
extern void mock_assert(const int result, const char * const expression, const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif //UNIT_TESTING

void increment_value(int * const value)
{
    assert(value);
    (*value)++;
}

void decrement_value(int * const value)
{
    if (value) {
        (*value)--;
    }
}
