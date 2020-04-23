/*
 * module _mux4
 *
 * A 4-input multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      in      Array of inputs (size 4)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux4(sel, in, out);
    parameter n = constants::WORD_LENGTH;

    input           [  1:0] sel;
    input           [n-1:0] in [3:0];
    output  wire    [n-1:0] out;

    wire    [n-1:0] out_lower;
    wire    [n-1:0] out_upper;

    _mux2 #(n) MUX_LOWER (.sel(sel[0]), .in(in[1:0]), .out(out_lower));
    _mux2 #(n) MUX_UPPER (.sel(sel[0]), .in(in[3:2]), .out(out_upper));
    assign out = sel[1] ? out_upper : out_lower;
endmodule