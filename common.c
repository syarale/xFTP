#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"


/* 
 * Poke and peek data in buffer.
 */
void
poke_u32(u_char *ptr, u_int32_t number)
{
    const u_int32_t tmp = number;
    ((u_char *)(ptr))[0] = (tmp>>24) & 0xff;
    ((u_char *)(ptr))[1] = (tmp>>16) & 0xff;
    ((u_char *)(ptr))[2] = (tmp>>8) & 0xff;
    ((u_char *)(ptr))[3] = (tmp) & 0xff;
    
    return;
}

void
poke_u8(u_char *ptr, u_int8_t number)
{
    const u_int8_t tmp = number;
    ((u_char *)(ptr))[0] = tmp;

    return;
}


void
peek_u32(const u_char *ptr, u_int32_t *number)
{   
    u_int32_t tmp;
    
    tmp = ((const u_char *)(ptr))[0] << 24;
    tmp = tmp | ((const u_char *)(ptr))[1] << 16;
    tmp = tmp | ((const u_char *)(ptr))[2] << 8;
    tmp = tmp | ((const u_char *)(ptr))[3];
    *number = tmp;

    return;
}

void
peek_u8(const u_char *ptr, u_int8_t *number)
{
    u_int8_t tmp;

    tmp = ((const u_char *)(ptr))[0];
    *number = tmp;

    return;
}



