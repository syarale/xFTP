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
 * Client and server transfer data by request.
 */

#define REQUEST_ID_INIT    0
#define REQUEST_TYPE_INIT  0
typedef unsigned char u_char;
struct request
{
    u_int32_t id;
    u_int8_t type;
    u_char *data;
    size_t data_len;
};

/*
 * Create a new request buffer.
 * Return the pointer to buffer on success, or NULL on allocation failure.
 */
struct request * request_new(void);

/* 
 * Copy infomation of req in an msg buffer, and send it to server.
 * Return the size of transfering.
 * Msg format is : | msg_len(5 + data_len) | id(4) | type(1) | data(data_len) |
 */
#define MSG_HEAD_LEN ((2*sizeof(u_int32_t)) + (sizeof(u_int8_t)))
#define MSG_MAX_LEN  0x80000
size_t send_request(int sockfd, struct request *req);

