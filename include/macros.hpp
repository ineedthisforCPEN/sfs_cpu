#ifndef _SFS_CPU_TEST_MACROS_H
#define _SFS_CPU_TEST_MACROS_H

/*
 * MACRO: REPEAT
 *
 * Repeat a series of steps a given number of times
 *
 * Parameters:
 *      n   The number of times to repeat the steps
 */
#define REPEAT(n)   for (int __repeat = 0; __repeat < n; ++__repeat)

/*
 * MACRO: TICK
 *
 * Let one half clock cycle elapse for a given device under test. Assumes that
 * the clock signal of the device is named `clk`
 *
 * Parameters:
 *      dut     Device under test
 */
#define TICK(dut)   dut->clk = ~(dut->clk); \
                    dut->eval();

/*
 * MACRO: PULSE
 *
 * Pulse the signal of a device under test, inverting it twice.
 *
 * Parameters:
 *      dut     Device under test
 *      signal  Signal to pulse
 */
#define PULSE(dut, signal)  dut->signal = ~(dut->signal); \
                            dut->eval(); \
                            dut->signal = ~(dut->signal); \
                            dut->eval();

#endif  // _SFS_CPU_TEST_MACROS_H