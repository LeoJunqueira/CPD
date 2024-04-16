#include <iostream>
#include <vector>


int mediana(int first, int last, int middle);
    int medio;
    // if((a > b) && (b > c) || (a < b) && (b < c))
    if((array[first] > array[middle]) && (array[middle] > array[last]) || (array[first] < array[middle]) && (array[middle] < array[last])){
        medio = middle;
    }
    
    if((array[middle] > array[first]) && (array[first] > array[last]) || (array[middle] < array[first]) && (array[first] < array[last])){
        medio = first;
    }

    if((array[first] > array[last]) && (array[last] > array[middle]) || (array[first] < array[last]) && (array[last] < array[middle])){
        medio = last;
    }
    return medio;
}


int main(){

    std::vector<int> array = {16,16,14,12,1,8,4,9,6,15,13,11,2,7,3,10,5};

    int i=0;
    int size = array.size();

    int first = i;
    int last = size-1;
    int middle = (last - first)/2;
    int mediana(array[first], array[last], array[middle]);

    std::cout << "Tamanho do array: " << size << std::endl;
    std::cout << "Índice do first: " << first << std::endl;
    std::cout << "Índice do last: " << last << std::endl;
    std::cout << "Índice do midle: " << middle << std::endl;
    
    return 0;
}