# SRC = $(wildcard ./src/*.sv)
SRC = ./src/full_adder.sv \
    ./src/adder.sv


ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
VERILATOR_COVERAGE = $(VERILATOR_ROOT)/bin/verilator_coverage
endif

VERILATOR_FLAGS += --cc --exe
CXXFLAGS += -g

# Optimize
# VERILATOR_FLAGS += -x-assign fast

# Warn abount lint issues; may not want this on less solid designs
# VERILATOR_FLAGS += -Wall
# VERILATOR_FLAGS += -Wall -Wno-lint

# Automatically build the Verilated model
VERILATOR_FLAGS += --build

# Make waveforms
VERILATOR_FLAGS += --trace
VERILATOR_FLAGS += --trace-max-array 1024

# Include the source directory 
VERILATOR_FLAGS += -I/home/aoc2025/m16134012/AOC2025/lab0/verilog/test1/src

# Ignore fatal warnings
VERILATOR_FLAGS += --Wno-fatal

# Run Verilator in debug mode
# VERILATOR_FLAGS += --debug

LOG_FILE ?= logs/terminal_text.log

######################################################################
default: all

.PHONY: all
all: tb0 tb1

run:
	@echo
	@echo "-- Verilator Start"

	@echo
	@echo "-- VERILATE ----------------"
	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT)

	@echo
	@echo "-- RUN ---------------------"
	@rm -rf logs
	@mkdir -p logs
	$(SIM_EXEC) +trace

	@echo
	@echo "-- DONE --------------------"
	@echo "To see waveforms, open adder_wave.vcd in a waveform viewer"
	@echo

######################################################################

# Specific Testbench Targets
# Pass TB_select as a parameter to the simulation executable
.PHONY: tb0 tb1

tb0: VERILATOR_FLAGS += --top-module full_adder
tb0: VERILATOR_INPUT = $(SRC) ./testbench/tb0.cpp
tb0: SIM_EXEC = obj_dir/Vfull_adder
tb0: LOG_FILE = logs/terminal_text_tb0.log
tb0: run
	@chmod 666 ./testbench/tb0.cpp

tb1: VERILATOR_FLAGS += --top-module adder
tb1: VERILATOR_INPUT = $(SRC) ./testbench/tb1.cpp
tb1: SIM_EXEC = obj_dir/Vadder
tb1: LOG_FILE = logs/terminal_text_tb1.log
tb1: run
	@chmod 666 ./testbench/tb_tb1.cpp

######################################################################
# Other targets

format:
	@clang-format -i ./testbench/*.cpp
show-config:
	$(VERILATOR) -V

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_dir logs *.log *.dmp *.vpd *.vcd *.fsdb coverage.dat core