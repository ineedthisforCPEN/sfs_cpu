/*
 * _mux16.cpp
 *
 * Simulation and test for verilog module `_mux16`. The device is a
 * sixteen input (default 32-bit width) multiplexer.
 */

#include "catch.hpp"
#include "macros.hpp"
#include "V_mux16.h"

#define TAGS "[mux][mux16]"


/*
 * TEST CASE: Validate _mux16 behaviour
 *
 * Confirm that modifying the select signal pushed the expected bits to
 * the output signal.
 */
TEST_CASE("Validate _mux16 behaviour", TAGS)
{
    V_mux16 *dut = new V_mux16;

    // Initialize device
    dut->sel = 0;
    for (int i = 0; i < 16; ++i)
    {
        dut->in[i] = i;
    }
    dut->eval();

    for (int i = 0; i < 16; ++i)
    {
        dut->sel = i;
        dut->eval();
        REQUIRE(dut->out == dut->in[i]);
    }
}