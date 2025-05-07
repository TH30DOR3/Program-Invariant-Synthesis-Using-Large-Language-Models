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

    // Invariant: modulus m must not be zero
    assert(m != 0);

    a %= m;
    if (a == 0) {
        return 0;
    }

    div_result.rem = a;

    while (div_result.rem > 0)
    {
        div_result = div(m, a);

        // Invariant: remainder must be less than divisor
        assert(div_result.rem < a);

        m = a;
        a = div_result.rem;

        int next = x[1] - (x[0] * div_result.quot);

        x[1] = x[0];
        x[0] = next;
    }

    // Invariant: result must be within valid range after mod
    return x[1];
}

affine_key_t inverse_key(affine_key_t key)
{
    // Invariant: 'a' must be coprime with ALPHABET_SIZE for inverse to exist
    assert(modular_multiplicative_inverse(key.a, ALPHABET_SIZE) != 0);

    affine_key_t inverse;

    inverse.a = modular_multiplicative_inverse(key.a, ALPHABET_SIZE);
    inverse.a += ALPHABET_SIZE;
    inverse.a %= ALPHABET_SIZE;
    inverse.b = -(key.b % ALPHABET_SIZE) + ALPHABET_SIZE;

    return inverse;
}

void affine_encrypt(char *s, affine_key_t key)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        // Invariant: input character must be in printable ASCII
        assert(s[i] >= Z95_CONVERSION_CONSTANT && s[i] < Z95_CONVERSION_CONSTANT + ALPHABET_SIZE);

        int c = (int)s[i] - Z95_CONVERSION_CONSTANT;
        c *= key.a;
        c += key.b;
        c %= ALPHABET_SIZE;

        // Invariant: encrypted character must also be in range
        assert(c >= 0 && c < ALPHABET_SIZE);

        s[i] = (char)(c + Z95_CONVERSION_CONSTANT);
    }
}

void affine_decrypt(char *s, affine_key_t key)
{
    affine_key_t inverse = inverse_key(key);

    for (int i = 0; s[i] != '\0'; i++)
    {
        // Invariant: encrypted char must be within printable ASCII
        assert(s[i] >= Z95_CONVERSION_CONSTANT && s[i] < Z95_CONVERSION_CONSTANT + ALPHABET_SIZE);

        int c = (int)s[i] - Z95_CONVERSION_CONSTANT;
        c += inverse.b;
        c *= inverse.a;
        c %= ALPHABET_SIZE;

        // Invariant: decrypted char must be valid
        assert(c >= 0 && c < ALPHABET_SIZE);

        s[i] = (char)(c + Z95_CONVERSION_CONSTANT);
    }
}

void test_string(const char *s, const char *ciphertext, int a, int b)
{
    // Invariant: ALPHABET_SIZE must not be zero for modular inverse
    assert(ALPHABET_SIZE != 0);

    // Invariant: 'a' must be valid for modular inverse
    assert(modular_multiplicative_inverse(a, ALPHABET_SIZE) != 0);

    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    assert(copy != NULL); // Invariant: malloc should not fail

    strcpy(copy, s);

    affine_key_t key = {a, b};

    affine_encrypt(copy, key);
    assert(strcmp(copy, ciphertext) == 0); // Encryption correctness

    affine_decrypt(copy, key);
    assert(strcmp(copy, s) == 0); // Decryption restores original

    free(copy);
}

static void tests()
{
    test_string("Hello!", "&3ddy2", 7, 11);
    test_string("TheAlgorithms/C", "DNC}=jHS2zN!7;E", 67, 67);
    test_string("0123456789", "840,($ {ws", 91, 88);
    test_string("7W@;cdeRT9uL", "JDfa*we?z&bL", 77, 76);
    test_string("~Qr%^-+++$leM", "r'qC0$sss;Ahf", 8, 90);
    test_string("The quick brown fox jumps over the lazy dog",
                "K7: .*6<4 =-0(1 90' 5*2/, 0):- +7: 3>%& ;08", 94, 0);
    test_string(
        "One-1, Two-2, Three-3, Four-4, Five-5, Six-6, Seven-7, Eight-8, "
        "Nine-9, Ten-10",
        "H&60>\\2*uY0q\\2*p4660E\\2XYn40x\\2XDB60L\\2VDI0 "
        "\\2V6B6&0S\\2%D=p;0'\\2tD&60Z\\2*6&0>j",
        51, 18);

    printf("All tests have successfully passed!\n");
}

int main()
{
    tests();
    return 0;
}
