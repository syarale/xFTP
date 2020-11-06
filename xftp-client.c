#include <stdio.h>
#include "common.h"
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/*
 * Call connect() function, and return the sockfd on success, -1 on error.
 */
int connect_server(char* server_ip)
{
    int sockfd;
    int conn_ret;
    struct sockaddr_in server_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SEVR_PORT);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    conn_ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (conn_ret == -1) {
        printf("[ERROR]: Failed to connect remote server(%s).\n", server_ip);
        return conn_ret;
    }
    return sockfd;
}