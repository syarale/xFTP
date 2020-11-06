
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

    printf("[INFO]: Connect to remote server, wait to input.\n");
    for (;;) {
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
        
        send(sockfd, cmd_buf, len, 0);
        if (strncmp(cmd_buf, "exit", 4) == 0) {
            break;
        }

        recv(sockfd, recv_buf, sizeof(recv_buf), 0);
        printf("[INFO]: Get data: %s \n", recv_buf);
    }
    
    return 0;
}


int
main(int argc, char** argv)
{
    int sockfd;
    int conn_ret, err;
    char* server_ip = argv[1];
    
    if (argc != 2) {
        printf("Usage:   xftp ip port\n");
        printf("Example: xftp 192.168.56.107\n");
        return 0;
    }

    sockfd = connect_server(server_ip);
    err = interactive_loop(stdin, sockfd);

    return 0;
}