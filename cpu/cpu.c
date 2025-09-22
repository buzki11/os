/* cpu/cpu.c */
#include "cpu.h"
#include "../drivers/screen.h"
#include "../drivers/screen.h"
#include <stdint.h>

/* Basic cpuid wrapper */
void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;
    __asm__ __volatile__ (
        "cpuid"
        : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
        : "a"(leaf)
    );
    if (eax) *eax = a;
    if (ebx) *ebx = b;
    if (ecx) *ecx = c;
    if (edx) *edx = d;
}

/* Read highest CPUID leaf and vendor string */
void cpu_probe(void) {
    uint32_t eax, ebx, ecx, edx;
    cpuid(0, &eax, &ebx, &ecx, &edx);
    uint32_t max_leaf = eax;

    char vendor[13];
    ((uint32_t*)vendor)[0] = ebx;
    ((uint32_t*)vendor)[1] = edx;
    ((uint32_t*)vendor)[2] = ecx;
    vendor[12] = '\0';

    kprint("[cpu] CPUID max leaf = ");
    kprint_hex(max_leaf);
    kprint("\n");

    kprint("[cpu] Vendor: ");
    kprint(vendor);
    kprint("\n");

    if (max_leaf >= 1) {
        cpuid(1, &eax, &ebx, &ecx, &edx);
        uint32_t family = ((eax >> 8) & 0xf) + ((eax >> 20) & 0xff);
        uint32_t model  = ((eax >> 4) & 0xf) + (((eax >> 16) & 0xf) << 4);
        kprint("[cpu] Family: ");
        kprint_hex(family);
        kprint(" Model: ");
        kprint_hex(model);
        kprint("\n");

        kprint("[cpu] Features (EDX): ");
        kprint_hex(edx);
        kprint("\n");

        kprint("[cpu] Features (ECX): ");
        kprint_hex(ecx);
        kprint("\n");
    }
}

