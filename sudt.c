/**
 * @file sudt.c
 * @brief 
 * @author supergui@live.cn
 * @version 1.0.0
 * @date 2018-01-24
 */
#include "sudt.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "sudt_pack.h"

#define SUDT_SOCKET_STATE_CLOSED 0x01
#define SUDT_SOCKET_STATE_LISTEN 0x02
#define SUDT_SOCKET_STATE_ESTABLISHED 0x03

typedef struct {
    int fd;
    int state;

    socklen_t local_addrlen, remote_addrlen;
    struct sockaddr local_addr, remote_addr; } sudt_socket_internal_t;

void sudt_socket_pack_read(sudt_socket_internal_t *sock, sudt_pack_t *pack) {
    char buf[2048];
    pack->addrlen = sizeof(pack->addr);

    ssize_t s = 0;
    for(;;) {
        s = recvfrom(sock->fd, buf, sizeof(buf), 0, &pack->addr, &(pack->addrlen));
        if(s<0) {
            continue;
        }

        sudt_pack_decode(buf, s, pack);

        // TODO
        // Checksum
        
        break;
    }
    
    return;
}

void sudt_socket_pack_write(sudt_socket_internal_t *sock, const sudt_pack_t *pack){
    size_t s = sudt_pack_encode_need_size(pack);
    char *buf = malloc(s);

    size_t s1 = sudt_pack_encode(pack, buf, sizeof(buf));
    for(;;) {
        if( sendto(sock->fd, buf, s1, 0, &(sock->remote_addr), sizeof(sock->remote_addr)) <0 ){
            continue;
        }
        break;
    }
    return;
}

sudt_socket_t* sudt_socket_create() {
    sudt_socket_internal_t *sock = malloc(sizeof(sudt_socket_internal_t));
    sock->fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( sock->fd<0 ) {
        return NULL;       
    }
    sock->state = SUDT_SOCKET_STATE_CLOSED;
    sock->local_addrlen = sizeof(sock->local_addr);
    sock->remote_addrlen = sizeof(sock->remote_addr);
    return (sudt_socket_t *)sock;
}

int sudt_socket_connect(sudt_socket_t *sock, const struct sockaddr *addr, socklen_t addrlen) {
    sudt_socket_internal_t *isock = (sudt_socket_internal_t *)sock;
    sudt_pack_t sync, ack;

    // Connect with socket type SOCK_DGRAM, which datagrams are sent by default address,
    // and only address from which are received.
    if( connect(isock->fd, addr, addrlen)<0 ) {
        return -1;
    }

    // Get socket local address and remote address
    getsockname(isock->fd, &(isock->local_addr), &(isock->local_addrlen));

    memcpy(&(isock->remote_addr), addr, addrlen);
    isock->remote_addrlen = addrlen;

    // SYNC
    sync.flags = SUDT_PACK_FLAG_SYNC; 
    sudt_socket_pack_write(isock, &sync);

    sudt_socket_pack_read(isock, &ack);
    if( !(ack.flags&SUDT_PACK_FLAG_ACK) ) {
        return -1;
    }

    return 0;
}

int sudt_socket_accept(sudt_socket_t *sock, struct sockaddr *addr, socklen_t *addr_len) {
    return 0;
}
