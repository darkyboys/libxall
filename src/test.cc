/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Checkout the README.md for more information
 * libXALL - The official implementation of xall lang.
 */

// This file contains the test

// Source
#include "xall.hh"
#include <fstream>

int main(){
    std::string code = "print (`hello\\`\\` world 2024`) { b (`hello world\\` 2025`) { p ( `hy`) { h1 (`HE`); }; h6 (``){b(`hy`)} } }; ";
    std::string rhtml = libxall::exec(code);
    std::ofstream a("a.html");
    a << rhtml; 
}