/*
 * tb__mux.sv
 *
 * SystemVerilog testbench for variable-input, variable-width
 * multiplexer module _mux.
 */

`include "macros.vh"


module tb__mux(tb_sel, tb_count, tb_out);
    input       [2:0] tb_sel;
    input       [2:0] tb_count;
    output  reg [31:0] tb_out;

    wire        [31:0] mux_in [7:0];
    wire        [31:0] mux_out [7:1];

    genvar count;
    generate
        for (count = 0; count < 8; ++count) begin
            assign mux_in[count] = count;
        end
    endgenerate

    generate
        for (count = 2; count <= 8; ++count) begin: MUX_BLOCK
            _mux #(count, 32) MUX_BLOCK (
                .sel(tb_sel[macros::log_2(count)-1:0]),
                .in(mux_in[count-1:0]),
                .out(mux_out[count-1])
            );
        end
    endgenerate
    
    always_comb begin
        case (tb_count)
            3'b001:  tb_out = mux_out[1];
            3'b010:  tb_out = mux_out[2];
            3'b011:  tb_out = mux_out[3];
            3'b100:  tb_out = mux_out[4];
            3'b101:  tb_out = mux_out[5];
            3'b110:  tb_out = mux_out[6];
            3'b111:  tb_out = mux_out[7];
            default: tb_out = 32'b0;
        endcase
    end
endmodule