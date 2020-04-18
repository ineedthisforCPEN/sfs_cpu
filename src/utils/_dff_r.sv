/*
 * module _dff_r
 *
 * D flip-flop with reset signal. Input signal is stored and passed to the
 * output signal on every positive clock edge. Additionally, while the reset
 * signal is held high, the output will be forced low for all n bits.
 *
 * Parameters:
 *      n       Size of D and Q in bits
 * Inputs:
 *      clk     Clock
 *      en      Enabel signal
 *      D       Input signal (n bits)
 * Outputs:
 *      Q       Output signal (n bits)
 */

`include "constants.vh"


module _dff_r(clk, rst, D, Q);
    parameter n = WORD_LENGTH;

    input       clk;
    input       rst;
    input       [n-1:0] D;
    output  reg [n-1:0] Q;

    always @(posedge rst, posedge clk) begin
        if (rst == 1'b1) begin
            Q <= {n{1'b0}};
        end else begin
            Q <= D;
        end
    end
endmodule