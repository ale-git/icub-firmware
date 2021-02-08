#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../asm/MeasCurr.s ../src/2FOC.c ../src/ADC.c ../src/DCLink.c ../src/DHES.c ../src/Faults.c ../src/PWM.c ../src/System.c ../src/can_icubProto.c ../src/can_icubProto_parser.c ../src/can_icubProto_trasmitter.c ../src/crc16.c ../src/ecan.c ../src/i2cTsens.c ../src/qep.c ../src/traps.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360919980/MeasCurr.o ${OBJECTDIR}/_ext/1360937237/2FOC.o ${OBJECTDIR}/_ext/1360937237/ADC.o ${OBJECTDIR}/_ext/1360937237/DCLink.o ${OBJECTDIR}/_ext/1360937237/DHES.o ${OBJECTDIR}/_ext/1360937237/Faults.o ${OBJECTDIR}/_ext/1360937237/PWM.o ${OBJECTDIR}/_ext/1360937237/System.o ${OBJECTDIR}/_ext/1360937237/can_icubProto.o ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o ${OBJECTDIR}/_ext/1360937237/crc16.o ${OBJECTDIR}/_ext/1360937237/ecan.o ${OBJECTDIR}/_ext/1360937237/i2cTsens.o ${OBJECTDIR}/_ext/1360937237/qep.o ${OBJECTDIR}/_ext/1360937237/traps.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360919980/MeasCurr.o.d ${OBJECTDIR}/_ext/1360937237/2FOC.o.d ${OBJECTDIR}/_ext/1360937237/ADC.o.d ${OBJECTDIR}/_ext/1360937237/DCLink.o.d ${OBJECTDIR}/_ext/1360937237/DHES.o.d ${OBJECTDIR}/_ext/1360937237/Faults.o.d ${OBJECTDIR}/_ext/1360937237/PWM.o.d ${OBJECTDIR}/_ext/1360937237/System.o.d ${OBJECTDIR}/_ext/1360937237/can_icubProto.o.d ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o.d ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o.d ${OBJECTDIR}/_ext/1360937237/crc16.o.d ${OBJECTDIR}/_ext/1360937237/ecan.o.d ${OBJECTDIR}/_ext/1360937237/i2cTsens.o.d ${OBJECTDIR}/_ext/1360937237/qep.o.d ${OBJECTDIR}/_ext/1360937237/traps.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360919980/MeasCurr.o ${OBJECTDIR}/_ext/1360937237/2FOC.o ${OBJECTDIR}/_ext/1360937237/ADC.o ${OBJECTDIR}/_ext/1360937237/DCLink.o ${OBJECTDIR}/_ext/1360937237/DHES.o ${OBJECTDIR}/_ext/1360937237/Faults.o ${OBJECTDIR}/_ext/1360937237/PWM.o ${OBJECTDIR}/_ext/1360937237/System.o ${OBJECTDIR}/_ext/1360937237/can_icubProto.o ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o ${OBJECTDIR}/_ext/1360937237/crc16.o ${OBJECTDIR}/_ext/1360937237/ecan.o ${OBJECTDIR}/_ext/1360937237/i2cTsens.o ${OBJECTDIR}/_ext/1360937237/qep.o ${OBJECTDIR}/_ext/1360937237/traps.o

