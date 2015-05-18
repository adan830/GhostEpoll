#include "SVR_Include.h"

#include "SVR_Server.h"
#include "SVR_MessageManager.h"

#include "APP_Application.h"


const INT16 SVR_PORT_CONST_INT16 = 6000;
const INT32 SVR_ERR_CONST_INT32   = 1;

int main()
{
    // init dbs

    // init msg mgr
    CMessageManager *poMsgMgr = new CMessageManager();
    if (!(poMsgMgr->Initialized()))
    {
        return SVR_ERR_CONST_INT32;
    }

    // init app
    CApplication *poApp = new CApplication();
    if (!poApp->Initialized(poMsgMgr))
    {
        return SVR_ERR_CONST_INT32;
    }

    // init svr
    CServer* poSvr = new CServer();
    if(!(poSvr->Initialized(SVR_PORT_CONST_INT16, poMsgMgr)))
    {
        return SVR_ERR_CONST_INT32;
    }

    // main loop
    while(true)
    {
        poSvr->Runing(); // recv and send messages
        poApp->Runing(); // handle message
    }

    
    // should not get to here!
    return 0;
}
