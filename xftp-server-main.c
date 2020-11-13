// #include <stdio.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <stdlib.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

// #include "common.h"



// static int
// service_loop(int client_fd)
// {
//     const char* ret = "hello client";
//     ssize_t len;
//     char recv_buf[MAX_DATA_MESSAGE];

//     for(;;) {
//         int recv_ret;

//         printf("[INFO]: Wait for data\n");
//         recv_ret = recv(client_fd, recv_buf, sizeof(recv_buf), 0);
//         if (recv_ret == 0) {
//             break;
//         }

//         printf("[INFO]: Get data:%s\n", recv_buf);
//         if (strncmp(recv_buf, "exit", 4) == 0) {
//             break;
//         }
//         send(client_fd, ret, MAX_DATA_MESSAGE, 0);
//         printf("[INFO]: Send data:%s\n\n", ret);
//     }


//     return 0;
// }


// static int
// start_listen(struct sockaddr_in* client_addr)
// {
//     int listen_fd, client_fd;
//     struct sockaddr_in server_addr;

//     listen_fd = socket(AF_INET, SOCK_STREAM, 0);
//     bzero(&server_addr, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     server_addr.sin_port = htons(SEVR_PORT);

//     bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
//     listen(listen_fd, MAX_LISTEN);
//     printf("[INFO]: Listen default port.\n");

//     return listen_fd;



// }

// static int
// wait_connect(int listen_fd, struct sockaddr_in* client_addr)
// {
//     int client_fd;
//     socklen_t client_len;

//     client_len = sizeof(client_addr);
//     client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
//     printf("[INFO]: Create connection with client.\n");

//     return client_fd;
    
// }

// int
// main()
// {
//     int client_fd, listen_fd;
//     int err;
//     pid_t child_pid;
//     struct sockaddr_in client_addr;

//     listen_fd = start_listen(&client_addr);


//     for (;;) {
//         client_fd = wait_connect(listen_fd, &client_addr);
//         if ((child_pid = fork()) == 0) {
//             close(listen_fd);
//             service_loop(client_fd);
//             exit(0);
//         }
//         close(client_fd);
//     }

//     printf("finished...\n");

//     return 0;
// }