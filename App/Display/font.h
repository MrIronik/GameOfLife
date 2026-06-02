#pragma once
#include <stdint.h>

#define FONT_WIDTH  5
#define FONT_HEIGHT 7

typedef struct
{
    char c;
    uint8_t data[FONT_HEIGHT]; // 5-bit wide bitmap per row
} font_char_t;

// tylko znaki których potrzebujesz
static const font_char_t font[] =
{
    {'G', {
        0b01110,
        0b10000,
        0b10111,
        0b10001,
        0b10001,
        0b10001,
        0b01110
    }},

    {'A', {
        0b01110,
        0b10001,
        0b10001,
        0b11111,
        0b10001,
        0b10001,
        0b10001
    }},

    {'M', {
        0b10001,
        0b11011,
        0b10101,
        0b10001,
        0b10001,
        0b10001,
        0b10001
    }},

    {'E', {
        0b11111,
        0b10000,
        0b11110,
        0b10000,
        0b10000,
        0b10000,
        0b11111
    }},

    {'O', {
        0b01110,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b01110
    }},

    {'F', {
        0b11111,
        0b10000,
        0b11110,
        0b10000,
        0b10000,
        0b10000,
        0b10000
    }},

    {'L', {
        0b10000,
        0b10000,
        0b10000,
        0b10000,
        0b10000,
        0b10000,
        0b11111
    }},

    {'I', {
        0b11111,
        0b00100,
        0b00100,
        0b00100,
        0b00100,
        0b00100,
        0b11111
    }},
};