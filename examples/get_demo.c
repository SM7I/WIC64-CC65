#include "wic64api.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>

void main(void) {
    char buffer[256];
    uint16_t len;

    clrscr();
    cprintf("WiC64 GET demo\n");

    memset(buffer, 0, sizeof(buffer));
    len = wic_get_url("http://example.com", buffer, sizeof(buffer));

    cprintf("Received %u bytes\n", len);
    cprintf("\nData:\n%s\n", buffer);

    while (1) { }
}

