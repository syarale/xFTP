#pragma once

int connect_server(char* server_ip);
ssize_t send_data(int sockfd, const char* buf, size_t len);


