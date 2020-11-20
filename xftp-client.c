#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#include "common.h"
#include "netbuf.h"
#include "xftp-client.h"


/*
 * Call connect() function, and return the sockfd on success, -1 on error.
 */
int
connect_server(char* server_ip)
{
    int sockfd;
    int conn_ret;
    struct sockaddr_in server_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SEVR_PORT);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    conn_ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (conn_ret == -1) {
        printf("[ERROR]: Failed to connect remote server(%s).\n", server_ip);
        return conn_ret;
    }
    return sockfd;
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
 * Send message buffer to server by calling write()
 */
static ssize_t
send_msg(const int sockfd, const char* buf, size_t len)
{
    ssize_t ret;
    ret = write(sockfd, buf, len);
    if (ret == -1) {
        ERROR("Failed to send msg to server");
    }

    return ret;
}

/* 
 * Copy infomation of req in an msg buffer, and send it to server.
 * Return the size of transfering on success, or -1 on error.
 * Msg format is : | msg_len(5 + data_len) | id(4) | type(1) | data(data_len) |
 */
size_t 
send_request(const int sockfd, struct request *req)
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

// /* test modify requset */
// void print_request(const struct request *req)
// {
//     printf("id: %d\n", req->id);
//     printf("type: %d\n", req->type);
//     printf("len: %d\n", req->data_len);

//     if (req->data == NULL) {
//         printf("data: NULL \n");
//     } else {
//         printf("data: %s \n", req->data);
//     }
//     return;
// }

/*
 * Send 'len' byte of buffer to server by socket.
 * Return the size of tranfering on success, or -1 on error.
 */
ssize_t
send_data(const int sockfd, const char* buf, size_t len)
{
    ssize_t ret;
    struct request *req = request_new();

    if (req == NULL) {
        ERROR("Failed to allocate 'request'.");
        return -1;
    }

    /* TODO: modify id and type */
    req->type = NET_OPEN_FILE;
    req->id = 1;
    if ((req->data = (char *)malloc(sizeof(char) * len)) == NULL) {
        ERROR("Failed to allocate space for req->data.");
        return -1;
    }

    memcpy(req->data, buf, len);
    
    /* test */
    print_request(req);

    ret = write(sockfd, buf, len);
    return ret;
}