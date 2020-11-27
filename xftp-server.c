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


struct netbuf *iqueue;
struct netbuf *oqueue;


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
    size_t ilen, olen, len;
    char buf[4*4096];   // TODO：modify the buf size.
    int is_out, r;
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
        FD_ZERO(&rset);    // Must clear rset and wset before call select every time
        FD_ZERO(&wset);
        
        FD_SET(in, &rset);
        if ((olen % 2) == 0) {
            FD_SET(out, &wset);
            is_out = 0;
        } else {
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
            len = read(client_fd, buf, sizeof(buf));
            if (len == 0) {
                LOG("Read EOF.");
                exit(0);
            } else if(len == -1) {
                ERROR("Failed to read: %s", strerror(errno));
                exit(1);
            } else {
                // r = netbuf_put(iqueue, buf, len);
                // printf("[xftp-server]: get data: %s\n", buf+9);
                printf("buf len is: %d\n", len);
                r = 0;
                if (r != 0) {
                    ERROR("Failed to put buffer in iqueue");
                    exit(1);
                }

            }
            printf("[xftp-server]: Get data: %s\n", buf + 9);
            if (strncmp(buf+9, "exit", 4) == 0) {
                break;
            }
        }

        if (FD_ISSET(out, &wset)) {
            len = write(client_fd, ret, MAX_DATA_MESSAGE);
            printf("[xftp-server]: Send data:%s\n\n", ret);
        }

        olen++;
    }

    printf("[xftp-server]:xftp-server exited...\n");

    return 0;
}


