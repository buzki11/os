/* kernel/probe.c */
#include "probe.h"
#include "../cpu/cpu.h"
#include "../drivers/pci.h"
#include "../drivers/screen.h"

void hw_probe_all(void) {
    kprint("=== Hardware probe starting ===\n");
    cpu_probe();
    pci_scan_bus();
    kprint("=== Hardware probe complete ===\n");
}

