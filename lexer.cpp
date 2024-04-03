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
std::vector<std::string> keyword_statements = {"if", "elif", "else", "for", "while", "print"};
std::vector<char> valid_parenthesis = {'(', ')', '{', '}', '[', ']'};


//token class, these will be generated to store in the parse tree 
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

//map that will store the tokens for the parser to use
std::vector<Token> Tokens;

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

std::unordered_map<std::string, Symbol> sym_table;

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
    int lineNum;
    std::string carriage = "\n";

    std::ifstream in(text);
    //ensure the file exists
    if(in.fail()){
        std::cout << "file does not exist" << std::endl;
        exit(1);
    }
    //start our line at 1
    lineNum = 1;
    //loop through character by character, including spaces
    while(in >> std::noskipws >> c){
        //check if we are at a newline, this is used to store the line count
        if(std::string(1, c) == carriage || in.peek() && in.eof()){
            std::cout << "LINENUMBER: " << lineNum << std::endl;
            lineNum++;
        }
        //checks if we found a statement, in which we have to lex differently
        if(is_keystatement(buff) && is_parenthesis(c)){
            Tokens.push_back(Token("Statement", buff, lineNum));
            Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c), lineNum));
            buff.clear();
            continue;
        }
        if(std::string(1, c) == "\""){
            buff+=c;
            c = in.get();
            while(std::string(1, c) != "\""){
                buff+=c;
                c = in.get();
            }
            buff+=c;
            Tokens.push_back(Token("Literal", buff, lineNum));
            buff.clear();
            continue;
        }
        //checks if we found a keyword, if the keyword is complete and there is a space in the next
        //in, we know that it is a complete keyword and not an identifier
        if(is_keyword(buff) && isspace(c)){
            std::string temp = buff;
            Tokens.push_back(Token("Keyword", buff, lineNum));
            buff.clear();
            if(temp == "return"){
                while(in.peek() != ';' && c != in.eof()){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Literal", buff+=c, lineNum));
                buff.clear();
                continue;          
            } else {
                continue;
            }
        }

        //special case when we want to find an identifier, we check if its not empty and if so we assume that it is
        //an identifier if it passes the is_identifier check function
        else if(isspace(c) || is_operator(std::string(1, c)) && !buff.empty() || !buff.empty() && is_parenthesis(c)){
            if(is_identifier(buff) && is_operator(std::string(1, c))){
                Tokens.push_back(Token("Identifier", buff, lineNum));
                buff.clear();
            } else if(is_identifier(buff) && c == ')'){
                Tokens.push_back(Token("Identifier", buff, lineNum));
                Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c), lineNum));
                buff.clear();
                continue;
            } else if(is_identifier(buff) && buff != ""){
                Tokens.push_back(Token("Identifier", buff, lineNum));
                buff.clear();
                continue;
            } else {
                continue;
            }
        } 
        //lexing the contents of an array
        if(is_parenthesis(c)){
            if(c == '[' && isalnum(in.peek())){
                Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c), lineNum));
                c = in.get();
                while(c != ']'){
                    if(c != ','){
                        buff+=c;
                        c=in.get();
                    } else if(c == ',' || ']'){
                        Tokens.push_back(Token("Literal", buff, lineNum));
                        Tokens.push_back(Token("Misc", std::string(1, c), lineNum));
                        buff.clear();
                        c=in.get();
                    }
                }
            } else if(c == ']'){
                Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c), lineNum));
                buff.clear();
                continue; 
            }
            Tokens.push_back(Token("Literal", buff, lineNum));
            Tokens.push_back(Token(get_parenthesis_type(std::string(1, c)), std::string(1, c), lineNum));
            buff.clear();
            continue;
        }
        
        if(is_misc(std::string(1, c)) || is_misc(std::string(1, c) + std::string(1, in.peek()))){
            if(is_misc(std::string(1, c) + std::string(1, in.peek()))){
                Tokens.push_back(Token("Misc", std::string(1, c) + std::string(1, in.peek()), lineNum));
            } else {
                Tokens.push_back(Token("Misc", std::string(1, c), lineNum));
            }
            buff.clear();
            in.get();
            continue;
        }
        //checking if literal, we know if the most recent token is an assignment operator, then the next thing that isnt
        //a space will be a literal assignment, so we use this if statment to assign literals
        if(!Tokens.empty() && is_operator(Tokens[Tokens.size()-1].get_val())){
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
                    Tokens.push_back(Token("String Literal", buff+=c, lineNum));
                    buff.clear();
                    continue;
                }
                while(!isspace(c) && in.peek() != ';' && c != in.eof() && in.peek() != ')'){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Literal", buff+=c, lineNum));
                buff.clear();
                continue;
            }
            if(curr_toke == "//"){
                while(in.peek() != ';'){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Comment", buff+=c, lineNum));
                buff.clear();
                continue;
            } 
            if(curr_toke == "return"){
                while(!isspace(c) && in.peek() != ';' && c != in.eof()){
                    buff+=c;
                    c = in.get();
                }
                Tokens.push_back(Token("Literal", buff+=c, lineNum));
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
                Tokens.push_back(Token(operator_type(std::string(1, c) + std::string(1, in.peek())), std::string(1, c) + std::string(1, in.peek()), lineNum));
                in.get();
            } else{
                Tokens.push_back(Token(operator_type(std::string(1, c)), std::string(1, c), lineNum));
            }
            buff.clear();
            continue;
        }
    }
}

//function to make our symbol table
void init_sym(){
    for(int i = 0; i < Tokens.size(); i++){
        if(Tokens[i].get_type() == "Keyword" && Tokens[i+2].get_type() == "Assignment Operator"){
            sym_table[Tokens[i+1].get_val()] = Symbol(Tokens[i].get_val(), "main", Tokens[i+3].get_val(), Tokens[i].get_lineNum());
        }
    }
}

void tester(){
    std::vector<std::string> tests = {"array_test.txt"};
    // std::vector<std::string> tests = {"array_test.txt", "full_test.txt", "if_statement_test.txt", "keyword_test.txt", "loop_test.txt", "print_test.txt", "program.txt"};
    for(int i = 0; i < tests.size(); i++){
        std::cout << std::endl << "-----------------------THIS IS TEST " << i+1 << ": " << tests[i] << "-----------------------" << std::endl;
        std::string path = "tests/";
        std::string test = tests[i];
        scan(path + test);

        //print out the contents of the map to make sure eveything is lexed
        for (int i = 0; i < Tokens.size(); i++) {
            std::cout << Tokens[i];
        }

        init_sym();

        std::cout << std::endl << "------------Symbol Table------------" << std::endl << std::endl;

        for (auto i = sym_table.begin(); i != sym_table.end(); i++) {
            std::cout << i->first << " : "<< i->second;
        }
        reset();
    }

}


int main(){
    tester();
}