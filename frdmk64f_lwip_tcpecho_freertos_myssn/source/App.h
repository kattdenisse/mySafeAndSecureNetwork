/**
* @file App.h
*
* @date 		17/02/2021
* @author 		Katya Denisse Ortega Luna
* @brief		El componente realiza
*
*
*/

#ifndef App_H_
#define App_H_

/* system headers */

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
extern          void  APP_vReceiveMsg(void);

extern          void APP_vInit(void);


#endif /* App_H_ */
