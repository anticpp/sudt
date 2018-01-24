/**
 * @file udt.h
 * @brief 
 * @author supergui@live.cn
 * @version 1.0.0
 * @date 2018-01-24
 */
#ifndef SIMPLE_UDT_20180124_H
#define SIMPLE_UDT_20180124_H

#include <unistd.h>

typedef struct {
    char data[1];
} udt_socket_t;

udt_socket_t* udt_socket_create();
int udt_socket_close(udt_socket_t *sock);
int udt_socket_bind(udt_socket_t *sock, const char *addr);
int udt_socket_listen(udt_socket_t *sock, int backlog);
int udt_socket_connect(udt_socket_t *sock, const char *addr);
ssize_t udt_socket_send(udt_socket_t *sock, const void *buffer, size_t len, int flags);
ssize_t udt_socket_recv(udt_socket_t *sock, void *buffer, size_t len, int flags);

#endif
