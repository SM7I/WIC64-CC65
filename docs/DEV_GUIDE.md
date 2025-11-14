WiC64 SDK Developer Guide
-------------------------

1. Install prerequisites

cc65 toolchain

VICE emulator (or real C64 with WiC64 module)

Your SDK folder containing:

wic64lib.lib + headers (wic64lib.h, wic64utils.h, wic64api.h)

Example programs

2. Create a new project
-----------------------

Make a folder mywicapp/ and copy in:

wic64lib.lib

wic64lib.h, wic64utils.h, wic64api.h

Create a new file: main.c:

#include "wic64api.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>

void main(void) {
    char buffer[256];
    uint16_t len;

    clrscr();
    cprintf("My first WiC64 app!\n");

    /* Fetch a web page */
    memset(buffer, 0, sizeof(buffer));
    len = wic_get_url("http://example.com", buffer, sizeof(buffer));

    cprintf("Received %u bytes\n", len);
    cprintf("\nData:\n%s\n", buffer);

    while (1) { }
}

3. Build the program
--------------------

From your project folder:

bash
cl65 -t c64 main.c wic64utils.c wic64api.c wic64lib.lib -o mywicapp.prg

This links against the static library and produces mywicapp.prg.

4. Run in VICE
--------------

Start VICE (x64sc).

Attach your WiC64 module (or enable networking emulation if supported).

Load the PRG:

LOAD"MYWICAPP.PRG",8,1
RUN

You should see:

My first WiC64 app!
Received XXX bytes
Data:
<page content>

5. Extend your app
------------------

POST data:

wic_post_data("http://example.com/post", (const uint8_t*)"Hello WiC64", 11);

Load PRG:

wic_load_file("http://example.com/game.prg", 0x0801);

6. Debugging
------------

If you see hangs, check CIA2 registers in VICE monitor:

$DD01 (PRB) → data bytes

$DD0D (ICR) → interrupt flags

Use ascii_to_petscii() if URLs look corrupted.

7. Best practices
-----------------

Keep URLs under 255 chars (fits static buffer).

Always check return values (len) before using data.

Use wic_send_command() for simple commands with no payload.

Use wic_post_data() for POSTs with payloads.
