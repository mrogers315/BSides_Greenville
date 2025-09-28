################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v00x_it.c \
../User/main.c \
../User/system_ch32v00x.c 

C_DEPS += \
./User/ch32v00x_it.d \
./User/main.d \
./User/system_ch32v00x.d 

OBJS += \
./User/ch32v00x_it.o \
./User/main.o \
./User/system_ch32v00x.o 


EXPANDS += \
./User/ch32v00x_it.c.234r.expand \
./User/main.c.234r.expand \
./User/system_ch32v00x.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/roger/mounriver-studio-projects/CH32V003F4U6_WS2812_Bit_bang/Debug" -I"c:/Users/roger/mounriver-studio-projects/CH32V003F4U6_WS2812_Bit_bang/Core" -I"c:/Users/roger/mounriver-studio-projects/CH32V003F4U6_WS2812_Bit_bang/User" -I"c:/Users/roger/mounriver-studio-projects/CH32V003F4U6_WS2812_Bit_bang/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

