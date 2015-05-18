#include "APP_Application.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

bool CApplication::Initialized(CMessageManager * poMsgMgr)
{
    if(NULL == poMsgMgr)
    {
        return false;
    }
    
    m_poMsgMgr = poMsgMgr;
    
    return true;
}

void CApplication::Runing()
{
    vector<InnrMessage> vecRecvMsgList;
    vector<InnrMessage> vecSendMsgList;
    
    m_poMsgMgr->GetRecvMsg(vecRecvMsgList);

    InnrMessage stSendMsg;
    for(UINT32 ulIdx = 0; ulIdx < vecRecvMsgList.size(); ++ulIdx)
    {
        stSendMsg = GetTestRsp(vecRecvMsgList[ulIdx]);
        vecSendMsgList.push_back(stSendMsg);
    }

    m_poMsgMgr->SetSendMsg(vecSendMsgList);
}

InnrMessage CApplication::GetTestRsp(InnrMessage& stRecvMsg)
{
    InnrMessage stSendMsg = {0};

    cout << "[CApplication::GetTestRsp] recv msg from client" << stRecvMsg.fdClient
         << " lenth is "   << stRecvMsg.usMsgBodyLen 
         << " message is: "<< stRecvMsg.acMsgBody << endl;

    stSendMsg.fdClient = stRecvMsg.fdClient;

    sprintf(stSendMsg.acMsgBody, "[svr] hello client%d recv your msg : %s",
            stRecvMsg.fdClient, stRecvMsg.acMsgBody);

    stSendMsg.usMsgBodyLen = (UINT16)(strlen(stSendMsg.acMsgBody) + 1);

    return stSendMsg;
}

