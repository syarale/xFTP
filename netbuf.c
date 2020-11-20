#include "common.h"
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



/*
 * Copy bytes to netbuf.
 * Return 0 on success, or non-zero on error.
 */
int
netbuf_put(struct netbuf *net_buf, const void *ptr, size_t len)
{
    int r;
    u_char *w_ptr;  // store bytes from where w_ptr point to in netbuf;
    
    r = netbuf_reserve(net_buf, len, &w_ptr);
    if (r != 0) {
        ERROR("Failed to reserve data in netbuf.");
        return r;
    }

    memcpy(w_ptr, ptr, len);
    return 0;
}