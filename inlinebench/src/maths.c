#include "maths.h"

int add_ints__extern(int a, int b)
{
    return a + b;
}

int mul_ints__extern(int a, int b)
{
    return a * b;
}

extern inline
int add_ints__extern_inline(int a, int b);
extern inline
int mul_ints__extern_inline(int a, int b);
