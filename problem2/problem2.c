
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

// Checked addition
bool check_add(int32_t a, int32_t b, int32_t *result)
{
    if (result == NULL)
        return false;

    // Positive overflow
    if ((b > 0) && (a > INT32_MAX - b))
        return false;

    // Negative overflow (underflow)
    if ((b < 0) && (a < INT32_MIN - b))
        return false;

    *result = a + b;
    return true;
}

// Checked subtraction
bool check_sub(int32_t a, int32_t b, int32_t *result)
{
    if (result == NULL)
        return false;

    // Subtracting a negative number may overflow
    if ((b < 0) && (a > INT32_MAX + b))
        return false;

    // Subtracting a positive number may underflow
    if ((b > 0) && (a < INT32_MIN + b))
        return false;

    *result = a - b;
    return true;
}

// Checked multiplication
bool check_mul(int32_t a, int32_t b, int32_t *result)
{
    if (result == NULL)
        return false;

    // Multiplication by zero
    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }

    // Special overflow case
    if ((a == INT32_MIN && b == -1) ||
        (b == INT32_MIN && a == -1)) {
        return false;
    }

    // Positive * Positive
    if (a > 0 && b > 0) {
        if (a > INT32_MAX / b)
            return false;
    }
    // Positive * Negative
    else if (a > 0 && b < 0) {
        if (b < INT32_MIN / a)
            return false;
    }
    // Negative * Positive
    else if (a < 0 && b > 0) {
        if (a < INT32_MIN / b)
            return false;
    }
    // Negative * Negative
    else {
        if (a < INT32_MAX / b)
            return false;
    }

    *result = a * b;
    return true;
}

int main(void)
{
    int32_t a = 23;
    int32_t b = -2147483647;
    int32_t result = 0;

    if (!check_add(a, b, &result))
        printf("Overflow detected in addition\n");
    else
        printf("Addition result: %" PRId32 "\n", result);

    if (!check_sub(a, b, &result))
        printf("Overflow detected in subtraction\n");
    else
        printf("Subtraction result: %" PRId32 "\n", result);

    if (!check_mul(a, b, &result))
        printf("Overflow detected in multiplication\n");
    else
        printf("Multiplication result: %" PRId32 "\n", result);

    return 0;
}
