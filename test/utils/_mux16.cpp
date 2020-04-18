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
    dut->in00 = 0;
    dut->in01 = 1;
    dut->in02 = 2;
    dut->in03 = 3;
    dut->in04 = 4;
    dut->in05 = 5;
    dut->in06 = 6;
    dut->in07 = 7;
    dut->in08 = 8;
    dut->in09 = 9;
    dut->in10 = 10;
    dut->in11 = 11;
    dut->in12 = 12;
    dut->in13 = 13;
    dut->in14 = 14;
    dut->in15 = 15;
    dut->eval();

    for (int i = 0; i < 16; ++i)
    {
        dut->sel = i;
        dut->eval();
        REQUIRE(dut->out == i);
    }
}