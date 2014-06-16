#ifndef __included_maths_h
#define __included_maths_h

extern
int add_ints__extern(int a, int b);
extern
int mul_ints__extern(int a, int b);

extern
int add_ints__extern_local(int a, int b);
extern
int mul_ints__extern_local(int a, int b);

static inline
int add_ints__static_inline(int a, int b)
{
    return a + b;
}
static inline
int mul_ints__static_inline(int a, int b)
{
    return a * b;
}

inline
int add_ints__extern_inline(int a, int b)
{
    return a + b;
}
inline
int mul_ints__extern_inline(int a, int b)
{
    return a * b;
}

inline
int add_ints__extern_inline_local(int a, int b)
{
    return a + b;
}
inline
int mul_ints__extern_inline_local(int a, int b)
{
    return a * b;
}

#endif /* __included_maths_h */

