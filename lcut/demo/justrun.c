#include <lcut.h>

void tc_trivial_test(lcut_tc_t *tc, void *data) {
    
}

int main(int argc, char *argv[])
{
    lcut_ts_t *suite = NULL;
    LCUT_TEST_BEGIN("A Trivial test", NULL, NULL);

    LCUT_TS_INIT(suite, "A Trivial test suite", NULL, NULL);
    LCUT_TC_ADD(suite, "A Trival test case", tc_trivial_test, NULL, NULL, NULL);
    LCUT_TS_ADD(suite);

    LCUT_TEST_RUN();
    LCUT_TEST_REPORT();
    LCUT_TEST_END();

    return 0;
}
