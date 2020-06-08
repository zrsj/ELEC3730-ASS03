################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Ass-03-CameraTask.c \
../Src/Ass-03-ControlTask.c \
../Src/Ass-03-LCDTask.c \
../Src/Ass-03-Lib.c \
../Src/Ass-03-SDTask.c \
../Src/Ass-03-TPTask.c \
../Src/Ass-03-TimeTask.c \
../Src/LCDTouch-Lib.c \
../Src/LCDTouch.c \
../Src/LCDTouchProcess.c \
../Src/bsp_driver_sd.c \
../Src/dcmi.c \
../Src/dma.c \
../Src/fatfs.c \
../Src/fatfs_platform.c \
../Src/freertos.c \
../Src/fsmc.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/sd_diskio.c \
../Src/sdio.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_tim.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tim.c 

OBJS += \
./Src/Ass-03-CameraTask.o \
./Src/Ass-03-ControlTask.o \
./Src/Ass-03-LCDTask.o \
./Src/Ass-03-Lib.o \
./Src/Ass-03-SDTask.o \
./Src/Ass-03-TPTask.o \
./Src/Ass-03-TimeTask.o \
./Src/LCDTouch-Lib.o \
./Src/LCDTouch.o \
./Src/LCDTouchProcess.o \
./Src/bsp_driver_sd.o \
./Src/dcmi.o \
./Src/dma.o \
./Src/fatfs.o \
./Src/fatfs_platform.o \
./Src/freertos.o \
./Src/fsmc.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/sd_diskio.o \
./Src/sdio.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_tim.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tim.o 

C_DEPS += \
./Src/Ass-03-CameraTask.d \
./Src/Ass-03-ControlTask.d \
./Src/Ass-03-LCDTask.d \
./Src/Ass-03-Lib.d \
./Src/Ass-03-SDTask.d \
./Src/Ass-03-TPTask.d \
./Src/Ass-03-TimeTask.d \
./Src/LCDTouch-Lib.d \
./Src/LCDTouch.d \
./Src/LCDTouchProcess.d \
./Src/bsp_driver_sd.d \
./Src/dcmi.d \
./Src/dma.d \
./Src/fatfs.d \
./Src/fatfs_platform.d \
./Src/freertos.d \
./Src/fsmc.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/sd_diskio.d \
./Src/sdio.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_tim.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/BSP" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/BSP/Fonts" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Inc" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/CMSIS/Include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


