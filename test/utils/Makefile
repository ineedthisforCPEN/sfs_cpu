CC = g++
FLAGS =

HARDWARE_DEFS = ../components/$*
TESTBENCH_DEFS = ../components/testbench/tb_$*
VERILATED_CPP = /usr/share/verilator/include/verilated.cpp

INCLUDES  = -I /usr/share/verilator/include
INCLUDES += -I ../../include
INCLUDES += -I $(HARDWARE_DEFS)
INCLUDES += -I $(TESTBENCH_DEFS)

COMPONENTS  = _decoder
COMPONENTS += _dff _dff_e _dff_er _dff_r
COMPONENTS += _mux _mux2 _mux4 _mux8 _mux16 _mux32

.PHONY: all
.PHONY: clean

all: $(COMPONENTS)

$(COMPONENTS): %: %.cpp
	$(MAKE) -C $(HARDWARE_DEFS) -f V$*.mk
	-$(MAKE) -C $(TESTBENCH_DEFS) -f Vtb_$*.mk
	$(CC) $(FLAGS) $(INCLUDES) -c $<

clean:
	rm *.o