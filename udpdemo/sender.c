#include"head.h"
int main(int argc,const char * argv[])
{

  int sockfd;
  struct sockaddr_in sockaddr;
  char rbuf[BUFF_SIZE];
  if(-1==(sockfd=socket(AF_INET,SOCK_DGRAM,0)))    //因为TCP仅仅支持一对一通信，UDP能够一对一，一对多，多对一，多对多。因为这个广播。是多对多。所以仅仅能是SOCK_DGRAM

    perror("socket");

  bzero(&sockaddr,sizeof(sockaddr));
  sockaddr.sin_family=AF_INET;
  sockaddr.sin_port=htons(BRAOD_PORT);   //#define BRAOD_PORT 50001
  sockaddr.sin_addr.s_addr=inet_addr(BRAOD_IP);//#define BRAOD_IP "192.168.1.255"

  if(-1==bind(sockfd,(struct sockaddr *)&sockaddr,sizeof(sockaddr)))
    perror("bind");


     while(1)
   {
     bzero(&rbuf,sizeof(rbuf));
     recvfrom(sockfd,rbuf,BUFF_SIZE,0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
     printf("--------%s-------\n",rbuf);
   }

   close(sockfd);
   return 0;
}

#if 0

#include"head.h"
int main(int argc ,const char * argv[])
{
    /*
     *创建组播发送方的步骤：
     *创建套接字
     *设置组播地址（可选）
     *发送数据
     *关闭套接字
     * */

    int sockfd;
    struct sockaddr_in multiaddr;
    char sbuf[BUFF_SIZE]="hello,xiaowang....\n";
    int n;
    if(-1==(sockfd=socket(AF_INET,SOCK_DGRAM,0)))
       perror("socket");

    bzero(&multiaddr,sizeof(multiaddr));
    multiaddr.sin_family=AF_INET;
    multiaddr.sin_port=htons(MULTI_PORT);   //#define MULTI_PORT 50002   仅仅要是用户自己定义端口就可以
    multiaddr.sin_addr.s_addr=inet_addr(MULTI_IP);
    #define MULTI_IP "224.4.4.4"  D类地址是组播地址224.0.0.1---239.255.255.254

    while(1)
    {
        sleep(1);
        if(-1==(n=sendto(sockfd,sbuf,strlen(sbuf),0,(struct sockaddr*)&multiaddr,sizeof(multiaddr))))
            perror("sendto");

        printf("in the sending..........\n");
    }   
    return 0;
}

#endif