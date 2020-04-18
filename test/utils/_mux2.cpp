/*
 * _mux2.cpp
 *
 * Simulation and test for verilog module `_mux2`. The device is a two
 * input (default 32-bit width) multiplexer.
 */

#include "catch.hpp"
#include "macros.hpp"
#include "V_mux2.h"

#define TAGS "[mux][mux2]"


/*
 * TEST CASE: Validate _mux2 behaviour
 *
 * Confirm that modifying the select signal pushed the expected bits to
 * the output signal.
 */
TEST_CASE("Validate _mux2 behaviour", TAGS)
{
    V_mux2 *dut = new V_mux2;

    // Initialize device
    dut->sel = 0;
    dut->in0 = 0;
    dut->in1 = 1;
    dut->eval();

    for (int i = 0; i < 2; ++i)
    {
        dut->sel = i;
        dut->eval();
        REQUIRE(dut->out == i);
    }
}