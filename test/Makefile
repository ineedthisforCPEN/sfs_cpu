CC = g++
FLAGS =

HARDWARE_DEFS = ./components
TESTBENCH_DEFS = ./components/testbench
VERILATED_CPP = /usr/share/verilator/include/verilated.cpp

INCLUDES  = -I /usr/share/verilator/include
INCLUDES += -I ../include

COMPONENTS = utils.o regfile.o

.PHONY: all
.PHONY: clean

all: $(COMPONENTS)
	$(CC) $(FLAGS) $(INCLUDES) \
		$(VERILATED_CPP) \
		$(COMPONENTS) \
		$(HARDWARE_DEFS)/*/V*__ALL.a \
		$(TESTBENCH_DEFS)/*/V*__ALL.a \
		main.cpp \
		-o test_components
	-rm $(COMPONENTS)

regfile.o:
	$(MAKE) -C regfile
	ld -r regfile/*.o -o regfile.o

utils.o:
	$(MAKE) -C utils
	ld -r utils/*.o -o utils.o

clean:
	-rm *.o
	-rm ./*/*.o