/*
 * _mux8.cpp
 *
 * Simulation and test for verilog module `_mux8`. The device is an
 * eight input (default 32-bit width) multiplexer.
 */

#include "catch.hpp"
#include "macros.hpp"
#include "V_mux8.h"

#define TAGS "[mux][mux8]"


/*
 * TEST CASE: Validate _mux8 behaviour
 *
 * Confirm that modifying the select signal pushed the expected bits to
 * the output signal.
 */
TEST_CASE("Validate _mux8 behaviour", TAGS)
{
    V_mux8 *dut = new V_mux8;

    // Initialize device
    dut->sel = 0;
    dut->in0 = 0;
    dut->in1 = 1;
    dut->in2 = 2;
    dut->in3 = 3;
    dut->in4 = 4;
    dut->in5 = 5;
    dut->in6 = 6;
    dut->in7 = 7;
    dut->eval();

    for (int i = 0; i < 8; ++i)
    {
        dut->sel = i;
        dut->eval();
        REQUIRE(dut->out == i);
    }
}