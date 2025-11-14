#include "wic64api.h"
#include "wic64lib.h"
#include "wic64utils.h"
#include <string.h>

/* Global static buffer to avoid too many locals */
static char temp[256];

uint16_t wic_get_url(const char* url, char* buffer, uint16_t bufsize) {
    uint16_t sum, url_len, to_copy;

    /* Copy URL into static buffer and convert */
    url_len = (uint16_t)strlen(url);
    if (url_len >= sizeof(temp)) url_len = (uint16_t)(sizeof(temp) - 1);
    memcpy(temp, url, url_len);
    temp[url_len] = '\0';
    ascii_to_petscii(temp);

    /* Ask module to DMI */
    sum = wic_com(1, (uint16_t)temp, (uint16_t)strlen(temp), 0, 0, (uint16_t)0xFFFF);

    /* Cap copy by bufsize */
    to_copy = sum;
    if (to_copy > bufsize) to_copy = bufsize;

    /* Copy from buffer’s address (simplified assumption) */
    wic_copy_to_buffer((uint16_t)buffer, buffer, to_copy);

    return sum;
}

uint16_t wic_post_data(const char* url, const uint8_t* data, uint16_t length) {
    uint16_t url_len;

    url_len = (uint16_t)strlen(url);
    if (url_len >= sizeof(temp)) url_len = (uint16_t)(sizeof(temp) - 1);
    memcpy(temp, url, url_len);
    temp[url_len] = '\0';
    ascii_to_petscii(temp);

    return wic_com(40,
                   (uint16_t)temp, (uint16_t)strlen(temp),
                   (uint16_t)data, length,
                   (uint16_t)0xFFFF);
}

uint16_t wic_load_file(const char* url, uint16_t target_addr) {
    uint16_t url_len;

    url_len = (uint16_t)strlen(url);
    if (url_len >= sizeof(temp)) url_len = (uint16_t)(sizeof(temp) - 1);
    memcpy(temp, url, url_len);
    temp[url_len] = '\0';
    ascii_to_petscii(temp);

    return wic_com(1, (uint16_t)temp, (uint16_t)strlen(temp), 0, 0, target_addr);
}

