#ifndef _SVR_APP_
#define _SVR_APP_

#include "SVR_Include.h"
#include "SVR_Epoll.h"
#include "SVR_MessageManager.h"

class CServer
{
public:
    bool Initialized(INT16 sSvrPort, CMessageManager* poMsgMgr);
    void Runing();

private:
    bool InitServerSocket(INT16 sSvrPort, SOCKET_FD& fdServer);
    void HandleEvents(EpollEvent* astEvents, UINT16 usEventCnt);
    void UpdateEpollClient();

    void HandleAcceptEvent();
    void HandleSendEvent(SOCKET_FD fdClient);
    void HandleRecvEvent(SOCKET_FD fdClient);

private:
    CEpoll m_oEpoll;
    CMessageManager* m_poMsgMgr;
};

#endif
