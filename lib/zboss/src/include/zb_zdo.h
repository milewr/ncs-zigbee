/*
 * ZBOSS Zigbee 3.0
 *
 * Copyright (c) 2012-2025 DSR Corporation, Denver CO, USA.
 * www.dsr-zboss.com
 * www.dsr-corporation.com
 * All rights reserved.
 *
 *
 * Use in source and binary forms, redistribution in binary form only, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 2. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 3. This software, with or without modification, must only be used with a Nordic
 *    Semiconductor ASA integrated circuit.
 *
 * 4. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* PURPOSE: Internal API of ZDO subsystem
*/

#ifndef ZB_ZDO_H
#define ZB_ZDO_H 1

#include "zboss_api_zdo.h"
#include "zdo_wwah_survey_beacons.h"
#include "zb_tlv.h"
#include "zboss_api_zcl.h"


/*! @cond internals_doc */
/*! \addtogroup ZB_ZDO */
/*! @{ */


/**
  Cluster ids for ZDO commands
 */
#define  ZDO_NWK_ADDR_REQ_CLID                       0x0000U
#define  ZDO_IEEE_ADDR_REQ_CLID                      0x0001U
#define  ZDO_NODE_DESC_REQ_CLID                      0x0002U
#define  ZDO_POWER_DESC_REQ_CLID                     0x0003U
#define  ZDO_SIMPLE_DESC_REQ_CLID                    0x0004U
#define  ZDO_ACTIVE_EP_REQ_CLID                      0x0005U
#define  ZDO_MATCH_DESC_REQ_CLID                     0x0006U
#define  ZDO_COMPLEX_DESC_REQ_CLID                   0x0010U
#define  ZDO_USER_DESC_REQ_CLID                      0x0011U
#define  ZDO_DEVICE_ANNCE_CLID                       0x0013U
#define  ZDO_SYSTEM_SERVER_DISCOVERY_REQ_CLID        0x0015U
#define  ZDO_PARENT_ANNCE_CLID                       0x001FU
#define  ZDO_BIND_REQ_CLID                           0x0021U
#define  ZDO_UNBIND_REQ_CLID                         0x0022U
#define  ZDO_CLEAR_ALL_BIND_REQ_CLID                 0x002BU
#define  ZDO_MGMT_LQI_REQ_CLID                       0x0031U
#define  ZDO_MGMT_RTG_REQ_CLID                       0x0032U
#define  ZDO_MGMT_BIND_REQ_CLID                      0x0033U
#define  ZDO_MGMT_LEAVE_REQ_CLID                     0x0034U
#define  ZDO_MGMT_DIRECT_JOIN_REQ_CLID               0x0035U
#define  ZDO_MGMT_PERMIT_JOINING_CLID                0x0036U
#define  ZDO_MGMT_NWK_UPDATE_REQ_CLID                0x0038U
#define  ZDO_MGMT_NWK_ENHANCED_UPDATE_REQ_CLID       0x0039U
#define  ZDO_MGMT_NWK_IEEE_JOINING_LIST_REQ_CLID     0x003AU
#define  ZDO_MGMT_NWK_BEACON_SURVEY_REQ_CLID         0x003CU
#define  ZDO_SECURITY_START_KEY_NEGOTIATION_REQ_CLID 0x0040U
#define  ZDO_SECURITY_GET_AUTH_TOKEN_REQ_CLID        0x0041U
#define  ZDO_SECURITY_GET_AUTH_LEVEL_REQ_CLID        0x0042U
#define  ZDO_SECURITY_SET_CONFIGURATION_REQ_CLID     0x0043U
#define  ZDO_SECURITY_GET_CONFIGURATION_REQ_CLID     0x0044U
#define  ZDO_SECURITY_START_KEY_UPDATE_REQ_CLID      0x0045U
#define  ZDO_SECURITY_DECOMMISSION_REQ_CLID          0x0046U
#define  ZDO_SECURITY_FRAME_CNT_CHALLENGE_REQ_CLID   0x0047U

#ifndef R23_DISABLE_DEPRECATED_ZDO_CMDS
#define  ZDO_USER_DESC_SET_CLID                  0x0014U
#define  ZDO_EXTENDED_SIMPLE_DESC_REQ_CLID       0x001DU
#define  ZDO_EXTENDED_ACTIVE_EP_REQ_CLID         0x001EU
#define  ZDO_END_DEVICE_BIND_REQ_CLID            0x0020U
#endif  /* R23_DISABLE_DEPRECATED_ZDO_CMDS */

#define  ZDO_NWK_ADDR_RESP_CLID                               0x8000U
#define  ZDO_IEEE_ADDR_RESP_CLID                              0x8001U
#define  ZDO_NODE_DESC_RESP_CLID                              0x8002U
#define  ZDO_POWER_DESC_RESP_CLID                             0x8003U
#define  ZDO_SIMPLE_DESC_RESP_CLID                            0x8004U
#define  ZDO_ACTIVE_EP_RESP_CLID                              0x8005U
#define  ZDO_MATCH_DESC_RESP_CLID                             0x8006U
#define  ZDO_COMPLEX_DESC_RESP_CLID                           0x8010U
#define  ZDO_USER_DESC_RESP_CLID                              0x8011U
#define  ZDO_USER_DESC_CONF_CLID                              0x8014U
#define  ZDO_SYSTEM_SERVER_DISCOVERY_RESP_CLID                0x8015U
#define  ZDO_PARENT_ANNCE_RESP_CLID                           0x801FU
#define  ZDO_BIND_RESP_CLID                                   0x8021U
#define  ZDO_UNBIND_RESP_CLID                                 0x8022U
#define  ZDO_CLEAR_ALL_BIND_RESP_CLID                         0x802BU
#define  ZDO_MGMT_LQI_RESP_CLID                               0x8031U
#define  ZDO_MGMT_RTG_RESP_CLID                               0x8032U
#define  ZDO_MGMT_BIND_RESP_CLID                              0x8033U
#define  ZDO_MGMT_LEAVE_RESP_CLID                             0x8034U
#define  ZDO_MGMT_PERMIT_JOINING_RESP_CLID                    0x8036U
#define  ZDO_MGMT_NWK_UPDATE_NOTIFY_CLID                      0x8038U
#define  ZDO_MGMT_NWK_ENHANCED_UPDATE_NOTIFY_CLID             0x8039U
#define  ZDO_MGMT_NWK_IEEE_JOINING_LIST_RESP_CLID             0x803AU
#define  ZDO_MGMT_NWK_UNSOLICITED_ENHANCED_UPDATE_NOTIFY_CLID 0x803BU
#define  ZDO_MGMT_NWK_BEACON_SURVEY_RESP_CLID                 0x803CU
#define  ZDO_SECURITY_START_KEY_NEGOTIATION_RESP_CLID         0x8040U
#define  ZDO_SECURITY_GET_AUTHENTICATION_TOKEN_RESP_CLID      0x8041U
#define  ZDO_SECURITY_GET_AUTH_LEVEL_RESP_CLID                0x8042U
#define  ZDO_SECURITY_SET_CONFIGURATION_RESP_CLID             0x8043U
#define  ZDO_SECURITY_GET_CONFIGURATION_RESP_CLID             0x8044U
#define  ZDO_SECURITY_START_KEY_UPDATE_RESP_CLID              0x8045U
#define  ZDO_SECURITY_DECOMMISSION_RESP_CLID                  0x8046U
#define  ZDO_SECURITY_FRAME_CNT_CHALLENGE_RESP_CLID           0x8047U

#ifndef R23_DISABLE_DEPRECATED_ZDO_CMDS
#define  ZDO_END_DEVICE_BIND_RESP_CLID                        0x8020U
#endif  /* R23_DISABLE_DEPRECATED_ZDO_CMDS */

/*! @} */
/*! @endcond */

#define ZB_SET_TLV_PANIC_WORKAROUND(val) (ZB_TCPOL().legacy_dev_tlv_panic_workaround = (val))
#define ZB_TLV_PANIC_WORKAROUND_ENABLED() (ZB_U2B(ZB_TCPOL().legacy_dev_tlv_panic_workaround))

/*! \addtogroup zdo_base */
/*! @{ */

/*Redefine zb_zdo_startup_complete to zboss_signal_handler*/
#define zb_zdo_startup_complete zboss_signal_handler

#define ZB_ZDO_IS_SRV_CMD(_cluster) (((_cluster) & (0x8000U))>>15U)
#define ZB_ZDO_IS_CLI_CMD(_cluster) (ZB_ZDO_IS_SRV_CMD(_cluster) == 0U)

#define ZB_ZDO_RESP_FROM_REQ_CLUSTER(_cli_cluster) ((_cli_cluster) | 0x8000U)

typedef void (*zb_apsme_update_device_ind_cb)(zb_apsme_update_device_ind_t *ind, zb_bool_t auth_allowed);
typedef void (*zb_assert_indication_cb_t)(zb_uint16_t file_id, zb_int_t line_number);
struct zb_zdo_device_annce_s;
typedef void (ZB_CODE * zb_device_annce_cb_t)(struct zb_zdo_device_annce_s *da);
typedef zb_ret_t (ZB_CODE * zb_zdo_responce_cb_t)(zb_uint8_t param, zb_uint16_t clusterid);
typedef void (*zb_zdo_set_channel_confirm_cb_t) (zb_uint8_t status);
typedef void (*zb_zdo_duty_cycle_mode_ind_cb_t) (zb_uint8_t mode);

/**
   \par Device start

   Startup procedure as defined in 2.5.5.5.6.2    Startup Procedure
*/


/* If any parameters are needed to be passed to the zdo_startup_complete, it
 * will be better to inherit zb_zdo_app_signal_hdr_t and introduce the structure
 * something like this:
 *
 * typedef struct zb_zdo_app_my_custom_event_s
 * {
 *   zb_zdo_app_signal_hdr_t super;
 *   zb_my_custom_data_type_t my_custom_data;
 * }
 *
 */

/*! @} */


/*! \addtogroup zdo_init */
/*! @{ */

