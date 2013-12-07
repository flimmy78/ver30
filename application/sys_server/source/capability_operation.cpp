#include "capability_operation.h"
#include "log.h"
#include "gmi_config_api.h"

static uint16_t l_ReslutionTable[][2] =
{
    {RES_1080P_WIDTH, RES_1080P_HEIGHT},
    {RES_720P_WIDTH, RES_720P_HEIGHT},
    {RES_D1_PAL_WIDTH, RES_D1_PAL_HEIGHT},
    {RES_D1_NTSC_WIDTH, RES_D1_NTSC_HEIGHT},
    {RES_CIF_NTSC_WIDTH, RES_CIF_NTSC_HEIGHT},
    {RES_CIF_PAL_WIDTH, RES_CIF_PAL_HEIGHT},
    {RES_QCIF_PAL_WIDTH, RES_QCIF_PAL_HEIGHT},
    {RES_QVGA_WIDTH, RES_QVGA_HEIGHT}
};


//software capability key
#define CAPABILITY_CONFIGURABLE_PATH     "/Capability/"
#define CAPABILITY_AUTO_PATH             "/Capability/"
#define CAPABILITY_SW_MEDIA_PATH         "/Capabilities/Device/Media/"
#define CAPABILITY_SW_MEDIA_KEY_S        "<Media>"
#define CAPABILITY_SW_MEDIA_KEY_E        "</Media>"
#define STREAM_COMBINE_KEY_S             "<VideoEncCombine>"
#define STREAM_COMBINE_KEY_E             "</VideoEncCombine>"
#define STREAM_COMBINE_ONE_STREAM_KEY    "/Capabilities/Device/Media/VideoEncCombine/OneStream/Combine%d/"
#define STREAM_COMBINE_TWO_STREAM_KEY    "/Capabilities/Device/Media/VideoEncCombine/TwoStream/Combine%d/"
#define STREAM_COMBINE_THREE_STREAM_KEY  "/Capabilities/Device/Media/VideoEncCombine/ThreeStream/Combine%d/"
#define STREAM_COMBINE_FOUR_STREAM_KEY   "/Capabilities/Device/Media/VideoEncCombine/FourStream/Combine%d/"
#define STREAM_COMBINE_NAME_KEY          "Name"
#define STREAM_COMBINE_NAME              "720P25fps_576P25fps"
#define MAX_STREAM_NUM_KEY               "MaxStreamNum"
#define MAX_PIC_WIDTH_KEY                "MaxPicWidth"
#define MAX_PIC_HEIGHT_KEY               "MaxPicHeight"

//hardware key
#define SENSOR_ID_2715   "ov2715"
#define SENSOR_ID_9715   "ov9715"
#define SENSOR_ID_IMX122 "imx122"
#define SENSOR_ID_34041  "mn34041pl"
#define SENSOR_ID_TW9910 "tw9910"

#define CPU_ID_A55       "A5S_55"
#define CPU_ID_A66       "A5S_66"
#define CPU_ID_A88       "A5S_88"

#define LENS_NONE        "NONE"
#define LENS_DF003       "DF003"
#define LENS_YB22        "YB22"

//limits key
//image
#define IMAGE_KEY           "/Config/Image/%s/"
#define AETARGET_RATIO_KEY  "AeTargetRatio"
#define BRIGHTNESS_KEY      "Brightness"
#define CONTRAST_KEY        "Contrast"
#define SATURATION_KEY      "Saturation"
#define HUE_KEY             "Hue"
#define SHARPNESS_KEY       "Sharpness"


CapabilityOperation::CapabilityOperation()
{
}

CapabilityOperation::~CapabilityOperation()
{
}


