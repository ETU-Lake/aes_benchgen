#include <stdint.h>
#include <openssl/evp.h>

/*
 * Operations are on only one block so ECB mode is with the input length of
 * one block should be good enough to not touch AES_CTX itself.
 */

int openssl_aes_encrypt(uint8_t out[static restrict 16],
                        const uint8_t plain[static restrict 16],
                        const uint8_t key[static restrict 16]) {
    int out_len = -1;
    EVP_CIPHER_CTX *ctx = NULL;

    if (!plain || !key) {
        goto FAULT;
    }

    ctx = EVP_CIPHER_CTX_new();
    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL) <= 0) {
        goto FAULT;
    }

    if (EVP_CIPHER_CTX_set_padding(ctx, 0) <= 0) {
        goto FAULT;
    }

    if (EVP_EncryptUpdate(ctx, out, &out_len, plain, 16) <= 0) {
        goto FAULT;
    }

    if (out_len != 16) {
        goto FAULT;
    }

    if (EVP_EncryptFinal_ex(ctx, out + out_len, &out_len) <= 0) {
        goto FAULT;
    }

    EVP_CIPHER_CTX_free(ctx);
    return 1;

FAULT:
    OPENSSL_cleanse(out, 16);
    if (ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }
    return 0;
}

int openssl_aes_decrypt(uint8_t out[static restrict 16],
                        const uint8_t cipher[static restrict 16],
                        const uint8_t key[static restrict 16]) {
    int out_len = -1;
    EVP_CIPHER_CTX *ctx = NULL;

    if (!cipher || !key ) {
        goto FAULT;
    }

    ctx = EVP_CIPHER_CTX_new();
    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL) <= 0) {
        goto FAULT;
    }

    if (EVP_CIPHER_CTX_set_padding(ctx, 0) <= 0) {
        goto FAULT;
    }

    if (EVP_DecryptUpdate(ctx, out, &out_len, cipher, 16) <= 0) {
        goto FAULT;
    }

    if (out_len != 16) {
        goto FAULT;
    }

    if (EVP_DecryptFinal_ex(ctx, out + out_len, &out_len) <= 0) {
        goto FAULT;
    }

    EVP_CIPHER_CTX_free(ctx);
    return 1;

FAULT:
    OPENSSL_cleanse(out, 16);
    if (ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }
    return 0;
}
