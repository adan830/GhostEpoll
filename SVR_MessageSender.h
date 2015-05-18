#ifndef _SVR_MSG_SENDER_
#define _SVR_MSG_SENDER_

#include "SVR_Include.h"

class CMsgSender
{
public:
    CMsgSender();
    CMsgSender(const InnrMessage *pstMsg);

    void Send();
    bool IsFinsh();

    SOCKET_FD GetClientFd();

private:
    UINT16 m_usCurrendIndex;
    SOCKET_FD m_fdClient;
    SockMessage m_stMessage;
};


#endif



