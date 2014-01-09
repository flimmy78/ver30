
// ipc_fw_v3x_resource.h
// define resource id or range for ipc_fw_v3x project
// note: these value are only default value, program can use other value.

#if !defined( IPC_FW_V3X_RESOURCE )
#define IPC_FW_V3X_RESOURCE

#define GMI_RESOURCE_CONFIG_FILE_NAME               "/opt/config/gmi_resource.xml"

#define GMI_EXTERN_NETWORK_PORT_PATH                "/Config/NetworkPort/Extern/"
#define GMI_INNER_NETWORK_PORT_PATH                 "/Config/NetworkPort/Inner/"

//extern network port
#define GMI_RTSP_SERVER_TCP_PORT_KEY                "RTSP_ServerPort"
#define GMI_DAEMON_UPDATE_SERVER_PORT_KEY           "UpdatePort"
#define GMI_HTTP_SERVER_PORT_KEY                    "HTTP_ServerPort"
#define GMI_SDK_SERVER_PORT_KEY                     "SDK_ServerPort"

//unix socket
#define GMI_CONTROL_S_UNIX_NAME                     "/tmp/sys_server"

/************************ udp port ************************/
//daemon server
#define GMI_DAEMON_HEARDBEAT_SERVER                 56780
#define GMI_DAEMON_HEARDBEAT_LOG                    56781
#define GMI_DAEMON_HEARDBEAT_MEDIA                  56782
#define GMI_DAEMON_HEARDBEAT_TRANSPORT              56783
#define GMI_DAEMON_HEARDBEAT_CONTROL                56784
#define GMI_DAEMON_HEARDBEAT_GB28181                56785
#define GMI_DAEMON_HEARDBEAT_ONVIF                  56786
#define GMI_DAEMON_HEARDBEAT_WEB                    56787
#define GMI_DAEMON_HEARTBEAT_SDK		            56788
#define GMI_DAEMON_HEARTBEAT_AUTH		            56789
#define GMI_DAEMON_HEARTBEAT_CONFIG_TOOL            56790
#define GMI_MONITOR_TO_SDK_PORT_DEFAULT             57008
//onvif server
#define GMI_ONVIF_C_PORT                            56680
#define GMI_ONVIF_S_PORT                            56681
#define GMI_ONVIF_AUTH_PORT                         56684

