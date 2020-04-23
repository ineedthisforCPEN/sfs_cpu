/*
 * module _mux16
 *
 * A 16-input multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      in      Array of inputs (size 16)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux16(sel, in, out);
    parameter n = constants::WORD_LENGTH;

    input           [  3:0] sel;
    input           [n-1:0] in [15:0];
    output  wire    [n-1:0] out;

    wire    [n-1:0] out_lower;
    wire    [n-1:0] out_upper;

    _mux8 #(n) MUX_LOWER (.sel(sel[2:0]), .in(in[ 7:0]), .out(out_lower));
    _mux8 #(n) MUX_UPPER (.sel(sel[2:0]), .in(in[15:8]), .out(out_upper));
    assign out = sel[3] ? out_upper : out_lower;
endmodule