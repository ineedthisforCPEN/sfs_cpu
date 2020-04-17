/*
 * _dff_r.cpp
 *
 * Simulation and test for verilog module `_dff_r`. The device is a
 * standard D-flip-flop that latches the input on every positive clock
 * cycle and can have the output reset to 0 while the reset signal
 * `rst` is set high.
 */

#include <stdint.h>

#include "catch.hpp"
#include "macros.hpp"
#include "V_dff_r.h"

#define TAGS "[dff][dff_r]"


/*
 * TEST CASE: Validate _dff_r behaviour
 *
 * Confirm that the device behaves like a standard D-flip-flop when the
 * reset signal is low.
 *
 * Confirm that the reset signal overrides standard D-flip-flop
 * behaviour.
 */
TEST_CASE("Validate _dff_r behaviour", TAGS)
{
    V_dff_r *dut = new V_dff_r;
    uint32_t D1 = 0x00000000;
    uint32_t D2 = 0xFFFFFFFF;

    // Initialize device
    dut->clk = 0;
    dut->rst = 0;
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
    }

    SECTION("Validate standard behaviour")
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
}