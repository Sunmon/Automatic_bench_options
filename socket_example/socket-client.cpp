#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#define CLNT_IP_ADDR "192.168.0.11"
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
    close(sock);

    return 0;
}