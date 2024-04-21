/*
THIS IS A LEGACY VERSION OF THE APL LEXER
VERSION: 1
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> keywords = {"integer", "string", "double", "character", "boolean", "float", "array", "dictionary", "return", "for", "if", "elif", "else", "while", "print"};
std::vector<std::string> booleans = {"True", "False"};
std::vector<std::string> arithmetic_operators = {"+", "-", "/", "*", "%"};
std::vector<std::string> rational_operators = {"<", "<=", ">", ">=", "==", "!="};
std::vector<std::string> assignment_operators = {"="};
std::vector<std::string> logical_operators = {"&&", "||", "!"};
std::vector<std::string> all_operators = {"+", "-", "/", "*", "%", "<", "<=", ">", ">=", "==", "!=", "=", "&&", "||", "!"};
std::vector<std::string> misc = {";", "//", ","};
std::vector<std::string> keyword_statements = {"if", "elif", "else", "for", "while", "print"};
std::vector<char> valid_parenthesis = {'(', ')', '{', '}', '[', ']'};

//token class, these will be generated to store in the parse tree 
class Token{
    std::string type;
    std::string val;
    public:
    Token() : type(""), val("") {}
    Token(std::string type, std::string val) : type(type), val(val){}

    std::string get_val(){
        return val;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Token& token){
        stream << token.type << " : " << token.val << std::endl;
        return stream;
    }
};

//map that will store the tokens for the parser to use
std::vector<Token> Tokens;

//this is a helper funciton to check if the buff is containing a keyword
bool is_keyword(std::string _keyword){
    if(std::count(keywords.begin(), keywords.end(), _keyword)){
        return true;
    }
    return false;
}

//this is a helper function to see if the buffer is currently holding an identifier
bool is_identifier(std::string _identifier){
    for(int i = 0; i < _identifier.length(); i++){
        if(isalpha(_identifier[i]) && _identifier != ""){
            continue;
        } else {
            return false;
        }
    }
    return true;
}

//helper function to check if the buffer is an operator
bool is_operator(std::string _operator){
    if(std::count(all_operators.begin(), all_operators.end(), _operator)){
        return true;
    } else {
        return false;
    }
}



//helper function to get specific type of operator for the token
std::string operator_type(std::string _operator){
    if(std::count(arithmetic_operators.begin(), arithmetic_operators.end(), _operator)){
        return "Arithmetic Operator";
    } else if(std::count(assignment_operators.begin(), assignment_operators.end(), _operator)){
        return "Assignment Operator";
    } else if(std::count(rational_operators.begin(), rational_operators.end(), _operator)){
        return "Rational Operator";
    } else if(std::count(logical_operators.begin(), logical_operators.end(), _operator)){
        return "Logical Operator";
    }
}

bool is_boolean(std::string _boolean){
    if(_boolean == "True" || _boolean == "False"){
        return true;
    } else {
        return false;
    }
}

bool is_misc(std::string _misc){
    if(std::count(misc.begin(), misc.end(), _misc)){
        return true;
    } else {
        return false;
    }
}

bool is_keystatement(std::string _keyword){
    if(std::count(keyword_statements.begin(), keyword_statements.end(), _keyword)){
        return true;
    } else {
        return false;
    }
}

bool is_parenthesis(char _c){
    if(std::count(valid_parenthesis.begin(), valid_parenthesis.end(), _c)){
        return true;
    } else {
        return false;
    }
}

std::string get_parenthesis_type(std::string _c){
    if(_c == "("){
        return "Open Parenthesis";
    } else if(_c == ")"){
        return "Close Parenthesis";
    } else if(_c == "{"){
        return "Open Bracket";
    } else if(_c == "}"){
        return "Close Bracket";
    } else if(_c == "["){
        return "Open Square Bracket";
    } else if(_c == "]"){
        return "Close Square Bracket";
    } else {
        return "";
    }
}


//this is the main scan function
//this function will turn every item in the file into a token
//each one of those tokens is pushed onto the stack
void scan(std::string text){
    char c;
    std::string buff;
    std::string type;
    std::string potential_operator;

    std::ifstream in(text);
    //ensure the file exists
    if(in.fail()){
        std::cout << "file does not exist" << std::endl;
        exit(1);
    }
    //loop through character by character, including spaces
    while(in >> std::noskipws >> c){
        //checks if we found a statement, in which we have to lex differently
        if(is_keystatement(buff) && is_parenthesis(c)){
            Tokens.push_back(Token("Statement", buff));
            Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c)));
            buff.clear();
            continue;
        }
        //checks if we found a keyword, if the keyword is complete and there is a space in the next
        //in, we know that it is a complete keyword and not an identifier
        if(is_keyword(buff) && isspace(c)){
            Tokens.push_back(Token("Keyword", buff));
            buff.clear();
            continue;
        }

        //special case when we want to find an identifier, we check if its not empty and if so we assume that it is
        //an identifier if it passes the is_identifier check function
        else if(isspace(c) || is_operator(std::string(1, c)) && !buff.empty() || !buff.empty() && is_parenthesis(c)){
            if(is_identifier(buff) && is_operator(std::string(1, c))){
                Tokens.push_back(Token("Identifier", buff));
                buff.clear();
            } else if(is_identifier(buff) && c == ')'){
                Tokens.push_back(Token("Identifier", buff));
                Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c)));
                buff.clear();
                continue;
            } else if(is_identifier(buff) && buff != ""){
                Tokens.push_back(Token("Identifier", buff));
                buff.clear();
                continue;
            } else {
                continue;
            }
        } 

        if(is_parenthesis(c)){
            Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c)));
            continue;
        }

        if(is_misc(std::string(1, c)) || is_misc(std::string(1, c) + std::string(1, in.peek()))){
            if(is_misc(std::string(1, c) + std::string(1, in.peek()))){
                Tokens.push_back(Token("Misc", std::string(1, c) + std::string(1, in.peek())));
            } else {
                Tokens.push_back(Token("Misc", std::string(1, c)));
            }
            buff.clear();
            in.get();
            continue;
        }
        //checking if literal, we know if the most recent token is an assignment operator, then the next thing that isnt
        //a space will be a literal assignment, so we use this if statment to assign literals
        if(!Tokens.empty()){
            bool temp = true;
            std::string curr_toke = Tokens[Tokens.size()-1].get_val();
            if(is_operator(curr_toke) || get_parenthesis_type(curr_toke) != ""){
                if(c == '"'){
                    buff+=c;
                    c = in.get();
                    while(c != '"'){
                        buff+=c;
                        c = in.get();
                    }
                    Tokens.push_back(Token("String Literal", buff+=c));
                    buff.clear();
                    continue;
                }
                while(!isspace(c) && in.peek() != ';' && c != in.eof() && in.peek() != ')'){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Literal", buff+=c));
                buff.clear();
                continue;
            }
            if(curr_toke == "//"){
                while(in.peek() != ';'){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Comment", buff+=c));
                buff.clear();
                continue;
            } 
            if(curr_toke == "return"){
                while(!isspace(c) && in.peek() != ';' && c != in.eof()){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Literal", buff+=c));
                buff.clear();
                continue;
            }
            if(curr_toke == "[" || curr_toke == ","){
                char p = in.peek();
                while(p != ',' && p != ']'){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Literal", buff+=c));
                buff.clear();
                continue;
            }
        }
        
        //if its alphanum we assume its a keyword, boolean, or identifier of some sort so we just add it
        if(isalpha(c)){
                buff+=c;
            }
        //checking if the current character is a valid op, or if the current character plus the next character is an op
        //we can do this manually since none of our operators exceed a length of 2
        //if either of these are caught, we check which one it is, and move accordingly using the operator_type function
        //special case if it is a double length operator, we use in.get() to skip the next character
        //so we dont process say the = at the end of <= individually
        if(is_operator(std::string(1, c)) || is_operator(std::string(1, c) + std::string(1, in.peek()))){
            if(is_operator(std::string(1, c) + std::string(1, in.peek()))){
                Tokens.push_back(Token(operator_type(std::string(1, c) + std::string(1, in.peek())), std::string(1, c) + std::string(1, in.peek())));
                in.get();
            } else{
                Tokens.push_back(Token(operator_type(std::string(1, c)), std::string(1, c)));
            }
            buff.clear();
            continue;
        }
    }
}



int main(){
    scan("tests/full_test.txt");

    //print out the contents of the map to make sure eveything is lexed
    for (int i = 0; i < Tokens.size(); i++) {
        std::cout << Tokens[i] << std::endl;
    }
}