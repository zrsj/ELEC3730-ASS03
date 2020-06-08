/*        $Id: LCDTouch.c 2111 2020-05-13 21:07:09Z Peter $
 *  $Revision: 2111 $
 *      $Date: 2020-05-14 07:07:09 +1000 (Thu, 14 May 2020) $
 *    $Author: Peter $
 */

#include "LCDTouch.h"

void
LCDTouch_main (void)
{
#ifdef STM32F407xx
  uint16_t i = 0;
#endif

  // Print welcome message
  // printf("\014");
  printf ("\n");
  printf ("%s\n", ASS_STRING);
  printf ("%s\n", VER_STRING);
  printf ("LCD Touch Example\n");

  // Initialise
#ifdef STM32F407xx
  LCDTouchProcessInit ();
#endif

  // Loop indefinitely
  while (1)
  {
#ifdef STM32F407xx
    LCDTouchProcess ();
#endif

#ifdef STM32F407xx
    if (i++ > 10000)
    {
      HAL_GPIO_TogglePin (GPIOD, LD3_Pin); // Toggle LED3
      i = 0;
    }
#endif
  }
}
