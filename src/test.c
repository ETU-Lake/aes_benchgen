#include <stdio.h>

#include <openssl/crypto.h>

#include "constants.h"
#include "self_aes.h"
#include "openssl_aes.h"
#include "test.h"

/*
 * key: "expand 32-byte k"
 * ascii in little endian
 * taken from the ChaCha20 constant.
 */
static const uint8_t test_key [16] = {
    0x65, 0x78, 0x70, 0x61,
    0x6E, 0x64, 0x20, 0x33,
    0x32, 0x2D, 0x62, 0x79,
    0x74, 0x65, 0x20, 0x6B,
};

/*
 * plain: "qwertyuiopasdfgh"
 * ascii in little endian
 */
static const uint8_t test_plain [16] = {
    0x71, 0x77, 0x65, 0x72,
    0x74, 0x79, 0x75, 0x69,
    0x6F, 0x70, 0x61, 0x73,
    0x64, 0x66, 0x67, 0x68,
};

static void test_internal(void) {
    uint8_t openssl_cipher[16], self_cipher[16], tmp[16];
    printf("Testing internal consistency...\n");
    TEST(openssl_aes_encrypt(openssl_cipher, test_plain, test_key), 1, "encryptiion via OpenSSL");
    TEST(openssl_aes_decrypt(tmp, openssl_cipher, test_key), 1, "decryption via OpenSSL");
    TEST(CRYPTO_memcmp(tmp, test_plain, 16), 0, "decryption result consistency");
    printf(" * Encrypting via self AES...\n");
    self_aes_encrypt(self_cipher, test_plain, test_key);
    TEST(CRYPTO_memcmp(openssl_cipher, self_cipher, 16), 0, "ciphertext result consistency");
    printf("Internal consistency is OK.\n");
}

static void test_keyexpand(void) {
    aes_ctx ctx;
    size_t i;
    printf("Generating Key Expansion test vector:\n");
    key_expansion(&ctx, test_key);
    for (i = 0; i < 127; i++) {
        printf("0x%X ", (ctx.roundkey)[i]);
        if (i % 16 == 15) {
            printf("\n");
        }
    }
    printf("\n");
}

static void test_addroundkey(aes_ctx * restrict ctx) {
    printf("Generating AddRoundKey test vector: (round = 5)\n");
    add_roundkey(ctx, 5);
    PRINT_STATE(ctx);
}

static void test_subbytes(aes_ctx * restrict ctx) {
    printf("Generating SubBytes test vector:\n");
    subbytes(ctx);
    PRINT_STATE(ctx);
}

static void test_shiftrows(aes_ctx * restrict ctx) {
    printf("Generating ShiftRows test vector:\n");
    shift_rows(ctx);
    PRINT_STATE(ctx);
}

static void test_mixcolumns(aes_ctx * restrict ctx) {
    printf("Generating MixColumns test vector:\n");
    mix_columns(ctx);
    PRINT_STATE(ctx);
}

static void test_cipher(void) {
    size_t i;
    uint8_t cipher[16];

    printf("Generating test cipher vector\n");
    self_aes_encrypt(cipher, test_plain, test_key);
    for (i = 0; i < 16; i++) {
        printf("0x%X ", cipher[i]);
    }
    printf("\n");
}


void test_eval(uint8_t opts) {
    size_t i;
    aes_ctx ctx;

    printf("Test Key (\"expand 32-byte k\" in ASCII, little endian):\n");
    for (i = 0; i < 16; i++) {
        printf("0x%X ", test_key[i]);
    }
    printf("\n");

    printf("Test Plaintext/State (\"qwertyuiopasdfgh\" in ASCII, little endian):\n");
    for (i = 0; i < 16; i++) {
        printf("0x%X ", test_plain[i]);
    }
    printf("\n");

    if (opts & INTERNAL) {
        test_internal();
    }

    if (opts & KEYEXPAND) {
        test_keyexpand();
    }

    if (opts & ADDROUNDKEY) {
        self_aes_test_ctx_gen(&ctx, test_key);
        test_addroundkey(&ctx);
    }

    if (opts & SUBBYTES) {
        self_aes_test_ctx_gen(&ctx, test_key);
        test_subbytes(&ctx);
    }

    if (opts & SHIFTROWS) {
        self_aes_test_ctx_gen(&ctx, test_key);
        test_shiftrows(&ctx);
    }

    if (opts & MIXCOLUMNS) {
        self_aes_test_ctx_gen(&ctx, test_key);
        test_mixcolumns(&ctx);
    }

    if (opts & CIPHER) {
        test_cipher();
    }
}
