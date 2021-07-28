################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./tm4c123gh6pm_startup_ccs.obj" \
"./Application/Init.obj" \
"./Application/SW_StateMachine.obj" \
"./Application/main.obj" \
"./Application/uartstdio.obj" \
"./FatFs_Control/SPI_Control.obj" \
"./FatFs_Control/ff.obj" \
"./FatFs_Control/sdmm.obj" \
"./Source/croutine.obj" \
"./Source/event_groups.obj" \
"./Source/list.obj" \
"./Source/queue.obj" \
"./Source/stream_buffer.obj" \
"./Source/tasks.obj" \
"./Source/timers.obj" \
"./Source/portable/CCS/ARM_CM4F/port.obj" \
"./Source/portable/CCS/ARM_CM4F/portasm.obj" \
"./Source/portable/MemMang/heap_2.obj" \
"C:/ti/TivaWare_C_Series-2.2.0.295/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Application/subdir_vars.mk
-include FatFs_Control/subdir_vars.mk
-include Source/subdir_vars.mk
-include Source/portable/CCS/ARM_CM4F/subdir_vars.mk
-include Source/portable/MemMang/subdir_vars.mk
-include subdir_rules.mk
-include Application/subdir_rules.mk
-include FatFs_Control/subdir_rules.mk
-include Source/subdir_rules.mk
-include Source/portable/CCS/ARM_CM4F/subdir_rules.mk
-include Source/portable/MemMang/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
StateMachine_TestQueue_MusicPlayer_FreeRTOS2.out \

EXE_OUTPUTS__QUOTED += \
"StateMachine_TestQueue_MusicPlayer_FreeRTOS2.out" \

BIN_OUTPUTS += \
StateMachine_TestQueue_MusicPlayer_FreeRTOS2.hex \

BIN_OUTPUTS__QUOTED += \
"StateMachine_TestQueue_MusicPlayer_FreeRTOS2.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "StateMachine_TestQueue_MusicPlayer_FreeRTOS2.out"

# Tool invocations
StateMachine_TestQueue_MusicPlayer_FreeRTOS2.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"StateMachine_TestQueue_MusicPlayer_FreeRTOS2.map" --heap_size=0 --stack_size=1024 -i"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/lib" -i"C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source" -i"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" -i"C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Application" -i"C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/FatFs_Control" -i"C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/portable/CCS/ARM_CM4F" -i"C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/portable/MemMang" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="StateMachine_TestQueue_MusicPlayer_FreeRTOS2_linkInfo.xml" --rom_model -o "StateMachine_TestQueue_MusicPlayer_FreeRTOS2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

StateMachine_TestQueue_MusicPlayer_FreeRTOS2.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: Arm Hex Utility'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armhex" --diag_wrap=off -o "StateMachine_TestQueue_MusicPlayer_FreeRTOS2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "tm4c123gh6pm_startup_ccs.obj" "Application\Init.obj" "Application\SW_StateMachine.obj" "Application\main.obj" "Application\uartstdio.obj" "FatFs_Control\SPI_Control.obj" "FatFs_Control\ff.obj" "FatFs_Control\sdmm.obj" "Source\croutine.obj" "Source\event_groups.obj" "Source\list.obj" "Source\queue.obj" "Source\stream_buffer.obj" "Source\tasks.obj" "Source\timers.obj" "Source\portable\CCS\ARM_CM4F\port.obj" "Source\portable\CCS\ARM_CM4F\portasm.obj" "Source\portable\MemMang\heap_2.obj" 
	-$(RM) "tm4c123gh6pm_startup_ccs.d" "Application\Init.d" "Application\SW_StateMachine.d" "Application\main.d" "Application\uartstdio.d" "FatFs_Control\SPI_Control.d" "FatFs_Control\ff.d" "FatFs_Control\sdmm.d" "Source\croutine.d" "Source\event_groups.d" "Source\list.d" "Source\queue.d" "Source\stream_buffer.d" "Source\tasks.d" "Source\timers.d" "Source\portable\CCS\ARM_CM4F\port.d" "Source\portable\MemMang\heap_2.d" 
	-$(RM) "Source\portable\CCS\ARM_CM4F\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

