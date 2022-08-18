#include "head.h"
int socket_init()
{
   int sockfd;
    struct sockaddr_in sockaddr;
   if((( sockfd=socket(AF_INET,SOCK_STREAM,0))==-1))
         sys_err("socket");

   bzero(&sockaddr,sizeof(sockaddr));
   sockaddr.sin_family=AF_INET;
   sockaddr.sin_port=htons(SER_PORT);
   sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   printf("%d=====\n",sockfd);

   if((bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr)))==-1)
        sys_err("bind");

    listen(sockfd,5); //要懂得监听的作用，事实上就是建立一个缓冲队列，让创建的队列最多能够同意五个套接字进入
    return sockfd;
}

int do_echo(int connectfd)
{
     char sbuf[BUFF_SIZE];
     char rbuf[BUFF_SIZE];
    int n;
   printf("int the server ==========\n");
   while(1)
   {
      printf("===============in the do_echo\n");
      bzero(rbuf,BUFF_SIZE);
      if((n=recv(connectfd,rbuf,BUFF_SIZE,0))==-1)
         sys_err("recv");

      if(n==0)     //假设接受为0，代表client已经断线，返回-1
         return -1;

      printf("server:rbuf==%s\n",rbuf);
      sprintf(sbuf,"%s %s",rbuf,"---------echo");

      send(connectfd,sbuf,strlen(sbuf),0);
   }

   return ;
}
int main(int argc,const char * argv[])
{
    //步骤：
   /*
    *1 创建套接字socket();
    *2 与IP地址绑定bind();
    *3监听  listen();
    *4假设有链接，接受链接，进行三次握手accept();
    *5与client进行数据的传输read(),send();
    *6关闭套接字close(sockfd);
    * 
    *注意：要掌握熟练掌握各个接口的调用
    * 为了实现多client和服务器的交互，该怎么做
    * */

   int sockfd;//具有基本属性的套接字描写叙述符
   int connectfd;//进行三次握手之后的套接字描写叙述符

     sockfd=socket_init();
    //listen(sockfd,5); //要懂得监听的作用，事实上就是建立一个缓冲队列，让创建的将要
                  //连接的套接字描写叙述符进队和出队
/*
 *
 *
 *     The   accept()   system    call  is  used  with  connection-based  socket  types
 *      (SOCK_STREAM, SOCK_SEQPACKET).  It extracts the first connection request on the
 *      queue  of  pending  connections for the listening socket, sockfd, creates a new
 *
 *
 * */
    pid_t pid;

    signal(SIGCHLD,SIG_IGN);

   while(1)
   {

        connectfd=accept(sockfd,NULL,NULL);   //一个服务器能够和多个client进程多次握手连接。 切记，connect（）函数在UDP协议中也能够用，不是TCP的专用
        if(connectfd == -1)
            sys_err("accept");

      if(-1==(pid=fork()))
      {
         perror("fork");
      }
      else if(pid==0)
      {

      printf("do_echo===%d\n", do_echo(connectfd));
      close(connectfd);    //将子进程从父进程拷贝到的套接字资源，关闭了
         close(sockfd);
      }
   }
close(connectfd);//父进程关闭自己的套接字
   close(sockfd);
     return 0;

}