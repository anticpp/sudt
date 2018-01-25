/**
 * @file pack->c
 * @brief 
 * @author supergui@live.cn
 * @version 1.0.0
 * @date 2018-01-25
 */
#include "sudt_pack.h"
#include "sudt_protocol.h"

size_t sudt_pack_encode_need_size(const sudt_pack_t *pack) {
    return sizeof(pack->seq) +
            sizeof(pack->ack) +
            sizeof(pack->flags) +
            sizeof(pack->winsize) +
            sizeof(pack->checksum) +
            sizeof(pack->datalen) +
            pack->datalen;
}

size_t sudt_pack_encode(const sudt_pack_t *pack, void *buf, size_t buflen) {
    size_t s = 0;

    s += sudt_protocol_encode_uint32(pack->seq, buf+s, buflen-s);
    s += sudt_protocol_encode_uint32(pack->ack, buf+s, buflen-s);
    s += sudt_protocol_encode_uint8(pack->flags, buf+s, buflen-s);
    s += sudt_protocol_encode_uint16(pack->winsize, buf+s, buflen-s);
    s += sudt_protocol_encode_uint16(pack->checksum, buf+s, buflen-s);
    s += sudt_protocol_encode_uint32(pack->datalen, buf+s, buflen-s);
    s += sudt_protocol_encode_data(pack->data, pack->datalen, buf+s, buflen-s);
    return s;
}

size_t sudt_pack_decode(const void *buf, size_t buflen, sudt_pack_t *pack) {
    size_t s = 0;

    s += sudt_protocol_decode_uint32(buf+s, buflen-s, &(pack->seq));
    s += sudt_protocol_decode_uint32(buf+s, buflen-s, &(pack->ack));
    s += sudt_protocol_decode_uint8(buf+s, buflen-s, &(pack->flags));
    s += sudt_protocol_decode_uint16(buf+s, buflen-s, &(pack->winsize));
    s += sudt_protocol_decode_uint16(buf+s, buflen-s, &(pack->checksum));
    s += sudt_protocol_decode_uint32(buf+s, buflen-s, &(pack->datalen));
    s += sudt_protocol_decode_data(buf+s, buflen-s, pack->data, pack->datalen);
    return s;
}