/** @brief ZDO start function.
  *
  * Typical device start: init, load some parameters from nvram and proceed with startup.
  *
  * Startup means either Formation (for ZC), rejoin or discovery/association join.  After startup
  * complete @ref zb_zdo_startup_complete callback is called, so application will know when to do
  * some useful things.
  *
  * Precondition: stack must be inited by @ref zb_init() call. @ref zb_init() loads IB from NVRAM
  * or set its defaults, so caller has a chance to change some parameters.
  * @note: ZB is not looped in this routine. Instead, it schedules callback and returns.  Caller
  * must run @ref zdo_main_loop() after this routine.
  *
  * @b Example:
  * @code
  *   zb_init("zdo_zc");
  *   ZB_AIB().aps_designated_coordinator = 1;
  *   ZB_IEEE_ADDR_COPY(ZB_PIBCACHE_EXTENDED_ADDRESS(), &g_zc_addr);
  *   ZB_PIBCACHE_PAN_ID() = 0x1aaa;
  *   if (zdo_dev_start() != RET_OK)
  *   {
  *     TRACE_MSG(TRACE_ERROR, "zdo_dev_start failed", (FMT__0));
  *   }
  *   else
  *   {
  *     zdo_main_loop();
  *   }
  * @endcode
  * @return RET_OK on success.
  *
  */
zb_ret_t zdo_dev_start(void);


/* TODO: [Multi-MAC] do not use PIB in samples here, do not use direct contexts access,
 * rewrite example with modern ZBOSS public API */
/**
   Application main loop.

   Must be called after zb_init() and zdo_dev_start().

   @b Example:
@code
  zb_init("zdo_zc");
  ZB_AIB().aps_designated_coordinator = 1;
  ZB_IEEE_ADDR_COPY(ZB_PIB_EXTENDED_ADDRESS(), &g_zc_addr);
  ZB_PIBCACHE_PAN_ID() = 0x1aaa;
  if (zdo_dev_start() != RET_OK)
  {
    TRACE_MSG(TRACE_ERROR, "zdo_dev_start failed", (FMT__0));
  }
  else
  {
    zdo_main_loop();
  }
@endcode

 */
void zdo_main_loop(void);

/**
   Initializes internal contexts specific for
   selected device type
 */
void zb_init_contexts_by_dev_type(void);

/**
   ZDO device init

   May be called as alter zdo_dev_start().
   Initialize ZDO without schedule zb_zdo_dev_start_cont

   @b Example:
@code
  zb_init("zdo_zc");
  ZB_AIB().aps_designated_coordinator = 1;
  ZB_IEEE_ADDR_COPY(ZB_PIB_EXTENDED_ADDRESS(), &g_zc_addr);
  ZB_PIBCACHE_PAN_ID() = 0x1aaa;
  zdo_dev_init();
    ZB_SCHEDULE_CALLBACK(zb_zdo_dev_start_cont, 0);
    zdo_main_loop();
@endcode

 */
zb_ret_t zb_zdo_dev_init(void);

/**
   Initiate ZBOSS start without zb_send_no_autostart_event auto-start
 */
zb_ret_t zb_zdo_start_no_autostart(void);

/**
   ZDO device start procedure
  Use when init device and start device process cut HW test/init procedure

 */
void zb_zdo_dev_start_cont(zb_uint8_t param);

#ifdef ZB_USE_INTERNAL_HEADERS

/**
   Callback which will be called after device startup complete or other event happen

   Must be defined in the application.

   @param param - ref to buffer with application event - @see zb_get_app_signal

@b Example:
@snippet tp_pro_bv_20_zc.c zb_af_set_data_indication

 */
void zboss_signal_handler(zb_uint8_t param);

#endif /* ZB_USE_INTERNAL_HEADERS */

/*! @} */

/* internal zdo_startup_complete */
void zb_zdo_startup_complete_int(zb_uint8_t param);
void zb_zdo_startup_complete_int_delayed(zb_uint8_t param, zb_uint16_t user_param);
void zb_zdo_device_first_start_int_delayed(zb_uint8_t param, zb_uint16_t user_param);
void zb_zdo_device_reboot_int_delayed(zb_uint8_t param, zb_uint16_t user_param);

/*! @cond internals_doc */
/*! \addtogroup ZB_ZDO ZDO Internals */
/*! @{ */

/**
   Send Device announce command for custom params
 */
void zdo_send_device_annce_ex(zb_uint8_t             param,
                              zb_zdo_device_annce_t *dev_annce
#ifdef ZB_USEALIAS
                             ,zb_bool_t use_alias
#endif
  );

/**
   Actually send Device announce command
 */
void zdo_send_device_annce(zb_uint8_t param);


/**
   Node_desc_resp/Power_Node_desc_resp primitive.

   @param param - index of buffer to fill with primitive parameters.
*/
void zdo_send_desc_resp(zb_uint8_t param);

/**
   Simple_desc_resp primitive.

   @param param - index of buffer to fill with primitive parameters.
*/
void zdo_send_simple_desc_resp(zb_uint8_t param);

#ifdef ZB_FIXED_OPTIONAL_DESC_RESPONSES
/**
  Complex_Desc_rsp primitive

  @param param - index of buffer that has complex descriptor request.
                 Will be reused to send response.
*/
void zb_zdo_send_complex_desc_resp(zb_uint8_t param);

/**
  User_Desc_rsp primitive

  @param param - index of buffer that has user descriptor request.
                 Will be reused to send response.
*/
void zb_zdo_send_user_desc_resp(zb_uint8_t param);

/**
  User_Desc_conf primitive

  @param param - index of buffer containing User_Desc_set primitive.
                 Will be reused to send confirm.
*/
void zb_zdo_send_user_desc_conf(zb_uint8_t param);
#endif

/**
   simple_desc_resp_convert_zboss convert payload from ZibBee ZDO format to ZBOSS ZDO format

   change order cluster count - cluster ids
   see @ref zb_zdo_simple_desc_resp_t and ZDO spec

   @param param - index of buffer with zb_zdo_simple_desc_resp_t.
   @return RET_OK or RET_IGNORE for malformed  payload in response.
*/
zb_ret_t zb_zdo_simple_desc_resp_convert_zboss(zb_uint8_t param);

/**
   Copies node descriptor, taking into account endian
   @param dst_desc - destination descriptor
   @param src_desc - source descriptor
*/
void zb_copy_node_desc(zb_af_node_desc_t *dst_desc, zb_af_node_desc_t *src_desc);

/**
   Copies node power descriptor, taking into accaunt endian
   @param dst_desc - destination descriptor
   @param src_desc - source descriptor
*/
void zb_copy_power_desc(zb_af_node_power_desc_t *dst_desc, zb_af_node_power_desc_t *src_desc);

/**
   Copies simple descriptor, taking into accaunt endian
   @param dst_desc - destination descriptor
   @param src_desc - source descriptor
*/
void zb_copy_simple_desc(zb_af_simple_desc_1_1_t* dst_desc, zb_af_simple_desc_1_1_t*src_desc);

/**
   NWK_addr_req  primitive.

   @param param - index of buffer to fill with primitive parameters.
   @param fc - APS FC of the response
*/
void zdo_device_nwk_addr_res(zb_uint8_t param, zb_uint8_t fc);

#define ZB_ZDO_SINGLE_DEV_RESPONSE  0x00U
#define ZB_ZDO_EXTENDED_RESPONSE    0x01U

/**
   IEEE_addr_req  primitive.

   @param param - index of buffer to fill with primitive parameters.
   @param fc - APS FC of the response
*/
void zdo_device_ieee_addr_res(zb_uint8_t param, zb_uint8_t fc);

/**
   Sends update notify command
   @param param - index of buffer
*/
void zb_zdo_nwk_upd_notify(zb_uint8_t param);

/**
   Active_EP_res primitive.

   @param param - index of buffer to fill with primitive parameters.
*/
void zdo_active_ep_res(zb_uint8_t param);

/**
   Match_Desc_res primitive.

   @param param - index of buffer to fill with primitive parameters.
*/
void zdo_match_desc_res(zb_uint8_t param);

/**
   Performs channel interference reporting and resolution
   @param param - unused
*/
void zb_zdo_check_fails(zb_uint8_t param);

/**
   Timer callback to set limit for channel check action
   @param param - unused
 */
void zb_zdo_channel_check_timer_cb(zb_uint8_t param);

/**
   Callback to finish channel check action, is called on
   Mgmt_NWK_Update_notify acknowledgement
   @param param - index of buffer with results
*/
void zb_zdo_channel_check_finish_cb(zb_uint8_t param);

#ifdef ZB_JOIN_CLIENT
/**
 * @brief Checks whether the rejoin process is active
 *
 * @return rejoin activeness status
 */
zb_bool_t zb_zdo_is_rejoin_active(void);

/**
 *  @brief Initiate rejoin to the (same) PAN.
 *  @param buf [IN] - pointer to the  zb_buf_t "buffer" used to perform rejoin
 *  @param ext_pan_id [IN] - Extended Pan ID of PAN to rejoin to; use same Pan ID
 *  (either aps_use_extended_pan_id or nib_ext_pan_id)
 *  @param channels_list [IN] - scanned channels
 *  @param secure [IN] - if set to ZB_TRUE, device will perform secured rejoin;
 *  if ZB_FALSE - device will do unsecure rejoin
 *  @param scan_duration [IN] - A value used to calculate the length of time to
 *  spend scanning each channel.
 *  @return NLME-JOIN.request schedule result.
 * TODO: write comments
 */
zb_ret_t zdo_initiate_rejoin(zb_bufid_t buf, zb_uint8_t *ext_pan_id,
                             zb_channel_page_t *channels_list, zb_bool_t secure_rejoin, zb_uint8_t scan_duration);
#else
#define zdo_initiate_rejoin(buf, ext_pan_id, channels_list, secure_rejoin, scan_duration)
#endif

/**
   Handles NWK_addr_resp and Extended_addr_resp responses

   @param param - index of buffer with request
 */
void zb_zdo_addr_resp_handle(zb_uint8_t param);


/**
   Handles Mgmt_NWK_Update_req request

   @param param - index of buffer with request
 */
void zb_zdo_mgmt_nwk_update_handler(zb_uint8_t param);


/**
   Handles Mgmt_NWK_Enhanced_Update_req request

   @param param - index of buffer with request
 */
void zb_zdo_mgmt_nwk_enhanced_update_handler(zb_uint8_t param);


/**
   Handles Mgmt_NWK_Unsolicited_Enhanced_Update_notification request

   @param param - index of buffer with request
 */
void zb_zdo_mgmt_unsol_enh_nwk_update_notify_handler(zb_uint8_t param);


/**
   Handles unsolicited Mgmt_NWK_Update_notification request

   @param param - index of buffer with request
 */
