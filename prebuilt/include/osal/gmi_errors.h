// gmi_errors.h
// define result value for internal function call
// To SDK used by client,specific result value list should be defined.
#if !defined( GMI_ERRORS )
#define GMI_ERRORS

#include "gmi_type_definitions.h"

// result type + os type + module type + reserve + error value
// 1bits         3bits     8bits         4bits     16bits

// result type definition
#define RESULT_TYPE_SUCCESS             0
#define RESULT_TYPE_FAIL                1

// operation system type definition
#define OPERATION_SYSTEM_LINUX_GENERAL  0
#define OPERATION_SYSTEM_WINDOWS        1
#if defined( __linux__ )
#define OPERATION_SYSTEM_TYPE           OPERATION_SYSTEM_LINUX_GENERAL
#elif defined( _WIN32 )
#define OPERATION_SYSTEM_TYPE           OPERATION_SYSTEM_WINDOWS
#else
#error not support current platform
#endif

// module type definition
#define MODULE_TYPE_GENERAL             0
#define MODULE_TYPE_COMMUNICATION       1
#define MODULE_TYPE_FILE                2
#define MODULE_TYPE_PROCESS             3
#define MODULE_TYPE_THREAD              4
// 0-99 is reserved for osal
// 100-255 is assigned to other module
#define MODULE_TYPE_LOG                 100
#define MODULE_TYPE_COMMAND_PIPELINE    101
#define MODULE_TYPE_UPDATE              102

#if ( __WORDSIZE == 64 )
typedef longlong_t  GMI_RESULT;
#else
typedef long_t      GMI_RESULT;
#endif

#if defined( SUCCEEDED )
#undef SUCCEEDED
#endif
#define SUCCEEDED(x)                    (0<=((GMI_RESULT)x))

#if defined( FAILED )
#undef FAILED
#endif
#define FAILED(x)                       (0>((GMI_RESULT)x))

#define MAKE_ERROR(r,o,m,v)             ((r<<31)+(o<<28)+(m<<20)+v)

// general result value
#define GMI_SUCCESS                         MAKE_ERROR(RESULT_TYPE_SUCCESS,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,0)

#define GMI_FAIL                            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,0)
#define GMI_NOT_IMPLEMENT                   MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,1)
#define GMI_NOT_SUPPORT                     MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,2)
#define GMI_INVALID_PARAMETER               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,3)
#define GMI_OUT_OF_MEMORY                   MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,4)
#define GMI_WAIT_TIMEOUT                    MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,5)
#define GMI_INVALID_OPERATION               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,6)
#define GMI_TRY_AGAIN_ERROR                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,7)
#define GMI_SYSTEM_BUSY                     MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,8)
#define GMI_NOT_ENOUGH_SPACE                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,9)
#define GMI_ALREADY_OPERATED                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,10)
#define GMI_OPEN_DEVICE_FAIL                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,11)
#define GMI_CLOSE_DEVICE_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,12)
#define GMI_QUERY_DEVICE_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,13)
#define GMI_CONFIG_DEVICE_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,14)
#define GMI_DEVICE_NOT_OPENED               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,15)
#define GMI_DEVICE_ALREADY_OPENED           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,16)
#define GMI_NO_ACCESS_RIGHT                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,17)
#define GMI_EXCEED_LIMIT                    MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,18)
#define GMI_SYSTEM_ERROR                    MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,19)//device read or write error, select error
#define GMI_NO_AVAILABLE_DATA               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_GENERAL,20)

// commmunication result value
#define GMI_OPEN_SERIAL_PORT_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,0)
#define GMI_CLOSE_SERIAL_PORT_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,1)
#define GMI_READ_SERIAL_PORT_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,2)
#define GMI_WRITE_SERIAL_PORT_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,3)
#define GMI_SET_SERIAL_PORT_PARAM_FAIL      MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,4)
#define GMI_GET_SERIAL_PORT_PARAM_FAIL      MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,5)

#define GMI_CREATE_SOCKET_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,10)
#define GMI_DESTROY_SOCKET_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,11)
#define GMI_SOCKET_SEND_FAIL                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,12)
#define GMI_SOCKET_RECEIVE_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,13)
#define GMI_SOCKET_BIND_FAIL                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,14)
#define GMI_SOCKET_OPEN_FAIL                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,15)
#define GMI_SOCKET_LISTEN_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,16)
#define GMI_SOCKET_ACCEPT_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,17)
#define GMI_SOCKET_CONNECT_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,18)
#define GMI_SET_SOCKET_OPTION_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,19)
#define GMI_GET_SOCKET_OPTION_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,20)

#define GMI_DISCARD_PACKET                  MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,21)
#define GMI_CONNECTION_RESET_ERROR          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,22)
#define GMI_SOCKET_ALREADY_RESET            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,23)
#define GMI_SOCKET_ALREADY_SHUTDOWN         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMUNICATION,24)

// file result value
#define GMI_CREATE_FILE_FAIL                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_FILE,0)
#define GMI_OPEN_FILE_FAIL                  MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_FILE,1)
#define GMI_CLOSE_FILE_FAIL                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_FILE,2)
#define GMI_DELETE_FILE_FAIL                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_FILE,3)
#define GMI_READ_FILE_FAIL                  MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_FILE,4)
#define GMI_WRITE_FILE_FAIL                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_FILE,5)
#define GMI_SEEK_FILE_FAIL                  MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_FILE,6)

// process result value
#define GMI_CREATE_ANONYMOUS_PIPE_FAIL      MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,0)
#define GMI_DESTROY_ANONYMOUS_PIPE_FAIL     MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,1)
#define GMI_WRITE_ANONYMOUS_PIPE_FAIL       MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,2)
#define GMI_READ_ANONYMOUS_PIPE_FAIL        MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,3)

