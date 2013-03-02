################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Libs


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Libs/DistanceDriver.cpp \
../Libs/SoftwareSerial.cpp \
../Libs/URMSerial.cpp \
../Libs/WiFlyRNXV.cpp \
../RoomTraq.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Libs/DistanceDriver.o \
Libs/SoftwareSerial.o \
Libs/URMSerial.o \
Libs/WiFlyRNXV.o \
RoomTraq.o


OBJS_AS_ARGS +=  \
Libs/DistanceDriver.o \
Libs/SoftwareSerial.o \
Libs/URMSerial.o \
Libs/WiFlyRNXV.o \
RoomTraq.o


C_DEPS +=  \
Libs/DistanceDriver.d \
Libs/SoftwareSerial.d \
Libs/URMSerial.d \
Libs/WiFlyRNXV.d \
RoomTraq.d


C_DEPS_AS_ARGS +=  \
Libs/DistanceDriver.d \
Libs/SoftwareSerial.d \
Libs/URMSerial.d \
Libs/WiFlyRNXV.d \
RoomTraq.d


OUTPUT_FILE_PATH +=RoomTraq.elf

OUTPUT_FILE_PATH_AS_ARGS +=RoomTraq.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler











Libs/%.o: ../Libs/%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C++ Compiler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -I"../../ArduinoCore" -I"../../ArduinoCore/Libraries"  -Os -ffunction-sections -fpack-struct -fshort-enums -g2 -Wall -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega328p   -o"$@" "$<" 
	@echo Finished building: $<

./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C++ Compiler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -I"../../ArduinoCore" -I"../../ArduinoCore/Libraries"  -Os -ffunction-sections -fpack-struct -fshort-enums -g2 -Wall -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega328p   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="RoomTraq.map" -Wl,--start-group -Wl,-lm -Wl,-lcore  -Wl,--end-group -Wl,-L"../../ArduinoCore"  -Wl,--gc-sections  -mmcu=atmega328p  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "RoomTraq.elf" "RoomTraq.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "RoomTraq.elf" "RoomTraq.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objdump.exe" -h -S "RoomTraq.elf" > "RoomTraq.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-size.exe" "RoomTraq.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "RoomTraq.elf" "RoomTraq.a" "RoomTraq.hex" "RoomTraq.lss" "RoomTraq.eep" "RoomTraq.map"
	