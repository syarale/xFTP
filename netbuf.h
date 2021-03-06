#pragma once
#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>



#define NETBUF_SIZE_INIT	256		    /* Initial allocation */
#define NETBUF_SIZE_MAX		0x8000000	/* Hard maximum size */
#define NETBUF_SIZE_INC	    256		    /* Preferred increment length */
#define NETBUF_PACK_MIN	    8192		/* Minimim packable offset */

struct netbuf {
	u_char *data;		/* Data */
	size_t off;		    /* First available byte is buf->data + buf->off */
	size_t size;		/* Last byte is buf->d + buf->size - 1 */
	size_t max_size;	/* Maximum size of buffer */
	size_t alloc;		/* Total bytes allocated to buf->d */
};

/*
 * Create a new netbuf buffer.
 * Returns pointer to buffer on success, or NULL on allocation failure.
 */
struct netbuf *netbuf_new(void);

/*
 * Copy bytes to netbuf.
 * Return 0 on success, or non-zero on error.
 */
int netbuf_put(struct netbuf *net_buf, const void *ptr, size_t len);


