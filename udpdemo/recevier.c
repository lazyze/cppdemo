#include"head.h"
int main(int argc,const char * argv[])
{
      int sockfd;
      int n;
      char rbuf[BUFF_SIZE];
      struct  sockaddr_in groupaddr;

      //创建套接字
      if(-1==(sockfd=socket(AF_INET,SOCK_DGRAM,0)))
          perror("socket");

      //增加组播
    struct ip_mreqn multiaddr;     //这些在Man 2 setsockopt  时在signal的有关描写叙述中能够查到的
      multiaddr.imr_multiaddr.s_addr=inet_addr(MULTI_IP);
      multiaddr.imr_address.s_addr=inet_addr(LOCAL_IP);
      multiaddr.imr_ifindex=0;

    //设置套接字同意发送组播信息的属性
      if(-1==setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&multiaddr,sizeof(multiaddr)))
              perror("setsockopt");


    //绑定组播地址
      bzero(&groupaddr,sizeof(groupaddr));
      groupaddr.sin_family=AF_INET;
      groupaddr.sin_port=htons(MULTI_PORT);
      groupaddr.sin_addr.s_addr=inet_addr(MULTI_IP);

      bind(sockfd,(struct sockaddr*)&groupaddr,sizeof(groupaddr));

      int t;
      while(1)
      {
    //    bzero(&rbuf,sizeof(rbuf));
           t=sizeof(groupaddr);
          if(-1==(n=recvfrom(sockfd,rbuf,BUFF_SIZE,0,(struct sockaddr*)&groupaddr,&t)))
              perror("recvfrom");
            sleep(1);  
          printf("%s-----------\n",rbuf);
      }
      return 0;
}
