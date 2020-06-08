/*        $Id: LCDTouch-Lib.c 2111 2020-05-13 21:07:09Z Peter $
 *  $Revision: 2111 $
 *      $Date: 2020-05-14 07:07:09 +1000 (Thu, 14 May 2020) $
 *    $Author: Peter $
 */

#include "LCDTouch.h"

// STEPIEN: Added two touch panel functions to make the interface more
//          consistent with the LCD BSP.

#ifdef STM32F407xx
uint8_t
BSP_TP_Init (void)
{
  // Initialise the interface and calibrate
  TP_Init (); // This is an empty function since done by STM32CubeMX
  TouchPanel_Calibrate ();

  return 0;
}

uint8_t
BSP_TP_GetDisplayPoint (Coordinate *pDisplay)
{
  Coordinate *pScreen;

  pScreen = Read_Ads7846 ();
  if (pScreen == NULL)
  {
    return 1; // Error reading the touch panel
  }
  if (getDisplayPoint (pDisplay, pScreen, &matrix) == DISABLE)
  {
    return 1; // Error in LCD
  }
  return 0;
}
#endif
