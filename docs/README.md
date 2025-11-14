# WiC64 SDK for cc65
--------------------

The **WiC64 SDK** provides a clean C interface to the [WiC64](https://wic64.de) module, enabling Commodore 64 programs to access modern networking features such as HTTP GET, POST, and file loading directly from the web.

This SDK is layered into:
- **Low-level**: hardware routines and raw command exchange (`wic_com`)
- **Mid-level**: utilities for string conversion, buffer management, error codes
- **High-level API**: developer-friendly functions (`wic_get_url`, `wic_post_data`, `wic_load_file`)

---

## 🚀 Quick Start

### Requirements
- [cc65](https://cc65.github.io/) compiler suite
- Commodore 64 emulator (e.g., VICE) or real hardware with WiC64 module

### Build
Clone or copy the SDK files into your project folder and run:

```bash
cl65 -t c64 wic64lib.c win64lib-asm.s wic64utils.c wic64api.c demo.c -o demo.prg

1. **API Reference**: Detailed docs for each function (parameters, return values, examples).  
2. **Troubleshooting Guide**: Expanded section with common cc65 quirks and fixes.  
3. **Examples Folder**: Separate demo programs (`get_demo.c`, `post_demo.c`, `load_demo.c`).  
4. **Library Build**: Package low-level code into `wic64lib.lib` for easier linking.  

*** Project Structure

wic64lib.[ch] + win64lib-asm.s → low-level routines

wic64utils.[ch] → mid-level utilities

wic64api.[ch] → high-level API

examples/ → demo programs

docs/ → API reference and troubleshooting

*** API Layers

Low-level: wic_com, setbyte, readbyte

Mid-level: ascii_to_petscii, wic_send_command, wic_copy_to_buffer

High-level: wic_get_url, wic_post_data, wic_load_file

*** EXAMPLE Get Request

#include "wic64api.h"
#include <conio.h>

void main(void) {
    char buffer[256];
    uint16_t len;

    clrscr();
    cprintf("WiC64 GET demo\n");

    len = wic_get_url("http://example.com", buffer, sizeof(buffer));
    cprintf("Received %u bytes\n", len);
}

*** EXAMPLE Post Request

len = wic_post_data("http://example.com/post", (const uint8_t*)"Hello WiC64", 11);
cprintf("POST returned %u bytes\n", len);

*** EXAMPLE Load PRG

wic_load_file("http://example.com/file.prg", 0x0801);
cprintf("File loaded at $0801\n");

