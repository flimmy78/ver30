#pragma once

#include "media_center_command_executor.h"

class MediaCenterSetOperationWithOneParameterCommandExecutor : public MediaCenterCommandExecutor
{
protected:
    MediaCenterSetOperationWithOneParameterCommandExecutor( uint32_t CommandId, enum CommandType Type );

public:
    virtual ~MediaCenterSetOperationWithOneParameterCommandExecutor(void);

    virtual GMI_RESULT	Create( ReferrencePtr<BasePacket>& Packet, SafePtr<BaseCommandExecutor>& CommandExecutor );
    virtual GMI_RESULT  Execute();

protected:
    uint32_t  m_Token;
    uint32_t  m_Parameter1;
};