GMI_RESULT CapabilityOperation::Initialize()
{
#if 0

    GMI_RESULT Result = m_Mutex.Create(NULL);
    if (FAILED(Result))
    {
        SYS_ERROR("m_Mutex.Create error\n");
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "m_Mutex.Create error\n");
        return Result;
    }

    SYS_INFO("GenerateSoftwareCapability start\n");
    Result = GenerateSoftwareCapability();
    if (FAILED(Result))
    {
        SYS_ERROR("GenerateSoftwareCapability fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "GenerateSoftwareCapability fail, Result = 0x%lx\n", Result);
        return Result;
    }
    SYS_INFO("GenerateSoftwareCapability end\n");
#endif

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::Deinitialize()
{
    //m_Mutex.Destroy();
    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetIrCutModeDnThr(int8_t *IrcutMode, int8_t *DayToNightThr, int8_t *NightToDayThr)
{
    SYS_INFO("%s in .......\n", __func__);
    boolean_t Exist = false;
    GMI_RESULT Result = FileIsExist(GMI_FACTORY_SETTING_CONFIG_FILE_NAME, &Exist);
    if (FAILED(Result))
    {
        SYS_ERROR("FileIsExist fail,Result = 0x%lx\n",Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "FileIsExist fail,Result = 0x%lx\n",Result);
        return Result;
    }
    if (!Exist)
    {
        SYS_INFO("%s not exist\n", GMI_FACTORY_SETTING_CONFIG_FILE_NAME);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "%s not exist\n", LIMITS_FILE_NAME);
        return GMI_FAIL;
    }

    FD_HANDLE  Handle;
    Result = GMI_XmlOpen(GMI_FACTORY_SETTING_CONFIG_FILE_NAME, &Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    char_t Path[128];
    memset(Path, 0, sizeof(Path));
    strcpy(Path, VIDEO_IRCUT_MODE_PATH);
    Result = GMI_XmlRead(Handle, (const char_t*)Path, VIDEO_IRCUT_MODE_KEY, VIDEO_IRCUT_MODE, IrcutMode, GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, (const char_t*)Path, VIDEO_IRCUT_DAYTONIGHT_THR_KEY, VIDEO_IRCUT_DAYTONIGHT_THR, DayToNightThr, GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, (const char_t*)Path, VIDEO_IRCUT_NIGHTTODAY_THR_KEY, VIDEO_IRCUT_NIGHTTODAY_THR, NightToDayThr, GMI_CONFIG_READ_ONLY);
    if (FAILED(Result))
    {
        GMI_XmlFileSave(Handle);
        return Result;
    }

    Result = GMI_XmlFileSave(Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    SYS_INFO("%s normal out .......\n", __func__);
    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GenerateSoftwareCapability()
{
    int32_t MaxStreamNum;
    int32_t MaxPicWidth;
    int32_t MaxPicHeight;

    GMI_RESULT Result = GetMediaParam(&MaxStreamNum, &MaxPicWidth, &MaxPicHeight);
    if (FAILED(Result))
    {
        SYS_ERROR("get media parameter form config capalibity fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "get media parameter form config capalibity fail, Result = 0x%lx\n", Result);
        return Result;
    }

    Result = CheckVideoReslution((uint16_t)MaxPicWidth, (uint16_t)MaxPicHeight);
    if (FAILED(Result))
    {
        SYS_ERROR("check video resolution fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "check video resolution fail, Result = 0x%lx\n", Result);
        return Result;
    }

    //get stream combine
    char_t *Combine = NULL;
    int32_t CombineLen;
    Result = GetStreamCombine(MaxPicHeight, &Combine, &CombineLen);
    if (FAILED(Result))
    {
        SYS_ERROR("read stream combine fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "read stream combine fail, Result = 0x%lx\n", Result);
        return Result;
    }

    //write correct stream combine to capability_software.xml
    Result = WriteStreamCombineToCapSw(Combine, CombineLen);
    if (FAILED(Result))
    {
        BaseMemoryManager::Instance().Deletes<char_t>(Combine);
        SYS_ERROR("write stream combine to software capability fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "write stream combine to software capability fail, Result = 0x%lx\n", Result);
        return Result;
    }
    BaseMemoryManager::Instance().Deletes<char_t>(Combine);

    //add the maxstream maxpicwidth, maxpicheight, this step exec must after "WriteStreamCombineToCapSw"
    Result = WriteMediaParamToCapSw(MaxStreamNum, MaxPicWidth, MaxPicHeight);
    if (FAILED(Result))
    {
        SYS_ERROR("write media parameter to sofware capability fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "open %s fail,Result = 0x%lx\n", Result);
        return Result;
    }

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::ExcuteImportFile(SysPkgConfigFileInfo *SysConfigFilePtr)
{
    if (NULL == SysConfigFilePtr)
    {
        return GMI_INVALID_PARAMETER;
    }
    SYS_INFO("s_FileTmpPath    = %s\n", SysConfigFilePtr->s_FileTmpPath);
    SYS_INFO("s_FileTargetPath = %s\n", SysConfigFilePtr->s_FileTargetPath);
    SYS_INFO("s_Persit         = %d\n", SysConfigFilePtr->s_Persit);
    SYS_INFO("s_Encrypt        = %d\n", SysConfigFilePtr->s_Encrypt);

    SYS_INFO("Import %s\n", SysConfigFilePtr->s_FileTmpPath);
    boolean_t Exist;

    GMI_RESULT Result = FileIsExist(SysConfigFilePtr->s_FileTmpPath, &Exist);
    if (FAILED(Result))
    {
        SYS_ERROR("FileIsExist fail,Result = 0x%lx\n",Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "FileIsExist fail,Result = 0x%lx\n",Result);
        return Result;
    }
    if (!Exist)
    {
        SYS_INFO("%s not exist\n", SysConfigFilePtr->s_FileTmpPath);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "%s not exist\n", SysConfigFilePtr->s_FileTmpPath);
        return GMI_FAIL;
    }

    char_t Cmd[128];
    memset(Cmd, 0, sizeof(Cmd));
    snprintf(Cmd, sizeof(Cmd), "mv %s %s", SysConfigFilePtr->s_FileTmpPath, SysConfigFilePtr->s_FileTargetPath);
    system(Cmd);

    if (0 == strcmp(CAPABILITY_CONFIGURABLE_FILE_NAME, SysConfigFilePtr->s_FileTargetPath))
    {
        Result = GenerateSoftwareCapability();
        if (FAILED(Result))
        {
            return Result;
        }

        //delete user setting when generate capability.
        memset(Cmd, 0, sizeof(Cmd));
        snprintf(Cmd, sizeof(Cmd), "rm -f %s", GMI_SETTING_CONFIG_FILE_NAME);
        system(Cmd);
    }

    if (0 == SysConfigFilePtr->s_Persit)
    {
        memset(Cmd, 0, sizeof(Cmd));
        snprintf(Cmd, sizeof(Cmd), "rm -f %s", SysConfigFilePtr->s_FileTargetPath);
        system(Cmd);
    }

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetVideoMaxCapability(int32_t *MaxStreamNum, int32_t *MaxPicWidth, int32_t *MaxPicHeight)
{
    FD_HANDLE  Handle;

    GMI_RESULT Result = GMI_XmlOpen(CAPABILITY_SW_FILE_NAME, &Handle);
    if (FAILED(Result))
    {
        return Result;
    }
    Result = GMI_XmlRead(Handle, CAPABILITY_SW_MEDIA_PATH, MAX_STREAM_NUM_KEY, VIDEO_ENCODE_STREAM_NUM, MaxStreamNum, GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, CAPABILITY_SW_MEDIA_PATH, MAX_PIC_WIDTH_KEY,  RES_720P_WIDTH,    MaxPicWidth,  GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, CAPABILITY_SW_MEDIA_PATH, MAX_PIC_HEIGHT_KEY, RES_720P_HEIGHT,   MaxPicHeight, GMI_CONFIG_READ_ONLY);
    if (FAILED(Result))
    {
        GMI_XmlFileSave(Handle);
        return Result;
    }

    Result = GMI_XmlFileSave(Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetVideoParams(int32_t StreamNum, int32_t CombineNo, int32_t Res[16][4])
{
    char_t Path[100];

    memset(Path, 0, sizeof(Path));
    switch (StreamNum)
    {
    case 1:
        snprintf(Path, sizeof(Path), STREAM_COMBINE_ONE_STREAM_KEY, CombineNo);
        break;
    case 2:
        snprintf(Path, sizeof(Path), STREAM_COMBINE_TWO_STREAM_KEY, CombineNo);
        break;
    case 3:
        snprintf(Path, sizeof(Path), STREAM_COMBINE_THREE_STREAM_KEY, CombineNo);
        break;
    case 4:
        snprintf(Path, sizeof(Path), STREAM_COMBINE_FOUR_STREAM_KEY, CombineNo);
        break;
    default:
        return GMI_NOT_SUPPORT;
    }

    FD_HANDLE  Handle;
    GMI_RESULT Result = GMI_XmlOpen(CAPABILITY_SW_FILE_NAME, &Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    SYS_INFO("path %s\n", Path);
    char_t Name[100];
    memset(Name, 0, sizeof(Name));
    Result = GMI_XmlRead(Handle, Path, STREAM_COMBINE_NAME_KEY, STREAM_COMBINE_NAME, Name, GMI_CONFIG_READ_ONLY);
    if (FAILED(Result))
    {
        GMI_XmlFileSave(Handle);
        return Result;
    }

    Result = GMI_XmlFileSave(Handle);
    if (FAILED(Result))
    {
        return Result;
    }


    char_t *NameTmp = NULL;
    char_t *ResTmp = NULL;
    char_t *Frames = NULL;
    uint8_t Nel = 1;
    int32_t Len = strlen(Name);
    NameTmp = Name;
    while (strsep(&NameTmp, "_"))
    {
        if (NameTmp)
        {
            Nel++;
        }
    }
    if (Nel != StreamNum)
    {
        SYS_ERROR("Get StreamNum %d, but RealStreamNum %d\n",  Nel, StreamNum);
        return GMI_FAIL;
    }

    uint32_t i = 0;
    for (NameTmp = Name; NameTmp < (Name+Len);)
    {
        ResTmp = Frames = NameTmp;
        for (NameTmp += strlen(NameTmp); NameTmp < (Name+Len) && !*NameTmp; NameTmp++);
        char_t *CIF_Ptr = NULL;
        if (NULL != (CIF_Ptr = strstr(ResTmp, "CIF")))
        {
            Res[i][1] = RES_CIF_PAL_HEIGHT;
            Frames = CIF_Ptr + strlen("CIF");
            char_t *P = strstr(Frames, "fps");
            *P = '\0';
            Res[i][2] = atoi(Frames);
        }
        else
        {
            ResTmp = strsep(&Frames, "P");
            if (NULL == Frames)
            {
                return GMI_INVALID_OPERATION;
            }
            char_t *P = strstr(Frames, "fps");
            *P = '\0';
            Res[i][1] = atoi(ResTmp);
            Res[i][2] = atoi(Frames);
        }

        uint32_t Row;
        for (Row = 0; Row < sizeof(l_ReslutionTable)/(sizeof(l_ReslutionTable[0][0])*2); Row++)
        {
            if (Res[i][1] == l_ReslutionTable[Row][1])
            {
                Res[i][0] = l_ReslutionTable[Row][0];
                break;
            }
        }
        SYS_INFO("[%s]:stream%d width=%d height=%d FrameRate=%d\n", __func__, i, Res[i][0], Res[i][1], Res[i][2]);
        i++;
    }

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetImageParams(int32_t Imgs[32])
{
    SYS_INFO("%s in .......\n", __func__);
    if (NULL == Imgs)
    {
        return GMI_INVALID_PARAMETER;
    }

    boolean_t Exist = false;
    GMI_RESULT Result = FileIsExist(LIMITS_FILE_NAME, &Exist);
    if (FAILED(Result))
    {
        SYS_ERROR("FileIsExist fail,Result = 0x%lx\n",Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "FileIsExist fail,Result = 0x%lx\n",Result);
        return Result;
    }
    if (!Exist)
    {
        SYS_INFO("%s not exist\n", LIMITS_FILE_NAME);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "%s not exist\n", LIMITS_FILE_NAME);
        return GMI_FAIL;
    }

    char_t SensorName[64];
    memset(SensorName, 0, sizeof(SensorName));
    Result = GetSensorName(SensorName);
    if (FAILED(Result))
    {
        SYS_INFO("get sensor info fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "get sensor info fail, Result = 0x%lx\n", Result);
        return Result;
    }

    FD_HANDLE  Handle;
    Result = GMI_XmlOpen(LIMITS_FILE_NAME, &Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    char_t Path[128];
    memset(Path, 0, sizeof(Path));
    sprintf(Path, IMAGE_KEY, SensorName);
    Result = GMI_XmlRead(Handle, Path, BRIGHTNESS_KEY, VIDEO_SOURCE_IMAGE_BRIGHTNESS, &Imgs[0], GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, Path, CONTRAST_KEY, VIDEO_SOURCE_IMAGE_CONTRAST, &Imgs[1], GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, Path, SATURATION_KEY, VIDEO_SOURCE_IMAGE_SATURATION, &Imgs[2], GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, Path, HUE_KEY, VIDEO_SOURCE_IMAGE_HUE, &Imgs[3], GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, Path, SHARPNESS_KEY, VIDEO_SOURCE_IMAGE_SHARPNESS, &Imgs[4], GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, Path, AETARGET_RATIO_KEY, VIDEO_IMAGE_ADVANCE_AETARGETRATIO, &Imgs[5], GMI_CONFIG_READ_ONLY);

    if (FAILED(Result))
    {
        GMI_XmlFileSave(Handle);
        return Result;
    }

    Result = GMI_XmlFileSave(Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    SYS_INFO("%s normal out .......\n", __func__);
    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetPtzSpeed(char_t HSpeed[10][64], char_t VSpeed[10][64])
{
    SYS_INFO("%s in .......\n", __func__);
    if (NULL == HSpeed
            || NULL == VSpeed)
    {
        return GMI_INVALID_PARAMETER;
    }

    boolean_t Exist = false;
    GMI_RESULT Result = FileIsExist(GMI_FACTORY_SETTING_CONFIG_FILE_NAME, &Exist);
    if (FAILED(Result))
    {
        SYS_ERROR("FileIsExist fail,Result = 0x%lx\n",Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "FileIsExist fail,Result = 0x%lx\n",Result);
        return Result;
    }
    if (!Exist)
    {
        SYS_INFO("%s not exist\n", GMI_FACTORY_SETTING_CONFIG_FILE_NAME);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "%s not exist\n", LIMITS_FILE_NAME);
        return GMI_FAIL;
    }

    FD_HANDLE  Handle;
    Result = GMI_XmlOpen(GMI_FACTORY_SETTING_CONFIG_FILE_NAME, &Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    char_t PTZSpeedPath[64];
    memset(PTZSpeedPath, 0, sizeof(PTZSpeedPath));
    strcpy(PTZSpeedPath, PTZ_SPEED_MAP_PATH);
    char_t HKey[32];
    char_t VKey[32];
    const char_t *Speed = "50,";
    for (int32_t i = 0; i < 10; i++)
    {
        memset(HKey, 0, sizeof(HKey));
        sprintf(HKey, PTZ_H_SPEED_KEY, i);
        memset(VKey, 0, sizeof(VKey));
        sprintf(VKey, PTZ_V_SPEED_KEY, i);
        Result = GMI_XmlRead(Handle, (const char_t*)PTZSpeedPath, (const char_t*)HKey, Speed, HSpeed[i], GMI_CONFIG_READ_ONLY);
        if (0 == strcmp(Speed, HSpeed[i]))
        {
            SYS_ERROR("read HSpeed fail\n");
            DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "read HSpeed fail\n");
            return GMI_FAIL;
        }

        Result = GMI_XmlRead(Handle, (const char_t*)PTZSpeedPath, (const char_t*)VKey, Speed, VSpeed[i], GMI_CONFIG_READ_ONLY);
        if (0 == strcmp(Speed, VSpeed[i]))
        {
            SYS_ERROR("read VSpeed fail\n");
            DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "read VSpeed fail\n");
            return GMI_FAIL;
        }
    }

    if (FAILED(Result))
    {
        GMI_XmlFileSave(Handle);
        return Result;
    }

    Result = GMI_XmlFileSave(Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    SYS_INFO("%s normal out .......\n", __func__);
    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetSensorName(char_t SensorName[64])
{
    GMI_RESULT Result;
    FD_HANDLE  Handle;
    char_t     Cpu[64];
    char_t     Sensor[64];
    char_t     Lens[64];

    Result = GMI_XmlOpen(CAPABILITY_AUTO_FILE_NAME, &Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    Result = GMI_XmlRead(Handle, CAPABILITY_AUTO_PATH, HW_CPU_KEY,    HW_CPU,    Cpu,    GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, CAPABILITY_AUTO_PATH, HW_SENSOR_KEY, HW_SENSOR, Sensor, GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, CAPABILITY_AUTO_PATH, HW_LENS_KEY,   HW_LENS,   Lens,   GMI_CONFIG_READ_ONLY);

    if (FAILED(Result))
    {
        GMI_XmlFileSave(Handle);
        return Result;
    }

    Result = GMI_XmlFileSave(Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    memcpy(SensorName, Sensor, sizeof(Sensor));

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetHwAutoDetectInfo(SysPkgComponents *SysComponents)
{
    GMI_RESULT Result;
    FD_HANDLE  Handle;
    char_t     Cpu[64];
    char_t     Sensor[64];
    char_t     Lens[64];

    Result = GMI_XmlOpen(CAPABILITY_AUTO_FILE_NAME, &Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    Result = GMI_XmlRead(Handle, CAPABILITY_AUTO_PATH, HW_CPU_KEY,    HW_CPU,    Cpu,    GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, CAPABILITY_AUTO_PATH, HW_SENSOR_KEY, HW_SENSOR, Sensor, GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(Handle, CAPABILITY_AUTO_PATH, HW_LENS_KEY,   HW_LENS,   Lens,   GMI_CONFIG_READ_ONLY);

    if (FAILED(Result))
    {
        GMI_XmlFileSave(Handle);
        return Result;
    }

    Result = GMI_XmlFileSave(Handle);
    if (FAILED(Result))
    {
        return Result;
    }

    SYS_INFO("Cpu %s, Sensor %s, Lens %s\n", Cpu, Sensor, Lens);

    if (strcmp(Sensor, SENSOR_ID_2715) == 0)
    {
        SysComponents->s_SensorId = e_SENSOR_OV2715;
    }
    else if (strcmp(Sensor, SENSOR_ID_9715) == 0)
    {
        SysComponents->s_SensorId = e_SENSOR_OV9715;
    }
    else if (strcmp(Sensor, SENSOR_ID_34041) == 0)
    {
        SysComponents->s_SensorId = e_SENSOR_MN34041;
    }
    else if (strcmp(Sensor, SENSOR_ID_IMX122) == 0)
    {
        SysComponents->s_SensorId = e_SENSOR_IMX122;
    }
    else
    {
        SysComponents->s_SensorId = e_SENSOR_OV9715;
    }

    if (strcmp(Cpu, CPU_ID_A88) == 0)
    {
        SysComponents->s_CpuId = e_CPU_A5S_88;
    }
    else if (strcmp(Cpu, CPU_ID_A66) == 0)
    {
        SysComponents->s_CpuId = e_CPU_A5S_66;
    }
    else
    {
        SysComponents->s_CpuId = e_CPU_A5S_55;
    }

    if (strcmp(Lens, LENS_DF003) == 0)
    {
        SysComponents->s_ZoomLensId = e_ZOOM_LENS_DF003;
    }
    else if (strcmp(Lens, LENS_YB22) == 0)
    {
        SysComponents->s_ZoomLensId = e_ZOOM_LENS_YB22;
    }
    else
    {
        SysComponents->s_ZoomLensId = e_ZOOM_LENS_NONE;
    }

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::CheckVideoReslution(uint16_t Width, uint16_t Height)
{
    if (Height%4 != 0
            || Width%4 != 0)
    {
        return GMI_INVALID_PARAMETER;
    }

    //sys components
    SysPkgComponents SysComponents;
    GMI_RESULT Result = GetHwAutoDetectInfo(&SysComponents);
    if (FAILED(Result))
    {
        SYS_ERROR("GetHwAutoDetectInfo fail, Result = 0x%lx\n", Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "GetHwAutoDetectInfo fail, Result = 0x%lx\n", Result);
        return Result;
    }

    //accrroding hw capabilities, check video encode width and height
    if (e_CPU_A5S_66 == SysComponents.s_CpuId
            || e_CPU_A5S_88 == SysComponents.s_CpuId)
    {
        if (Height > RES_1080P_HEIGHT
                || Width > RES_1080P_WIDTH)
        {
            SYS_ERROR("Height %d error, Width %d error\n", Height, Width);
            DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "Height %d error, Width %d error\n", Height, Width);
            return GMI_NOT_SUPPORT;
        }
    }
    else if (e_CPU_A5S_55 == SysComponents.s_CpuId)
    {
        if (Height > RES_720P_HEIGHT
                || Width > RES_720P_WIDTH)
        {
            SYS_ERROR("Height %d error, Width %d error\n", Height, Width);
            DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "Height %d error, Width %d error\n", Height, Width);
            return GMI_NOT_SUPPORT;
        }
    }
    else
    {
        SYS_ERROR("SysComponents.s_CpuId %d not support\n", SysComponents.s_CpuId);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "SysComponents.s_CpuId %d not support\n", SysComponents.s_CpuId);
        return GMI_NOT_SUPPORT;
    }

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetMediaParam(int32_t *MaxStreamNumPtr, int32_t *MaxPicWidthPtr, int32_t *MaxPicHeightPtr)
{
    boolean_t CapConfigExist;
    GMI_RESULT Result = FileIsExist(CAPABILITY_CONFIGURABLE_FILE_NAME, &CapConfigExist);
    if (FAILED(Result))
    {
        SYS_ERROR("FileIsExist fail,Result = 0x%lx\n",Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "FileIsExist fail,Result = 0x%lx\n",Result);
        return Result;
    }
    if (!CapConfigExist)
    {
        SYS_INFO("%s not exist\n", CAPABILITY_CONFIGURABLE_FILE_NAME);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "%s not exist\n", CAPABILITY_CONFIGURABLE_FILE_NAME);
        return Result;
    }

    FD_HANDLE CapConfigHd;
    int32_t MaxStreamNum;
    int32_t MaxPicWidth;
    int32_t MaxPicHeight;

    //open configurable file
    Result = GMI_XmlOpen(CAPABILITY_CONFIGURABLE_FILE_NAME, &CapConfigHd);
    if (FAILED(Result))
    {
        SYS_ERROR("open %s fail,Result = 0x%lx\n", CAPABILITY_CONFIGURABLE_FILE_NAME, Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "open %s fail,Result = 0x%lx\n", CAPABILITY_CONFIGURABLE_FILE_NAME, Result);
        return Result;
    }

    Result = GMI_XmlRead(CapConfigHd, CAPABILITY_CONFIGURABLE_PATH, MAX_STREAM_NUM_KEY, 2, &MaxStreamNum, GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(CapConfigHd, CAPABILITY_CONFIGURABLE_PATH, MAX_PIC_WIDTH_KEY, 1280, &MaxPicWidth, GMI_CONFIG_READ_ONLY);
    Result = GMI_XmlRead(CapConfigHd, CAPABILITY_CONFIGURABLE_PATH, MAX_PIC_HEIGHT_KEY, 720, &MaxPicHeight, GMI_CONFIG_READ_ONLY);
    if (FAILED(Result))
    {
        GMI_XmlFileSave(CapConfigHd);
        return Result;
    }

    Result = GMI_XmlFileSave(CapConfigHd);
    if (FAILED(Result))
    {
        return Result;
    }

    *MaxStreamNumPtr = MaxStreamNum;
    *MaxPicWidthPtr  = MaxPicWidth;
    *MaxPicHeightPtr = MaxPicHeight;

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::WriteMediaParamToCapSw(int32_t MaxStreamNum, int32_t MaxPicWidth, int32_t MaxPicHeight)
{
    FD_HANDLE CapSwHd;

    //open software capbility
    GMI_RESULT Result = GMI_XmlOpen(CAPABILITY_SW_FILE_NAME, &CapSwHd);
    if (FAILED(Result))
    {
        return Result;
    }

    Result = GMI_XmlWrite(CapSwHd, CAPABILITY_SW_MEDIA_PATH, MAX_STREAM_NUM_KEY,   (const int32_t)MaxStreamNum);
    Result = GMI_XmlWrite(CapSwHd, CAPABILITY_SW_MEDIA_PATH, MAX_PIC_WIDTH_KEY,    (const int32_t)MaxPicWidth);
    Result = GMI_XmlWrite(CapSwHd, CAPABILITY_SW_MEDIA_PATH, MAX_PIC_HEIGHT_KEY,   (const int32_t)MaxPicHeight);
    if (FAILED(Result))
    {
        GMI_XmlFileSave(CapSwHd);
        return Result;
    }

    Result = GMI_XmlFileSave(CapSwHd);
    if (FAILED(Result))
    {
        return Result;
    }

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::GetStreamCombine(int32_t MaxPicHeight, char_t **Combine,  int32_t *CombineLen)
{
    char_t CombineFile[100];

    memset(CombineFile, 0, sizeof(CombineFile));
    sprintf(CombineFile, "/opt/config/%dp_combine.xml", MaxPicHeight);

    boolean_t Exist = false;
    GMI_RESULT Result = FileIsExist(CombineFile, &Exist);
    if (FAILED(Result))
    {
        SYS_ERROR("FileIsExist fail,Result = 0x%lx\n",Result);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "FileIsExist fail,Result = 0x%lx\n",Result);
        return Result;
    }
    if (!Exist)
    {
        SYS_INFO("%s not exist\n", CombineFile);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "%s not exist\n", CombineFile);
        return Result;
    }

    FILE *Fp = NULL;
    Fp = fopen(CombineFile, "rb");
    if (NULL == Fp)
    {
        SYS_ERROR("open %s fail\n", CombineFile);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "open %s fail\n", CombineFile);
        return GMI_FAIL;
    }

    fseek(Fp, 0, SEEK_END);
    int32_t FileSize = ftell(Fp);
    fseek(Fp, 0, SEEK_SET);
    ReferrencePtr<char_t, DefaultObjectsDeleter>Buffer(BaseMemoryManager::Instance().News<char_t>(FileSize));
    if (NULL == Buffer.GetPtr())
    {
        if (NULL != Fp)
        {
            fclose(Fp);
            Fp = NULL;
        }
        SYS_ERROR("Buffer News fail\n");
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "Buffer News fail\n");
        return GMI_OUT_OF_MEMORY;
    }

    int32_t Read = fread(Buffer.GetPtr(), 1, FileSize, Fp);
    if (Read != FileSize)
    {
        if (NULL != Fp)
        {
            fclose(Fp);
            Fp = NULL;
        }
        SYS_ERROR("fread fail, Read %d, FileSize %d\n", Read, FileSize);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "fread fail, Read %d, FileSize %d\n", Read, FileSize);
        return GMI_FAIL;
    }

    const char_t *Key = STREAM_COMBINE_KEY_S;
    char_t *Pos1 = strstr(Buffer.GetPtr(), Key);
    const char_t *BrotherKey = STREAM_COMBINE_KEY_E;
    char_t *Pos2 = strstr(Pos1, BrotherKey);
    Pos2 += strlen(BrotherKey);
    int32_t Len = Pos2 - Pos1;

    *Combine = BaseMemoryManager::Instance().News<char_t>(Len);
    memcpy(*Combine, Pos1, Len);
    *CombineLen = Len;

    if (NULL != Fp)
    {
        fclose(Fp);
        Fp = NULL;
    }
    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::WriteStreamCombineToCapSw(char_t *Combine,  int32_t CombineLen)
{
    int32_t Fd = open(CAPABILITY_SW_FILE_NAME, O_CREAT|O_RDWR);
    if (0 > Fd)
    {
        SYS_ERROR("open %s fail, Fd %d\n", CAPABILITY_SW_FILE_NAME, Fd);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "open %s fail, Fd %d\n", CAPABILITY_SW_FILE_NAME, Fd);
        return GMI_FAIL;
    }

    int32_t SwFileSize = lseek(Fd, 0, SEEK_END);
    lseek(Fd, 0, SEEK_SET);

    ReferrencePtr<char_t, DefaultObjectsDeleter>ToBuffer(BaseMemoryManager::Instance().News<char_t>(SwFileSize + CombineLen));
    if (NULL == ToBuffer.GetPtr())
    {
        if (0 < Fd)
        {
            close(Fd);
            Fd = 0;
        }
        SYS_ERROR("ToBuffer News fail\n");
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "ToBuffer News fail\n");
        return GMI_OUT_OF_MEMORY;
    }
    memset(ToBuffer.GetPtr(), 0, SwFileSize + CombineLen);

    ReferrencePtr<char_t, DefaultObjectsDeleter>SrcBuffer(BaseMemoryManager::Instance().News<char_t>(SwFileSize));
    if (NULL == SrcBuffer.GetPtr())
    {
        if (0 < Fd)
        {
            close(Fd);
            Fd = 0;
        }
        SYS_ERROR("SrcBuffer News fail\n");
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "SrcBuffer News fail\n");
        return GMI_OUT_OF_MEMORY;
    }
    memset(SrcBuffer.GetPtr(), 0, SwFileSize);

    int32_t Ret = read(Fd, SrcBuffer.GetPtr(), SwFileSize);
    if (Ret != SwFileSize)
    {
        if (0 < Fd)
        {
            close(Fd);
            Fd = 0;
        }
        SYS_ERROR("read fail, Read %d, FileSize %d\n", Ret, SwFileSize);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "read fail, Read %d, FileSize %d\n", Ret, SwFileSize);
        return GMI_FAIL;
    }

    if (0 < Fd)
    {
        close(Fd);
        Fd = 0;
    }

    const char_t *MediaKey = CAPABILITY_SW_MEDIA_KEY_S;
    char_t *Pos1 = strstr(SrcBuffer.GetPtr(), MediaKey);
    if (NULL == Pos1)
    {
        SYS_ERROR("can not find key %s\n", MediaKey);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "can not find key %s\n", MediaKey);
        return GMI_FAIL;
    }
    Pos1 += strlen(MediaKey);
    int32_t CurLen = Pos1-SrcBuffer.GetPtr();
    memcpy(ToBuffer.GetPtr(),  SrcBuffer.GetPtr(), CurLen);
    memcpy(ToBuffer.GetPtr() + CurLen, Combine, CombineLen);

    const char_t *MediaBrotherKey = CAPABILITY_SW_MEDIA_KEY_E;
    char_t *Pos2 = strstr(SrcBuffer.GetPtr(), MediaBrotherKey);
    CurLen += CombineLen;
    int32_t LeftLen = SwFileSize - (Pos2 - SrcBuffer.GetPtr());
    memcpy(ToBuffer.GetPtr() + CurLen, Pos2, LeftLen);
    int32_t TotalLen = CurLen + LeftLen;

    //Lock();
    Fd = open(CAPABILITY_SW_FILE_NAME, O_WRONLY|O_CREAT|O_TRUNC);
    if (0 > Fd)
    {
        Unlock();
        SYS_ERROR("open %s fail", CAPABILITY_SW_FILE_NAME);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "open %s fail", CAPABILITY_SW_FILE_NAME);
        return GMI_FAIL;
    }

    Ret = write(Fd, ToBuffer.GetPtr(), TotalLen);
    if (Ret != TotalLen)
    {
        Unlock();
        SYS_ERROR("write %s fail, write %d, FileSize %d\n", CAPABILITY_SW_FILE_NAME, Ret, TotalLen);
        DEBUG_LOG(g_DefaultLogClient, e_DebugLogLevel_Exception, "write %s fail, write %d, FileSize %d\n", CAPABILITY_SW_FILE_NAME, Ret, TotalLen);
        return GMI_FAIL;
    }

    if (0 < Fd)
    {
        close(Fd);
        Fd = 0;
    }
    //Unlock();

    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::FileIsExist(const char_t *File, boolean_t *Exist)
{
    if (NULL == File)
    {
        return GMI_INVALID_PARAMETER;
    }

    FILE *Fp = NULL;

    Fp = fopen(File, "rb");
    if (NULL == Fp)
    {
        *Exist = false;
    }
    else
    {
        *Exist = true;
    }

    if (NULL != Fp)
    {
        fclose(Fp);
        Fp = NULL;
    }

    return GMI_SUCCESS;
}

GMI_RESULT CapabilityOperation::Lock()
{
    //m_Mutex.Lock(TIMEOUT_INFINITE);
    return GMI_SUCCESS;
}


GMI_RESULT CapabilityOperation::Unlock()
{
    //m_Mutex.Unlock();
    return GMI_SUCCESS;
}

