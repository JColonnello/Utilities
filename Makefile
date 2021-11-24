LIB_NAME ?= utilities
TARGET_LIB := lib$(LIB_NAME)
TARGET_EXEC := Test.bin

BUILD_DIR ?= obj
SRC_DIRS ?= ./
ASSEMBLY_DIR ?= asm
SRC_LIB_DIRS ?= $(SRC_DIRS)/src/
SRC_TEST_DIRS ?= $(SRC_DIRS)/test/

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s -or -name *.cs)
SRCS_LIB := $(shell find $(SRC_LIB_DIRS) -name *.cpp -or -name *.c -or -name *.s)
SRCS_TEST := $(shell find $(SRC_TEST_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS_LIB := $(SRCS_LIB:$(SRC_DIRS)/%=$(BUILD_DIR)/%.o)
OBJS_TEST := $(SRCS_TEST:$(SRC_DIRS)/%=$(BUILD_DIR)/%.o)

INC_DIRS := $(SRC_LIB_DIRS)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LDFLAGS_LIB ?= -lm
LDFLAGS_TEST ?= -rpath=$(BUILD_DIR),-lm
CFLAGS ?= -g -Wall -Wextra -std=c11
DEP_FLAGS := -MMD -MP

all: native test

rebuild: clean all

native: $(BUILD_DIR)/$(TARGET_LIB).a #$(BUILD_DIR)/$(TARGET_LIB).so

test: $(BUILD_DIR)/$(TARGET_EXEC)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(ASSEMBLY_DIR)

#Test
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS_TEST) $(BUILD_DIR)/$(TARGET_LIB).a
	$(MKDIR_P) $(dir $@)
	$(CC) $(OBJS_TEST) $(BUILD_DIR)/$(TARGET_LIB).a -o $@ -L$(BUILD_DIR) -Wl,$(LDFLAGS_TEST)

#Shared library
$(BUILD_DIR)/$(TARGET_LIB).so: $(OBJS_LIB)
	$(MKDIR_P) $(dir $@)
	$(CC) $(OBJS_LIB) -o $@ --shared -Wl,$(LDFLAGS_LIB)

#Static library
$(BUILD_DIR)/$(TARGET_LIB).a: $(OBJS_LIB)
	$(MKDIR_P) $(dir $@)
	$(AR) rcs $@ $(OBJS_LIB)

# c source
$(BUILD_DIR)/%.c.o: $(SRC_DIRS)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(DEP_FLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: all rebuild native clean test

MKDIR_P ?= mkdir -p

-include $(OBJS_LIB:%.o=%.d) $(OBJS_TEST:%.o=%.d)