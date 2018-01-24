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

typedef struct {
    int fd;
    void *send;
    void *recv;
} sudt_socket_internal_t;

sudt_socket_t* sudt_socket_create() {
    sudt_socket_internal_t *sock = malloc(sizeof(sudt_socket_internal_t));

    sock->fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( sock->fd<0 ) {
        return NULL;       
    }
    return (sudt_socket_t *)sock;
}