void zb_zdo_mgmt_handle_unsol_nwk_update_notify(zb_uint8_t param);

/**
   Bind/Unbind response primitive

   @param param - index of buffer with request
   @param bind - true for bind, false for unbind
 */
void zb_zdo_bind_unbind_res(zb_uint8_t param, zb_bool_t bind);

void zb_zdo_clear_all_bind_res(zb_uint8_t param);

/**
   Sends 2.4.4.3.2 Mgmt_Lqi_rsp
   @param param - index of buffer with Lqi request
 */
void zdo_lqi_resp(zb_uint8_t param);

#if defined ZB_JOINING_LIST_SUPPORT && defined ZB_ROUTER_ROLE

/**
   Sends 2.4.4.4.11 Mgmt_NWK_IEEE_Joining_List_rsp
   @param param - index of buffer with nwk ieee joining list request
 */
void zdo_nwk_joining_list_resp(zb_uint8_t param);

/**
   Helper function that is responsible for actual Mgmt_NWK_IEEE_Joining_List_rsp sending
   To be used as a callback for mlme-get.confirm
*/
void zdo_nwk_joining_list_resp_send(zb_uint8_t param);

/**
   Sends 2.4.3.3.11 Mgmt_NWK_IEEE_Joining_List_req
   @param param - index of buffer with nwk ieee joining list request
 */
zb_uint8_t zb_zdo_mgmt_nwk_ieee_joining_list_req(zb_uint8_t param, zb_callback_t cb);

#endif /* defined ZB_JOINING_LIST_SUPPORT && defined ZB_ROUTER_ROLE */

/**
   Allocates buffer and schedules to execute zb_get_peer_short_addr()
   @param dst_addr_ref - reference to destination IEEE address
   @param cb - callback to run on get peer address finish
   @param param - parameter for callback function
 */
void zb_start_get_peer_short_addr(zb_address_ieee_ref_t dst_addr_ref, zb_callback_t cb, zb_uint8_t param);

/**
   Sends response for System_Server_Discovery_req
   @param param - index of buffer with request
 */
void zdo_system_server_discovery_res(zb_uint8_t param);

/**
   Sends 2.4.4.2.1 End_Device_Bind_rsp command
   @param param - index of buffer to use for i/o
   @param status - End_Device_Bind_req command status
*/
void zb_zdo_end_device_bind_resp(zb_uint8_t param, zb_zdp_status_t status);

/**
   Handle end_device_bind_req command
   @param param - index of buffer with request
 */
void zb_zdo_end_device_bind_handler(zb_uint8_t param);

/**
   Handle incoming mgmt_leave_req

   @param param - buffer with request
 */
void zdo_mgmt_leave_srv(zb_uint8_t param);

/**
   Try to send mgmt_leave_rsp if somebody waiting for it.

   mgmt_leave operation is registered in the leave pending list: after LEAVE
   command send confirm must send response.
   Search is done using buffer ref: it always same.
   If nothing found in the pending list, can proceed with leave.confirm
   operations (clear addresses), else need to wait until response sent.

   @param param - ref to the buffer used for overall LEAVE operation
   @param status - status to pass to the peer

   @return TRUE if resp sent, FALSE otherwise
 */
zb_bool_t zdo_try_send_mgmt_leave_rsp(zb_uint8_t param, zb_uint8_t status);

void zb_zdo_register_addr_resp_cb(zb_callback_t addr_resp_cb);

#if !defined NCP_MODE_HOST && !defined ZB_LITE_NO_OLD_CB
void zb_zdo_register_leave_cb(zb_callback_t leave_cb);
#endif

#ifndef ZB_DISABLE_ASSERT_INDICATION
/**
  Register a callback which should be called when application falls into assert
 */
void zb_zdo_register_assert_indication_cb(zb_assert_indication_cb_t assert_cb);
#endif

/**
 Register a callback which will be called when TC received device update
 */

void zb_zdo_register_update_device_indication_cb(zb_apsme_update_device_ind_cb cb);


#ifdef ZB_MAC_DUTY_CYCLE_MONITORING
void zb_zdo_register_duty_cycle_mode_indication_cb(zb_zdo_duty_cycle_mode_ind_cb_t cb);
#endif

/**
   handle Mgmt_Permit_Joining_req request

   @param param - permit joining parameters

   @return nothing
 */
void zb_zdo_mgmt_permit_joining_handle(zb_uint8_t param);

/**
   changes channel

   @param channel - channel number

   @return nothing
 */
void zb_zdo_set_channel_cb(zb_uint8_t channel);

/**
   changes channel without updating NWKUpdateID field

   @param channel - channel number

   @return nothing
 */
void zb_zdo_do_set_channel(zb_uint8_t channel);

#ifdef ZB_ROUTER_ROLE

void zb_zdo_mgmt_permit_joining_confirm_handle(zb_uint8_t param);

#ifdef ZB_CERTIFICATION_HACKS
/* ZB_UINT8_MAX used as a special value
  (this value forces stack to not consider this value at all)
*/
void zb_set_max_joins(zb_uint8_t max_joins);

zb_uint8_t zb_get_max_joins(void);

#endif /* ZB_CERTIFICATION_HACKS */
#endif /* ZB_ROUTER_ROLE */

#ifndef ZB_LITE_NO_ZDO_RESPONSE_VALIDATION
zb_bool_t zb_zdo_validate_reponse(zb_bufid_t buf, zb_uint16_t cluster_id);
#endif

/*! @} */
/*! @endcond */


/* FIXME: why invented special macro? Kill it! */
#if 0
#ifndef ZB_LITTLE_ENDIAN
#define ZB_LETOH16_XOR(val) \
  ((zb_uint8_t*)&val)[0] = ((zb_uint8_t)val)^(*((zb_uint8_t*)&val));\
  ((zb_uint8_t*)&val)[1] = (*((zb_uint8_t*)&val))^((zb_uint8_t)val);\
  ((zb_uint8_t*)&val)[0] = (*((zb_uint8_t*)&val))^(zb_uint8_t)val;
#else
#define ZB_LETOH16_XOR(val)
#endif
#endif  /* 0 */

#define ZB_LETOH16_XOR ZB_LETOH16_ONPLACE


/*
  Run-time hide of some clusters.
  Introduced to filter out sub-ghz cluster in 2.4-only mode.
 */
typedef zb_int_t (*zdo_cluster_filter_t)(zb_uint16_t clid);

#ifdef ZB_FILTER_OUT_CLUSTERS
void zdo_add_cluster_filter(zdo_cluster_filter_t filter);
zb_int_t zdo_check_cluster_filtered_out(zb_uint16_t clid);
#define ZDO_CLUSTER_FILTERED_OUT(clid) zdo_check_cluster_filtered_out(clid)
#else
#define ZDO_CLUSTER_FILTERED_OUT(clid) 0
#endif


void zdo_clear_after_leave(zb_uint8_t param);

/** @brief Callback registration function. */
zb_bool_t register_zdo_cb(
  zb_uint8_t tsn, zb_callback_t cb,
  zb_uint8_t resp_counter, zb_uint8_t cb_type,
  zb_bool_t rx_on_when_idle);

/** @addtogroup zdo_disc
  * @{
  */


/** @brief Reset all registered ZDO callbacks.
  * There are some cases when ZDO callbacks are not needed anymore (for example, on
  * leave). Reset the callbacks and free the space for more actual and important routines
  * (for example, leave confirm).
  */
void zdo_cb_reset(void);

/** @} */ /* group zdo_disc */

/* If forget device param is true - then remove all information related to device;
 * otherwise - remove device from neighbors, children and unlock its address entry,
 * save application data (bindings e.t.c) */
void zdo_device_removed(zb_uint8_t param, zb_uint16_t forget_device);
void zb_send_leave_signal(zb_uint8_t param, zb_uint16_t user_param);

void zb_zdo_register_device_annce_cb(zb_device_annce_cb_t cb);

void zb_zdo_register_zb_zdo_responce_cb(zb_zdo_responce_cb_t cb);

void zb_zdo_register_leave_indication_cb(zb_callback_t cb);

void zb_zdo_register_set_channel_confirm_cb(zb_zdo_set_channel_confirm_cb_t cb);

/* **************************** Device Updated Signal functions **************************** */

/**
 * @brief Send @ZB_ZDO_SIGNAL_DEVICE_UPDATE signal
 *
 * @param param - reference to the buffer
 * @param long_addr - long address of the updated device
 * @param short_addr - short address of the updated device
 * @param status - the updated status of the device
 *        (see r21 spec, Table 4.14 APSME-UPDATE-DEVICE.request Parameters)
 * @param parent_short - short address of the device parent, 0xffff if unknown
 * @param action - action TC made - @see secur_tc_action
 */
void zb_send_device_update_signal(zb_uint8_t param,
                                  zb_ieee_addr_t long_addr,
                                  zb_uint16_t short_addr,
                                  zb_uint8_t status,
                                  zb_uint16_t parent_short,
                                  zb_uint8_t action);
/**
 * @brief Prepare parameters and send
 *        @ZB_ZDO_SIGNAL_DEVICE_UPDATE signal with delay
 *
 * @param long_addr - long address of the updated device
 *                    (need to getting @zb_address_ieee_ref_t)
 * @param status - status of the updated device
 *                 (see r21 spec, Table 4.14 APSME-UPDATE-DEVICE.request Parameters)
 * @param parent_addr - long address of the parent
 * @param ret - return status of TC authorization procedure
 */
void zb_prepare_and_send_device_update_signal(zb_ieee_addr_t long_addr, zb_uint8_t status, zb_ieee_addr_t parent_addr, zb_ret_t ret);

/* **************************** Device Authorized Signal functions **************************** */

#define ZB_GET_AUTHORIZATION_STATUS(var) ((var) >> 2U)
#define ZB_GET_AUTHORIZATION_TYPE(var) ((var) & 0x03U)

#define ZB_PACK_AUTHORIZATION_PARAMS(status, type) (((status) << 2U) | ((type) & 0x03U))

/**
 * @brief Send @ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED signal
 *
 * @param param - reference to the buffer
 * @param long_addr - long address of the authorized device
 * @param short_addr - short address of the authorized device
 * @param authorization_type - authorization type (legacy, r21 TCLK)
 * @param authorization_status - authorization status (depends on authorization_type)
 */
void zb_send_device_authorized_signal(zb_uint8_t param,
                                      zb_ieee_addr_t long_addr,
                                      zb_uint16_t short_addr,
                                      zb_uint8_t authorization_type,
                                      zb_uint8_t authorization_status);

