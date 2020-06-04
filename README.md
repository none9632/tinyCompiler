# tinyCompiler

This is a very small and simple compiler that implements basic arithmetic operations.
This project was created in order to understand the basic principles of the compiler
that will later be used to create [myCompiler](https://github.com/none9632/myCompiler).
An expression of type `1+1` ( *or another expression that matches the grammar* ) is fed to 
the compiler input and the output file output.asm in which this expression is implemented
in NASM assembler.

## Build and run

    $ make
    $ ./tinyCompiler [options] <expression>
   
## Testing

    $ make test

## Grammar

    <program> ::= <expr>

    <expr>    ::= <term> { ( "+" | "-" ) <term> }
    <term>    ::= <term> { ( "*" | "/" ) <term> }
    <factor>  ::= <NUM> | "(" <expr> ")"

    <NUM>     ::= <digit> { <digit> }
    <digit>   ::= "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "0"

## Author

Ivan Andreev\
Email:  ivanandreev1234@protonmail.com

## Links

* [CS143: Compiler](https://www.keithschwarz.com/cs143/WWW/sum2011/)

## License

[MIT License](LICENSE)