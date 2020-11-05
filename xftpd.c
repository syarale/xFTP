#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"



static int
service_loop(int client_fd)
{
    const char* ret = "hello client.";
    ssize_t len;
    char recv_buf[MAX_DATA_MESSAGE];
    printf("wait for data.\n");
    recv(client_fd, recv_buf, sizeof(recv_buf), 0);
    printf("get data: %s\n", recv_buf);

    printf("ret len is : %d\n", sizeof(ret));
    send(client_fd, ret, 50, 0);
    printf("send data: %s.\n", ret);

    return 0;
}


int
main()
{
    int client_fd, listen_fd;
    int err;
    socklen_t client_len;
    struct sockaddr_in client_addr, server_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SEVR_PORT);

    bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    listen(listen_fd, MAX_LISTEN);

    client_len = sizeof(client_addr);
    printf("[INFO]: Listen default port.\n");

    client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
    printf("[INFO]: Create connection with client.\n");

    err = service_loop(client_fd);

    printf("finished...\n");

    return 0;
}