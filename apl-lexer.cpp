/*
This is the current implementation of the apl lexer
VERSION: 3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

std::vector<std::string> keywords = {"integer", "string", "double", "character", "boolean", "float", "array", "dictionary", "return", "for", "if", "elif", "else", "while", "print"};
std::vector<std::string> booleans = {"True", "False"};
std::vector<std::string> arithmetic_operators = {"+", "-", "/", "*", "%"};
std::vector<std::string> rational_operators = {"<", "<=", ">", ">=", "==", "!="};
std::vector<std::string> assignment_operators = {"="};
std::vector<std::string> logical_operators = {"&&", "||", "!"};
std::vector<std::string> all_operators = {"+", "-", "/", "*", "%", "<", "<=", ">", ">=", "==", "!=", "=", "&&", "||", "!"};
std::vector<std::string> misc = {";", "//", ","};
std::vector<std::string> statements = {"if", "elif", "else", "for", "while", "print"};
std::vector<std::string> valid_parenthesis = {"(", ")", "[", "]"};
std::unordered_map<std::string, Symbol> sym_table;
std::vector<Token> Tokens;


//token object, these will be generated to store in the parse tree 
class Token{
    std::string type;
    std::string val;
    int lineNum;
    public:
    Token() : type(""), val(""), lineNum() {}
    Token(std::string type, std::string val, int lineNum) : type(type), val(val), lineNum(lineNum){}

    std::string get_type(){
        return type;
    }

    std::string get_val(){
        return val;
    }

    int get_lineNum(){
        return lineNum;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Token& token){
        stream << token.type << " : " << token.val << std::endl;
        return stream;
    }
};

//our symbol object for our symbol table, this will be used in IR and CodeGen
class Symbol{
    std::string type;
    std::string scope;
    std::string value;
    int lineOfDeclaration;
    // TODO 
    // std::vector<int> linesOfUse;

    public:
    Symbol() : type(""), scope(""), value("") {}
    Symbol(std::string type, std::string scope, std::string value, int lineOfDeclaration) : type(type), scope(scope), value(value), lineOfDeclaration(lineOfDeclaration){}

    friend std::ostream& operator<< (std::ostream& stream, const Symbol& sym){
        stream << "Type: " << sym.type << " | Scope: " << sym.scope << " | Value: " << sym.value << " | Line Of Declaration: " << sym.lineOfDeclaration << std::endl;
        return stream;
    }
};

class Tokenize{
    public:
        void newline(){};
        void statement(){};
        void str(){};
        void keyword(){};
        void identifier(){};
        void array(){};
        void parenthesis(){};
        void misc(){};
        void literal(){};
        void character(){};
};

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
    } else {
        return "";
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

bool is_statement(std::string _keyword){
    if(std::count(statements.begin(), statements.end(), _keyword)){
        return true;
    } else {
        return false;
    }
}

bool is_parenthesis(std::string buff){
    if(std::count(valid_parenthesis.begin(), valid_parenthesis.end(), buff)){
        return true;
    } else {
        return false;
    }
}

std::string get_parenthesis_type(std::string buff){
    if(buff == "("){
        return "Open Parenthesis";
    } else if(buff == ")"){
        return "Close Parenthesis";
    } else if(buff == "{"){
        return "Open Bracket";
    } else if(buff == "}"){
        return "Close Bracket";
    } else if(buff == "["){
        return "Open Square Bracket";
    } else if(buff == "]"){
        return "Close Square Bracket";
    } else {
        return "";
    }
}

void reset(){
    Tokens.clear();
    sym_table.clear();
}



//this is the main scan function
//this function will turn every item in the file into a token
//each one of those tokens is pushed onto the stack
void scan(std::string text){
    char c;
    std::string buff;
    std::string type;
    std::string potential_operator;
    int lineNum = 1;
    char carriage = '\n';
    Tokenize tokenize;

    std::ifstream in(text);
    //ensure the file exists
    if(in.fail()){
        std::cout << "file does not exist" << std::endl;
        exit(1);
    }
    //main while loop
    while(in >> std::noskipws >> c){
        if(c == carriage || in.peek() && in.eof())
        {
            tokenize.newline();
        } 
        else if(buff == "\"")
        {
            tokenize.str();
        } 
        else if(is_parenthesis(buff))
        {
            tokenize.parenthesis();
        }
        else if(is_misc(buff))
        {
            tokenize.misc();
        } 
        else if(is_keyword(buff) && isspace(c))
        {
            if(is_statement && is_parenthesis(std::string(1,c)))
            {
                tokenize.statement();
            } 
            else 
            {
                tokenize.keyword();
            }
        }
        else if(!is_keyword(buff) && !is_operator(buff) && isspace(c) && buff != "")
        {
            tokenize.literal();
        }
        else
        {
            tokenize.character();
        }
    }
}





int main(){

}