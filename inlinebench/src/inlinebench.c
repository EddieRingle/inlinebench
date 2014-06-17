#include <stdio.h>
#include <stdint.h>

#include <libtime/libtime.h>

#include "maths.h"

#define bmin(x, y) ((y) ^ (((x) ^ (y)) & -((x) < y)))

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
    int      addresult, mulresult;
    uint64_t addtime, multime;
};

#define LOOP_MAX 1000

struct time_result test_extern(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r = 0;

    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += add_ints__extern(i, r);
    }
    end = libtime_cpu();
    result.addresult = r;
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += mul_ints__extern(i, r);
    }
    end = libtime_cpu();
    result.mulresult = r;
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_extern_local(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r = 0;

    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += add_ints__extern_local(i, r);
    }
    end = libtime_cpu();
    result.addresult = r;
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += mul_ints__extern_local(i, r);
    }
    end = libtime_cpu();
    result.mulresult = r;
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_static_inline(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r = 0;

    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += add_ints__static_inline(i, r);
    }
    end = libtime_cpu();
    result.addresult = r;
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += mul_ints__static_inline(i, r);
    }
    end = libtime_cpu();
    result.mulresult = r;
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_extern_inline(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r = 0;

    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += add_ints__extern_inline(i, r);
    }
    end = libtime_cpu();
    result.addresult = r;
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += mul_ints__extern_inline(i, r);
    }
    end = libtime_cpu();
    result.mulresult = r;
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

struct time_result test_extern_inline_local(void)
{
    struct time_result result;
    uint64_t start, end;
    int i, r = 0;

    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += add_ints__extern_inline_local(i, r);
    }
    end = libtime_cpu();
    result.addresult = r;
    result.addtime = libtime_cpu_to_wall(end - start);
    start = libtime_cpu();
    for (i = 0; i < LOOP_MAX; i++) {
        r += mul_ints__extern_inline_local(i, r);
    }
    end = libtime_cpu();
    result.mulresult = r;
    result.multime = libtime_cpu_to_wall(end - start);

    return result;
}

#define TRIAL_CNT 10

#define testfn(_ib_fn, _ib_name) \
    { \
        accumulator.addresult = 0; \
        accumulator.addtime = 0; \
        accumulator.mulresult = 0; \
        accumulator.multime = 0; \
        lowest.addtime = UINT32_MAX; \
        lowest.multime = UINT32_MAX; \
        for (i = 0; i < TRIAL_CNT; i++) { \
            tmp = _ib_fn(); \
            accumulator.addtime += tmp.addtime; \
            accumulator.multime += tmp.multime; \
            accumulator.addresult += tmp.addresult; \
            accumulator.mulresult += tmp.mulresult; \
            lowest.addtime = bmin(lowest.addtime, tmp.addtime); \
            lowest.multime = bmin(lowest.multime, tmp.multime); \
        } \
        printf(_ib_name " functions:\n"); \
        printf("Avg. add time: %4lu\t\t(Result: %4d)\n", accumulator.addtime / TRIAL_CNT, accumulator.addresult); \
        printf("Min. add time: %4lu\t\t(Result: %4d)\n", lowest.addtime, accumulator.addresult); \
        printf("Avg. mul time: %4lu\t\t(Result: %4d)\n", accumulator.multime / TRIAL_CNT, accumulator.mulresult); \
        printf("Min. mul time: %4lu\t\t(Result: %4d)\n", lowest.multime, accumulator.mulresult); \
    }

int main(int argc, char **argv)
{
    struct time_result accumulator, lowest;
    struct time_result tmp;
    int i;

    libtime_init();
    testfn(test_extern, "extern");
    testfn(test_extern_local, "local extern");
    testfn(test_static_inline, "static inline");
    testfn(test_extern_inline, "extern inline");
    testfn(test_extern_inline_local, "local extern inline");

    return 0;
}


