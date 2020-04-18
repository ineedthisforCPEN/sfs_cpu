/*
 * module _mux8
 *
 * A 8-input multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      inX     Input X     (output if sel = X)
 * Outputs:
 *      out     The select input signal
 */
module _mux8(sel, in0, in1, in2, in3, in4, in5, in6, in7, out);
    parameter n = WORD_LENGTH;

    input           [  2:0] sel;
    input           [n-1:0] in0, in1, in2, in3, in4, in5, in6, in7;
    output  wire    [n-1:0] out;

    wire    [n-1:0] out_lower;
    wire    [n-1:0] out_upper;

    _mux4 #(n) MUX_LOWER (
        .sel(sel[1:0]),
        .in0(in0), .in1(in1), .in2(in2), .in3(in3),
        .out(out_lower)
    );
    _mux4 #(n) MUX_UPPER (
        .sel(sel[1:0]),
        .in0(in4), .in1(in5), .in2(in6), .in3(in7),
        .out(out_upper)
    );
    assign out = sel[2] ? out_upper : out_lower;
endmodule