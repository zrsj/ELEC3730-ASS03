/*
 *        $Id: Ass-03-TPTask.c 2139 2020-05-28 22:20:37Z Peter $
 *  $Revision: 2139 $
 *      $Date: 2020-05-29 08:20:37 +1000 (Fri, 29 May 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

void StartTPTask(void const * argument)
{
  printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));
  while (1)
  {
	  osDelay(1000);
  }
}
