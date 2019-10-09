// http://ftp.linux.co.kr/pub/DOCS/Linux_Network_&_System_Programming%B1%B3%C0%E7.pdf
// page 72
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>


//make socket
int socket(int protocolFamily, int type, int protocol)
{

}


//ex1: call socket() and print socket number
void makeSocket()
{
    int fd1,fd2,sd1,sd2;
    printf("getdtablesize() = %d\n",getdtablesize());
    
    fd1 = open("/etc/passwd",O_RDONLY,0);   //open file
    printf("/etc/passwd's file descriptor = %d\n",fd1);

    sd1= socket(PF_INET, SOCK_STREAM,0);        //open stream socket
    printf("stream socket descriptor = %d\n",sd1);

    sd2 = socket(PF_INET, SOCK_DGRAM, 0); //open datagram socket
    printf("datagram socket descriptor = %d\n",sd2);

    fd2= open("/etc/hosts",O_RDONLY,0); //open file
    printf("/etc/hosts's file descriptor = %d\n",fd2);

    //close file & sockets
    close(fd2);
    close(fd1);
    close(sd2);
    close(sd1);
}


int main()
{
    makeSocket();

}