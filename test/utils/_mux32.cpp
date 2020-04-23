/*
 * _mux32.cpp
 *
 * Simulation and test for verilog module `_mux32`. The device is a
 * thirty-two input (default 32-bit width) multiplexer.
 */

#include "catch.hpp"
#include "macros.hpp"
#include "V_mux32.h"

#define TAGS "[mux][mux32]"


/*
 * TEST CASE: Validate _mux32 behaviour
 *
 * Confirm that modifying the select signal pushed the expected bits to
 * the output signal.
 */
TEST_CASE("Validate _mux32 behaviour", TAGS)
{
    V_mux32 *dut = new V_mux32;

    // Initialize device
    dut->sel = 0;
    for (int i = 0; i < 32; ++i)
    {
        dut->in[i] = i;
    }
    dut->eval();

    for (int i = 0; i < 32; ++i)
    {
        dut->sel = i;
        dut->eval();
        REQUIRE(dut->out == dut->in[i]);
    }
}