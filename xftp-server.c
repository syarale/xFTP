#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdlib.h>

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
    int recv_ret;
    int in, out, max;
    int ilen, olen;
    char recv_buf[100];
    int is_out;
    const char* ret = "hello client";
    fd_set rset, wset;
    
    printf("[xftp-server]: Launch xftp-server process...\n");
    client_fd = atoi(argv[1]);
    in = client_fd;
    out = client_fd;
    max = 0;
	if (in > max)
		max = in;
	if (out > max)
		max = out;
    
    is_out = 0;
    olen = 1;
    for (;;) {
        // Must clear rset and wset before call select every time
        FD_ZERO(&rset);     
        FD_ZERO(&wset);
        
        FD_SET(in, &rset);
        if ((olen % 2) == 0) {
            FD_SET(out, &wset);
            is_out = 1;
        }
        
        if (is_out) {
            printf("[xftp-server]: Wait for data\n");
        }

        if (select(max + 1, &rset, &wset, NULL, NULL) == -1) {
            if (errno == EINTR) {
                continue;
            }
            printf("[xftp-server]: error, select: %s\n", strerror(errno));
            exit(2);
        }

        if (FD_ISSET(in, &rset)) {
            recv_ret = read(client_fd, recv_buf, MAX_DATA_MESSAGE);
            if (recv_ret == 0){
                break;
            }
            printf("[xftp-server]: Get data:%s\n", recv_buf);
            if (strncmp(recv_buf, "exit", 4) == 0) {
                break;
            }
        }

        if (FD_ISSET(out, &wset)) {
            write(client_fd, ret, MAX_DATA_MESSAGE);
            printf("[xftp-server]: Send data:%s\n\n", ret);
        }

        olen++;
    }

    printf("[xftp-server]:xftp-server exited...\n");

    return 0;
}


