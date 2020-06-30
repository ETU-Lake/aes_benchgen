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

#define PRINT_STATE(ctx)                             \
    do {                                             \
        size_t i,j;                                  \
        for (i = 0; i < 4; i++) {                    \
            for (j = 0; j < 4; j++) {                \
                printf("0x%X ", (ctx->state)[i][j]); \
            }                                        \
            printf("\n");                            \
        }                                            \
    } while(0)

void test_eval(uint8_t opts);
