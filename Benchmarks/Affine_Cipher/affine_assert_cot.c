#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 95
#define Z95_CONVERSION_CONSTANT 32

typedef struct
{
    int a;
    int b;
} affine_key_t;

int modular_multiplicative_inverse(unsigned int a, unsigned int m)
{
    int x[2] = {1, 0};
    div_t div_result;

    if (m == 0) {
        return 0;
    }

    a %= m;
    if (a == 0) {
        return 0;
    }

    // Invariant: 0 < a < m at this point
    assert(a > 0 && a < m);

    div_result.rem = a;

    while (div_result.rem > 0)
    {
        div_result = div(m, a);

        // Invariant: m >= a >= 0

