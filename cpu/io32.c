/* in cpu/ports.c add these or a new file cpu/io32.c */
#include <stdint.h>

uint32_t inl(uint16_t port) {
    uint32_t ret;
    __asm__ __volatile__ ("inl %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void outl(uint16_t port, uint32_t val) {
    __asm__ __volatile__ ("outl %0, %1" : : "a"(val), "d"(port));
}