/**
 * @brief Prepare parameters and send the
 *        @ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED signal with delay
 *
 * @param long_addr - long address of the authorized device
 *                    (need to getting the @zb_address_ieee_ref_t)
 * @param authorization_type - authorization type (legacy, r21 TCLK, )
 * @param authorization_status - authorization status (depends on authorization_type)
 */
void zb_prepare_and_send_device_authorized_signal(zb_ieee_addr_t long_addr,
                                                  zb_uint8_t authorization_type,
                                                  zb_uint8_t authorization_status);

#ifdef DEBUG
/**
 * @brief Send @ZB_DEBUG_SIGNAL_TCLK_READY signal
 *
 * @param param - reference to the buffer
 * @param long_addr - long address of the partner device
 */
void zb_send_tclk_ready_debug_signal(zb_uint8_t param, zb_ieee_addr_t long_addr);

/**
 * @brief Prepare parameters and send the
 *        @ZB_DEBUG_SIGNAL_TCLK_READY signal with delay
 *
 * @param long_addr - long address of the partner device
 */
void zb_prepare_and_send_tclk_ready_debug_signal(zb_ieee_addr_t long_addr);
#endif

/**
 * @brief Alarm to send @ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED signal
 *        for legacy devices ( < r21)
 *
 * @param param - address reference
 */
void zb_legacy_device_auth_signal_alarm(zb_uint8_t param);

/* @brief Cancel zb_legacy_device_auth_signal_alarm
 *        for legacy devices ( < r21)
 *
 * @param long_addr - IEEE64 address reference
 */
void zb_legacy_device_auth_signal_cancel(zb_ieee_addr_t long_addr);


/* MM: For unicast, counter should be set to 1 and callback can be freed in two
 * ways: timeout or ZDO response recept
 * For broadcast, counter should be set to 0xFF(?) and callback can be
 * freed only in one way: timeout
 *
 * EE: Really, unicast must be 1. That values were from pre-historic logic.
 * I still keep DEFAULT_COUNTER (but changed const): seems, in some cases we can
 * send broadcast ZDO packets and receive more than 1 answer.
 */

/**
 * @brief Send @ref ZB_ZDO_DEVICE_UNAVAILABLE signal
 *
 * @param param - a buf ID, @see zb_bufid_t
 * @param param2 - an address reference, @see zb_address_ieee_ref_t
 */
void zb_zdo_send_device_unavailable_signal(zb_uint8_t param, zb_uint16_t param2);

void zb_send_no_active_links_left_signal(zb_uint8_t param);

#define ZB_ZDO_CB_UNICAST_COUNTER     1U  /* 1 resp for Unicast */
#define ZB_ZDO_CB_BROADCAST_COUNTER   0xFFU  /* wait for timeout */
#define ZB_ZDO_CB_DEFAULT_COUNTER     0xFEU    /* Default value (just for check) */

#define ZB_ZDO_CB_KILLER_QUANT          (5U * ZB_TIME_ONE_SECOND)
#define ZB_ZDO_CB_KILLER_CRITICAL_TIME(_rx_on_when_idle)  \
  (2U*ZB_N_APS_MAX_FRAME_RETRIES * ZB_N_APS_ACK_WAIT_DURATION(_rx_on_when_idle))
#define ZB_ZDO_CB_CLOCK_COUNTER(_rx_on_when_idle) \
  (ZB_ZDO_CB_KILLER_CRITICAL_TIME(_rx_on_when_idle) / ZB_ZDO_CB_KILLER_QUANT + 1U)

void zdo_aps_decryption_failed(zb_uint8_t param);

#define ZB_ZDO_NEIGHBOR_ERROR_VALUE     0xffU

typedef struct zb_zdo_get_channel_req_s
{
  zb_callback_t cb;
} zb_zdo_get_channel_req_t;

typedef struct zb_zdo_get_channel_resp_t
{
  zb_uint8_t status;
  zb_uint8_t channel;
} zb_zdo_get_channel_resp_t;

void zb_zdo_get_channel(zb_uint8_t param);

/* Poll control */

/**
   Running poll mode
 */
typedef enum zb_poll_mode_e
{
  ZB_ZDO_PIM_FAST,              /*!< Fast poll  */
  ZB_ZDO_PIM_LONG,              /*!< Long poll  */
  ZB_ZDO_PIM_TURBO              /*!< Turbo poll  */
#ifdef SNCP_MODE
  ,
  ZB_ZDO_PIM_STOP               /*!< Poll stopped */
#endif
} zb_poll_mode_t;

/**
   Arguments of asynchronous Get In Fast Poll Status response.
*/
typedef ZB_PACKED_PRE struct zb_zdo_pim_get_in_fast_poll_flag_resp_s
{
  zb_bool_t in_fast_poll; /**< in fast poll status flag */
} ZB_PACKED_STRUCT
zb_zdo_pim_get_in_fast_poll_flag_resp_t;

/**
 * @name Fast poll stopping result
 * @anchor stop_fast_poll_result
 */
/** @{ */
#define ZB_ZDO_PIM_STOP_FAST_POLL_RESULT_NOT_STARTED 0U /*!< Fast poll was not started  */
/** Fast poll was not stopped because ZDO_CTX().pim.fast_poll_on value still not equals to zero
 * after decreasing */
#define ZB_ZDO_PIM_STOP_FAST_POLL_RESULT_NOT_STOPPED 1U
#define ZB_ZDO_PIM_STOP_FAST_POLL_RESULT_STOPPED     2U /*!< Fast poll was stopped  */
/** @} */

/**
 * @brief Type for fast poll stopping result.
 *
 * Holds one of @ref stop_fast_poll_result. Kept only for backward compatibility as
 * @ref stop_fast_poll_result were declared previously as enum. Can be removed in future releases.
 */
typedef zb_uint8_t zb_stop_fast_poll_result_t;

/**
   Arguments of asynchronous Stop Fast Poll Extended response.
*/
typedef ZB_PACKED_PRE struct zb_zdo_pim_stop_fast_poll_extended_resp_s
{
  zb_stop_fast_poll_result_t stop_result; /**< fast poll stopping result */
} ZB_PACKED_STRUCT
zb_zdo_pim_stop_fast_poll_extended_resp_t;


#ifdef ZB_ED_FUNC
/**
   Initialize Poll Interval Management default settings
 */
void zb_zdo_pim_init(void);
void zb_zdo_pim_init_defaults(void);
void zb_zdo_pim_start_fast_poll(zb_uint8_t param);
void zb_zdo_fast_poll_leave(zb_uint8_t param);
void zb_zdo_pim_stop_fast_poll(zb_uint8_t param);
void zb_zdo_pim_reset_turbo_poll_min(zb_uint8_t param);
void zb_zdo_pim_reset_turbo_poll_max(zb_uint8_t param);
void zb_zdo_pim_got_data(zb_uint8_t param);
void zb_zdo_pim_continue_polling_for_pkt(void);
zb_poll_mode_t zb_zdo_pim_get_mode(void);
void zb_zdo_pim_set_fast_poll_interval(zb_time_t ms);
void zb_zdo_pim_set_fast_poll_timeout(zb_time_t ms);
zb_bool_t zb_zdo_pim_in_fast_poll(void);
zb_time_t zb_zdo_get_pim_fast_poll_interval_ms(void);
zb_time_t zb_zdo_get_pim_fast_poll_timeout_ms(void);
void zb_zdo_pim_set_turbo_poll_max(zb_time_t turbo_poll_max_ms);
void zb_zdo_pim_set_turbo_poll_min(zb_time_t turbo_poll_min_ms);
zb_time_t zb_zdo_get_pim_turbo_poll_min_ms(void);
zb_time_t zb_zdo_get_poll_interval_ms(void);
void zb_zdo_pim_start_poll(zb_uint8_t param);
void zb_zdo_pim_stop_poll(zb_uint8_t param);
void zb_zdo_turbo_poll_packets_leave(zb_uint8_t param);
void zb_zdo_update_long_poll_int(zb_uint8_t param);
void zb_zdo_pim_continue_turbo_poll(void);
zb_time_t zb_zdo_pim_get_long_poll_ms_interval(void);
void zb_zdo_pim_turbo_poll_cancel_packet(void);
void zb_zdo_pim_set_mac_poll_retry_count(zb_uint8_t cnt);
void zb_zdo_pim_set_mac_poll_failure_wait_time(zb_uint8_t t);
void zb_zdo_pim_repeat_poll(void);

#ifdef ZB_USE_INTERNAL_HEADERS
void zb_zdo_pim_set_long_poll_interval(zb_time_t ms);
void zb_zdo_pim_start_turbo_poll_packets(zb_uint8_t n_packets);
#endif
/**
 * @brief Sends asynchronous request to check whether the device is in fast poll mode
 *
 * @param param buffer that will be used to store response parameters.
 *
 * @param cb
 */
void zb_zdo_pim_get_in_fast_poll_flag_req(zb_uint8_t param, zb_callback_t cb);


/**
 * @brief Sends asynchronous request to stop fast poll and get stopping result
 *
 * @param param buffer that will be used to store response parameters.
 *
 * @param cb
 */
void zb_zdo_pim_stop_fast_poll_extended_req(zb_uint8_t param, zb_callback_t cb);

#else
/* No any polling if not ZED-only or ZR switched to ZED */
#define zb_zdo_pim_init()
#define zb_zdo_pim_init_defaults()
#define zb_zdo_pim_start_fast_poll(param)
#define zb_zdo_fast_poll_leave(param)
#define zb_zdo_pim_stop_fast_poll(param)
#define zb_zdo_pim_reset_turbo_poll_min(param)
#define zb_zdo_pim_reset_turbo_poll_max(param)
#define zb_zdo_pim_got_data(param)
#define zb_zdo_pim_continue_polling_for_pkt()
#define zb_zdo_pim_get_mode() 0U
#define zb_zdo_pim_set_fast_poll_interval(ms)
#define zb_zdo_pim_set_fast_poll_timeout(ms)
#define zb_zdo_pim_set_long_poll_interval(ms)
#define zb_zdo_pim_in_fast_poll() 0U
#define zb_zdo_get_pim_fast_poll_interval_ms() 0U
#define zb_zdo_get_pim_fast_poll_timeout_ms() 0U
#define zb_zdo_pim_set_turbo_poll_max(turbo_poll_max_ms)
#define zb_zdo_pim_set_turbo_poll_min(turbo_poll_min_ms)
#define zb_zdo_get_pim_turbo_poll_min_ms() 0U
#define zb_zdo_pim_start_poll(param)
#define zb_zdo_pim_stop_poll(param)
#define zb_zdo_update_long_poll_int(param)
#define zb_zdo_turbo_poll_packets_leave(param)
#define zb_zdo_pim_continue_turbo_poll(param)
#define zb_zdo_pim_start_turbo_poll_packets(n_packets)
#define zb_zdo_pim_get_long_poll_ms_interval() 0U
#define zb_zdo_pim_get_in_fast_poll_flag_req(param, cb)
#define zb_zdo_pim_stop_fast_poll_extended_req(param, cb)
#define zb_zdo_pim_set_mac_poll_retry_count(cnt)
#define zb_zdo_pim_set_mac_poll_failure_wait_time(t)
#define zb_zdo_pim_repeat_poll()
#define zb_zdo_pim_turbo_poll_cancel_packet()

