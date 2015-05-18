#include "SVR_Server.h"

const UINT16 MAX_EPOLL_EVENT_COUNT = 20;

/***************************************************/
/*    public                                       */
/***************************************************/

bool CServer::Initialized(INT16 sSvrPort, CMessageManager* poMsgMgr)
{
    if(NULL == poMsgMgr)
    {
        return false;
    }
    m_poMsgMgr = poMsgMgr;

    SOCKET_FD fdServer;
    if(!InitServerSocket(sSvrPort, fdServer))
    {
        cout << "[CServer::Initialized]:InitServerSocket" << endl;
        return false;
    }

    if(!m_oEpoll.Initalisation(fdServer))
    {
        cout << "[CServer::Initialized]: m_oEpoll" << endl;
        return false;
    }

    cout << "[CServer::Initialized]: init finish! listen port:"  << sSvrPort << endl;
    
    return true;
}

void CServer::Runing()
{
    EpollEvent astEvents[MAX_EPOLL_EVENT_COUNT];
    UINT16 uEventCnt = m_oEpoll.EpollWait(MAX_EPOLL_EVENT_COUNT, astEvents);

    if(0 == uEventCnt)
    {
        return;
    }

    cout << "[CServer::Runing]: epoll wait seccess " << "uEventCnt[" << uEventCnt << "]"<< endl;
    
    HandleEvents(astEvents, uEventCnt);
    UpdateEpollClient();
}

/***************************************************/
/*     private                                     */
/***************************************************/

bool CServer::InitServerSocket(INT16 sSvrPort, SOCKET_FD& fdServer)
{
    fdServer = socket(AF_INET, SOCK_STREAM, 0);
    
    SocketAddrIn stServerAddr = {0};
    
    stServerAddr.sin_family = AF_INET;
    stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    stServerAddr.sin_port=htons(sSvrPort);
    
    bind(fdServer,(struct sockaddr *)(&stServerAddr), sizeof(stServerAddr));
    listen(fdServer, 20);

    cout << "[CServer::InitServerSocket]: listen..." << endl;

    return true;
}

void CServer::HandleEvents(EpollEvent* astEvents, UINT16 usEventCnt)
{
    for(UINT16 uEvtIdx = 0; uEvtIdx < usEventCnt; ++uEvtIdx)
    {
        cout << "[CServer::HandleEvents]: handle event [" << astEvents[uEvtIdx].events << "]" << endl;
  
        if(m_oEpoll.GetServerSocketFd() == astEvents[uEvtIdx].data.fd)
        {                
            HandleAcceptEvent();
        }            
        else if((astEvents[uEvtIdx].events & EPOLLIN) == EPOLLIN)
        {                
            m_poMsgMgr->OnEpollIn(astEvents[uEvtIdx].data.fd);
        }            
        else if((astEvents[uEvtIdx].events & EPOLLOUT) == EPOLLOUT)
        {
            m_poMsgMgr->OnEpollOut(astEvents[uEvtIdx].data.fd);
        }
        else
        {
            close(astEvents[uEvtIdx].data.fd);
            m_oEpoll.DelClient(astEvents[uEvtIdx].data.fd);
        }
    }
}

void CServer::UpdateEpollClient()
{
    vector<SOCKET_FD> vecInSocket  = m_poMsgMgr->GetNeedSetInSocketList();
    vector<SOCKET_FD> vecOutSocket = m_poMsgMgr->GetNeedSetOutSocketList();

    for(UINT16 usIdx = 0; usIdx < vecInSocket.size(); ++usIdx)
    {
        m_oEpoll.ModClient(vecInSocket[usIdx], EPOLLIN|EPOLLET);
    }

    for(UINT16 usIdx = 0; usIdx < vecOutSocket.size(); ++usIdx)
    {
        m_oEpoll.ModClient(vecOutSocket[usIdx], EPOLLOUT|EPOLLET);
    }

    if(vecInSocket.size() == 0 && vecOutSocket.size() == 0)
    {
        return;
    }

    cout << "[CServer::UpdateEpollClient]:" << " in: [" << vecInSocket.size() << "], out :[" << vecOutSocket.size() << "]"<< endl;
}

void CServer::HandleAcceptEvent()
{
    SocketAddrIn stClient  = {0};
    
    SOCKET_FD    fdServer  = m_oEpoll.GetServerSocketFd();
    socklen_t    iSize     = sizeof(stClient);
    SocketAddr  *pstClient = (SocketAddr*)(&stClient);
    
    SOCKET_FD    fdClient  = accept(fdServer, pstClient, &iSize);

    fcntl(fdClient, F_SETFL, (fcntl(fdClient, F_GETFL)|O_NONBLOCK));

    m_oEpoll.AddClient(fdClient, EPOLLIN|EPOLLET);
    m_poMsgMgr->OnEpollAccp(fdClient);
    
    cout << "[CServer::HandleAcceptEvent]:" << " accept client [" << fdClient << "]" << endl;
}

