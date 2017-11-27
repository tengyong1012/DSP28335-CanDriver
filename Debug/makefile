################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/c2000_6.2.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./CAN_TEST.obj" \
"./DSP2833x_ADC_cal.obj" \
"./DSP2833x_CSMPasswords.obj" \
"./DSP2833x_CodeStartBranch.obj" \
"./DSP2833x_CpuTimers.obj" \
"./DSP2833x_DefaultIsr.obj" \
"./DSP2833x_EPwm.obj" \
"./DSP2833x_GlobalVariableDefs.obj" \
"./DSP2833x_MemCopy.obj" \
"./DSP2833x_PieCtrl.obj" \
"./DSP2833x_PieVect.obj" \
"./DSP2833x_SysCtrl.obj" \
"./DSP2833x_usDelay.obj" \
"./DSP28_ECan.obj" \
"./main.obj" \
"./canfestival/src/28335timerdriver.obj" \
"./canfestival/src/ObjDict.obj" \
"./canfestival/src/dcf.obj" \
"./canfestival/src/emcy.obj" \
"./canfestival/src/lifegrd.obj" \
"./canfestival/src/lss.obj" \
"./canfestival/src/nmtMaster.obj" \
"./canfestival/src/nmtSlave.obj" \
"./canfestival/src/objacces.obj" \
"./canfestival/src/pdo.obj" \
"./canfestival/src/sdo.obj" \
"./canfestival/src/states.obj" \
"./canfestival/src/sync.obj" \
"./canfestival/src/timer.obj" \
"../DSP2833x_Headers_nonBIOS.cmd" \
"../F28335.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include canfestival/src/subdir_vars.mk
-include subdir_rules.mk
-include canfestival/src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
28335_Can_TxRx.out \

EXE_OUTPUTS__QUOTED += \
"28335_Can_TxRx.out" \

BIN_OUTPUTS += \
28335_Can_TxRx.hex \

BIN_OUTPUTS__QUOTED += \
"28335_Can_TxRx.hex" \


# All Target
all: 28335_Can_TxRx.out

# Tool invocations
28335_Can_TxRx.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"28335_Can_TxRx.map" --stack_size=0x300 --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="28335_Can_TxRx_linkInfo.xml" --rom_model -o "28335_Can_TxRx.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

28335_Can_TxRx.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/hex2000"  -o "28335_Can_TxRx.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "CAN_TEST.pp" "DSP2833x_CpuTimers.pp" "DSP2833x_DefaultIsr.pp" "DSP2833x_EPwm.pp" "DSP2833x_GlobalVariableDefs.pp" "DSP2833x_MemCopy.pp" "DSP2833x_PieCtrl.pp" "DSP2833x_PieVect.pp" "DSP2833x_SysCtrl.pp" "DSP28_ECan.pp" "main.pp" "canfestival\src\28335timerdriver.pp" "canfestival\src\ObjDict.pp" "canfestival\src\dcf.pp" "canfestival\src\emcy.pp" "canfestival\src\lifegrd.pp" "canfestival\src\lss.pp" "canfestival\src\nmtMaster.pp" "canfestival\src\nmtSlave.pp" "canfestival\src\objacces.pp" "canfestival\src\pdo.pp" "canfestival\src\sdo.pp" "canfestival\src\states.pp" "canfestival\src\sync.pp" "canfestival\src\timer.pp" 
	-$(RM) "CAN_TEST.obj" "DSP2833x_ADC_cal.obj" "DSP2833x_CSMPasswords.obj" "DSP2833x_CodeStartBranch.obj" "DSP2833x_CpuTimers.obj" "DSP2833x_DefaultIsr.obj" "DSP2833x_EPwm.obj" "DSP2833x_GlobalVariableDefs.obj" "DSP2833x_MemCopy.obj" "DSP2833x_PieCtrl.obj" "DSP2833x_PieVect.obj" "DSP2833x_SysCtrl.obj" "DSP2833x_usDelay.obj" "DSP28_ECan.obj" "main.obj" "canfestival\src\28335timerdriver.obj" "canfestival\src\ObjDict.obj" "canfestival\src\dcf.obj" "canfestival\src\emcy.obj" "canfestival\src\lifegrd.obj" "canfestival\src\lss.obj" "canfestival\src\nmtMaster.obj" "canfestival\src\nmtSlave.obj" "canfestival\src\objacces.obj" "canfestival\src\pdo.obj" "canfestival\src\sdo.obj" "canfestival\src\states.obj" "canfestival\src\sync.obj" "canfestival\src\timer.obj" 
	-$(RM) "DSP2833x_ADC_cal.pp" "DSP2833x_CSMPasswords.pp" "DSP2833x_CodeStartBranch.pp" "DSP2833x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

