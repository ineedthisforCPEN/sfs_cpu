/*
 * _dff.cpp
 *
 * Simulation and test for verilog module `_dff`. The device is a
 * standard D-flip-flop that latches the input on every positive clock
 * cycle.
 */

#include <stdint.h>

#include "catch.hpp"
#include "macros.hpp"
#include "V_dff.h"

#define TAGS "[dff]"


/*
 * TEST CASE: Validate _dff behaviour
 *
 * Confirm that the value in D is latched only on a positive clock edge
 * and not on a negative edge or when the signal is held high or low.
 */
TEST_CASE("Validate _dff behaviour", TAGS)
{
    V_dff *dut = new V_dff;
    uint32_t D1 = 0x00000000;
    uint32_t D2 = 0xFFFFFFFF;

    // Initialize device
    dut->clk = 0;
    dut->D = D1;
    dut->eval();
    PULSE(dut, clk);

    // Confirm that the device has been initialized properly
    REQUIRE(dut->Q == D1);

    // Confirm latch on positive clock edge
    dut->D = D2;
    TICK(dut);  // Posedge
    REQUIRE(dut->Q == D2);

    // Confirm value is held when clock is held high
    dut->D = D1;
    REPEAT(10)
    {
        dut->eval();
    }
    REQUIRE(dut->Q == D2);

    // Confirm value is held on negative clock edge
    TICK(dut);  // Negedge
    REQUIRE(dut->Q == D2);

    // Confirm value is held when clock is held low
    REPEAT(10)
    {
        dut->eval();
    }
    REQUIRE(dut->Q == D2);

    // Confirm that the next value is latched on a positive clock edge
    TICK(dut);  // Posedge
    REQUIRE(dut->Q == D1);
}