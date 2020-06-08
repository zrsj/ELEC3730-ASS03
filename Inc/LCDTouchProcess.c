/*        $Id: LCDTouchProcess.c 2111 2020-05-13 21:07:09Z Peter $
 *  $Revision: 2111 $
 *      $Date: 2020-05-14 07:07:09 +1000 (Thu, 14 May 2020) $
 *    $Author: Peter $
 */

#include "LCDTouch.h"

void
LCDTouchProcessInit (void)
{
  // STEPIEN: Assume horizontal display

  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init ();
  BSP_LCD_DisplayOn ();
  BSP_TP_Init ();

  // Display welcome message
  BSP_LCD_Clear (LCD_COLOR_WHITE);
  BSP_LCD_SetFont (&Font12);
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAtLine (0, (uint8_t*) ASS_STRING);
  BSP_LCD_DisplayStringAtLine (1, (uint8_t*) VER_STRING);

  // Create colour choices
  BSP_LCD_SetTextColor (LCD_COLOR_RED);
  BSP_LCD_FillRect (5, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_BLUE);
  BSP_LCD_FillRect (40, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_GREEN);
  BSP_LCD_FillRect (75, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_FillRect (110, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_MAGENTA);
  BSP_LCD_FillRect (145, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_ORANGE);
  BSP_LCD_FillRect (180, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_CYAN);
  BSP_LCD_FillRect (215, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_YELLOW);
  BSP_LCD_FillRect (250, 200, 30, 30);

  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_SetFont (&Font24);
  BSP_LCD_DisplayChar (290, 205, 'C');
  BSP_LCD_DrawHLine (0, 196, 320);

  BSP_LCD_DrawVLine (1, 198, 35);
  BSP_LCD_DrawVLine (37, 198, 35);
  BSP_LCD_DrawVLine (72, 198, 35);
  BSP_LCD_DrawVLine (107, 198, 35);
  BSP_LCD_DrawVLine (142, 198, 35);

  BSP_LCD_DrawVLine (177, 198, 35);
  BSP_LCD_DrawVLine (212, 198, 35);
  BSP_LCD_DrawVLine (247, 198, 35);
  BSP_LCD_DrawVLine (282, 198, 35);
  BSP_LCD_DrawVLine (317, 198, 35);

  BSP_LCD_DrawHLine (1, 232, 320);
}

void
LCDTouchProcess (void)
{
  // STEPIEN: Assume horizontal display

  uint16_t linenum = 0;

  if (BSP_TP_GetDisplayPoint (&display) == 0)
  {
    if (((display.y < 190) && (display.y >= 38)))
    {
      if ((display.x >= 318) || (display.x < 2))
      {
      }
      else
      {
        BSP_LCD_FillCircle (display.x, display.y, 2);
        // printf ("TOUCH:  Got (%3d,%3d)\n", display.x, display.y);
      }
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 180)
        && (display.x <= 210))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_ORANGE);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 215)
        && (display.x <= 245))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_CYAN);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 250)
        && (display.x <= 280))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_YELLOW);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 5)
        && (display.x <= 35))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_RED);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 40)
        && (display.x <= 70))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_BLUE);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 75)
        && (display.x <= 105))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_GREEN);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 110)
        && (display.x <= 140))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 145)
        && (display.x <= 175))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_MAGENTA);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 285)
        && (display.x <= 315))
    {
      BSP_LCD_SetFont (&Font12);
      for (linenum = 3; linenum < 16; linenum++)
      {
        BSP_LCD_ClearStringLine (linenum);
      }
    }
    else
    {
    }
  }
}
