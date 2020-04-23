/*
 * regfile.cpp
 *
 * Simulation and test for verilog module `regfile`. The device is the
 * CPU register file. This test is for a simple implementation with one
 * input data port and two output data ports, allowing for single-cycle
 * computation for arithmetic formulae of the form C = A + B.
 */

#include "catch.hpp"
#include "macros.hpp"
#include "Vregfile.h"

#define TAGS "[regfile][simple]"
#define REGFILE_SIZE 32


/*
 * TEST CASE: Validate register file behaviour
 *
 * Confirm that the following features work as expected:
 *      - Enable signal
 *      - Single port read (ports 1 and 2)
 *      - Dual port read
 *      - Write and single port read (ports 1 and 2)
 *      - Write and dual port read
 *      - Reset signal
 */
TEST_CASE("Validate register file behaviour", TAGS)
{
    Vregfile *dut = new Vregfile;

    // Initialize device
    dut->clk = 0;
    dut->rst = 1;   // Reset device
    dut->en = 1;
    dut->addr_in = 0;
    dut->data_in = 0;
    dut->addr_out_1 = 0;
    dut->addr_out_2 = 0;
    PULSE(dut, clk);
    dut->rst = 0;

    for (int port = 0; port < REGFILE_SIZE; ++port)
    {
        dut->addr_in = port;
        dut->data_in = port;
        PULSE(dut, clk);
    }
    dut->en = 0;
    dut->eval();

    SECTION("Enable signal")
    {
        for (int port = 0; port < REGFILE_SIZE; ++port)
        {
            dut->addr_in = port;
            dut->data_in = 0xFFFFFFFF;
            PULSE(dut, clk);
        }
        for (int port = 0; port < REGFILE_SIZE; ++port)
        {
            dut->addr_out_1 = port;
            dut->eval();
            REQUIRE(dut->data_out_1 == port);
        }

        dut->en = 1;
        for (int port = 0; port < REGFILE_SIZE; ++port)
        {
            dut->addr_in = port;
            dut->data_in = 0xFFFFFFFF;
            PULSE(dut, clk);
        }
        for (int port = 0; port < REGFILE_SIZE; ++port)
        {
            dut->addr_out_1 = port;
            dut->eval();
            REQUIRE(dut->data_out_1 == 0xFFFFFFFF);
        }
    }

    SECTION("Single-port read")
    {
        SECTION("PORT 1")
        {
            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_out_1 = port;
                dut->eval();
                REQUIRE(dut->data_out_1 == port);
            }
        }
        
        SECTION("PORT 2")
        {
            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_out_2 = port;
                dut->eval();
                REQUIRE(dut->data_out_2 == port);
            }
        }
    }

    SECTION("Dual-port read")
    {
        for (int port1 = 0; port1 < REGFILE_SIZE; ++port1)
        {
            for (int port2 = 0; port2 < REGFILE_SIZE; ++port2)
            {
                dut->addr_out_1 = port1;
                dut->addr_out_2 = port2;
                dut->eval();
                REQUIRE(dut->data_out_1 == port1);
                REQUIRE(dut->data_out_2 == port2);
            }
        }
    }

    SECTION("Write and single-port read (different registers)")
    {
#if REGFILE_SIZE > 1
        dut->en = 1;
        dut->eval();

        SECTION("PORT 1")
        {
            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_in = port;
                dut->addr_out_1 = (port + 1) % REGFILE_SIZE;
                dut->eval();
                dut->data_in = dut->data_out_1;
                PULSE(dut, clk);
            }

            dut->en = 0;
            dut->eval();
            for (int port = 0; port < REGFILE_SIZE - 1; ++port)
            {
                dut->addr_out_1 = port;
                dut->eval();
                REQUIRE(dut->data_out_1 == (port + 1) % REGFILE_SIZE);
            }

            dut->addr_out_1 = REGFILE_SIZE - 1;
            dut->eval();
            REQUIRE(dut->data_out_1 == 1);
        }

        SECTION("PORT 2")
        {
            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_in = port;
                dut->addr_out_2 = (port + 1) % REGFILE_SIZE;
                dut->eval();
                dut->data_in = dut->data_out_2;
                PULSE(dut, clk);
            }

            dut->en = 0;
            dut->eval();

            for (int port = 0; port < REGFILE_SIZE - 1; ++port)
            {
                dut->addr_out_2 = port;
                dut->eval();
                REQUIRE(dut->data_out_2 == (port + 1) % REGFILE_SIZE);
            }

            dut->addr_out_2 = REGFILE_SIZE - 1;
            dut->eval();
            REQUIRE(dut->data_out_2 == 1);
        }
#endif
    }

    SECTION("Write and single-port read (same registers)")
    {
        dut->en = 1;
        dut->eval();

        SECTION("PORT 1")
        {
            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_in = port;
                dut->addr_out_1 = port;
                dut->eval();
                dut->data_in = dut->data_out_1 << 1;
                PULSE(dut, clk);
            }

            dut->en = 0;
            dut->eval();

            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_out_1 = port;
                dut->eval();
                REQUIRE(dut->data_out_1 == port << 1);
            }
        }

        SECTION("PORT 2")
        {
            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_in = port;
                dut->addr_out_2 = port;
                dut->eval();
                dut->data_in = dut->data_out_2 << 1;
                PULSE(dut, clk);
            }

            dut->en = 0;
            dut->eval();

            for (int port = 0; port < REGFILE_SIZE; ++port)
            {
                dut->addr_out_2 = port;
                dut->eval();
                REQUIRE(dut->data_out_2 == port << 1);
            }
        }
    }

    SECTION("Write and dual-port read")
    {
        dut->en = 1;
        dut->eval();

        for (int port1 = 0; port1 < REGFILE_SIZE; ++port1)
        {
            for (int port2 = 0; port2 < REGFILE_SIZE; ++port2)
            {
                for (int inport = 0; inport < REGFILE_SIZE; ++inport)
                {
                    SECTION("")
                    {
                        dut->addr_in = inport;
                        dut->addr_out_1 = port1;
                        dut->addr_out_2 = port2;
                        dut->eval();
                        dut->data_in = dut->data_out_1 + dut->data_out_2;
                        PULSE(dut, clk);

                        dut->addr_out_1 = inport;
                        dut->eval();
                        REQUIRE(dut->data_out_1 == port1 + port2);
                    }
                }
            }
        }
    }

    SECTION("Reset signal")
    {
        // Ensure that the reset signal overrides the enable signal
        dut->rst = 1;
        dut->eval();

        for (int port = 0; port < REGFILE_SIZE; ++port)
        {
            dut->addr_out_1 = port;
            dut->eval();
            REQUIRE(dut->data_out_1 == 0);
        }

        // Ensure the reset holds even when we attempt to write
        for (int port = 0; port < REGFILE_SIZE; ++port)
        {
            dut->addr_in = port;
            dut->data_in = 0xFFFFFFFF;
            PULSE(dut, clk);
        }

        for (int port = 0; port < REGFILE_SIZE; ++port)
        {
            dut->addr_out_1 = port;
            dut->eval();
            REQUIRE(dut->data_out_1 == 0);
        }
    }
}