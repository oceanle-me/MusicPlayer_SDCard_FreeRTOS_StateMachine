################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/portable/CCS/ARM_CM4F/%.obj: ../Source/portable/CCS/ARM_CM4F/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/FatFs_Control" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Application" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/include" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/portable" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/FreeRTOSv202104.00/FreeRTOS/Source" --include_path="C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Source/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="Source/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/portable/CCS/ARM_CM4F/%.obj: ../Source/portable/CCS/ARM_CM4F/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/FatFs_Control" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Application" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/include" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/Dell/workspace_v10/StateMachine_TestQueue_MusicPlayer_FreeRTOS2/Source/portable" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/FreeRTOSv202104.00/FreeRTOS/Source" --include_path="C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Source/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="Source/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