# Source Files
SOURCEFILES=../asm/MeasCurr.s ../src/2FOC.c ../src/ADC.c ../src/DCLink.c ../src/DHES.c ../src/Faults.c ../src/PWM.c ../src/System.c ../src/can_icubProto.c ../src/can_icubProto_parser.c ../src/can_icubProto_trasmitter.c ../src/crc16.c ../src/ecan.c ../src/i2cTsens.c ../src/qep.c ../src/traps.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script="..\eElinkerscript_appl_2FOC.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/2FOC.o: ../src/2FOC.c  .generated_files/cfca1728a6e05feb6b688425b91582f307fe9e3d.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/2FOC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/2FOC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/2FOC.c  -o ${OBJECTDIR}/_ext/1360937237/2FOC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/2FOC.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/ADC.o: ../src/ADC.c  .generated_files/f6a563dc1f74573acb7d38e3e85743932e336df.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ADC.c  -o ${OBJECTDIR}/_ext/1360937237/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ADC.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/DCLink.o: ../src/DCLink.c  .generated_files/cd8cb896bb4baf15026b4853eabddf6cce30e8cd.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DCLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DCLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/DCLink.c  -o ${OBJECTDIR}/_ext/1360937237/DCLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/DCLink.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/DHES.o: ../src/DHES.c  .generated_files/65bf8fa83533c5ca0e502571bd7bc0077c0f2e37.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DHES.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DHES.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/DHES.c  -o ${OBJECTDIR}/_ext/1360937237/DHES.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/DHES.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/Faults.o: ../src/Faults.c  .generated_files/8fe4d414603820097dc24a58edcad12179f29353.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Faults.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Faults.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/Faults.c  -o ${OBJECTDIR}/_ext/1360937237/Faults.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Faults.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/PWM.o: ../src/PWM.c  .generated_files/b8e968d04fc8d9a85a9ec29fa48b3e02b5eb6ae8.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/PWM.c  -o ${OBJECTDIR}/_ext/1360937237/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/PWM.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/System.o: ../src/System.c  .generated_files/119932a027227f8a120167f111f42f81996ebec4.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/System.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/System.c  -o ${OBJECTDIR}/_ext/1360937237/System.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/System.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/can_icubProto.o: ../src/can_icubProto.c  .generated_files/cd9daf82576452a05e4d66c3a75cad45ed529d81.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/can_icubProto.c  -o ${OBJECTDIR}/_ext/1360937237/can_icubProto.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_icubProto.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o: ../src/can_icubProto_parser.c  .generated_files/1a41b364c20544f1d11e9b03b08ec7197d60dec3.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/can_icubProto_parser.c  -o ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o: ../src/can_icubProto_trasmitter.c  .generated_files/e5292001fd6feeb9bded0c6bb2ed60bf2d488bbe.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/can_icubProto_trasmitter.c  -o ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/crc16.o: ../src/crc16.c  .generated_files/5b5baf9013977fc40cae8fa6ed92517cc1dc874.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/crc16.c  -o ${OBJECTDIR}/_ext/1360937237/crc16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/crc16.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/ecan.o: ../src/ecan.c  .generated_files/2077ac23bfe0a36ddab49bb81c1873405967d94a.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ecan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ecan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ecan.c  -o ${OBJECTDIR}/_ext/1360937237/ecan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ecan.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/i2cTsens.o: ../src/i2cTsens.c  .generated_files/d7d965cae602c3a7775d01df0b0994f87c27d280.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2cTsens.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2cTsens.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/i2cTsens.c  -o ${OBJECTDIR}/_ext/1360937237/i2cTsens.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/i2cTsens.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/qep.o: ../src/qep.c  .generated_files/e0ab696814c5d403f3ce6a5693aa5f14c1cd9cc7.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/qep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/qep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/qep.c  -o ${OBJECTDIR}/_ext/1360937237/qep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/qep.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/traps.o: ../src/traps.c  .generated_files/b70333b71afc8872f551b525867a1f5ba343584e.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/traps.c  -o ${OBJECTDIR}/_ext/1360937237/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/traps.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1360937237/2FOC.o: ../src/2FOC.c  .generated_files/207c5b3252473b1dcac4bf35c23a95fc5da23aeb.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/2FOC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/2FOC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/2FOC.c  -o ${OBJECTDIR}/_ext/1360937237/2FOC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/2FOC.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/ADC.o: ../src/ADC.c  .generated_files/fc20d07f115473c54a61f26d25711546bf6bfbd3.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ADC.c  -o ${OBJECTDIR}/_ext/1360937237/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ADC.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/DCLink.o: ../src/DCLink.c  .generated_files/652c5911aea694a9303c51f0651a1eebf89a5736.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DCLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DCLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/DCLink.c  -o ${OBJECTDIR}/_ext/1360937237/DCLink.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/DCLink.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/DHES.o: ../src/DHES.c  .generated_files/915732333ead55a08756171ee6547e9526a27388.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DHES.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DHES.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/DHES.c  -o ${OBJECTDIR}/_ext/1360937237/DHES.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/DHES.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/Faults.o: ../src/Faults.c  .generated_files/bc0bfbeda7e2aca7ab21873969323ae7b1440ae5.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Faults.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Faults.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/Faults.c  -o ${OBJECTDIR}/_ext/1360937237/Faults.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Faults.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/PWM.o: ../src/PWM.c  .generated_files/30da9f8d6ad181fb845b1381269711617d0aad94.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/PWM.c  -o ${OBJECTDIR}/_ext/1360937237/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/PWM.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/System.o: ../src/System.c  .generated_files/12327adf3fc6d63ac67ab4dca3cbf19f994fb718.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/System.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/System.c  -o ${OBJECTDIR}/_ext/1360937237/System.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/System.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/can_icubProto.o: ../src/can_icubProto.c  .generated_files/afc672c728ec7bda4655e5531006e43cd1c19a7.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/can_icubProto.c  -o ${OBJECTDIR}/_ext/1360937237/can_icubProto.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_icubProto.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o: ../src/can_icubProto_parser.c  .generated_files/48b181a6b7d86e11b339c51cb061b18405156f13.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/can_icubProto_parser.c  -o ${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_icubProto_parser.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o: ../src/can_icubProto_trasmitter.c  .generated_files/1963bbb4505082fec0c34ad59f47fb0b703de753.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/can_icubProto_trasmitter.c  -o ${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/can_icubProto_trasmitter.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/crc16.o: ../src/crc16.c  .generated_files/1723af97e183f35acd2ecb468ee1bbbd597dfbeb.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/crc16.c  -o ${OBJECTDIR}/_ext/1360937237/crc16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/crc16.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/ecan.o: ../src/ecan.c  .generated_files/a5c39771dd1fb064b2632d40c5edd0b54b8aa4a5.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ecan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ecan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ecan.c  -o ${OBJECTDIR}/_ext/1360937237/ecan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ecan.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/i2cTsens.o: ../src/i2cTsens.c  .generated_files/8355d9da11d9b4661fb77e59632932418aec8c1c.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2cTsens.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2cTsens.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/i2cTsens.c  -o ${OBJECTDIR}/_ext/1360937237/i2cTsens.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/i2cTsens.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/qep.o: ../src/qep.c  .generated_files/8e75fd119309ba93789a38ce2359c850224044ff.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/qep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/qep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/qep.c  -o ${OBJECTDIR}/_ext/1360937237/qep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/qep.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1360937237/traps.o: ../src/traps.c  .generated_files/a32e93dfeead91b201ca463dfc5758eb68e1cb66.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/traps.c  -o ${OBJECTDIR}/_ext/1360937237/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/traps.o.d"        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O1 -I"../include" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360919980/MeasCurr.o: ../asm/MeasCurr.s  .generated_files/f57d31cdfbfba43b46885765deeab27903e05da1.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360919980" 
	@${RM} ${OBJECTDIR}/_ext/1360919980/MeasCurr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360919980/MeasCurr.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../asm/MeasCurr.s  -o ${OBJECTDIR}/_ext/1360919980/MeasCurr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../asm" -Wa,-MD,"${OBJECTDIR}/_ext/1360919980/MeasCurr.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1360919980/MeasCurr.o: ../asm/MeasCurr.s  .generated_files/8a7ab7aeaf36449a2f36ce4f85091299a62245c5.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360919980" 
	@${RM} ${OBJECTDIR}/_ext/1360919980/MeasCurr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360919980/MeasCurr.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../asm/MeasCurr.s  -o ${OBJECTDIR}/_ext/1360919980/MeasCurr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../asm" -Wa,-MD,"${OBJECTDIR}/_ext/1360919980/MeasCurr.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../eElinkerscript_appl_2FOC.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../eElinkerscript_appl_2FOC.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/2FOC-V3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
