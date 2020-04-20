CC = verilator
FLAGS = -Wall -cc
BUILD_DIR = ../../test/components
INCLUDE_DIR = ../../include

TESTBENCH_SRC = ../../test/testbench/tb_$<
TESTBENCH_OBJ = $(BUILD_DIR)/testbench/tb_$*

COMPONENTS  = _decoder
COMPONENTS += _dff _dff_e _dff_er _dff_r
COMPONENTS += _mux _mux2 _mux4 _mux8 _mux16 _mux32

.PHONY: all
.PHONY: clean

all: $(COMPONENTS)

%: %.sv $(INCLUDE_DIR)/*.vh
	# Build module
	mkdir -p $(BUILD_DIR)/$*
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) --Mdir $(BUILD_DIR)/$* $<

	# If a corresponding testbench exists, build it, too
	test -f $(TESTBENCH_SRC) && \
		mkdir -p $(TESTBENCH_OBJ) && \
		$(CC) $(FLAGS) -I$(INCLUDE_DIR) --Mdir $(TESTBENCH_OBJ) $(TESTBENCH_SRC) \
	|| test ! -f $(TESTBENCH_SRC)

clean:
	-rm -rf $(BUILD_DIR)/*