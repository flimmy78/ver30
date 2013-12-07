#ifndef __SYS_SET_NETWORK_PORT_CMD_H__
#define __SYS_SET_NETWORK_PORT_CMD_H__

#include "sys_base_command_executor.h"

class SysSetNetworkPortCommandExecutor : public SysBaseCommandExecutor
{
public:
    SysSetNetworkPortCommandExecutor();
    virtual ~SysSetNetworkPortCommandExecutor();
    virtual GMI_RESULT	Create( ReferrencePtr<BasePacket>& Packet, SafePtr<BaseCommandExecutor>& CommandExecutor );
    virtual GMI_RESULT  Execute();
    virtual GMI_RESULT  Reply();
};


#endif

