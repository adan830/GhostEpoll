#include "SVR_MessageSender.h"

CMsgSender::CMsgSender()
{
    m_usCurrendIndex = 0;
    m_fdClient = -1;
    m_stMessage.ulMsgTotalLen = 0;
}

CMsgSender::CMsgSender(const InnrMessage *pstMsg)
{
    m_usCurrendIndex = 0;
    m_fdClient = pstMsg->fdClient;
    m_stMessage.ulMsgTotalLen = pstMsg->usMsgBodyLen + sizeof(m_stMessage.ulMsgTotalLen);

    memcpy(m_stMessage.acMessageBuffer, pstMsg->acMsgBody, pstMsg->usMsgBodyLen);
}

void CMsgSender::Send()
{
    INT32 iSendLen = 0;
    do
    {
        iSendLen = write(m_fdClient, (char *)(&m_stMessage), m_stMessage.ulMsgTotalLen - m_usCurrendIndex);

        if(iSendLen > 0)
        {
            m_usCurrendIndex += (UINT16)iSendLen;
        }
    }
    while(iSendLen > 0 && !IsFinsh());
}

bool CMsgSender::IsFinsh()
{
    if(m_usCurrendIndex < sizeof(m_stMessage.ulMsgTotalLen))
    {
        return false;
    }

    if(m_usCurrendIndex < m_stMessage.ulMsgTotalLen)
    {
        return false;
    }

    return true;
}

SOCKET_FD CMsgSender::GetClientFd()
{
    return m_fdClient;
}

