# tinyCompiler
Very simple compiler

## Grammar

    <program> ::= <expr>

    <expr>    ::= <term> { ( "+" | "-" ) <term> }
    <term>    ::= <term> { ( "*" | "/" ) <term> }
    <factor>  ::= <NUM> | "(" <expr> ")"

    <NUM>     ::= <digit> { <digit> }
    <digit>   ::= "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "0"
