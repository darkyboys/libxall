/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Checkout the README.md for more information
 * libXALL - The official implementation of xall lang.
 */

// This file is very important for linking everything together.

// Source starts from here
#include <cstddef>
#ifndef LIBXALL
#define LIBXALL 1

// Std Cxx17 STL
#include <iostream>
#include <string>
#include <vector>

namespace libxall {
    typedef std::vector <std::string> str_vector; // str_vector is the shortform for writting the string vector declaration
    
    std::string exec(std::string arg_line){ // arg keyword here helps to remember the arg_line is function argument
        std::string rendered_xhtml; // the variable for containing the rendered xhtml, xhtml means some xall concepts will be still present in html so that's why xhtml for xall html.
        
        bool is_string_open = false, // flag used to set the status of string weather it's open/closed.
             is_function_open = false,
             append_string = false,
             make_function = false,
             is_children_open = false,
             is_childern_childern_open = false;
        
        // Minimal signals
        bool is_childern_string_open = false;
        
        std::string function_name,
                    function_data,
                    children_data;
        
        str_vector functions_name = {},
                   functions_data = {};

        for (std::size_t i = 0;i < arg_line.length();i++) { // loop through every character in the line! Initially turning character into tokens.
            std::cout<<"'"<<arg_line[i]<<"'\n"; // debugging the initial tokens
            // now tokenising the xall syntax to understand the code - This section will use a full state-machiene for this task
            // Please do not change the order of anything. The State machiene may broke quickly
            // String management
            if (arg_line[i] == '`' and is_string_open and arg_line[i-1] == '\\') append_string = true; // if the string was open but now requested to be closed so close it
            else if (arg_line[i] == '`' and is_string_open) is_string_open = false; // if the string was open but now requested to be closed so close it
            else if (arg_line[i] == '`' and not is_string_open) { is_string_open = true; continue;}// if the string was not opened so open it
            // String management - Closed

            // Line Ending Unit
            if (arg_line[i] == ';' and not is_function_open and not is_string_open) { // means the program wants to end the line so end it with a simple ending logic
                arg_line = arg_line.substr(i+1); // cut the previous line
                i = 0; // restart the loop, Here we wrote 0 because the index 0 will be the new starting point of the functions so the lexical annalysis will be correct and accurate. 
                make_function = true; // set make function to true for making a function.
            }

            else if (arg_line[i] == ';' and is_function_open and not is_string_open) { // means the program wants to end the line so end it with a simple ending logic
                std::cout<<"Error -> Function "<<function_name<<" was already open so why terminating the line with ';' ?\n", std::exit ( 3 );
            }

            // Children Handeling Unit
            if (arg_line[i] == '{' and not is_function_open and not is_string_open and not is_children_open and not is_childern_childern_open) { // means the program wants to open up the children so open it
                std::cout<<"Starting the unit at : "<<i<<"\n";
                std::size_t ended_string_pos = 0;
                for (std::size_t x = i+1;x < arg_line.length();x++){
                    // std::cout<< "test: "<<arg_line[x]<<"\n";
                    // Minimal string handeling.
                    if (arg_line[x] == '`' and is_childern_string_open and arg_line[x-1] == '\\') is_childern_string_open = true;
                    else if (arg_line[x] == '`' and is_childern_string_open) is_childern_string_open = false, ended_string_pos = x;
                    else if (arg_line[x] == '`' and not is_childern_string_open) is_childern_string_open = true;

                    // std::cout<<"test: string-status("<<is_childern_string_open<<")\n";
                    // children manager
                    children_data += arg_line[x];

                    // Children management unit
                    // if (arg_line[x] == '}' and is_childern_childern_open and not is_childern_string_open) is_childern_childern_open = false, std::cout<<"Successfully closed the children\n";
                    // else if (arg_line[x] == '{' and not is_childern_childern_open and not is_childern_string_open) is_childern_childern_open = true, std::cout<<"Successfully opened the children\n";
                    // else if (arg_line[x] == '}' and not is_childern_string_open and not is_childern_childern_open) {
                    //     std::string exec_children = exec(children_data);
                    //     function_data += exec_children;
                    //     children_data.clear();
                    //     i = x;
                    //     std::cout<< "Ending the unit at : "<<x<<"\n"<<"With data : "<<exec_children<<"\n"<<"The value of i : "<<i<<"\n"<<"function name : "<<function_name<<"\n"<<"function data : "<<function_data<<"\n";
                    //     break;
                    // }
                    
                    // if (arg_line[x] == '{' and not is_childern_childern_open and not is_childern_string_open) {
                    //     std::size_t blocks = 1;
                    //     for (std::size_t a = x;a < arg_line.length();a++) {
                    //         children_data += arg_line[a];
                    //         std::cout<<"Value a : "<<a<<"\n";
                    //         if (blocks == 0) break;
                    //         if (arg_line[a] == '{' and not is_childern_string_open) blocks += 1;
                    //         if (arg_line[a] == '}' and not is_childern_string_open) blocks -= 1;
                    //         std::cout<<"The value of blocks : "<<blocks<<"\n"<<"string: "<<arg_line[a]<<"\n";
                    //     }
                    //     std::cout<<"Got Content: "<<children_data<<"\n";
                    // }

                    // std::cout<<"Children strings: "<<is_childern_childern_open<<"\n";

                }
                std::size_t terminate_children = arg_line.rfind("}");
                if (terminate_children == std::string::npos) std::cout<<"Error -> Function Extender For "<<function_name<<" was already Opened but not closed! Expected '}'.\n", std::exit ( 3 );
                if (terminate_children > ended_string_pos) {
                    std::string exec_content = arg_line.substr(i+1, terminate_children);
                    i = terminate_children;
                    std::string pre_batch_compile_output_output = exec(exec_content);
                    function_data += pre_batch_compile_output_output;
                    std::cout<<"Exec: "<<pre_batch_compile_output_output<<"\n"<<"function name: "<<function_name<<"\nfunction data: "<<function_data<<"\n";
                }
            }


            // Function management 
            if (arg_line[i] == '(' and not is_function_open and not is_string_open) { // if function was not open then open it
                // std::cout<<"Collision detected!\n";
                is_function_open = true;
                std::string temp; // hold the temporary name
                for (std::size_t x = i-1;x >= 0;x--) {
                    if (x == 0) {
                        if (arg_line[0] == ' ') break;
                        else {
                            temp += arg_line[x];
                            break;
                        }
                    }
                    else if (arg_line[x] == ' ') continue; // ignore white spaces
                    else {
                        temp += arg_line[x];
                    }
                    // std::cout<<"temp: "<<temp<<"\n"; // debussing purpose
                } // here we get the function name in reversed order , Now we must reverse it again to get a fixed version
                for (std::size_t y = temp.length()-1;y >= 0;y--){
                    function_name += temp [y];
                    if (y == 0) break;
                } // here we get the real function name

                // std::cout<<"'"<<function_name<<"'\n"; // debug the function name when needed
            } // Extracted the function name and the function status is set to open now
            else if (arg_line[i] == '(' and is_function_open and not is_string_open) std::cout<<"Error -> Function "<<function_name<<" was already open so why reopening it again ?\n", std::exit ( 3 );
            else if (arg_line[i] == ')' and is_function_open and not is_string_open) is_function_open = false;
            else if (arg_line[i] == ')' and not is_function_open and not is_string_open)  std::cout<<"Error -> Function "<<function_name<<" was already closed so why reclosing it again ?\n", std::exit ( 3 );
            
            // Function Argument Management & Rendering Unit
            if (is_string_open and is_function_open) {
                if (append_string) {
                    function_data.pop_back();
                    function_data += "`";
                    append_string = false;
                }
                else {
                    function_data += arg_line[i];
                }
            } // append to the data when string is an argument
            // std::cout<<"Func status : "<<is_function_open<<"\nstring state : "<<is_string_open<<"\n";
            if (make_function) {
                functions_data.push_back(function_data);
                function_data.clear();
                functions_name.push_back(function_name);
                function_name.clear();
                make_function = false;
            }
        }
    
        for (std::size_t f = 0;f < functions_name.size();f++){
            // std::cout<<"function name is : "<<functions_name[f]<<"\nfunction data is : "<<functions_data[f]<<"\n";
            rendered_xhtml += "<" + functions_name[f] + ">" + functions_data[f] + "</" + functions_name[f] + ">";
        }

        // rendered_xhtml = "<" + function_name  + ">" + function_data + "</" + function_name  + ">";

        return rendered_xhtml;
    }
};

#endif