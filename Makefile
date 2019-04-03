# Configuration options ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

debug ?= 0

# Project and tool names ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

BSTD_JSON ?= bstd_json
EXAMPLES  ?= examples
TESTS     ?= tests

# Directory Layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

$(shell mkdir -p bin)
BIN_DIR ?= ./bin
SRC  ?= ./src
EXAMPLES_SRC  ?= ./examples
TESTS_SRC  ?= ./test

$(shell mkdir -p build/dependencies)
BUILD_DIR      ?= ./build
DEPENDENCY_DIR := $(BUILD_DIR)/dependencies
DEPENDENCIES   := $(DEPENDENCY_DIR)/dependencies
D_FILES        := $(DEPENDENCY_DIR)/$*.d

ERROR_INC ?= -I$(HOME)/Projects/bstd_error/include
TEST_INC  ?= -I$(HOME)/Projects/bstd_test/include
INC  := -Iinclude $(ERROR_INC) $(TEST_INC) -I$(SRC) \

# Compiler Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

CXX 	  = g++
CXXFLAGS  = -std=c++2a -Wall -Werror -pedantic -fPIC
LDFLAGS   = -shared
LINK      = -Lbin -L$(HOME)/Projects/bstd_test/bin
LINK_JSON = $(LINK) -lbstdjson
LINK_TEST = $(LINK) -lbstdtest
LINK_ALL = $(LINK_JSON) $(LINK_TEST)


ifeq ($(debug), 1)
	CXXFLAGS += -g
endif

DEPS = -MMD -MF $(D_FILES)

# File Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

SRCS := $(shell find $(SRC) -path "*.cpp")
OBJS := $(SRCS:.cpp=.o)
LIB  := $(BIN_DIR)/libbstdjson.so

EXAMPLE_SRCS := $(shell find $(EXAMPLES_SRC) -path "*.cpp")
EXAMPLES     := $(basename $(EXAMPLE_SRCS))
TEST_SRCS    := $(shell find $(TESTS_SRC) -path "*.cpp")
TESTS        := $(basename $(TEST_SRCS))

# Object File Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.cpp.o: $(SRCS)
	@echo Compiling $<...
	@$(CXX) -c $(CXXFLAGS) $(DEPS) $(INC) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Executable Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

all:	$(BSTD_JSON) $(EXAMPLES) $(TESTS)

# Build bstd::json library.
.PHONY: $(BSTD_JSON)
$(BSTD_JSON):	$(LIB)
$(LIB):		$(OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) -o $@ $^
		@rm -f $(OBJS)

# Build all examples.
.PHONY: $(EXAMPLES)
$(EXAMPLES):  %: %.cpp $(LIB)
	      @echo Compiling $<...
	      @$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_JSON) $(INC) $< -o $@
	      @cat $(D_FILES) >> $(DEPENDENCIES)

# Build all tests.
# TODO: fix not being able to run test executable from different directories.
.PHONY: $(TESTS)
$(TESTS):	%: %.cpp $(LIB)
		@echo Compiling $<...
		@$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_ALL) $(INC) $< -o $@
		@cat $(D_FILES) >> $(DEPENDENCIES)

# Cleanup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -f $(shell find $(DEPENDENCY_DIR) -path "*.d")
	@rm -f $(shell find . -path "*.o")
	@rm -f $(EXAMPLES)
	@rm -f $(TESTS)
	@rm -f $(DEPENDENCIES)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)

# Other stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# include automatically generated dependencies
-include $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
