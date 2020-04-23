/*
 * _mux.cpp
 *
 * Simulation and test for verilog module `_mux`. The device is a
 * variable input, variable bit-width multiplexer.
 *
 * The test uses testbench `tb__mux`, which implements several 32-bit
 * wide multiplexers ranging from 2 to 8 inputs. The inputs are
 * hardcoded in the module so that inputN == N. 
 */

#include "catch.hpp"
#include "macros.hpp"
#include "Vtb__mux.h"


/*
 * TEST CASE: Validate _mux behaviour for variable inputs
 *
 * Confirm that no matter how many input signals the mux is
 * instantiated with, we will get the expected output.
 */
TEST_CASE("Validate _mux behaviour for variable inputs", "[mux][var_inputs]")
{
    Vtb__mux *dut = new Vtb__mux;

    for (int count = 2; count <= 8; ++count)
    {
        for (int sel = 0; sel < count; ++sel)
        {
            dut->tb_sel = sel;
            dut->tb_count = count - 1;
            dut->eval();
            REQUIRE(dut->tb_out == sel);
        }
    }
}