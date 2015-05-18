#ifndef _SVR_INC_
#define _SVR_INC_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <set>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>

using namespace std;

#define MAX_MESSAGE_LENTH (1024)
#define MAX_CLEINT_NUM    (1024)


typedef char  INT8;
typedef short INT16;
typedef int   INT32;

typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;

typedef int EPOLL_FD;
typedef int SOCKET_FD;

typedef struct epoll_event EpollEvent;
typedef struct sockaddr_in SocketAddrIn;
typedef struct sockaddr    SocketAddr;

/**********************************************/
/*                  Message                   */
/**********************************************/
   
typedef struct
{
    UINT32 ulMsgTotalLen;
    INT8   acMessageBuffer[MAX_MESSAGE_LENTH]; 
}SockMessage;

typedef struct
{
    SOCKET_FD fdClient;
    UINT16 usMsgBodyLen;
    INT8 acMsgBody[MAX_MESSAGE_LENTH]; 
}InnrMessage;

#endif

