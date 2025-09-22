#ifndef IO32_H
#define IO32_H
#include <stdint.h>
uint32_t inl(uint16_t port);
void outl(uint16_t port, uint32_t val);
#endif

