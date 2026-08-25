

PROJECT := falling-sand-simulation

CXX := c++

CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2
CPPFLAGS := -Iinclude -Iexternal/raylib/src

# Directories
SCR_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

RAYLIB_DIR := external/raylib
RAYLIB_LIB := $(RAYLIB_DIR)/src/libraylib.a

# Source files
SOURCES := 


APP_NAME := falling-sand

CXX := c++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2

# Directories
SRC_DIR := src
BUILD_DIR := build
RAYLIB_DIR := external/raylib

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

# Platform-specific linker settings
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    LDLIBS := -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
else ifeq ($(UNAME_S),Linux)
    LDLIBS := -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Targets
.PHONY: all run clean

all: $(BUILD_DIR)/$(APP_NAME)

$(RAYLIB_DIR):
	git clone --depth 1 --branch 6.0 https://github.com/raysan5/raylib.git $(RAYLIB_DIR)

$(RAYLIB_DIR)/src/libraylib.a: $(RAYLIB_DIR)
	$(MAKE) -C $(RAYLIB_DIR)/src PLATFORM=PLATFORM_DESKTOP

$(BUILD_DIR)/$(APP_NAME): $(SOURCES) $(RAYLIB_DIR)/src/libraylib.a
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) \
		-I$(RAYLIB_DIR)/src \
		$(SOURCES) \
		$(RAYLIB_DIR)/src/libraylib.a \
		$(LDLIBS) \
		-o $@

run: all
	./$(BUILD_DIR)/$(APP_NAME)

clean:
	rm -rf $(BUILD_DIR)