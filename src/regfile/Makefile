CC = verilator
FLAGS = -Wall -cc
BUILD_DIR = ../../test/components
INCLUDE_DIR = ../../include
UTILS_DIR = ../utils

TESTBENCH_SRC = ../../test/testbench/tb_$<
TESTBENCH_OBJ = $(BUILD_DIR)/testbench/tb_$*

COMPONENTS  = regfile

.PHONY: all
.PHONY: clean

all: $(COMPONENTS)

%: %.sv $(INCLUDE_DIR)/*.vh
	# Build module
	mkdir -p $(BUILD_DIR)/$*
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(UTILS_DIR) --Mdir $(BUILD_DIR)/$* $<

	# If a corresponding testbench exists, build it, too
	test -f $(TESTBENCH_SRC) && \
		mkdir -p $(TESTBENCH_OBJ) && \
		$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(UTILS_DIR) --Mdir $(TESTBENCH_OBJ) $(TESTBENCH_SRC) \
	|| test ! -f $(TESTBENCH_SRC)

clean:
	-rm -rf $(BUILD_DIR)/*