/*
 * macros.vh
 *
 * Definitions for commonly used macros/functions. These are NOT meant
 * for synthesis. These are intended to be used for calculations for
 * module parameters.
 */

`ifndef _macros_vh
`define _macros_vh

package macros;
    /*
     * log_2
     *
     * Calculate log-base-2 (rounded down) of a given input.
     *
     * Parameters:
     *      value   Value whose log-base-2 to calculate
     *
     * Return:
     *      Returns the floor of log-base-2 of the given value.
     */
    function int log_2;
        input int value;
        for (log_2 = 0; value > 0; ++log_2) begin
            value = value >> 1;
        end
        log_2 -= 1;
    endfunction
endpackage;

`endif