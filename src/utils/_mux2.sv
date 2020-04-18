/*
 * module _mux2
 *
 * A 2-input, variable-bit width multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      in      Array of inputs (size 2)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux2(sel, in, out);
    parameter n = constants::WORD_LENGTH;

    input           sel;
    input           [n-1:0] in [1:0];
    output  wire    [n-1:0] out;

    assign out = sel ? in[1] : in[0];
endmodule