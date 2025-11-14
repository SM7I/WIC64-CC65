#include "wic64utils.h"
#include "wic64lib.h"
#include <string.h>

/* Simple ASCII -> PETSCII tweak similar to your low-level transformation:
   - a..z (97..122) -> A..Z (65..90) by -32
   - Leave other characters as-is for now. */
void ascii_to_petscii(char* str) {
    char* p = str;
    while (*p) {
        unsigned char c = (unsigned char)*p;
        if (c >= 97 && c <= 122) {
            c = (unsigned char)(c - 32);
        }
        *p = (char)c;
        ++p;
    }
}

/* Reverse of above: A..Z -> a..z */
void petscii_to_ascii(char* str) {
    char* p = str;
    while (*p) {
        unsigned char c = (unsigned char)*p;
        if (c >= 65 && c <= 90) {
            c = (unsigned char)(c + 32);
        }
        *p = (char)c;
        ++p;
    }
}

/* Copy bytes from source_addr into buffer safely */
uint16_t wic_copy_to_buffer(uint16_t source_addr, char* buffer, uint16_t bufsize) {
    uint16_t i;
    for (i = 0; i < bufsize; ++i) {
        buffer[i] = (char)peek((uint16_t)(source_addr + i));
    }
    return bufsize;
}

/* Send a command with only a string parameter; caller decides target.
   Returns the sum returned by wic_com. */
uint16_t wic_send_command(uint8_t com, const char* param, uint16_t target) {
    uint16_t parastart = (uint16_t)param;
    uint16_t paralength = (uint16_t)strlen(param);
    return wic_com(com, parastart, paralength, 0, 0, target);
}

