#ifndef __SYS_BASE_COMMAND_EXECUTOR_H__
#define __SYS_BASE_COMMAND_EXECUTOR_H__

#include "system_service_manager.h"
#include "gmi_system_headers.h"
#include "base_command_executor.h"

class SysBaseCommandExecutor : public BaseCommandExecutor
{
public:
    SysBaseCommandExecutor( uint32_t CommandId, enum CommandType Type );
    ~SysBaseCommandExecutor();
    GMI_RESULT SetParameter( ReferrencePtr<SystemServiceManager> SystemServiceManagerPtr, void_t *Argument, size_t ArgumentSize);

protected:
    ReferrencePtr<SystemServiceManager> m_SystemServiceManager;
    void_t *m_Argument;
    size_t  m_ArgumentSize;
};

#endif
