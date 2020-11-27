#include <string.h>
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


/* Check if has enough space to allocate or not */
static int
netbuf_check_reserve(struct netbuf *buf, size_t len)
{
    size_t used;
    int r;

    used = buf->size - buf->off;
    if ((used + len) > buf->max_size) {
        return (used + len - buf->max_size);
    }

    return 0;
}


/*
 * Check if netbuf should move data or not. If not, return void.
 * Or move data of netbuf, and update member(size, off) of netbuf.
 */
static void
netbuf_may_pack(struct netbuf *buf, int force)
{
    if (buf->off == 0) {
        return;
    }

    if (force || (buf->off > NETBUF_PACK_MIN && buf->off >= (buf->size/2))) {
        memmove(buf->data, buf->data + buf->off, buf->size - buf->off);
        buf->off = 0;
        buf->size -= buf->off;
    }
    return;
}


/*
 * Allocate len-size space on netbuf, (may move [data + off, data + size] 
 * data to [data, data + off]), and update the member of netbuf.
 * Return r (>0) on error, 0 on success.
 */
static int
netbuf_allocate(struct netbuf *buf, size_t len)
{
    int r;
    size_t need;
    u_char *dp;

    /* check if has enough space to allocate or not */
    if ((r = netbuf_check_reserve(buf, len)) != 0) {
        ERROR("len over limitation, has no more space to allocate.");
        return r;
    }

    /* already have it */
    if (buf->alloc - buf->size >= len) {
        return 0;
    }

    /* may move bytes front */
    netbuf_may_pack(buf, buf->size + len > buf->max_size);
    
    need = len - (buf->alloc - buf->size);
    if ((dp = realloc(buf->data, buf->alloc + need)) == NULL) {
        ERROR("Failed to realloc space for netbuf...");
        return -1;
    }

    buf->data = dp;
    buf->alloc += need;
    
    return 0;
}




/*
 * Update netbuf and allocate space to store len-size data.
 * Return r (>0) on error, or save the write pointer in dpp on success.
 */
static int
netbuf_reserve(struct netbuf *buf, size_t len, u_char **dpp)
{
    int r;
    u_char *dp;

    if (dpp != NULL) {
        *dpp = NULL;
    }

    if ((r = netbuf_allocate(buf, len)) != 0) {
        ERROR("Failed to allocate netbuf...");
        return r;
    }

    dp = buf->data + buf->size;
    buf->size += len;
    *dpp = dp; 
    return 0;
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