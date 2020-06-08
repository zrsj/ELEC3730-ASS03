/*********************************************************************************************************
*
* File                : sccb.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : Yehui
*
*                                  (c) Copyright 2005-2017, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sccb.h"
#include "i2c.h"

/* --EV5 */
#define  I2C_EVENT_MASTER_MODE_SELECT                      ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */

/* --EV6 */
#define  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED        ((uint32_t)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */
#define  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED           ((uint32_t)0x00030002)  /* BUSY, MSL and ADDR flags */

/* Master RECEIVER mode -----------------------------*/ 
/* --EV7 */
#define  I2C_EVENT_MASTER_BYTE_RECEIVED                    ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */

/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                 ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */
/* --EV8_2 */
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED                 ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */





__IO uint32_t  DCMI_TIMEOUT_MAX = 10000;

static ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);
/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void SCCB_GPIO_Config(void)
{
//	I2C_InitTypeDef  SCCB_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure; 
//	
//	RCC_AHB1PeriphClockCmd(Open207V_SCCB_SDA_GPIO_CLK | Open207V_SCCB_SCL_GPIO_CLK,ENABLE);
//	
//	RCC_APB1PeriphClockCmd(Open207V_SCCB_CLK,ENABLE);
//	
//	GPIO_PinAFConfig(Open207V_SCCB_SDA_GPIO_PORT, Open207V_SCCB_SDA_SOURCE, Open207V_SCCB_SDA_AF);
//	GPIO_PinAFConfig(Open207V_SCCB_SCL_GPIO_PORT, Open207V_SCCB_SCL_SOURCE, Open207V_SCCB_SCL_AF);
//	
//	GPIO_InitStructure.GPIO_Pin =  Open207V_SCCB_SDA_PIN | Open207V_SCCB_SCL_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//		
//	I2C_DeInit(Open207V_SCCB);
//	SCCB_InitStructure.I2C_Mode = I2C_Mode_I2C;
//	SCCB_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
//	SCCB_InitStructure.I2C_OwnAddress1 = SCCB_SLAVE_ADDRESS7;
//	SCCB_InitStructure.I2C_Ack = I2C_Ack_Enable;
//	SCCB_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	SCCB_InitStructure.I2C_ClockSpeed = SCCB_SPEED;
//	
//	I2C_Cmd(Open207V_SCCB, ENABLE);
//	I2C_Init(Open207V_SCCB, &SCCB_InitStructure);
//	
//	I2C_AcknowledgeConfig(Open207V_SCCB, ENABLE);	
}

/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Device: OV7670 write address.
  * @param  Addr: OV7670 register address. 
  * @param  Data: data to be written to the specific register 
  * @retval 0x00 if write operation is OK. 
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
uint8_t DCMI_SingleRandomWrite(uint8_t Reg, uint8_t Data)
{
  if(HAL_I2C_Mem_Write(&hi2c2, OV7670_DEVICE_ADDRESS, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Data, 1, 100) != HAL_OK)
  {
    return 0xFF;
  }
  return 0;
}

/**
  * @brief  Reads a byte from a specific Camera register 
  * @param  Device: OV7670 write address.
  * @param  Addr: OV7670 register address. 
  * @retval data read from the specific register or 0xFF if timeout condition 
  *         occured. 
  */

uint8_t DCMI_SingleRandomRead(uint8_t Reg, uint8_t *Data)
{
  /*
  Note: Not like OV2640, OV7670 doesn't generate SIOC clock, so the board must prepare Stop after receiving data 
        then generate Start Condition.
        In this case, to use HAL_I2C_Mem_Read(), you have to change the function I2C_RequestMemoryRead() and 
        add this line hi2c->Instance->CR1 |= I2C_CR1_STOP; before the 2nd hi2c->Instance->CR1 |= I2C_CR1_START;
  */

  // STEPIEN: Followed above instructions. The initialisation gives the correct response now.
  uint8_t state;
  state = HAL_I2C_Mem_Read(&hi2c2, OV7670_DEVICE_ADDRESS, Reg, I2C_MEMADD_SIZE_8BIT, Data, 1, 100);
  if(state != HAL_OK)
  {
    return 0xFF;
  }
  return 0;
  
  uint32_t timeout = DCMI_TIMEOUT_MAX;

    /* Clear AF flag if arised */
  hi2c2.Instance->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  hi2c2.Instance->CR1 |= I2C_CR1_START;


  /* Test on I2C2 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(hi2c2.Instance, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  hi2c2.Instance->DR = OV7670_DEVICE_WRITE_ADDRESS;
 
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(hi2c2.Instance, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send I2C2 location address LSB */
  hi2c2.Instance->DR = (uint8_t)Reg;

  /* Test on I2C2 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(hi2c2.Instance, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  hi2c2.Instance->SR1 |= (uint16_t)0x0400;
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  hi2c2.Instance->CR1 |= I2C_CR1_STOP;

  /*-----------------------------------------------------------------------------------*/
  /* Generate the Start Condition */
  hi2c2.Instance->CR1 |= I2C_CR1_START;

  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(hi2c2.Instance, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/
  /* Send DCMI selcted device slave Address for write */
  hi2c2.Instance->DR = OV7670_DEVICE_READ_ADDRESS;
   
  /* Test on I2C2 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(hi2c2.Instance, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
      
  /*-----------------------------------------------------------------------------------*/
  /* Prepare an NACK for the next data received */
  hi2c2.Instance->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ACK);

  /* Test on Open207V_SCCB EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(hi2c2.Instance, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  /*-----------------------------------------------------------------------------------*/    
  /* Prepare Stop after receiving data */
  hi2c2.Instance->CR1 |= I2C_CR1_STOP;

  /*-----------------------------------------------------------------------------------*/
  /* Receive the Data */
  *Data = (uint8_t)I2C2->DR;
  /* Clear AF flag if arised */
  hi2c2.Instance->SR1 |= (uint16_t)0x0400;

  return 0;
}

static ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_EVENT(I2C_EVENT));

  /* Read the I2Cx status register */
  flag1 = I2Cx->SR1;
  flag2 = I2Cx->SR2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);

  /* Check whether the last event contains the I2C_EVENT */
  if ((lastevent & I2C_EVENT) == I2C_EVENT)
  {
    /* SUCCESS: last event is equal to I2C_EVENT */
    status = SUCCESS;
  }
  else
  {
    /* ERROR: last event is different from I2C_EVENT */
    status = ERROR;
  }
  /* Return status */
  return status;
}
