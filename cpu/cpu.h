/* cpu/cpu.h */
#ifndef CPU_H
#define CPU_H

#include <stdint.h>

void cpu_probe(void); /* prints vendor, model, features */
void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

#endif

