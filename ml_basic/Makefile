SRC_DIR := src
HPP_DIR := hpp
LIB_DIR := lib
OUT_DIR := out
BIN_DIR := Build
INCLUDE_DIR := include

WARN_FLAGS := -Wall -Wno-unused-function -Wno-reorder

CXX_FLAGS := -I$(HPP_DIR) -I$(INCLUDE_DIR) -std=c++20 -fPIC -L$(LIB_DIR) -O3 $(WARN_FLAGS)
OUT_FLAGS := -shared

SRC_FILES := $(shell find $(SRC_DIR)/ -name "*.cpp")
OUT_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(SRC_FILES))

MODULE_NAME := ml_basic
MODULE_FILE := $(BIN_DIR)/$(MODULE_NAME).so

$(MODULE_FILE): $(OUT_FILES)
	@if [ ! -d "$(BIN_DIR)" ]; then mkdir "$(BIN_DIR)"; fi
	$(CXX) $(OUT_FLAGS) $^ -o $@

all: $(MODULE_FILE)

$(OUT_FILES): $(SRC_FILES)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d "$(OUT_DIR)" ]; then mkdir "$(OUT_DIR)"; fi
	@if [ ! -d "$(dir $@)" ]; then mkdir "$(dir $@)"; fi
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -fr $(OUT_DIR)/*
	rm -fr $(BIN_DIR)/*
	rm -f $(MODULE_FILE)

.PHONY: clean all