# XALL1 - Markup Language
XALL1 is a Markup Language for creating such a high quality websites with a lot of ease. This is the official repository for Obtaining `libXALL` which is the official library responsible for Compiling the XALL Lang Into HTML Code So that the browsers can execute the XALL Programs with a lot of ease. `libXALL` also allows you to create a custom Compiler for XALL With a lot of ease, You only need to know about how `libXALL` works and what functions & classes are there in `libXALL` and how you may use them.

## Installing libXALL
Installing `libXALL` is very simple just clone this repository via this command and then copy the XALL `Cxx Headerfile` where every you want it to be.

```bash
# Copy command
git clone https://github.com/darkyboys/libxall.git
cd libxall/src
cp xall.hpp ..
cp xall.hpp ..
mkdir xall
cp xall.hpp xall
echo "libXALL Was installed successfully, Now use it localy!. Move max directory where every you want"
echo ""
```

## Library - Refrence
This is the simple yet usefull documentation for `libXALL` for developers who are seeking to create a `XALL Compiler/Transpiler` like `xtrans`. This is for everyone!

*Note - libXALL Will Only Compile 1 Line Of XALL Program At A Time So You Would Manually Need To Implement File To Line Conversion*

### Basics
`libXALL` is written only for C++ no backward official Compatiblity with C as `libXALL` relies on C++ STL for a lot of it's parts, So it is required for the developer to be familiar with C++ for learning `libXALL`.

 - Install LibXALL and then include it.

```cxx
// Include libXALL - Ensuring that you have installed it in your development environment.
#include "xall/xall.hpp"
```

**XALL Class**
`XALL` class in **libXALL** is only what you should take care about because, This is the only class which is responsible for compiling a line of `XALL` program into `html` code. `libXALL` also has it's own `libXTypes` and `libXCompile` but you should only take care about `XALL` class.

**XALL Class & It's Methods**
`XALL` Class only has 1 usefull method which is `XCompile()` which returns the compiled version of xall program to html in form of `std::string`. TO Use this you must initalise the `XALL` Class.

```cxx
#include "xall/xall.hpp"
#include <iostream>

int main(){
    XALL myCompiler("XALL Program Line Of Code must go here");
    std::cout<<myCompiler.XCompile();
}
```

XCompile reads the initalised string and then returns the compiled form of that string.

For internals - Please refer the documentation.


## Writting XALL Programs
XALL Allows you to write your XALL Program in soo many ways just follow the syntax.

**Blocks**
`Blocks` in `XALL` are the  basic building blocks for creating webpages and they are directly comverted into html tags. Syntax:- blockname ( "Block content as string" ) ;

Examole:-
```xall
p("This is the paragraph tag!");
```

You can structure blocks like how you want
```xall
p
(
    "This is p"
);
```

You can add 2 strings by just writting them
```xall
h1 ("This is " "h1");
p(
    "This is p"
    "A Cool Element"
    "This webpage is written in XALL"
);
```

**Arguments**
`Arguments` in `XALL` are also vvery important as they are compiled into html attributes. Syntax :- block("content") [attribute name:"attribute value"];

Example:-
```xall
h1("This is my headding")[style:"h1"];
```

Multiple attributes can be also given
```xall
h1 ("Hello world 2025") [id:"Myh1"][class:"myH1-class"][style:"Hy"]
```

Or format it like
```xall
h1
(
    "This is headding 1"
)
[style: "h1"]
[id: "h1-id"]
[class: "h1-class"]
;
```

## Thanks!
Contributions Are Open Just Follow The <a href="CONTRIBUTING.md">Contribution GuideLines</a>

Copyright (c) ghgltggamer 2025
