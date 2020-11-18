#include "netbuf.h"


// struct netbuf {
// 	u_char *d;		    /* Data */
// 	size_t off;		    /* First available byte is buf->d + buf->off */
// 	size_t size;		/* Last byte is buf->d + buf->size - 1 */
// 	size_t max_size;	/* Maximum size of buffer */
// 	size_t alloc;		/* Total bytes allocated to buf->d */
// };

/*
 * Create a new netbuf buffer.
 * Returns pointer to buffer on success, or NULL on allocation failure.
 */
struct netbuf *
netbuf_new(void)
{
    struct netbuf *ret;
    if ((ret = calloc(sizeof(*ret), 1)) == NULL) {
        return NULL;
    }

    ret->alloc = NETBUF_SIZE_INIT;
    ret->max_size = NETBUF_SIZE_MAX;
    ret->off = 0;
    ret->size = 0;
    if ((ret->data = calloc(1, ret->alloc)) == NULL) {
        free(ret);
        return NULL;
    }

    return ret;
}
