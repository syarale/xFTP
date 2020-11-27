#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>


#define SEVR_PORT 6999
#define MAX_CMD_LINE 100
#define MAX_DATA_MESSAGE 100
#define MAX_LISTEN  5
#define INVALID_ERR 0


/* Request type */
#define NET_OPEN_FILE 0



typedef unsigned char u_char;
typedef unsigned char u_char;

/* 
 * Use macro definitions for debugging.
 */
#define DEBUG_PRINT do{}while(0)
#if defined(DEBUG_PRINT)
#define DEBUG(format, ...)\
        do{\
            printf("[DEBUG]: "); \
            printf("%s: ", __func__); \
            printf(format, ##__VA_ARGS__); \
            printf("\n"); \
        }while(0)

#define LOG(format, ...)\
        do{\
            printf("[INFO]: "); \
            printf(format, ##__VA_ARGS__); \
            printf("\n"); \
        }while(0)

#define WARN(format, ...)\
        do{\
            printf("[WARN]: "); \
            printf(format, ##__VA_ARGS__); \
            printf("\n"); \
        }while(0)
#endif

#define ERROR(format, ...)\
        do{\
            printf("[ERROR]: "); \
            printf("%s: ", __func__); \
            printf(format, ##__VA_ARGS__); \
            printf("\n"); \
        }while(0)


/* 
 * Poke and peek data in buffer.
 */

void poke_u32(u_char *ptr, u_int32_t number);
void poke_u8(u_char *ptr, u_int8_t number);

void peek_u32(const u_char *ptr, u_int32_t *number);
void peek_u8(const u_char *ptr, u_int8_t *number);
