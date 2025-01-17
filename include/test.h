#pragma once

#define TEST(func, cond, msg)           \
    do {                                \
        printf(" * Testing %s: ", msg); \
        if (func != cond) {             \
            printf("FAIL\n");           \
            return;                     \
        }                               \
        printf("OK\n");                 \
    } while(0)

/*
 * [j][i] is due to state being indexed as [column][row]
 * However we want to print row by row.
 */
#define PRINT_STATE(ctx)                             \
    do {                                             \
        size_t i, j;                                 \
        for (i = 0; i < 4; i++) {                    \
            for (j = 0; j < 4; j++) {                \
                printf("0x%X ", (ctx->state)[j][i]); \
            }                                        \
            printf("\n");                            \
        }                                            \
    } while(0)

void test_eval(uint8_t opts);