//sys server
#define GMI_CONTROL_C_PORT                          56682
#define GMI_CONTROL_S_PORT                          56683
//cgi
#define GMI_CGI_C_PORT_START                        56690
#define GMI_CGI_S_PORT_START                        56700
//cgi auth port
#define GMI_CGI_AUTH_PORT                           56686
//ntp loacl listen port
#define GMI_NTP_S_PORT                              56701
//config_tool
#define GMI_CONFIG_TOOL_C_PORT                      56687
#define GMI_CONFIG_TOOL_S_PORT                      56688
#define GMI_CONFIG_TOOL_AUTH_PORT                   56689
//media center server
#define GMI_MEDIA_CENTER_SERVER_COMMAND_PORT        56630
#define GMI_MEDIA_CENTER_CLIENT_COMMAND_PORT        56631
//streaming media server
#define MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_PATH            "/Config/media_center_server/ipc_media_data_dispatch/"
#define MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_SERVER_UDP_PORT "server_udp_port"
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO1    56650
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO2    56651
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO3    56652
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO4    56653
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_AUDIO1    56654
#define MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_CLIENT_UDP_PORT "client_udp_port"
#define GMI_STREAMING_MEDIA_SERVER_DECODE_AUDIO1    56655
//streaming media client - onvif
#define ONVIF_MEDIA_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_PATH             "/Config/onvif_media_server/ipc_media_data_dispatch/"
#define ONVIF_MEDIA_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_CLIENT_UDP_PORT  "client_udp_port"
#define GMI_STREAMING_MEDIA_ONVIF_ENCODE_VIDEO1     56660
#define GMI_STREAMING_MEDIA_ONVIF_ENCODE_VIDEO2     56661
#define GMI_STREAMING_MEDIA_ONVIF_ENCODE_VIDEO3     56662
#define GMI_STREAMING_MEDIA_ONVIF_ENCODE_VIDEO4     56663
#define GMI_STREAMING_MEDIA_ONVIF_ENCODE_AUDIO1     56664
#define ONVIF_MEDIA_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_SERVER_UDP_PORT  "server_udp_port"
#define GMI_STREAMING_MEDIA_ONVIF_DECODE_AUDIO1     56665
//streaming media client - gb28181
#define GB_MEDIA_CLIENT_IPC_MEDIA_DATA_DISPATCH_CONFIG_PATH                "/Config/gb_media_client/ipc_media_data_dispatch/"
#define GB_MEDIA_CLIENT_IPC_MEDIA_DATA_DISPATCH_CONFIG_CLIENT_UDP_PORT     "client_udp_port"
#define GMI_STREAMING_MEDIA_GB28181_ENCODE_VIDEO1   56670
#define GMI_STREAMING_MEDIA_GB28181_ENCODE_VIDEO2   56671
#define GMI_STREAMING_MEDIA_GB28181_ENCODE_VIDEO3   56672
#define GMI_STREAMING_MEDIA_GB28181_ENCODE_VIDEO4   56673
#define GMI_STREAMING_MEDIA_GB28181_ENCODE_AUDIO1   56674
#define GB_MEDIA_CLIENT_IPC_MEDIA_DATA_DISPATCH_CONFIG_SERVER_UDP_PORT     "server_udp_port"
#define GMI_STREAMING_MEDIA_GB28181_DECODE_AUDIO1   56675
//streaming media client - sdk stream
#define SDK_MEDIA_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_PATH               "/Config/sdk_media_server/ipc_media_data_dispatch/"
#define SDK_MEDIA_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_CLIENT_UDP_PORT    "client_udp_port"
#define GMI_STREAMING_MEDIA_SDK_ENCODE_VIDEO1       56640
#define GMI_STREAMING_MEDIA_SDK_ENCODE_VIDEO2       56641
#define GMI_STREAMING_MEDIA_SDK_ENCODE_VIDEO3       56642
#define GMI_STREAMING_MEDIA_SDK_ENCODE_VIDEO4       56643
#define GMI_STREAMING_MEDIA_SDK_ENCODE_AUDIO1       56644
#define SDK_MEDIA_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_SERVER_UDP_PORT    "server_udp_port"
#define GMI_STREAMING_MEDIA_SDK_DECODE_AUDIO1       56645
// onvif rtsp server
#define ONVIF_MEDIA_SERVER_RTSP_CONFIG_PATH                                "/Config/onvif_media_server/rtsp/"
#define ONVIF_MEDIA_SERVER_RTSP_CONFIG_SERVER_MULTICAST_ADDRESS            "server_multicast_address"
#define ONVIF_MEDIA_SERVER_RTSP_CONFIG_SERVER_RTP_UDP_PORT                 "server_rtp_udp_port"
#define ONVIF_MEDIA_SERVER_RTSP_CONFIG_SERVER_RTCP_UDP_PORT                "server_rtcp_udp_port"
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO1_RTP     2000
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO1_RTCP    2001
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO2_RTP     2002
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO2_RTCP    2003
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO3_RTP     2004
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO3_RTCP    2005
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO4_RTP     2006
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO4_RTCP    2007
#define GMI_ONVIF_RTSP_SERVER_ENCODE_AUDIO1_RTP     2008
#define GMI_ONVIF_RTSP_SERVER_ENCODE_AUDIO1_RTCP    2009
#define GMI_ONVIF_RTSP_SERVER_DECODE_AUDIO1_RTP     2010
#define GMI_ONVIF_RTSP_SERVER_DECODE_AUDIO1_RTCP    2011
#define GMI_ONVIF_RTSP_SERVER_AUTH_PORT             56691
//rtsp server tcp port
#define GMI_RTSP_SERVER_TCP_PORT                    554
//http server port
#define GMI_HTTP_SERVER_PORT                        80
//onvif port
#define GMI_ONVIF_SERVER_PORT                       8080
//sdk server port
#define GMI_SDK_SERVER_PORT                         30000

//authentication server port
#define GMI_AUTH_SERVER_PORT                        51243

// these UDP port used by share memory log server and client
#define LOG_SERVER_DEFAULT_SERVER_PORT              50000
#define LOG_UPGRADE_DEFAULT_PORT                    50001
#define LOG_MEDIA_CENTER_DEFAULT_PORT               50002
#define LOG_CONTROL_CENTER_DEFAULT_PORT             50003
#define LOG_GB28181_DEFAULT_PORT                    50004
#define LOG_ONVIF_DEFAULT_PORT                      50005
#define LOG_PRIVATE_STREAM_DEFAULT_PORT             50006
#define LOG_STORAGE_DEFAULT_PORT                    50007
#define LOG_WEB_DEFAULT_PORT                        50008
#define LOG_AUTHENTICATION_DEFAULT_PORT             50009
#define LOG_GB_RTP_DEFAULT_PORT                     50010
#define LOG_ONVIF_RTSP_DEFAULT_PORT                 50011
#define LOG_SDK_DEFAULT_PORT                        50012

