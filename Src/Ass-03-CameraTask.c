/*
 *        $Id: Ass-03-CameraTask.c 2168 2020-06-14 21:52:43Z Peter $
 *  $Revision: 2168 $
 *      $Date: 2020-06-15 07:52:43 +1000 (Mon, 15 Jun 2020) $
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

  // while (1)
    osDelay(5000);

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
        FrameCounter++;
        FrameXferCplt = 0;
        LineCounter = 0;
      }

      if (LineCounter < XSIZE/2)
      {
        // Get control of LCD screen and skip line if we can't
        if (osMutexWait (LCDMutexHandle, 0) == osOK)
        {
        // Set the window for the camera image and change update direction
        ili9325_SetDisplayWindow(XSIZE-YSIZE/2-1, 1, YSIZE/2, XSIZE/2);
        ili9325_WriteReg(LCD_REG_3, 0x1000);

        // Set start of line and get ready to write to LCD GRAM
        ili9325_SetCursor (XSIZE-YSIZE/2-1+LineCounter, XSIZE/2);
        LCD_IO_WriteReg (LCD_REG_34);

        // Write line to LCD screen (only half) (should do using DMA)
        LCD_IO_WriteMultipleData ((uint8_t *) camera_buffer, XSIZE/2*2);

        // Set the window for full size again and restore update direction
        ili9325_SetDisplayWindow(0, 0, XSIZE, YSIZE);
        ili9325_WriteReg(LCD_REG_3, 0x1028);

        // Give back control
        osMutexRelease (LCDMutexHandle);
        }
      }
    }

    // Stop DCMI interface
    // HAL_DCMI_Stop (&hdcmi);

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

