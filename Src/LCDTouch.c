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
  LCDTouchProcessInit ();
#endif

}
