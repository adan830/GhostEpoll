#include "SVR_Epoll.h"

#include <sys/epoll.h>

bool CEpoll::Initalisation(SOCKET_FD fdServer)
{
    m_fdServer = fdServer;
    m_fdEpoll  = epoll_create(MAX_CLEINT_NUM);

    AddClient(fdServer, EPOLLIN|EPOLLET);
    
    return true;
}

bool CEpoll::AddClient(SOCKET_FD fdClient, UINT32 ulEvent)
{
    EpollEvent stEvent; 
    
    stEvent.data.fd = fdClient;     
    stEvent.events = ulEvent;
    
    epoll_ctl(m_fdEpoll, EPOLL_CTL_ADD, fdClient, &stEvent);

    return true;
}

bool CEpoll::ModClient(SOCKET_FD fdClient, UINT32 ulEvent)
{
    EpollEvent stEvent; 
    
    stEvent.data.fd = fdClient;     
    stEvent.events = ulEvent;
    
    epoll_ctl(m_fdEpoll, EPOLL_CTL_MOD, fdClient, &stEvent);

    return true;
}

bool CEpoll::DelClient(SOCKET_FD fdClient)
{ 
    epoll_ctl(m_fdEpoll, EPOLL_CTL_DEL, fdClient, NULL);

    return true;
}


UINT16 CEpoll::EpollWait(UINT16 uMaxEvtCnt, EpollEvent* pstEvtList)
{
    return epoll_wait(m_fdEpoll, pstEvtList, uMaxEvtCnt, 0);
}

SOCKET_FD CEpoll::GetServerSocketFd()
{
    return m_fdServer;
}

