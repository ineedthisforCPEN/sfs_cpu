/*
 * module _mux32
 *
 * A 32-input multiplexer.
 *
 * Parameters:
 *      n       Size of the input and output signals in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      inXX    Input XX    (output if sel = X)
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"


module _mux32(sel,
        in00, in01, in02, in03, in04, in05, in06, in07,
        in08, in09, in10, in11, in12, in13, in14, in15,
        in16, in17, in18, in19, in20, in21, in22, in23,
        in24, in25, in26, in27, in28, in29, in30, in31,
        out
);
    parameter n = constants::WORD_LENGTH;

    input           [  4:0] sel;
    input           [n-1:0] in00, in01, in02, in03, in04, in05, in06, in07;
    input           [n-1:0] in08, in09, in10, in11, in12, in13, in14, in15;
    input           [n-1:0] in16, in17, in18, in19, in20, in21, in22, in23;
    input           [n-1:0] in24, in25, in26, in27, in28, in29, in30, in31;
    output  wire    [n-1:0] out;

    wire    [n-1:0] out_lower;
    wire    [n-1:0] out_upper;

    _mux16 #(n) MUX_LOWER (
        .sel(sel[3:0]),
        .in00(in00), .in01(in01), .in02(in02), .in03(in03),
        .in04(in04), .in05(in05), .in06(in06), .in07(in07),
        .in08(in08), .in09(in09), .in10(in10), .in11(in11),
        .in12(in12), .in13(in13), .in14(in14), .in15(in15),
        .out(out_lower)
    );
    _mux16 #(n) MUX_UPPER (
        .sel(sel[3:0]),
        .in00(in16), .in01(in17), .in02(in18), .in03(in19),
        .in04(in20), .in05(in21), .in06(in22), .in07(in23),
        .in08(in24), .in09(in25), .in10(in26), .in11(in27),
        .in12(in28), .in13(in29), .in14(in30), .in15(in31),
        .out(out_upper)
    );
    assign out = sel[4] ? out_upper : out_lower;
endmodule