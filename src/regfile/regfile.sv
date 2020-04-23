/*
 * module regfile
 *
 * A simple register file implemenation with one data input and two
 * data output ports in order to support single-cycle execution of
 * certain arithmetic operations (e.g. C = A + B).
 *
 * Inputs:
 * Outputs:
 */

`include "constants.vh"
`include "macros.vh"


module regfile(
    clk, rst, en,                       // Control signals
    addr_in, addr_out_1, addr_out_2,    // Address ports
    data_in, data_out_1, data_out_2     // Data ports
);
    localparam addr = macros::log_2(constants::WORD_LENGTH);
    localparam size = constants::REGFILE_SIZE;
    localparam word = constants::WORD_LENGTH;

    // Constrol signals
    input       clk;
    input       rst;
    input       en;

    // Address ports
    input       [addr-1:0] addr_in;
    input       [addr-1:0] addr_out_1;
    input       [addr-1:0] addr_out_2;

    // Data ports
    input       [word-1:0] data_in;
    output  reg [word-1:0] data_out_1;
    output  reg [word-1:0] data_out_2;

    // Internal wires
    wire    [size-1:0] register_en;
    wire    [word-1:0] register_out [size-1:0];

    // Modules for internal constrol signals and data flow
    _decoder #(addr, size) DECODE_ADDR_IN (
        .in(addr_in),
        .out(register_en)
    );
    _mux #(size, word) MUX_DATA_OUT_1 (
        .sel(addr_out_1),
        .in(register_out),
        .out(data_out_1)
    );
    _mux #(size, word) MUX_DATA_OUT_2 (
        .sel(addr_out_2),
        .in(register_out),
        .out(data_out_2)
    );

    // Instantiate the registers
    genvar reg_num;
    generate
        for (reg_num = 0; reg_num < constants::REGFILE_SIZE; ++reg_num)
        begin: REGISTER
            _dff_er #(word) REGISTER (
                .clk(clk),
                .rst(rst),
                .en(en & register_en[reg_num]),
                .D(data_in),
                .Q(register_out[reg_num])
            );
        end
    endgenerate
endmodule