#endif  /* ZB_ED_FUNC */

void zb_zdo_device_is_unreachable(zb_uint8_t addr_ref);

zb_uint8_t zdo_get_aging_timeout(void);

/**
   Set Request Timeout Enumeration value that will be used in End Device Timeout Request
   command (see 3.4.11 - r21 Zigbee spec)

   @param timeout - Request Timeout Enumeration value (see 3.4.11.3.1)
 */
void zdo_set_aging_timeout(zb_uint8_t timeout);

zb_time_t zdo_get_ed_keepalive_timeout(void);

void zb_zdo_start_router(zb_uint8_t param);

void zdo_mgmt_permit_joining_resp_cli(zb_uint8_t param);

void zb_set_zdo_descriptor(void);

/*! \addtogroup zdo_general_api */
/*! @{ */

void zdo_rejoin_clear_prev_join(void);

/**
   predict (not really increment) ZDO TSN value according to the policy

   @return ZDO TSN predicted value
 */
zb_uint8_t zdo_tsn_predict(void);

/**
   update (increment) ZDO TSN value according to the policy

   @return ZDO TSN updated value
 */
zb_uint8_t zdo_tsn_inc(void);

/**
   get current ZDO TSN value

   @return ZDO TSN current value
 */
zb_uint8_t zdo_tsn_get(void);

/**
   ZBOSS commissioning type
 */
typedef enum  zb_commissioning_type_e
{
  /* Note: classic must 1 for backward compatibility with apps used ZBOSS r21 API */
  ZB_COMMISSIONING_CLASSIC = 0, /*!< Classic == core certification tests == HA. Nearly obsolete now.  */
  /* Note: BDB mode must 1 for backward compatibility with apps used ZBOSS r21 API */
  ZB_COMMISSIONING_BDB = 1,     /*!< BDB mode. */
  ZB_COMMISSIONING_SE,
/*  ZB_COMMISSIONING_ZLL,         / !< ZLL not via BDB (is it ever usable?)  */
} zb_commissioning_type_t;


/* ZB_COMMISSIONING_TYPE() can be either hard-coded or selectable depending on build type. */
#if defined ZB_BDB_MODE && defined ZB_LITE_BDB_ONLY_COMMISSIONING && !defined ZB_SE_COMMISSIONING

#define ZB_COMMISSIONING_TYPE() ZB_COMMISSIONING_BDB

#elif defined ZB_SE_COMMISSIONING && !defined ZB_BDB_MODE && defined ZB_SE_ONLY_COMMISSIONING

#define ZB_COMMISSIONING_TYPE() ZB_COMMISSIONING_SE

#else

#define ZB_CONFIGURABLE_COMMISSIONING_TYPE

#endif  /* commissioning type selector */


#ifdef ZB_CONFIGURABLE_COMMISSIONING_TYPE

#ifdef ZB_COMMISSIONING_TYPE
#undef ZB_COMMISSIONING_TYPE
#endif

#define ZB_COMMISSIONING_TYPE() COMM_CTX().commissioning_type
/* Classic is required for cert tests only, so have it in configurable case */
#ifndef ZB_COMMISSIONING_CLASSIC_SUPPORT
#define ZB_COMMISSIONING_CLASSIC_SUPPORT
#endif

#endif  /* ZB_CONFIGURABLE_COMMISSIONING_TYPE */

/**
 * @name Rejoin reasons
 * @anchor rejoin_reason
 *
 * Note: These values were members of `enum zb_rejoin_reason_t` type but were converted to a
 * set of macros due to MISRA violations.
 */
/** @{ */
#define ZB_REJOIN_REASON_SELF_INITIATED           0U /*!< Local device initiated rejoin */
#define ZB_REJOIN_REASON_BACKOFF_REJOIN           1U /*!< Backoff rejoin */
#define ZB_REJOIN_REASON_PARENT_LOST              2U /*!< Rejoin caused by parent lost */
#define ZB_REJOIN_REASON_DEV_ANNCE_SENDING_FAILED 3U /*!< Rejoin caused by failed device announcement transmission  */
#define ZB_REJOIN_REASON_LEAVE_WITH_REJOIN        4U /*!< Rejoin cause by leave command with rejoin bit enabled  */
/** @} */

#ifdef ZB_COMMISSIONING_CLASSIC_SUPPORT
void zdo_classic_initiate_commissioning(zb_uint8_t param);
#endif

#if defined ZB_JOINING_LIST_SUPPORT

typedef ZB_PACKED_PRE struct zb_jl_q_ent_s
{
  zb_callback_t func;           /*!< function to call  */
  zb_uint8_t param;             /*!< parameter to pass to 'func'  */
}
ZB_PACKED_STRUCT
zb_jl_q_ent_t;

ZB_RING_BUFFER_DECLARE(zb_joining_list_op_q, zb_jl_q_ent_t, ZB_JOINING_LIST_Q_SIZE);

#endif /* ZB_JOINING_LIST_SUPPORT */

/*! @} */

/*Legacy API for device role selection. Used in some old tests*/
#ifdef ZB_COORDINATOR_ROLE
void zb_set_network_coordinator_role_with_mode(zb_uint32_t channel_mask, zb_uint8_t bdb_mode);
void zb_set_nwk_coordinator_role_legacy_ext(zb_channel_list_t channel_list);
#endif /* ZB_COORDINATOR_ROLE */

#ifdef ZB_ROUTER_ROLE
void zb_set_network_router_role_with_mode(zb_uint32_t channel_mask, zb_commissioning_type_t bdb_mode);
void zb_set_nwk_router_role_legacy_ext(zb_channel_list_t channel_list);
#endif /* ZB_ROUTER_ROLE */

#ifdef ZB_ED_FUNC
void zb_set_network_ed_role_with_mode(zb_uint32_t channel_mask, zb_commissioning_type_t bdb_mode);
void zb_set_nwk_ed_role_legacy_ext(zb_channel_list_t channel_list);
#endif /* ZB_ED_FUNC */

#ifdef ZB_USE_INTERNAL_HEADERS
#ifdef ZB_COORDINATOR_ROLE
void zb_set_network_coordinator_role_legacy(zb_uint32_t channel_mask);
#endif /* ZB_COORDINATOR_ROLE */

#ifdef ZB_ROUTER_ROLE
void zb_set_network_router_role_legacy(zb_uint32_t channel_mask);
#endif /* ZB_ROUTER_ROLE */

#ifdef ZB_ED_FUNC
void zb_set_network_ed_role_legacy(zb_uint32_t channel_mask);
#endif /* ZB_ED_FUNC */
#endif /* ZB_USE_INTERNAL_HEADERS */

/**
  Set simple descriptor parameters
  @param simple_desc - pointer to simple descriptor
  @param endpoint - Endpoint
  @param app_profile_id - Application profile identifier
  @param app_device_id - Application device identifier
  @param app_device_version - Application device version
  @param app_input_cluster_count - Application input cluster count
  @param app_output_cluster_count - Application output cluster count

*/
void zb_set_simple_descriptor(zb_af_simple_desc_1_1_t *simple_desc,
                              zb_uint8_t  endpoint, zb_uint16_t app_profile_id,
                              zb_uint16_t app_device_id, zb_bitfield_t app_device_version,
                              zb_uint8_t app_input_cluster_count, zb_uint8_t app_output_cluster_count);

/**
  Set input cluster item
  @param simple_desc - pointer to simple descriptor
  @param cluster_number - cluster item number
  @param cluster_id - cluster ID

*/
void zb_set_input_cluster_id(zb_af_simple_desc_1_1_t *simple_desc, zb_uint8_t cluster_number, zb_uint16_t cluster_id);

/*! @brief Set output cluster item
    @param simple_desc - pointer to simple descriptor
    @param cluster_number - cluster item number
    @param cluster_id - cluster ID

*/
void zb_set_output_cluster_id(zb_af_simple_desc_1_1_t *simple_desc, zb_uint8_t cluster_number, zb_uint16_t cluster_id);

/**
  Set default descriptors values for FFD.
  @param device_type - device type ZB_COORDINATOR or ZB_ROUTER

  @code
    zb_set_default_ffd_descriptor_values(ZB_COORDINATOR);
  @endcode

 */
void zb_set_default_ffd_descriptor_values(zb_logical_type_t device_type);

/**
  Set default descriptors values for end device.
 */
void zb_set_default_ed_descriptor_values(void);

/**
  Adds simple descriptor.
  @param simple_desc - pointer to simple descriptor to add
  @return RET_OK, RET_OVERFLOW

  @par Example
  @snippet tp_zdo_bv_09_zc.c zb_set_simple_descriptor
  @par

 */
zb_ret_t zb_add_simple_descriptor(zb_af_simple_desc_1_1_t *simple_desc);

/**
  Set node descriptor for FFD
  @param device_type - FFD device type ZB_COORDINATOR or ZB_ROUTER
*/
void zb_set_ffd_node_descriptor(zb_logical_type_t device_type);

/**
  Set node descriptor for end device
  @param power_src - true if the current power source is mains power, false otherwise
  @param rx_on_when_idle - receiver on when idle sub-field
  @param alloc_addr - allocate address sub-field
*/
void zb_set_ed_node_descriptor(zb_bool_t power_src, zb_bool_t rx_on_when_idle, zb_bool_t alloc_addr);

