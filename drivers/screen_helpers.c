#include "screen.h"

/* Print a 32-bit value in hexadecimal */
void kprint_hex(uint32_t val) {
    char hex[9];
    const char *digits = "0123456789ABCDEF";
    for (int i = 0; i < 8; i++) {
        hex[7 - i] = digits[val & 0xF];
        val >>= 4;
    }
    hex[8] = '\0';
    kprint(hex);  // Uses your existing kprint function
}

