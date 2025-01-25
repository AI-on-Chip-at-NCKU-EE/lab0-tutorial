SRC = $(wildcard ./src/*.sv)


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
VERILATOR_FLAGS += -I/home/aoc2025/m16134012/AOC2025/lab0/verilog/test2/src

# Ignore fatal warnings
VERILATOR_FLAGS += --Wno-fatal

VERILATOR_INPUT = $(SRC) ./testbench/test.cpp
SIM_EXEC = obj_dir/Vtrafficlight_ctrl

# Run Verilator in debug mode
# VERILATOR_FLAGS += --debug

LOG_FILE ?= logs/terminal_text.log

######################################################################
default: run

.PHONY: run
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

# Other targets

format:
	clang-format -i ./testbench/*.cpp
show-config:
	$(VERILATOR) -V

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_dir logs *.log *.dmp *.vpd *.vcd *.fsdb coverage.dat core