/** @cond internals_doc */
#define ZB_NODE_DESC_LOGICAL_TYPE_MASK 0x7U       /* 0000.0000 0000.0111 */
#define ZB_NODE_DESC_COMPLEX_DESC_AVAIL_MASK 0x8U /* 0000.0000 0000.1000 */
#define ZB_NODE_DESC_USER_DESC_AVAIL_MASK 0x10U   /* 0000.0000 0001.0000 */
#define ZB_NODE_DESC_USER_DESC_FRAG_MASK 0x20U    /* 0000.0000 0010.0000 */
#define ZB_NODE_DESC_APS_FLAGS_MASK    0x700U     /* 0000.0111 0000.0000 */
#define ZB_NODE_DESC_FREQ_BAND_MASK    0xF800U    /* 1111.1000 0000.0000 */

#define ZB_NODE_DESC_SERVER_FLAGS_STACK_REV_MASK 0xFE00U /* 1111.1110 0000.0000 */

#define ZB_SET_NODE_DESC_LOGICAL_TYPE(desc, value)              \
  ( (desc)->node_desc_flags &= (zb_uint16_t)~ZB_NODE_DESC_LOGICAL_TYPE_MASK, \
    (desc)->node_desc_flags |= (zb_uint16_t)(value) )

#define ZB_GET_NODE_DESC_LOGICAL_TYPE(desc) \
  ( (desc)->node_desc_flags & ZB_NODE_DESC_LOGICAL_TYPE_MASK )

#define ZB_SET_NODE_DESC_COMPLEX_DESC_AVAIL(desc, value)         \
  ( (desc)->node_desc_flags &= (zb_uint16_t)~ZB_NODE_DESC_COMPLEX_DESC_AVAIL_MASK, \
    (desc)->node_desc_flags |= (zb_uint16_t)((value) << 3U) )

#define ZB_GET_NODE_DESC_COMPLEX_DESC_AVAIL(desc)                \
  ( ((desc)->node_desc_flags & ZB_NODE_DESC_COMPLEX_DESC_AVAIL_MASK) >> 3U )

#define ZB_SET_NODE_DESC_USER_DESC_AVAIL(desc, value)                 \
  ( (desc)->node_desc_flags &= (zb_uint16_t)~ZB_NODE_DESC_USER_DESC_AVAIL_MASK,    \
    (desc)->node_desc_flags |= (zb_uint16_t)((value) << 4U) )

#define ZB_GET_NODE_DESC_USER_DESC_AVAIL(desc)                    \
  ( ((desc)->node_desc_flags & ZB_NODE_DESC_USER_DESC_AVAIL_MASK) >> 4U )

#define ZB_SET_NODE_DESC_FRAGMENTATION_SUPPORTED(desc, value)                 \
  ( (desc)->node_desc_flags &= (zb_uint16_t)~ZB_NODE_DESC_USER_DESC_FRAG_MASK,    \
    (desc)->node_desc_flags |= (zb_uint16_t)((value) << 5U) )

#define ZB_GET_NODE_DESC_FRAGMENTATION_SUPPORTED(desc)                    \
  ( ((desc)->node_desc_flags & ZB_NODE_DESC_USER_DESC_FRAG_MASK) >> 5U )

#define ZB_SET_NODE_DESC_APS_FLAGS(desc, value)                    \
  ( (desc)->node_desc_flags &= (zb_uint16_t)~ZB_NODE_DESC_APS_FLAGS_MASK,       \
    (desc)->node_desc_flags |= (zb_uint16_t)((value) << 8U) )

#define ZB_GET_NODE_DESC_APS_FLAGS(desc)                    \
  ( ((desc)->node_desc_flags & ZB_NODE_DESC_APS_FLAGS_MASK) >> 8U )

#define ZB_SET_NODE_DESC_FREQ_BAND(desc, value)               \
  ( (desc)->node_desc_flags &= (zb_uint16_t)~ZB_NODE_DESC_FREQ_BAND_MASK,       \
    (desc)->node_desc_flags |= (zb_uint16_t)((value) << 11U) )

#define ZB_GET_NODE_DESC_FREQ_BAND(desc)                      \
  ( ((desc)->node_desc_flags & ZB_NODE_DESC_FREQ_BAND_MASK) >> 11U )

#define ZB_GET_NODE_DESC_STACK_VERSION(desc)                  \
  ( ((desc)->server_mask) >> 9U )

#define ZB_GET_NODE_DESC_SERVER_FLAGS_STACK_REV(desc)         \
  ( ((desc)->server_mask & ZB_NODE_DESC_SERVER_FLAGS_STACK_REV_MASK) >> 9 )
/** @endcond */ /*internals_doc */

/**
  Set node descriptor
  @param device_type - FFD device type ZB_COORDINATOR or ZB_ROUTER or RFD device type - ZB_END_DEVICE
  @param power_src - 1 if the current power source is mains power, 0 otherwise
  @param rx_on_when_idle - receiver on when idle sub-field
  @param alloc_addr - allocate address sub-field

  @b Example
  @code
    zb_set_node_descriptor(ZB_END_DEVICE, ZB_TRUE, ZB_FALSE, ZB_TRUE);
  @endcode

  NOTE: zboss_start() overwrites this descriptor with default values.
*/
void zb_set_node_descriptor(zb_logical_type_t device_type, zb_bool_t power_src, zb_bool_t rx_on_when_idle, zb_bool_t alloc_addr);

/** @cond internals_doc */
/* Macro to set node descriptor, 2.3.2.3 Node Descriptor  */

#define ZB_SET_NODE_DESCRIPTOR(logical_type_p, fragmentation_support, frequency_band_p, mac_capability_flags_p, manufacturer_code_p, \
                                max_buf_size_p, max_incoming_transfer_size_p, server_mask_p, \
                                max_outgoing_transfer_size_p, desc_capability_field_p) \
  do \
  { \
    ZB_SET_NODE_DESC_LOGICAL_TYPE(ZB_ZDO_NODE_DESC(), (logical_type_p)); \
    ZB_SET_NODE_DESC_COMPLEX_DESC_AVAIL(ZB_ZDO_NODE_DESC(), 0U);  /* complex desc is not supported */ \
    ZB_SET_NODE_DESC_USER_DESC_AVAIL(ZB_ZDO_NODE_DESC(), 0U);     /* usr desc is not supported */ \
    ZB_SET_NODE_DESC_FRAGMENTATION_SUPPORTED(ZB_ZDO_NODE_DESC(), fragmentation_support); \
    ZB_SET_NODE_DESC_APS_FLAGS(ZB_ZDO_NODE_DESC(), 0U); /* not supported by spec */ \
    ZB_SET_NODE_DESC_FREQ_BAND(ZB_ZDO_NODE_DESC(), ((zb_uint16_t)frequency_band_p)); \
    ZB_ZDO_NODE_DESC()->mac_capability_flags = (mac_capability_flags_p);          \
    ZB_ZDO_NODE_DESC()->manufacturer_code = (zb_uint16_t)(manufacturer_code_p); \
    ZB_ZDO_NODE_DESC()->max_buf_size = (zb_uint8_t)(max_buf_size_p);              \
    ZB_ZDO_NODE_DESC()->max_incoming_transfer_size = (zb_uint16_t)(max_incoming_transfer_size_p); \
    ZB_ZDO_NODE_DESC()->server_mask = ((zb_uint16_t)(server_mask_p)) | (ZB_STACK_SPEC_VERSION << 9); /*see 2.3.2.3.10 Server Mask Field*/ \
    ZB_ZDO_NODE_DESC()->max_outgoing_transfer_size = (zb_uint16_t)(max_outgoing_transfer_size_p); \
    ZB_ZDO_NODE_DESC()->desc_capability_field = (zb_uint8_t)(desc_capability_field_p); \
  } while (ZB_FALSE)
/** @endcond */ /* internals_doc */

#define ZB_NODE_DESCRIPTOR_SERVER_MASK_SET_STACK_REVISION(server_mask, revision)  \
  (((server_mask) & 0x1FFU) | ((revision) << 9U))

#define ZB_NODE_DESCRIPTOR_SET_STACK_REVISION(revision) \
  (ZB_ZDO_NODE_DESC()->server_mask =                    \
    ZB_NODE_DESCRIPTOR_SERVER_MASK_SET_STACK_REVISION(  \
      ZB_ZDO_NODE_DESC()->server_mask, revision))       \

/** @cond internals_doc */
#define ZB_POWER_DESC_CUR_POWER_MODE_MASK     0x000FU /* 0000.0000 0000.1111 */
#define ZB_POWER_DESC_AVAIL_POWER_SOURCES_MASK 0x00F0U /* 0000.0000 1111.0000 */
#define ZB_POWER_DESC_CUR_POWER_SOURCE_MASK   0x0F00U /* 0000.1111 0000.0000 */
#define ZB_POWER_DESC_CUR_POWER_SOURCE_LEVEL_MASK 0xF000U /* 1111.0000 0000.0000 */

#define ZB_SET_POWER_DESC_CUR_POWER_MODE(desc, value)               \
  ( (desc)->power_desc_flags &= (zb_uint16_t)~ZB_POWER_DESC_CUR_POWER_MODE_MASK, \
    (desc)->power_desc_flags |= (zb_uint16_t)(value) )

#define ZB_GET_POWER_DESC_CUR_POWER_MODE(desc)                      \
  ( (desc)->power_desc_flags & ZB_POWER_DESC_CUR_POWER_MODE_MASK )

#define ZB_SET_POWER_DESC_AVAIL_POWER_SOURCES(desc, value)               \
  ( (desc)->power_desc_flags &= (zb_uint16_t)~ZB_POWER_DESC_AVAIL_POWER_SOURCES_MASK, \
    (desc)->power_desc_flags |= (zb_uint16_t)(((zb_uint16_t)value) << 4U) )

#define ZB_GET_POWER_DESC_AVAIL_POWER_SOURCES(desc)                      \
  ( ((desc)->power_desc_flags & ZB_POWER_DESC_AVAIL_POWER_SOURCES_MASK) >> 4U )

#define ZB_SET_POWER_DESC_CUR_POWER_SOURCE(desc, value)               \
  ( (desc)->power_desc_flags &= (zb_uint16_t)~ZB_POWER_DESC_CUR_POWER_SOURCE_MASK, \
    (desc)->power_desc_flags |= (zb_uint16_t)(((zb_uint16_t)value) << 8U) )

