#pragma once

#include <stdint.h>

#define Nb 4
#define Nk 4
#define Nr 10
#define getSBoxValue(num) (sbox[(num)])

typedef uint8_t state_t[4][4];

void KeyExpansion(uint8_t * restrict RoundKey, const uint8_t * restrict Key);
void AddRoundKey(uint8_t round, state_t* state, const uint8_t* RoundKey);
void SubBytes(state_t* state);
void ShiftRows(state_t* state);
uint8_t xtime(uint8_t x);
void MixColumns(state_t* state);
uint8_t Multiply(uint8_t x, uint8_t y);
void Cipher(state_t* state, const uint8_t* RoundKey);
