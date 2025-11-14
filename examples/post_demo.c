#include "wic64api.h"
#include <conio.h>
#include <stdio.h>

void main(void) {
    uint16_t len;

    clrscr();
    cprintf("WiC64 POST demo\n");

    len = wic_post_data("http://example.com/post", (const uint8_t*)"Hello WiC64", 11);

    cprintf("POST returned %u bytes\n", len);

    while (1) { }
}

