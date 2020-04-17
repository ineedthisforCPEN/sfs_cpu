CC = g++
FLAGS =

HARDWARE_DEFS = ../components/$*
VERILATED_CPP = /usr/share/verilator/include/verilated.cpp

INCLUDES  = -I /usr/share/verilator/include
INCLUDES += -I ../../include
INCLUDES += -I $(HARDWARE_DEFS)

#COMPONENTS  = _decoder
#COMPONENTS += _dff _dff_e _dff_er _dff_r
#COMPONENTS += _mux2 _mux4 _mux8 _mux16 _mux32
COMPONENTS  = _dff _dff_e _dff_er _dff_r

.PHONY: all
.PHONY: clean

all: $(COMPONENTS)

$(COMPONENTS): %: %.cpp
	cd $(HARDWARE_DEFS) && $(MAKE) -f V$*.mk -j $$(nproc)
	$(CC) $(FLAGS) $(INCLUDES) -c $<

clean:
	rm *.o