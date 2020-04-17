/*
 * module _dff_e
 *
 * D flip-flop with enable signal. Input signal is stored and passed to the
 * output signal on every positive clock edge, but only when the enable signal
 * `en` is set high.
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


module _dff_e(clk, en, D, Q);
    parameter n = BIT_WIDTH;

    input       clk;
    input       en;
    input       [n-1:0] D;
    output  reg [n-1:0] Q;
    
    always @(posedge clk) begin
        if (en == 1'b1) begin
            Q <= D;
        end
    end
endmodule