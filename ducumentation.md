# APL - Documentation

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


### Operators:
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

`<statement>` ::= `<declaration>` | `<assignment>` | `<if_statement>` | `<while_loop>` | `<for_loop>` | `<return_statement>` | `<print_statement>` 

`<declaration>` ::= `<type>` `<identifier>` = `<value>` ; 

`<assignment>` ::= `<identifier>` = `<expression>` | `<value>` ; 

`<if_statement>` ::= if ( `<expression>` ) { `<program>` } `<elif_statement>` `<else_statement>`

`<elif_statement>` ::= elif ( `<expression>` ) { `<program>` } `<elif_statement>`

`<else_statement>` ::= else { `<program>` }

`<while_loop>` ::= while ( `<expression>` ) { `<program>` } 

`<for_loop>` ::= for ( `<assignment>` ; `<expression>` ; `<assignment>` ) { `<program>` } 

`<return_statement>` ::= return `<expression>` ; 

`<print_statement>` ::= print ( `<expression>` | `<value>` ) ; 

`<expression>` ::= `<logical_expression>` 

`<logical_expression>` ::= `<logical_term>` | `<logical_expression>` && `<logical_term>` | `<logical_expression>` || `<logical_term>` 

`<logical_term>` ::= `<comparison>` | ! `<logical_term>`

`<comparison>` ::= `<arithmetic_expression>` `<comparison_operator>` `<arithmetic_expression>` 

`<value>` ::= `<numeric_literal>` | `<string_literal>` | `<boolean_literal>` | `<character_literal>` | `<identifier>` | `<array_literal>`

`<array_literal>` ::= `[ <type> ]` 

`<type>` ::= integer | double | boolean | string | character | array 

`<identifier>` ::= `<variable_name>` | `<function_name>`

`<comparison_operator>` ::= `==` | `!=` | `<` | `<=` | `>` | `>=`

`<numeric_literal>` ::= `<integer_literal>`

`<integer_literal>` ::= [0-9]

`<string_literal>` ::= " `<string_characters>` " 

`<boolean_literal>` ::= True | False 

`<character_literal>` ::= `<character>` 

`<string_characters>` ::= `<string_character>` | `<string_characters>` `<string_character>` 

`<string_character>` ::= `<any_character_except_double_quote>`

`<variable_name>` ::= `<alphabetic_character>` | `<variable_name>` `<alphabetic_character>` | `<variable_name>` `<numeric_character>`

`<function_name>` ::= `<alphabetic_character>` `<alphabetic_character>` | `<function_name>` `<alphabetic_character>` | `<function_name>` `<numeric_character>` 

`<alphabetic_character>` ::= [a-zA-Z]

`<numeric_character>` ::= [0-9]

