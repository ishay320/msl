#include <stdio.h>
#include <time.h>

#include "ansi.h"

static clock_t _test_start = 0;
static size_t _tests_run   = 0;

void print_success(const char* test_name) {
    double ms = (double)(clock() - _test_start) * 1000.0 / CLOCKS_PER_SEC;
    _tests_run++;
    printf(AN_GREEN "[%ld] '%s' passed." AN_RESET AN_DIM " (%.3f ms)\n" AN_RESET, _tests_run, test_name, ms);
}

#define RUN(fn)                \
    do {                       \
        _test_start = clock(); \
        fn();                  \
        print_success(#fn);    \
    } while (0)

#define START_SUITE                \
    clock_t suite_start = clock(); \
    printf(AN_BOLD AN_CYAN "Running " __FILE__ " tests..." AN_RESET "\n")

#define SUMMERY                                                                                                                 \
    do {                                                                                                                        \
        double _total_ms = (double)(clock() - suite_start) * 1000.0 / CLOCKS_PER_SEC;                                           \
        printf(AN_GREEN "\nAll %ld " __FILE__ " tests passed!" AN_RESET AN_DIM " (%.3f ms)\n" AN_RESET, _tests_run, _total_ms); \
    } while (0)
