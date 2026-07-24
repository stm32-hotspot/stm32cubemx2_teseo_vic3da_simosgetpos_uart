/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "example.h"
#include "teseo_vic3da.h"
#include "stdio.h"
#include "gnss_data.h"
#include "teseo_vic3da_conf.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables */
teseo_vic3da_object_t *pTeseovic3da0; /* pointer referencing the TESEO LIV3F object instance */
teseo_vic3da_io_t *io_ctx;
static GNSSParser_Data_t gnss_parser_data;

/** ########## Step 1 ##########
  * The init of TESEO LIV3F is triggered by the applicative code
  */

app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  PRINT_DBG("Booting...\r\n");
  pTeseovic3da0 = MX_TESEO_VIC3DA_getobject();
  /* Initialize teseo_vic3da */
  if (teseo_vic3da_drv_init(pTeseovic3da0, MX_TESEO_VIC3DA) != EXEC_STATUS_UNKNOWN)
  {
    PRINTF("[ERROR] teseo_vic3da initialization error\r\n");
    goto _app_init_exit;
  }
  PRINTF("[INFO] teseo_vic3da initialization completed\r\n");

  if (teseo_drv_register_callbacks(pTeseovic3da0) != EXEC_STATUS_UNKNOWN)
  {
    PRINTF("[ERROR] teseo_vic3da callback error\r\n");
    goto _app_init_exit;
  }

  /* Initialize GNSS Parser */
  if (GNSS_PARSER_Init(&gnss_parser_data) != 0)
  {
    PRINTF("[ERROR] GNSS_PARSER_Init error\r\n");
    goto _app_init_exit;
  }

  /* USER CODE BEGIN teseo_vic3da_PostTreatment */

  /* USER CODE END teseo_vic3da_PostTreatment */

  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
}

app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  GNSSParser_Status_t status, check;
  const teseo_vic3da_msg_t *gnss_msg;
#if (CONFIG_USE_FEATURE == 1)
  static uint8_t config_done = 0;
#endif /* CONFIG_USE_FEATURE */

  for (;;)
  {
#if (TESEO_VIC3DA_I2C_BUS == 1)
    teseo_vic3da_drv_i2c_background_process();
    HAL_Delay(100);
#if (USE_FREE_RTOS_NATIVE_API)
    vTaskDelay(portTICK_PERIOD_MS * 5U);
#else
#if (USE_AZRTOS_NATIVE_API)
    tx_thread_sleep(((TX_TIMER_TICKS_PER_SECOND / 100)));
#endif /* USE_AZRTOS_NATIVE_API */
#endif /* USE_FREE_RTOS_NATIVE_API */
#endif /* teseo_vic3da_I2C_BUS */

#if (CONFIG_USE_FEATURE == 1)
    /* Use config_done to control configuration */
    if (!config_done)
    {
      uint32_t low_mask = 0x18004F;
      uint32_t high_mask = GEOFENCE;
      PRINT_OUT("\n\rConfigure Message List\n\r");
      app_cfg_msg_list(low_mask, high_mask);
      /* Delay to allow Teseo to process the message list configuration before sending the next command */
      HAL_Delay(1000);

      PRINT_OUT("\n\rEnable Geofence\r\n");
      app_en_feature("GEOFENCE,1");
      /* Delay to allow Teseo to process the geofence enable command before sending the next command */
      HAL_Delay(500);

      PRINT_OUT("\n\rConfigure Geofence Circle\n\r");
      app_geofence_cfg("Geofence-Lecce");

      /* Update config_done to indicate configuration is complete */
      config_done = 1;
    }
#endif /* CONFIG_USE_FEATURE */

    gnss_msg = (teseo_vic3da_msg_t *)teseo_vic3da_drv_get_message(pTeseovic3da0);

    if (gnss_msg == NULL)
    {
      continue;
    }

    check = GNSS_PARSER_CheckSanity((uint8_t *)gnss_msg->buf, gnss_msg->len);

    if (check != GNSS_PARSER_ERROR)
    {
      for (uint8_t m = 0; m < NMEA_MSGS_NUM; m++)
      {
        status = GNSS_PARSER_ParseMsg(&gnss_parser_data, (eNMEAMsg)m, (uint8_t *)gnss_msg->buf);

        if ((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPGGA))
        {
          GNSS_DATA_GetValidInfo(&gnss_parser_data);
        }
#if (CONFIG_USE_FEATURE == 1)
        if ((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMGEOFENCE))
        {
          GNSS_DATA_GetGeofenceInfo(&gnss_parser_data);
        }
        if ((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSGL))
        {
          GNSS_DATA_GetMsglistAck(&gnss_parser_data);
        }
        if ((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSAVEPAR))
        {
          GNSS_DATA_GetGNSSAck(&gnss_parser_data);
        }
#endif /* CONFIG_USE_FEATURE */
      }
    }

    if (teseo_vic3da_drv_release_message(pTeseovic3da0, (teseo_vic3da_msg_t *)gnss_msg) != EXEC_STATUS_UNKNOWN)
    {
      break;
    }
  }

  return_status = EXEC_STATUS_OK;

  return return_status;
}

#if (CONFIG_USE_FEATURE == 1)
/* CfgMessageList */
static void app_cfg_msg_list(uint32_t low_mask, uint32_t high_mask)
{
  GNSS_DATA_CfgMessageList(low_mask, high_mask);
}

static void app_en_feature(char *command)
{
  if (strcmp(command, "GEOFENCE,1") == 0)
  {
    GNSS_DATA_EnableGeofence(1);
  }
  if (strcmp(command, "GEOFENCE,0") == 0)
  {
    GNSS_DATA_EnableGeofence(0);
  }
}

static void app_geofence_cfg(char *command)
{
  if (strcmp(command, "Geofence-Lecce") == 0)
  {
    GNSS_DATA_ConfigGeofence(&Geofence_STLecce);
  }
  if (strcmp(command, "Geofence-Catania") == 0)
  {
    GNSS_DATA_ConfigGeofence(&Geofence_Catania);
  }
}
#endif /* CONFIG_USE_FEATURE */

uint8_t GNSS_PRINT(char *p_buffer)
{
  if (HAL_UART_Transmit(BASIC_STDIO_UART_GETHANDLE(), (uint8_t *)p_buffer, (uint16_t)strlen((char *)p_buffer),
                        1000) != HAL_OK)
  {
    return 1;
  }
  fflush(stdout);

  return 0;
}

uint8_t GNSS_PUTC(char p_char)
{
  if (HAL_UART_Transmit(BASIC_STDIO_UART_GETHANDLE(), (uint8_t *)&p_char, 1, 1000) != HAL_OK)
  {
    return 1;
  }
  fflush(stdout);

  return 0;
}
void GNSSResetModule(void)
{
  teseo_drv_reset_module(pTeseovic3da0);
}

/** ########## Step 3 ##########
  * In this example, app_deinit is never called and is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  teseo_vic3da_drv_deinit(pTeseovic3da0);

  return EXEC_STATUS_OK;
}