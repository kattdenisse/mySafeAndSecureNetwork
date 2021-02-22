/**
* @file Security.c
*
* @date 		17/02/2021
* @author 		Katya Denisse Ortega Luna
* @brief		El componente realiza
*
*
*/

/* System headers */

/* Used headers */
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"
#include "err.h"

#include "aes.h"
#include "fsl_crc.h"

/* Own headers */
#include "Security.h"
#include "Security_cfg.h"
#include "Security_def.h"

/* public_variables */

/* internal__pre-processor macros */
#define SECURITY_s_nCRC_SIZE				(4U)

/* private_variables */

/* private_functions */

/*!
 * @brief
 * @details
 */
static void Security_s_vInitCrc32(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial         = 0x04C11DB7U;
    config.seed               = seed;
    config.reflectIn          = true;
    config.reflectOut         = true;
    config.complementChecksum = true;
    config.crcBits            = kCrcBits32;
    config.crcResult          = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

static uint32_t Security_s_u32CRC32(const uint8_t* pu8Msg, size_t sLen)
{
	CRC_Type *base = CRC0;
	uint32_t u32Checksum;

	Security_s_vInitCrc32(base, 0xFFFFFFFFU);
    CRC_WriteData(base, pu8Msg, sLen);
    u32Checksum = CRC_Get32bitResult(base);

    PRINTF("CRC-32: 0x%08x", u32Checksum);
	PRINTF("\r\n");

	return u32Checksum;
}

static void Security_s_vEncryptAES(const uint8_t* p8Buff, uint8_t* pu8EncryptMsg, uint16_t u16Len)
{
	/* AES data */
	uint8_t key[] = KEY_CFG;
	uint8_t iv[]  = IV_CFG;
	struct AES_ctx ctx;
	size_t padded_len;

	/* Init the AES context structure */
	AES_init_ctx_iv(&ctx, key, iv);

	/* To encrypt an array its lenght must be a multiple of 16 so we add zeros */
	padded_len = u16Len + (16 - (u16Len%16) );
	memcpy(pu8EncryptMsg, p8Buff, u16Len);

	AES_CBC_encrypt_buffer(&ctx, pu8EncryptMsg, padded_len);

	PRINTF("Encrypted Message: ");
	for(int i=0; i<u16Len; i++) {
		PRINTF("0x%02x,", pu8EncryptMsg[i]);
	}
	PRINTF("\r\n");
}

static uint16_t Security_s_u16DecryptAES(uint8_t* pu8Buff, const uint8_t* pu8EncryptMsg, uint16_t u16Len)
{
	/* AES data */
	uint8_t key[] = KEY_CFG;
	uint8_t iv[]  = IV_CFG;
	struct AES_ctx ctx;
	size_t padded_len;

	/* Init the AES context structure */
	AES_init_ctx_iv(&ctx, key, iv);

	/* To encrypt an array its lenght must be a multiple of 16 so we add zeros */
	padded_len = u16Len + (16 - (u16Len%16) );
	memcpy(pu8Buff, pu8EncryptMsg, u16Len);

	AES_CBC_decrypt_buffer(&ctx, pu8Buff, padded_len);
	
	PRINTF("Decrypted Message: ");
	for(int i=0; i<u16Len; i++) {
		PRINTF("0x%02x,", pu8Buff[i]);
	}
	PRINTF("\r\n");
	
	return u16Len;
}

static void Security_s_vPackageMsg(uint8_t* pu8SecureMsg, uint8_t* pu8EncryptMsg, uint8_t* pu8CRC, uint16_t u16Len)
{
	uint16_t u16i;
	uint16_t u16j;
	
	for(u16i=0U; u16i<u16Len; u16i++) 
	{
		pu8SecureMsg[u16i] = pu8EncryptMsg[u16i];
	}
	for(u16j=0; u16j<(uint16_t)SECURITY_s_nCRC_SIZE; u16j++, u16i++) 
	{
		pu8SecureMsg[u16i] = pu8CRC[u16j];
	}
}

static void Security_s_vUnpackMsg(uint8_t* pu8SecureMsg, uint8_t* pu8DecryptMsg, uint8_t* pu8CRC, uint16_t u16Len)
{
	uint16_t u16i;
	uint16_t u16j;
	
	for(u16i=0U; u16i<u16Len; u16i++) 
	{
		pu8DecryptMsg[u16i] = pu8SecureMsg[u16i];
	}
	for(u16j=0; u16j<(uint16_t)SECURITY_s_nCRC_SIZE; u16j++, u16i++) 
	{
		pu8CRC[u16j] = pu8SecureMsg[u16i];
	}	
}

static void Security_s_vPrintData(const uint8_t* pu8Buff, uint16_t u16len)
{
	uint16_t u16i;

	for(u16i=0; u16i<u16len; u16i++)
	{
		PRINTF("0x%02x,", pu8Buff[u16i]);
	}
	PRINTF("\r\n\n");
}

/* public_functions */

struct netconn* Security_stServerCreate(void)
{
	struct netconn* conn;

	/* Create a new connection identifier. */
	/* Bind connection to well known port number 7. */
	conn = netconn_new(NETCONN_TCP);
	netconn_bind(conn, IP_ADDR_ANY, 7);
	
	LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

	/* Tell connection to go into listening mode. */
	netconn_listen(conn);

	return conn;
}

struct netconn* Security_stServerAccept(struct netconn *conn)
{
	struct netconn* newconn;
	err_t err;
	
    /* Grab new connection. */
    err = netconn_accept(conn, &newconn);
	
	return newconn;
}

void Security_vClientCreate(void)
{
}

uint16_t Security_u16Receive(struct netconn *newconn, uint8_t* pu8DecryptMsg)
{
	/* Process the new connection. */
    struct netbuf *buf;
    void *data;
	uint8_t u8SecureMsg[512];
	uint16_t u16len;
	uint32_t u32ReadCRC;
	uint32_t u32CRC;
	err_t err;

    if ((err = netconn_recv(newconn, &buf)) == ERR_OK)
	{
    	netbuf_data(buf, &data, &u16len);
			
		u16len = u16len - (uint16_t)SECURITY_s_nCRC_SIZE;
		Security_s_vUnpackMsg(data, &u8SecureMsg, (uint8_t*)&u32ReadCRC, u16len);
		u32CRC = Security_s_u32CRC32((const uint8_t*)&u8SecureMsg, u16len);
			
		PRINTF("Encrypted message received:");
		Security_s_vPrintData((void*)&u8SecureMsg, u16len);

		if(u32CRC == u32ReadCRC)
		{
			u16len = Security_s_u16DecryptAES(pu8DecryptMsg, (const uint8_t*)&u8SecureMsg, u16len);
		}
		else
		{
		}
        netbuf_delete(buf);
      }
    else
    {
    	PRINTF("Encrypted message NO received: \n");
    }
    return u16len;
}

void Security_vSend(struct netconn *newconn, const uint8_t* data, uint16_t u16len)
{
	/* Process the new connection. */
    struct netbuf *buf;
	uint8_t u8EncryptMsg[512];
	uint8_t u8SecureMsg[512];
	uint32_t u32CRC;
	err_t err;

	Security_s_vEncryptAES(data, &u8EncryptMsg, u16len);
	u32CRC = Security_s_u32CRC32((const uint8_t*)&u8EncryptMsg, u16len);
	Security_s_vPackageMsg(&u8SecureMsg, &u8EncryptMsg, (uint8_t*)&u32CRC, u16len);

	u16len = u16len + (uint16_t)SECURITY_s_nCRC_SIZE;

	PRINTF("Encrypted message sent:");
	Security_s_vPrintData((void*)&u8SecureMsg, u16len);

	err = netconn_write(newconn, &u8SecureMsg, u16len, NETCONN_COPY);
}

void Security_vClose(struct netconn *newconn)
{
	/*printf("Got EOF, looping\n");*/ 
    /* Close connection and discard connection identifier. */
    netconn_close(newconn);
    netconn_delete(newconn);
}

/* EOF */
