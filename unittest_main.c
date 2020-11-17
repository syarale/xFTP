#include <stdio.h>
#include <stdlib.h>
#include "netbuf.h"

// struct netbuf {
// 	u_char *data;		/* Data */
// 	size_t off;		    /* First available byte is buf->data + buf->off */
// 	size_t size;		/* Last byte is buf->d + buf->size - 1 */
// 	size_t max_size;	/* Maximum size of buffer */
// 	size_t alloc;		/* Total bytes allocated to buf->d */
// };

void test_netbuf_new() {
    struct netbuf* net;
    net = netbuf_new();

    if (net == NULL) {
        printf("Failed to allocate netbuff\n");
        return;
    }

    printf("data size: %d\n", sizeof(*(net->data)));
    printf("off: %d\n", net->off);
    printf("size: %d\n", net->size);
    printf("max size: %d\n", net->max_size);
    printf("alloc: %d\n", net->alloc);

    free(net->data);
    free(net);
    
    return;
}



int main()
{
    test_netbuf_new();
    return 0;
}