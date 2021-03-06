/**
 * @file sudt.h
 * @brief 
 * @author supergui@live.cn
 * @version 1.0.0
 * @date 2018-01-24
 */
#ifndef SUDT_20180124_H
#define SUDT_20180124_H

#include <unistd.h>
#include <sys/socket.h>

typedef struct {
    char data[1];
} sudt_socket_t;

sudt_socket_t* sudt_socket_create();

int sudt_socket_close(sudt_socket_t *sock);

int sudt_socket_bind(sudt_socket_t *sock, const struct sockaddr *addr, socklen_t addrlen);

int sudt_socket_listen(sudt_socket_t *sock, int backlog);

int sudt_socket_accept(sudt_socket_t *sock, struct sockaddr *addr, socklen_t *addrlen);

int sudt_socket_connect(sudt_socket_t *sock, const struct sockaddr *addr, socklen_t addrlen);

ssize_t sudt_socket_send(sudt_socket_t *sock, const void *buf, size_t buflen, int flags);

ssize_t sudt_socket_recv(sudt_socket_t *sock, void *buf, size_t buflen, int flags);


#endif
