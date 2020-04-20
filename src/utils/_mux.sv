/*
 * module _mux
 *
 * A variable-input, variable-bit width multiplexer.
 *
 * Parameters:
 *      n       Number of inputs
 *      w       Width of inputs in bits
 * Inputs:
 *      sel     Signal that selects which input to forward
 *      in      Input signal as an array on inputs
 * Outputs:
 *      out     The select input signal
 */

`include "constants.vh"
`include "macros.vh"

module _mux(sel, in, out);
    parameter n = constants::REGFILE_SIZE;
    parameter w = constants::WORD_LENGTH;
    localparam s = macros::log_2(n);

    input           [s-1:0] sel;
    input           [w-1:0] in [n-1:0];
    output  wire    [w-1:0] out;

    genvar          i;
    /* verilator lint_off UNOPTFLAT */  // Generate below not circular
    /* verilator lint_off WIDTH */      // Unused bit sel_onehot[0]
    /* verilator lint_off UNUSED */     // Unused bit sel_onehot[0]
    wire    [w-1:0] mux_out [n-1:0];
    wire    [n-1:0] sel_onehot;
    /* verilator lint_on UNOPTFLAT */
    /* verilator lint_on WIDTH */
    /* verilator lint_on UNUSED */

    _decoder #(s, n) SEL_DECODER(.in(sel), .out(sel_onehot));

    assign mux_out[0] = in[0];
    generate
        for (i = 1; i < n; ++i) begin
            assign mux_out[i] = sel_onehot[i] ? in[i] : mux_out[i-1];
        end
    endgenerate
    assign out = mux_out[n-1];
endmodule