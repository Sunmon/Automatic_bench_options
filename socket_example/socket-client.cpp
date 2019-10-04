#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#define CLNT_IP_ADDR "192.168.0.9"
#define SERV_IP_ADDR "192.168.0.11"
#define CLNT_PORT 5000

int sock, nbyte;
struct sockaddr_in server_addr;

int main(int argc, char *argv[])
{

    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("socket failed in client!");
        return -1;
    }
    
    server_addr.sin_family = AF_INET;           //소켓 주소 체계 = 인터넷으로 설정
    server_addr.sin_port = htons(CLNT_PORT);    //포트 번호
    server_addr.sin_addr.s_addr= htonl(INADDR_ANY);    //서버 자신의 주소 자동으로 가져오기. ip주소 저장 구조체

    inet_pton(AF_INET, SERV_IP_ADDR, &server_addr.sin_addr);

    // 연결 요청,,
    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed !");
        return -1;
    }

    printf("Connection Success !\n");

    printf("asdfadsf\n");
    char msg[30] = {0};
    int isReceive = recv(sock, msg, 30, 0);
    // printf("%d", isReceive);
    if(isReceive>0) {
        printf("Received msg : ");
        msg[29] = '\0';
        printf("%s", msg);
        // std::cout << msg << std::endl;
    }
    // int str_len = read(sock, &msg, sizeof(msg));
    // for(auto& m: msg) printf("%c", m);
    // printf("\n");

    // puts("received msg");


    close(sock);

    //TODO: 만약 소켓 안 닫고 종료하면, 알아서 닫히나?

    return 0;
}