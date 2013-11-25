#pragma once

#if !defined( IPC_MEDIA_DATA_RESEND_NUMBER )
#define IPC_MEDIA_DATA_RESEND_NUMBER          64
#endif

#include "application_packet.h"
#include "general_command_pipeline_manager.h"
#include "gmi_system_headers.h"
#include "udp_session.h"

class IpcMediaDataNextDataCommandRequester;
class IpcMediaDataReleaseDataCommandRequester;
class IpcMediaDataUDPSession;

#if !defined( MEDIA_DATA_CALLBAK_FUNCTION )
#define MEDIA_DATA_CALLBAK_FUNCTION 1
typedef void_t (*MEDIA_DATA_CALLBAK)( void_t *UserData, uint32_t MediaType, uint32_t MediaId, const void_t *Frame, size_t FrameLength, const struct timeval *FrameTS, const void_t *ExtraData, size_t ExtraDataLength );
#endif//MEDIA_DATA_CALLBAK_FUNCTION

class IPC_MediaDataClient4
{
public:
    IPC_MediaDataClient4(void);
    ~IPC_MediaDataClient4(void);

    GMI_RESULT Initialize  ( uint16_t Local_UDP_Port, uint32_t ApplicationId );
    GMI_RESULT Deinitialize();

    // notify server of new client, server check if user use pull mode or not, to determine if or not send notify to user when new data come.
    GMI_RESULT Register    ( uint16_t Server_UDP_Port, uint32_t MediaType, uint32_t MediaId, boolean_t PullMode, MEDIA_DATA_CALLBAK Callback, void_t *UserData );
    // notify server of unregister
    GMI_RESULT Unregister  ();
    // read media data from server
    GMI_RESULT Read        ( void_t *Frame, size_t *FrameLength, struct timeval *FrameTS, void_t *ExtraData, uint32_t *ExtraDataLength, uint32_t Timeout = 40/* ms unit */ );
    // write media data to server
    GMI_RESULT Write       ( const void_t *Frame, size_t FrameLength, const struct timeval *FrameTS, const void_t *ExtraData, uint32_t ExtraDataLength );

private:
    GMI_RESULT _Read          ( void_t *Frame, uint32_t *FrameLength, struct timeval *FrameTS, void_t *ExtraData, uint32_t *ExtraDataLength, uint32_t Timeout );
    GMI_RESULT _WaitForNewData( uint32_t Timeout );
    GMI_RESULT _GetData       ( uint32_t& GetOffset, uint32_t& GetLength, uint32_t Timeout );
    GMI_RESULT _ReleaseData   ();

    GMI_RESULT WaitForReply   ( uint8_t MessageType, uint16_t MessageId, uint8_t *ReceiveBuffer, size_t *ReceiveBufferSize, long_t TryCount, boolean_t ConcernNewDataNotify );
private:
    ReferrencePtr<GMI_Socket>                                                                       m_ClientSocket;
    ReferrencePtr<IpcMediaDataUDPSession,DefaultObjectDeleter,MultipleThreadModel>                  m_UDP_Session;
    uint32_t                                                                                        m_ApplicationId;
    uint32_t                                                                                        m_MediaType;
    uint32_t                                                                                        m_MediaId;
    boolean_t                                                                                       m_PullMode;
    MEDIA_DATA_CALLBAK                                                                              m_Callback;
    void_t                                                                                          *m_UserData;
    long_t                                                                                          m_ShareMemoryKey;
    uint32_t                                                                                        m_ShareMemorySize;
    GMI_ShareMemory                                                                                 m_ShareMemory;
    void_t                                                                                          *m_MemoryPtr;

    uint8_t                                                                                         m_ReceiveBuffer[UDP_MAX_MESSAGE_LENGTH];
    boolean_t                                                                                       m_NewDataComming;
    boolean_t                                                                                       m_HasMoreData;
};
