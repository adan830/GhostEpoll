#ifndef _SVR_MSG_MGR_
#define _SVR_MSG_MGR_

#include "SVR_Include.h"
#include "SVR_MessageSender.h"
#include "SVR_MessageReceiver.h"

class CMessageManager
{
public:
    bool Initialized();
    
    // for app
    void GetRecvMsg(vector<InnrMessage>& vecMsgList);
    void SetSendMsg(const vector<InnrMessage>& vecMsgList);

    // for svr
    void OnEpollIn(SOCKET_FD fdClent);
    void OnEpollOut(SOCKET_FD fdClent);
    void OnEpollAccp(SOCKET_FD fdClent);
    
    vector<SOCKET_FD> GetNeedSetInSocketList();
    vector<SOCKET_FD> GetNeedSetOutSocketList();

private:
    map<SOCKET_FD, CMsgRecver> m_mapRecver;
    map<SOCKET_FD, CMsgSender> m_mapSender;

    vector<SOCKET_FD> m_vecNeedModIn;
    vector<SOCKET_FD> m_vecNeedModOut;

    vector<InnrMessage> m_vecRecvMsg;
};



#endif
