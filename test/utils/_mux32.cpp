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
    dut->in16 = 16;
    dut->in17 = 17;
    dut->in18 = 18;
    dut->in19 = 19;
    dut->in20 = 20;
    dut->in21 = 21;
    dut->in22 = 22;
    dut->in23 = 23;
    dut->in24 = 24;
    dut->in25 = 25;
    dut->in26 = 26;
    dut->in27 = 27;
    dut->in28 = 28;
    dut->in29 = 29;
    dut->in30 = 30;
    dut->in31 = 31;
    dut->eval();

    for (int i = 0; i < 32; ++i)
    {
        dut->sel = i;
        dut->eval();
        REQUIRE(dut->out == i);
    }
}