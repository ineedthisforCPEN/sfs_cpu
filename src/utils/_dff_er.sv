/*
 * module _dff_er
 *
 * D flip-flop with enable signal. Input signal is stored and passed to the
 * output signal on every positive clock edge, but only when the enable signal
 * `en` is set high.
 *
 * Parameters:
 *      n       Size of D and Q in bits
 * Inputs:
 *      clk     Clock
 *      rst     Reset signal
 *      en      Enabel signal
 *      D       Input signal (n bits)
 * Outputs:
 *      Q       Output signal (n bits)
 */

`include "constants.vh"


module _dff_er(clk, rst, en, D, Q);
    parameter n = WORD_LENGTH;

    input       clk;
    input       rst;
    input       en;
    input       [n-1:0] D;
    output  reg [n-1:0] Q;

    always @(posedge rst, posedge clk) begin
        if (rst == 1'b1) begin
            Q <= {n{1'b0}};
        end else if (en == 1'b1) begin
            Q <= D;
        end
    end
endmodule