/************************ tcp port  ************************/
// log server
// publish server port, later log will use SDK to transmit log information and don't use this tcp port
#define GMI_LOG_PUBLISH_SERVER_PORT                 2000

//daemon update server port
#define GMI_DAEMON_UPDATE_SERVER_PORT               8000
/************************ pipe name ************************/
//daemon server

#define  GMI_RESOURCE_XML                           "/opt/config/gmi_resource.xml"
#define  GMI_SYS_SDK_PORT_PATH                      "/ipc/connect_port_resource"
#define  GMI_SYS_SERVER_TO_SDK_PORT_ITEM            "sys_server_to_sdk_port"
#define  GMI_SDK_TO_SYS_SERVER_PORT_ITEM            "sdk_to_sys_server_port"

#define SYS_SERVER_TO_SDK_PORT                      57000
#define SDK_TO_SYS_SERVER_PORT                      57002


/************************ mutex id ************************/
//daemon server

/********* log *********/
#define LOG_SERVER_CONFIG_PATH                                       "/Config/log_server/"
//log server
#define LOG_SERVER_CONFIG_SHARE_MEMORY_MUTEX_ID                      "share_memory_mutex_id"
#define GMI_LOG_SERVER_DEFAULT_SHARE_MEMORY_IPC_MUTEX_ID             2340

//streaming media data dispatch
#define MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_PATH             "/Config/media_center_server/ipc_media_data_dispatch/"
#define MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_IPC_MUTEX_KEY    "ipc_mutex_key"
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO1_IPC_MUTEX_KEY       2346
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO2_IPC_MUTEX_KEY       2348
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO3_IPC_MUTEX_KEY       2350
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO4_IPC_MUTEX_KEY       2352
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_AUDIO1_IPC_MUTEX_KEY       2354
#define GMI_STREAMING_MEDIA_SERVER_DECODE_AUDIO1_IPC_MUTEX_KEY       2356

#define GMI_USER_LOG_SHARE_MEMORY_KEY                                2360

/************************ share memory key ************************/

//log server
#define LOG_SERVER_CONFIG_SHARE_MEMORY_KEY                           "share_memory_key"
#define GMI_LOG_SERVER_DEFAUL_SHARE_MEMORY_KEY                       1230
#define GMI_USER_LOG_IPC_MUTEX_KEY                                   1231

//streaming media center server
// the same as MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_IPC_MUTEX_KEY
//#define MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_PATH             "/Config/media_center_server/ipc_media_data_dispatch/"
#define MEDIA_CENTER_SERVER_IPC_MEDIA_DATA_DISPATCH_CONFIG_SHARE_MEMORY_KEY "share_memory_key"
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO1_SHARE_MEMORY_KEY    1234
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO2_SHARE_MEMORY_KEY    1235
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO3_SHARE_MEMORY_KEY    1236
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_VIDEO4_SHARE_MEMORY_KEY    1237
#define GMI_STREAMING_MEDIA_SERVER_ENCODE_AUDIO1_SHARE_MEMORY_KEY    1238
#define GMI_STREAMING_MEDIA_SERVER_DECODE_AUDIO1_SHARE_MEMORY_KEY    1239

/************************ multicast address ************************/
//onvif rtsp server
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO1_MULTICAST_ADDRESS        "224.0.0.100"
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO2_MULTICAST_ADDRESS        "224.0.0.100"
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO3_MULTICAST_ADDRESS        "224.0.0.100"
#define GMI_ONVIF_RTSP_SERVER_ENCODE_VIDEO4_MULTICAST_ADDRESS        "224.0.0.100"
#define GMI_ONVIF_RTSP_SERVER_ENCODE_AUDIO1_MULTICAST_ADDRESS        "224.0.0.100"
#define GMI_ONVIF_RTSP_SERVER_DECODE_AUDIO1_MULTICAST_ADDRESS        "224.0.0.100"//not used for now 

#endif//IPC_FW_V3X_RESOURCE