#define ZB_GET_POWER_DESC_CUR_POWER_SOURCE(desc)                      \
  ( ((desc)->power_desc_flags & ZB_POWER_DESC_CUR_POWER_SOURCE_MASK) >> 8U )

#define ZB_SET_POWER_DESC_CUR_POWER_SOURCE_LEVEL(desc, value)               \
  ( (desc)->power_desc_flags &= (zb_uint16_t)~ZB_POWER_DESC_CUR_POWER_SOURCE_LEVEL_MASK, \
    (desc)->power_desc_flags |= (zb_uint16_t)(((zb_uint16_t)value) << 12U) )

#define ZB_GET_POWER_DESC_CUR_POWER_SOURCE_LEVEL(desc)                  \
  ( ((desc)->power_desc_flags & ZB_POWER_DESC_CUR_POWER_SOURCE_LEVEL_MASK) >> 12U )


/**
  Set node power descriptor
  @param current_power_mode - current power mode
  @param available_power_sources - available power sources
  @param current_power_source - current power source
  @param current_power_source_level - current power source level

  NOTE: zboss_start() overwrites this descriptor with default values
        if ZB_SET_DEFAULT_POWER_DESCRIPTOR is defined
*/
void zb_set_node_power_descriptor(zb_current_power_mode_t current_power_mode, zb_uint8_t available_power_sources,
                                  zb_uint8_t current_power_source, zb_power_source_level_t current_power_source_level);

/**
 * Set node descriptor manufacturer code
 *
 * @param manuf_code - current power mode
*/
void zdo_set_node_descriptor_manufacturer_code(zb_uint16_t manuf_code);

/** @endcond */ /*internals_doc */

/**
 * Parent announce handler
 *
 * @param param - reference to buffer to construct response in
 * @param param_req - reference to buffer containing device announce being handled
 */
void zdo_parent_annce_handler(zb_uint8_t param, zb_uint16_t param_req);

#ifdef ZB_ROUTER_ROLE
/**
 * @brief Sends Parent_Annce
 *
 * @param param - reference to buffer containing command
 *
 * @see ZB R21 spec, subclause 2.4.3.1.12.
 */
void zdo_send_parent_annce(zb_uint8_t param);

void zdo_send_parent_annce_at_formation(zb_uint8_t param);
#endif

zb_uint8_t zb_commissioning_default_permit_duration(void);

#ifdef ZB_FORMATION
void zdo_formation_force_link(void);

void zdo_start_formation(zb_uint8_t param);

void zdo_commissioning_formation_done(zb_uint8_t param);

void zdo_commissioning_formation_failed(zb_uint8_t param);
#endif

void zdo_comm_set_permit_join(zb_uint8_t param, zb_callback_t cb);

void zdo_commissioning_leave(zb_bufid_t buf, zb_bool_t rejoin, zb_bool_t remove_children);

#ifdef ZB_DISTRIBUTED_SECURITY_ON
zb_bool_t zb_tc_is_distributed(void);

void zb_sync_distributed(void);
#endif

/**
   TLV management
 */

#if defined ZB_JOIN_CLIENT

/* [VK]: to avoid a MISRA warning for the Rule-5.1:
 * The external identifier 'xxx' clashes with other identifier(s) in the first 31 characters 1 time(s).
 */
void zb_zdo_st_key_neg_req_put_tlv(zb_uint8_t param);
#define zb_zdo_start_key_negotiation_req_put_tlv zb_zdo_st_key_neg_req_put_tlv

void zb_zdo_get_auth_tok_req_put_tlv(zb_uint8_t param);
#define zb_zdo_get_authentication_token_req_put_tlv zb_zdo_get_auth_tok_req_put_tlv

zb_ret_t zb_zdo_start_k_neg_r_proc_tlv(zb_uint8_t *tlv_ptr,
                                       zb_uint8_t tlv_data_len,
                                       zb_ieee_addr_t tc_ieee);

#define zb_zdo_start_key_negotiation_rsp_process_tlv zb_zdo_start_k_neg_r_proc_tlv

zb_ret_t zb_zdo_get_auth_tkn_rsp_proc_tlv(zb_uint8_t *tlv_ptr,
                                          zb_uint8_t tlv_data_len,
                                          zb_uint8_t *passphrase);

#define zb_zdo_get_authentication_token_rsp_process_tlv zb_zdo_get_auth_tkn_rsp_proc_tlv

#endif /* ZB_JOIN_CLIENT */

#if defined ZB_COORDINATOR_ROLE || defined ZB_ROUTER_ROLE

void zb_zdo_st_key_neg_rsp_put_tlv(zb_uint8_t param,
                                   zb_uint8_t *public_point);
#define zb_zdo_start_key_negotiation_rsp_put_tlv zb_zdo_st_key_neg_rsp_put_tlv


void zb_zdo_get_auth_tok_rsp_put_tlv(zb_uint8_t param, zb_uint8_t *passphrase);
#define zb_zdo_get_authentication_token_rsp_put_tlv zb_zdo_get_auth_tok_rsp_put_tlv

/**
 * Parse and validate incoming key negotiation request TLV
 * Places ref, public_keypoint_i (and for zigbee direct selected key neg method) in context
 *
 * @param tlv_ptr       pointer to the body of the TLV
 *                      (should not include the outer TLV header, describing the whole TLV's length)
 * @param tlv_data_len  actual length of the TLV body
 * @param is_dlk        if true, uses dlk
 *
 * @return If TLV appeared to be valid, returns (allocates) key negotiation context, filling following fields:
 *         ref, selected_key_neg_method, public_key_point_i
 *         If TLV is not valid, returns NULL
 *
 * @note it is guaranteed, that resp_param->status is ZB_APS_STATUS_SUCCESS if return value is not NULL
 */
zb_secur_ecdhe_common_ctx_t* zb_zdo_start_key_negotiation_req_process_parse_tlv(const zb_uint8_t* tlv_ptr,
                                                                                zb_uint8_t tlv_data_len,
                                                                                zb_uint8_t* resp_param,
                                                                                zb_bool_t is_dlk);

/**
    @return RET_OK, RET_ERROR, RET_NO_MATCH
 */
zb_ret_t zb_zdo_get_authentication_token_req_process_tlv(zb_uint8_t *tlv_ptr,
                                                         zb_uint8_t tlv_data_len);

#endif /* ZB_COORDINATOR_ROLE || ZB_ROUTER_ROLE */

void zb_zdo_key_neg_methods_put_tlv(zb_uint8_t param);

void zb_zdo_upd_key_req_put_tlvs(zb_uint8_t param, zb_uint8_t selected_method, zb_uint8_t selected_secret);

#ifdef ZB_JOIN_CLIENT
zb_ret_t zb_zdo_upd_key_req_process_tlv(zb_uint8_t *tlv_ptr,
                                        zb_uint8_t tlv_data_len,
                                        zb_uint16_t src_short_addr);
#endif /* ZB_JOIN_CLIENT */

#if defined ZB_COORDINATOR_ROLE || defined ZB_ROUTER_ROLE
zb_ret_t zb_zdo_select_key_neg_method(zb_ieee_addr_t partner_ieee_addr,
                                      zb_uint16_t partner_methods,
                                      zb_uint8_t  partner_secrets,
                                      zb_uint8_t *selected_method,
                                      zb_uint8_t *selected_secret);

zb_ret_t zb_zdo_select_key_neg_method_in_ecdhe_ctx(zb_secur_ecdhe_common_ctx_t *ecdhe_ctx);
#endif /* ZB_COORDINATOR_ROLE || ZB_ROUTER_ROLE */

zb_ret_t zb_secur_get_auth_token_key_by_ieee(zb_ieee_addr_t ieee_addr, zb_uint8_t *key);

#ifdef ZB_COORDINATOR_ROLE
zb_secur_ecdhe_common_ctx_t *zb_zdo_alloc_ecdhe_ctx_with_support_kn_tlv(zb_ieee_addr_t ieee_addr,
                                                                        zb_uint8_t supported_kn_methods,
                                                                        zb_uint8_t  supported_secrets);
#endif /* ZB_COORDINATOR_ROLE */

zb_ret_t zb_zdo_key_neg_methods_and_frag_param_process_tlv(zb_uint8_t *tlv_ptr,
                                                           zb_uint8_t tlv_data_len,
                                                           zb_uint8_t src_short_addr);
void zb_zdo_encapsulation_put_tlv(zb_uint8_t param,
                                  zb_secur_ecdhe_common_ctx_t *ecdhe_ctx);

void zb_zdo_encapsulation_process_tlv(zb_uint8_t *tlv_ptr,
                                      zb_uint8_t tlv_data_len,
                                      zb_secur_ecdhe_common_ctx_t *ecdhe_ctx);

zb_ret_t zb_zdo_clear_all_bind_put_tlv(zb_uint8_t param);
zb_ret_t zb_zdo_clear_all_bind_process_tlv(zb_uint8_t *tlv_ptr,
                                           zb_uint8_t tlv_data_len,
                                           zb_tlv_clear_all_bind_req_eui64_t *tlv_param);

/* Decommission TLV is the same as the Clear_all_bind TLV */
#define zb_zdo_decommission_put_tlv zb_zdo_clear_all_bind_put_tlv
zb_ret_t zb_zdo_decommission_process_tlv(zb_uint8_t *tlv_ptr,
                                         zb_uint8_t tlv_data_len,
                                         zb_tlv_decommission_req_eui64_t *tlv_param);

void zb_zdo_get_auth_level_req_put_target_ieee_tlv(zb_uint8_t param, zb_uint8_t *target_ieee);
zb_ret_t zb_zdo_get_auth_level_req_process_target_ieee_tlv(zb_uint8_t *tlv_ptr, zb_uint8_t tlv_data_len, zb_uint8_t *target_ieee);

void zb_zdo_get_auth_level_rsp_put_dev_auth_lvl_tlv(zb_uint8_t param, zb_uint8_t *target_ieee, zb_uint8_t initial_join_auth, zb_uint8_t active_lk_type);
zb_ret_t zb_zdo_get_auth_level_rsp_process_dev_auth_lvl_tlv(zb_uint8_t *tlv_ptr, zb_uint8_t tlv_data_len,
                                                            zb_uint8_t *target_ieee, zb_uint8_t *initial_join_auth, zb_uint8_t *active_lk_type);

typedef struct zb_zdo_processing_status_tlv_ctx_s
{
  zb_uint8_t conf_mode_param_tlv_status;
  zb_uint8_t next_channel_change_tlv_status;
  zb_uint8_t next_pan_id_tlv_status;
}zb_zdo_processing_status_tlv_ctx_t;

