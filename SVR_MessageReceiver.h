#ifndef _SVR_MSG_RCVER_
#define _SVR_MSG_RCVER_

#include "SVR_Include.h"

class CMsgRecver
{
public:
    CMsgRecver();
    CMsgRecver(SOCKET_FD fdClient);

    INT32 Recv();
    bool IsFinsh();
    void GetInnrMsg(InnrMessage& stMsg);

private:
    UINT16 m_usCurrendIndex;
    SOCKET_FD m_fdClient;
    SockMessage m_stMessage;
};


#endif


