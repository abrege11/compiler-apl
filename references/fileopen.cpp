#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//if you declare text as an int and there isn't an int given, the program breaks, even commas etc
int main(){
    string text;
    //tries to find test.txt in my project folder
    ifstream in("program.txt");
    //this is failure checking, very important to include
    if(in.fail()){
        //error message
        cout << "Bad" << endl;
        exit(1);
    }
    //this is saying to do this while it isnt the end of the file
    while(!in.eof()){
    //this take the text from the file
    in >> text;
    //this prints it out
    cout << text << endl;
    }
}


void findlinecount(){
    int count=0;
    string text;
    ifstream in("notes.cpp");
    if(in.fail()){
        cout << "Bad" << endl;
        exit(1);
    }
    while(!in.eof()){
        getline(in, text);
        for (int i=0; i<text.length(); i++){
            if (text[i] == ' '){
                count++;
            }
        }        
    }
    cout << count;
}





void nextnotes(){
    string text;
    ifstream in("test.txt");
    if(in.fail()){
        cout << "Bad" << endl;
        exit(1);
    }
        //loop to get a certain line of text
        for(int linenum = 1; linenum < 29; linenum++){
            getline(in, text);
        }
    cout << text;
}

void bombnotes(){
    int n = 100;
    string *text = new string[n];
    ifstream in("test.txt");
    if(in.fail()){
        cout << "Bad" << endl;
        exit(1);
    }
    int i;
    for (i = 0; !in.eof(); i++)
    {
        getline(in, text[i]);
    }
    cout << i << " lines." << endl;
    for (int curr = i-1; curr >=0; curr--){
        cout << curr << " " << text[curr] << endl;
    }

}

ofstream ofs;


int mainnotes(){
    /*
    string text;
    ofstream file ("test.txt");
        for(int i=0; i<7; i++){
            file << 'a';
        }
    */
    int count=0;
    ofs.open("test.txt", ios::out | ios::trunc);
    ofs.close();

    ifstream in("notes.cpp");
    if(in.fail()){
        cout << "Bad" << endl;
        exit(1);
    }

//    ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
//    ofs.close();
}