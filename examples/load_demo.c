#include "wic64api.h"
#include <conio.h>
#include <stdio.h>

void main(void) {
    uint16_t len;

    clrscr();
    cprintf("WiC64 LOAD demo\n");

    /* Load PRG directly into BASIC start ($0801) */
    len = wic_load_file("http://example.com/file.prg", 0x0801);

    cprintf("File loaded, return value %u\n", len);

    while (1) { }
}

