// https://blog.neonkid.xyz/116

#include <cstdio>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h> //socket()
#include <unistd.h>
#include <cstring>
#define SERV_IP_ADDR "192.168.0.11"
#define SERV_PORT 5000
#define BUF_LEN 128
struct sockaddr_in server_addr, client_addr; //인터넷 소켓 주소 구조체
int server_fd, client_fd;   //서버와 클라이언트 소켓 번호
char buffer[BUF_LEN];



//socket server [열 포트번호]
int main(int argc, char *argv[])
{
    //TCP로 통신 설정
    server_fd = socket(PF_INET, SOCK_STREAM, 0);
    if( server_fd < 0)
    {
        perror("Socket failed !");
        return -1;
    }

    //server_addr 구조체 초기화
    server_addr.sin_family = AF_INET;           //소켓 주소 체계 = 인터넷으로 설정
    server_addr.sin_port = htons(SERV_PORT);    //포트 번호
    server_addr.sin_addr.s_addr= htonl(INADDR_ANY);    //서버 자신의 주소 자동으로 가져오기. ip주소 저장 구조체
    // server_addr.sin_addr.s_addr=inet_addr(SERV_IP_ADDR);

    //bind socket to port
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("Socket failed !");
        return -1;
    }

    //listen
    if(listen(server_fd, 1) < 0)
    {
        printf("Server : Can't listening connect.\n");
        return -1;
    };
    
    printf("Listening... \n");
    socklen_t addr_len = sizeof(client_addr);

    while(true)
    {
        //client의 socket정보를 받는다
        // client_fd = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t*)sizeof(client_addr));
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
        if(client_fd < 0)
        {
            printf("accept failed ! \n");
            return -1;
        }
        char temp[20];
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
        printf("Connected client: %s\n", temp);


        // int msg_size = read(client_fd, buffer, 1024);
        // write(client_fd, buffer, msg_size);


        //send message to client
        // std::string msg = "hello, world!";
        // char* buf = msg.c_str();
        // write(client_fd, , sizeof(msg.c_str()));
        // write(client_fd, &msg, sizeof(msg));
        // puts("written msg");

        char msg[] = "hello world!";
        int isSend = send(client_fd, msg, sizeof(msg), 0);
        if(isSend > 0)
        {
            printf("send complete\n");
            close(client_fd);

        }






    }
     close(server_fd);


    return 0;
}