# software version
SW_VER = 1.0.0

# hardware version
HW_VER = 2.0

# output name
TARGET = lora

# linker script
LD_SCRIPT = stm32l151cb.ld

# sources
SRC += main.c startup.c

# sys sources
SRC += ./sys/src/critical.c ./sys/src/sem.c
SRC += ./sys/src/ev.c

# util sources
SRC += ./util/src/stdio.c ./util/src/string.c

# device drivers
SRC += ./dev/src/watchdog.c ./dev/src/usart1.c
SRC += ./dev/src/cpuclock.c ./dev/src/debug.c
SRC += ./dev/src/spi1.c ./dev/src/sx1272.c
SRC += ./dev/src/extimux.c

# compiler flags
CC_FLAGS  = -mcpu=cortex-m3 -mthumb -g -Os -I. -fdata-sections 
CC_FLAGS += -ffunction-sections -Wl,--gc-sections 
CC_FLAGS += -Wall -Wmissing-field-initializers -Wsign-compare
CC_FLAGS += -Wmissing-parameter-type -Wold-style-declaration
CC_FLAGS += -Woverride-init -Wtype-limits -Wuninitialized
CC_FLAGS += -Wcast-align -Wno-format
CC_FLAGS += -pedantic-errors -std=c99
# version information
CC_FLAGS += -DSW_VER=\"$(SW_VER)\" -DHW_VER=\"$(HW_VER)\" 
 
# linker flags 
LD_FLAGS  = -T$(LD_SCRIPT)
LD_FLAGS += -nostartfiles -Wl,-Map=$(TARGET).map,--cref

# object copy flags 
OBC_FLAGS = -O binary

# tools
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBC = arm-none-eabi-objcopy
OBD = arm-none-eabi-objdump
NM = arm-none-eabi-nm
RM = rm
SIZE = arm-none-eabi-size
ECHO = echo
CHKSUM = chksum
BIN2C = bin2c

# sources converted to objs
OBJ = $(SRC:%.c=%.o)
# binary file name
OUTPUT = $(TARGET)_$(HW_VER)_$(SW_VER)

# generate elf and bin
all: $(TARGET).elf $(OUTPUT).bin $(TARGET).lst map size

# generate elf file from objs
$(TARGET).elf: $(OBJ)
	@ $(ECHO) ---------------------    Linking   ---------------------
	$(CC) $(CC_FLAGS) $(OBJ) --output $@ $(LD_FLAGS) 

# generate bin file and generate checksum for it 
$(OUTPUT).bin: $(TARGET).elf
	@ $(ECHO) ---------------------    Copying   ---------------------
	$(OBC) $(OBC_FLAGS) $< $@
	$(CHKSUM) $(OUTPUT).bin

# geneate listing
$(TARGET).lst: $(TARGET).elf
	@ $(ECHO) ---------------------    Listing   ---------------------
	$(OBD) -S $< > $@

# compile all sources
%.o : %.c
	@ $(ECHO) --------------------- Compiling $< ---------------------
	$(CC) -c $(CC_FLAGS) $< -o $@

# show size information
size: $(TARGET).elf
	@ $(ECHO) --------------------- Section size ---------------------
	$(SIZE) $(TARGET).elf

# generate symbol map
map: $(TARGET).elf
	@ $(ECHO) --------------------- Symbol map ---------------------
	$(NM) -n -o $(TARGET).elf > $(TARGET).map

# cleanser xD
clean:
	$(RM) -f $(OBJ) $(OUTPUT).bin $(TARGET).lst $(TARGET).elf $(TARGET).map
