/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer on Sat, Jan 18, 05:52PM Timzone-Asia/Kolkata
 * Licensed under the MIT License
 * Checkout the DOCS For More information
*/

// Source
#ifndef LIB_XALL1
#define LIB_XALL1 1

// C++ STL
#include <iostream>
#include <string>
#include <cstddef>
#include <iterator>
#include <vector>

// Lib XTypes is defined here
namespace LibXTypes {
    std::size_t is_String(std::string __in__, std::size_t index){
        std::size_t rval = 2;
        bool is_String_Started = false;
        std::size_t string_StartPoint, string_EndPoint; // Current string management
        for (std::size_t i = 0;i < __in__.length();i++){
            if (index > __in__.length()) break; // For Type safety
            
            if (__in__[i] == '\"' && is_String_Started == true){ // string ended
                is_String_Started = false;
                string_EndPoint = i;
                // std::cout<<"end point"<<string_EndPoint<<"\n"; // test
                if (index > string_StartPoint && index < string_EndPoint){
                    rval = 1;
                    // std::cout<<"Collision detected!\n";
                    break;
                }
                else rval = 0;
            }
            else if (__in__[i] == '\"' && is_String_Started == false){ // string started
                is_String_Started = true;
                string_StartPoint = i;
                // std::cout<<"start point"<<string_StartPoint<<"\n"; // test
            }
        }
        if (string_EndPoint < string_StartPoint) {
            std::cout<<"Error during the Tokenisation: LibXTypes - String Operator Error. The String was not closed!, Can't Proceed The Compilation.\n";
            std::exit ( 3 );
        }

        return rval;
    }

    std::vector <char> reserved_Symbols = {'(', ')', ';'};

    std::size_t is_Terminatable(char __char__){
        std::size_t rval = 0;
        for (std::size_t i = 0;i < reserved_Symbols.size();i++){
            if (__char__ == reserved_Symbols[i]) rval = 1;
        }
        return rval;
    }

    void remove_XStringSyntax(std::string& line){
        std::string fval;
        // std::cout<<"Line is "<<line<<"\n";
        for (std::size_t i = 0;i < line.length();i++){
            // std::cout<<line[i]<<"\n"; // test
            if (line[i] == '\"'){
                // std::cout<<"Terminatable found on : "<<i<<"\n"; // test
                continue;
            }
            fval += line[i];
        }
        line = fval;
        fval.clear();
    }
};

