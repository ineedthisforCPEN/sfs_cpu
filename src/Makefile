CC = verilator
FLAGS = -Wall -cc
BUILD_DIR = ../test/components
INCLUDE_DIR = ../include

COMPONENTS  = regfile utils

.PHONY: all
.PHONY: $(COMPONENTS)
.PHONY: clean

all: $(COMPONENTS)

regfile:
	$(MAKE) -C regfile

utils:
	$(MAKE) -C utils

clean:
	-rm -rf $(BUILD_DIR)/*