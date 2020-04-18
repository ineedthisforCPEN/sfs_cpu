/*
 * _decoder.cpp
 *
 * Simulation and test for verilog module `_decoder`. The device is an
 * n-bit one-hot decoder. It convers a binary signal into the
 * equivalent one-hot signal.
 */

#include <stdint.h>

#include "catch.hpp"
#include "macros.hpp"
#include "V_decoder.h"

#define TAGS "[decoder][onehot]"


/*
 * TEST CASE: Validate _decoder behaviour
 *
 * Verify decoder output for all possible inputs for a 5-bit to
 * 32-bit decoder (these are the default values for the module).
 */
TEST_CASE("Validate _decoder behaviour", TAGS)
{
    V_decoder *dut = new V_decoder;
    
    // Initialize device
    dut->in = 0;
    dut->eval();

    for (int in = 0; in < 0b100000; ++in)
    {
        dut->in = in;
        dut->eval();
        REQUIRE(dut->out == 1 << in);
    }
}