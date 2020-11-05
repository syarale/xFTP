
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "xftp.h"
#include "xftp-client.h"
#include "common.h"


static int
interactive_loop(FILE* fp, int sockfd) 
{
    size_t len;
    char cmd_buf[MAX_CMD_LINE + 1];                 // the last char is '\0'
    char recv_buf[MAX_CMD_LINE + 1];

    printf("[INFO]: Connect to remote server.\n");
    printf("xftp> ");
    fgets(cmd_buf, sizeof(cmd_buf) - 1, stdin);
    len = strlen(cmd_buf);

    // fget save '\n' of the last char in stdin line.
    if (cmd_buf[len - 1] != '\n') {
        printf("[ERROR]: Invalid input, The max-length is %d characters.\n", MAX_CMD_LINE-1);
        return INVALID_ERR;
    } else {
        cmd_buf[len - 1] = '\0';
    }

    send(sockfd, cmd_buf, sizeof(cmd_buf), 0);
    recv(sockfd, recv_buf, sizeof(recv_buf), 0);
    printf("[INFO]: Get data: %s \n", recv_buf);

    return 0;
}

int
main(int argc, char** argv)
{
    int sockfd;
    int conn_ret, err;
    char* server_ip = argv[1];
    struct sockaddr_in server_addr;

    if (argc != 2) {
        printf("Usage:   xftp ip port\n");
        printf("Example: xftp 192.168.56.107\n");
        return 0;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SEVR_PORT);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    conn_ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (conn_ret == -1) {
        printf("[ERROR]: Failed to connect remote server(%s).\n", server_ip);
        return 0;
    }

    err = interactive_loop(stdin, sockfd);

    return 0;
}