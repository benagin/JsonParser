# Configuration options ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

debug ?= 0

# Project and tool names ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

BSTD_JSON ?= bstd_json
EXAMPLES  ?= examples
TESTS     ?= tests
INSTALL   ?= install

# Directory Layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# TODO: make this configurable and/or work on other machines.
INSTALL_DIR ?= /usr/local/lib

$(shell mkdir -p bin)
BIN_DIR       ?= ./bin
SRC           ?= ./src
EXAMPLES_SRC  ?= ./examples
TESTS_SRC     ?= ./test

$(shell mkdir -p build/dependencies)
BUILD_DIR      ?= ./build
DEPENDENCY_DIR := $(BUILD_DIR)/dependencies
DEPENDENCIES   := $(DEPENDENCY_DIR)/dependencies
D_FILES        := $(DEPENDENCY_DIR)/$*.d

# TODO: change this to work on other machines.
ERROR_INC ?= -I$(HOME)/Projects/bstd_error/include
TEST_INC  ?= -I$(HOME)/Projects/bstd_test/include
INC       := -Iinclude $(ERROR_INC) $(TEST_INC) -I$(SRC) \

# Compiler Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

CXX 	  = g++
CXXFLAGS  = -std=c++2a -Wall -Werror -pedantic -fPIC
LDFLAGS   = -shared
# TODO: change this to work on other machines.
LINK      = -Lbin -L$(HOME)/Projects/bstd_test/bin
LINK_JSON = $(LINK) -lbstdjson
LINK_TEST = $(LINK) -lbstdtest
LINK_ALL  = $(LINK_JSON) $(LINK_TEST)


ifeq ($(debug), 1)
	CXXFLAGS += -g
endif

DEPS = -MMD -MF $(D_FILES)

# File Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

SRCS := $(shell find $(SRC) -path "*.cpp")
OBJS := $(SRCS:.cpp=.o)
LIB  := $(BIN_DIR)/libbstdjson.so

EXAMPLE_SRCS       := $(shell find $(EXAMPLES_SRC) -path "*.cpp")
EXAMPLES_BASENAMES := $(basename $(EXAMPLE_SRCS))
TEST_SRCS          := $(shell find $(TESTS_SRC) -path "*.cpp")
TESTS_BASENAMES    := $(basename $(TEST_SRCS))

# Object File Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.cpp.o: $(SRCS)
	@echo Compiling $<...
	@$(CXX) -c $(CXXFLAGS) $(DEPS) $(INC) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

# Target Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

all:	$(BSTD_JSON) $(EXAMPLES) $(TESTS)

# Build bstd::json library.
.PHONY: $(BSTD_JSON)
$(BSTD_JSON):	$(LIB)
$(LIB):		$(OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) -o $@ $^
		@rm -f $(OBJS)

# Install the library to $(INSTALL_DIR).
.PHONY: $(INSTALL)
$(INSTALL):	$(LIB)
		@echo Installing...
		@cp $(LIB) $(INSTALL_DIR)

# Build all examples.
.PHONY: $(EXAMPLES)
$(EXAMPLES):	        $(EXAMPLES_BASENAMES)
$(EXAMPLES_BASENAMES):  %: %.cpp $(LIB)
	@echo Compiling $<...
	@$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_JSON) $(INC) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

# Build all tests.
# TODO: fix not being able to run test executable from different directories.
.PHONY: $(TESTS)
$(TESTS):	        $(TESTS_BASENAMES)
$(TESTS_BASENAMES):	%: %.cpp $(LIB)
	@echo Compiling $<...
	@$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_ALL) $(INC) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

# Cleanup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -f $(shell find $(DEPENDENCY_DIR) -path "*.d")
	@rm -f $(shell find . -path "*.o")
	@rm -f $(EXAMPLES_BASENAMES)
	@rm -f $(TESTS_BASENAMES)
	@rm -f $(DEPENDENCIES)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)

# Other stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Include automatically generated dependencies.
-include $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
