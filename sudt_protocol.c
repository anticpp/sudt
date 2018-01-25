/**
 * @file protocol.c
 * @brief 
 * @author supergui@live.cn
 * @version 1.0.0
 * @date 2018-01-25
 */

#include "sudt_protocol.h"
#include <string.h>

size_t sudt_protocol_encode_uint8(uint8_t i, void *buf, size_t buflen) {
    if(buflen<sizeof(uint8_t)) {
        return 0;
    }

    char *p = (char *)buf;
    p[0] = (i & 0xff);
    return sizeof(uint8_t);
}

size_t sudt_protocol_encode_uint16(uint16_t i, void *buf, size_t buflen) {
    if(buflen<sizeof(uint16_t)) {
        return 0;
    }

    char *p = (char *)buf;
    p[0] = (i>>8) & 0xff;
    p[1] = i & 0xff;
    return sizeof(uint16_t);
}

size_t sudt_protocol_encode_uint32(uint32_t i, void *buf, size_t buflen) {
    if(buflen<sizeof(uint32_t)) {
        return 0;
    }

    char *p = (char *)buf;
    p[0] = (i>>24) & 0xff;
    p[1] = (i>>16) & 0xff;
    p[2] = (i>>8) & 0xff;
    p[3] = i & 0xff;
    return sizeof(uint32_t);
}

size_t sudt_protocol_encode_data(const void *data, size_t datalen, void *buf, size_t buflen) {
    if(buflen<datalen) {
        return 0;
    }

    memcpy(buf, data, datalen);
    return datalen;
}

size_t sudt_protocol_decode_uint8(const void *buf, size_t buflen, uint8_t *pi) {
    if(buflen<sizeof(uint8_t)) {
        return 0;
    }

    const char *p = (const char *)buf;
    *pi = (p[0] & 0xff);
    return sizeof(uint8_t);
}

size_t sudt_protocol_decode_uint16(const void *buf, size_t buflen, uint16_t *pi) {
    if(buflen<sizeof(uint16_t)) {
        return 0;
    }

    const char *p = (const char *)buf;
    *pi = ( (p[0]<<8) & 0xff00 ) +
            ( p[1] &  0xff );
    return sizeof(uint16_t);
}

size_t sudt_protocol_decode_uint32(const void *buf, size_t buflen, uint32_t *pi) {
    if(buflen<sizeof(uint32_t)) {
        return 0;
    }

    const char *p = (const char *)buf;
    *pi = ( (p[0]<<24) & 0xff000000 ) +
          ( (p[1]<<16) & 0xff0000 ) +
          ( (p[2]<<8) & 0xff00 ) +
            ( p[3] &  0xff );
    return sizeof(uint32_t);
}

size_t sudt_protocol_decode_data(const void *buf, size_t buflen, void *data, size_t *datalen) {
    if(buflen<datalen) {
        return 0;
    }

    memcpy(data, buf, datalen);
    return datalen;
}
