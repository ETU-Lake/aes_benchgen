#pragma once

#include <stdint.h>

int openssl_aes_encrypt(uint8_t out[static restrict 16],
                        const uint8_t plain[static restrict 16],
                        const uint8_t key[static restrict 16]);
int openssl_aes_decrypt(uint8_t out[static restrict 16],
                        const uint8_t cipher[static restrict 16],
                        const uint8_t key[static restrict 16]);
