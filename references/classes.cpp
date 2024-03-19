#include <iostream>
#include <string>
using namespace std;

class Bag{
    int *data;
    int size;
    public:
    Bag(int _size){
        data = new int[_size];
        for(int i = 0; i < _size; i++){
            data[i] = 0;
        }
        size = _size;
    }
    Bag(){
        data = new int[100];
        for(int i = 0; i < 100; i++){
            data[i] = 0;
        }
        size = 100;
    }
    void add(int pos){
        if(pos >= 0 && pos < size){
            data[pos]++;
        }else{
            cout << "Out of range" << endl;
        }
    }
    void sub(int pos){
        if(pos >= 0 && pos < size && data[pos] > 0){
            data[pos]--;
        }else{
            cout << "Out of range" << endl;
        }
    }
    friend std::ostream& operator<< (std::ostream& stream, const Bag& bag){
        for(int i = 0; i < bag.size; i++){
            cout << bag.data[i];
        }
        return stream;
    }
};


int main(){
    Bag b1(100);
    b1.add(3);
    b1.add(5);
    b1.add(3);
    cout << b1;
    Bag b2;
    b2.add(1);
    b2.add(1);
    b2.sub(1);
}