#include "udt.h"

typedef struct {
    int fd;
    void *send;
    void *recv;
} udt_socket_internal_t;

udt_socket_t* udt_socket_create() {
    udt_socket_internal_t *sock = malloc(sizeof(udt_socket_internal_t));
    return (udt_socket_t *)sock;
}
