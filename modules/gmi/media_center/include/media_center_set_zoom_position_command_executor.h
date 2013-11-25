#pragma once

#include "media_center_set_operation_with_one_parameter_command_executor.h"

class MediaCenterSetZoomPositionCommandExecutor : public MediaCenterSetOperationWithOneParameterCommandExecutor
{
public:
    MediaCenterSetZoomPositionCommandExecutor();
    virtual ~MediaCenterSetZoomPositionCommandExecutor(void);

    virtual GMI_RESULT	Create( ReferrencePtr<BasePacket>& Packet, SafePtr<BaseCommandExecutor>& CommandExecutor );
    virtual GMI_RESULT  Execute();
};
