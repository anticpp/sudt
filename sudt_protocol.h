/**
 * @file protocol.h
 * @brief 
 * @author supergui@live.cn
 * @version 1.0.0
 * @date 2018-01-25
 */
#include <stdio.h>
#include <stdint.h>

size_t sudt_protocol_encode_uint8(uint8_t i, void *buf, size_t buflen);

size_t sudt_protocol_encode_uint16(uint16_t i, void *buf, size_t buflen);

size_t sudt_protocol_encode_uint32(uint32_t i, void *buf, size_t buflen);

size_t sudt_protocol_encode_data(const void *data, size_t datalen, void *buf, size_t buflen);

size_t sudt_protocol_decode_uint8(const void *buf, size_t buflen, uint8_t *pi);

size_t sudt_protocol_decode_uint16(const void *buf, size_t buflen, uint16_t *pi);

size_t sudt_protocol_decode_uint32(const void *buf, size_t buflen, uint32_t *pi);

size_t sudt_protocol_decode_data(const void *buf, size_t buflen, void *data, size_t datalen);
