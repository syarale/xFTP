#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

// struct request
// {
//     u_int32_t id;
//     u_int8_t type;
//     u_char* data;
//     size_t data_len;
// };



void
poke_u32(char *buf, u_int32_t number)
{

    return;
}

void
poke_u8(char *buf, u_int8_t number)
{

    return;
}


static ssize_t
send_msg(int sockfd, const char* buf, size_t len)
{
    ssize_t ret;
    ret = write(sockfd, buf, len);
    return ret;
}

/*
 * Create a new request buffer.
 * Return the pointer to buffer on success, or NULL on allocation failure.
 */
struct request * 
request_new(void)
{
    struct request* ret;
 
    if ((ret = calloc(sizeof(*ret), 1)) == NULL) {
        LOG("%s: Failed to allocate space.", __func__);
        return NULL;
    }

    ret->id = REQUEST_ID_INIT;
    ret->type = REQUEST_TYPE_INIT;
    ret->data = NULL;
    ret->data_len = 0;
    return ret;
}

/* 
 * Copy infomation of req in an msg buffer, and send it to server.
 * Return the size of transfering.
 * Msg format is : | msg_len(5 + data_len) | id(4) | type(1) | data(data_len) |
 */
size_t 
send_request(int sockfd, struct request *req)
{
    u_int32_t msg_len;
    char *req_buf;
    size_t ret;

    assert(req != NULL);

    msg_len = MSG_HEAD_LEN + req->data_len;
    if (msg_len > MSG_MAX_LEN) {
        ERROR("%s: Failed to send messages, message size over limitation.", __func__);
        return -1;
    }
    if ((req_buf = calloc(sizeof(char), msg_len)) == NULL) {
        ERROR("%s: Failed to allocate space.");
        return -1;
    }

    poke_u32(req_buf, msg_len);
    poke_u32(req_buf + 4, req->id);
    poke_u8(req_buf + 4 + 4, req->type);
    memcpy(req_buf + MSG_HEAD_LEN, req->data, req->data_len);
    ret = send_msg(sockfd, req_buf, msg_len);

    return ret;
}