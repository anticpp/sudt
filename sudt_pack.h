/**
 * @file pack.h
 * @brief 
 * @author supergui@live.cn
 * @version 1.0.0
 * @date 2018-01-25
 */
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SUDT_PACK_FLAG_FIN (0x01)
#define SUDT_PACK_FLAG_SYNC (0x01<<1)
#define SUDT_PACK_FLAG_RST (0x01<<2)
#define SUDT_PACK_FLAG_PUSH (0x01<<3)
#define SUDT_PACK_FLAG_ACK (0x01<<4)

#define SUDT_PACK_DATA_MEM_TYPE_DEFAULT 0x00
#define SUDT_PACK_DATA_MEM_TYPE_STACK 0x01
#define SUDT_PACK_DATA_MEM_TYPE_HEAP 0x02

typedef struct {
    uint32_t seq;
    uint32_t ack;
    uint8_t flags;
    uint16_t winsize;
    uint16_t checksum;
    uint32_t datalen;
    void *data;
    
    // Memory type
    int data_mem_type;
    
    // Remote socket address which received
    struct sockaddr addr;
    socklen_t addrlen;
} sudt_pack_t;

void sudt_pack_reset(sudt_pack_t *pack);

size_t sudt_pack_encode_need_size(const sudt_pack_t *pack);

size_t sudt_pack_encode(const sudt_pack_t *pack, void *buf, size_t buflen);

size_t sudt_pack_decode(const void *buf, size_t buflen, sudt_pack_t *pack);
