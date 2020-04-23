CC = g++
FLAGS =

HARDWARE_DEFS = ../components/$*
TESTBENCH_DEFS = ../components/testbench/tb_$*
VERILATED_CPP = /usr/share/verilator/include/verilated.cpp

INCLUDES  = -I /usr/share/verilator/include
INCLUDES += -I ../../include
INCLUDES += -I $(HARDWARE_DEFS)
INCLUDES += -I $(TESTBENCH_DEFS)

COMPONENTS  = regfile

.PHONY: all
.PHONY: clean

all: $(COMPONENTS)

$(COMPONENTS): %: %.cpp
	$(MAKE) -C $(HARDWARE_DEFS) -f V$*.mk
	-$(MAKE) -C $(TESTBENCH_DEFS) -f Vtb_$*.mk
	$(CC) $(FLAGS) $(INCLUDES) -c $<

clean:
	rm *.o