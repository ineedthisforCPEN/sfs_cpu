/*
 * _dff.sv
 *
 * Standard D flip-flop. Input signal is stored and passed to the output wire
 * on every positive clock edge.
 *
 * Parameters:
 *      n       Size of D and Q (in bits)
 * Inputs:
 *      clk     Clock
 *      D       Input signal (n bits)
 * Output:
 *      Q       Output wire (n bits)
 */

`include "constants.vh"

module _dff(clk, D, Q);
    parameter n = WORD_LENGTH;

    input       clk;
    input       [n-1:0] D;
    output  reg [n-1:0] Q;

    always @(posedge clk) begin
        Q <= D;
    end
endmodule