void zb_zdo_set_configuration_req_process_tlv(zb_uint8_t *tlv_ptr,
                                              zb_uint8_t tlv_data_len,
                                              zb_zdo_processing_status_tlv_ctx_t *tlv_statuses);

void zb_zdo_put_processing_status_tlv(zb_uint8_t param, zb_zdo_processing_status_tlv_ctx_t *tlv_statuses);


void zb_zdo_construct_relay_tlv(zb_uint8_t param, zb_uint8_t *joiner_ieee);

void zb_zdo_cut_all_except_relay_msg_tlv(zb_uint8_t param);
void zb_zdo_get_tunneled_frame_from_relay(zb_uint8_t param);

zb_ret_t zb_zdo_link_key_capabilities_process_tlv(zb_uint8_t *tlv_ptr, zb_uint8_t tlv_data_len, zb_uint8_t *capabilities);
void zb_zdo_link_key_cap_put_tlv(zb_uint8_t param, zb_uint8_t capabilities);

void zb_zdo_beacon_survey_resp_put_tlv(zb_uint8_t param, zb_zdo_beacon_survey_resp_params_t *resp_params);

zb_ret_t zb_zdo_put_tlv_by_id(zb_uint8_t param, zb_uint8_t id);

void zdo_load_production_config(void);
void zb_send_no_autostart_signal(zb_uint8_t param);
void zb_nlme_leave_indication_cont(zb_uint8_t param_buf);

/**
 * Returns if the device is authenticated in the network.
 */
zb_bool_t zb_zdo_authenticated(void);

/**
 * Returns if the device has a valid TCLK.
 */
zb_bool_t zb_zdo_tclk_valid(void);

#define ZB_IS_TC() ZB_IS_DEVICE_ZC()

void zb_get_use_extended_pan_id(zb_ext_pan_id_t ext_pan_id);

void zb_set_use_extended_pan_id(const zb_ext_pan_id_t ext_pan_id);

void zb_set_nwk_role_mode_common(zb_nwk_device_type_t device_type,
                                          zb_uint32_t channel_mask,
                                          zb_commissioning_type_t mode);

void zb_set_nwk_role_mode_common_ext(zb_nwk_device_type_t device_type,
                                              zb_channel_list_t channel_list,
                                              zb_commissioning_type_t mode);

zb_commissioning_type_t zb_zdo_get_commissioning_type(void);

void zb_zdo_data_indication(zb_uint8_t param);

void zb_zdo_init(void);

#ifdef ZB_ENABLE_ZCL
zb_bool_t zb_af_is_confirm_for_zcl_frame(zb_uint8_t param);

void zb_af_handle_zcl_frame_data_confirm(zb_uint8_t param);

zb_bool_t zb_af_handle_zcl_frame(zb_uint8_t param);
#endif /* ZB_ENABLE_ZCL */

void zb_zdo_send_status_res(zb_uint8_t param, zb_uint8_t status);

void zb_send_leave_indication_signal(zb_uint8_t param);

void zdo_send_signal_no_args(zb_uint8_t param, zb_uint16_t signal);

void zdo_mgmt_beacon_survey_req_handler(zb_uint8_t param);

void zdo_beacon_survey_hook(zb_uint8_t param);

void zb_zdo_beacon_survey_resp_handler(zb_uint8_t param);

void zdo_secur_get_config_rsp_hook(zb_uint8_t param);

void zdo_aps_challenge_timeout(zb_uint8_t param);

void zb_zdo_secur_get_auth_level_req_handle(zb_uint8_t param);


/* Challenge req/rsp functions */
#define ZB_ZDO_CHALLENGE_RSP_MIC_SIZE (8U)

void zb_zdo_secur_send_challenge_req(zb_uint8_t param);

void zb_zdo_secur_challenge_req_handle(zb_uint8_t param);

void zb_zdo_secur_challenge_resp_handle(zb_uint8_t param);

void zb_zdo_challenge_req_put_tlv (zb_uint8_t param, zb_uint8_t *rand);

zb_uint8_t *zb_zdo_challenge_rsp_put_tlv (zb_uint8_t param, zb_uint8_t *rand, zb_uint32_t out_cnt, zb_uint32_t challenge_cnt);

zb_ret_t zb_zdo_challenge_req_process_tlv(zb_uint8_t *tlv_ptr, zb_uint8_t tlv_data_len,
                                              zb_uint8_t *sender_ieee, zb_uint8_t *rand_value);
zb_ret_t zb_zdo_challenge_resp_process_tlv(zb_uint8_t *tlv_ptr, zb_uint8_t tlv_data_len,
                                              zb_uint8_t *sender_ieee, zb_uint8_t *rand_value,
                                              zb_uint32_t *out_counter, zb_uint32_t *challenge_counter, zb_uint8_t *mic);


#if defined NCP_MODE && !defined NCP_MODE_HOST
void zdo_send_ncp_join_signal(zb_uint8_t param);
#endif /* defined NCP_MODE && !defined NCP_MODE_HOST */

#ifdef ZB_PRODUCTION_CONFIG
/**
 * Check whether production configuration block is present in device
 *
 * @return production configuration presence status
 */
zb_bool_t zb_production_configuration_check_presence(void);

/**
 * Read data from production configuration header
 *
 * @param prod_cfg_hdr - pointer to production configuration header
 * @param hdr_len - size of production configuration header
 *
 * @return RET_OK is success, RET_ERROR otherwise
 */
zb_ret_t zb_production_cfg_read_header(zb_uint8_t *prod_cfg_hdr, zb_uint16_t hdr_len);

/**
 * Read data from production configuration block
 *
 * @param buffer - buffer to read into
 * @param len - length of block to read
 * @param offset - offset to read from
 *
 * @return RET_OK is success, RET_ERROR otherwise
 */
zb_ret_t zb_production_cfg_read(zb_uint8_t *buffer, zb_uint16_t len, zb_uint16_t offset);

#endif

#ifdef ZB_CERTIFICATION_HACKS
/**
   Sent network report command after panid conflict detect on ZR

   This is legacy pre-r23 Network report.
   It is present in r23 Test Specification at GU side - see  Test Case 8.2 (PAN ID Conflict)
 */
void zb_panid_conflict_send_legacy_network_report(zb_uint8_t param);
#endif

void zb_send_device_interview_signal_common(zb_bufid_t param, zb_address_ieee_ref_t addr_ref, zb_uint32_t signal_code, zb_uint16_t status);

/**
 * @brief Prepare parameters and send
 *        @ZB_ZDO_SIGNAL_DEVICE_READY_FOR_INTERVIEW signal with delay
 *
 * @param param - buffer that will be reused for storing the signal parameters
 * @addr_ref - ieee address reference to device which is going to be interviewed
 */
void zb_send_device_ready_for_interview_signal_delayed(zb_bufid_t param, zb_uint16_t addr_ref);

/**
 * @brief Prepare parameters and send
 *        @ZB_ZDO_SIGNAL_DEVICE_INTERVIEW_FINISHED signal with RET_ERROR status
 *
 * @param param - buffer for signal
 */
void zb_send_device_interview_failed_signal_delayed(zb_bufid_t param, zb_uint16_t addr_ref);

/**
 * @brief Prepare parameters and send
 *        @ZB_ZDO_SIGNAL_DEVICE_INTERVIEW_FINISHED signal with RET_OK status
 *
 * @param param - buffer for signal
 */
void zb_send_device_interview_done_signal_delayed(zb_bufid_t param, zb_uint16_t addr_ref);

#ifdef ZB_COORDINATOR_ROLE
/**
 * @brief Starts Device Interview stage on Trust Center
 *
 * @param param buffer for signal
 * @param joiner_ref reference to joiner's ieee address
 * @return zb_ret_t result of Device Interview starting
 */
zb_ret_t zb_start_device_interview_on_tc(zb_bufid_t param, zb_address_ieee_ref_t ieee_ref);
#endif /* ZB_COORDINATOR_ROLE */

#ifdef ZB_JOIN_CLIENT
/**
 * @brief Check device interview requirements
 * @return zb_bool_t TRUE if device interview should be started on joiner
 */
zb_bool_t zb_need_start_device_interview_on_joiner(zb_bool_t relayed, zb_bool_t verified);

/**
 * @brief Starts Device Interview stage on joiner
 * @return zb_ret_t result of Device Interview starting
 */
zb_ret_t zb_start_device_interview_on_joiner(void);

/**
 * @brief Stops Device Interview stage on joiner
 */
void zb_stop_device_interview_on_joiner(void);

/**
  @brief Checks whether Device Interview is started on the joiner's side
  @return Device Interview status flag
 */
zb_bool_t zb_is_device_interview_started_on_joiner(void);
#endif /* ZB_JOIN_CLIENT */

#ifdef ZB_COORDINATOR_ROLE
void send_transport_key_after_dlk(zb_uint8_t param, zb_secur_ecdhe_common_ctx_t *dlk_ctx_p);
#endif /* ZB_COORDINATOR_ROLE */

zb_uint8_t zdo_send_req_by_short(zb_uint16_t command_id, zb_uint8_t param, zb_callback_t cb,
                                 zb_uint16_t addr, zb_uint8_t resp_counter);
zb_uint8_t zdo_send_req_by_long(zb_uint16_t command_id, zb_uint8_t param, zb_callback_t cb,
                                zb_ieee_addr_t addr);
void zdo_send_resp_by_short(zb_uint16_t command_id, zb_uint8_t param, zb_uint16_t addr, zb_bool_t aps_secur);


/**
   @brief Enable broadcasting TX failure diagnostic at ZC

   If TX failure debug is switched on and 1/4 or more packets are failed to
   transmit due to CSMA/CA failed, ZC broadcasts
   Mgmt_NWK_Unsolicited_Enhanced_Update_notify with MAC TX statistics.

   That function is debug only.

   @param enable - if ZB_TRUE, enable that debug feature
 */
void zb_zdo_enable_tx_fail_debug(zb_bool_t enable);

zb_ret_t zb_check_next_panid(zb_uint16_t panid);

zb_ret_t zb_check_next_channel(zb_channel_page_t channel_page);

void zdo_maybe_discover_ieee(zb_uint16_t short_addr);

void zdo_maybe_discover_short(zb_address_ieee_ref_t ref);

#endif /* ZB_ZDO_H */
