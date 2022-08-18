#ifndef _HEAD_H_
#define _HEAD_H_

#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netinet/in.h>
#include<error.h>
#include<errno.h>
#include<unistd.h>      //fork
#include<sys/wait.h>

#define SER_PORT 50004
#define SER_IP "192.168.192.128"
#define CLIENT_PORT 50000
#define CLIENT_IP "192.168.192.128"

#define BUFF_SIZE 100
#define SIZE 20

typedef struct _USER
{
  char name[SIZE];
  char passwd[SIZE];
}usr;
#define sys_err(_msg)  error(EXIT_FAILURE,errno,_msg)
/*errno是个全局变量，调用之后，能够在错误发生的情况下，也能输出——msg信息
*作为调试用
* */
#endif
