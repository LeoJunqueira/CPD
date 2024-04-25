#include <iostream>   // Biblioteca para entrada e saída
#include <vector>     // Biblioteca para vetores
#include <random>     // Biblioteca do Random 

// Função que imprime o vetor
void imprimeVetor(const std::vector<int>& vetor){
    for(int i=0; i < vetor.size(); i++){
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;
}

// Função que imprime o vetor destacando os elementos trocados
void imprimeStatus(const std::vector<int>& vetor, int key, int larger){
    for(int i=0; i < vetor.size(); i++){
        if(i == key || i == larger){
            std::cout << "(" << vetor[i] << ") ";
        }else{
            std::cout << vetor[i] << " ";
        }
    }
    std::cout << std::endl;
}



// Função que recebe um vetor, o primeiro e o último número de índice deste vetor
// e devolve a mediana deste vetor
int mediana(std::vector<int> array, int first, int last){
    
    int middle = (last - first)/2;
    int medio;
    // if((a > b) && (b > c) || (a < b) && (b < c))
    if(((array[first] > array[middle]) && (array[middle] > array[last])) || ((array[first] < array[middle]) && (array[middle] < array[last]))){
        medio = middle;
    }
    
    if(((array[middle] > array[first]) && (array[first] > array[last])) || ((array[middle] < array[first]) && (array[first] < array[last]))){
        medio = first;
    }

    if(((array[first] > array[last]) && (array[last] > array[middle])) || ((array[first] < array[last]) && (array[last] < array[middle]))){
        medio = last;
    }

    return medio;
}

// Função recebe o primeiro e o último número de índice deste vetor 
// e retorna um número aleatório nesse intervalo
int random(int min, int max) {
    // Cria um gerador de números aleatórios
    std::random_device rd;

    // Inicializa um gerador de números aleatórios com semente
    std::mt19937 gen(rd());

    // Define o intervalo
    std::uniform_int_distribution<> distr(min, max);

    // Gera um número aleatório no intervalo
    int aleatorio = distr(gen);

    return aleatorio;
}

// Coloca o elemento A e B de posição
void swap(std::vector<int>& array, int elmtA, int elmtB){
    
    int swp = array[elmtA];
    array[elmtA] = array[elmtB];
    array[elmtB] = swp;
    
}

void medianaLomuto(std::vector<int> array, int fst, int lst, const std::string& arquivo){
    imprimeVetor(array);
    int medio = mediana(array, fst, lst);
    std::cout << "Mediana: " << array[medio] << std::endl;
    swap(array, fst, medio);
    imprimeVetor(array);
    int size = lst - fst;
    int larger = fst +1;  
    int key;      // Apagar e declarar dentro do FOR 
    for(int i = 1; i < size; i++){
        key = i+1;
        if(array[fst] > array[key]){
            if(larger == key){
                larger++;
            }else{
                swap(array, larger, key);
                larger++;
            }
        }
        imprimeStatus(array, key, larger);
    }
    swap(array, fst, larger-1);
    imprimeStatus(array, key, larger);
    key = larger -1;
    if(key>fst){
        medianaLomuto(array, fst, key-1, "stats-mediana-lomuto.txt");
    }
    if(key<lst){
        medianaLomuto(array, key+1, lst, "stats-mediana-lomuto.txt");
    }
    // std::cout << "Valor smaller: " << array[smaller] << std::endl;
    // std::cout << "Índice smaller: " << smaller << std::endl;
}

int main(){

    // std::vector<int> array = {16,16,14,12,1,8,4,9,6,15,13,11,2,7,3,10,5};
    std::vector<int> array = {16,16,14,12,1,8,4,9,6,15,5,11,2,7,3,10,13};
    // std::vector<int> array = {16,9,14,12,1,8,4,5,6,15,13,11,2,7,3,10,16};
    // std::vector<int> array = {16,5,14,12,1,8,4,16,6,15,13,11,2,7,3,10,9};

    int i=1;
    int size = array[0];
    int first = i;
    int last = size;
/*
imprimeVetor(array);
int medio = mediana(array, first, last);
imprimeVetor(array);
*/
medianaLomuto(array, first, last, "stats-mediana-lomuto.txt");

///////////////   TESTES DA TROCA    ////////////////////////////////////
// Troquei o nome de algumas variáveis, os testes não vão funcionar
/*
    // int swap(array, first, last);   // Chamada da função
    // int swap(array, smaller, larger);   // Chamada da função

    std::cout << "Valor do last: " << array[last] << std::endl;

    swap(array, first, last);

    std::cout << "Valor do first: " << array[first] << std::endl;
    std::cout << "Valor do last: " << array[last] << std::endl;
*/
///////////////   FIM - TESTES DA TROCA    //////////////////////////////


///////////////   TESTES DO RANDOM    ////////////////////////////////////
/*
    // int numR = random(first, last);  // Chamada da função

    std::cout << "Índice aleatório: " << numR << std::endl;
    std::cout << "Número aleatório: " << array[numR] << std::endl;

    numR = random(1, 10);
    std::cout << "Número aleatório: " << numR << std::endl;

    numR = random(1, 10);
    std::cout << "Número aleatório: " << numR << std::endl;

    numR = random(1, 10);
    std::cout << "Número aleatório: " << numR << std::endl;
*/
///////////////   FIM - TESTES DA RANDOM    //////////////////////////////


///////////////   TESTES DA MEDIANA    //////////////////////////////////
/*
    int i=1;
    int size = array[0];
    int first = i;
    int last = size;

    // int medio = mediana(array, first, last);  // Chamada da função

    std::cout << "Tamanho do array: " << size << std::endl;
    std::cout << "Índice do first: " << first << std::endl;
    std::cout << "Índice do last: " << last << std::endl;
    std::cout << "Valor do last: " << array[last] << std::endl;
    std::cout << "Índice da mediana: " << medio << std::endl;
    std::cout << "Valor da mediana: " << array[medio] << std::endl;
*/
///////////////   FIM - TESTES DA MEDIANA    //////////////////////////////////

    std::cout << "Rodou!" << std::endl;

    return 0;
}