/*
 * main.cpp
 *
 * Run all simulations and unit tests for each CPU component. Each
 * component should have its own unit tests and simulations. This
 * file serves only to initialize verilated in the main function
 * before running each test.
 *
 * No unit tests should be performed or performed here. This file
 * should only be modified if global setup or cleanup needs to be
 * modified.
 */

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "verilated.h"

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    return Catch::Session().run(argc, argv);
}