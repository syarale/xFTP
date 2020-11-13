#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"
#include "netbuf.h"


static int
service_loop(int client_fd)
{
    const char* ret = "hello client";
    ssize_t len;
    char recv_buf[MAX_DATA_MESSAGE];

    for(;;) {
        int recv_ret;

        printf("[xftp-server]: Wait for data\n");
        recv_ret = read(client_fd, recv_buf, MAX_DATA_MESSAGE);
        if (recv_ret == 0) {
            break;
        }

        printf("[xftp-server]: Get data:%s\n", recv_buf);
        if (strncmp(recv_buf, "exit", 4) == 0) {
            break;
        }
        write(client_fd, ret, MAX_DATA_MESSAGE);
        printf("[xftp-server]: Send data:%s\n\n", ret);
    }

    return 0;
}


int
main(int argc, char** argv)
{
    int client_fd;
    int err;

    printf("[xftp-server]: Launch xftp-server process...\n");
    client_fd = atoi(argv[1]);
    err = service_loop(client_fd);
    printf("[xftp-server]:xftp-server exited...\n");

    return 0;
}


