#include "xall.hpp"
#ifdef LIB_XALL1

#include <string>
#include <iostream>

int main(){
    std::string code = "pnd ( \"Hello world 2024\" ) [href:\"abc\"][std:\"gtl\"][ gtl:\"bgfssffk\"    ] ;";
    XALL a = code;
    std::string get_HTML = a.XCompile() + "\n";
    std::cout<<get_HTML;
    // std::cout<<LibXTypes::is_Terminatable('a')<<"\n";
    // std::cout<<"The Code Result Was: "<<LibXTypes::is_String(code, code.length()-3);
}

#endif