#include <iostream>
#include <vector>


int main(){
    std::vector<int> v1 = {1, 2, 3};
    for(int i=0; i < v1.size(); i++){
        std::cout << v1[i];
    }
}