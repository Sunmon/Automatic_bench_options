#include <stdio.h>
#include <stdlib.h>
// #include <sys/socket.h>
// #include <sys/types.h>
#include <string.h> //memset()
#include <arpa/inet.h>  //inet_ntop()
#include <netinet/in.h> //socket()
// #include <unistd.h>

// #define SERV_IP_ADDR "192.168.0.11"
#define SERV_PORT 5000
#define BUF_LEN 128
char* SERV_IP_ADDR;
typedef int SOCK;
SOCK clt_sock;   //클라이언트 소켓
struct sockaddr_in serv_addr; //인터넷 전용 소켓주소 구조체. 주소체계,IP,포트번호 저장
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
//NOTE: server에 있는애랑 다름
void initSockAddr(struct sockaddr_in& addr, char* ip, char* port = "SERV_PORT")
{
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;                  //소켓 주소 체계 = 인터넷으로 설정
    addr.sin_port = htons(atoi(port));           //포트 번호
    addr.sin_addr.s_addr= inet_addr(ip);    //서버 주소 ip주소 저장 구조체

    // inet_pton(AF_INET, SERV_IP_ADDR, &addr.sin_addr);
}

void connecting(SOCK& sock, const struct sockaddr_in& serverAddr)
{
    int isSuccess = connect(clt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(isSuccess >= 0)
    {
        printf("Connected\n");
    }
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



//socket-client [server IP]
int main(int argc, char* argv[])
{   
    SERV_IP_ADDR = argv[1];
    initSock(clt_sock);
    initSockAddr(serv_addr, SERV_IP_ADDR);
    connecting(clt_sock, serv_addr);



}
