#pragma once
#include <stdio.h>
#include <stdarg.h>


#define SEVR_PORT 6999
#define MAX_CMD_LINE 100
#define MAX_DATA_MESSAGE 100
#define MAX_LISTEN  5
#define INVALID_ERR 0


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



/* Client and server transfer data by request */
// struct request
// {
//     u_int32_t msg_len;
//     u_int32_t id;
//     u_int8_t type;
//     u_char* data;
// };


/*
 * Create a new request buffer.
 * Return the pointer to buffer on success, or NULL on allocation failure.
 */
// struct request* request_new(void);
