#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h> //memset()
#include <arpa/inet.h>  //inet_ntop()
#include <netinet/in.h> //socket()
// #include <unistd.h>

#define SERV_IP_ADDR "192.168.0.11"
#define SERV_PORT 5000
#define BUF_LEN 128
typedef int SOCK;
SOCK serv_sock, clt_sock;   //서버와 클라이언트 소켓
struct sockaddr_in serv_addr, clt_addr; //인터넷 전용 소켓주소 구조체. 주소체계,IP,포트번호 저장
char buffer[BUF_LEN+1];       //클라이언트에 보낼 메세지를 저장


//네트워크로 전송하기 전에 함수를 사용하여 네트워크 바이트 순서로 바꿈htons()
//‒네트워크로부터 수신한 숫자는 ntohs 함수를 사용하여 자신의 호스트 바이트 순서로 바

//소켓 생성
void initSock(SOCK& sock)
{
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        printf("Socket init failed\n");
        exit(-1);
    }

}

//sockaddr_in 구조체 초기화
void initSockAddr(struct sockaddr_in& addr)
{
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;                  //소켓 주소 체계 = 인터넷으로 설정
    addr.sin_port = htons(SERV_PORT);           //포트 번호
    addr.sin_addr.s_addr= htonl(INADDR_ANY);    //서버 자신의 주소 자동으로 가져오기. ip주소 저장 구조체
}

//socket과 소켓 구조체 바인딩
void binding(SOCK& sock, struct sockaddr_in& addr)
{
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if(bind < 0)
    {
        printf("Socket bind failed\n");
        exit(-1);
    }
}

void listening(int& serverSock, int connects)
{
    int isListen = listen(serverSock, connects);
    if(isListen < 0)
    {
        printf("Listening failed\n");
        exit(-1);
    }
    printf("Listening...\n");
}

void connecting(SOCK& serverSock, SOCK& clientSock, struct sockaddr_in& clientAddr )
{
    clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, (socklen_t *)sizeof(clientAddr));
    if(clientSock < 0)
    {
        printf("accept failed ! \n");
        exit(-1);
    }

    //클라이언트 주소 프린트
    //NOTE: remove this
    char clt_IP[20];
    inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, clt_IP, sizeof(clt_IP));
    printf("Connected client: %s\n", clt_IP);
}

void sending(SOCK& receiver, char* msg, int flag)
{
    int isSuccess = send(receiver, msg, sizeof(msg), flag);
    if(isSuccess >= 0)
    {
        printf("send complete\n");
    }
}

void receiving(SOCK& sender, char* msg, int flag)
{
    int isSuccess = recv(sender, msg, sizeof(msg), flag);
    if(isSuccess >= 0)
    {
        printf("receive complete\n");
    }
}


int main()
{
    initSock(serv_sock);
    initSockAddr(serv_addr);
    binding(serv_sock, serv_addr);
    
    listening(serv_sock, 1);
    connecting(serv_sock, clt_sock, clt_addr);

    // sending(clt_sock, buffer, 0);

}