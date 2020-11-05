#include <stdio.h>

#define MAX_CMD_LINE 20

void test_sizeof()
{
    int len;
    char cmd_buf[MAX_CMD_LINE];

    len =  sizeof(cmd_buf);
    printf("len is : %d\n", len);
    return;
}

int main()
{
    test_sizeof();




    return 0;
}