################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/GPSManager.c" \
"../Sources/MessageManager.c" \
"../Sources/SCI.c" \
"../Sources/StringUtilis.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/GPSManager.c \
../Sources/MessageManager.c \
../Sources/SCI.c \
../Sources/StringUtilis.c \
../Sources/main.c \

OBJS += \
./Sources/GPSManager_c.obj \
./Sources/MessageManager_c.obj \
./Sources/SCI_c.obj \
./Sources/StringUtilis_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/GPSManager_c.obj" \
"./Sources/MessageManager_c.obj" \
"./Sources/SCI_c.obj" \
"./Sources/StringUtilis_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/GPSManager_c.d \
./Sources/MessageManager_c.d \
./Sources/SCI_c.d \
./Sources/StringUtilis_c.d \
./Sources/main_c.d \

C_DEPS_QUOTED += \
"./Sources/GPSManager_c.d" \
"./Sources/MessageManager_c.d" \
"./Sources/SCI_c.d" \
"./Sources/StringUtilis_c.d" \
"./Sources/main_c.d" \

OBJS_OS_FORMAT += \
./Sources/GPSManager_c.obj \
./Sources/MessageManager_c.obj \
./Sources/SCI_c.obj \
./Sources/StringUtilis_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/GPSManager_c.obj: ../Sources/GPSManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/GPSManager.args" -ObjN="Sources/GPSManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/MessageManager_c.obj: ../Sources/MessageManager.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MessageManager.args" -ObjN="Sources/MessageManager_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SCI_c.obj: ../Sources/SCI.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SCI.args" -ObjN="Sources/SCI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/StringUtilis_c.obj: ../Sources/StringUtilis.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/StringUtilis.args" -ObjN="Sources/StringUtilis_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


