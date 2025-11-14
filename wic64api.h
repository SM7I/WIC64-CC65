#ifndef WIC64API_H
#define WIC64API_H

#include <stdint.h>
#include "wic64utils.h"

/* Fetch data from a URL into buffer (DMI mode), returns bytes reported by module.
   Note: URL string is converted to PETSCII internally. */
uint16_t wic_get_url(const char* url, char* buffer, uint16_t bufsize);

/* POST data to URL, returns bytes reported by module (DMI mode).
   Note: URL string converted to PETSCII internally. */
uint16_t wic_post_data(const char* url, const uint8_t* data, uint16_t length);

/* Load a PRG from URL into target_addr (direct write mode). Returns sum. */
uint16_t wic_load_file(const char* url, uint16_t target_addr);

#endif

