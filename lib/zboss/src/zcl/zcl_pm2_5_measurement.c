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
/* PURPOSE: PM2.5 cluster implementation.
*/


#define ZB_TRACE_FILE_ID 139

#include "zb_common.h"

#if defined (ZB_ZCL_SUPPORT_CLUSTER_PM2_5_MEASUREMENT)

#include "zboss_api.h"
#include "zcl/zb_zcl_pm2_5_measurement.h"

#define PM2_5(_short)        ZB_ZCL_PM2_5_MEASUREMENT_ ## _short
#define PM2_5_ATTR(_short)   ZB_ZCL_ATTR_PM2_5_MEASUREMENT_ ## _short ## _ID

#define PM2_5_ATTR_DESC_A(_endpoint, _short)  \
                             zb_zcl_get_attr_desc_a((_endpoint),     \
                                ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT, \
                                ZB_ZCL_CLUSTER_SERVER_ROLE,          \
                                PM2_5_ATTR(_short))

static zb_ret_t check_value_pm2_5_measurement_server(zb_uint16_t  attr_id,
                                                     zb_uint8_t   endpoint,
                                                     zb_uint8_t  *value);

void zb_zcl_pm2_5_measurement_init_server(void)
{
  zb_zcl_add_cluster_handlers(ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
                              ZB_ZCL_CLUSTER_SERVER_ROLE,
                              check_value_pm2_5_measurement_server,
                              (zb_zcl_cluster_write_attr_hook_t)NULL,
                              (zb_zcl_cluster_handler_t)NULL);
}


void zb_zcl_pm2_5_measurement_init_client(void)
{
  zb_zcl_add_cluster_handlers(ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
                              ZB_ZCL_CLUSTER_CLIENT_ROLE,
                              (zb_zcl_cluster_check_value_t)NULL,
                              (zb_zcl_cluster_write_attr_hook_t)NULL,
                              (zb_zcl_cluster_handler_t)NULL);
}

static zb_ret_t check_value_pm2_5_measurement_server(zb_uint16_t  attr_id,
                                                     zb_uint8_t   endpoint,
                                                     zb_uint8_t  *value)
{
  zb_bool_t ok = ZB_TRUE;
  zb_ret_t ret = RET_OK;

  zb_single_t min_value, max_value;

  ZVUNUSED(endpoint);

  switch (attr_id)
  {
    case PM2_5_ATTR(MIN_MEASURED_VALUE):
    {
      zb_single_t min_value_new = ZB_ZCL_ATTR_GETSINGLE(value);

      if (min_value_new == PM2_5(MIN_MEASURED_VALUE_UNDEFINED))
      {
        ret = RET_OK;
      }
      else
      {
        zb_zcl_attr_t *attr_desc = PM2_5_ATTR_DESC_A(endpoint, MAX_MEASURED_VALUE);
        ZB_ASSERT(attr_desc);

        max_value = ZB_ZCL_GET_ATTRIBUTE_VAL_SINGLE(attr_desc);

        ok = ok && min_value_new >= PM2_5(MIN_MEASURED_VALUE_MIN_VALUE);
        ok = ok && min_value_new < max_value;

        ret = ok ? RET_OK : RET_ERROR;
      }

      break;
    }
    case PM2_5_ATTR(MAX_MEASURED_VALUE):
    {
      zb_single_t max_value_new = ZB_ZCL_ATTR_GETSINGLE(value);

      if (max_value_new == PM2_5(MAX_MEASURED_VALUE_UNDEFINED))
      {
        ret = RET_OK;
      }
      else
      {
        zb_zcl_attr_t *attr_desc = PM2_5_ATTR_DESC_A(endpoint, MIN_MEASURED_VALUE);
        ZB_ASSERT(attr_desc);

        min_value = ZB_ZCL_GET_ATTRIBUTE_VAL_SINGLE(attr_desc);

        ok = ok && max_value_new <= PM2_5(MAX_MEASURED_VALUE_MAX_VALUE);
        ok = ok && max_value_new > min_value;

        ret = ok ? RET_OK : RET_ERROR;
      }

      break;
    }
    case PM2_5_ATTR(MEASURED_VALUE):
    {
      zb_single_t new_measured_value = ZB_ZCL_ATTR_GETSINGLE(value);

      if (new_measured_value == PM2_5(MEASURED_VALUE_UNKNOWN))
      {
        ret = RET_OK;
      }
      else
      {
        zb_zcl_attr_t *min_attr_desc = PM2_5_ATTR_DESC_A(endpoint, MIN_MEASURED_VALUE);
        zb_zcl_attr_t *max_attr_desc = PM2_5_ATTR_DESC_A(endpoint, MAX_MEASURED_VALUE);
        ZB_ASSERT(min_attr_desc);
        ZB_ASSERT(max_attr_desc);

        min_value = ZB_ZCL_GET_ATTRIBUTE_VAL_SINGLE(min_attr_desc);

        max_value = ZB_ZCL_GET_ATTRIBUTE_VAL_SINGLE(max_attr_desc);

        ok = ok && new_measured_value <= max_value;
        ok = ok && new_measured_value >= min_value;

        ret = ok ? RET_OK : RET_ERROR;
      }

      break;
    }
    default:
      break;
  }

  TRACE_MSG(TRACE_ZCL1, "check_value_pm2_5_measurement ret %hd", (FMT__H, ret));
  return ret;
}

#endif /* ZB_ZCL_SUPPORT_CLUSTER_PM2_5_MEASUREMENT */
