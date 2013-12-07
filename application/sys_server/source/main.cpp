#include "stdio.h"
#include "stdlib.h"
#include "log.h"
#include "daemon.h"
#include "net_manager.h"
#include "sys_command_processor.h"
#include "gmi_system_headers.h"
#include "base_memory_manager.h"
#include "ipc_fw_v3.x_resource.h"
#include "gmi_daemon_heartbeat_api.h"


//system command service object
static  SafePtr<SysCommandProcessor> l_SysCmdService;

void SignalHandler(int signum)
{
    if (signum == SIGINT)
    {
        printf("receive SIGINT (Ctrl-C) signal\n");
        exit(0);
    }
    else if (signum == SIGIO)
    {
        printf("receive SIGIO signal\n");
    }
    else if (signum == SIGPIPE)
    {
        printf("receive SIGPIPE signal\n");
    }
    else if (signum == SIGHUP)
    {
        printf("receive SIGHUP signal\n");
        exit(0);
    }
    else if (signum == SIGQUIT)
    {
        printf("receive SIGQUIT signal\n");
        exit(0);
    }
    else if (signum == SIGSEGV)
    {
        sleep(1);
    }
    else
    {
        printf("receive unknown signal. signal = %d\n", signum);
    }
    return;
}


void Release(void)
{
    //system service uninit
    l_SysCmdService->Deinitialize();
    //daemon unregister
    DaemonUnregister();
    return;
}

int main( int32_t argc, char_t *argv[])
{
    GMI_RESULT Result = GMI_SUCCESS;
    int32_t  Signal;
    sigset_t NewMask;
    sigset_t OldMask;
    struct sigaction Sa;

    //signal
    Sa.sa_handler = SignalHandler;
    sigfillset(&Sa.sa_mask);
    Sa.sa_flags = SA_NOMASK;
    sigemptyset(&NewMask);
    for (Signal = 1; Signal <= _NSIG; ++Signal)
    {
        if (( Signal == SIGIO )
                || ( Signal == SIGPOLL )
                || ( Signal == SIGINT )
                || ( Signal == SIGQUIT )
                || ( Signal == SIGHUP )
                || ( Signal == SIGPIPE )
                || ( Signal == SIGSEGV )
           )
        {
            sigaction(Signal, &Sa, NULL);
        }
        else
        {
            sigaddset(&NewMask, Signal);
        }
    }
    sigprocmask(SIG_BLOCK, &NewMask, &OldMask);

    //register exit func
    atexit(Release);

    LogInitial();

    //net activate
    //Result = NetActivate(0);
    //if (FAILED(Result))
    //{
    //    SYS_ERROR("NetActivate fail, Result = 0x%lx\n", Result);
    //return -1;
    //}

    //daemon init
    Result = DaemonRegister();
    if (FAILED(Result))
    {
        SYS_ERROR("DaemonRegister fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "DaemonRegister fail, Result = 0x%lx\n", Result);
        return -1;
    }

    //system command service new
    l_SysCmdService = BaseMemoryManager::Instance().New<SysCommandProcessor>(GMI_CONTROL_C_PORT, GMI_CONTROL_S_PORT, 62*1024);
    if (NULL == l_SysCmdService.GetPtr())
    {
        SYS_ERROR("l_SysCmdService new fail\n");
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "l_SysCmdService new fail\n");
        return -1;
    }

    //system command service init
    Result = l_SysCmdService->Initialize(NULL);
    if (FAILED(Result))
    {
        SYS_ERROR("SysCmdService Initialize fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "SysCmdService Initialize fail, Result = 0x%lx\n", Result);
        return -1;
    }

    DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Info, "main initial complete\n");

    uint32_t BootFlag = APPLICATION_RUNNING;

    while (1)
    {
        Result = DaemonKeepAlive(&BootFlag);
        if (SUCCEEDED(Result))
        {
            if (APPLICATION_QUIT == BootFlag)
            {
                SYS_INFO("daemon inform system server normal out!!!\n");
                break;
            }
        }
        GMI_Sleep(1000);
    }

    l_SysCmdService->Deinitialize();
    DaemonUnregister();
    return EXIT_SUCCESS;
}

