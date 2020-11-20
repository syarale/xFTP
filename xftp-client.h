#pragma once



int connect_server(char* server_ip);
ssize_t send_data(const int sockfd, const char* buf, size_t len);


/* 
 * Client and server transfer data by request.
 */
#define REQUEST_ID_INIT    0
#define REQUEST_TYPE_INIT  0
#define MSG_MAX_LEN  0x80000
#define MSG_HEAD_LEN ((2*sizeof(u_int32_t)) + (sizeof(u_int8_t)))

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
size_t send_request(const int sockfd, struct request *req);

