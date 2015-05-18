#ifndef _APP_APPLICATION_
#define _APP_APPLICATION_

#include "SVR_Include.h"
#include "SVR_MessageManager.h"

class CApplication
{
public:
    bool Initialized(CMessageManager* poMsgMgr);

    void Runing();

private:
    InnrMessage GetTestRsp(InnrMessage& stRecvMsg);

private:
    CMessageManager* m_poMsgMgr;
};

#endif




