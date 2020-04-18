/*
 * module _mux2
 *
 * A 2-input, variable-bit width multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      in0     First input     (output if sel = 0)
 *      in1     Second input    (output if sel = 1)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux2(sel, in0, in1, out);
    parameter n = constants::WORD_LENGTH;

    input           sel;
    input           [n-1:0] in0, in1;
    output  wire    [n-1:0] out;

    assign out = sel ? in1 : in0;
endmodule