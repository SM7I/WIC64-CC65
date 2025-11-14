#ifndef WIC64UTILS_H
#define WIC64UTILS_H

#include <stdint.h>

/* Error codes for higher layers */
typedef enum {
    WIC_OK = 0,
    WIC_TIMEOUT,
    WIC_INVALID_RESPONSE,
    WIC_BUFFER_OVERFLOW
} WICError;

/* Convert ASCII string to PETSCII (basic mapping for lowercase -> uppercase) */
void ascii_to_petscii(char* str);

/* Convert PETSCII string back to ASCII (basic mapping for uppercase -> lowercase) */
void petscii_to_ascii(char* str);

/* Copy up to bufsize bytes from a source address into buffer. Returns bytes copied. */
uint16_t wic_copy_to_buffer(uint16_t source_addr, char* buffer, uint16_t bufsize);

/* Convenience: send a command with only a string parameter (no data), target direct memory */
uint16_t wic_send_command(uint8_t com, const char* param, uint16_t target);

#endif

