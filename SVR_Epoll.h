#ifndef _SVR_EPOLL_
#define _SVR_EPOLL_

#include "SVR_Include.h"

class CEpoll
{
public:
    bool Initalisation(SOCKET_FD fdServer);
    
    bool AddClient(SOCKET_FD fdClient, UINT32 ulEvent);
    bool ModClient(SOCKET_FD fdClient, UINT32 ulEvent);
    bool DelClient(SOCKET_FD fdClient);

    UINT16 EpollWait(UINT16 uMaxEvtCnt, EpollEvent* pstEvtList);

    SOCKET_FD GetServerSocketFd();

private:
    EPOLL_FD m_fdEpoll;
    SOCKET_FD m_fdServer;
};

#endif

