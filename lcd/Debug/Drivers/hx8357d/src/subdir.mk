################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/hx8357d/src/LCD_Driver.c 

OBJS += \
./Drivers/hx8357d/src/LCD_Driver.o 

C_DEPS += \
./Drivers/hx8357d/src/LCD_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/hx8357d/src/%.o Drivers/hx8357d/src/%.su Drivers/hx8357d/src/%.cyclo: ../Drivers/hx8357d/src/%.c Drivers/hx8357d/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"N:/EECS373/LCD_test/Drivers/hx8357d/inc" -I"N:/EECS373/LCD_test/Drivers/ili9341/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-hx8357d-2f-src

clean-Drivers-2f-hx8357d-2f-src:
	-$(RM) ./Drivers/hx8357d/src/LCD_Driver.cyclo ./Drivers/hx8357d/src/LCD_Driver.d ./Drivers/hx8357d/src/LCD_Driver.o ./Drivers/hx8357d/src/LCD_Driver.su

.PHONY: clean-Drivers-2f-hx8357d-2f-src

