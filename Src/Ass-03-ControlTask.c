/*
 *        $Id: Ass-03-ControlTask.c 2171 2020-06-14 22:25:52Z Peter $
 *  $Revision: 2171 $
 *      $Date: 2020-06-15 08:25:52 +1000 (Mon, 15 Jun 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

void StartControlTask(void const * argument)
{
  printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));

  // DrawBoxSend(100, 210, 210, 20); // Test during Week 12 lecture

  /*
  AddButtonSend( 5,  6,   80, 40, "One");
  AddButtonSend( 5,  51,  80, 40, "Two");
  AddButtonSend( 5,  96,  80, 40, "Three");
  AddButtonSend( 5, 141,  80, 40, "Four");
  AddButtonSend( 5, 186,  80, 40, "Five");
  AddButtonSend(90,   6,  80, 40, "Six");
  AddButtonSend(90,  51,  80, 40, "Seven");
  AddButtonSend(90,  96,  80, 40, "Eight");
  */

  while (1)
  {
    osDelay(1000);
  }
}
