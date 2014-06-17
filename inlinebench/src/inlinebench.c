#include <stdio.h>

#include <libtime/libtime.h>

#include "maths.h"

int add_ints__extern_local(int a, int b)
{
    return a + b;
}

int mul_ints__extern_local(int a, int b)
{
    return a * b;
}

extern inline
int add_ints__extern_inline_local(int a, int b);
extern inline
int mul_ints__extern_inline_local(int a, int b);

struct time_result {
    uint64_t addtime, multime;
};

struct time_result test_extern(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r;

    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += add_ints__extern(i, 1000 - i);
    }
    end = libtime_cpu();
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += mul_ints__extern(i, 3);
    }
    end = libtime_cpu();
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_extern_local(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r;

    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += add_ints__extern_local(i, 1000 - i);
    }
    end = libtime_cpu();
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += mul_ints__extern_local(i, 3);
    }
    end = libtime_cpu();
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_static_inline(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r;

    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += add_ints__static_inline(i, 1000 - i);
    }
    end = libtime_cpu();
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += mul_ints__static_inline(i, 3);
    }
    end = libtime_cpu();
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_extern_inline(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r;

    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += add_ints__extern_inline(i, 1000 - i);
    }
    end = libtime_cpu();
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += mul_ints__extern_inline(i, 3);
    }
    end = libtime_cpu();
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_extern_inline_local(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r;

    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += add_ints__extern_inline_local(i, 1000 - i);
    }
    end = libtime_cpu();
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0, r = 0; i < 1000; i++) {
        r += mul_ints__extern_inline_local(i, 3);
    }
    end = libtime_cpu();
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

#define TRIAL_CNT 10

int main(int argc, char **argv)
{
    struct time_result accumulator;
    struct time_result tmp;
    int i;

    libtime_init();
    accumulator.addtime = 0;
    accumulator.multime = 0;
    for (i = 0; i < TRIAL_CNT; i++) {
        tmp = test_extern();
        accumulator.addtime += tmp.addtime;
        accumulator.multime += tmp.multime;
    }
    printf("extern - Avg. add time:\t\t\t%lu\n", accumulator.addtime / TRIAL_CNT);
    printf("extern - Avg. mul time:\t\t\t%lu\n", accumulator.multime / TRIAL_CNT);
    accumulator.addtime = 0;
    accumulator.multime = 0;
    for (i = 0; i < TRIAL_CNT; i++) {
        tmp = test_extern_local();
        accumulator.addtime += tmp.addtime;
        accumulator.multime += tmp.multime;
    }
    printf("local extern - Avg. add time:\t\t%lu\n", accumulator.addtime / TRIAL_CNT);
    printf("local extern - Avg. mul time:\t\t%lu\n", accumulator.multime / TRIAL_CNT);
    accumulator.addtime = 0;
    accumulator.multime = 0;
    for (i = 0; i < TRIAL_CNT; i++) {
        tmp = test_static_inline();
        accumulator.addtime += tmp.addtime;
        accumulator.multime += tmp.multime;
    }
    printf("static inline - Avg. add time:\t\t%lu\n", accumulator.addtime / TRIAL_CNT);
    printf("static inline - Avg. mul time:\t\t%lu\n", accumulator.multime / TRIAL_CNT);
    accumulator.addtime = 0;
    accumulator.multime = 0;
    for (i = 0; i < TRIAL_CNT; i++) {
        tmp = test_extern_inline();
        accumulator.addtime += tmp.addtime;
        accumulator.multime += tmp.multime;
    }
    printf("extern inline - Avg. add time:\t\t%lu\n", accumulator.addtime / TRIAL_CNT);
    printf("extern inline - Avg. mul time:\t\t%lu\n", accumulator.multime / TRIAL_CNT);
    accumulator.addtime = 0;
    accumulator.multime = 0;
    for (i = 0; i < TRIAL_CNT; i++) {
        tmp = test_extern_inline_local();
        accumulator.addtime += tmp.addtime;
        accumulator.multime += tmp.multime;
    }
    printf("local extern inline - Avg. add time:\t%lu\n", accumulator.addtime / TRIAL_CNT);
    printf("local extern inline - Avg. mul time:\t%lu\n", accumulator.multime / TRIAL_CNT);

    return 0;
}


