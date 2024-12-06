################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD/Src/fonts.c \
../Drivers/LCD/Src/ili9341.c 

OBJS += \
./Drivers/LCD/Src/fonts.o \
./Drivers/LCD/Src/ili9341.o 

C_DEPS += \
./Drivers/LCD/Src/fonts.d \
./Drivers/LCD/Src/ili9341.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD/Src/%.o Drivers/LCD/Src/%.su Drivers/LCD/Src/%.cyclo: ../Drivers/LCD/Src/%.c Drivers/LCD/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mvielmet/Documents/eecs373_squirrel_feeder/integration/Drivers/LCD/Inc" -I../Drivers/LCD/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-LCD-2f-Src

clean-Drivers-2f-LCD-2f-Src:
	-$(RM) ./Drivers/LCD/Src/fonts.cyclo ./Drivers/LCD/Src/fonts.d ./Drivers/LCD/Src/fonts.o ./Drivers/LCD/Src/fonts.su ./Drivers/LCD/Src/ili9341.cyclo ./Drivers/LCD/Src/ili9341.d ./Drivers/LCD/Src/ili9341.o ./Drivers/LCD/Src/ili9341.su

.PHONY: clean-Drivers-2f-LCD-2f-Src

