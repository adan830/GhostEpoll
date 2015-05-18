#include "SVR_MessageManager.h"

bool CMessageManager::Initialized()
{
    return true;
}

// for app
void CMessageManager::GetRecvMsg(vector<InnrMessage>& vecMsgList)
{
    vecMsgList = m_vecRecvMsg;
    
    if(vecMsgList.size() == 0)
    {
        return;
    }
    
    m_vecRecvMsg.clear();
    cout << "[CMessageManager::GetRecvMsg] recv" << vecMsgList.size() << "msgs from client" << endl ;
}

void CMessageManager::SetSendMsg(const vector<InnrMessage>& vecMsgList)
{
    m_vecNeedModOut.clear();
    m_vecNeedModIn.clear();

    for(UINT16 usIdx =0; usIdx < vecMsgList.size(); usIdx++)
    {
        CMsgSender oSend(&(vecMsgList[usIdx]));
        m_mapSender[oSend.GetClientFd()] = oSend;
    }

    if(vecMsgList.size() == 0)
    {
        return;
    }

    cout << "[CMessageManager::SetSendMsg] need send" << vecMsgList.size() << "msgs to client" << endl; 
}

// for svr
void CMessageManager::OnEpollIn(SOCKET_FD fdClent)
{
    if(m_mapRecver.count(fdClent) == 0)
    {
        cout << "[CMessageManager::OnEpollIn]: no recver" << endl;
        return;
    }

    m_mapRecver[fdClent].Recv();

    if(!m_mapRecver[fdClent].IsFinsh())
    {
        return;
    }
    
    InnrMessage stMsg;
    
    m_mapRecver[fdClent].GetInnrMsg(stMsg);
    m_vecRecvMsg.push_back(stMsg);
    
    m_mapRecver.erase(fdClent);
    m_vecNeedModOut.push_back(fdClent);
}

void CMessageManager::OnEpollOut(SOCKET_FD fdClent)
{
    if(m_mapSender.count(fdClent) == 0)
    {
        cout << "[CMessageManager::OnEpollIn]: no Sender" << endl;
        return;
    }

    cout << "[CMessageManager::OnEpollOut]: Send[" << fdClent << "]" << endl;

    m_mapSender[fdClent].Send();

    if(!m_mapSender[fdClent].IsFinsh())
    {
        return;
    }

    m_mapSender.erase(fdClent);
    m_vecNeedModIn.push_back(fdClent);

    CMsgRecver oReciver(fdClent);
    m_mapRecver[fdClent] = oReciver;
}

void CMessageManager::OnEpollAccp(SOCKET_FD fdClent)
{
    if(m_mapSender.count(fdClent) != 0)
    {
        cout << "[CMessageManager::OnEpollAccp]: err : have Sender" << endl;
        return;
    }
    
    CMsgRecver oReciver(fdClent);
    m_mapRecver[fdClent] = oReciver;
}


vector<SOCKET_FD> CMessageManager::GetNeedSetInSocketList()
{
    return m_vecNeedModIn;
}

vector<SOCKET_FD> CMessageManager::GetNeedSetOutSocketList()
{
    return m_vecNeedModOut;
}

