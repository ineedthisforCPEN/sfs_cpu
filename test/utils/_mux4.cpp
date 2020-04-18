/*
 * _mux4.cpp
 *
 * Simulation and test for verilog module `_mux4`. The device is a four
 * input (default 32-bit width) multiplexer.
 */

#include "catch.hpp"
#include "macros.hpp"
#include "V_mux4.h"

#define TAGS "[mux][mux4]"


/*
 * TEST CASE: Validate _mux4 behaviour
 *
 * Confirm that modifying the select signal pushed the expected bits to
 * the output signal.
 */
TEST_CASE("Validate _mux4 behaviour", TAGS)
{
    V_mux4 *dut = new V_mux4;

    // Initialize device
    dut->sel = 0;
    dut->in0 = 0;
    dut->in1 = 1;
    dut->in2 = 2;
    dut->in3 = 3;
    dut->eval();

    for (int i = 0; i < 4; ++i)
    {
        dut->sel = i;
        dut->eval();
        REQUIRE(dut->out == i);
    }
}