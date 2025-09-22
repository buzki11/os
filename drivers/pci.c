/* drivers/pci.c */
#include "pci.h"
#include "../drivers/screen.h"
#include "../drivers/screen.h"
#include "../cpu/ports.h" /* for outb/inb/outl/inl functions */
#include "../cpu/io32.h"
#include <stdint.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

/* Build config address */
static uint32_t pci_address(uint8_t bus, uint8_t device, uint8_t func, uint8_t offset) {
    return (uint32_t)(
        (1U << 31) |
        ((uint32_t)bus << 16) |
        ((uint32_t)device << 11) |
        ((uint32_t)func << 8) |
        (offset & 0xFC)
    );
}

static uint32_t pci_config_read32(uint8_t bus, uint8_t device, uint8_t func, uint8_t offset) {
    uint32_t addr = pci_address(bus, device, func, offset);
    outl(PCI_CONFIG_ADDRESS, addr);
    return inl(PCI_CONFIG_DATA);
}

void pci_scan_bus(void) {
    kprint("[pci] Scanning PCI bus...\n");
    for (uint16_t bus = 0; bus < 256; ++bus) {
        for (uint8_t dev = 0; dev < 32; ++dev) {
            for (uint8_t func = 0; func < 8; ++func) {
                uint32_t v = pci_config_read32(bus, dev, func, 0);
                uint16_t vendor = v & 0xFFFF;
                uint16_t device = (v >> 16) & 0xFFFF;
                if (vendor == 0xFFFF) {
                    /* no device */
                    if (func == 0) break; /* if function 0 isn't present, no more functions on this dev */
                    continue;
                }
                kprint("[pci] found device - bus:");
                kprint_hex(bus);
                kprint(" dev:");
                kprint_hex(dev);
                kprint(" func:");
                kprint_hex(func);
                kprint(" vendor:0x");
                kprint_hex(vendor);
                kprint(" device:0x");
                kprint_hex(device);
                kprint("\n");
            }
        }
    }
    kprint("[pci] done scanning.\n");
}