// XALL Lang Classes
class XALL{
public:
    std::string code_Line = "";
    XALL (std::string __code_Line__) : code_Line(__code_Line__) {};
    // Once we have the code line we must provide the XALL LibXCompiler Direct Access
    // LibXCompiler Starts from here
    std::string XCompile(){
        std::string html;
        std::string config_tagName, config_tagContent, config_tagAttributes; // tokens
        bool is_Block_Open = false, is_String_Open = false, is_Squae_Open = false, is_Statement_Open = false, is_First_Argument = true; // Flags For State Machiene
        std::size_t squae_StartPos, last_BendPos;
        std::string attribute_Name, attribute_Value;
        bool is_String_Secondary_Open = false;
        for (std::size_t i = 0;i < code_Line.length();i++){
            // html += code_Line[i] + std::string("\n"); // test
            // Syntax Lexical Annalyser Unit - Main
            if (is_String_Secondary_Open){
                attribute_Value += code_Line[i];
            }
            if (is_Squae_Open && code_Line[i] == '\"'){
                if (LibXTypes::is_String(code_Line, i) == 0){
                    if (is_String_Secondary_Open){ // string closed
                        is_String_Secondary_Open = false;
                    }
                    else if (is_String_Secondary_Open == false){ // string opened
                        is_String_Secondary_Open = true;
                    }
                }
            }
            if (is_Squae_Open && code_Line[i] == ':'){
                if (LibXTypes::is_String(code_Line, i) == 0){
                    if (is_First_Argument){
                        for (std::size_t x = i;x > squae_StartPos;x--){
                            attribute_Name += code_Line[x];
                            if (x == squae_StartPos){
                                break;
                            }
                        }
                        std::string str_aname;
                        for (std::size_t y = attribute_Name.length();y > 0;y--) str_aname += attribute_Name[y];
                        attribute_Name = str_aname;
                        str_aname.clear();
                    }
                }
            }
            if (code_Line[i] == ']'){
                if (LibXTypes::is_String(code_Line, i) == 0){
                    // std::cout<<"Bracket Found! Squae - closed\n";
                    if (is_Squae_Open == true) is_Squae_Open = false;
                    else {
                        std::cout<<"Error during Tokenisation : LibXALL Error -> Can't Close Squae While a Squae is not opened.\n";
                    }
                    std::string main_attribute_value;
                    for (std::size_t z = 0;z < attribute_Value.length();z++){
                        if (attribute_Value[z] == '\"') continue;
                        main_attribute_value += attribute_Value[z];
                    }
                    attribute_Value = main_attribute_value;
                    config_tagAttributes += attribute_Name + "=\"" + attribute_Value + "\" ";
                    // std::cout<<"Arg name: "<<attribute_Name<<"\nArg Value: "<<attribute_Value<<"\n"; // argument name
                    attribute_Name = attribute_Value = "";
                }
            }
            else if (code_Line[i] == '['){
                if (LibXTypes::is_String(code_Line, i) == 0){
                    // std::cout<<"Bracket Found! Squae - Open\n";
                    if (is_Squae_Open == false) {
                        is_Squae_Open = true;
                        squae_StartPos = i;
                    }
                    else {
                        std::cout<<"Error during Tokenisation : LibXALL Error -> Can't Open Another Squae While a Squae is already opened.\n";
                    }
                }
            }
            // Function Lexer
            if (code_Line[i] == '\"'){
                if (LibXTypes::is_String(code_Line, i) == 0){
                    if (is_String_Open){ // String closing
                        is_String_Open = false;
                        // std::cout<<"String closed at "<<i<<"\n"; // test
                    }
                    else if (is_String_Open == false){ // Open The String
                        is_String_Open = true;
                        // std::cout<<"String opened at "<<i<<"\n"; // test
                    }
                }
            }
            else if (code_Line[i] == ')'){
                if (LibXTypes::is_String(code_Line, i) == 0 && is_Block_Open){
                    is_Block_Open = false;
                    // std::cout<<"Closing block found at "<<i<<"\n"<<"Block Status : "<<is_Block_Open<<"\n"; // test
                }
            }
            else if (code_Line[i] == '('){
                // std::cout<<"Colision found at: "<<i<<"\n"<<"Status of collision: "<<LibXTypes::is_String(code_Line, i) <<"\n";
                if (LibXTypes::is_String(code_Line, i) == 0 && is_Block_Open == false){
                    is_Block_Open = true;
                    // Tag name extraction
                    for (std::size_t x = i-1;true;x--){
                        // std::cout<<"X value: "<<x<<"\n"; // test
                        if (x == 0) {
                            config_tagName += code_Line[0];
                            break;
                        }
                        if (LibXTypes::is_Terminatable(code_Line[x])) break;
                        if (code_Line[x] == ' ') continue;
                        else config_tagName += code_Line[x];
                    }
                }
                std::string temp_tagName;
                for (std::size_t y = config_tagName.length();y >= 0;y--){
                    temp_tagName += config_tagName[y];
                    if (y == 0) break;
                }
                config_tagName = temp_tagName;
                temp_tagName.clear();
                // std::cout<<"Tag Name: <"<<config_tagName<<">\n"; // test
            }
            // Syntax Lexical Annalyser Unit Ended
            // Syntax Parsing Unit Starts From here
            if (is_Block_Open && is_String_Open){ // content is injectable
                config_tagContent += code_Line[i];
                // std::cout<<"The Content Is Injecting\n"; // test
            }
            // Syntax Parsing Unit Starts From here - ended
        }
        // Syntax Error Unit
        if (is_Block_Open == true){
            std::cout<<"Error during tokenisation: LibXALL Error -> Can't proceed with an Opened block with '(' not closed with ')'";
        }
        // Syntax Error Unit - End
        // Finaliser Unit
        std::string temp_tagContent = config_tagContent;
        LibXTypes::remove_XStringSyntax(temp_tagContent);
        config_tagContent = temp_tagContent;
        // Finaliser Unit - end
        // std::cout<<"Tag Content: "<<config_tagContent<<"\n"; // test
        // std::cout<<"Tag Attributes: "<<config_tagAttributes<<"\n"; // test
        html = "<" + config_tagName + " " + config_tagAttributes + ">" + config_tagContent + "</" + config_tagName + ">";
        return html;
    }
};

#endif