#include "media_center_set_operation_with_one_parameter_command_executor.h"

#include "application_packet.h"

MediaCenterSetOperationWithOneParameterCommandExecutor::MediaCenterSetOperationWithOneParameterCommandExecutor( uint32_t CommandId, enum CommandType Type )
    : MediaCenterCommandExecutor( CommandId, Type )
    , m_Token( 0 )
    , m_Parameter1( 0 )
{
}

MediaCenterSetOperationWithOneParameterCommandExecutor::~MediaCenterSetOperationWithOneParameterCommandExecutor(void)
{
}

GMI_RESULT MediaCenterSetOperationWithOneParameterCommandExecutor::Create( ReferrencePtr<BasePacket>& Packet, SafePtr<BaseCommandExecutor>& CommandExecutor )
{
    MediaCenterSetOperationWithOneParameterCommandExecutor *SetOperationWithOneParameterCommandExecutor = (MediaCenterSetOperationWithOneParameterCommandExecutor*) CommandExecutor.GetPtr();

    SetOperationWithOneParameterCommandExecutor->m_Session = Packet->GetSession();
    SetOperationWithOneParameterCommandExecutor->m_Reply = Packet->Clone();
    SetOperationWithOneParameterCommandExecutor->SetParameter( m_MediaCenter );

    uint8_t *Offset = Packet->GetPacketPayloadBuffer();

    BIGENDIAN_TO_UINT( Offset, SetOperationWithOneParameterCommandExecutor->m_Token );               // Token
    Offset += sizeof(uint32_t);

    BIGENDIAN_TO_UINT( Offset, SetOperationWithOneParameterCommandExecutor->m_Parameter1 );          // Parameter1
    Offset += sizeof(uint32_t);

    return GMI_SUCCESS;
}

GMI_RESULT MediaCenterSetOperationWithOneParameterCommandExecutor::Execute()
{
    uint16_t PayloadSize = sizeof(uint32_t);
    ReferrencePtr<ApplicationPacket> Reply( BaseMemoryManager::Instance().New<ApplicationPacket>() );
    if ( NULL == Reply.GetPtr() )
    {
        return GMI_OUT_OF_MEMORY;
    }

    GMI_RESULT Result = Reply->AllocatePacketBuffer( 0, PayloadSize );
    if ( FAILED( Result ) )
    {
        return Result;
    }

    ApplicationPacket *CommandPacket = (ApplicationPacket*) m_Reply.GetPtr();

    uint8_t MessageType = GMI_MESSAGE_TYPE_REPLY;

    Result = ApplicationPacket::FillPacketHeader( Reply->GetPacketHeaderBuffer(), CommandPacket->GetMessageTag(), CommandPacket->GetHeaderFlags(),
             CommandPacket->GetMajorVersion(), CommandPacket->GetMinorVersion(), CommandPacket->GetSequenceNumber(),
             MessageType, CommandPacket->GetMessageId() );
    if ( FAILED( Result ) )
    {
        return Result;
    }

    uint8_t *PayloadBuffer = Reply->GetPacketPayloadBuffer();
    uint8_t *Offset = PayloadBuffer;

    UINT_TO_BIGENDIAN( m_Result, Offset );				        // Result
    Offset += sizeof(uint32_t);

    Result =  Reply->CalculatePacketChecksum();
    if ( FAILED( Result ) )
    {
        return Result;
    }

    m_Reply = Reply;

    return GMI_SUCCESS;
}