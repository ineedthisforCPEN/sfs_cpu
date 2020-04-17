/*
 * module _decoder
 *
 * A n bit one hot decoder. Decodes an n-bit signal to a one-hot m-bit
 * signal. It is the user's responsibility to ensure that m = 2^n.
 *
 * Parameters:
 *      n       Size of the input signal to decode
 *      m       Size of the output one-hot signal
 * Inputs:
 *      in      Input signal
 * Outputs:
 *      out     Output signal
 */


module _decoder(in, out);
    parameter n = 5;
    parameter m = 32;

    input       [n-1:0] in;
    output  reg [m-1:0] out;

    assign out = 1'b1 << in;
endmodule