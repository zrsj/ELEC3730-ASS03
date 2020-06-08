/*        $Id: LCDTouch.h 2111 2020-05-13 21:07:09Z Peter $
 *  $Revision: 2111 $
 *      $Date: 2020-05-14 07:07:09 +1000 (Thu, 14 May 2020) $
 *    $Author: Peter $
 */

// LCD Touch example include file

#ifndef LCDTOUCH_H_
#define LCDTOUCH_H_

// Standard includes

extern void
initialise_monitor_handles (void); // STEPIEN: To allow printing to console

#ifdef STM32F407xx
#include "stm32f4xx_hal.h"
#include "openx07v_c_lcd.h"
#include "touch_panel.h"
#include "main.h"
#else
#include <windows.h>
#endif
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

// Description and version strings
#define ASS_STRING "ELEC3730-2020s1 LCD Touch Example"
#define VER_STRING "Ver: 01 $Rev: 2111 $"

// Example main
extern void
LCDTouch_main (void);

// Example initialisation and loop
extern void
LCDTouchProcessInit (void);
extern void
LCDTouchProcess (void);

// Library functions
#ifdef STM32F407xx
extern uint8_t
BSP_TP_Init (void);
extern uint8_t
BSP_TP_GetDisplayPoint (Coordinate *pDisplay);
#endif

#endif /* LCDTOUCH_H_ */
