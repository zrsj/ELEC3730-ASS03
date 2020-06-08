/*
 *        $Id: Ass-03-CameraTask.c 2139 2020-05-28 22:20:37Z Peter $
 *  $Revision: 2139 $
 *      $Date: 2020-05-29 08:20:37 +1000 (Fri, 29 May 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

// STEPIEN: Added from main()

#define XSIZE                          320
#define YSIZE                          240
#define BUFFER_LEN                     XSIZE

uint16_t camera_buffer[BUFFER_LEN];
uint16_t FrameXferCplt = 0;
uint16_t LineXferCplt = 0;
uint16_t LineCounter = 0;
uint16_t FrameCounter = 0;

void
StartCameraTask (void const * argument)
{
  printf ("INFO: Hello from %s!\n", pcTaskGetName (osThreadGetId ()));

  // Initialise the LCD here for now for the example
  BSP_LCD_Init ();
  BSP_LCD_Clear (LCD_COLOR_WHITE);

  // Set LCD cursor location
  ili9325_SetCursor (0, 0);

  // Prepare to write GRAM (0x22)
  LCD_IO_WriteReg (LCD_REG_34);

  // Infinite loop
  while (1)
  {
    // Get control
    //
    osMutexWait (SDIODCMIMutexHandle, osWaitForever);
    // printf ("INFO: %s has control of shared SDIO/DCMI pins!\n",
    //         pcTaskGetName (osThreadGetId ()));

    // Get a number of frames before giving releasing MUTEX
    FrameCounter = 0;
    while (FrameCounter < 20)
    {

      // Capture one line from camera
      HAL_DCMI_Start_DMA (&hdcmi, DCMI_MODE_CONTINUOUS,
                          (uint32_t) camera_buffer, BUFFER_LEN / 2);

      // STEPIEN: Note use of semaphore to indicate line capture complete
      osSemaphoreWait (DCMILineCompleteHandle, osWaitForever);

      // Check for frame synchronisation
      LineCounter++;
      if ((LineCounter >= YSIZE) && FrameXferCplt)
      {
        // Set LCD direction
        ili9325_SetCursor (0, 0);
        // Prepare to write GRAM (0x22)
        LCD_IO_WriteReg (LCD_REG_34);
        FrameCounter++;
        FrameXferCplt = 0;
        LineCounter = 0;
      }

      // Write line to LCD screen (should do using DMA)
      LCD_IO_WriteMultipleData ((uint8_t *) camera_buffer, BUFFER_LEN * 2);
    }

    // Stop DCMI interface
    HAL_DCMI_Stop (&hdcmi);

    // Give back control
    osMutexRelease (SDIODCMIMutexHandle);
    osThreadYield ();

  }
}

/**
 * @brief  Frame Event callback.
 * @param  None
 * @retval None
 */
void
HAL_DCMI_FrameEventCallback (DCMI_HandleTypeDef *hdcmi)
{
  FrameXferCplt = 1;
}

/**
 * @brief  Line Event callback.
 * @param  None
 * @retval None
 */
void
HAL_DCMI_LineEventCallback (DCMI_HandleTypeDef *hdcmi)
{
  osSemaphoreRelease (DCMILineCompleteHandle);
}

