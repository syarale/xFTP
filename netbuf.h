#pragma once
#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u_int;
typedef unsigned char u_char;

#define NETBUF_SIZE_INIT	256		    /* Initial allocation */
#define NETBUF_SIZE_MAX		0x8000000	/* Hard maximum size */
#define NETBUF_SIZE_INC	    256		    /* Preferred increment length */

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


