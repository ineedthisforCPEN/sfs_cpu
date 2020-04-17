/*
 * _dff_er.cpp
 *
 * Simulation and test for verilog module `_dff_er`. The device is a
 * standard D-flip-flop that latches the input on every positive clock
 * cycle when the enable signal `en` is set high, and can have the
 * output reset to 0 while the reset signal `rst` is set high.
 */

#include <stdint.h>

#include "catch.hpp"
#include "macros.hpp"
#include "V_dff_er.h"

#define TAGS "[dff][dff_er]"


/*
 * TEST CASE: Validate _dff_er behaviour
 *
 * Confirm that the device behaves like a standard D-flip-flop when the
 * enable signal is set high, and does not latch input when the enable
 * signal is set low.
 *
 * Confirm that the reset signal overrides standard D-flip-flop
 * behaviour.
 */
TEST_CASE("Validate _dff_er behaviour", TAGS)
{
    V_dff_er *dut = new V_dff_er;
    uint32_t D1 = 0x00000000;
    uint32_t D2 = 0xFFFFFFFF;
    uint32_t D3 = 0x55555555;

    // Initialize device
    dut->clk = 0;
    dut->rst = 0;
    dut->en = 1;
    dut->D = D1;
    dut->eval();
    PULSE(dut, clk);

    // Confirm that the device has been initialized properly
    REQUIRE(dut->Q == D1);

    SECTION("Validate behaviour for rst signal")
    {
        dut->D = D2;
        PULSE(dut, clk);
        REQUIRE(dut->Q == D2);

        SECTION("Pulsing reset signal resets device")
        {
            PULSE(dut, rst);
            REQUIRE(dut->Q == 0);
        }

        SECTION("Holding reset high keeps output reset")
        {
            dut->rst = 1;
            dut->eval();
            REQUIRE(dut->Q == 0);

            dut->D = D2;
            REPEAT(10)
            {
                PULSE(dut, clk);
            }
            REQUIRE(dut->Q == 0);
        }

        SECTION("Reset signal overrides enable signal")
        {
            dut->en = 0;
            dut->D = D3;
            dut->eval();
            REPEAT(10)
            {
                PULSE(dut, clk);
            }
            REQUIRE(dut->Q == D2);

            dut->rst = 1;
            dut->eval();
            REQUIRE(dut->Q == 0);
        }
    }

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