################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/WiringSerial/Serial.c 

OBJS += \
./Core/WiringSerial/Serial.o 

C_DEPS += \
./Core/WiringSerial/Serial.d 


# Each subdirectory must supply rules for building sources it contributes
Core/WiringSerial/Serial.o: ../Core/WiringSerial/Serial.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/home/mahendra/STM32CubeIDE/workspace_1.5.0/STM32_Ringbuffer/Core/WiringSerial" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/WiringSerial/Serial.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

