/*
 *        $Id: Ass-03-LCDTask.c 2168 2020-06-14 21:52:43Z Peter $
 *  $Revision: 2168 $
 *      $Date: 2020-06-15 07:52:43 +1000 (Mon, 15 Jun 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

uint8_t intResetScreen = 0;

/*
 * This task manages the LCD display. It has the following widgets:
 *
 * - TextBox: Text inside a box
 * - DrawBox: Draws a box (example added during Week 12 lecture)
 *
 * Functions include those called to do the action and the ones
 * that actually do it.
 *
 */

// Declare handle for the LCD Task mail queue

osMailQId LCDTaskMailQueueHandle;

// Declare structures for the LCD Task messages

struct TextBox_s
{
  uint16_t x, y, w, h;  // Top left position and size
  char t[MESS_STR_LEN]; // String to be displayed
};

struct DrawBox_s
{
  uint16_t x, y, w, h;  // Top left position and size
};

struct LCDTaskMessage_s
{
  void (*f)(void *p);
  union
  {
    struct TextBox_s TB;
    struct DrawBox_s DB;
  };
} LCDTaskMessage;

// LCD Task functions

void TextBoxDo(void *p)
{
  struct TextBox_s pp;
  struct LCDTaskMessage_s *ppp;

  // Get information
  ppp = (struct LCDTaskMessage_s *)p;
  pp = ppp->TB;
  DEBUG(printf("DEBUG: -> TextBoxDo(%d,%d,%d,%d,'%s')\n",pp.x, pp.y, pp.w, pp.h, pp.t);)

  // Draw box and write string
  BSP_LCD_DrawRect(pp.x, pp.y, pp.w, pp.h);
  BSP_LCD_DisplayStringAt(pp.x+pp.w/2, pp.y+pp.h/2-16/2, pp.t, CENTER_MODE);
}

void TextBoxSend(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *t)
{
  struct LCDTaskMessage_s *mess;

  mess = osMailAlloc(LCDTaskMailQueueHandle,osWaitForever);
  if (mess == NULL)
  {
    printf("ERROR: Unable to send TextBoxSend() mail\n");
    return;
  }
  mess->f = &TextBoxDo;
  mess->TB.x = x;
  mess->TB.y = y;
  mess->TB.w = w;
  mess->TB.h = h;
  strncpy(mess->TB.t, t, MESS_STR_LEN);
  osMailPut(LCDTaskMailQueueHandle,mess);
}

void DrawBoxDo(void *p)
{
  struct DrawBox_s pp;
  struct LCDTaskMessage_s *ppp;

  // Get information
  ppp = (struct LCDTaskMessage_s *)p;
  pp = ppp->DB;
  DEBUG(printf("DEBUG: -> DrawBoxDo(%d,%d,%d,%d')\n",pp.x, pp.y, pp.w, pp.h);)

  // Draw box
  BSP_LCD_DrawRect(pp.x, pp.y, pp.w, pp.h);
}

void DrawBoxSend(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  struct LCDTaskMessage_s *mess;

  mess = osMailAlloc(LCDTaskMailQueueHandle,osWaitForever);
  if (mess == NULL)
  {
    printf("ERROR: Unable to send DrawBoxSend() mail\n");
    return;
  }
  mess->f = &DrawBoxDo;
  mess->DB.x = x;
  mess->DB.y = y;
  mess->DB.w = w;
  mess->DB.h = h;
  osMailPut(LCDTaskMailQueueHandle,mess);
}

// Initialise the mail queue
void InitLCDTaskMailQueue(void)
{
  osMailQDef(LCDTaskMailQueue, 16, LCDTaskMessage);
  LCDTaskMailQueueHandle = osMailCreate(osMailQ(LCDTaskMailQueue), NULL);
}

void StartLCDTask(void const * argument)
{
  osEvent evt;
  struct LCDTaskMessage_s *mess;

  printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));

  // Set default LCD display settings
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetFont(&Font16);

  // Loop waiting for messages for actions
  while (1)
  {

    evt = osMailGet(LCDTaskMailQueueHandle, osWaitForever);
    if (evt.status == osEventMail)
    {
      mess = (struct LCDTaskMessage_s *)evt.value.p;
      DEBUG(printf("DEBUG: LCDTask got message\n"));
      osMutexWait (LCDMutexHandle, osWaitForever);
      mess->f(mess);
      osMutexRelease (LCDMutexHandle);
      osMailFree(LCDTaskMailQueueHandle, evt.value.p);
    }
    osThreadYield();
  }
}
