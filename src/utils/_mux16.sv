/*
 * module _mux16
 *
 * A 16-input multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      inXX    Inputs XX   (0 through 15)(output if sel = XX)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux16(sel,
        in00, in01, in02, in03, in04, in05, in06, in07,
        in08, in09, in10, in11, in12, in13, in14, in15,
        out
);
    parameter n = constants::WORD_LENGTH;

    input           [  3:0] sel;
    input           [n-1:0] in00, in01, in02, in03, in04, in05, in06, in07;
    input           [n-1:0] in08, in09, in10, in11, in12, in13, in14, in15;
    output  wire    [n-1:0] out;

    wire    [n-1:0] out_lower;
    wire    [n-1:0] out_upper;

    _mux8 #(n) MUX_LOWER (
        .sel(sel[2:0]),
        .in0(in00), .in1(in01), .in2(in02), .in3(in03),
        .in4(in04), .in5(in05), .in6(in06), .in7(in07),
        .out(out_lower)
    );
    _mux8 #(n) MUX_UPPER (
        .sel(sel[2:0]),
        .in0(in08), .in1(in09), .in2(in10), .in3(in11),
        .in4(in12), .in5(in13), .in6(in14), .in7(in15),
        .out(out_upper)
    );
    assign out = sel[3] ? out_upper : out_lower;
endmodule