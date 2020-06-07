#pragma once

typedef struct aes_ctx__ {
    uint8_t roundkey[176];
    uint8_t state[4][4];
} aes_ctx;

void key_expansion(aes_ctx * restrict ctx, const uint8_t key[static restrict 16]);
void subbytes(aes_ctx * restrict ctx);
void shift_rows(aes_ctx * restrict ctx);
void mix_columns(aes_ctx * restrict ctx);
void add_roundkey(aes_ctx * restrict ctx, size_t round_num);
void self_aes_encrypt(uint8_t out[static restrict 16],
                      const uint8_t plain[static restrict 16],
                      const uint8_t key[static restrict 16]);
void self_aes_test_ctx_gen(aes_ctx * restrict ctx, const uint8_t key[static restrict 16]);