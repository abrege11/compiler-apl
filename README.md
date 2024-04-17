# Abe's Programming Language (APL)
This is my senior project, I plan on creating a simple compiler that will later be used to write another compiler. 

This is a very ambitious project that I started in December of 2023 over winter break of my junior year of university at NMU (Northern Michigan University). I completed the first version of the lexer in about a month with research factored in, and I haven't been able to work on much more up to now, Feb 16. due to a large course load. I hope to be able to expand this project little by little as the semester goes on.

<br>

# Documentation

## 1.00 - All valid inputs
<br> **Types**: `integer`, `double`, `boolean`, `string`, `character`, `array`
<br> **Operators**: `+`, `-`, `*`, `/`, `%`, `&&`, `||`, `!`, `=`, `!=`, `==`, `<`, `<=`, `>`, `>=`
<br> **Misc**: `//`, `;`
<br> **Statments/Loops**: `if`, `elif`, `else`, `while`, `for`, `return`, `print()`



## 1.01 - Declarations:
<br> `<type> <var> = <val>;`
<br><br>-  `integer i = 1;`
<br>- `double d = 1.1;`
<br>- `boolean b = True; | False;`
<br>- `string s = "this is a string";`
<br>- `character c = 'c';`
<br>- `array arr = [integer];`
<br>

## 1.02 - Token Types:
**Identifier**: `variable names`, `function names` <br><br>
**Keyword**: Keywords with special function in langauge (`for`, `if`, `while`) <br><br>
**Numeric Literal**: Numeric values (`ints`, `doubles`)<br><br>
**String Literal**: Data enclosed in quotes `" "` <br><br>
**Boolean Literal**: `True` or `False`<br><br>
**Character Literal**: Single characters (`'a'`, `'b'`, `'1'`, `'2'`)<br><br>
**Punctuation**: Commas `,` and semicolons `;`<br><br>
**Comments**: Anything on the same line and proceeding `//`<br><br>
**Whitespace**: `spaces`, `tabs`, `newlines`<br><br>
**EOF**: indication of end of source file<br><br>


## 1.03 - Operators:
- Arithmetic:
    - addition: +
    - subtraction: -
    - division: /
    - multiplication: *
    - modulus: %
- Rational:
    - less than: <
    - less than or equal to: <=
    - greater than: >
    - greater than or equal to: >=
    - equal to: ==
    - not equal to: != 
- Assignment:
    - assign to: = 
- Logical:
    - logical and: &&
    - logical or: ||
    - logical not: ! <br>



## 1.04 - APL Grammar | BNF Notation
`<program>` ::= `<statement>` | `<program>` `<statement>` 

<statement> ::= <declaration> | <assignment> | <if_statement> | <while_loop> | <for_loop> | <return_statement> | <print_statement> \

<declaration> ::= <type> <identifier> '=' <value> ';' \

<assignment> ::= <identifier> '=' <expression> ';' \

<if_statement> ::= 'if' '(' <expression> ')' '{' <program> '}' <elif_statement> <else_statement> \

<elif_statement> ::= 'elif' '(' <expression> ')' '{' <program> '}' <elif_statement> | ε \

<else_statement> ::= 'else' '{' <program> '}' | ε \

<while_loop> ::= 'while' '(' <expression> ')' '{' <program> '}' \

<for_loop> ::= 'for' '(' <assignment> ';' <expression> ';' <assignment> ')' '{' <program> '}' \

<return_statement> ::= 'return' <expression> ';' \

<print_statement> ::= 'print' '(' <expression> ')' ';' \

<expression> ::= <logical_expression> \

<logical_expression> ::= <logical_term> | <logical_expression> '&&' <logical_term> | <logical_expression> '||' <logical_term> \

<logical_term> ::= <comparison> | '!' <logical_term> \

<comparison> ::= <arithmetic_expression> <comparison_operator> <arithmetic_expression> \

<arithmetic_expression> ::= <term> | <arithmetic_expression> '+' <term> | <arithmetic_expression> '-' <term> \

<term> ::= <factor> | <term> '*' <factor> | <term> '/' <factor> | <term> '%' <factor> \

<factor> ::= <value> | '(' <expression> ')' \

<value> ::= <numeric_literal> | <string_literal> | <boolean_literal> | <character_literal> | <identifier> | <array_literal> \

<array_literal> ::= '[' <type> ']' \

<type> ::= 'integer' | 'double' | 'boolean' | 'string' | 'character' | 'array' \

<identifier> ::= <variable_name> | <function_name> \

<comparison_operator> ::= '==' | '!=' | '<' | '<=' | '>' | '>=' \

<numeric_literal> ::= <integer_literal> | <double_literal> \

<integer_literal> ::= [0-9]+ \

<double_literal> ::= [0-9]+ '.' [0-9]+ \

<string_literal> ::= '"' <string_characters> '"' \

<boolean_literal> ::= 'True' | 'False' \

<character_literal> ::= '\'' <character> '\'' \

<string_characters> ::= <string_character> | <string_characters> <string_character> \

<string_character> ::= <any_character_except_double_quote> \

<variable_name> ::= <alphabetic_character> | <variable_name> <alphabetic_character> | <variable_name> <numeric_character> \

<function_name> ::= <alphabetic_character> <alphabetic_character> | <function_name> <alphabetic_character> | <function_name> <numeric_character> \

<alphabetic_character> ::= [a-zA-Z] \

<numeric_character> ::= [0-9] \

