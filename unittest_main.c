#include <stdio.h>
#include <stdlib.h>

#include "common.h"
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

void test_poke_peek()
{
    u_char *ptr = (u_char *)malloc(sizeof(u_int32_t));
    u_int32_t i_32 = 0x00553247;
    u_int32_t o_32;
    u_int8_t i_8 = 0x65;
    u_int8_t o_8;

    poke_u32(ptr, i_32);
    peek_u32(ptr, &o_32);
    printf("%d \n", o_32);
    printf("%d \n", i_32);

    poke_u8(ptr, i_8);
    peek_u8(ptr, &o_8);
    printf("%d \n", o_8);
    printf("%d \n", i_8);

    free(ptr);
    return;
}

int main()
{
    // test_netbf_new();
    test_poke_peek();
    return 0;
}