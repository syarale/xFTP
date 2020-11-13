#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"

static int
start_listen(struct sockaddr_in* client_addr)
{
    int listen_fd, client_fd;
    struct sockaddr_in server_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SEVR_PORT);

    bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    listen(listen_fd, MAX_LISTEN);
    printf("[xftpd]: Listen default port.\n");

    return listen_fd;
}

static int
wait_connect(int listen_fd, struct sockaddr_in* client_addr)
{
    int client_fd;
    socklen_t client_len;

    client_len = sizeof(client_addr);
    client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
    printf("[xftpd]: Create connection with client.\n");

    return client_fd;
    
}

int
main()
{
    int client_fd, listen_fd;
    int err;
    pid_t child_pid;
    struct sockaddr_in client_addr;

    listen_fd = start_listen(&client_addr);
    for (;;) {
        printf("[xftpd]: Wait to connect...\n");
        client_fd = wait_connect(listen_fd, &client_addr);
        if ((child_pid = fork()) == 0) {
            char client_fd_buf[10];

            close(listen_fd);
            snprintf(client_fd_buf, 10, "%d", client_fd);

            // launch xftp-server to process request.
            char* argv[]={"./xftp-server", client_fd_buf, NULL};
            char* envp[]={NULL};
            execve("./xftp-server", argv, envp);
            exit(0);
        }
        close(client_fd);
    }

    printf("[xftpd]: xftpd exited...\n");
    return 0;
}