#define GMI_CREATE_EVENT_IPC_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,10)
#define GMI_OPEN_EVENT_IPC_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,11)
#define GMI_DESTROY_EVENT_IPC_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,12)
#define GMI_WAIT_EVENT_IPC_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,13)
#define GMI_SIGNAL_EVENT_IPC_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,14)

#define GMI_CREATE_MESSAGE_QUEUE_FAIL       MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,20)
#define GMI_DESTROY_MESSAGE_QUEUE_FAIL      MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,21)
#define GMI_OPEN_MESSAGE_QUEUE_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,22)
#define GMI_CLOSE_MESSAGE_QUEUE_FAIL        MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,23)
#define GMI_MESSAGE_QUEUE_SEND_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,24)
#define GMI_MESSAGE_QUEUE_RECEIVE_FAIL      MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,25)

#define GMI_CREATE_MUTEX_IPC_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,30)
#define GMI_OPEN_MUTEX_IPC_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,31)
#define GMI_DESTROY_MUTEX_IPC_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,32)
#define GMI_LOCK_MUTEX_IPC_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,33)
#define GMI_UNLOCK_MUTEX_IPC_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,34)
#define GMI_MUTEX_IPC_ALREADY_EXIST         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,35)
#define GMI_MUTEX_IPC_NOT_FOUND             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,36)

#define GMI_CREATE_NAMED_PIPE_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,40)
#define GMI_DESTROY_NAMED_PIPE_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,41)
#define GMI_OPEN_NAMED_PIPE_FAIL            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,42)
#define GMI_CLOSE_NAMED_PIPE_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,43)
#define GMI_WRITE_NAMED_PIPE_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,44)
#define GMI_READ_NAMED_PIPE_FAIL            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,45)
#define GMI_PIPE_LISTENING_ERROR            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,46)
#define GMI_BROKEN_PIPE_ERROR               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,47)

#define GMI_CREATE_SEMAPHORE_IPC_FAIL       MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,60)
#define GMI_OPEN_SEMAPHORE_IPC_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,61)
#define GMI_DESTROY_SEMAPHORE_IPC_FAIL      MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,62)
#define GMI_WAIT_SEMAPHORE_IPC_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,63)
#define GMI_POST_SEMAPHORE_IPC_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,64)

#define GMI_CREATE_SHARE_MEMORY_FAIL        MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,70)
#define GMI_DESTROY_SHARE_MEMORY_FAIL       MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,71)
#define GMI_OPEN_SHARE_MEMORY_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,72)
#define GMI_CLOSE_SHARE_MEMORY_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,73)
#define GMI_MAP_SHARE_MEMORY_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,74)
#define GMI_UNMAP_SHARE_MEMORY_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,75)
#define GMI_WRITE_SHARE_MEMORY_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,76)
#define GMI_READ_SHARE_MEMORY_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_PROCESS,77)

// thread result value
#define GMI_CREATE_EVENT_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,0)
#define GMI_DESTROY_EVENT_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,1)
#define GMI_WAIT_EVENT_FAIL                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,2)
#define GMI_SIGNAL_EVENT_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,3)

#define GMI_CREATE_MUTEX_ATTR_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,10)
#define GMI_DESTROY_MUTEX_ATTR_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,11)
#define GMI_SET_MUTEX_ATTR_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,12)
#define GMI_GET_MUTEX_ATTR_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,13)
#define GMI_CREATE_MUTEX_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,14)
#define GMI_DESTROY_MUTEX_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,15)
#define GMI_LOCK_MUTEX_FAIL                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,16)
#define GMI_UNLOCK_MUTEX_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,17)

#define GMI_CREATE_RWLOCK_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,20)
#define GMI_DESTROY_RWLOCK_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,21)
#define GMI_ACQUIRE_RLOCK_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,22)
#define GMI_RELEASE_RLOCK_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,23)
#define GMI_ACQUIRE_WLOCK_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,24)
#define GMI_RELEASE_WLOCK_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,25)

#define GMI_CREATE_SEMAPHORE_FAIL           MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,30)
#define GMI_DESTROY_SEMAPHORE_FAIL          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,31)
#define GMI_WAIT_SEMAPHORE_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,32)
#define GMI_POST_SEMAPHORE_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,33)

#define GMI_CREATE_THREAD_ATTR_FAIL         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,40)
#define GMI_DESTROY_THREAD_ATTR_FAIL        MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,41)
#define GMI_SET_THREAD_ATTR_FAIL            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,42)
#define GMI_GET_THREAD_ATTR_FAIL            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,43)
#define GMI_CREATE_THREAD_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,44)
#define GMI_DESTROY_THREAD_FAIL             MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,45)
#define GMI_START_THREAD_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,46)
#define GMI_PAUSE_THREAD_FAIL               MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,47)
#define GMI_RESUME_THREAD_FAIL              MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,48)
#define GMI_STOP_THREAD_FAIL                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,49)
#define GMI_SET_THREAD_FAIL                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,50)
#define GMI_GET_THREAD_FAIL                 MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_THREAD,51)

// command pipeline
#define GMI_NO_PACKET_PARSER_ERROR          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMAND_PIPELINE,0)
#define GMI_NO_COMMAND_PARSER_ERROR         MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_COMMAND_PIPELINE,1)

// update
#define GMI_UPDATE_OVER_SELECTED            MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_UPDATE,0)
#define GMI_UPDATE_XML_ERROR                MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_UPDATE,1)
#define GMI_UPDATE_DEVICE_NOT_OPEN          MAKE_ERROR(RESULT_TYPE_FAIL,OPERATION_SYSTEM_TYPE,MODULE_TYPE_UPDATE,2)

#endif//GMI_ERRORS