#ifndef __SYS_GET_PRESET_INFO_CMD_H__
#define __SYS_GET_PRESET_INFO_CMD_H__

#include "sys_base_command_executor.h"


class SysGetPresetInfoCommandExecutor : public SysBaseCommandExecutor
{
public:
    SysGetPresetInfoCommandExecutor(void);
    virtual ~SysGetPresetInfoCommandExecutor(void);

    virtual GMI_RESULT	Create( ReferrencePtr<BasePacket>& Packet, SafePtr<BaseCommandExecutor>& CommandExecutor );
    virtual GMI_RESULT  Execute();
    virtual GMI_RESULT  Reply();
};

#endif
