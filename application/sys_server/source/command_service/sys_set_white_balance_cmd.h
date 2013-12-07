#ifndef __SYS_SET_WHITE_BALANCE_CMD_H__
#define __SYS_SET_WHITE_BALANCE_CMD_H__

#include "sys_base_command_executor.h"


class SysSetWhiteBalanceCommandExecutor : public SysBaseCommandExecutor
{
public:
    SysSetWhiteBalanceCommandExecutor();
    virtual ~SysSetWhiteBalanceCommandExecutor();
    virtual GMI_RESULT	Create( ReferrencePtr<BasePacket>& Packet, SafePtr<BaseCommandExecutor>& CommandExecutor );
    virtual GMI_RESULT  Execute();
    virtual GMI_RESULT  Reply();
};

#endif



