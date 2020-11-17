#include <sys/select.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_CMD_LINE 20

void test_sizeof()
{
    int len;
    char cmd_buf[MAX_CMD_LINE];

    len =  sizeof(cmd_buf);
    printf("len is : %d\n", len);
    return;
}


void test_select_out()
{
    fd_set rset;
    int maxfd;
    int fileno;
    FILE* file;
    
    // fileno = STDOUT_FILENO; 
    fileno = open("./hello.txt", O_WRONLY|O_CREAT|O_TRUNC);
    int i;
    for (i = 0; i < 2; i++) {
        FD_ZERO(&rset);

        printf("fileno: %d\n", fileno);
        FD_SET(fileno, &rset); 
        maxfd = fileno + 1;
        printf("11111\n");
        select(maxfd, &rset, NULL, NULL, NULL);
        printf("222222\n");
        if (FD_ISSET(fileno, &rset)) {
            printf("stdout:ready to write.\n");
        }
    }

    return;
}

int main()
{
    test_select_out();
    return 0;
}

