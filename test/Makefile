CC = g++
FLAGS =

HARDWARE_DEFS = ./components
VERILATED_CPP = /usr/share/verilator/include/verilated.cpp

INCLUDES  = -I /usr/share/verilator/include
INCLUDES += -I ../include

COMPONENTS = utils.o

.PHONY: all
.PHONY: hardware
.PHONY: clean

all: $(COMPONENTS)
	$(MAKE) $(HARDWARE_DEFS)/*
	$(CC) $(FLAGS) $(INCLUDES) \
		$(VERILATED_CPP) \
		$(COMPONENTS) \
		$(HARDWARE_DEFS)/*/V*__ALL.a \
		main.cpp \
		-o test_components
	-rm $(COMPONENTS)

utils.o:
	cd utils && $(MAKE) -j $$(nproc)
	ld -r utils/*.o -o utils.o

hardware: %: $(HARDWARE_DEFS)/%/V%.cpp
	$(MAKE) -C $(HARDWARE_DEFS)/$* -f $(HARDWARE_DEFS)/$*/V$*.mk

clean:
	-rm *.o
	-rm ./*/*.o