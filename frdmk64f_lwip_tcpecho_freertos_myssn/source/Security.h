/**
* @file Security.h
*
* @date 		17/02/2021
* @author 		Katya Denisse Ortega Luna
* @brief		El componente realiza
*
*
*/

#ifndef Security_H_
#define Security_H_

/* system headers */
#include <stdint.h>
#include "err.h"
#include "lwip/api.h"

/* own headers */

/*****************************************************************************/
/* helper macros */

/* exported variables */

/* exported functions */
/**
 * @fn          void COUPSENS_vMonitor(void)
 * @brief       Obtiene el estado del sensor de acoplamiento trasero y delantero y los trasmite al CTV por CAN
 * @pre         Se necesita haber ejecutado las siguientes interfaces previamente sin errores: #ANTIGLITCH_vMonitor
 * @return      void
*/
extern          struct netconn* Security_stServerCreate(void);

extern			struct netconn* Security_stServerAccept(struct netconn* conn);

extern			void Security_vClientCreate(void);

extern			uint16_t Security_u16Receive(struct netconn *newconn, uint8_t* pu8DecryptMsg);

extern			void Security_vSend(struct netconn *newconn, const uint8_t* data, uint16_t u16len);

extern			void Security_vClose(struct netconn *newconn);


#endif /* Security_H_ */
