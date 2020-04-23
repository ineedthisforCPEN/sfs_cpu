/*
 * module _mux8
 *
 * A 8-input multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      in      Array of inputs (size 8)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux8(sel, in, out);
    parameter n = constants::WORD_LENGTH;

    input           [  2:0] sel;
    input           [n-1:0] in [7:0];
    output  wire    [n-1:0] out;

    wire    [n-1:0] out_lower;
    wire    [n-1:0] out_upper;

    _mux4 #(n) MUX_LOWER (.sel(sel[1:0]), .in(in[3:0]), .out(out_lower));
    _mux4 #(n) MUX_UPPER (.sel(sel[1:0]), .in(in[7:4]), .out(out_upper));
    assign out = sel[2] ? out_upper : out_lower;
endmodule