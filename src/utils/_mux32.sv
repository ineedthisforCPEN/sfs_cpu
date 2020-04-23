/*
 * module _mux32
 *
 * A 32-input multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      in      Array of inputs (size 32)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux32(sel, in, out);
    parameter n = constants::WORD_LENGTH;

    input           [  4:0] sel;
    input           [n-1:0] in [31:0];
    output  wire    [n-1:0] out;

    wire    [n-1:0] out_lower;
    wire    [n-1:0] out_upper;

    _mux16 #(n) MUX_LOWER (.sel(sel[3:0]), .in(in[15: 0]), .out(out_lower));
    _mux16 #(n) MUX_UPPER (.sel(sel[3:0]), .in(in[31:16]), .out(out_upper));
    assign out = sel[4] ? out_upper : out_lower;
endmodule