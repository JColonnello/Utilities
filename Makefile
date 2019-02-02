LIB_NAME ?= Utilities
TARGET_LIB := lib$(LIB_NAME).so
TARGET_EXEC := Test.bin
TARGET_CS := Control.exe

BUILD_DIR ?= obj
SRC_DIRS ?= ./
ASSEMBLY_DIR ?= asm
SRC_LIB_DIRS ?= $(SRC_DIRS)/src/
SRC_TEST_DIRS ?= $(SRC_DIRS)/test/

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s -or -name *.cs)
SRCS_CS := $(shell find $(SRC_DIRS) -name *.cs)
SRCS_LIB := $(shell find $(SRC_LIB_DIRS) -name *.cpp -or -name *.c -or -name *.s)
SRCS_TEST := $(shell find $(SRC_TEST_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS_LIB := $(SRCS_LIB:$(SRC_DIRS)/%=$(BUILD_DIR)/%.o)
OBJS_TEST := $(SRCS_TEST:$(SRC_DIRS)/%=$(BUILD_DIR)/%.o)
ASM_OBJS := $(SRCS_LIB:$(SRC_DIRS)/%=$(ASSEMBLY_DIR)/%.s)

INC_DIRS := $(SRC_LIB_DIRS)
#INC_DIRS ?= $(SRC_DIRS)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LDFLAGS_LIB ?= -lm
LDFLAGS_TEST ?= -rpath=$(BUILD_DIR),-l$(LIB_NAME),-lm
CFLAGS ?= -O3 -Wall -std=c99 $(INC_FLAGS)
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

all: native test #csharp

rebuild: clean all

native: $(BUILD_DIR)/$(TARGET_LIB)

test: $(BUILD_DIR)/$(TARGET_EXEC)

csharp: $(BUILD_DIR)/$(TARGET_CS)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(ASSEMBLY_DIR)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS_TEST) $(BUILD_DIR)/$(TARGET_LIB)
	$(MKDIR_P) $(dir $@)
	$(CC) $(OBJS_TEST) -o $@ -L$(BUILD_DIR) -Wl,$(LDFLAGS_TEST)

$(BUILD_DIR)/$(TARGET_LIB): $(OBJS_LIB) #$(ASM_OBJS)
	$(MKDIR_P) $(dir $@)
	$(CC) $(OBJS_LIB) -o $@ --shared -Wl,$(LDFLAGS_LIB) 

$(BUILD_DIR)/$(TARGET_CS): $(SRCS_CS)
	$(MKDIR_P) $(dir $@)
	mcs -out:$@ $(SRCS_CS)

# assembly
$(BUILD_DIR)/%.s.o: $(SRC_DIRS)/%.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: $(SRC_DIRS)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# assembly code
$(ASSEMBLY_DIR)/%.c.s: $(SRC_DIRS)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -S $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: $(SRC_DIRS)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all rebuild native clean test csharp

MKDIR_P ?= mkdir -p

