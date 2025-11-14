Low Level Layer (wic64lib)
--------------------------

uint16_t wic_com(uint8_t com, uint16_t parastart, uint16_t paralength, uint16_t datastart, uint16_t datalength, uint16_t target)

Purpose: Core command exchange with the WiC64 module.

*** Parameters:

com → Command number (e.g., 1 = GET, 40 = POST).

parastart → Address of parameter string (URL).

paralength → Length of parameter string.

datastart → Address of data block (for POST).

datalength → Length of data block.

target → Memory address for response, or 0xFFFF for DMI mode.

Return: Number of bytes reported by the module.

*** Notes: Use this when you need full control over parameters and data.

uint8_t setbyte(uint8_t value)
Sends a byte to the WiC64 via CIA2 port B.

Waits until the module acknowledges.

uint8_t readbyte(void)
Reads a byte from the WiC64 via CIA2 port B.

Waits until data is available.

void wic_port_send_setup(void)
Configures CIA2 for sending data.

void wic_port_recv_setup(void)
Configures CIA2 for receiving data.

void wic_irq_clear(void)
Clears interrupt flags.

void wic_cli(void)
Re enables interrupts after communication.

uint8_t lowhighbyte(uint8_t lorh, uint16_t value)
Returns low or high byte of a 16 bit value.

lorh = 1 → low byte, lorh = 2 → high byte.

*** Memory helpers

uint8_t peek(uint16_t addr) → Read a byte from memory.

void poke(uint16_t addr, uint8_t v) → Write a byte to memory.

uint16_t deek(uint16_t addr) → Read a 16‑bit word from memory.

*** Mid Level Utilities (wic64utils)

void ascii_to_petscii(char* str)
Converts ASCII string to PETSCII (basic mapping: lowercase → uppercase).

--- Useful for URLs and parameters.

void petscii_to_ascii(char* str)
Converts PETSCII string back to ASCII (uppercase → lowercase).

uint16_t wic_copy_to_buffer(uint16_t source_addr, char* buffer, uint16_t bufsize)

Copies up to bufsize bytes from source_addr into buffer.

Returns number of bytes copied.

uint16_t wic_send_command(uint8_t com, const char* param, uint16_t target)
Convenience wrapper for wic_com.

Sends a command with a string parameter only (no data block).

*** Example:

wic_send_command(6, "", 0x0658);
enum WICError
Error codes for higher layers:

WIC_OK

WIC_TIMEOUT

WIC_INVALID_RESPONSE

WIC_BUFFER_OVERFLOW

*** High Level API (wic64api)

uint16_t wic_get_url(const char* url, char* buffer, uint16_t bufsize)
Fetches data from a URL into buffer.

Uses DMI mode (target = 0xFFFF).

Returns number of bytes reported by the module.

uint16_t wic_post_data(const char* url, const uint8_t* data, uint16_t length)
Sends data to a server via POST.

URL is converted to PETSCII internally.

Returns number of bytes reported by the module.

uint16_t wic_load_file(const char* url, uint16_t target_addr)
Loads a PRG file from a URL directly into memory at target_addr.

*** Example:

wic_load_file("http://example.com/file.prg", 0x0801);

--- Examples

GET
char buffer[256];
uint16_t len = wic_get_url("http://example.com", buffer, sizeof(buffer));

POST
wic_post_data("http://example.com/post", (const uint8_t*)"Hello", 5);

Load PRG
wic_load_file("http://example.com/file.prg", 0x0801);

*** Notes: Always include wic64lib.h, wic64utils.h, and wic64api.h in your program.

PETSCII conversion is minimal; extend as needed for full URL support.

For POST with data, use wic_post_data (not wic_send_command).
