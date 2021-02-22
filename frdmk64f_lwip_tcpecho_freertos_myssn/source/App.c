/**
* @file App.c
*
* @date 		17/02/2021
* @author 		Katya Denisse Ortega Luna
* @brief		El componente realiza
*
*
*/

/* System headers */

/* Used headers */
#include "Security.h"
#include "Security_def.h"

#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"

/* Own headers */
#include "App.h"
#include "App_cfg.h"
#include "App_def.h"

/* public_variables */

/* internal__pre-processor macros */

/* private_variables */

/* private_functions */
static void APP_s_vPrintData(const uint8_t* pu8Buff, uint16_t u16len)
{
	uint16_t u16i;
	
	for(u16i=0; u16i<u16len; u16i++)
	{
		PRINTF("0x%02x,", pu8Buff[u16i]);
	}
	PRINTF("\r\n");
}

/* public_functions */

/*!
 * @brief
 * @details
 */
void  APP_vReceiveMsg(void)
{
	uint8_t u8Msg[512] = {0};
	uint16_t u16Len;
	struct netconn *conn;
	struct netconn *newconn;
	uint8_t u8i;

	conn = Security_stServerCreate();

	while(1)
	{
		newconn = Security_stServerAccept(conn);

		if(newconn == NULL)
		{
			PRINTF("No accepted new connection\n");
		}
		else
		{

			PRINTF("Accepted new connection");
			PRINTF("\n");

			for(u8i = 0U; u8i < APP_nNUM_MSG_CFG; u8i++)
			{
				u16Len = Security_u16Receive(newconn, &u8Msg);
				PRINTF("Message received:");
				APP_s_vPrintData(u8Msg, u16Len);

				Security_vSend(newconn, &u8Msg, u16Len);
			}
			PRINTF("Finished new connection\n");
		}
		Security_vClose(newconn);
	}
}

void APP_vInit(void)
{
	sys_thread_new("APP_vReceiveMsg", APP_vReceiveMsg, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}

/* EOF */
