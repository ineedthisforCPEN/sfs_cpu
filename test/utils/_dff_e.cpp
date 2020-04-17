/*
 * _dff_e.cpp
 *
 * Simulation and test for verilog module `_dff_e`. The device is a
 * standard D-flip-flop that latches the input on every positive clock
 * cycle when the enable signal `en` is set high.
 */

#include <stdint.h>

#include "catch.hpp"
#include "macros.hpp"
#include "V_dff_e.h"

#define TAGS "[dff][dff_e]"


/*
 * TEST CASE: Validate _dff_e behaviour
 *
 * Confirm that the device behaves like a standard D-flip-flop when the
 * enable signal is set high, and does not latch input when the enable
 * signal is set low.
 */
TEST_CASE("Validate _dff_e behaviour", TAGS)
{
    V_dff_e *dut = new V_dff_e;
    uint32_t D1 = 0x00000000;
    uint32_t D2 = 0xFFFFFFFF;

    // Initialize device
    dut->clk = 0;
    dut->en = 1;
    dut->D = D1;
    dut->eval();
    PULSE(dut, clk);

    // Confirm that the device has been initialized properly
    REQUIRE(dut->Q == D1);

    SECTION("Validate behaviour for en = 1'b0")
    {
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

    SECTION("Validate behaviour for en = 1'b1")
    {
        // Confirm input is not latched when enable signal is set low
        dut->en = 0;
        dut->D = D2;
        dut->eval();

        REPEAT(10)
        {
            PULSE(dut, clk);
        }
        REQUIRE(dut->Q == D1);

        // Confirm that re-enabling the device latches the input
        dut->en = 1;
        PULSE(dut, clk);
        REQUIRE(dut->Q == D2);
    }
}