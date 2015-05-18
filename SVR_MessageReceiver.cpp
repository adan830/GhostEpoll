#include "SVR_MessageReceiver.h"

CMsgRecver::CMsgRecver()
{
    m_usCurrendIndex = 0;
    m_stMessage.ulMsgTotalLen = 0;
    m_fdClient = -1;
}

CMsgRecver::CMsgRecver(SOCKET_FD fdClient)
{
    m_usCurrendIndex = 0;
    m_stMessage.ulMsgTotalLen = 0;
    m_fdClient = fdClient;

}

INT32 CMsgRecver::Recv()
{
    INT32 iReadLen = 0;

    do
    {
        iReadLen = read(m_fdClient, (char *)(&m_stMessage) + m_usCurrendIndex, sizeof(SockMessage) - m_usCurrendIndex);

        if(iReadLen > 0)
        {
             m_usCurrendIndex += iReadLen;
        }
    }
    while(iReadLen > 0 && !IsFinsh());
}

bool CMsgRecver::IsFinsh()
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
void CMsgRecver::GetInnrMsg(InnrMessage& stMsg)
{
    stMsg.fdClient = m_fdClient;
    stMsg.usMsgBodyLen = m_stMessage.ulMsgTotalLen - sizeof(m_stMessage.ulMsgTotalLen);

    memcpy(stMsg.acMsgBody, m_stMessage.acMessageBuffer, stMsg.usMsgBodyLen);
}

