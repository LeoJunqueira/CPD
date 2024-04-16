#include<iostream>
#include<iostream>


int main(){
    int a = 5;
    int b = 3;
    int c = 1;

    //int mediana(int first, int last, int middle);
    if((a > b) && (b > c) || (a < b) && (b < c)){
        std::cout << "O B é o médio." << std::endl;
    }
    return 0;
}