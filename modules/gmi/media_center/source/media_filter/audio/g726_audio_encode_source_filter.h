#pragma once

#include "audio_source_filter.h"

#define SAVE_G726_AUDIO_ENCODE_FILE 0

class G726_AudioEncodeSourceFilter : public AudioSourceFilter
{
protected:
    G726_AudioEncodeSourceFilter(void);
    virtual ~G726_AudioEncodeSourceFilter(void);

public:
    static  G726_AudioEncodeSourceFilter*  CreateNew();
    friend class BaseMemoryManager;

    virtual GMI_RESULT	Initialize( int32_t FilterId, const char_t *FilterName, size_t FilterNameLength, void_t *Argument, size_t ArgumentSize );
    virtual GMI_RESULT  Deinitialize();
    virtual GMI_RESULT  Play();
    virtual GMI_RESULT  Stop();

    GMI_RESULT GetEncodeConfig( void_t *EncodeParameter, size_t *EncodeParameterLength );
    GMI_RESULT SetEncodeConfig( const void_t *EncodeParameter, size_t EncodeParameterLength );

private:
    static void_t MediaEncCallBack( void_t *UserDataPtr, MediaEncInfo *EncInfo, ExtMediaEncInfo *ExtEncInfo );

private:
    FD_HANDLE                                m_HardwareSource;
#if SAVE_G726_AUDIO_ENCODE_FILE
    FILE                                     *m_AudioFile;
#endif
};
