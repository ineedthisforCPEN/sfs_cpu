CC = verilator
FLAGS = -Wall -cc
BUILD_DIR = ../../test/components
INCLUDE_DIR = ../../include

COMPONENTS  = _decoder
COMPONENTS += _dff _dff_e _dff_er _dff_r
COMPONENTS += _mux2 _mux4 _mux8 _mux16 _mux32

.PHONY: all
.PHONY: clean

all: $(COMPONENTS)

%: %.sv $(INCLUDE_DIR)/*.vh
	mkdir -p $(BUILD_DIR)/$*
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) --Mdir $(BUILD_DIR)/$* $<

clean:
	-rm -rf $(BUILD_DIR)/*